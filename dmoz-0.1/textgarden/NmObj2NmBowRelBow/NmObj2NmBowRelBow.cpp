#include "mine.h"
#include "nmobj.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Named-Objects To Name-Bow & Relation-Bow", 0);
  TStr InNmObjFNm=Env.GetIfArgPrefixStr("-ino:", "", "Input-NamedObjects-FileName");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ino:", "", "Input-BagOfWords-FileName");
  TStr OutNmBowFNm=Env.GetIfArgPrefixStr("-onbow:", "Out.Nm.Bow", "Output-Name-BagOfWords");
  TStr OutRelBowFNm=Env.GetIfArgPrefixStr("-orbow:", "Out.Rel.Bow", "Output-Relation-BagOfWords");
  TStr OutNmBowStatFNm=Env.GetIfArgPrefixStr("-onbows:", "Out.Nm.Bow.Stat", "Output-Name-BagOfWords-Statistics");
  TStr OutRelBowStatFNm=Env.GetIfArgPrefixStr("-orbows:", "Out.Rel.Bow.Stat", "Output-Relation-BagOfWords-Statistics");
  int MnNmObjFq=Env.GetIfArgPrefixInt("-mnnofq:", -1, "Minimum-NamedObjects-Frequency"); 
  int MxDocs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents"); 
  bool DumpP=Env.GetIfArgPrefixBool("-dump:", false, "Dump"); 
  if (Env.IsEndOfRun()){return 0;}

  InNmObjFNm="../Cpd2NmObj/Out.NmObj";
  InBowFNm="../Cpd2NmObj/Out.Bow";
  MxDocs=100000;
  DumpP=false;

  // loading input files
  printf("Loading Named-Objects File %s ...", InNmObjFNm.CStr());
  PNmObjBs NmObjBs=TNmObjBs::LoadBin(InNmObjFNm);
  printf(" Done.\n");
  printf("Loading Bag-Of-Words File %s ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");
  printf("Creating Bag-Of-Words-Weights ...");
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF);
  printf(" Done.\n");

  PBowDocBs NmBowDocBs=NmObjBs->GetNmBowDocBs(BowDocBs, BowDocWgtBs, MnNmObjFq);
  
  PBowDocBs RelBowDocBs=NmObjBs->GetRelBowDocBs(BowDocBs, BowDocWgtBs, MnNmObjFq);

  return 0;
  Catch;
  return 1;
}