#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Text To Compact-Documents");
  TStr InCpdFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Cpd-Path");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-Text-File");
  if (Env.IsEndOfRun()){return 0;}

  printf("Extracting Cpd File '%s' into Text File '%s' ...\n", InCpdFNm.CStr(), OutTxtFNm.CStr());
  PSIn CpdSIn=TCpDoc::FFirstCpd(InCpdFNm); PCpDoc CpDoc; int CpDocN=0;
  PSOut TxtSOut=TFOut::New(OutTxtFNm); FILE* fTxt=TxtSOut->GetFileId();
  while (TCpDoc::FNextCpd(CpdSIn, CpDoc)){
    CpDocN++; printf("%d\r", CpDocN);
    fprintf(fTxt, "%s\n", CpDoc->GetTitleStr().CStr());
    for (int ParN=0; ParN<CpDoc->GetPars(); ParN++){
      TStr ParStr=CpDoc->GetParStr(ParN);
      fprintf(fTxt, "%s\n", ParStr.CStr());
    }
    fprintf(fTxt, "\n");
  }
  printf("\nDone.\n");

  return 0;
  Catch;
  return 1;
}

