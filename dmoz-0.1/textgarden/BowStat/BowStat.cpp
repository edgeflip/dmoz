#include <mine.h>

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words To Semantic-Space", 1);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-File");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading bag-of-words data from '%s' ... ", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  printf("Number of documents: %d\n", BowDocBs->GetDocs());
  printf("Number of words: %d\n", BowDocBs->GetWords());

  return 0;
  Catch;
  return 1;
}