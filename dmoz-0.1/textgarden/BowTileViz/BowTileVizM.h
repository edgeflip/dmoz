//---------------------------------------------------------------------------

#ifndef BowTileVizMH
#define BowTileVizMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TBowTileVizF : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TSplitter *Splitter1;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *BowDocBsFNmEd;
        TButton *BowDocBsFNmBrowseBt;
        TEdit *VizDocsEd;
        TButton *VisualizeBt;
        TEdit *MxDocsPerLeafClustEd;
        TOpenDialog *BowDocBsOd;
        TLabel *Label4;
        TEdit *FontSizeEd;
        TCSpinButton *FontSizeSb;
        TCheckBox *DrawEllipsesCb;
        TCheckBox *DrawWordWgtCb;
        TEdit *BoxWordsEd;
        TCSpinButton *CSpinButton1;
        TLabel *Labl99;
        TLabel *AllDocsLbl;
        TPanel *DataP;
        TGroupBox *GroupBox3;
        TGroupBox *VisGb;
        TSplitter *VisDataS;
        TSplitter *WordStrDocStrS;
        TPaintBox *Pb;
        TMemo *DocStrM;
        TPanel *WordStrDataNmP;
        TGroupBox *WordStrGb;
        TListBox *WordStrLb;
        TSplitter *WordStrDocNmS;
        TGroupBox *DocNmGb;
        TListBox *DocNmLb;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BowDocBsFNmBrowseBtClick(TObject *Sender);
        void __fastcall VisualizeBtClick(TObject *Sender);
        void __fastcall PbPaint(TObject *Sender);
        void __fastcall FontSizeSbUpClick(TObject *Sender);
        void __fastcall FontSizeSbDownClick(TObject *Sender);
        void __fastcall DrawEllipsesCbClick(TObject *Sender);
        void __fastcall DrawWordWgtCbClick(TObject *Sender);
        void __fastcall CSpinButton1DownClick(TObject *Sender);
        void __fastcall CSpinButton1UpClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall VisDataSMoved(TObject *Sender);
        void __fastcall WordStrDocStrSMoved(TObject *Sender);
        void __fastcall WordStrDocNmSMoved(TObject *Sender);
        void __fastcall PbMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall DocNmLbClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  class TState;
  TState* State;
  void UpdateDataP();
public:		// User declarations
        __fastcall TBowTileVizF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBowTileVizF *BowTileVizF;
//---------------------------------------------------------------------------
#endif
