#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Google-Scholar Crawling", 0);
  int NewCrawlP=Env.GetIfArgPrefixBool("-new:", false, "Create-New-File");
  TStr GgSchBsFNm=Env.GetIfArgPrefixStr("-f:", "Scholar.GgSch", "Scholar-Base-FileName");
  TStr SeedAuthNm=Env.GetIfArgPrefixStr("-sa:", "m grobelnik", "Seed-Author-Name");
  int DelaySecs=Env.GetIfArgPrefixInt("-ds:", 0, "Delay-Between-Queries-(Seconds)");
  if (Env.IsEndOfRun()){return 0;}

  // load or create crawl
  PGgSchBs GgSchBs; TStr AuthNm;
  if ((!NewCrawlP)&&(TFile::Exists(GgSchBsFNm))){
    printf("Continue crawling from '%s'.\n", GgSchBsFNm.CStr());
    printf("Loading '%s' ...", GgSchBsFNm.CStr());
    GgSchBs=TGgSchBs::LoadBin(GgSchBsFNm);
    printf(" Done.\n");
    AuthNm=GgSchBs->GetAuthNmToCrawl();
  } else {
    printf("New crawl (will be saved into '%s').\n", GgSchBsFNm.CStr());
    GgSchBs=TGgSchBs::New();
    AuthNm=SeedAuthNm.GetLc();
  }
  TRnd Rnd;
  forever {
    // get author hits
    printf("[%s]", AuthNm.CStr());
    PGgSchRSet SchRSet=TGg::ScholarAuthorSearch(AuthNm);
    printf("(%d)", SchRSet->GetHits());
    SchRSet->SaveXml("Scholar.RSet.Xml");
    GgSchBs->SetAuthCrawled(AuthNm);
    GgSchBs->AddRSet(SchRSet);
    // save crawl
    GgSchBs->SaveBin(GgSchBsFNm);
    // select new author
    AuthNm=GgSchBs->GetAuthNmToCrawl();
    if (AuthNm.Empty()){break;}
    // wait
    int WaitMSecs=int(DelaySecs*1000*(1+(Rnd.GetUniDev()*0.5)-0.25));
    printf(" [%ds", WaitMSecs/1000);
    TSysProc::Sleep(WaitMSecs);
    printf("] ", WaitMSecs);
  }

  return 0;
  Catch;
  return 1;
}

