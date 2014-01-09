#include "google.h"
#include "nmobj.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Google-Result-Set To Named-Objects");
  TStr InRSetBinFNm=Env.GetIfArgPrefixStr("-ib:", "Google.RSet", "Input-Google-ResultSet-Binary-File");
  TStr OutNmObjFNm=Env.GetIfArgPrefixStr("-o:", "Google.NmObj", "Output-NamedObjects-File");
  if (Env.IsEndOfRun()){return 0;}

  // loading result-set
  PRSet RSet=TRSet::LoadBin(InRSetBinFNm);
  const TStrQuV& UrlTitleSrcCtxQuV=RSet->GetUrlTitleSrcCtxQuV();
  PNmObjBs NmObjBs=TNmObjBs::GetFromStrQuV(UrlTitleSrcCtxQuV);
  NmObjBs->SaveBin(OutNmObjFNm);
  NmObjBs->SaveTxtNmObj(
   "NmObjFq.Txt", "NmObjSw.Txt", "NmObjAbc.Txt", "NmObjDoc.Txt");

  return 0;
  Catch;
  return 1;
}

