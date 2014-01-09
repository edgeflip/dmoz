#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Asfa To Ontology-Light", 0);
  TStr InAsfaFPath=Env.GetIfArgPrefixStr("-i:", "f:/data/Asfa/", "Input-Asfa-FilePath");
  TStr OutOntoLightFNm=Env.GetIfArgPrefixStr("-o:", "f:/Data/OntoLight/Asfa.OntoLight", "Output-OntoLight-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "f:/Data/OntoLight/Asfa.OntoLight.Txt", "Output-Text-FileName");
  if (Env.IsEndOfRun()){return 0;}

  PLwOnto LwOnto=TLwOnto::LoadAsfaVoc(InAsfaFPath);

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
