//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "base.h"
#include "mine.h"
#include "nmobj.h"
#include "graph.h"
#include "gksvcl.h"

#include "ContexterM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TContexterF *ContexterF;

/////////////////////////////////////////////////
// Form-State
class TContexterF::TState{
public:
  PGks Gks;
  TStr NmObjBsFNm;
  PNmObjBs NmObjBs;
  PBowDocBs BowDocBs;
  PBowDocWgtBs BowDocWgtBs;
  TStr RootNmObjStr;
  PGraph CtxTree;
  int SubNodes, DrawLevels, CtxLen, FontSize;
  UndefCopyAssign(TState);
public:
  TState():
    Gks(TVclGks::New(ContexterF->Pb)),
    NmObjBsFNm(), NmObjBs(), BowDocBs(),
    SubNodes(8), DrawLevels(1), CtxLen(5), FontSize(8){}
  ~TState(){}
};

/////////////////////////////////////////////////
// Context-Tree
PGraph GetCtxTreeGraph(
 const PNmObjBs& NmObjBs, const TStr& RootNmObjStr, const int& MxDist){
  // create distance graph
  PGraph Graph=TGraph::New();
  // create root note
  int RootNmObjId=NmObjBs->GetNmObjId(RootNmObjStr);
  PVrtx RootVrtx=TGVrtx::New(RootNmObjId, RootNmObjStr);
  Graph->AddVrtx(RootVrtx);
  // create distance vector
  TIntV NmObjDistV(NmObjBs->GetNmObjs()); NmObjDistV.PutAll(-1);
  NmObjDistV[RootNmObjId]=0;
  // create queue
  TIntPrQ OpenNmObjIdDistPrQ; OpenNmObjIdDistPrQ.Push(TIntPr(RootNmObjId, 0));
  while (!OpenNmObjIdDistPrQ.Empty()){
    // get name-object-id from queue
    int NmObjId=OpenNmObjIdDistPrQ.Top().Val1;
    int NmObjDist=OpenNmObjIdDistPrQ.Top().Val2;
    OpenNmObjIdDistPrQ.Pop();
    IAssert(NmObjDistV[NmObjId]==NmObjDist);
    // get named-object string
    TStr NmObjStr=NmObjBs->GetNmObjStr(NmObjId);
    TStr UcNmObjStr=NmObjStr.GetUc();
    printf("[%s:%d] ", NmObjStr.CStr(), NmObjDist);
    // check distance
    if (NmObjDist>MxDist){continue;}
    // get named-object vertex
    PVrtx SrcVrtx=Graph->GetVrtx(NmObjId);
    // get named-object children
    TIntPrV FqNmObjIdPrV; NmObjBs->GetFqNmObjIdPrV(NmObjStr, FqNmObjIdPrV);
    int SubNmObjs=FqNmObjIdPrV.Len();
    // traverse named-object children
    int CreatedSubNmObjs=0;
    for (int SubNmObjN=0; SubNmObjN<SubNmObjs; SubNmObjN++){
      // get child data
      int SubNmObjFq=FqNmObjIdPrV[SubNmObjN].Val1;
      int SubNmObjId=FqNmObjIdPrV[SubNmObjN].Val2;
      TStr SubNmObjStr=NmObjBs->GetNmObjStr(SubNmObjId);
      TStr UcSubNmObjStr=SubNmObjStr.GetUc();
      TStr SubNmObjVNm=SubNmObjStr;
      // calculate and add context string formed from coref-named-objects
      {TChA CtxChA; TIntPrV FqNmObjIdPrV;
      ContexterF->State->NmObjBs->GetFqNmObjIdPrV(SubNmObjStr, FqNmObjIdPrV);
      FqNmObjIdPrV.Sort(false);
      FqNmObjIdPrV.Trunc(ContexterF->State->CtxLen); FqNmObjIdPrV.Clr();
      for (int NmObjN=0; NmObjN<FqNmObjIdPrV.Len(); NmObjN++){
        TStr CoNmObjStr=ContexterF->State->NmObjBs->GetNmObjStr(FqNmObjIdPrV[NmObjN].Val2);
        if (SubNmObjStr!=CoNmObjStr){
          CtxChA+='['; CtxChA+=CoNmObjStr; CtxChA+=']'; CtxChA+='\\';}
      }
      if (!CtxChA.Empty()){
        SubNmObjVNm=SubNmObjStr+"\\"+CtxChA;}}
      // push child named-object-id if necessary
      if (NmObjDistV[SubNmObjId]==-1){
        // check number of subnodes
        int MxCreatedSubNmObjs=0;
        switch (NmObjDist){
          case 0: MxCreatedSubNmObjs=/*20;*/ContexterF->State->SubNodes; break;
          case 1: MxCreatedSubNmObjs=4; break;
          case 2: MxCreatedSubNmObjs=2; break;
          case 3: MxCreatedSubNmObjs=1; break;
          case 4: MxCreatedSubNmObjs=1; break;
          default: MxCreatedSubNmObjs=0; break;
        }
        // check if stop creating branches
        CreatedSubNmObjs++;
        if (CreatedSubNmObjs>MxCreatedSubNmObjs){break;}
        // push edge
        OpenNmObjIdDistPrQ.Push(TIntPr(SubNmObjId, NmObjDist+1));
        NmObjDistV[SubNmObjId]=NmObjDist+1;
        // create vertex
        TStr VNm=SubNmObjVNm;
        PVrtx DstVrtx=TGVrtx::New(SubNmObjId, VNm);
        Graph->AddVrtx(DstVrtx);
        // create edge
        //TStr ENm=TStr("_")+TInt::GetStr(NmObjId)+"-"+TInt::GetStr(SubNmObjId);
        TStr ENm=TInt::GetStr(SubNmObjFq);
        // calculate and add context string formed from coref-named-objects
        if (ContexterF->InterNmObjContextCb->Checked){
          TChA CtxChA;
          TStr SrcNmObjStr=NmObjStr;
          TChA DstNmObjChA=DstVrtx->GetVNm();
          if (DstNmObjChA.IsChIn('\\')){
            DstNmObjChA.Trunc(DstNmObjChA.SearchCh('\\'));}
          TStr DstNmObjStr=DstNmObjChA;
          PBowSpV ConceptSpV=ContexterF->State->NmObjBs->GetNmObjConcept(
           ContexterF->State->BowDocBs, ContexterF->State->BowDocWgtBs,
           SrcNmObjStr, DstNmObjStr);
          TStrFltPrV WordStrWgtPrV;
          ConceptSpV->GetWordStrWgtPrV(
           ContexterF->State->BowDocBs, -1, 1, WordStrWgtPrV);
          TStrV UcWordStrSfV;
          for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
            // get word
            TStr UcWordStr=WordStrWgtPrV[WordN].Val1;
            // remove duplicates
            if (UcWordStr.IsStrIn(UcNmObjStr)){continue;}
            if (UcWordStr.IsStrIn(UcSubNmObjStr)){continue;}
            if (UcNmObjStr.IsStrIn(UcWordStr)){continue;}
            if (UcSubNmObjStr.IsStrIn(UcWordStr)){continue;}
            bool Ok=true;
            for (int WordSfN=0; WordSfN<UcWordStrSfV.Len(); WordSfN++){
              if (UcWordStrSfV[WordSfN].IsStrIn(UcWordStr)){Ok=false; break;}
              if (UcWordStr.IsStrIn(UcWordStrSfV[WordSfN])){Ok=false; break;}
            }
            if (!Ok){continue;}
            // add word
            UcWordStrSfV.Add(UcWordStr);
            CtxChA+='['; CtxChA+=UcWordStr; CtxChA+=']'; CtxChA+='\n';
            // finish if limit reached
            if (UcWordStrSfV.Len()>=ContexterF->State->CtxLen){break;}
          }
          ENm=ENm+"\n"+CtxChA;
        }
        // create and add edge to the graph
        PEdge Edge=TGEdge::New(SrcVrtx, DstVrtx, ENm);
        Edge->PutWgt(1+log(SubNmObjFq));
        Graph->AddEdge(Edge);
      }
    }
  }
  Graph->SetEdgeWidth(5);
  Graph->PlaceTreeAsStar();
  Graph->RescaleXY(0.1, RootVrtx);
  // return graph
  return Graph;
}

