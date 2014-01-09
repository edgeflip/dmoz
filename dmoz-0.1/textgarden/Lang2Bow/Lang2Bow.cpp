#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Languages-Texts To Languages-Bag-Of-Words", 1);
  TStr InLangFPath=Env.GetIfArgPrefixStr("-ilang:", "", "Input-LanguagesTexts-FilePath");
  TStr OutLangBowFNm=Env.GetIfArgPrefixStr("-obow:", "Lang.Bow", "Output-LanguageBow-FileName");
  TStr OutStatFNm=Env.GetIfArgPrefixStr("-ostat:", "Lang.Stat.Txt", "Output-LanguagesStatistics-FileName");
  if (Env.IsEndOfRun()){return 0;}


  return 0;
  Catch;
  return 1;
}
