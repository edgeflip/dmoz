#include "net.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  printf("(c) Marko Grobelnik & Dunja Mladenic, http://ai.ijs.si/\n");
  Env.PrepArgs("Get Web-Page From Internet");
  TStr InUrlStr=Env.GetIfArgPrefixStr("-iurl:", "", "Input-Url");
  TStr InUrlListFNm=Env.GetIfArgPrefixStr("-ilist:", "", "Input-Url-List");
  TStr OutFNm=Env.GetIfArgPrefixStr("-o:", "WebPage", "Output-FileName-Base");
  bool OutHttpP=Env.GetIfArgPrefixBool("-ohttp:", false, "Output-Http-File");
  bool OutHttpBodyP=Env.GetIfArgPrefixBool("-obody:", true, "Output-Http-Body-File");
  bool OutXmlP=Env.GetIfArgPrefixBool("-oxml:", false, "Output-Xml-File");
  bool OutXmlTextP=Env.GetIfArgPrefixBool("-xotxt:", true, "Xml-Output-Text");
  bool OutXmlUrlP=Env.GetIfArgPrefixBool("-xourl:", true, "Xml-Output-Urls");
  bool OutXmlToksP=Env.GetIfArgPrefixBool("-xotok:", true, "Xml-Output-Tokens");
  bool OutXmlTagsP=Env.GetIfArgPrefixBool("-xotag:", true, "Xml-Output-Tags");
  bool OutXmlArgsP=Env.GetIfArgPrefixBool("-xoarg:", true, "Xml-Output-Arguments");
  bool OutTxtP=Env.GetIfArgPrefixBool("-otxt:", false, "Output-Text-File");
  bool OutTxtUrlP=Env.GetIfArgPrefixBool("-tourl:", false, "Text-Output-Urls");
  bool OutTxtTagsP=Env.GetIfArgPrefixBool("-totag:", false, "Text-Output-Tags");
  bool OutScrP=Env.GetIfArgPrefixBool("-oscr:", false, "Output-To-Screen");
  TStr UserAgent=Env.GetIfArgPrefixStr("-ua:", "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0)", "User-Agent");
  int MxConns=Env.GetIfArgPrefixInt("-mxconns:", 10, "Max-Connections");
  
  if (Env.IsEndOfRun()){return 0;}

  // fetch page
  TWebPgToFileFetch WebFetch(
   OutFNm, OutHttpP, OutHttpBodyP,
   OutXmlP, OutXmlTextP, OutXmlUrlP, OutXmlToksP, OutXmlTagsP, OutXmlArgsP,
   OutTxtP, OutTxtUrlP, OutTxtTagsP,
   OutScrP, true);
  WebFetch.PutUserAgentStr(UserAgent);
  WebFetch.PutMxConns(MxConns);

  if (!InUrlStr.Empty()) {
    WebFetch.FetchUrl(InUrlStr);
  } else if (!InUrlListFNm.Empty()) {
    printf("Loading Urls .");
    TStr InUrlListStr = TStr::LoadTxt(InUrlListFNm); 
    TStrV UrlStrV; InUrlListStr.SplitOnAllCh('\n', UrlStrV); printf(".\n");
    for (int UrlStrN = 0; UrlStrN < UrlStrV.Len(); UrlStrN++) {
      if (UrlStrN % 1000 == 0) { printf("%d\r", UrlStrN); }
      TStr UrlStr = UrlStrV[UrlStrN];
      UrlStr.DelChAll('\r');
      WebFetch.FetchUrl(UrlStr);
    } printf("%d\n", UrlStrV.Len());
  } else {
    return 0;
  }

  if (!WebFetch.Empty()) { 
    printf("Crawling ...\n"); 
    TSysMsg::Loop(); 
  }

  return 0;
  Catch;
  return 1;
}

