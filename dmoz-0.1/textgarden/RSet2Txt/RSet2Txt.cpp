#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Result-Set To Text", 0);
  TStr InRSetFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-ResultSet-FileName");
  TStr OutRSetXmlFNm=Env.GetIfArgPrefixStr("-o:", "RSet.Xml", "Output-ResultSet-Xml-FileName");
  bool MultiRSetsP=Env.GetIfArgPrefixBool("-rsets:", false, "Multiple-ResultSets");
  if (Env.IsEndOfRun()){return 0;}

  printf("Loading Result-Set from Binary-File '%s' ... ", InRSetFNm.CStr());
  PRSet RSet=TRSet::LoadBin(InRSetFNm, MultiRSetsP);
  printf("Done.\n");

  printf("Saving Result-Set to Xml-File '%s' ...", OutRSetXmlFNm.CStr());
  TRSet::SaveXml(OutRSetXmlFNm, RSet);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}
