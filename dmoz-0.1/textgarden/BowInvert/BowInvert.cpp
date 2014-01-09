#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Inverted Bag-Of-Words");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-Inverted-BagOfWords-FileName");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  // invert bag-of-words
  printf("Inverting ...", OutBowFNm.CStr());
  PBowDocBs InvBowDocBs=BowDocBs->GetInvDocBs();
  printf(" Done.\n");

  // save bow data
  if (OutBowFNm.Empty()){
    OutBowFNm=InBowFNm.GetFPath()+InBowFNm.GetFMid()+"Inv"+InBowFNm.GetFExt();
    TStr::PutFExtIfEmpty(OutBowFNm, ".Bow");
  }
  printf("Saving bag-of-word data to '%s' ...", OutBowFNm.CStr());
  InvBowDocBs->SaveBin(OutBowFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