/////////////////////////////////////////////////
// Top-Level
__fastcall TContexterF::TContexterF(TComponent* Owner): TForm(Owner){}

void __fastcall TContexterF::FormCreate(TObject *Sender){
  State=new TState();
}

void __fastcall TContexterF::FormClose(TObject *Sender, TCloseAction &Action){
  delete State;
}

void __fastcall TContexterF::OpenMIClick(TObject *Sender){
  if (NmObjBsFNmOd->Execute()){
    // load files
    State->NmObjBsFNm=NmObjBsFNmOd->FileName.c_str();
    State->NmObjBs=TNmObjBs::LoadBin(State->NmObjBsFNm);
    State->BowDocBs=TBowDocBs::LoadBin(TStr::PutFExt(State->NmObjBsFNm, ".NmObj.Bow"));
    State->BowDocWgtBs=TBowDocWgtBs::New(State->BowDocBs, bwwtNrmTFIDF);
    NmObjSortRgClick(Sender);
  }
}

void __fastcall TContexterF::NmObjSortRgClick(TObject *Sender){
  // determine sort-order
  bool SortByNameP=false;
  if (NmObjSortRg->ItemIndex==0){SortByNameP=true;}
  else if (NmObjSortRg->ItemIndex==1){SortByNameP=false;}
  else {NmObjSortRg->ItemIndex=1; SortByNameP=false;}
  // fill NmObjLb
  NmObjLb->Clear();
  ConceptWordLb->Clear();
  CoNmObjLb->Clear();
  if (SortByNameP){
    //...sorted by name
    TStrIntPrV NmObjStrFqPrV;
    State->NmObjBs->GetNmObjStrFqPrV(NmObjStrFqPrV, 3);
    NmObjStrFqPrV.Sort();
    for (int NmObjN=0; NmObjN<NmObjStrFqPrV.Len(); NmObjN++){
      TStr LbItemStr=NmObjStrFqPrV[NmObjN].Val1+
       TInt::GetStr(NmObjStrFqPrV[NmObjN].Val2, " (%d)");
      NmObjLb->Items->Add(LbItemStr.CStr());
    }
  } else {
    //...sorted by frequency
    TIntStrPrV NmObjFqStrPrV;
    State->NmObjBs->GetNmObjFqStrPrV(NmObjFqStrPrV, 3);
    NmObjFqStrPrV.Sort(false);
    for (int NmObjN=0; NmObjN<NmObjFqStrPrV.Len(); NmObjN++){
      TStr LbItemStr=NmObjFqStrPrV[NmObjN].Val2+
       TInt::GetStr(NmObjFqStrPrV[NmObjN].Val1, " (%d)");
      NmObjLb->Items->Add(LbItemStr.CStr());
    }
  }
}

