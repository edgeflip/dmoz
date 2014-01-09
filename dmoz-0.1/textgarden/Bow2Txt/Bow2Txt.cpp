#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Text", -1);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutLnDocFNm=Env.GetIfArgPrefixStr("-olndoc:", "", "Output-LineDocuments-FileName");
  TStr WgtTypeStr=Env.GetIfArgPrefixStr("-w:", "tfidf", "Weighting (none, norm, bin, tfidf");
  TStr OutSparseMLFNm=Env.GetIfArgPrefixStr("-oml:", "", "Output-Matlab-TermDocumentMatrix-FileName");
  TStr OutSparseCatMLFNm=Env.GetIfArgPrefixStr("-omlcat:", "", "Output-Matlab-CategoryDocumentMatrix-FileName");
  TStr OutStatFNm=Env.GetIfArgPrefixStr("-ostat:", "", "Output-Statistics-FileName");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  PBowDocBs BowDocBs;
  if (!InBowFNm.Empty()){
    printf("Loading data '%s' ...", InBowFNm.CStr());
    BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    printf(" Done.\n");
  }

  // output line-documets
  if ((!BowDocBs.Empty())&&(!OutLnDocFNm.Empty())){
    printf("Saving Line-Documents to '%s' ...", OutLnDocFNm.CStr());
    TBowFl::SaveLnDocTxt(BowDocBs, OutLnDocFNm);
    printf(" Done.\n");
  }

  // output sparse-matlab
  if ((!BowDocBs.Empty())&&(!OutSparseMLFNm.Empty())){
    printf("Calculating bag-of-word-weights ...");
    TBowWordWgtType WgtType;
    if (WgtTypeStr == "none") { WgtType = bwwtEq; } 
    else if (WgtTypeStr == "norm") { WgtType = bwwtNrmEq; } 
    else if (WgtTypeStr == "bin") { WgtType = bwwtBin; }
    else if (WgtTypeStr == "tfidf") { WgtType = bwwtNrmTFIDF; } 
    else { TExcept::Throw("Invalid parameter -w!", WgtTypeStr); }
    PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, WgtType);
    printf(" Done.\n");
    printf("Saving Sparse-Matlab to '%s' ...", OutSparseMLFNm.CStr());
    TIntV TrainDIdV; BowDocBs->GetTrainDIdV(TrainDIdV);
    TBowFl::SaveSparseMatlabTxt(BowDocBs, BowDocWgtBs, 
        OutSparseMLFNm, OutSparseCatMLFNm, TrainDIdV);
    printf(" Done.\n");
  }

  // output statistics
  if ((!BowDocBs.Empty())&&(!OutStatFNm.Empty())){
    printf("Saving Statistics to '%s' ...", OutStatFNm.CStr());
    BowDocBs->SaveTxtStat(OutStatFNm, true, true, true);
    printf(" Done.\n");
  }

  return 0;
  Catch;
  return 1;
}

