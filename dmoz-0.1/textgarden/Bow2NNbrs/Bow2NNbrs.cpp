#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Nearest-Neighbours", -1);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-BagOfWords-FileName");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-oxml:", "NNbrs.Xml", "Output-NNeighbours-Xml-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-otxt:", "NNbrs.Txt", "Output-NNeighbours-Txt-File");
  bool OutScrP=Env.GetIfArgPrefixBool("-oscr:", true, "Output-To-Screen");
  int TopNNbrDocs=Env.GetIfArgPrefixInt("-topdocs:", 10, "Output-Top-NNeighbour-Documents");
  int TopNNbrWords=Env.GetIfArgPrefixInt("-topwords:", 10, "Output-Top-NNeighbour-Words");
  int QueryId=Env.GetIfArgPrefixInt("-qid:", -1, "Query-DocumentId");
  bool QueryAllIdP=Env.GetIfArgPrefixBool("-qall:", false, "Query-All-DocumentIds");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cutww:", 0.0, "Cut-Word-Weight-Sum-Percentage");
  int MnWordFq=Env.GetIfArgPrefixInt("-mnwfq:", 0, "Minimal-Word-Frequency");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading data '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  PBowDocWgtBs BowDocWgtBs=
   TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF, CutWordWgtSumPrc, MnWordFq);
  printf(" Done.\n");

  if (QueryAllIdP){
    // create output files
    PSOut XmlSOut; PSOut TxtSOut;
    if (!OutXmlFNm.Empty()){XmlSOut=TFOut::New(OutXmlFNm);}
    if (!OutTxtFNm.Empty()){TxtSOut=TFOut::New(OutTxtFNm);}
    // create similarity
    PBowSim BowSim=TBowSim::New(bstCos);
    // traverse all documents
    int Docs=BowDocWgtBs->GetDocs();
    for (int DIdN=0; DIdN<Docs; DIdN++){
      // get doc-id
      int QueryId=BowDocWgtBs->GetDId(DIdN);
      printf("Doc:%d\r", QueryId);
      // get query-vector
      PBowSpV QueryBowSpV=BowDocWgtBs->GetSpV(QueryId);
      // calculate similarity
      TFltIntKdV SimDIdKdV;
      BowDocWgtBs->GetSimDIdV(QueryBowSpV, BowSim, SimDIdKdV);
      // output xml
      if (!XmlSOut.Empty()){
        BowDocWgtBs->SaveXmlSimDIdV(XmlSOut, BowDocBs,
         QueryBowSpV, SimDIdKdV, TopNNbrDocs, 0);
      }
      // output txt
      if (!TxtSOut.Empty()){
        BowDocWgtBs->SaveTxtSimDIdV(TxtSOut, BowDocBs,
         QueryBowSpV, SimDIdKdV, TopNNbrDocs, 0, TopNNbrWords, '\n');
      }
    }
  } else
  if (QueryId!=-1){
    // get query-vector
    PBowSpV QueryBowSpV=BowDocWgtBs->GetSpV(QueryId);

    // calculate similarity
    PBowSim BowSim=TBowSim::New(bstCos);
    TFltIntKdV SimDIdKdV; BowDocWgtBs->GetSimDIdV(QueryBowSpV, BowSim, SimDIdKdV);

    // output xml search results
    if (!OutXmlFNm.Empty()){
      PSOut SOut=TFOut::New(OutXmlFNm);
      BowDocWgtBs->SaveXmlSimDIdV(
       SOut, BowDocBs, QueryBowSpV, SimDIdKdV, TopNNbrDocs, 0);
    }
    // output text search results
    if (!OutTxtFNm.Empty()){
      PSOut SOut=TFOut::New(OutTxtFNm);
      BowDocWgtBs->SaveTxtSimDIdV(
       SOut, BowDocBs, QueryBowSpV, SimDIdKdV, TopNNbrDocs, 0, TopNNbrWords, '\n');
    }
    // output to screen
    if (OutScrP){
      PSOut SOut=TSOut::StdOut;
      BowDocWgtBs->SaveTxtSimDIdV(
       SOut, BowDocBs, QueryBowSpV, SimDIdKdV, TopNNbrDocs, 0, TopNNbrWords, '\n');
    }
  }

  return 0;
  Catch;
  return 1;
}
