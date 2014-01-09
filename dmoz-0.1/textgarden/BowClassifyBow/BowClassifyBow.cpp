#include "mine.h"

int main(int argc, char* argv[]){
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // get command line parameters
    Env.PrepArgs("Bag-Of-Words To Bag-Of-Word-Weights");
    TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "", "Input-BagOfWords-FileName");
    TStr InTrBowFNm=Env.GetIfArgPrefixStr("-itr:", "", "Training-BagOfWords-FileName");
    TStr InBowMdFNm=Env.GetIfArgPrefixStr("-imd:", "", "Input-BagOfWords-Model-FileName");
    TStr CatNm=Env.GetIfArgPrefixStr("-cat:", "", "Category-Name");
    TStr WgtTypeStr=Env.GetIfArgPrefixStr("-w:", "tfidf", "Weighting (none, norm, bin, tfidf)");
    TStr OutResFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-Classification-Results-FileName");
    bool OutStat=Env.GetIfArgPrefixBool("-ostat:", false, "Output-Statistics");
    if (Env.IsEndOfRun()){return 0;}

    // load bow data
    printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
    PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    PBowDocBs OrgBowDocBs=TBowDocBs::LoadBin(InTrBowFNm);
    printf(" Done.\n");
    printf("Calculating bag-of-word-weights ...");
    TBowWordWgtType WgtType = bwwtUndef;
    if (WgtTypeStr == "none") { WgtType = bwwtEq; } 
    else if (WgtTypeStr == "norm") { WgtType = bwwtNrmEq; } 
    else if (WgtTypeStr == "bin") { WgtType = bwwtBin; }
    else if (WgtTypeStr == "tfidf") { WgtType = bwwtNrmTFIDF; } 
    else { TExcept::Throw("Invalid parameter -w!", WgtTypeStr); }
    PBowDocWgtBs BowDocWgtBs = TBowDocWgtBs::New(BowDocBs, WgtType, 0, 0);
    printf(" Done.\n");

    // load bow-model
    printf("Loading bag-of-words-model from '%s' ...", InBowMdFNm.CStr());
    PBowMd BowMd=TBowMd::LoadBin(InBowMdFNm, OrgBowDocBs);
    printf(" Done.\n");

    if (OutStat) {
        TIntV DIdV; BowDocBs->GetTestDIdV(DIdV);
        if (DIdV.Empty()) { BowDocBs->GetAllDIdV(DIdV); }
        TCfyRes Results = TBowSVMMd::Test(BowMd, BowDocBs, BowDocWgtBs, DIdV, CatNm);
        Results.PrStat("Results");
    }

    if (!OutResFNm.Empty()) {
        PSOut ResSOut = TFOut::New(OutResFNm); TFltStrPrV ResV;
        TIntV DIdV; BowDocBs->GetAllDIdV(DIdV); const int Vecs = DIdV.Len();
        for (int VecN = 0; VecN < Vecs; VecN++) {
            PBowSpV DocSpV = BowDocWgtBs->GetSpV(DIdV[VecN]);
            ResV.Clr(); BowMd->GetCfy(DocSpV, ResV);
            const double PredCls = ResV.Len() > 0 ? ResV[0].Val1 : -1.0;
            ResSOut->PutStrLn(TStr::Fmt("%5.2f", PredCls));
        }
    }

    return 0;
    Catch;
    return 1;
}

