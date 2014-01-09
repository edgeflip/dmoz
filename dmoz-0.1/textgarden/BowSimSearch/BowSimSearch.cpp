#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words Similarity Search");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-File");
  TStr InQueryStr=Env.GetIfArgPrefixStr("-qs:", "", "Input-Query-String");
  TStr InQueryHtmlFNm=Env.GetIfArgPrefixStr("-qh:", "", "Input-Query-Html-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "BowSimSearch.Xml", "Output-Xml-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "BowSimSearch.Txt", "Output-Txt-File");
  bool OutScrP=Env.GetIfArgPrefixBool("-os:", true, "Output-To-Screen");
  int TopDocs=Env.GetIfArgPrefixInt("-topdocs:", 10, "Output-Top-Hits");
  int TopDocWords=Env.GetIfArgPrefixInt("-topwords:", 10, "Output-Top-Document-Words");
  double MnSim=Env.GetIfArgPrefixFlt("-mnsim:", 0, "Output-Minimal-Similarity");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.5, "Cut-Word-Weight-Sum-Percentage");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 5, "Minimal-Word-Frequency");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  if (InBowFNm.Empty()){
    TExcept::Throw("No Input-BagOfWords-File specified!");}
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);

  // generate weighted-bow
  PBowDocWgtBs BowDocWgtBs=
   TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF, CutWordWgtSumPrc, MnWordFq);

  // get query document in bow form
  PBowSpV QueryBowSpV;
  if (!InQueryStr.Empty()){
    QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(InQueryStr, BowDocWgtBs);
  } else
  if (!InQueryHtmlFNm.Empty()){
    QueryBowSpV=BowDocBs->GetSpVFromHtmlFile(InQueryHtmlFNm, BowDocWgtBs);
  } else {
    TExcept::Throw("No Input-Query specified!");
  }

  // calculate similarity
  PBowSim BowSim=TBowSim::New(bstCos);
  TFltIntKdV SimDIdKdV; BowDocWgtBs->GetSimDIdV(QueryBowSpV, BowSim, SimDIdKdV);

  // output text search results
  // output xml search results
  if (!OutXmlFNm.Empty()){
    PSOut SOut=TFOut::New(OutXmlFNm);
    BowDocWgtBs->SaveXmlSimDIdV(
     SOut, BowDocBs, QueryBowSpV, SimDIdKdV, TopDocs, MnSim/*, TopDocWords*/);
  }
  // output text search results
  if (!OutTxtFNm.Empty()){
    PSOut SOut=TFOut::New(OutTxtFNm);
    BowDocWgtBs->SaveTxtSimDIdV(
     SOut, BowDocBs, QueryBowSpV, SimDIdKdV, TopDocs, MnSim, TopDocWords);
  }
  // output to screen
  if (OutScrP){
    PSOut SOut=TSOut::StdOut;
    BowDocWgtBs->SaveTxtSimDIdV(
     SOut, BowDocBs, QueryBowSpV, SimDIdKdV, TopDocs, MnSim, TopDocWords);
  }

  return 0;
  Catch;
  return 1;
}


