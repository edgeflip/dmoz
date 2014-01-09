#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Web-Log-Binary To Bag-Of-Words-Weights", -1);
  TStr InWlbFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-WebLogBin-FileName");
  TStr OutUsrBowFNm=Env.GetIfArgPrefixStr("-ousr:", "WebLogUsr.Bow", "Output-UserBow-FileName");
  TStr OutUsrTxtBowFNm=Env.GetIfArgPrefixStr("-ousrtxt:", "WebLogUsrTxt.Bow", "Output-UserTextBow-FileName");
  TStr OutUrlBowFNm=Env.GetIfArgPrefixStr("-ourl:", "WebLogUrl.Bow", "Output-UrlBow-FileName");
  int MnUsrClicks=Env.GetIfArgPrefixInt("-mnusrc:", 10, "Min-User-Clicks");
  int MnUrlClicks=Env.GetIfArgPrefixInt("-mnurlc:", 3, "Min-Url-Clicks");
  TStr WebRootFPath=Env.GetIfArgPrefixStr("-webroot:", "", "Web-Root-Path");
  if (Env.IsEndOfRun()){return 0;}

  // load web-log data
  PWebLog WebLog;
  if (!InWlbFNm.Empty()){
    WebLog=TWebLog::LoadBin(InWlbFNm);
  } else {
    TExcept::Throw("No Input Web-Log-Binary File!");
  }

  // create bag-of-words for users from document-text
  if ((!OutUsrTxtBowFNm.Empty())&&(!WebRootFPath.Empty())){
    printf("*** Users <- Html-Docs\n");
    PBowDocBs UsrHtmlBowDocBs=
     WebLog->GetUsrBowDocBsFromHtml(MnUsrClicks, WebRootFPath);
    printf("Saving to file '%s'... ", OutUsrTxtBowFNm.CStr());
    UsrHtmlBowDocBs->SaveBin(OutUsrTxtBowFNm);
    printf("Done.\n");
  }

  // create bag-of-words for users from urls
  if (!OutUsrBowFNm.Empty()){
    printf("*** Users <- URLs\n");
    PBowDocBs UsrBowDocBs=WebLog->GetUsrBowDocBsFromUrl(MnUsrClicks);
    printf("Saving to file '%s'... ", OutUsrBowFNm.CStr());
    UsrBowDocBs->SaveBin(OutUsrBowFNm);
    printf("Done.\n");
  }

  // create bag-of-words for urls from users
  if (!OutUrlBowFNm.Empty()){
    printf("*** URLs <- Users\n");
    PBowDocBs UrlBowDocBs=WebLog->GetUrlBowDocBsFromUsr(MnUrlClicks);
    printf("Saving to file '%s'... ", OutUrlBowFNm.CStr());
    UrlBowDocBs->SaveBin(OutUrlBowFNm);
    printf("Done.\n");
  }

  return 0;
  Catch;
  return 1;
}

