#include "wikipedia.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Wikipedia-Xml to Wikipedia-Binary", 0);
  TStr InXmlFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Xml-FileName");
  TStr OutBinFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-BinFileName");
  if (Env.IsEndOfRun()){return 0;}
  InXmlFNm="f:/data/wikipedia/slwiki-20061208-pages-articles.xml";
  OutBinFNm="slwiki.wikibs";

  // create Wiki-Base
  PWikiBs WikiBs=TWikiBs::LoadXml(InXmlFNm);

  // save Wiki-Base
  printf("Saving to %s ...", OutBinFNm.CStr());
  WikiBs->SaveBin(OutBinFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}
