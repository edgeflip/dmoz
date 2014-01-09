#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("SemanticSpace to BowPartition");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "", "Input-BagOfWords-File");
  TStr InSemSpaceFNm=Env.GetIfArgPrefixStr("-issp:", "", "Input-SemanticSpace-File");
  TStr OutPartFNm=Env.GetIfArgPrefixStr("-o:", "SemSpace.BowPart", "Output-BowPartition-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "SemSpace.Txt", "Output-Txt-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "SemSpace.Xml", "Output-Xml-File");
  double Eps=Env.GetIfArgPrefixFlt("-eps:", false, "Epsilon (everything under is regarded zero)");
  if (Env.IsEndOfRun()){return 0;}

  // load data
  if (InBowFNm.Empty()){TExcept::Throw("No Input-Bow-File specified!");}
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  if (InSemSpaceFNm.Empty()){TExcept::Throw("No Input-SemanticSpace-File specified!");}
  PSemSpace SemSpace = TSemSpace::LoadBin(InSemSpaceFNm);  

  // transform SemSpace to BowDocPart
  PBowDocPart BowDocPart = SemSpace->GetBowDocPart(BowDocBs, Eps);

  // output partition
  if (!OutPartFNm.Empty()){
    TFOut SOut(OutPartFNm); BowDocPart->Save(SOut);}
  if (!OutTxtFNm.Empty()){
    BowDocPart->SaveTxt(OutTxtFNm, BowDocBs, true, 15, 0.5, false);}
  if (!OutXmlFNm.Empty()){
    BowDocPart->SaveXml(OutXmlFNm, BowDocBs);}

  return 0;
  Catch;
  return 1;
}

