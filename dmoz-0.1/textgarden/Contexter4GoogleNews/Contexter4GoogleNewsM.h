//---------------------------------------------------------------------------

#ifndef Contexter4GoogleNewsMH
#define Contexter4GoogleNewsMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TContexterF : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *Sb;
        TMainMenu *MM;
        TPanel *Panel1;
        TPanel *Panel2;
        TMenuItem *FileMI;
        TEdit *QueryEd;
        TLabel *Label1;
        TButton *EnSearchShowBt;
        TMenuItem *OpenMI;
        TOpenDialog *RSetOd;
        TProgressBar *ProgressBar;
        TTimer *ProgressTimer;
        TMenuItem *SaveAsMI;
        TSaveDialog *RSetSd;
        TPageControl *Pc;
        TTabSheet *EntNetworkTs;
        TSplitter *EnSplitter1;
        TSplitter *EnSplitter3;
        TSplitter *EnSplitter2;
        TGroupBox *CtxNmObjGb;
        TRadioGroup *CtxNmObjSortRg;
        TListBox *CtxNmObjLb;
        TPanel *GrP;
        TPaintBox *EnPb;
        TPanel *Panel4;
        TLabel *Label2;
        TLabel *Label5;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *EnFontSizeEd;
        TCSpinButton *EnFontSizeSb;
        TCheckBox *EnInterNmObjContextCb;
        TEdit *EnDrawLevelsEd;
        TCSpinButton *EnDrawLevelsBt;
        TEdit *EnCtxLenEd;
        TCSpinButton *EnCtxLenSb;
        TEdit *EnSubNodesEd;
        TCSpinButton *EnSubNodesSb;
        TGroupBox *EnCoNmObjGb;
        TListBox *EnCoNmObjLb;
        TGroupBox *EnConceptGb;
        TListBox *EnConceptWordLb;
        TTabSheet *EntLinkageTs;
        TTabSheet *TopicMapTs;
        TGroupBox *DstNmObjGb;
        TRadioGroup *DstNmObjSortRg;
        TListBox *DstNmObjLb;
        TSplitter *Splitter2;
        TGroupBox *SrcNmObjGb;
        TRadioGroup *SrcNmObjSortRg;
        TListBox *SrcNmObjLb;
        TSplitter *Splitter3;
        TPanel *Panel3;
        TPanel *Panel5;
        TRichEdit *NmObjLinkageREd;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *SrcNmObjEd;
        TEdit *DstNmObjEd;
        TMenuItem *TestMI;
        TPanel *Panel6;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *AllDocsLbl;
        TButton *VizualizeBt;
        TEdit *VizClustsEd;
        TEdit *VizClustSimSumPrcEd;
        TEdit *TmFontSizeEd;
        TCSpinButton *TmFontSizeSb;
        TPanel *Panel7;
        TPaintBox *TmPb;
        TCheckBox *EnKeywordsCb;
        TButton *EnSearchMergeShowBt;
        TSplitter *Splitter1;
        TPaintBox *ElPb;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall OpenMIClick(TObject *Sender);
        void __fastcall CtxNmObjLbClick(TObject *Sender);
        void __fastcall NmObjSortRgClick(TObject *Sender);
        void __fastcall EnPbPaint(TObject *Sender);
        void __fastcall EnSearchShowBtClick(TObject *Sender);
        void __fastcall EnInterNmObjContextCbClick(TObject *Sender);
        void __fastcall EnSubNodesSbUpClick(TObject *Sender);
        void __fastcall EnSubNodesSbDownClick(TObject *Sender);
        void __fastcall EnDrawLevelsBtUpClick(TObject *Sender);
        void __fastcall EnDrawLevelsBtDownClick(TObject *Sender);
        void __fastcall EnCtxLenSbUpClick(TObject *Sender);
        void __fastcall EnCtxLenSbDownClick(TObject *Sender);
        void __fastcall EnFontSizeSbUpClick(TObject *Sender);
        void __fastcall EnFontSizeSbDownClick(TObject *Sender);
        void __fastcall CorefNmObjLbClick(TObject *Sender);
        void __fastcall ProgressTimerTimer(TObject *Sender);
        void __fastcall SaveAsMIClick(TObject *Sender);
        void __fastcall SrcDstNmObjLbClick(TObject *Sender);
        void __fastcall TestMIClick(TObject *Sender);
        void __fastcall VizualizeBtClick(TObject *Sender);
        void __fastcall TmPbPaint(TObject *Sender);
        void __fastcall TmFontSizeSbDownClick(TObject *Sender);
        void __fastcall TmFontSizeSbUpClick(TObject *Sender);
        void __fastcall EnKeywordsCbClick(TObject *Sender);
        void __fastcall ElPbPaint(TObject *Sender);
public:	// User declarations
  class TState;
  TState* State;
  void PrepRSetEnv();
  void UpdateClustRectPrV();
public:		// User declarations
        __fastcall TContexterF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TContexterF *ContexterF;
//---------------------------------------------------------------------------
#endif
