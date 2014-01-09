#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("DMoz Topic To Bow", -1);
  TStr InFPath=Env.GetIfArgPrefixStr("-i:", "", "Input-File-Path");
  TStr OutFPath=Env.GetIfArgPrefixStr("-o:", "", "Output-File-Path");
  TStr RootCatNm=Env.GetIfArgPrefixStr("-c:", "Top", "Root-Category-Name");
  TStrV PosCatNmV=Env.GetIfArgPrefixStrV("-sc:", "Selected-Categories");
  TStrV NegCatNmV=Env.GetIfArgPrefixStrV("-uc:", "Unselected-Categories");
  int MnCatDocs=Env.GetIfArgPrefixInt("-mncdocs:", -1, "Min-Category-Documents");
  TStr SwSetTypeNm=Env.GetIfArgPrefixStr("-stopword:", "en523", "Stop-Word-Set "+TSwSet::GetSwSetTypeNmVStr());
  TStr StemmerTypeNm=Env.GetIfArgPrefixStr("-stemmer:", "porter", "Stemmer "+TStemmer::GetStemmerTypeNmVStr());
  int MxNGramLen=Env.GetIfArgPrefixInt("-ngramlen:", 3, "Max-NGram-Length");
  int MnNGramFq=Env.GetIfArgPrefixInt("-ngramfq:", 5, "Min-NGram-Frequency");
  if (Env.IsEndOfRun()){return 0;}
  // -i:\Data\DMoz -o:\Data\DMoz -c:Top -uc:Top/World -mncdocs:10000
  // -i:\Data\DMoz -o:\Data\DMoz -c:Top -sc:Top/Home -sc:Top/Reference
  // -i:\Data\DMoz -o:\Data\DMoz -c:Top/Computers/Artificial_Intelligence -uc:Top/Computers/Artificial_Intelligence/Agents
  // -i:\Data\DMoz -o:\Data\DMoz -c:Top -sc:Top/Business -sc:Top/Society -sc:Top/Computers -mncdocs:100

  // prepare file-name values
  TStr OutNrFPath=TStr::GetNrFPath(OutFPath);
  TStr RootCatFMid=TStr::GetFNmStr(RootCatNm, true);

  // load DMoz-Base
  PDMozBs DMozBs=TDMozBs::LoadBin(TDMozInfo::BinFullFBase, InFPath);

  // retrieve title&desc-string-vector
  TStrV DocNmV; TStrV DocStrV;
  printf("Retrieving sub-tree documents ...");
  DMozBs->GetSubTreeDocV(RootCatNm, PosCatNmV, NegCatNmV, DocNmV, DocStrV, true, 1);
  printf(" Done.\n");

  // stop-words
  PSwSet SwSet=TSwSet::GetSwSet(SwSetTypeNm);
  // stemming
  PStemmer Stemmer=TStemmer::GetStemmer(StemmerTypeNm);
  // create ngrams
  PNGramBs NGramBs;
  if (!((MxNGramLen==1)&&(MnNGramFq==1))){
    NGramBs=TNGramBs::GetNGramBsFromHtmlStrV(
     DocStrV, MxNGramLen, MnNGramFq, SwSet, Stemmer);
  }

  // save ngram-statistics
  if (!NGramBs.Empty()){
    TStr NGramStatFNm=OutNrFPath+RootCatFMid+".NGramStat.Txt";
    printf("Saving ngram-statistics to %s ...", NGramStatFNm.CStr());
    NGramBs->SaveTxt(NGramStatFNm, true);
    printf(" Done.\n");
  }

  // create bag-of-words
  printf("Creating bag-of-words...\n");
  PBowDocBs BowDocBs=TBowDocBs::New(SwSet, Stemmer, NGramBs);
  for (int DocN=0; DocN<DocNmV.Len(); DocN++){
    if (((DocN+1)%100==0)||(DocN+1==DocNmV.Len())){
      printf("  %d/%d Docs\r", 1+DocN, DocNmV.Len());}
    int DId=BowDocBs->AddHtmlDoc(DocNmV[DocN], TStrV(), DocStrV[DocN]);
    TStr UrlStr=DMozBs->GetExtUrlStr(DocNmV[DocN].GetInt());
    BowDocBs->PutDocDescStr(DId, UrlStr);
  }
  BowDocBs->AssertOk();
  DocNmV.Clr(); DocStrV.Clr();
  printf("\nDone.\n");

  // save bow-file
  TStr OutBowFNm=OutNrFPath+RootCatFMid+".Bow";
  printf("Saving bag-of-words to %s ...", OutBowFNm.CStr());
  BowDocBs->SaveBin(OutBowFNm);
  printf(" Done.\n");

  // save bow-statistics file
  TStr OutBowStatFNm=OutNrFPath+RootCatFMid+".BowStat.Txt";
  printf("Saving bag-of-words statistics to %s ...", OutBowStatFNm.CStr());
  BowDocBs->SaveTxtStat(OutBowStatFNm);
  printf(" Done.\n");

  // create tfidf-vectors
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtLogDFNrmTFIDF);

  // prepare similarity measure
  PBowSim BowSim=TBowSim::New(bstCos);

  // create document-partition with centroids
  printf("Creating bag-of-words-partition ...\n");
  PBowDocPart BowDocPart=
   DMozBs->GetBowDocPart(RootCatNm, PosCatNmV, NegCatNmV, BowDocBs, BowDocWgtBs, BowSim, MnCatDocs);
  printf("\nDone.\n");

  // save document-partition
  TStr OutBowDocPartFNm=OutNrFPath+RootCatFMid+".BowPart";
  printf("Saving bag-of-words-partition to %s ...", OutBowDocPartFNm.CStr());
  BowDocPart->SaveBin(OutBowDocPartFNm);
  printf(" Done.\n");

  // save document-partition text-statistics
  TStr OutBowDocPartTxtFNm=OutNrFPath+RootCatFMid+".BowPartStat.Txt";
  printf("Saving bag-of-words-partition-text-statisitics to %s ...", OutBowDocPartTxtFNm.CStr());
  BowDocPart->SaveTxt(OutBowDocPartTxtFNm, BowDocBs, true, 10000, 0.66, true);
  printf(" Done.\n");

  // save document-partition xml
  TStr OutBowDocPartXmlFNm=OutNrFPath+RootCatFMid+".BowPartStat.Xml";
  printf("Saving bag-of-words-partition-xml to %s ...", OutBowDocPartXmlFNm.CStr());
  BowDocPart->SaveXml(OutBowDocPartXmlFNm, BowDocBs);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

