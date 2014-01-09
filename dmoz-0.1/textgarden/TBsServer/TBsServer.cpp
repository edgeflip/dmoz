#include "mine.h"
#include "webtxtbs.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Text-Base Server");
  TStr InTBsFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-TextBase-FileName");
  int SrvPortN=Env.GetIfArgPrefixInt("-port:", 8888, "Server-Port");
  if (Env.IsEndOfRun()){return 0;}

  // notification
  PNotify Notify=TNotify::StdNotify;

  // load text-base
  TStr TxtBsNm=InTBsFNm.GetFBase();
  TStr TxtBsFPath=InTBsFNm.GetFPath();
  printf("Loading Web-Base...\r");
  PWebTxtBs WebTxtBs=TWebTxtBs::New(Notify);
  WebTxtBs->TxtBsOpenForRdOnly(TxtBsNm, TxtBsFPath);

  // create & activate server
  PWebSrv WebSrv=TWebTxtBsSrv::New(WebTxtBs, SrvPortN, Notify);

  // message loop
  TSysMsg::Loop();

  return 0;
  Catch;
  return 1;
}

