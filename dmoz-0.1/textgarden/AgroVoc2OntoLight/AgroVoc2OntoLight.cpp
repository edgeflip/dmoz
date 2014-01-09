#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("AgroVoc To Ontology-Light", 0);
  TStr InAgroVocFPath=Env.GetIfArgPrefixStr("-i:", "f:/data/agrovoc/msaccess", "Input-AgroVoc-FilePath");
  TStr OutOntoLightFNm=Env.GetIfArgPrefixStr("-o:", "f:/Data/OntoLight/AgroVoc.OntoLight", "Output-OntoLight-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "f:/Data/OntoLight/AgroVoc.OntoLight.Txt", "Output-Text-FileName");
  if (Env.IsEndOfRun()){return 0;}

  PLwOnto LwOnto=TLwOnto::LoadAgroVoc(InAgroVocFPath);

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
