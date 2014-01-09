#include "google.h"
#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Get Related Web Pages");
  TStr SrcUrlStr=Env.GetIfArgPrefixStr("-i:", "", "Source-Url");
  //TStr OutXmlUrlFNm=Env.GetIfArgPrefixStr("-oux:", "RelatedUrls.Xml", "Output-Xml-Related-Urls-File");
  TStr OutXmlFCrawlFNm=Env.GetIfArgPrefixStr("-ocx:", "FocusedCrawl.Xml", "Output-Xml-FocusedCrawl-File");
  TStr OutTxtFCrawlFNm=Env.GetIfArgPrefixStr("-oct:", "FocusedCrawl.Txt", "Output-Txt-FocusedCrawl-File");
  bool OutFCrawlDocP=Env.GetIfArgPrefixBool("-ocxdoc:", false, "Output-Focused-Crawl-Document");
  int MxCands=Env.GetIfArgPrefixInt("-mxcands:", -1, "Maximal-Number-Of-Candidates");
  TStr ProxyStr=Env.GetIfArgPrefixStr("-proxy:", "", "Proxy (Domain-Name:Port");
  if (Env.IsEndOfRun()){return 0;}

  // get focused-crawl
  PGgFCrawl FCrawl=TGgFCrawl::GetFCrawl(SrcUrlStr, MxCands, ProxyStr);
  // save focused-crawl to xml
  if (!OutXmlFCrawlFNm.Empty()){
    FCrawl->SaveXml(OutXmlFCrawlFNm, OutFCrawlDocP);}
  // save focused-crawl to text
  if (!OutTxtFCrawlFNm.Empty()){
    FCrawl->SaveTxt(OutTxtFCrawlFNm);}

  return 0;
  Catch;
  return 1;
}

