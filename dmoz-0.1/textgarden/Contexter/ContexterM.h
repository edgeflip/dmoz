//---------------------------------------------------------------------------

#ifndef ContexterMH
#define ContexterMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TContexterF : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *NmObjGb;
        TSplitter *Splitter1;
        TPanel *GrP;
        TSplitter *Splitter2;
        TGroupBox *ConceptGb;
        TMainMenu *MM;
        TMenuItem *FileMI;
        TMenuItem *OpenMI;
        TOpenDialog *NmObjBsFNmOd;
        TRadioGroup *NmObjSortRg;
        TListBox *NmObjLb;
        TListBox *ConceptWordLb;
        TSplitter *Splitter3;
        TGroupBox *CoNmObjGb;
        TListBox *CoNmObjLb;
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TPaintBox *Pb;
        TLabel *Label1;
        TLabel *Label5;
        TEdit *FontSizeEd;
        TCSpinButton *FontSizeSb;
        TCheckBox *InterNmObjContextCb;
        TLabel *Label3;
        TEdit *DrawLevelsEd;
        TCSpinButton *DrawLevelsBt;
        TEdit *CtxLenEd;
        TCSpinButton *CtxLenSb;
        TLabel *Label4;
        TEdit *SubNodesEd;
        TCSpinButton *SubNodesSb;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OpenMIClick(TObject *Sender);
        void __fastcall NmObjSortRgClick(TObject *Sender);
        void __fastcall NmObjLbClick(TObject *Sender);
        void __fastcall CoNmObjLbClick(TObject *Sender);
        void __fastcall PbPaint(TObject *Sender);
        void __fastcall FontSizeSbUpClick(TObject *Sender);
        void __fastcall FontSizeSbDownClick(TObject *Sender);
        void __fastcall InterNmObjContextCbClick(TObject *Sender);
        void __fastcall DrawLevelsBtUpClick(TObject *Sender);
        void __fastcall DrawLevelsBtDownClick(TObject *Sender);
        void __fastcall CtxLenSbDownClick(TObject *Sender);
        void __fastcall CtxLenSbUpClick(TObject *Sender);
        void __fastcall SubNodesSbUpClick(TObject *Sender);
        void __fastcall SubNodesSbDownClick(TObject *Sender);
private:	// User declarations
  class TState;
public:		// User declarations
  TState* State;
        __fastcall TContexterF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TContexterF *ContexterF;
//---------------------------------------------------------------------------
#endif
