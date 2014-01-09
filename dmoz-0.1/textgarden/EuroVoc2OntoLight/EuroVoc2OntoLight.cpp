#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("EuroVoc To Ontology-Light", 0);
  TStr InEuroVocFPath=Env.GetIfArgPrefixStr("-i:", "f:/data/EuroVoc/", "Input-EuroVoc-FilePath");
  TStr OutOntoLightFNm=Env.GetIfArgPrefixStr("-o:", "f:/Data/OntoLight/EuroVoc.OntoLight", "Output-OntoLight-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "f:/Data/OntoLight/EuroVoc.OntoLight.Txt", "Output-Text-FileName");
  if (Env.IsEndOfRun()){return 0;}

  PLwOnto LwOnto=TLwOnto::LoadEuroVoc(InEuroVocFPath);

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
