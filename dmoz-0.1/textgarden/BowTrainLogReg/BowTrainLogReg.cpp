#include "mine.h"

int main(int argc, char* argv[]){
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // get command line parameters
    Env.PrepArgs("Bag-Of-Words To Logistic-Regression-Model", 1);
    TStr InBowFNm = Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
    TStr OutBowMdFNm = Env.GetIfArgPrefixStr("-o:", "", "Output-Logistic-Regresion-Model-FileName");
    TStr CatNm=Env.GetIfArgPrefixStr("-cat:", "", "Category-Name");
    int DIdType = Env.GetIfArgPrefixInt("-td:", 0, "Training-Documents (0 - all, 1 - train, 2 - test)");
    double Treshold = Env.GetIfArgPrefixFlt("-t:", 0.5, "Treshold");
    int Verb = Env.GetIfArgPrefixInt("-v:", 0, "Verbosity");
    double ChangeEps = Env.GetIfArgPrefixFlt("-eps:", 0.01, "Stop-Crateria");
    int MaxStep = Env.GetIfArgPrefixInt("-max_step:", 100, "Maximal-Number-of-Steps-for-CG");
    if (Env.IsEndOfRun()){return 0;}
    
    // load bow data
    printf("Loading bag-of-words data from '%s' ... ", InBowFNm.CStr());
    PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    printf(" Done.\n");
	// calculating weights
    printf("Calculating bag-of-word-weights ...");
    PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF, 0, 0);
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

    printf("Training Logistic-Regression-Model ..."); if (Verb > 0) printf("\n"); 
    PBowMd LogRegMd = CatNm.Empty() ? 
		TBowLogRegMd::New(BowDocBs, BowDocWgtBs, DIdV, Treshold, ChangeEps, MaxStep, Verb) :
		TBowLogRegMd::New(BowDocBs, BowDocWgtBs, CatNm, DIdV, Treshold, ChangeEps, MaxStep, Verb);
    LogRegMd->Save(TFOut(OutBowMdFNm));
    printf(" Done.\n");

    return 0;

    Catch;

    return 1;
}