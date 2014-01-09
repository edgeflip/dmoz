//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "gksvcl.h"
#include "graph.h"
#include "mine.h"

#include "BowGraphVizM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TBowGraphVizF *BowGraphVizF;

/////////////////////////////////////////////////
// State
class TBowGraphVizF::TState{
public:
  PGks Gks;
  int FontSize;
  bool DrawWordWgtP;
  PGraph Graph;
  TBowDocPart::TClustRectPrV ClustRectPrV;
  TBowDocPartClustV ActClustV;
  PBowDocBs BowDocBs;
  PBowDocPart BowDocPart;
  double VisDataProp, WordStrDocStrProp, WordStrDocNmProp;
public:
  TState():
    Gks(), FontSize(8), DrawWordWgtP(false), Graph(),
    ClustRectPrV(), ActClustV(), BowDocBs(), BowDocPart(),
    VisDataProp(0.66), WordStrDocStrProp(0.75), WordStrDocNmProp(0.4){}
};

/////////////////////////////////////////////////
// Top-Level
__fastcall TBowGraphVizF::TBowGraphVizF(TComponent* Owner): TForm(Owner){}

void __fastcall TBowGraphVizF::FormCreate(TObject *Sender){
  State=new TState();
  State->Gks=TVclGks::New(Pb);
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
  DrawWordWgtCb->Checked=State->DrawWordWgtP;
}

void __fastcall TBowGraphVizF::FormClose(TObject *Sender, TCloseAction &Action){
  State->BowDocPart=NULL;
  delete State;
}

void __fastcall TBowGraphVizF::FormShow(TObject *Sender){
  FormResize(Sender);
}

void __fastcall TBowGraphVizF::FormResize(TObject *Sender){
  VisGb->Width=BowGraphVizF->Width*State->VisDataProp;
  WordStrDataNmP->Height=DataP->Height*State->WordStrDocStrProp;
  WordStrGb->Width=WordStrDataNmP->Width*State->WordStrDocNmProp;
  UpdateClustRectPrV();
}

void __fastcall TBowGraphVizF::VisDataSMoved(TObject *Sender){
  State->VisDataProp=double(VisGb->Width)/double(BowGraphVizF->Width);
  PbPaint(Sender);
}

void __fastcall TBowGraphVizF::WordStrDocStrSMoved(TObject *Sender){
  State->WordStrDocStrProp=double(WordStrDataNmP->Height)/double(DataP->Height);
  PbPaint(Sender);
}

void __fastcall TBowGraphVizF::WordStrDocNmSMoved(TObject *Sender){
  State->WordStrDocNmProp=double(WordStrGb->Width)/double(WordStrDataNmP->Width);
  PbPaint(Sender);
}

void __fastcall TBowGraphVizF::BowDocBsFNmBrowseBtClick(TObject *Sender){
  if (BowDocBsOd->Execute()){
    BowDocBsFNmEd->Text=BowDocBsOd->FileName.c_str();
    // load data
    State->BowDocBs=TBowDocBs::LoadBin(BowDocBsFNmEd->Text.c_str());
    AllDocsLbl->Caption=(TStr("/")+TInt::GetStr(State->BowDocBs->GetDocs())).CStr();
  }
}

