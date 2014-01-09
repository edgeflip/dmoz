#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words Hierarchical-K-Means");
  TStr InFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-File");
  TStr OutPartFNm=Env.GetIfArgPrefixStr("-op:", "HKMeans.BowPart", "Output-BowPartition-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "HKMeans.Txt", "Output-Txt-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "HKMeans.Xml", "Output-Xml-File");
  int Docs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents");
  int RndSeed=Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
  int MxDocsPerClust=Env.GetIfArgPrefixInt("-mxcdocs:", 100, "Maximal-Documents-Per-Cluster");
  int ClustTrials=Env.GetIfArgPrefixInt("-ctrials:", 1, "Clustering-Trials");
  double ConvergEps=Env.GetIfArgPrefixFlt("-ceps:", 10, "Convergence-Epsilon");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.5, "Cut-Word-Weight-Sum-Percentage");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 5, "Minimal-Word-Frequency");
  bool PropBowDocWgtBsP=Env.GetIfArgPrefixBool("-propwgt:", false, "Propagate-Weights");
  if (Env.IsEndOfRun()){return 0;}

  // load data
  if (InFNm.Empty()){
    TExcept::Throw("No Input-File specified!");}
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InFNm);

  // get doc-ids
  TIntV AllDIdV; BowDocBs->GetAllDIdV(AllDIdV);
  if (Docs!=-1){AllDIdV.Trunc(Docs);}

  // get document partition
  PBowSim BowSim=TBowSim::New(bstCos); // similarity object
  TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
  TSecTm StartTm=TSecTm::GetCurTm(); // get start-time
  PBowDocPart BowDocPart=TBowClust::GetHKMeansPart(
   TNotify::StdNotify, // log output
   BowDocBs, // document data
   BowSim, // similarity function
   TRnd(RndSeed), // random generator
   MxDocsPerClust, // max. documents per leaf cluster
   ClustTrials, // trials per k-means
   ConvergEps, // convergence epsilon for k-means
   1, // min. documents per cluster
   WordWgtType, // word weighting
   CutWordWgtSumPrc, // cut-word-weights percentage
   MnWordFq, // minimal word frequency
   AllDIdV, // training documents
   PropBowDocWgtBsP, NULL); // propagate weights, weights-base
  TSecTm EndTm=TSecTm::GetCurTm(); // get end-time
  printf("Duration: %d secs\n", TSecTm::GetDSecs(StartTm, EndTm));

  // output partition
  if (!OutPartFNm.Empty()){
    TFOut SOut(OutPartFNm); BowDocPart->Save(SOut);}
  if (!OutTxtFNm.Empty()){
    BowDocPart->SaveTxt(OutTxtFNm, BowDocBs, true, 15, 0.5, true);}
  if (!OutXmlFNm.Empty()){
    BowDocPart->SaveXml(OutXmlFNm, BowDocBs);}
 
  return 0;
  Catch;
  return 1;
}

