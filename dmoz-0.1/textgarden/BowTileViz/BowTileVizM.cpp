//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "gksvcl.h"
#include "tmine.h"

#include "BowTileVizM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TBowTileVizF *BowTileVizF;

/////////////////////////////////////////////////
// State
class TBowTileVizF::TState{
public:
  PGks Gks;
  int FontSize;
  int BoxWords;
  bool DrawEllipsesP;
  bool DrawWordWgtP;
  TBowDocPart::TClustRectPrV ClustRectPrV;
  TBowDocPartClustV ActClustV;
  PBowDocBs BowDocBs;
  double VisDataProp, WordStrDocStrProp, WordStrDocNmProp;
public:
  TState():
    Gks(), FontSize(8), BoxWords(5),
    DrawEllipsesP(true), DrawWordWgtP(false),
    ClustRectPrV(), ActClustV(), BowDocBs(),
    VisDataProp(0.66), WordStrDocStrProp(0.75), WordStrDocNmProp(0.4){}
};

/////////////////////////////////////////////////
// Top-Level
__fastcall TBowTileVizF::TBowTileVizF(TComponent* Owner): TForm(Owner){}

void __fastcall TBowTileVizF::FormCreate(TObject *Sender){
  State=new TState();
  State->Gks=TVclGks::New(Pb);
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
  BoxWordsEd->Text=TInt::GetStr(State->BoxWords).CStr();
  DrawEllipsesCb->Checked=State->DrawEllipsesP;
  DrawWordWgtCb->Checked=State->DrawWordWgtP;
}

void __fastcall TBowTileVizF::FormClose(TObject *Sender, TCloseAction &Action){
  delete State;
}

void __fastcall TBowTileVizF::FormShow(TObject *Sender){
  FormResize(Sender);
}

void __fastcall TBowTileVizF::FormResize(TObject *Sender){
  VisGb->Width=BowTileVizF->Width*State->VisDataProp;
  WordStrDataNmP->Height=DataP->Height*State->WordStrDocStrProp;
  WordStrGb->Width=WordStrDataNmP->Width*State->WordStrDocNmProp;
}

