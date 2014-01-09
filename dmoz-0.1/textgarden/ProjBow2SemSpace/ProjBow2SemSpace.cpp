#include <mine.h>

int main(int argc, char* argv[]) {
  Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);
    // get command line parameters
    Env.PrepArgs("Project-Bag-Of-Words-To-Semantic-Space");
    TStr InSemSpaceFNm = Env.GetIfArgPrefixStr("-issp:", "", "Input-Semantic-Space-FileName");
    TStr BowFNm = Env.GetIfArgPrefixStr("-ibow:", "", "Input-Bow-FileName");
    TStr ProjBowFNm = Env.GetIfArgPrefixStr("-obow:", "", "Output-Projected-Bow-FileName");
    int ProjSpaceDim = Env.GetIfArgPrefixInt("-sspdim:", -1, "Number-Of-Dimensions-Used-For-Projections (-1 for all)");
    bool Normalize = Env.GetIfArgPrefixBool("-nrm:", false, "Normalize-Projected-Vectors");

    if (Env.IsEndOfRun()){return 0;}

    // load semantic space and BOW for projection
    printf("Loading ");
    PSemSpace SemSpace = TSemSpace::LoadBin(InSemSpaceFNm); printf(".");
    PBowDocBs BowDocBs = TBowDocBs::LoadBin(BowFNm); printf(".");
    PBowDocWgtBs BowDocWgtBs = TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF); printf("."); 
    TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
    printf(" Done\n");
    // calculate dimensions
    int SpaceDim = (ProjSpaceDim != -1) ? ProjSpaceDim : SemSpace->GetDim();
    // project
    printf("Projecting\n");
    PBowDocBs ProjBowDocBs = SemSpace->Project(BowDocBs, BowDocWgtBs, DIdV, SpaceDim, Normalize);
    printf("Saving\n");
    ProjBowDocBs->SaveBin(ProjBowFNm);
    printf("Fin\n");

  return 0;
  Catch;
  return 1;
}