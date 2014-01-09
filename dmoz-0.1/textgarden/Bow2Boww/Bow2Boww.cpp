#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Bag-Of-Word-Weights using precalculated weights");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutBowwFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-BagOfWordWeights-FileName");
  TStr Type=Env.GetIfArgPrefixStr("-type:", "", "Method-Type (load, svm)");
  TStr InWgtFNm=Env.GetIfArgPrefixStr("-iwgt:", "", "Input-Matlab-WordWeights-FileName");
  double SvmC=Env.GetIfArgPrefixFlt("-svmcost:", 1.0, "Svm-Cost-Parameter");
  int SvmTime=Env.GetIfArgPrefixInt("-svmtime:", 60, "Max-Time-per-Model (in seconds)");
  bool PutUntiNorm=Env.GetIfArgPrefixBool("-unitnorm:", false, "Normalize-Document-Vectors");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.0, "Cut-Word-Weight-Sum-Percentage");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 0, "Minimal-Word-Frequency");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  PBowDocWgtBs BowDocWgtBs;
  if (Type == "load") {
      // loading word weights
      printf("Loading word-weights data from '%s' ...", InWgtFNm.CStr());
      TVec<TFltV> WordWgtVV; 
      Fail; //TLAMisc::LoadTFltVV(InWgtFNm, WordWgtVV);
      IAssert(WordWgtVV.Len() == 1);
      printf(" Done.\n");

      TFltV& WordWgtV = WordWgtVV[0];
      for (int WgtN = 0; WgtN < WordWgtV.Len(); WgtN++) {
          if (WordWgtV[WgtN] > 0.0) {
              WordWgtV[WgtN] = sqrt(WordWgtV[WgtN]);
          }
      }

      // calculate boww data
      printf("Calculating bag-of-word-weights data ...");
      BowDocWgtBs = TBowDocWgtBs::NewPreCalcWgt(BowDocBs, 
          WordWgtV, PutUntiNorm, CutWordWgtSumPrc, MnWordFq);
      printf(" Done.\n"); 
  } else if (Type == "svm") {
      printf("Calculating bag-of-word-weights data ... \n");
      PBowDocWgtBs TfidfWgtBs = TBowDocWgtBs::New(BowDocBs, 
          bwwtLogDFNrmTFIDF, CutWordWgtSumPrc, MnWordFq);
      BowDocWgtBs = TBowDocWgtBs::NewSvmWgt(BowDocBs, TfidfWgtBs, 
          TIntV(), SvmC, SvmTime, false, TIntV(), PutUntiNorm, 
          CutWordWgtSumPrc, MnWordFq);
      printf("Done.\n"); 

  } else {
      printf("Wrong method type!\n");
  }

  // save boww data
  if (!OutBowwFNm.Empty()){
    TStr::PutFExtIfEmpty(OutBowwFNm, ".Boww");
    printf("Saving bag-of-word-weights data to '%s' ...", OutBowwFNm.CStr());
    BowDocWgtBs->SaveBin(OutBowwFNm);
    BowDocWgtBs->SaveTxtStat(OutBowwFNm + ".txt", BowDocBs, true, true, true);
    printf(" Done.\n");
  }

  return 0;
  Catch;
  return 1;
}
