#include "mine.h"

int main(int argc, char* argv[]){
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // get command line parameters
    Env.PrepArgs("Bag-Of-Words To Binary-SVM-Model", 1);
    TStr InBowFNm = Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
    TStr OutBowMdFNm = Env.GetIfArgPrefixStr("-o:", "", "Output-Binary-SVM-Model-FileName");
    bool OutStatP=Env.GetIfArgPrefixBool("-ostat:", false, "Output-Statistics (*Stat.Txt)");
    TStr WgtTypeStr=Env.GetIfArgPrefixStr("-w:", "tfidf", "Weighting (none, norm, bin, tfidf, given");
    TStr InWgtFNm = Env.GetIfArgPrefixStr("-iw:", "", "Input-Weighted-Bag-of-Words-FileName");
    int DIdType = Env.GetIfArgPrefixInt("-td:", 0, "Training-Documents (0 - all, 1 - train, 2 - test)");
    double c = Env.GetIfArgPrefixFlt("-c:", 1.0, "Cost-Parameter");
    double j = Env.GetIfArgPrefixFlt("-j:", 1.0, "Weight-for-Cost-Parameter-for-Relevant-Documents");
    int cacheSize = Env.GetIfArgPrefixInt("-cachesize:", 50, "Memory-Cache-Size (Mb)");
    int time = Env.GetIfArgPrefixInt("-time:", -1, "Upper-Time-Limit");
    int verb = Env.GetIfArgPrefixInt("-v:", 0, "Verbosity (0-3)");
    int subSize = Env.GetIfArgPrefixInt("-subsize:", 36, "Subproblem-Size");
    double eps_ter = Env.GetIfArgPrefixFlt("-ter:", 1e-3, "Terminating-Condition");
    bool shrink = Env.GetIfArgPrefixBool("-shrink:", true, "Shrinking");
    bool DoCrossValidation = Env.GetIfArgPrefixBool("-cv:", false, "Cross-Validation");
    int Folds = Env.GetIfArgPrefixInt("-folds:", 5, "Number-of-Folds");
    int Seed = Env.GetIfArgPrefixInt("-seed:", 1, "Seed-for-Cross-Validation");
	TStr OutCVStatFNm = Env.GetIfArgPrefixStr("-ocv:", "", "Output-Cross-Validation-Result-FileName");
    if (Env.IsEndOfRun()){return 0;}
    
    // load bow data
    printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
    PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    printf(" Done.\n");
    // calculating weights
    printf("Calculating bag-of-word-weights ...");
    TBowWordWgtType WgtType = bwwtUndef;
    if (WgtTypeStr == "none") { WgtType = bwwtEq; } 
    else if (WgtTypeStr == "norm") { WgtType = bwwtNrmEq; } 
    else if (WgtTypeStr == "bin") { WgtType = bwwtBin; }
    else if (WgtTypeStr == "tfidf") { WgtType = bwwtLogDFNrmTFIDF; } 
    else if (WgtTypeStr == "given") { /* do nothing */ }     
    else { TExcept::Throw("Invalid parameter -w!", WgtTypeStr); }
    PBowDocWgtBs BowDocWgtBs;
    if (WgtType == bwwtUndef) { BowDocWgtBs = TBowDocWgtBs::LoadBin(InWgtFNm); } 
    else { BowDocWgtBs = TBowDocWgtBs::New(BowDocBs, WgtType, 0, 0); }
    printf(" Done.\n");

    // prepare output filename
    if (OutBowMdFNm.Empty()){
        OutBowMdFNm=TStr::PutFExt(InBowFNm, TBowMd::BowMdFExt);
    }

    // prepare parameters for learning (setting up default values)
    TIntV DIdV;
    if (DIdType == 0) {
        BowDocBs->GetAllDIdV(DIdV);
    } else if (DIdType == 1) {
        BowDocBs->GetTrainDIdV(DIdV);
    } else if (DIdType == 2) {
        BowDocBs->GetTestDIdV(DIdV);
    } else {
        TExcept::Throw("Invalid parameter -td!");
    }

    if (DoCrossValidation) {
        TCfyRes CfyRes = TBowSVMMd::CrossValidMultiClsLinear(Folds, Seed, BowDocBs, BowDocWgtBs, 
            c, j, true, TSVMLearnParam::Lin(time, verb, subSize, eps_ter, shrink));    
        CfyRes.PrStat("Macro Average:");
        if (!OutCVStatFNm.Empty()) { CfyRes.PrTabStat(OutCVStatFNm); }
    } else {
        printf("Training SVM models ... "); if (verb > 0) printf("\n"); 
        PBowMd BowSVMMd = TBowSVMMd::NewMultiClsLinear(BowDocBs, BowDocWgtBs, DIdV, c, j, true, 
            TSVMLearnParam::Lin(time, verb, subSize, eps_ter, shrink), 1000);    
        printf("Saving ... ");
        BowSVMMd->SaveBin(OutBowMdFNm);
        printf("Done.\n");
    }

    return 0;
    Catch;
    return 1;
}