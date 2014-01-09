#include "tmine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words To Tile-Vizualization");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-File");
  TStr OutTileFNm=Env.GetIfArgPrefixStr("-o:", "VizTile.Xml", "Output-Tile-File");
  int Docs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents");
  int RndSeed=Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
  int MnDocsPerClust=Env.GetIfArgPrefixInt("-mncdocs:", 100, "Minimal-Documents-Per-Cluster");
  int ClustTrials=Env.GetIfArgPrefixInt("-ctrials:", 1, "Clustering-Trials");
  double ConvergEps=Env.GetIfArgPrefixFlt("-ceps:", 10, "Convergence-Epsilon");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.5, "Cut-Word-Weight-Sum-Percentage");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 5, "Minimal-Word-Frequency");
  bool PropBowDocWgtBsP=Env.GetIfArgPrefixBool("-propwgt", false, "Propagate-Weights");
  int TopWords=Env.GetIfArgPrefixInt("-topwords:", 10, "Top-Words");
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
  PBowDocPart BowDocPart=TBowClust::GetHKMeansPart(
   TNotify::StdNotify, // log output
   BowDocBs, // document data
   BowSim, // similarity function
   TRnd(RndSeed), // random generator
   MnDocsPerClust, // max. documents per leaf cluster
   ClustTrials, // trials per k-means
   ConvergEps, // convergence epsilon for k-means
   1, // min. documents per cluster
   WordWgtType, // word weighting
   CutWordWgtSumPrc, // cut-word-weights percentage
   MnWordFq, // minimal word frequency
   AllDIdV, // training documents
   PropBowDocWgtBsP, NULL); // propagate weights, weights-base

  // get area-partition
  TBowDocPart::TClustRectPrV ClustRectPrV;
  BowDocPart->GetAreaPart(TFltRect(0, 0, 1, 1), ClustRectPrV);

  // create & save tiling-xml-document
  PXmlTok TileXmlTok=TXmlTok::New("TileViz");
  for (int ClustRectPrN=0; ClustRectPrN<ClustRectPrV.Len(); ClustRectPrN++){
    PBowDocPartClust Clust=ClustRectPrV[ClustRectPrN].Val1;
    TFltRect VRect=ClustRectPrV[ClustRectPrN].Val2;
    if (!Clust->IsSubPart()){
      // get best words string
      TStrFltPrV WordStrWgtPrV;
      Clust->GetTopWordStrWgtPrV(BowDocBs, TopWords, 0.5, WordStrWgtPrV);
      TChA BestWordVChA;
      for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
        BestWordVChA+=WordStrWgtPrV[WordN].Val1;
        //BestWordVChA+=TFlt::GetStr(WordStrWgtPrV[WordN].Val2, " (%.2f)");
        BestWordVChA+="\n";
      }
      TStr TxtStr=BestWordVChA;
      // create tile rectangle
      PXmlTok RectXmlTok=TXmlTok::New("Rect");
      RectXmlTok->AddArg("MnX", VRect.MnX);
      RectXmlTok->AddArg("MnY", VRect.MnY);
      RectXmlTok->AddArg("MxX", VRect.MxX);
      RectXmlTok->AddArg("MxY", VRect.MxY);
      RectXmlTok->AddArg("Text", TxtStr);
      // add tile rectangle
      TileXmlTok->AddSubTok(RectXmlTok);
    }
  }
  // create xml-document
  PXmlDoc TileXmlDoc=TXmlDoc::New(TileXmlTok);
  // save xml-document
  TileXmlDoc->SaveTxt(OutTileFNm);

  return 0;
  Catch;
  return 1;
}

