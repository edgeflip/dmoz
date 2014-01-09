#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("DMoz-Binary To Ontology-Light", -1);
  TStr InFPath=Env.GetIfArgPrefixStr("-i:", "f:/Data/DMoz", "Input-File-Path");
  TStr InDMozBinFBase=Env.GetIfArgPrefixStr("-ib:", TDMozInfo::BinFullFBase, "Input-DMoz-Binary-FileName");
  TStr RootCatNm=Env.GetIfArgPrefixStr("-c:", "Top", "Root-Category-Name");
  TStr OutOntoLightFNm=Env.GetIfArgPrefixStr("-o:", "f:/Data/OntoLight/DMoz.OntoLight", "Output-OntoLight-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "f:/Data/OntoLight/DMoz.OntoLight.Txt", "Output-Text-FileName");
  if (Env.IsEndOfRun()){return 0;}

  PLwOnto LwOnto=TLwOnto::LoadDMozVoc(InDMozBinFBase, InFPath);

  printf("Saving OntoLight to '%s' ...", OutOntoLightFNm.CStr());
  LwOnto->SaveBin(OutOntoLightFNm);
  printf(" Done.\n");

  printf("Saving Text to '%s' ...", OutTxtFNm.CStr());
  LwOnto->SaveTxt(OutTxtFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

