#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Web-Log To Web-Log-Binary");
  TStr InWebLogYbTxtFNm=Env.GetIfArgPrefixStr("-iyb:", "", "Input-WebLog-YieldBroker-Text-FileName");
  TStr InWebLogIneTxtFNm=Env.GetIfArgPrefixStr("-iine:", "", "Input-WebLog-Ine-Text-FileName");
  TStr OutWebLogFNm=Env.GetIfArgPrefixStr("-o:", "WebLog.Wlb", "Output-WebLogBinary-FileName");
  if (Env.IsEndOfRun()){return 0;}
  // -iine:../Deploy/Data/IneWebLog.Txt -o:../Deploy/Data/IneWebLog.Wlb
  // -iyb:../Deploy/Data/YbWebLog.Txt -o:../Deploy/Data/YbWebLog.Wlb

  // load web-log data
  PWebLog WebLog;
  if (!InWebLogIneTxtFNm.Empty()){
    WebLog=TWebLog::LoadTxt(InWebLogIneTxtFNm);
  } else
  if (!InWebLogYbTxtFNm.Empty()){
    WebLog=TWebLog::LoadYbTxt(InWebLogYbTxtFNm);
  } else {
    TExcept::Throw("No Input Web-Log File!");
  }

  // save binary file
  if (!OutWebLogFNm.Empty()){
    printf("Saving web-log-binary file '%s'... ", OutWebLogFNm.CStr());
    WebLog->SaveBin(OutWebLogFNm);
    printf("Done.\n");
  }

  return 0;
  Catch;
  return 1;
}
