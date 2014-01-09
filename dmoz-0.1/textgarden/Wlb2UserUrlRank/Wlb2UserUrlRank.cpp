#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Web-Log-Binary To User/Url-Rankings", -1);
  TStr InWlbFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-WebLogBin-FileName");
  TStr OutUURankXmlFNm=Env.GetIfArgPrefixStr("-ox:", "WebUsrUrlRank.Xml", "Output-UserUrlRank-Xml-FileName");
  TStr OutUURankTxtFNm=Env.GetIfArgPrefixStr("-ot:", "WebUsrUrlRank.Txt", "Output-UserUrlRank-Text-FileName");
  bool OutScrP=Env.GetIfArgPrefixBool("-os:", true, "Output-To-Screen");
  int TopRanks=Env.GetIfArgPrefixInt("-topranks:", 100, "Output-Top-Ranks");
  if (Env.IsEndOfRun()){return 0;}

  // load web-log data
  PWebLog WebLog;
  if (!InWlbFNm.Empty()){
    WebLog=TWebLog::LoadBin(InWlbFNm);
  } else {
    TExcept::Throw("No Input Web-Log-Binary File!");
  }

  // calculate rankings
  TFltIntKdV WgtUsrIdKdV; TFltIntKdV WgtUrlIdKdV;
  WebLog->GetUsrUrlRank(WgtUsrIdKdV, WgtUrlIdKdV);

  // output results
  // output to xml
  if (!OutUURankXmlFNm.Empty()){
    PSOut SOut=TFOut::New(OutUURankXmlFNm);
    WebLog->SaveXmlUURank(SOut, WgtUsrIdKdV, WgtUrlIdKdV, TopRanks);
  }
  // output to text
  if (!OutUURankTxtFNm.Empty()){
    PSOut SOut=TFOut::New(OutUURankTxtFNm);
    WebLog->SaveTxtUURank(SOut, WgtUsrIdKdV, WgtUrlIdKdV, TopRanks);
  }
  // output to screen
  if (OutScrP){
    PSOut SOut=TSOut::StdOut;
    WebLog->SaveTxtUURank(SOut, WgtUsrIdKdV, WgtUrlIdKdV, TopRanks);
  }

  return 0;
  Catch;
  return 1;
}

