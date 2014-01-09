#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Acquis to Compact-Document", 0);
  TStr InAcquisFPath=Env.GetIfArgPrefixStr("-i:", "", "Input-Acquis-FilePath");
  TStrV AcquisLangNmV=Env.GetIfArgPrefixStrV("-l:", "Acquis-Language-Name");
  TStr OutCpdFNm=Env.GetIfArgPrefixStr("-o:", "Acquis.Cpd", "Output-CompactDocument-FileName");
  if (Env.IsEndOfRun()){return 0;}
  InAcquisFPath="f:/data/acquis";
  AcquisLangNmV.Add("en");
  OutCpdFNm="Acquis-En.Cpd";

  TAcquisBs::SaveAcquisToCpd(InAcquisFPath, AcquisLangNmV, OutCpdFNm);

  return 0;
  Catch;
  return 1;
}
