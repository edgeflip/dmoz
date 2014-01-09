#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Pruned Bag-Of-Words");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-Pruned-BagOfWords-FileName");
  int RndSeed=Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
  int Docs=Env.GetIfArgPrefixInt("-dnum:", -1, "Documents-Number");
  int DocsPrc=Env.GetIfArgPrefixInt("-dprc:", 1, "Documents-Percent");
  double MnWordFqPrc=Env.GetIfArgPrefixFlt("-mnwprc:", 0, "Minimal-Word-Percent");
  double MxWordFqPrc=Env.GetIfArgPrefixFlt("-mxwprc:", 1, "Maximal-Word-Percent");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 0, "Minimal-Word-Frequency");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  // prune bow data
  if (Docs!=-1){
    printf("Sampling documents by absolute number (%d) ...", Docs);
    TRnd Rnd(RndSeed);
    TIntV DIdV; BowDocBs->GetAbsSampleDIdV(Docs, Rnd, DIdV);
    BowDocBs=BowDocBs->GetSubDocSet(DIdV);
    printf(" Done.\n");
  }
  if (DocsPrc!=1){
    printf("Sampling documents by percentage (%g) ...", DocsPrc);
    TRnd Rnd(RndSeed);
    TIntV DIdV; BowDocBs->GetRelSampleDIdV(DocsPrc, Rnd, DIdV);
    BowDocBs=BowDocBs->GetSubDocSet(DIdV);
    printf(" Done.\n");
  }
  if ((MnWordFqPrc>0)||(MxWordFqPrc<1)){
    printf("Pruning words by relative frequency (%g, %g) ...", MnWordFqPrc, MxWordFqPrc);
    BowDocBs=BowDocBs->GetLimWordRelFqDocBs(MnWordFqPrc, MxWordFqPrc);
    printf(" Done.\n");
  }
  if (MnWordFq>0){
    printf("Pruning words by absolute frequency (%d) ...", MnWordFq);
    BowDocBs=BowDocBs->GetLimWordAbsFqDocBs(MnWordFq);
    printf(" Done.\n");
  }

  // save bow data
  if (OutBowFNm.Empty()){
    OutBowFNm=InBowFNm.GetFPath()+InBowFNm.GetFMid()+"Pruned"+InBowFNm.GetFExt();
    TStr::PutFExtIfEmpty(OutBowFNm, ".Bow");
  }
  printf("Saving bag-of-word data to '%s' ...", OutBowFNm.CStr());
  BowDocBs->SaveBin(OutBowFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

