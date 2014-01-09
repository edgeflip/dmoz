#include "mine.h"
#include "graph.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words To Graph-Vizualization");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-File");
  TStr OutGraphFNm=Env.GetIfArgPrefixStr("-o:", "VizGraph.Xml", "Output-Graph-File");
  int Docs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents");
  int Clusts=Env.GetIfArgPrefixInt("-clusts:", 10, "Clusters");
  int RndSeed=Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
  int ClustTrials=Env.GetIfArgPrefixInt("-ctrials:", 1, "Clustering-Trials");
  double ConvergEps=Env.GetIfArgPrefixFlt("-ceps:", 10, "Convergence-Epsilon");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.5, "Cut-Word-Weight-Sum-Percentage");
  double ClustSimSumPrc=Env.GetIfArgPrefixFlt("-cssp:", 0.3, "Cluster-Similarity-Sum-Percent-Treshold");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 5, "Minimal-Word-Frequency");
  if (Env.IsEndOfRun()){return 0;}

  // load data
  if (InBowFNm.Empty()){
    TExcept::Throw("No Input-File specified!");}
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

  // create graph
  PGraph Graph=TGGraph::New();

  // create vertices
  TVrtxV VrtxV;
  for (int ClustN=0; ClustN<BowDocPart->GetClusts(); ClustN++){
    // get cluster
    PBowDocPartClust Clust=BowDocPart->GetClust(ClustN);
    // get best words string
    TStrFltPrV WordStrWgtPrV;
    Clust->GetTopWordStrWgtPrV(BowDocBs, 7, 0.5, WordStrWgtPrV);
    TChA BestWordVChA;
    for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
      BestWordVChA+=WordStrWgtPrV[WordN].Val1;
      //BestWordVChA+=TFlt::GetStr(WordStrWgtPrV[WordN].Val2, " (%.2f)");
      BestWordVChA+="\n";
    }
    // create vertex
    TStr ClustNm=BestWordVChA;
    PVrtx Vrtx=new TGVrtx(ClustNm);
    Graph->AddVrtx(Vrtx);
    VrtxV.Add(Vrtx);
  }

  // create edges
  TFltIntIntTrV ClustSimN1N2TrV;
  BowDocPart->GetTopClustSimV(ClustSimSumPrc, ClustSimN1N2TrV);
  for (int ClustSimN=0; ClustSimN<ClustSimN1N2TrV.Len(); ClustSimN++){
    double Sim=ClustSimN1N2TrV[ClustSimN].Val1;
    int ClustN1=ClustSimN1N2TrV[ClustSimN].Val2;
    int ClustN2=ClustSimN1N2TrV[ClustSimN].Val3;
    TStr EdgeNm=TFlt::GetStr(Sim, "%.3f");
    PEdge Edge=TGEdge::New(VrtxV[ClustN1], VrtxV[ClustN2], EdgeNm, false);
    Graph->AddEdge(Edge);
    Edge->PutWgt(TMath::Sqr(Sim));
  }

  // place graph
  Graph->PlaceSimAnnXY(TRnd(RndSeed));

  // save graph
  Graph->SaveXml(OutGraphFNm);

  return 0;
  Catch;
  return 1;
}

