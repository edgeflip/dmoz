//---------------------------------------------------------------------------

#ifndef GraphDrawMH
#define GraphDrawMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TGraphDrawF : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TSplitter *Splitter1;
        TPanel *Panel2;
        TPaintBox *Pb;
        TLabel *Label1;
        TEdit *GraphFNmEd;
        TButton *LoadGraphBt;
        TOpenDialog *LoadGraphOd;
        TStatusBar *StatusBar1;
        TButton *PlaceGraphBySimAnnBt;
        TButton *PlaceTreeAsStarBt;
        TButton *SaveGraphBt;
        TSaveDialog *SaveGraphSd;
        TCSpinButton *FontSizeSb;
        TEdit *FontSizeEd;
        TLabel *Label2;
        TButton *PlaceGraphCircleBt;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PbPaint(TObject *Sender);
        void __fastcall PbMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall PbMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall PbMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PlaceTreeAsStarBtClick(TObject *Sender);
        void __fastcall SaveGraphBtMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall LoadGraphBtMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FontSizeSbUpClick(TObject *Sender);
        void __fastcall FontSizeSbDownClick(TObject *Sender);
        void __fastcall PlaceGraphCircleBtClick(TObject *Sender);
        void __fastcall PlaceGraphBySimAnnBtClick(TObject *Sender);
private:	// User declarations
  class TState;
  TState* State;
public:		// User declarations
        __fastcall TGraphDrawF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphDrawF *GraphDrawF;
//---------------------------------------------------------------------------
#endif
