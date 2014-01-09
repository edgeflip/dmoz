#include <mine.h>

void ActiveLearningLoop(PBowDocBs BowDocBs, const TStr& CatNm, const double& C,
        const double& j, const TStr& StatFNm) {


    const int CId = BowDocBs->GetCId(CatNm);
    PBowAL BowAL = TBowAL::NewFromCat(BowDocBs, CId, C, j);

    forever {
        // stop if everything labled
        if (!BowAL->GenQueryDIdV()) break;

        // write the question
        double MinDist; int DId; 
        BowAL->GetQueryDistDId(0, MinDist, DId);
        const TStr DocNm = BowDocBs->GetDocNm(DId);
        const TStr DocStr = BowDocBs->GetDocStr(DId);
        printf("Does the following document belong to the \'%s\' category?\n", CatNm.CStr());
        printf("=======================================================================\n");
        printf("%s:\n", DocNm.CStr());
        printf("%s\n", DocStr.CStr());
        printf("=======================================================================\n");
        printf("Distance from the hyperplane is %g.\n", MinDist);
        printf(" 1 - yes\n"); printf(" 2 - no\n"); printf(" 3 - exit\n");

        // read the answer
        int UserResponse = 0;
        do { scanf("%d", &UserResponse); }
        while (!(1 <= UserResponse && UserResponse <= 3));
        // user had enough?
        if (UserResponse == 3) break;

        // add the category information to Bow and to TrainSet
        if (UserResponse == 1) {
            printf("Adding to category %s!\n", CatNm.CStr());
            BowAL->MarkQueryDoc(DId, true);
        } else if (UserResponse == 2) {
            printf("Taking note that it is not in the category %s!\n", CatNm.CStr());
            BowAL->MarkQueryDoc(DId, false);
        }
    }

    printf("\n");
    // if user wants, we mark the rest of the positive documents with this category
    printf("Mark the rest of the documents? (1 - yes, 2 - no)");
    int UserResponse = 0; do { scanf("%d", &UserResponse); }
    while (!(1 <= UserResponse && UserResponse <= 2));
    if (UserResponse == 1) {
        BowAL->MarkUnlabeledPosDocs();
    }
}

int main(int argc, char* argv[]) {
    Try;
    // create environment
    Env=TEnv(argc, argv, TNotify::StdNotify);

    // command line parameters
    Env.PrepArgs("Bag-Of-Words Active-Learning", 2);
    // input-output files
    TStr InBowFName = Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName (.Bow)");
    TStr OutBowFName = Env.GetIfArgPrefixStr("-o:", "", "Output-Labled-BagOfWords-FileName (.Bow)");
    TStr CatNm=Env.GetIfArgPrefixStr("-cat:", "", "Category-Name");
    double c = Env.GetIfArgPrefixFlt("-c:", 1.0, "Cost-Parameter");
    double j = Env.GetIfArgPrefixFlt("-j:", 1.0, "Weight-for-Cost-Parameter-for-Relevant-Documents");
    if (Env.IsEndOfRun()){return 0;}

    PBowDocBs BowDocBs = TBowDocBs::LoadBin(InBowFName);
    EAssertR(BowDocBs->IsCatNm(CatNm), CatNm + " is not a valid category name!");
    ActiveLearningLoop(BowDocBs, CatNm, c, j,  TStr::PutFExt(OutBowFName, ".stat.txt"));
    BowDocBs->SaveBin(OutBowFName);

	TStrV PosDocNmV, NegDocNmV;
	const int CId = BowDocBs->GetCId(CatNm);
	for (int DId = BowDocBs->GetDocs(); DId < BowDocBs->GetDocs(); DId++) {
		TStr DocNm = BowDocBs->GetDocNm(DId);
		if (BowDocBs->IsCatInDoc(DId, CId)) {
			PosDocNmV.Add(DocNm);
		} else {
			NegDocNmV.Add(DocNm);
		}
	}
	PosDocNmV.Sort(); NegDocNmV.Sort();

	printf("\nNumber of positive documents: %d\n", PosDocNmV.Len());
	printf("Number of negative documents: %d\n", NegDocNmV.Len());
	
	printf("\nList of positive documents:\n");
	for (int PosDocNmN = 0; PosDocNmN < PosDocNmV.Len(); PosDocNmN++) {
		if (PosDocNmN > 0) { printf(", "); }
		printf("%s", PosDocNmV[PosDocNmN].CStr());
	}

    return 0;
    Catch;
    return 1;
}

