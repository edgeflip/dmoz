#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Index Text-Base");
  TStr TBsFNm=Env.GetIfArgPrefixStr("-i:", "", "TextBase-File");
  bool MemStatP=Env.GetIfArgPrefixBool("-memstat:", false, "Memory-Statistics");
  if (Env.IsEndOfRun()){return 0;}

  // get text-base names
  TStr TxtBsNm=TBsFNm.GetFBase();
  TStr TxtBsFPath=TBsFNm.GetFPath();
  // create index
  TTxtBs::GenIndex(TxtBsNm, TxtBsFPath, MemStatP);

  return 0;
  Catch;
  return 1;
}

