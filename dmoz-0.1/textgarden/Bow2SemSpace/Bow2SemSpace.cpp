#include "mine.h"

int main(int argc, char* argv[]){
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // command line parameters
    Env.PrepArgs("Bag-Of-Words To Semantic-Space", 1);
    TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "", "Input-BagOfWords-File");
    TStr InBowPartFNm=Env.GetIfArgPrefixStr("-ibp:", "", "Input-BagOfWords-Partition-File");
    TStr OutBinFNm=Env.GetIfArgPrefixStr("-ob:", "", "Output-SemanticSpace-Binary-File");
    TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "", "Output-SemanticSpace-Text-File");
    TStr SemSpaceType=Env.GetIfArgPrefixStr("-t:", "lsi", "Semantic-Space-Type (lsi, lsif, pca)");
    int SpaceDims=Env.GetIfArgPrefixInt("-dims:", 50, "Number-Of-Space-Dimensions");
    TStr OrtoTypeStr=Env.GetIfArgPrefixStr("-reorto:", "full", "Reortogonalization (none, selective, full)");
    int TopWords=Env.GetIfArgPrefixInt("-topwords:", 25, "Top-Words");
    double TopWordsWgtPrc=Env.GetIfArgPrefixFlt("-topwwp:", 0.5, "Top-Words-Weights-Percent");
    bool ApproxStat=Env.GetIfArgPrefixBool("-ostat:", false, "Generate-Approximation-Statistics");
    if (Env.IsEndOfRun()){return 0;}

    TVec<PBowSpV> DocSpV;
    PBowDocBs BowDocBs; PBowDocWgtBs BowDocWgtBs;
    if (!InBowFNm.Empty()) {
      // load bow data
      printf("Loading bag-of-words data from '%s' ... ", InBowFNm.CStr());
      BowDocBs=TBowDocBs::LoadBin(InBowFNm);
      printf(" Done.\n");
      // calculating weights
      printf("Calculating bag-of-word-weights ...");
      PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF, 0, 0);
      printf(" Done.\n");
      for (int DIdN = 0; DIdN < BowDocWgtBs->GetDocs(); DIdN++) {
        DocSpV.Add(BowDocWgtBs->GetSpV(BowDocWgtBs->GetDId(DIdN)));
      }
    } else if (!InBowPartFNm.Empty()) {
      printf("Loading bag-of-words-partition data from '%s' ... ", InBowPartFNm.CStr());
      PBowDocPart BowDocPart=TBowDocPart::LoadBin(InBowPartFNm);
      printf(" Done.\n");
      for (int ClustN = 0; ClustN < BowDocPart->GetClusts(); ClustN++) {
        DocSpV.Add(BowDocPart->GetClust(ClustN)->GetConceptSpV());
      }
    } else {
        TExcept::Throw("No specified input file!");
    }


    // calcualte semantic-space
    SpaceDims = TInt::GetMn(SpaceDims, DocSpV.Len());
    PSemSpace SemSpace;
    if (SemSpaceType=="lsi"){
        // Load type of ortogonalization
        TSpSVDReOrtoType OrtoType;
        if (OrtoTypeStr == "none") { OrtoType = ssotNoOrto; }
        else if (OrtoTypeStr == "selective") { OrtoType = ssotSelective; }
        else if (OrtoTypeStr == "full") { OrtoType = ssotFull; }
        else { TExcept::Throw("Invalid parameter -t", OrtoTypeStr); }

        SemSpace=TSemSpaceAlg::CalcSparseLSI(DocSpV, SpaceDims, 3*SpaceDims, OrtoType);
    } else if (SemSpaceType=="lsif"){
        SemSpace=TSemSpaceAlg::CalcFullLSI(DocSpV, SpaceDims);
    } else if (SemSpaceType=="pca"){
        SemSpace=TSemSpaceAlg::CalcKPCA(DocSpV);
    } else {
        TExcept::Throw("Invalid parameter -t", SemSpaceType);
    }

    // saving result-set
    if (!OutBinFNm.Empty()){
        SemSpace->SaveBin(OutBinFNm);}
    if (!InBowFNm.Empty() && !OutTxtFNm.Empty()){
        SemSpace->SaveTxt(OutTxtFNm, BowDocBs, TopWords, TopWordsWgtPrc);}
    //if (ApproxStat){
    //    SemSpace->SaveApporxStat(TStr::PutFExt(OutBinFNm, ".ApproxStat.txt"), DocSpV, 5);}

    return 0;
    Catch;
    return 1;
}


