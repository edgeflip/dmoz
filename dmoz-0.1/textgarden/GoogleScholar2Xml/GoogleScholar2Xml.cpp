#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Google-Scholar To XML", 0);
  TStr GgSchBsFNm=Env.GetIfArgPrefixStr("-i:", "Scholar.GgSch", "Input-Scholar-Base-FileName");
  TStr GgSchBsXmlFNm=Env.GetIfArgPrefixStr("-o:", "Scholar.GgSch.Xml", "Output-Scholar-Base-Xml-FileName");
  if (Env.IsEndOfRun()){return 0;}

  printf("Loading from '%s' ...", GgSchBsFNm.CStr());
  PGgSchBs GgSchBs=TGgSchBs::LoadBin(GgSchBsFNm);
  printf(" Done.\n");

  printf("Saving to '%s' ...", GgSchBsXmlFNm.CStr());
  GgSchBs->SaveXml(GgSchBsXmlFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

