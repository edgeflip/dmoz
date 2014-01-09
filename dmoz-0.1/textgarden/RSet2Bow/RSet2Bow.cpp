#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Result-Set To Bag-Of-Words", 0);
  TStr InRSetFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-ResultSet-FileName");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-o:", "RSet.Bow", "Output-ResultSet-BagOfWords-FileName");
  TStr OutBowStatFNm=Env.GetIfArgPrefixStr("-ot:", "RSet.BowStat.Txt", "Output-BagOfWords-Statistics-FileName");
  bool MultiRSetsP=Env.GetIfArgPrefixBool("-rsets:", false, "Multiple-ResultSets");
  TStr SwSetTypeNm=Env.GetIfArgPrefixStr("-stopword:", "en523", "Stop-Word-Set "+TSwSet::GetSwSetTypeNmVStr());
  TStr StemmerTypeNm=Env.GetIfArgPrefixStr("-stemmer:", "porter", "Stemmer "+TStemmer::GetStemmerTypeNmVStr());
  int MxNGramLen=Env.GetIfArgPrefixInt("-ngramlen:", 3, "Max-NGram-Length");
  int MnNGramFq=Env.GetIfArgPrefixInt("-ngramfq:", 5, "Min-NGram-Frequency");
  if (Env.IsEndOfRun()){return 0;}

  printf("Loading Result-Set from Binary-File '%s' ...", InRSetFNm.CStr());
  PRSet RSet=TRSet::LoadBin(InRSetFNm, MultiRSetsP);
  printf(" Done.\n");

  printf("Creating Bag-Of-Words ...");
  PBowDocBs BowDocBs=RSet->GetBowDocBs(SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  printf(" Done.\n");

  // save bow
  printf("Saving Bow to '%s' ...", OutBowFNm.CStr());
  BowDocBs->SaveBin(OutBowFNm);
  printf(" Done.\n");

  // save bow-statistics
  if (!OutBowStatFNm.Empty()){
    printf("Saving Bow-Statistics to '%s' ...", OutBowStatFNm.CStr());
    BowDocBs->SaveTxtStat(OutBowStatFNm);
    printf(" Done.\n");
  }

  return 0;
  Catch;
  return 1;
}