/////////////////////////////////////////////////
// Vizualization
void __fastcall TBowGraphVizF::VizualizeBtClick(TObject *Sender){
  if (!State->BowDocBs.Empty()){
    // parameters
    TStr BowDocBsFNm=BowDocBsFNmEd->Text.c_str();
    int Docs=TStr(VizDocsEd->Text.c_str()).GetInt(1000);
    int Clusts=TStr(VizClustsEd->Text.c_str()).GetInt(10);
    double ClustSimSumPrc=TStr(VizClustSimSumPrcEd->Text.c_str()).GetFlt(0.3)/100;

    // get doc-ids
    TIntV AllDIdV; State->BowDocBs->GetAllDIdV(AllDIdV);
    if (Docs!=-1){AllDIdV.Trunc(Docs);}

    // get document partition
    PBowSim BowSim=TBowSim::New(bstCos); // similarity object
    TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
    State->BowDocPart=TBowClust::GetKMeansPart(
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
    for (int ClustN=0; ClustN<State->BowDocPart->GetClusts(); ClustN++){
      // get cluster
      PBowDocPartClust Clust=State->BowDocPart->GetClust(ClustN);
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
    State->BowDocPart->GetTopClustSimV(ClustSimSumPrc, ClustSimN1N2TrV);
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
    State->Graph=Graph;
    TRnd Rnd(1);
    State->Graph->PlaceSimAnnXY(Rnd, State->Gks);

    // get area-partition
    UpdateClustRectPrV();

    // draw graph
    State->Gks->Clr();
    PbPaint(Sender);
  }
}

void __fastcall TBowGraphVizF::PbPaint(TObject *Sender){
  if (!State->Graph.Empty()){
    State->Graph->Draw(State->Gks, true, true, State->FontSize);
    /*bad positioning when resizing window
    PGksPen Pen=PGksPen(new TGksPen(TGksColor::GetRed()));
    State->Gks->SetPen(Pen);
    for (int VrtxN=0; VrtxN<State->Graph->GetVrtxs(); VrtxN++){
      PVrtx Vrtx=State->Graph->GetVrtx(VrtxN);
      PBowDocPartClust Clust=State->BowDocPart->GetClust(VrtxN);
      TGksRect Rect=Vrtx->GetRect();
      State->Gks->Rectangle(Rect);
    }*/
  }
}

void __fastcall TBowGraphVizF::FontSizeSbUpClick(TObject *Sender){
  State->FontSize++;
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
  DocStrM->Font->Size=DocStrM->Font->Size+1;
  PbPaint(Sender);
}

void __fastcall TBowGraphVizF::FontSizeSbDownClick(TObject *Sender){
  if (State->FontSize>1){
    State->FontSize--;
    FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
    if (DocStrM->Font->Size>1){
      DocStrM->Font->Size=DocStrM->Font->Size-1;}
    PbPaint(Sender);
  }
}

void __fastcall TBowGraphVizF::DrawWordWgtCbClick(TObject *Sender){
  State->DrawWordWgtP=!State->DrawWordWgtP;
  DrawWordWgtCb->Checked=State->DrawWordWgtP;
  PbPaint(Sender);
  UpdateDataP();
}

void __fastcall TBowGraphVizF::PbMouseDown(
 TObject *Sender, TMouseButton Button, TShiftState Shift, int PX, int PY){
  if (!State->ClustRectPrV.Empty()){
    TBowDocPart::GetClustAtXY(PX, PY, State->ClustRectPrV, true, State->ActClustV);
    PbPaint(Sender);
    UpdateDataP();
    if (DocNmLb->Items->Count>0){
      DocNmLb->ItemIndex=0; DocNmLbClick(Sender);}
  }
}

void TBowGraphVizF::UpdateClustRectPrV(){
  // get area-partition
  if (!State->BowDocPart.Empty()){
    State->ClustRectPrV.Clr();
    for (int VrtxN=0; VrtxN<State->Graph->GetVrtxs(); VrtxN++){
      PVrtx Vrtx=State->Graph->GetVrtx(VrtxN);
      PBowDocPartClust Clust=State->BowDocPart->GetClust(VrtxN);
      TFltRect FltRect=Vrtx->GetRect().GetFltRect();
      State->ClustRectPrV.Add(TBowDocPart::TClustRectPr(Clust, FltRect));
    }
  }
}

void TBowGraphVizF::UpdateDataP(){
  WordStrLb->Items->Clear();
  DocNmLb->Items->Clear();
  DocStrM->Lines->Clear();
  if (!State->ActClustV.Empty()){
    PBowDocPartClust Clust=State->ActClustV[0];
    // add words string
    TStrFltPrV WordStrWgtPrV;
    Clust->GetTopWordStrWgtPrV(State->BowDocBs, -1, 0.75, WordStrWgtPrV);
    WordStrLb->Visible=false;
    for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
      TChA BestWordVChA=WordStrWgtPrV[WordN].Val1;
      if (State->DrawWordWgtP){
        BestWordVChA+=TFlt::GetStr(WordStrWgtPrV[WordN].Val2, " (%.2f)");}
      WordStrLb->Items->Add(BestWordVChA.CStr());
    }
    WordStrLb->Visible=true;
    // add document names
    TFltStrPrV DCSimDocNmPrV;
    for (int DIdN=0; DIdN<Clust->GetDocs(); DIdN++){
      int DId=Clust->GetDId(DIdN);
      double DCSim=Clust->GetDCSim(DIdN);
      TStr DocNm=State->BowDocBs->GetDocNm(DId);
      DCSimDocNmPrV.Add(TFltStrPr(DCSim, DocNm));
    }
    DCSimDocNmPrV.Sort(false);
    DocNmLb->Visible=false;
    for (int DIdN=0; DIdN<DCSimDocNmPrV.Len(); DIdN++){
      double DCSim=DCSimDocNmPrV[DIdN].Val1;
      TStr DocNm=DCSimDocNmPrV[DIdN].Val2;
      TStr DocDescStr=DocNm+TFlt::GetStr(DCSim, " (%.3f)");
      DocNmLb->Items->Add(DocDescStr.CStr());
    }
    DocNmLb->Visible=true;
  }
}

void __fastcall TBowGraphVizF::DocNmLbClick(TObject *Sender){
  DocStrM->Lines->Clear();
  if ((0<=DocNmLb->ItemIndex)&&(DocNmLb->ItemIndex<DocNmLb->Items->Count)){
    TStr DocDescStr=DocNmLb->Items->Strings[DocNmLb->ItemIndex].c_str();
    TStr DocNm; TStr ParenDCSimStr;
    DocDescStr.SplitOnLastCh(DocNm, ' ', ParenDCSimStr);
    int DId=State->BowDocBs->GetDId(DocNm);
    TStr DocStr=State->BowDocBs->GetDocStr(DId);
    DocStrM->Lines->Clear();
    DocStrM->Lines->Add(DocStr.CStr());
  }
}