void __fastcall TContexterF::NmObjLbClick(TObject *Sender){
  // get named-object string
  TStr LbItemStr=NmObjLb->Items->Strings[NmObjLb->ItemIndex].c_str();
  TStr FqStr; LbItemStr.SplitOnCh(State->RootNmObjStr, ' ', FqStr);
  // get concept-vector
  PBowSpV ConceptSpV=State->NmObjBs->GetNmObjConcept(
   State->BowDocBs, State->BowDocWgtBs, State->RootNmObjStr);
  TStrFltPrV WordStrWgtPrV;
  ConceptSpV->GetWordStrWgtPrV(State->BowDocBs, 100, 0.66, WordStrWgtPrV);
  // fill concept-list-box
  ConceptWordLb->Clear();
  for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
    TStr LbItemStr=WordStrWgtPrV[WordN].Val1+
     TFlt::GetStr(WordStrWgtPrV[WordN].Val2, " (%.3f)");
    ConceptWordLb->Items->Add(LbItemStr.CStr());
  }
  // get coref-named-objects
  TIntPrV FqNmObjIdPrV;
  State->NmObjBs->GetFqNmObjIdPrV(State->RootNmObjStr, FqNmObjIdPrV);
  FqNmObjIdPrV.Sort(false); FqNmObjIdPrV.Trunc(100);
  // fill coref-named-objects
  CoNmObjLb->Clear();
  for (int NmObjN=0; NmObjN<FqNmObjIdPrV.Len(); NmObjN++){
    TStr CoNmObjStr=State->NmObjBs->GetNmObjStr(FqNmObjIdPrV[NmObjN].Val2);
    if (State->RootNmObjStr!=CoNmObjStr){
      TStr LbItemStr=CoNmObjStr+TInt::GetStr(FqNmObjIdPrV[NmObjN].Val1, " (%d)");
      CoNmObjLb->Items->Add(LbItemStr.CStr());
    }
  }
  // context-tree
  State->CtxTree=GetCtxTreeGraph(State->NmObjBs, State->RootNmObjStr, State->DrawLevels-1);
  PbPaint(Sender);
}

