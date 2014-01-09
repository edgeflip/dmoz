#include "mine.h"
#include "mkcca.h"

int main(int argc, char* argv[]){
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);
    // command line parameters
    Env.PrepArgs("Training Multiview Multicore KCCA");
    TStrV InBowFNmV = Env.GetIfArgPrefixStrV("-ibow:", TStrV(), "Input-BagOfWords-FileName");
    int Cores = Env.GetIfArgPrefixInt("-cores:", 1, "Number-of-Cores");
    if (Env.IsEndOfRun()){return 0;}

    TVec<PBowDocBs> BowDocBsV;
    for (int InBowFNmN = 0; InBowFNmN < InBowFNmV.Len(); InBowFNmN++) {
        TStr InBowFNm = InBowFNmV[InBowFNmN];
        printf("Loading %s ...\n", InBowFNm.CStr());
        PBowDocBs BowDocBs = TBowDocBs::LoadBin(InBowFNm);
        BowDocBsV.Add(BowDocBs);        
    }

    printf("Calculating KCCA ...\n");
    TVec<PSemSpace> SemSpaceV;
    TMKCCASemSpace::Calc(BowDocBsV, SemSpaceV);
    printf("Done\n");

    return 0;
    Catch;
    return 1;
}

