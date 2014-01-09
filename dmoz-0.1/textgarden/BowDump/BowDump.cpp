#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command-line-parameters
  Env.PrepArgs("Bag-Of-Words To Dump", -1);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutDumpFNm=Env.GetIfArgPrefixStr("-o:", "BowDump.Txt", "Output-Dump-FileName");
  bool SaveWordsP=Env.GetIfArgPrefixBool("-sw:", true, "Save-Words");
  bool SaveCatsP=Env.GetIfArgPrefixBool("-sc:", true, "Save-Categories");
  bool SaveDocsP=Env.GetIfArgPrefixBool("-sd:", true, "Save-Documents");
  if (Env.IsEndOfRun()){return 0;}

  // load bow-data
  PBowDocBs BowDocBs;
  if (!InBowFNm.Empty()){
    printf("Loading data '%s' ...", InBowFNm.CStr());
    BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    printf(" Done.\n");
  }

  // output text-file
  if ((!BowDocBs.Empty())&&(!OutDumpFNm.Empty())){
    printf("Saving data to '%s' ...", OutDumpFNm.CStr());
    BowDocBs->SaveTxtStat(OutDumpFNm, SaveWordsP, SaveCatsP, SaveDocsP);
    printf(" Done.", OutDumpFNm.CStr());
  }

  return 0;
  Catch;
  return 1;
}
