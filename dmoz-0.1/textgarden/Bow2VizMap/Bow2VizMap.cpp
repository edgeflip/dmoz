#include <vizmap.h>

int main(int argc, char* argv[]) {
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words To Vizualization-Map", 1);
  // input-output files
  TStr BowFName = Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName (.Bow)");
  TStr SemSpaceFName = Env.GetIfArgPrefixStr("-issp:", "", "Input-Sematic-Space-FileName (.Ssp)");
  TStr BowPartFName = Env.GetIfArgPrefixStr("-ibp:", "", "Input-BagOfWords-Partition-FileName (.BowPart)");
  TStr PointsFName = Env.GetIfArgPrefixStr("-o:", "", "Output-Points-FileName (.VizMap)");
  double SemSpaceThresh = Env.GetIfArgPrefixFlt("-ssp_thresh:", 0.7, "Reduce-Space-Average-Approximation");
  int TopClustN = Env.GetIfArgPrefixInt("-bp_clusts:", 3, "Number-of-Top-Clusters-Used");
  int MaxStep = Env.GetIfArgPrefixInt("-max_step:", 10000, "Max-Number-Of-Iteration");
  int MaxTime = Env.GetIfArgPrefixInt("-max_secs:", 1000, "Max-Number-Of-Seconds");
  double MinDiff = Env.GetIfArgPrefixFlt("-min_diff:", 0.0001, "Min-Iteration-Difference");
  bool PrecalcKeyWd = Env.GetIfArgPrefixBool("-keywd:", false, "Precalculate-Keywords");
  int KeyWdN = Env.GetIfArgPrefixInt("-numkeywd:", 2000, "Number-Of-Precalculated-Keywords");
  double KeyWdR = Env.GetIfArgPrefixFlt("-radkeywd:", 0.2, "Radious-for-averaging-keywords");
  int Landscapes = Env.GetIfArgPrefixInt("-numlndscp:", 2, "Number-Of-Landscapes");
  int RlfWidth = Env.GetIfArgPrefixInt("-lndscpx:", 500, "Width-Of-Landscapes");
  int RlfHeight = Env.GetIfArgPrefixInt("-lndscpy:", 500, "Height-Of-Landscapes");
  double Sigma = Env.GetIfArgPrefixFlt("-sigma:", 0.01, "Sigma-Parameter-For-RBF-Kernel");
  double SigmaDecay = Env.GetIfArgPrefixFlt("-decay:", 0.5, "Sigma-Decreasing-Coficient");
  if (Env.IsEndOfRun()){return 0;}

  // create/load VizMap
  if (!BowFName.Empty()) {
    printf("Loading bag-of-words data from '%s' ... ", BowFName.CStr());
    PBowDocBs BowDocBs=TBowDocBs::LoadBin(BowFName);
    PBowDocWgtBs BowDocWgtBs = TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF);
    printf(" Done.\n");

    PVizMap VizMap;
    // calculate document positions
    if (!SemSpaceFName.Empty() && !BowPartFName.Empty()) {
        printf("Loading semantic-space data from '%s' ... ", SemSpaceFName.CStr());
        PSemSpace SemSpace = TSemSpace::LoadBin(SemSpaceFName);
        printf(" Done.\n");
        printf("Loading bow-partition data from '%s' ... ", BowPartFName.CStr());
        PBowDocPart BowDocPart = TBowDocPart::LoadBin(BowPartFName);
        printf(" Done.\n");
        VizMap = TVizMapFactory::ClustLsiMdsDocLndMrk(BowDocWgtBs,  
            BowDocPart, SemSpace, TopClustN, SemSpaceThresh, MaxStep, 
            MaxTime, MinDiff, TStdNotify::New());
    } else if (!SemSpaceFName.Empty()) {
        printf("Loading semantic-space data from '%s' ... ", SemSpaceFName.CStr());
        PSemSpace SemSpace = TSemSpace::LoadBin(SemSpaceFName);
        printf(" Done.\n");
        VizMap = TVizMapFactory::DocLsiMds(BowDocWgtBs, SemSpace, TVec<TFltV>(), 
            SemSpaceThresh, MaxStep, MaxTime, MinDiff, TStdNotify::New());
    } else {
        TExcept::Throw("No semantic-space provided!");
    }
    // add docuemnt metadata
    TVizMapFactory::AddDocMetadata(VizMap, BowDocBs, BowDocBs, BowDocWgtBs);
    // calculate background landscapes
    for (int LandscapeN = 0; LandscapeN < Landscapes; LandscapeN++) {
        VizMap->AddLandscape(RlfWidth, RlfHeight, Sigma, false);
        Sigma *= SigmaDecay;
    }
    // precalcualte keywords
    if (PrecalcKeyWd) { VizMap->GenKeyWds(KeyWdN, KeyWdR, 3, 1); }

    // save file
    if (PointsFName.Empty()) { PointsFName = TStr::PutFExt(BowFName, ".VizMap"); }
    VizMap->Save(TFOut(PointsFName));
  }

  return 0;
  Catch;
  return 1;
}

