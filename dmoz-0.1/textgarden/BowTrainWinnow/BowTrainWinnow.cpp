#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Bag-Of-Word-Weights");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutBowMdFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-BagOfWords-Model-FileName");
  TStr CatNm=Env.GetIfArgPrefixStr("-cat:", "", "Category-Name");
  int TopCats=Env.GetIfArgPrefixInt("-topcats:", -1, "Top-Categories");
  bool AllCatP=Env.GetIfArgPrefixBool("-allcat:", false, "All-Categories");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  // prepare output filename
  if (OutBowMdFNm.Empty()){
    OutBowMdFNm=TStr::PutFExt(InBowFNm, TBowMd::BowMdFExt);
  }

  PBowMd BowMd;
  if (AllCatP||(TopCats!=-1)){
    BowMd=TBowWinnowMd::NewMulti(BowDocBs, TopCats);
  } else {
    BowMd=TBowWinnowMd::New(BowDocBs, CatNm);
  }
  BowMd->SaveBin(OutBowMdFNm);

  return 0;
  Catch;
  return 1;
}
