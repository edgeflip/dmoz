#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("DMoz-RDF to DMoz-Binary");
  TStr InFPath=Env.GetIfArgPrefixStr("-i:", "", "Input-File-Path");
  TStr OutFPath=Env.GetIfArgPrefixStr("-o:", "", "Output-File-Path");
  bool SructOnlyP=Env.GetIfArgPrefixBool("-struct:", false, "Structure-Only");
  int MemPoolLen=Env.GetIfArgPrefixInt("-m:", 1000000000, "Output-File-Path");
  if (Env.IsEndOfRun()){return 0;}

  // create DMoz-Base
  PDMozBs DMozBs; TStr OutFBase;
  if (SructOnlyP){
    // generate structure only
    DMozBs=TDMozBs::LoadTxt(InFPath, false, false);
    OutFBase=TDMozInfo::BinStructFBase;
  } else {
    // generate structure+contents
    DMozBs=TDMozBs::LoadTxt(InFPath, true, false, MemPoolLen);
    OutFBase=TDMozInfo::BinFullFBase;
  }

  // save DMoz-Base
  printf("Saving %s at %s ...", OutFBase.CStr(), OutFPath.CStr());
  DMozBs->SaveBin(OutFBase, OutFPath);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

