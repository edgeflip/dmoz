#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words-Partition To Dump", -1);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ib:", "", "Input-BagOfWords-FileName");
  TStr InBowPartFNm=Env.GetIfArgPrefixStr("-ip:", "", "Input-BagOfWordsPartition-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "", "Output-Text-FileName");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "", "Output-Xml-FileName");
  TStr OutRdfFNm=Env.GetIfArgPrefixStr("-or:", "", "Output-Rdf-FileName");
  bool SaveWordsP=Env.GetIfArgPrefixBool("-sw:", true, "Save-Words");
  int TopWords=Env.GetIfArgPrefixInt("-topwords:", 10, "Top-Words");
  double TopWordsWgtPrc=Env.GetIfArgPrefixFlt("-topwwp:", 1.0, "Top-Words-Weights-Percent");
  bool SaveDocsP=Env.GetIfArgPrefixBool("-sd:", true, "Save-Documents");
  if (Env.IsEndOfRun()){return 0;}

  // load bow-data
  PBowDocBs BowDocBs;
  if (!InBowFNm.Empty()){
    printf("Loading Bag-Of-Words Data '%s' ...", InBowFNm.CStr());
    BowDocBs=TBowDocBs::LoadBin(InBowFNm);
    printf(" Done.\n");
  }
  // load bow-partition-data
  PBowDocPart BowDocPart;
  if (!InBowPartFNm.Empty()){
    printf("Loading Partition Data '%s' ...", InBowPartFNm.CStr());
    BowDocPart=TBowDocPart::LoadBin(InBowPartFNm);
    printf(" Done.\n");
  }

  // output text-file
  if ((!BowDocBs.Empty())&&(!BowDocPart.Empty())&&(!OutTxtFNm.Empty())){
    printf("Saving data to '%s' ...", OutTxtFNm.CStr());
    BowDocPart->SaveTxt(OutTxtFNm, BowDocBs,
     SaveWordsP, TopWords, TopWordsWgtPrc, SaveDocsP);
    printf(" Done.");
  }
  // output Xml-file
  if ((!BowDocBs.Empty())&&(!BowDocPart.Empty())&&(!OutXmlFNm.Empty())){
    printf("Saving data to '%s' ...", OutXmlFNm.CStr());
    BowDocPart->SaveXml(OutXmlFNm, BowDocBs);
    printf(" Done.");
  }
  // output Rdf-file
  if ((!BowDocBs.Empty())&&(!BowDocPart.Empty())&&(!OutRdfFNm.Empty())){
    printf("Saving data to '%s' ...", OutRdfFNm.CStr());
    BowDocPart->SaveRdf(OutRdfFNm, BowDocBs);
    printf(" Done.");
  }

  return 0;
  Catch;
  return 1;
}

