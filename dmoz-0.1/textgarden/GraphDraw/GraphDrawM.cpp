//---------------------------------------------------------------------------

#include <vcl.h>
#include "graph.h"
#include "gksvcl.h"
#pragma hdrstop

#include "GraphDrawM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TGraphDrawF *GraphDrawF;

/////////////////////////////////////////////////
// State
class TGraphDrawF::TState{
public:
  PGks Gks;
  PGraph Graph;
  int FontSize;
  double BorderFac;
  bool SelP;
  int SelPX1, SelPY1, SelPX2, SelPY2;
  bool MoveP;
  int MovePX, MovePY;
public:
  TState():
    Gks(), Graph(), FontSize(8), BorderFac(0.1),
    SelP(false), MoveP(false){}
};

/////////////////////////////////////////////////
// Top-Level
__fastcall TGraphDrawF::TGraphDrawF(TComponent* Owner): TForm(Owner){}

void __fastcall TGraphDrawF::FormCreate(TObject *Sender){
  State=new TState();
  State->Gks=TVclGks::New(Pb);
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
}

void __fastcall TGraphDrawF::FormClose(TObject *Sender, TCloseAction &Action){
  delete State;
}

void __fastcall TGraphDrawF::LoadGraphBtMouseDown(
 TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y){
  // load with the dialog
  if (Button==mbLeft){
    if (LoadGraphOd->Execute()){
      TStr GraphFNm=LoadGraphOd->FileName.c_str();
      GraphFNmEd->Text=GraphFNm.CStr();
      if (GraphFNm.GetFExt().GetUc()==".XML"){
        State->Graph=TGraph::LoadXml(GraphFNm);
      } else {
        State->Graph=TGraph::LoadTxt(GraphFNm);
      }
      State->BorderFac=0.1;
      // draw graph
      PbPaint(Sender);
    }
  }
  // load without the dialog
  if (Button==mbRight){
    TStr GraphFNm=GraphFNmEd->Text.c_str();
    if (!GraphFNm.Empty()){
      State->Graph=TGraph::LoadTxt(GraphFNm);
      State->BorderFac=0.1;
      // draw graph
      PbPaint(Sender);
    }
  }
}

void __fastcall TGraphDrawF::SaveGraphBtMouseDown(
 TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y){
  if (State->Graph.Empty()){return;}
  // save with the dialog
  if (Button==mbLeft){
    SaveGraphSd->FileName=GraphFNmEd->Text.c_str();
    if (SaveGraphSd->Execute()){
      TStr GraphFNm=SaveGraphSd->FileName.c_str();
      //GraphFNmEd->Text=GraphFNm.CStr();
      if (GraphFNm.GetFExt().GetUc()==".XML"){
        State->Graph->SaveXml(GraphFNm);
        //TStr XmlStr; State->Graph->GetXmlDoc()->SaveStr(XmlStr);
        //PXmlDoc XmlDoc=TXmlDoc::LoadStr(XmlStr);
        //TStr XmlStr1; XmlDoc->SaveStr(XmlStr1);
      } else
      if (GraphFNm.GetFExt().GetUc()==".TAB"){
        State->Graph->SaveTxtTab(GraphFNm);
      } else {
        State->Graph->SaveTxt(GraphFNm);
      }
    }
  }
  // save without the dialog
  if (Button==mbRight){
    TStr GraphFNm=GraphFNmEd->Text.c_str();
    State->Graph->SaveTxt(GraphFNm);
  }
}

void __fastcall TGraphDrawF::PlaceGraphBySimAnnBtClick(TObject *Sender){
  if (State->Graph.Empty()){return;}
  // place graph
  TRnd Rnd(0);
  State->Graph->PlaceSimAnnXY(Rnd, State->Gks);
  // reascale coordinates to fit
  State->Graph->RescaleXY(State->BorderFac);
  // draw graph
  PbPaint(Sender);
}

void __fastcall TGraphDrawF::PlaceTreeAsStarBtClick(TObject *Sender){
  if (State->Graph.Empty()){return;}
  // test tree structure
  PVrtx RootVrtx;
  if (State->Graph->IsTree(RootVrtx)){
    // place graph
    State->Graph->PlaceTreeAsStar();
    // reascale coordinates to fit
    State->Graph->RescaleXY(State->BorderFac, RootVrtx);
    // draw a graph
    PbPaint(Sender);
  } else {
    Application->MessageBox("Graph has not a tree structure!", "Warning", MB_OK);
  }
}

void __fastcall TGraphDrawF::PlaceGraphCircleBtClick(TObject *Sender){
  if (State->Graph.Empty()){return;}
  // place graph
  State->Graph->PlaceCircle();
  // reascale coordinates to fit
  State->Graph->RescaleXY(State->BorderFac);
  // draw graph
  PbPaint(Sender);
}

void __fastcall TGraphDrawF::PbPaint(TObject *Sender){
  if (!State->Graph.Empty()){
    State->Gks->Clr();
    State->Graph->Draw(State->Gks, true, true, State->FontSize);
  }
}

