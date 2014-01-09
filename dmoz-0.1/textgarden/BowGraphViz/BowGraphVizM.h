//---------------------------------------------------------------------------

#ifndef BowGraphVizMH
#define BowGraphVizMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TBowGraphVizF : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TSplitter *Splitter1;
        TLabel *Label1;
        TEdit *BowDocBsFNmEd;
        TButton *BowDocBsFNmBrowseBt;
        TOpenDialog *BowDocBsOd;
        TLabel *Label2;
        TEdit *VizDocsEd;
        TButton *VizualizeBt;
        TLabel *Label3;
        TEdit *VizClustsEd;
        TLabel *Label4;
        TEdit *VizClustSimSumPrcEd;
        TLabel *Label5;
        TEdit *FontSizeEd;
        TCSpinButton *FontSizeSb;
        TCheckBox *DrawWordWgtCb;
        TLabel *AllDocsLbl;
        TPanel *DataP;
        TGroupBox *GroupBox3;
        TGroupBox *VisGb;
        TPaintBox *Pb;
        TMemo *DocStrM;
        TPanel *WordStrDataNmP;
        TGroupBox *WordStrGb;
        TListBox *WordStrLb;
        TSplitter *WordStrDocNmS;
        TGroupBox *DocNmGb;
        TListBox *DocNmLb;
        TSplitter *VisDataS;
        TSplitter *WordStrDocStrS;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BowDocBsFNmBrowseBtClick(TObject *Sender);
        void __fastcall VizualizeBtClick(TObject *Sender);
        void __fastcall PbPaint(TObject *Sender);
        void __fastcall FontSizeSbDownClick(TObject *Sender);
        void __fastcall FontSizeSbUpClick(TObject *Sender);
        void __fastcall DrawWordWgtCbClick(TObject *Sender);
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
  void UpdateClustRectPrV();
  void UpdateDataP();
public:		// User declarations
        __fastcall TBowGraphVizF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBowGraphVizF *BowGraphVizF;
//---------------------------------------------------------------------------
#endif
