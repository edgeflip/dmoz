#include "crawler.h"

void GetPresetConfig(const TStr& ConfigNm, const PCrawlerDef& Def,
 TStr& CrawlBsNm, TStr& CrawlBsFPath, TStr& CrawlBsFAccessNm, int& CrawlBsMxSegLen){
  TSysMemStat MemStat;
  // Slovenia
  if (ConfigNm=="bled"){
    // storage
    CrawlBsNm="bled";
    CrawlBsFPath="Data";
    CrawlBsMxSegLen=1000000000;
    // crawling parameters
    int MxUrls=1000000;
    Def->PutMxUrls(MxUrls);
    Def->PutMnConns(1);
    Def->PutMxConns(100);
    Def->PutMxConnsPerSrv(3);
    Def->PutAfterFetchDelaySecs(1);
    Def->PutMxLev(5);
    Def->PutMxDep(2);
    Def->PutMxContLen(10000000);
    Def->PutMnQLen(100000);
    Def->PutQResetMod(100000);
    Def->PutMxQSegLen(10000000);
    Def->PutMxRetries(2);
    Def->PutRevisitSecs(-1);
    Def->PutRedirDmAllowed(false);
    Def->AddStartUrlStr("http://www.bled.si/");
    Def->AddRqDmNm(".bled.si");
    //Def->AddRqContTypeNm("text/*");
    Def->OptHtmlCrawling();
    Def->LoadUrlStrV("Url-Slovakia.Txt");
  }
  if (ConfigNm=="default"){
    // storage
    CrawlBsNm="crawl";
    CrawlBsFPath="Data";
    CrawlBsMxSegLen=1000000000;
    // crawling parameters
    int MxUrls=TSysMemStat::Is64Bit()&&(MemStat.GetTotalPhys()>uint64(4000000000)) ? TB4Def::GetP2(25) : TB4Def::GetP2(20);
    Def->PutMxUrls(MxUrls);
    Def->PutMnConns(1);
    Def->PutMxConns(100);
    Def->PutMxConnsPerSrv(3);
    Def->PutAfterFetchDelaySecs(1);
    Def->PutMxLev(5);
    Def->PutMxDep(-1);
    Def->PutMxContLen(10000000);
    Def->PutMnQLen(100000);
    Def->PutQResetMod(100000);
    Def->PutMxQSegLen(10000000);
    Def->PutMxRetries(2);
    Def->PutRevisitSecs(-1);
    Def->PutRedirDmAllowed(false);
    //Def->AddStartUrlStr("http://www.research.microsoft.com/");
    //Def->AddRqDmNm("research.microsoft.com"); 
    // content-type
    Def->AddRqContTypeNm("text/*");
  }
  // Croatia
  if (ConfigNm=="hr"){
    // storage
    CrawlBsNm="hr";
    CrawlBsFPath="Data";
    CrawlBsMxSegLen=1000000000;
    // crawling parameters
    int MxUrls=TSysMemStat::Is64Bit()&&(MemStat.GetTotalPhys()>uint64(4000000000)) ? TB4Def::GetP2(25) : TB4Def::GetP2(20);
    Def->PutMxUrls(MxUrls);
    Def->PutMnConns(10);
    Def->PutMxConns(100);
    Def->PutMxConnsPerSrv(2);
    Def->PutAfterFetchDelaySecs(1);
    Def->PutMxLev(5);
    Def->PutMxDep(-1);
    Def->PutMxContLen(10000000);
    Def->PutMnQLen(100000);
    Def->PutQResetMod(100000);
    Def->PutMxQSegLen(10000000);
    Def->PutMxRetries(2);
    Def->PutRevisitSecs(100);
    Def->PutRedirDmAllowed(false);
    // starting-points
    Def->AddStartUrlStr("http://www.hr/");
    // allowed-domains
    Def->AddRqDmNm(".hr");
  }
  // Slovenia
  if (ConfigNm=="si"){
    // storage
    CrawlBsNm="si";
    CrawlBsFPath="Data";
    CrawlBsMxSegLen=1000000000;
    // crawling parameters
    int MxUrls=TSysMemStat::Is64Bit()&&(MemStat.GetTotalPhys()>uint64(4000000000)) ? TB4Def::GetP2(25) : TB4Def::GetP2(20);
    Def->PutMxUrls(MxUrls);
    Def->PutMnConns(10);
    Def->PutMxConns(100);
    Def->PutMxConnsPerSrv(1);
    Def->PutAfterFetchDelaySecs(10);
    Def->PutMxLev(5);
    Def->PutMxDep(-1);
    Def->PutMxContLen(10000000);
    Def->PutMnQLen(100000);
    Def->PutQResetMod(100000);
    Def->PutMxQSegLen(10000000);
    Def->PutMxRetries(2);
    Def->PutRevisitSecs(100);
    Def->PutRedirDmAllowed(false);
    // starting-points
    Def->AddStartUrlStr("http://www.matkurja.com/"); 
    Def->AddStartUrlStr("http://www.najdi.si/");
    Def->AddStartUrlStr("http://www.slowwwenia.com/"); 
    Def->AddStartUrlStr("http://www.raziskovalec.com/");
    Def->AddStartUrlStr("http://www.arnes.si/");
    Def->AddStartUrlStr("http://www.siol.net/");
    Def->AddStartUrlStr("http://www.s5.net/");
    Def->AddStartUrlStr("http://www.volja.net/");
    Def->AddStartUrlStr("http://www.amis.net/");
    Def->AddStartUrlStr("http://www.ijs.si/"); 
    Def->AddStartUrlStr("http://www.uni-lj.si/"); 
    Def->AddStartUrlStr("http://www.uni-mb.si/"); 
    Def->AddStartUrlStr("http://www.upr.si/");
    Def->AddStartUrlStr("http://www.gov.si/");
    Def->AddStartUrlStr("http://www.slovenia-tourism.si/");
    Def->AddStartUrlStr("http://www.sta.si/"); 
    Def->AddStartUrlStr("http://www.rtvslo.si/");
    Def->AddStartUrlStr("http://www.24ur.com/");
    Def->AddStartUrlStr("http://www.infonet.fm/");
    Def->AddStartUrlStr("http://www.delo.si/"); 
    Def->AddStartUrlStr("http://www.dnevnik.si/"); 
    Def->AddStartUrlStr("http://www.vecer.si/"); 
    Def->AddStartUrlStr("http://www.finance-on.net/"); 
    Def->AddStartUrlStr("http://www.ljnovice.com/");
    Def->AddStartUrlStr("http://www.dohodnina.com/"); 
    Def->AddStartUrlStr("http://www.mladina.si/"); 
    Def->AddStartUrlStr("http://www.preseren.net/");
    Def->AddStartUrlStr("http://www.murn-aleksandrov.net/");
    Def->AddStartUrlStr("http://www.brank.org/");
    // allowed-domains
    Def->AddRqDmNm(".si"); 
    Def->AddRqDmNm("matkurja.com"); 
    Def->AddRqDmNm("slowwwenia.com"); 
    Def->AddRqDmNm("raziskovalec.com"); 
    Def->AddRqDmNm("siol.net");
    Def->AddRqDmNm("s5.net");
    Def->AddRqDmNm("volja.net");
    Def->AddRqDmNm("amis.net");
    Def->AddRqDmNm("24ur.com");
    Def->AddRqDmNm("infonet.fm");
    Def->AddRqDmNm("finance-on.net");
    Def->AddRqDmNm("ljnovice.com"); 
    Def->AddRqDmNm("dohodnina.com");
    Def->AddRqDmNm("preseren.net");
    Def->AddRqDmNm("murn-aleksandrov.net");
    Def->AddRqDmNm("brank.org");
    // allowed-content-types
    // Def->AddRqContTypeNm("text/*");
  } 
}

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Web-Bird-Crawler", 1);
  TStr ConfigNm=Env.GetIfArgPrefixStr("-preset:", "", "Preset-Configuration-Name (values: si, hr)");
  TStr CrawlBsNm=Env.GetIfArgPrefixStr("-cb:", "crawl", "Crawl-Base-Name");
  TStr CrawlBsFPath=Env.GetIfArgPrefixStr("-cp:", "", "Crawl-File-Path");
  TStr CrawlBsFAccessNm=Env.GetIfArgPrefixStr("-cbacc:", "new", "Crawl-Base-Access (new or cont[inue]) or rest[ore]");
  int CrawlBsMxSegLen=Env.GetIfArgPrefixInt("-csl:", 1000000000, "Crawl-File-Maximum-Segment-Length");
  int MxUrls=Env.GetIfArgPrefixInt("-mxurls:", 10000000, "Maximum-Number-Of-Urls");
  int MnConns=Env.GetIfArgPrefixInt("-mnc:", 1, "Minimum-Connections");
  int MxConns=Env.GetIfArgPrefixInt("-mxc:", 100, "Maximum-Connections");
  int MxConnsPerSrv=Env.GetIfArgPrefixInt("-mxcps:", 1, "Maximum-Connections-Per-Server");
  int AfterFetchDelaySecs=Env.GetIfArgPrefixInt("-afdelay:", 0, "After-Fetch-Delay");
  int MxLev=Env.GetIfArgPrefixInt("-mxlevs:", -1, "Maximum-Levels");
  int MxDep=Env.GetIfArgPrefixInt("-mxdep:", -1, "Maximum-Depth");
  int MxContLen=Env.GetIfArgPrefixInt("-mxcl:", 10000000, "Maximum-Content-Length");
  int MnQLen=Env.GetIfArgPrefixInt("-mnq:", 100000, "Minimum-Queue-Length");
  int QResetMod=Env.GetIfArgPrefixInt("-qrm:", 100000, "Queue-Reset-Modulo");
  int MxQSegLen=Env.GetIfArgPrefixInt("-mxqsl:", 10000000, "Maximum-Queue-Segment-Length");
  int MxRetries=Env.GetIfArgPrefixInt("-mxhr:", 2, "Maximum-Http-Retries");
  int RevisitSecs=Env.GetIfArgPrefixInt("-revsec:", -1, "Revisit-Seconds");
  bool RedirDmAllowedP=Env.GetIfArgPrefixBool("-redirdm:", false, "Redirection-Domains-Allowed");
  TStrV StartUrlStrV=Env.GetIfArgPrefixStrV("-surl:", "Start-Url (multiple)");
  TStrV RqDmNmV=Env.GetIfArgPrefixStrV("-dm:", "Required Domains (multiple)");
  TStrV BadDmNmV=Env.GetIfArgPrefixStrV("-bdm:", "Bad Domains (multiple)");
  TStr GeoIpBsFNm=Env.GetIfArgPrefixStr("-geoip:", "Country.GeoIp", "GeoIP-FileName");
  TStrV CountryNmV=Env.GetIfArgPrefixStrV("-country:", "Country-Names to Crawl (multiple)");
  TStrV SiteUrlStrV=Env.GetIfArgPrefixStrV("-site:", "URLs of Sites to Crawl (multiple)");
  TStr SiteUrlStrVFNm=Env.GetIfArgPrefixStr("-sitef:", "", "File-Name with URLs of Sites to Crawl");
  TStrV RqContTypeNmV=Env.GetIfArgPrefixStrV("-ct:", "Required Content-Types (multiple)");
  TStrV BadFExtV=Env.GetIfArgPrefixStrV("-badext:", "Bad-File-Extensions (multiple)");
  bool OptHtmlCrawlP=Env.GetIfArgPrefixBool("-opthtml:", false, "Optimise-Html-Crawling");
  if (Env.IsEndOfRun()){return 0;}
  // -surl:http://www.elsevier.com/ -rqdm:.elsevier.com -mxlevs:999
  //-cb:test -cp:. -ct:text/* -dm:www.running-fitness.com -surl:http://www.running-fitness.com -redirdm:y
  //-cb:test -cp:. -ct:text/* -dm:www.ibm.si -surl:http://www.ibm.si -redirdm:y

  // create crawler
  PCrawler Crawler=TCrawler::New();

  // prepare crawler-definition
  PCrawlerDef Def=Crawler->GetDef();
  Def->PutMxUrls(MxUrls);
  Def->PutMnConns(MnConns);
  Def->PutMxConns(MxConns);
  Def->PutMxConnsPerSrv(MxConnsPerSrv);
  Def->PutAfterFetchDelaySecs(AfterFetchDelaySecs);
  Def->PutMxLev(MxLev);
  Def->PutMxDep(MxDep);
  Def->PutMxContLen(MxContLen);
  Def->PutMnQLen(MnQLen);
  Def->PutQResetMod(QResetMod);
  Def->PutMxQSegLen(MxQSegLen);
  Def->PutMxRetries(MxRetries);
  Def->PutRevisitSecs(RevisitSecs);
  Def->PutRedirDmAllowed(RedirDmAllowedP);
  Def->AddStartUrlStrV(StartUrlStrV);
  Def->AddRqDmNmV(RqDmNmV);
  Def->AddBadDmNmV(BadDmNmV);
  Def->LoadGeoIpBs(GeoIpBsFNm);
  Def->AddRqCountryNmV(CountryNmV);
  Def->AddSiteUrlStrV(SiteUrlStrV);
  Def->LoadUrlStrV(SiteUrlStrVFNm);
  Def->AddRqContTypeNmV(RqContTypeNmV);
  Def->AddBadFExtV(BadFExtV);
  if (OptHtmlCrawlP){Def->OptHtmlCrawling();}
  GetPresetConfig(ConfigNm, Def, CrawlBsNm, CrawlBsFPath, CrawlBsFAccessNm, CrawlBsMxSegLen);

  // output settings
  printf("===Review Config===================================\n");
  printf("  Preset Configuration Name: %s\n", ConfigNm.CStr());
  printf("            Crawl Base Name: %s\n", CrawlBsNm.CStr());
  printf("            Crawl File Path: %s\n", CrawlBsFPath.CStr());
  printf("          Crawl Base Access: %s\n", CrawlBsFAccessNm.CStr());
  printf("%s", Def->GetStr().CStr());
  printf("===================================================\n\n");

  // define crawl-base
  Crawler->DefCrawlBs(CrawlBsNm, CrawlBsFPath, CrawlBsFAccessNm, CrawlBsMxSegLen);
  // start-crawling
  Crawler->StartCrawling();
  // activate web-browser
  TSysConsole::OpenFile(TStr::Fmt("http://localhost:%d/", Crawler->GetWebSrv()->GetPortN()));
  // message-loop
  TSysMsg::Loop();
  // stop-crawling
  Crawler->StopCrawling();

  return 0;
  Catch;
  return 1;
}