//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "base.h"
#include "google.h"
#include "nmobj.h"
#include "mine.h"
#include "graph.h"
#include "gksvcl.h"

#include "Contexter4GoogleNewsM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TContexterF *ContexterF;

/////////////////////////////////////////////////
// Form-State
class TContexterF::TState{
public:
  TStr RSetFNm;
  PRSet RSet;
  PBowDocBs BowDocBs;
  PBowDocWgtBs BowDocWgtBs;
  PNmObjBs NmObjBs;
  // entity-network
  PGks EnGks;
  TStr EnRootNmObjStr;
  PGraph EnCtxTree;
  int EnSubNodes, EnDrawLevels, EnCtxLen, EnFontSize;
  // entity-linkage
  TStr ElSrcNmObjStr, ElDstNmObjStr;
  PGraph ElGraph;
  PGks ElGks;
  int ElFontSize;
  // topic-map
  PGks TmGks;
  int TmFontSize;
  PGraph TmClustGraph;
  TBowDocPart::TClustRectPrV TmClustRectPrV;
  PBowDocPart TmBowDocPart;
  UndefCopyAssign(TState);
public:
  TState():
    RSetFNm(), RSet(), BowDocBs(), BowDocWgtBs(), NmObjBs(),
    EnGks(TVclGks::New(ContexterF->EnPb)),
    EnRootNmObjStr(), EnCtxTree(),
    EnSubNodes(8), EnDrawLevels(1), EnCtxLen(5), EnFontSize(8),
    ElSrcNmObjStr(), ElDstNmObjStr(), ElGraph(),
    ElGks(TVclGks::New(ContexterF->ElPb)),
    ElFontSize(10),
    TmGks(TVclGks::New(ContexterF->TmPb)),
    TmFontSize(8), TmClustGraph(),
    TmClustRectPrV(), TmBowDocPart(){}
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
      FqNmObjIdPrV.Trunc(ContexterF->State->EnCtxLen); FqNmObjIdPrV.Clr();
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
          case 0: MxCreatedSubNmObjs=/*20;*/ContexterF->State->EnSubNodes; break;
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
        if (ContexterF->EnInterNmObjContextCb->Checked){
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
            if (UcWordStrSfV.Len()>=ContexterF->State->EnCtxLen){break;}
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
// Best-Paths
void GetBestPaths(
 const TStr& SrcNmObjStr, const TStr& DstNmObjStr, const PNmObjBs& NmObjBs){
  int SrcNmObjId=NmObjBs->GetNmObjId(SrcNmObjStr);
  int DstNmObjId=NmObjBs->GetNmObjId(DstNmObjStr);
  int NmObjs=NmObjBs->GetNmObjs();
  TIntPrV ParLevPrV(NmObjs); TIntPrV DstParLevPrV;
  ParLevPrV.PutAll(TIntPr(-1, -1));
  int CurLev=0;
  ParLevPrV[SrcNmObjId]=TIntPr(SrcNmObjId, CurLev);
  forever{
    CurLev++; int NewEdges=0;
    for (int NmObjId1=0; NmObjId1<NmObjs; NmObjId1++){
      if (ParLevPrV[NmObjId1].Val2==CurLev-1){
        TIntV DocIdV1; NmObjBs->GetNmObjDocIdV(NmObjId1, DocIdV1);
        for (int NmObjId2=0; NmObjId2<NmObjs; NmObjId2++){
          if ((NmObjId2==DstNmObjId)||(ParLevPrV[NmObjId2].Val2==-1)){
            TIntV DocIdV2; NmObjBs->GetNmObjDocIdV(NmObjId2, DocIdV2);
            TIntV IntrsDocIdV; DocIdV1.Intrs(DocIdV2, IntrsDocIdV);
            if (!IntrsDocIdV.Empty()){
              ParLevPrV[NmObjId2]=TIntPr(NmObjId1, CurLev); NewEdges++;
              if (NmObjId2==DstNmObjId){
                DstParLevPrV.Add(TIntPr(NmObjId1, CurLev));
              }
            }
          }
        }
      }
    }
    if ((NewEdges==0)||(ParLevPrV[DstNmObjId].Val2!=-1)){
      break;
    }
  }
  // prepare graph
  THash<TStr, PVrtx> VrtxNmToVrtxH; TStrPrV VrtxNmPrV;
  VrtxNmToVrtxH.AddKey(SrcNmObjStr);
  VrtxNmToVrtxH.AddKey(DstNmObjStr);
  // write path
  ContexterF->NmObjLinkageREd->Clear();
  for (int DstParLevPrN=0; DstParLevPrN<DstParLevPrV.Len(); DstParLevPrN++){
    ParLevPrV[DstNmObjId]=DstParLevPrV[DstParLevPrN];
    int DstParLev=ParLevPrV[DstNmObjId].Val2;
    TStr DstNmObjStr=NmObjBs->GetNmObjStr(DstNmObjId);
    ContexterF->NmObjLinkageREd->Lines->Add(DstNmObjStr.CStr());
    int ParNmObjId=DstNmObjId;
    TStr PrevNmObjStr=DstNmObjStr;
    forever {
      if (ParNmObjId==SrcNmObjId){break;}
      ParNmObjId=ParLevPrV[ParNmObjId].Val1;
      int ParLev=ParLevPrV[ParNmObjId].Val2;
      TStr CurNmObjStr=NmObjBs->GetNmObjStr(ParNmObjId);
      TStr ParNmObjStr=TStr::GetSpaceStr((DstParLev-ParLev)*4)+CurNmObjStr;
      ContexterF->NmObjLinkageREd->Lines->Add(ParNmObjStr.CStr());
      // create vertex & edge
      VrtxNmToVrtxH.AddKey(CurNmObjStr);
      if (!PrevNmObjStr.Empty()){
        if (PrevNmObjStr<CurNmObjStr){
          VrtxNmPrV.AddUnique(TStrPr(PrevNmObjStr, CurNmObjStr));
        } else
        if (PrevNmObjStr>CurNmObjStr){
          VrtxNmPrV.AddUnique(TStrPr(CurNmObjStr, PrevNmObjStr));
        }
      }
      // save curent named-object
      PrevNmObjStr=CurNmObjStr;
    }
  }
  // generate graph
  // create graph
  PGraph Graph=TGGraph::New();
  // create vertices
  for (int VrtxN=0; VrtxN<VrtxNmToVrtxH.Len(); VrtxN++){
    TStr VrtxNm=VrtxNmToVrtxH.GetKey(VrtxN);
    PVrtx Vrtx=TGVrtx::New(VrtxNm);
    VrtxNmToVrtxH.GetDat(VrtxNm)=Vrtx;
    Graph->AddVrtx(Vrtx);
  }
  // create edges
  for (int EdgeN=0; EdgeN<VrtxNmPrV.Len(); EdgeN++){
    PVrtx Vrtx1=VrtxNmToVrtxH.GetDat(VrtxNmPrV[EdgeN].Val1);
    PVrtx Vrtx2=VrtxNmToVrtxH.GetDat(VrtxNmPrV[EdgeN].Val2);
    PEdge Edge=new TGEdge(Vrtx1, Vrtx2, TStr::Fmt("_%d", EdgeN), false);
    Graph->AddEdge(Edge);
  }
  // place graph
  ContexterF->State->ElGraph=Graph;
  TRnd Rnd(1);
  ContexterF->State->ElGraph->PlaceSimAnnXY(Rnd, ContexterF->State->ElGks);
  // draw graph
  ContexterF->State->ElGks->Clr();
  ContexterF->ElPbPaint(NULL);
}

/////////////////////////////////////////////////
// Form-State
__fastcall TContexterF::TContexterF(TComponent* Owner): TForm(Owner){}

void __fastcall TContexterF::FormCreate(TObject *Sender){
  Pc->ActivePage=EntNetworkTs;
  State=new TState();
}

void __fastcall TContexterF::FormClose(TObject *Sender, TCloseAction &Action){
  delete State;
}

void TContexterF::PrepRSetEnv(){
  IAssert(!State->RSet.Empty());
  // create bag-of-words
  State->BowDocBs=State->RSet->GetBowDocBs();
  // create bag-of-words-weights
  State->BowDocWgtBs=TBowDocWgtBs::New(State->BowDocBs, bwwtLogDFNrmTFIDF);
  // create named-objects
  TStr FPath=TSysProc::GetExeFNm().GetFPath();
  const TStrQuV& UrlTitleSrcCtxQuV=State->RSet->GetUrlTitleSrcCtxQuV();
  State->NmObjBs=TNmObjBs::GetFromStrQuV(
   UrlTitleSrcCtxQuV,
   swstEn523,
   FPath+"Contexter4GoogleNews-StopWord.Txt",
   FPath+"Contexter4GoogleNews-WordStem.Txt",
   FPath+"Contexter4GoogleNews-WordType.Txt");
  State->NmObjBs->SaveTxtNmObj(
   FPath+"NmObjFq.Txt", FPath+"NmObjSw.Txt",
   FPath+"NmObjAbc.Txt", FPath+"NmObjDoc.Txt");
  // reset root-name
  State->EnRootNmObjStr="";
  // reset context-tree
  State->EnCtxTree=NULL;
  EnPbPaint(NULL);
  // reset topic-map
  State->TmClustGraph=NULL;
  TmPbPaint(NULL);
  // reset source & destination named-objects
  State->ElSrcNmObjStr="";
  State->ElDstNmObjStr="";
  // show named-entities
  NmObjSortRgClick(CtxNmObjSortRg);
  NmObjSortRgClick(SrcNmObjSortRg);
  NmObjSortRgClick(DstNmObjSortRg);
  // reset page-control
  Pc->ActivePage=EntNetworkTs;
}

void __fastcall TContexterF::OpenMIClick(TObject *Sender){
  if (RSetOd->Execute()){
    // get result-set file-name
    State->RSetFNm=RSetOd->FileName.c_str();
    // load result-set file
    State->RSet=TRSet::LoadBin(State->RSetFNm);
    // prepare result-set environment
    PrepRSetEnv();
  }
}

void __fastcall TContexterF::SaveAsMIClick(TObject *Sender){
  if (State->RSet.Empty()){return;}
  if (RSetSd->Execute()){
    // get result-set file-name
    State->RSetFNm=RSetSd->FileName.c_str();
    // save result-set file
    State->RSet->SaveBin(State->RSetFNm);
  }
}

void __fastcall TContexterF::TestMIClick(TObject *Sender){
  // get result-set file-name
  State->RSetFNm="c:\\users\\marko\\dev\\iexm\\iexmcontexter\\test.rset";
  // load result-set file
  State->RSet=TRSet::LoadBin(State->RSetFNm);
  // prepare result-set environment
  PrepRSetEnv();
}

void __fastcall TContexterF::EnSearchShowBtClick(TObject *Sender){
  TStr QueryStr=QueryEd->Text.c_str();
  QueryStr=QueryStr.GetTrunc();
  if (!QueryStr.Empty()){
    // start progress-bar
    ProgressTimer->Enabled=true;
    ProgressBar->Position=ProgressBar->Min;
    ProgressBar->Visible=true;
    // disable form
    ContexterF->Enabled=false;
    // crawl for result-set
    PRSet RSet=TGg::NewsSearch(QueryStr);
    if (Sender==EnSearchShowBt){
      State->RSet=RSet;
      if (State->RSet.Empty()){
        State->RSet=TRSet::New();}
    } else
    if (Sender==EnSearchMergeShowBt){
      if (State->RSet.Empty()){
        State->RSet=TRSet::New();}
      if (!RSet.Empty()){
        State->RSet->Merge(RSet);}
    } else {
      Fail;
    }
    // prepare result-set environment
    PrepRSetEnv();
    // enable form
    ContexterF->Enabled=true;
    // stop progress-bar
    ProgressBar->Visible=false;
    ProgressTimer->Enabled=false;
  }
}

void __fastcall TContexterF::ProgressTimerTimer(TObject *Sender){
  if (ProgressBar->Position>=ProgressBar->Max){
    ProgressBar->Position=ProgressBar->Min;}
  ProgressBar->Position=ProgressBar->Position+1;
}


void __fastcall TContexterF::EnInterNmObjContextCbClick(TObject *Sender){
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::NmObjSortRgClick(TObject *Sender){
  // select radio-group & list-box
  TRadioGroup* NmObjSortRg=NULL; TListBox* NmObjLb=NULL;
  if (Sender==CtxNmObjSortRg){NmObjSortRg=CtxNmObjSortRg; NmObjLb=CtxNmObjLb;}
  else if (Sender==SrcNmObjSortRg){NmObjSortRg=SrcNmObjSortRg; NmObjLb=SrcNmObjLb;}
  else if (Sender==DstNmObjSortRg){NmObjSortRg=DstNmObjSortRg; NmObjLb=DstNmObjLb;}
  else {return;}

  // determine sort-order
  bool SortByNameP=false;
  if (NmObjSortRg->ItemIndex==0){SortByNameP=true;}
  else if (NmObjSortRg->ItemIndex==1){SortByNameP=false;}
  else {NmObjSortRg->ItemIndex=1; SortByNameP=false;}
  // fill NmObjLb
  NmObjLb->Clear();
  EnConceptWordLb->Clear();
  EnCoNmObjLb->Clear();
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

void __fastcall TContexterF::CtxNmObjLbClick(TObject *Sender){
  TListBox* NmObjLb=CtxNmObjLb;
  // get named-object string
  if ((NmObjLb->ItemIndex<0)||(NmObjLb->Items->Count<=NmObjLb->ItemIndex)){
    return;}
  TStr LbItemStr=NmObjLb->Items->Strings[NmObjLb->ItemIndex].c_str();
  TStr FqStr; LbItemStr.SplitOnCh(State->EnRootNmObjStr, ' ', FqStr);
  // get concept-vector
  PBowSpV ConceptSpV=State->NmObjBs->GetNmObjConcept(
   State->BowDocBs, State->BowDocWgtBs, State->EnRootNmObjStr);
  TStrFltPrV WordStrWgtPrV;
  ConceptSpV->GetWordStrWgtPrV(State->BowDocBs, 100, 0.66, WordStrWgtPrV);
  // fill concept-list-box
  EnConceptWordLb->Clear();
  for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
    TStr LbItemStr=WordStrWgtPrV[WordN].Val1+
     TFlt::GetStr(WordStrWgtPrV[WordN].Val2, " (%.3f)");
    EnConceptWordLb->Items->Add(LbItemStr.CStr());
  }
  // get coref-named-objects
  TIntPrV FqNmObjIdPrV;
  State->NmObjBs->GetFqNmObjIdPrV(State->EnRootNmObjStr, FqNmObjIdPrV);
  FqNmObjIdPrV.Sort(false); FqNmObjIdPrV.Trunc(100);
  // fill coref-named-objects
  EnCoNmObjLb->Clear();
  for (int NmObjN=0; NmObjN<FqNmObjIdPrV.Len(); NmObjN++){
    TStr CoNmObjStr=State->NmObjBs->GetNmObjStr(FqNmObjIdPrV[NmObjN].Val2);
    if (State->EnRootNmObjStr!=CoNmObjStr){
      TStr LbItemStr=CoNmObjStr+TInt::GetStr(FqNmObjIdPrV[NmObjN].Val1, " (%d)");
      EnCoNmObjLb->Items->Add(LbItemStr.CStr());
    }
  }
  // context-tree
  State->EnCtxTree=GetCtxTreeGraph(State->NmObjBs, State->EnRootNmObjStr, State->EnDrawLevels-1);
  EnPbPaint(Sender);
}

void __fastcall TContexterF::CorefNmObjLbClick(TObject *Sender){
  TListBox* NmObjLb=CtxNmObjLb;
  // get named-object string
  TStr LbItemStr=EnCoNmObjLb->Items->Strings[EnCoNmObjLb->ItemIndex].c_str();
  TStr NmObjStr; TStr FqStr; LbItemStr.SplitOnCh(NmObjStr, ' ', FqStr);
  // find named-object in NmObjLb
  TStr ExtNmObjStr=NmObjStr+" ";
  for (int NmObjN=0; NmObjN<NmObjLb->Items->Count; NmObjN++){
    TStr LbItemStr=NmObjLb->Items->Strings[NmObjN].c_str();
    if (LbItemStr.IsPrefix(ExtNmObjStr)){
      NmObjLb->ItemIndex=NmObjN; break;}
  }
  // simulate click
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnPbPaint(TObject *Sender){
  if (State->EnCtxTree.Empty()){return;}
  // clear screen
  State->EnGks->Clr();
  State->EnCtxTree->Draw(State->EnGks, true, true, State->EnFontSize);
}

void __fastcall TContexterF::EnKeywordsCbClick(TObject *Sender){
  EnConceptGb->Visible=!EnConceptGb->Visible;
  EnCoNmObjGb->Visible=!EnCoNmObjGb->Visible;
  EnSplitter2->Visible=!EnSplitter2->Visible;
  EnSplitter3->Visible=!EnSplitter3->Visible;
}

void __fastcall TContexterF::EnSubNodesSbUpClick(TObject *Sender){
  State->EnSubNodes++;
  EnSubNodesEd->Text=TInt::GetStr(State->EnSubNodes).CStr();
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnSubNodesSbDownClick(TObject *Sender){
  if (State->EnSubNodes>0){State->EnSubNodes--;}
  EnSubNodesEd->Text=TInt::GetStr(State->EnSubNodes).CStr();
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnDrawLevelsBtUpClick(TObject *Sender){
  State->EnDrawLevels++;
  EnDrawLevelsEd->Text=TInt::GetStr(State->EnDrawLevels).CStr();
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnDrawLevelsBtDownClick(TObject *Sender){
  if (State->EnDrawLevels>1){State->EnDrawLevels--;}
  EnDrawLevelsEd->Text=TInt::GetStr(State->EnDrawLevels).CStr();
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnCtxLenSbUpClick(TObject *Sender){
  State->EnCtxLen++;
  EnCtxLenEd->Text=TInt::GetStr(State->EnCtxLen).CStr();
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnCtxLenSbDownClick(TObject *Sender){
  if (State->EnCtxLen>0){State->EnCtxLen--;}
  EnCtxLenEd->Text=TInt::GetStr(State->EnCtxLen).CStr();
  CtxNmObjLbClick(Sender);
}

void __fastcall TContexterF::EnFontSizeSbUpClick(TObject *Sender){
  TListBox* NmObjLb=CtxNmObjLb;
  State->EnFontSize++;
  NmObjLb->Font->Size=NmObjLb->Font->Size+1;
  EnConceptWordLb->Font->Size=EnConceptWordLb->Font->Size+1;
  EnCoNmObjLb->Font->Size=EnCoNmObjLb->Font->Size+1;
  EnPbPaint(Sender);
  EnFontSizeEd->Text=TInt::GetStr(State->EnFontSize).CStr();
}

void __fastcall TContexterF::EnFontSizeSbDownClick(TObject *Sender){
  TListBox* NmObjLb=CtxNmObjLb;
  if (State->EnFontSize>1){
    State->EnFontSize--;
    if (NmObjLb->Font->Size>1){
      NmObjLb->Font->Size=NmObjLb->Font->Size-1;}
    if (EnConceptWordLb->Font->Size>1){
      EnConceptWordLb->Font->Size=EnConceptWordLb->Font->Size-1;}
    if (EnCoNmObjLb->Font->Size>1){
      EnCoNmObjLb->Font->Size=EnCoNmObjLb->Font->Size-1;}
    EnPbPaint(Sender);
    EnFontSizeEd->Text=TInt::GetStr(State->EnFontSize).CStr();
  }
}

void __fastcall TContexterF::SrcDstNmObjLbClick(TObject *Sender){
  TListBox* NmObjLb=NULL;
  if (Sender==SrcNmObjLb){NmObjLb=SrcNmObjLb;}
  else if (Sender==DstNmObjLb){NmObjLb=DstNmObjLb;}
  else {return;}
  // get & assign named-object string
  TStr NmObjStr;
  TStr LbItemStr=NmObjLb->Items->Strings[NmObjLb->ItemIndex].c_str();
  TStr FqStr; LbItemStr.SplitOnCh(NmObjStr, ' ', FqStr);
  if (Sender==SrcNmObjLb){State->ElSrcNmObjStr=NmObjStr;}
  else if (Sender==DstNmObjLb){State->ElDstNmObjStr=NmObjStr;}
  else {Fail;}
  SrcNmObjEd->Text=State->ElSrcNmObjStr.CStr();
  DstNmObjEd->Text=State->ElDstNmObjStr.CStr();
  // calculate paths if source & destination are given
  if ((!State->ElSrcNmObjStr.Empty())&&(!State->ElDstNmObjStr.Empty())){
    GetBestPaths(State->ElSrcNmObjStr, State->ElDstNmObjStr, State->NmObjBs);
  }
}

void __fastcall TContexterF::ElPbPaint(TObject *Sender){
  if (!State->ElGraph.Empty()){
    State->ElGraph->Draw(State->ElGks, true, true, State->ElFontSize);
  }
}

void __fastcall TContexterF::VizualizeBtClick(TObject *Sender){
  if (!State->BowDocBs.Empty()){
    // parameters
    int Clusts=TStr(VizClustsEd->Text.c_str()).GetInt(10);
    double ClustSimSumPrc=TStr(VizClustSimSumPrcEd->Text.c_str()).GetFlt(0.3)/100;

    // get doc-ids
    TIntV AllDIdV; State->BowDocBs->GetAllDIdV(AllDIdV);

    // get document partition
    PBowSim BowSim=TBowSim::New(bstCos); // similarity object
    TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
    State->TmBowDocPart=TBowClust::GetKMeansPart(
     TNotify::StdNotify, // log output
     State->BowDocBs, // document data
     BowSim, // similarity function
     TRnd(1), // random generator
     Clusts, // number of clusters
     1, // trials per k-means
     10, // convergence epsilon for k-means
     1, // min. documents per cluster
     WordWgtType, // word weighting
     0.5, // cut-word-weights percentage
     5, // minimal word frequency
     AllDIdV); // training documents

    // create graph
    PGraph Graph=TGGraph::New();

    // create vertices
    TVrtxV VrtxV;
    for (int ClustN=0; ClustN<State->TmBowDocPart->GetClusts(); ClustN++){
      // get cluster
      PBowDocPartClust Clust=State->TmBowDocPart->GetClust(ClustN);
      // get best words string
      TStrFltPrV WordStrWgtPrV;
      Clust->GetTopWordStrWgtPrV(State->BowDocBs, -1, 1.0, WordStrWgtPrV);
      TChA BestWordVChA;
      BestWordVChA+=TInt::GetStr(Clust->GetDocs())+" Docs\n";
      TStrV UcWordStrSfV;
      for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
        // get word
        TStr UcWordStr=WordStrWgtPrV[WordN].Val1;
        // remove duplicates
        bool Ok=true;
        for (int WordSfN=0; WordSfN<UcWordStrSfV.Len(); WordSfN++){
          if (UcWordStrSfV[WordSfN].IsStrIn(UcWordStr)){Ok=false; break;}
          if (UcWordStr.IsStrIn(UcWordStrSfV[WordSfN])){Ok=false; break;}
        }
        if (!Ok){continue;}
        // add word
        UcWordStrSfV.Add(UcWordStr);
        BestWordVChA+=WordStrWgtPrV[WordN].Val1;
        BestWordVChA+="\n";
        // finish if limit reached
        if (UcWordStrSfV.Len()>=15){break;}
      }
      // create vertex
      TStr ClustNm=BestWordVChA;
      PVrtx Vrtx=new TGVrtx(ClustNm);
      Graph->AddVrtx(Vrtx);
      VrtxV.Add(Vrtx);
    }

    // create edges
    TFltIntIntTrV ClustSimN1N2TrV;
    State->TmBowDocPart->GetTopClustSimV(ClustSimSumPrc, ClustSimN1N2TrV);
    for (int ClustSimN=0; ClustSimN<ClustSimN1N2TrV.Len(); ClustSimN++){
      double Sim=ClustSimN1N2TrV[ClustSimN].Val1;
      double ClustN1=ClustSimN1N2TrV[ClustSimN].Val2;
      double ClustN2=ClustSimN1N2TrV[ClustSimN].Val3;
      TStr EdgeNm=TFlt::GetStr(Sim, "%.2f");
      PEdge Edge=new TGEdge(VrtxV[ClustN1], VrtxV[ClustN2], EdgeNm, false);
      Graph->AddEdge(Edge);
      Edge->PutWgt(TMath::Sqr(Sim));
    }

    // place graph
    State->TmClustGraph=Graph;
    TRnd Rnd(1);
    State->TmClustGraph->PlaceSimAnnXY(Rnd, State->TmGks);

    // get area-partition
    UpdateClustRectPrV();

    // draw graph
    State->TmGks->Clr();
    TmPbPaint(Sender);
  }
}

void TContexterF::UpdateClustRectPrV(){
  // get area-partition
  if (!State->TmBowDocPart.Empty()){
    State->TmClustRectPrV.Clr();
    for (int VrtxN=0; VrtxN<State->TmClustGraph->GetVrtxs(); VrtxN++){
      PVrtx Vrtx=State->TmClustGraph->GetVrtx(VrtxN);
      PBowDocPartClust Clust=State->TmBowDocPart->GetClust(VrtxN);
      TFltRect FltRect=Vrtx->GetRect().GetFltRect();
      State->TmClustRectPrV.Add(TBowDocPart::TClustRectPr(Clust, FltRect));
    }
  }
}

void __fastcall TContexterF::TmPbPaint(TObject *Sender){
  if (!State->TmClustGraph.Empty()){
    State->TmClustGraph->Draw(State->TmGks, true, true, State->TmFontSize);
  }
}

void __fastcall TContexterF::TmFontSizeSbUpClick(TObject *Sender){
  State->TmFontSize++;
  TmFontSizeEd->Text=TInt::GetStr(State->TmFontSize).CStr();
  TmPbPaint(Sender);
}

void __fastcall TContexterF::TmFontSizeSbDownClick(TObject *Sender){
  if (State->TmFontSize>1){
    State->TmFontSize--;
    TmFontSizeEd->Text=TInt::GetStr(State->TmFontSize).CStr();
    TmPbPaint(Sender);
  }
}


