#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Text To Bag-Of-Words");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Bow-FileName");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-o:", "", "output-Bow-FileName");
  int OutDocs=Env.GetIfArgPrefixInt("-docs:", -1, "Number-Of-Output-Documents");
  double PrcDocs=Env.GetIfArgPrefixFlt("-prc:", -1, "Percentage-Of-Output-Documents");
  int RndSeed=Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
  if (Env.IsEndOfRun()){return 0;}

  PBowDocBs SrcBowDocBs=TBowDocBs::LoadBin(InBowFNm);

  TIntV DIdV; SrcBowDocBs->GetAllDIdV(DIdV);
  TRnd Rnd(RndSeed); DIdV.Shuffle(Rnd);
  if (OutDocs!=-1){DIdV.Trunc(OutDocs);}
  else if (PrcDocs!=-1){DIdV.Trunc(1+int(DIdV.Len()*PrcDocs));}

  PBowDocBs DstBowDocBs=SrcBowDocBs->GetSubDocSet(DIdV);
  DstBowDocBs->SaveBin(OutBowFNm);

  return 0;
  Catch;
  return 1;
}

