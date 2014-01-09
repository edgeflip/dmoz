#include "mine.h"

int main(int argc, char* argv[]){
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // get command line parameters
    Env.PrepArgs("Bag-Of-Words To One-Class-SVM-Model", 1);
    TStr InBowFNm = Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
    TStr OutBowMdFNm = Env.GetIfArgPrefixStr("-o:", "", "Output-One-Class-SVM-Model-FileName");
    TStr CatNm=Env.GetIfArgPrefixStr("-cat:", "", "Category-Name");
    TStr WgtTypeStr=Env.GetIfArgPrefixStr("-w:", "tfidf", "Weighting (none, norm, bin, tfidf, given");
    TStr InWgtFNm = Env.GetIfArgPrefixStr("-iw:", "", "Input-Weighted-Bag-of-Words-FileName");
    int DIdType = Env.GetIfArgPrefixInt("-td:", 0, "Training-Documents (0 - all, 1 - train, 2 - test)");
    double nu = Env.GetIfArgPrefixFlt("-nu:", 0.1, "Nu-Parameter");
    TStr kernelType = Env.GetIfArgPrefixStr("-t:", "linear", "Kernel-Type (linear, polynomial, radial, sigmoid)");
    double ker_p = Env.GetIfArgPrefixFlt("-ker_p:", 3.0, "Degree-of-Polynomail-Kernel");
    double ker_s = Env.GetIfArgPrefixFlt("-ker_s:", 1.0, "Linear-Part-in-Polynomial-Kernel");
    double ker_c = Env.GetIfArgPrefixFlt("-ker_c:", 1.0, "Constant-Part-in-Polynomail-Kernel");
    double ker_gamma = Env.GetIfArgPrefixFlt("-ker_gamma:", 1.0, "Gamma-for-Radial-Kernel");
    int cacheSize = Env.GetIfArgPrefixInt("-cachesize:", 50, "Memory-Cache-Size");
    int time = Env.GetIfArgPrefixInt("-time:", -1, "Upper-Time-Limit");
    int verb = Env.GetIfArgPrefixInt("-v:", 0, "Verbosity");
    int subSize = Env.GetIfArgPrefixInt("-subsize:", -1, "Subproblem-Size");
    double eps_ter = Env.GetIfArgPrefixFlt("-ter:", 1e-3, "Terminating-Condition");
    bool shrink = Env.GetIfArgPrefixBool("-shrink:", true, "Shrinking");
    bool DoCrossValidation = Env.GetIfArgPrefixBool("-cv:", false, "Cross-Validation");
    int Folds = Env.GetIfArgPrefixInt("-folds:", 5, "Number-of-Folds");
    int Seed = Env.GetIfArgPrefixInt("-seed:", 1, "Seed-for-Cross-Validation");
	TStr OutCVStatFNm = Env.GetIfArgPrefixStr("-ocv:", "", "Output-Cross-Validation-Result-FileName");
    if (Env.IsEndOfRun()){return 0;}
    
    // load bow data
    printf("Loading bag-of-words data from '%s' ... ", InBowFNm.CStr());
    PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    printf(" Done.\n");
	// calculating weights
    printf("Calculating bag-of-word-weights ...");
    TBowWordWgtType WgtType = bwwtUndef;
    if (WgtTypeStr == "none") { WgtType = bwwtEq; } 
    else if (WgtTypeStr == "norm") { WgtType = bwwtNrmEq; } 
    else if (WgtTypeStr == "bin") { WgtType = bwwtBin; }
    else if (WgtTypeStr == "tfidf") { WgtType = bwwtNrmTFIDF; } 
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
    if (subSize == -1) subSize = (kernelType == "linear") ? 36 : 10;
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

    printf("Training one-class-SVM-model ... "); if (verb > 0) printf("\n"); 
    PBowMd OneClassSVMMd;
    if (kernelType == "linear") {
        if (!DoCrossValidation) {
            OneClassSVMMd = TBowSVMMd::NewOneClassLinear(BowDocBs, BowDocWgtBs, 
                CatNm, DIdV, nu, TSVMLearnParam::Lin(time, verb, subSize, eps_ter, shrink));
        } else {
            TCfyRes Results  = TBowSVMMd::CrossValidOneClassLinear(Folds, Seed, 
                BowDocBs, BowDocWgtBs, CatNm, DIdV, nu, TSVMLearnParam::Lin(
                time, verb, subSize, eps_ter, shrink));
            Results.PrStat("Average");
            if (!OutCVStatFNm.Empty()) { Results.PrTabStat(OutCVStatFNm); }
        }
    } else {
        PKernel ker;
		if (kernelType == "polynomial") {
            if (ker_p <= 0.0) TExcept::Throw("Error: ker_p must be > 0\n");
            if (ker_s <= 0.0) TExcept::Throw("Error: ker_s must be > 0\n");
            ker = TPolynomialKernel::New(ker_p, ker_s, ker_c);
		} else
		if (kernelType == "radial") {
            if (ker_gamma <= 0.0) TExcept::Throw("Error: ker_gamma must be > 0\n");
            ker = TRadialKernel::New(ker_gamma); 
		} else
		if (kernelType == "sigmoid") {
            if (ker_p == 0.0) TExcept::Throw("Error: ker_p must be != 0\n");
            ker = TSigmoidKernel::New(ker_s, ker_c);
		} else {
            TExcept::Throw("Error: wrong SVM-Kernel-Type!", kernelType);
        }
        if (!DoCrossValidation) {
            OneClassSVMMd = TBowSVMMd::NewOneClass(ker, BowDocBs, 
                BowDocWgtBs, CatNm, DIdV, nu, TSVMLearnParam::NonLin(
                time, cacheSize, verb, subSize, eps_ter, shrink));
        } else {
            TCfyRes Results = TBowSVMMd::CrossValidOneClass(Folds, Seed, 
                ker, BowDocBs, BowDocWgtBs, CatNm, DIdV, nu, TSVMLearnParam::NonLin(
                time, cacheSize, verb, subSize, eps_ter, shrink));
            Results.PrStat("Average");
            if (!OutCVStatFNm.Empty()) { Results.PrTabStat(OutCVStatFNm); }
        }
    }

    // save model
    if (!OneClassSVMMd.Empty()) {
        OneClassSVMMd->SaveBin(OutBowMdFNm);
    }
    printf(" Done.\n");

    return 0;

    Catch;

    return 1;
}