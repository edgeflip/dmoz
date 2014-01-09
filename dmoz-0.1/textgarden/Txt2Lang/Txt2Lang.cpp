#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Text To Language", 1);
  TStr InHtmlFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Html-FileName");
  TStr InLangBowFNm=Env.GetIfArgPrefixStr("-ilang:", "Lang.Bow", "Input-Language-Bow-FileName");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-oxml:", "Lang.Xml", "Output-Language-Xml-File");
  if (Env.IsEndOfRun()){return 0;}

  return 0;
  Catch;
  return 1;
}