void __fastcall TContexterF::CoNmObjLbClick(TObject *Sender){
  // get named-object string
  TStr LbItemStr=CoNmObjLb->Items->Strings[CoNmObjLb->ItemIndex].c_str();
  TStr NmObjStr; TStr FqStr; LbItemStr.SplitOnCh(NmObjStr, ' ', FqStr);
  // find named-object in NmObjLb
  TStr ExtNmObjStr=NmObjStr+" ";
  for (int NmObjN=0; NmObjN<NmObjLb->Items->Count; NmObjN++){
    TStr LbItemStr=NmObjLb->Items->Strings[NmObjN].c_str();
    if (LbItemStr.IsPrefix(ExtNmObjStr)){
      NmObjLb->ItemIndex=NmObjN; break;}
  }
  // simulate click
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::PbPaint(TObject *Sender){
  if (State->CtxTree.Empty()){return;}
  // clear screen
  State->Gks->Clr();
  State->CtxTree->Draw(State->Gks, true, true, State->FontSize);
}

void __fastcall TContexterF::InterNmObjContextCbClick(TObject *Sender){
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::SubNodesSbUpClick(TObject *Sender){
  State->SubNodes++;
  SubNodesEd->Text=TInt::GetStr(State->SubNodes).CStr();
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::SubNodesSbDownClick(TObject *Sender){
  if (State->SubNodes>0){State->SubNodes--;}
  SubNodesEd->Text=TInt::GetStr(State->SubNodes).CStr();
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::DrawLevelsBtUpClick(TObject *Sender){
  State->DrawLevels++;
  DrawLevelsEd->Text=TInt::GetStr(State->DrawLevels).CStr();
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::DrawLevelsBtDownClick(TObject *Sender){
  if (State->DrawLevels>1){State->DrawLevels--;}
  DrawLevelsEd->Text=TInt::GetStr(State->DrawLevels).CStr();
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::CtxLenSbUpClick(TObject *Sender){
  State->CtxLen++;
  CtxLenEd->Text=TInt::GetStr(State->CtxLen).CStr();
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::CtxLenSbDownClick(TObject *Sender){
  if (State->CtxLen>0){State->CtxLen--;}
  CtxLenEd->Text=TInt::GetStr(State->CtxLen).CStr();
  NmObjLbClick(Sender);
}

void __fastcall TContexterF::FontSizeSbUpClick(TObject *Sender){
  State->FontSize++;
  NmObjLb->Font->Size=NmObjLb->Font->Size+1;
  ConceptWordLb->Font->Size=ConceptWordLb->Font->Size+1;
  CoNmObjLb->Font->Size=CoNmObjLb->Font->Size+1;
  PbPaint(Sender);
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
}

void __fastcall TContexterF::FontSizeSbDownClick(TObject *Sender){
  if (State->FontSize>1){
    State->FontSize--;
    if (NmObjLb->Font->Size>1){
      NmObjLb->Font->Size=NmObjLb->Font->Size-1;}
    if (ConceptWordLb->Font->Size>1){
      ConceptWordLb->Font->Size=ConceptWordLb->Font->Size-1;}
    if (CoNmObjLb->Font->Size>1){
      CoNmObjLb->Font->Size=CoNmObjLb->Font->Size-1;}
    PbPaint(Sender);
    FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
  }
}