void __fastcall TBowTileVizF::VisDataSMoved(TObject *Sender){
  State->VisDataProp=double(VisGb->Width)/double(BowTileVizF->Width);
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::WordStrDocStrSMoved(TObject *Sender){
  State->WordStrDocStrProp=double(WordStrDataNmP->Height)/double(DataP->Height);
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::WordStrDocNmSMoved(TObject *Sender){
  State->WordStrDocNmProp=double(WordStrGb->Width)/double(WordStrDataNmP->Width);
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::BowDocBsFNmBrowseBtClick(TObject *Sender){
  if (BowDocBsOd->Execute()){
    BowDocBsFNmEd->Text=BowDocBsOd->FileName.c_str();
    // load data
    State->BowDocBs=TBowDocBs::LoadBin(BowDocBsFNmEd->Text.c_str());
    AllDocsLbl->Caption=(TStr("/")+TInt::GetStr(State->BowDocBs->GetDocs())).CStr();
  }
}

/////////////////////////////////////////////////
// Visualization

void __fastcall TBowTileVizF::VisualizeBtClick(TObject *Sender){
  // parameters
  TStr BowDocBsFNm=BowDocBsFNmEd->Text.c_str();
  int Docs=TStr(VizDocsEd->Text.c_str()).GetInt(1000);
  int MxDocsPerLeafClust=TStr(MxDocsPerLeafClustEd->Text.c_str()).GetInt(100);

  // load data
  State->BowDocBs=TBowDocBs::LoadBin(BowDocBsFNm);

  // get doc-ids
  TIntV AllDIdV; State->BowDocBs->GetAllDIdV(AllDIdV);
  if (Docs!=-1){AllDIdV.Trunc(Docs);}

  // get document partition
  PBowSim BowSim=TBowSim::New(bstCos); // similarity object
  TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
  TSecTm StartTm=TSecTm::GetCurTm();
  PBowDocPart BowDocPart=TBowClust::GetHKMeansPart(
   TNotify::StdNotify, // log output
   State->BowDocBs, // document data
   BowSim, // similarity function
   TRnd(1), // random generator
   MxDocsPerLeafClust, // max. documents per leaf cluster
   1, // trials per k-means
   10, // convergence epsilon for k-means
   1, // min. documents per cluster
   WordWgtType, // word weighting
   0.5, // cut-word-weights percentage
   5, // minimal word frequency
   AllDIdV, // training documents
   false, NULL); // propagate weights, weights-base

  // get area-partition
  State->ClustRectPrV.Clr();
  BowDocPart->GetAreaPart(TFltRect(0, 0, 1, 1), State->ClustRectPrV);

  // draw
  State->Gks->Clr();
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::PbPaint(TObject *Sender){
  if (!State->ClustRectPrV.Empty()){
    State->Gks->Clr();
    // draw
    TBowDocPart::TClustRectPrV& ClustRectPrV=State->ClustRectPrV;
    for (int ClustRectPrN=0; ClustRectPrN<ClustRectPrV.Len(); ClustRectPrN++){
      PBowDocPartClust Clust=ClustRectPrV[ClustRectPrN].Val1;
      TFltRect VRect=ClustRectPrV[ClustRectPrN].Val2;
      if (!Clust->IsSubPart()){
        // get best words string
        TStrFltPrV WordStrWgtPrV;
        Clust->GetTopWordStrWgtPrV(State->BowDocBs, State->BoxWords, 0.66, WordStrWgtPrV);
        TChA BestWordVChA;
        for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
          BestWordVChA+=WordStrWgtPrV[WordN].Val1;
          BestWordVChA+="\n";
        }
        // draw rectangle
        TGksRect PRect=State->Gks->GetVToPRect(VRect);
        PGksPen Pen=PGksPen(new TGksPen(TGksColor::GetBlue()));
        for (int ActClustN=0; ActClustN<State->ActClustV.Len(); ActClustN++){
          if (State->ActClustV[ActClustN]()==Clust()){
            Pen=PGksPen(new TGksPen(TGksColor::GetRed(), gpmCopy, gpsSolid, 5));
            break;
          }
        }
        State->Gks->SetPen(Pen);
        State->Gks->RoundRect(PRect, 10, 10);
        State->Gks->SetFont(TGksFont::New("Arial", State->FontSize));
        // draw text
        TStr TxtStr=BestWordVChA;
        // split text to lines
        TStrV TxtStrV; TxtStr.SplitOnAllCh('\n', TxtStrV);
        // get lines position data
        TIntV TxtWidthV; TIntV TxtHeightV;
        int TxtVWidth; int TxtVHeight; TIntV YV;
        State->Gks->GetStrVData(
         TxtStrV, PRect.GetXCenter(), PRect.GetYCenter(),
         TxtWidthV, TxtHeightV, TxtVWidth, TxtVHeight, YV);
        // draw text
        for (int TxtStrN=0; TxtStrN<TxtStrV.Len(); TxtStrN++){
          State->Gks->PutTxt(TxtStrV[TxtStrN],
           PRect.GetXCenter()-TxtWidthV[TxtStrN]/2, YV[TxtStrN]-TxtHeightV[TxtStrN]/2);
        }
      }
    }
    // draw hierarchical ellipses
    if (State->DrawEllipsesP){
      PGksPen Pen=new TGksPen(TGksColor::GetBlue());
      State->Gks->SetPen(Pen);
      PGksBrush Brush=new TGksBrush(TGksColor::GetBlue(), gbsClear);
      State->Gks->SetBrush(Brush);
      for (int ClustRectPrN=0; ClustRectPrN<ClustRectPrV.Len(); ClustRectPrN++){
        PBowDocPartClust Clust=ClustRectPrV[ClustRectPrN].Val1;
        TFltRect VRect=ClustRectPrV[ClustRectPrN].Val2;
        if (Clust->IsSubPart()){
          TGksRect PRect=State->Gks->GetVToPRect(VRect);
          State->Gks->Ellipse(PRect);
        }
      }
    }
  }
}

void __fastcall TBowTileVizF::FontSizeSbUpClick(TObject *Sender){
  State->FontSize++;
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
  DocStrM->Font->Size=DocStrM->Font->Size+1;
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::FontSizeSbDownClick(TObject *Sender){
  if (State->FontSize>1){
    State->FontSize--;
    FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
    if (DocStrM->Font->Size>1){
      DocStrM->Font->Size=DocStrM->Font->Size-1;}
    PbPaint(Sender);
  }
}

void __fastcall TBowTileVizF::CSpinButton1DownClick(TObject *Sender){
  if (State->BoxWords>1){
    State->BoxWords--;
    BoxWordsEd->Text=TInt::GetStr(State->BoxWords).CStr();
    PbPaint(Sender);
  }
}

void __fastcall TBowTileVizF::CSpinButton1UpClick(TObject *Sender){
  State->BoxWords++;
  BoxWordsEd->Text=TInt::GetStr(State->BoxWords).CStr();
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::DrawEllipsesCbClick(TObject *Sender){
  State->DrawEllipsesP=!State->DrawEllipsesP;
  DrawEllipsesCb->Checked=State->DrawEllipsesP;
  PbPaint(Sender);
}

void __fastcall TBowTileVizF::DrawWordWgtCbClick(TObject *Sender){
  State->DrawWordWgtP=!State->DrawWordWgtP;
  DrawWordWgtCb->Checked=State->DrawWordWgtP;
  PbPaint(Sender);
  UpdateDataP();
}

void TBowTileVizF::UpdateDataP(){
  WordStrLb->Items->Clear();
  DocNmLb->Items->Clear();
  DocStrM->Lines->Clear();
  if (!State->ActClustV.Empty()){
    PBowDocPartClust Clust=State->ActClustV[0];
    // add words string
    TStrFltPrV WordStrWgtPrV;
    Clust->GetTopWordStrWgtPrV(State->BowDocBs, -1, 0.66, WordStrWgtPrV);
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

void __fastcall TBowTileVizF::PbMouseDown(
 TObject *Sender, TMouseButton Button, TShiftState Shift, int PX, int PY){
  if (!State->ClustRectPrV.Empty()){
    double VX=State->Gks->GetPToVX(PX);
    double VY=State->Gks->GetPToVX(PY);
    TBowDocPart::GetClustAtXY(VX, VY, State->ClustRectPrV, true, State->ActClustV);
    PbPaint(Sender);
    UpdateDataP();
    if (DocNmLb->Items->Count>0){
      DocNmLb->ItemIndex=0; DocNmLbClick(Sender);}
  }
}

void __fastcall TBowTileVizF::DocNmLbClick(TObject *Sender){
  DocStrM->Lines->Clear();
  if ((0<=DocNmLb->ItemIndex)&&(DocNmLb->ItemIndex<DocNmLb->Items->Count)){
    TStr DocDescStr=DocNmLb->Items->Strings[DocNmLb->ItemIndex].c_str();
    TStr DocNm; TStr ParenDCSimStr;
    DocDescStr.SplitOnLastCh(DocNm, ' ', ParenDCSimStr);
    int DId=State->BowDocBs->GetDId(DocNm);
    TStr DocStr=State->BowDocBs->GetDocStr(DId);
    DocStrM->Lines->Clear();
    DocStrM->Lines->Add(DocStr.CStr());
    DocStrM->SelStart=0;
  }
}


