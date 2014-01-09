#include "tmine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Text-Base Dump");
  TStr InTBsFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-TextBase-FileName");
  TStr OutDmpFNm=Env.GetIfArgPrefixStr("-o:", "TxtBs.Dmp", "Output-Dump-FileName");
  if (Env.IsEndOfRun()){return 0;}

  // load text-base
  TStr TxtBsNm=InTBsFNm.GetFBase();
  TStr TxtBsFPath=InTBsFNm.GetFPath();
  printf("Loading Text-Base '%s' at '%s' ...", TxtBsNm.CStr(), TxtBsFPath.CStr());
  PTxtBs TxtBs=TTxtBs::New(TxtBsNm, TxtBsFPath, faRdOnly);
  printf(" Done.\n");

  // dump text-base
  printf("Dumping to '%s' ...", OutDmpFNm.CStr());
  TxtBs->SaveTxt(OutDmpFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