void __fastcall TGraphDrawF::PbMouseDown(TObject *Sender,
 TMouseButton Button, TShiftState Shift, int X, int Y){
  if (State->Graph.Empty()){return;}
  // left button + ctrl-key
  if ((Button==mbLeft)&&(Shift.Contains(ssCtrl))){
    PVrtx Vrtx; PEdge Edge;
    if (State->Graph->IsVrtxAt(State->Gks, X, Y, Vrtx)){
      State->Graph->GetPp()->AddPpStr("BoldVNm");
      State->Graph->GetPp()->PutValStr("BoldVNm", Vrtx->GetVNm());
    }
    //if (State->Graph->IsEdgeAt(State->Gks, X, Y, Edge)){}
  }
  // left button
  if (Button==mbLeft){
    // prepare selection coordinates
    State->SelP=true;
    State->SelPX1=X; State->SelPY1=Y;
    State->SelPX2=X; State->SelPY2=Y;
    // draw rectangle
    State->Gks->SetPen(TGksPen::New(TGksColor::GetRed(), gpmXor, gpsSolid));
    State->Gks->SetBrush(TGksBrush::New(TGksColor::GetRed(), gbsSolid));
    State->Gks->Rectangle(State->SelPX1, State->SelPY1, State->SelPX2, State->SelPY2);
  }
  // right button
  if (Button==mbRight){
    // prepare selection coordinates
    State->MoveP=true;
    State->MovePX=X; State->MovePY=Y;
  }
}

void __fastcall TGraphDrawF::PbMouseMove(TObject *Sender,
 TShiftState Shift, int X, int Y){
  if (State->Graph.Empty()){return;}
  // left button
  if (State->SelP){
    // remove rectangle
    State->Gks->SetPen(TGksPen::New(TGksColor::GetRed(), gpmXor, gpsSolid));
    State->Gks->SetBrush(TGksBrush::New(TGksColor::GetRed(), gbsSolid));
    State->Gks->Rectangle(State->SelPX1, State->SelPY1, State->SelPX2, State->SelPY2);
    // update coordinates
    State->SelPX2=X; State->SelPY2=Y;
    // draw rectangle
    State->Gks->Rectangle(State->SelPX1, State->SelPY1, State->SelPX2, State->SelPY2);
  }
  // right button
  if (State->MoveP){
    // get offset from previous coordinates
    int PXDiff=State->MovePX-X;
    int PYDiff=State->MovePY-Y;
    // update coordinates
    State->MovePX=X; State->MovePY=Y;
    // translation
    double VXDiff=State->Gks->GetPToVX(PXDiff);
    double VYDiff=State->Gks->GetPToVY(PYDiff);
    State->Graph->RescaleXY(0+VXDiff, 0+VYDiff, 1+VXDiff, 1+VYDiff);
    // redraw
    PbPaint(Sender);
  }
}

void __fastcall TGraphDrawF::PbMouseUp(TObject *Sender,
 TMouseButton Button, TShiftState Shift, int X, int Y){
  if (State->Graph.Empty()){return;}
  // left button
  if (State->SelP){
    // remove rectangle
    State->Gks->SetPen(TGksPen::New(TGksColor::GetRed(), gpmXor, gpsSolid));
    State->Gks->SetBrush(TGksBrush::New(TGksColor::GetRed(), gbsSolid));
    State->Gks->Rectangle(State->SelPX1, State->SelPY1, State->SelPX2, State->SelPY2);
    // disable selection & update coordinates
    State->SelP=false;
    State->SelPX2=X; State->SelPY2=Y;
    // rescale
    if ((State->SelPX1>State->SelPX2)||(State->SelPY1>State->SelPY2)){
      State->Graph->RescaleXY(State->BorderFac);
    } else {
      double SelVX1=State->Gks->GetPToVX(State->SelPX1);
      double SelVY1=State->Gks->GetPToVY(State->SelPY1);
      double SelVX2=State->Gks->GetPToVX(State->SelPX2);
      double SelVY2=State->Gks->GetPToVY(State->SelPY2);
      State->Graph->RescaleXY(SelVX1, SelVY1, SelVX2, SelVY2);
    }
    // redraw
    PbPaint(Sender);
  }
  // right button
  if (State->MoveP){
    // disable moving
    State->MoveP=false;
    // get offset from previous coordinates
    int PXDiff=State->MovePX-X;
    int PYDiff=State->MovePY-Y;
    // translation
    double VXDiff=State->Gks->GetPToVX(PXDiff);
    double VYDiff=State->Gks->GetPToVY(PYDiff);
    State->Graph->RescaleXY(0+VXDiff, 0+VYDiff, 1+VXDiff, 1+VYDiff);
    // redraw
    PbPaint(Sender);
  }
}

void __fastcall TGraphDrawF::FormKeyDown(TObject *Sender, WORD &Key,
 TShiftState Shift){
  if (State->Graph.Empty()){return;}
  // increase/decrease border & rescale
  double DX=0.03; double DY=0.03;
  if (Key==107/*'+'*/){State->Graph->RescaleXY(0+DX, 0+DY, 1-DX, 1-DY);}
  if (Key==109/*'-'*/){State->Graph->RescaleXY(0-DX, 0-DY, 1+DX, 1+DY);}
  if (Key==VK_LEFT){State->Graph->RescaleXY(0+DX, 0, 1+DX, 1);}
  if (Key==VK_UP){State->Graph->RescaleXY(0, 0+DX, 1, 1+DX);}
  if (Key==VK_RIGHT){State->Graph->RescaleXY(0-DX, 0, 1-DX, 1);}
  if (Key==VK_DOWN){State->Graph->RescaleXY(0, 0-DX, 1, 1-DX);}
  // redraw
  PbPaint(Sender);
}

void __fastcall TGraphDrawF::FontSizeSbUpClick(TObject *Sender){
  State->FontSize++;
  FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
  PbPaint(Sender);
}

void __fastcall TGraphDrawF::FontSizeSbDownClick(TObject *Sender){
  if (State->FontSize>0){
    State->FontSize--;
    FontSizeEd->Text=TInt::GetStr(State->FontSize).CStr();
    PbPaint(Sender);
  }
}


