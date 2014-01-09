#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words K-Means");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Bow-File");
  TStr OutPartFNm=Env.GetIfArgPrefixStr("-op:", "KMeans.BowPart", "Output-BowPartition-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "KMeans.Txt", "Output-Txt-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "KMeans.Xml", "Output-Xml-File");
  int Docs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents");
  int Clusts=Env.GetIfArgPrefixInt("-clusts:", 10, "Clusters");
  int RndSeed=Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
  int ClustTrials=Env.GetIfArgPrefixInt("-ctrials:", 1, "Clustering-Trials");
  double ConvergEps=Env.GetIfArgPrefixFlt("-ceps:", 10, "Convergence-Epsilon");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.5, "Cut-Word-Weight-Sum-Percentage");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 5, "Minimal-Word-Frequency");
  bool SaveDocNmP=Env.GetIfArgPrefixBool("-sdnm:", false, "Save-Document-Names");
  if (Env.IsEndOfRun()){return 0;}

  // load data
  if (InBowFNm.Empty()){
    TExcept::Throw("No Input-Bow-File specified!");}
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);

  // get doc-ids
  TIntV AllDIdV; BowDocBs->GetAllDIdV(AllDIdV);
  if (Docs!=-1){AllDIdV.Trunc(Docs);}

  // get document partition
  PBowSim BowSim=TBowSim::New(bstCos); // similarity object
  TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
  TSecTm StartTm=TSecTm::GetCurTm(); // get start-time
  PBowDocPart BowDocPart=TBowClust::GetKMeansPart(
   TNotify::StdNotify, // log output
   BowDocBs, // document data
   BowSim, // similarity function
   TRnd(RndSeed), // random generator
   Clusts, // number of clusters
   ClustTrials, // trials per k-means
   ConvergEps, // convergence epsilon for k-means
   1, // min. documents per cluster
   WordWgtType, // word weighting
   CutWordWgtSumPrc, // cut-word-weights percentage
   MnWordFq, // minimal word frequency
   AllDIdV); // training documents
  TSecTm EndTm=TSecTm::GetCurTm(); // get end-time
  printf("Duration: %d secs\n", TSecTm::GetDSecs(StartTm, EndTm));

  // output partition
  if (!OutPartFNm.Empty()){
    TFOut SOut(OutPartFNm); BowDocPart->Save(SOut);}
  if (!OutTxtFNm.Empty()){
    BowDocPart->SaveTxt(OutTxtFNm, BowDocBs, true, 15, 0.5, SaveDocNmP);}
  if (!OutXmlFNm.Empty()){
    BowDocPart->SaveXml(OutXmlFNm, BowDocBs);}

  return 0;
  Catch;
  return 1;
}

