#include "stdafx.h"
#include "webtxtbs.h"

/////////////////////////////////////////////////
// Web-Text-Base-Notifications
class TWebTxtBsNotify: public TNotify{
public:
  TWebTxtBs* WebTxtBs;
  PSOut LogSOut;
public:
  TWebTxtBsNotify(const PWebTxtBs& _WebTxtBs, const TStr& LogFNm):
    TNotify(), WebTxtBs(_WebTxtBs()), LogSOut(TFOut::New(LogFNm)){}
  static PNotify New(const PWebTxtBs& WebTxtBs, const TStr& LogFNm){
    return new TWebTxtBsNotify(WebTxtBs, LogFNm);}

  void OnNotify(const TNotifyType& Type, const TStr& MsgStr){
    TStr LogStr=TNotify::GetTypeStr(Type)+": "+MsgStr;
    LogSOut->PutStr(LogStr); LogSOut->PutDosLn();
    printf("%s\n", LogStr.CStr());
  }
  void OnStatus(const TStr& MsgStr){
    printf("%s\n", MsgStr.CStr());
    if (WebTxtBs->IsFetchActive()&&WebTxtBs->IsFetchEnd()){TSysMsg::Quit();}
  }
};

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Web-Crawling into Text-Base");
  TStr InWebFilterFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Web-Filter-File");
  TStr OutTBsFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-TextBase-FileName");
  TStr OutLogFNm=Env.GetIfArgPrefixStr("-olog:", "Crawl2TBs.Log", "Output-Log-FileName");
  bool IndexTxtBsP=Env.GetIfArgPrefixBool("-index:", false, "Create-TextBase-Index");
  if (Env.IsEndOfRun()){return 0;}

  // get text-base names
  if (OutTBsFNm.Empty()){
    OutTBsFNm=InWebFilterFNm.GetFPath()+InWebFilterFNm.GetFMid();}
  TStr TxtBsNm=OutTBsFNm.GetFBase();
  TStr TxtBsFPath=OutTBsFNm.GetFPath();

  // create web-text-base
  PWebTxtBs WebTxtBs=TWebTxtBs::New(TNotify::StdNotify);
  WebTxtBs->PutNotify(TWebTxtBsNotify::New(WebTxtBs, OutLogFNm));

  // create text-base
  WebTxtBs->TxtBsNew(TxtBsNm, TxtBsFPath);
  // start fetching
  WebTxtBs->FetchStart(TxtBsNm, TxtBsFPath, InWebFilterFNm, IndexTxtBsP);

  // message loop
  TSysMsg::Loop();

  return 0;
  Catch;
  return 1;
}
