#include "mine.h"
//#include "vizmap.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Text To Bag-Of-Words");
  TStr InFPath=Env.GetIfArgPrefixStr("-ihtml:", "", "Input-Html-Path");
  TStr InMtxFNm=Env.GetIfArgPrefixStr("-imtx:", "", "Input-Matrix-File");
  TStr InTabFNm=Env.GetIfArgPrefixStr("-itab:", "", "Input-Tab-File");
  TStr InTsactFNm=Env.GetIfArgPrefixStr("-itsc:", "", "Input-Transaction-File");
  TStr InSparseFNm=Env.GetIfArgPrefixStr("-ispr:", "", "Input-Sparse-File");
  TStr InSvmLightFNm=Env.GetIfArgPrefixStr("-isvml:", "", "Input-SvmLight-File");
  TStr InCpdFNm=Env.GetIfArgPrefixStr("-icpd:", "", "Input-CompactDocuments-File");
  TStr InTBsFNm=Env.GetIfArgPrefixStr("-itbs:", "", "Input-TextBase-File");
  TStr InLnDocFNm=Env.GetIfArgPrefixStr("-ilndoc:", "", "Input-LineDocuments-File");
  TStr InNmLnDocFNm=Env.GetIfArgPrefixStr("-inlndoc:", "", "Input-Named-LineDocuments-File");
  TStr InReuters21578FPath=Env.GetIfArgPrefixStr("-ir21578:", "", "Input-Reuters21578-Path");
  TStr InCiaWFBFPath=Env.GetIfArgPrefixStr("-iciawfb:", "", "Input-CIA-World-Fact-Book-Path");
  TStr InDaxFNm=Env.GetIfArgPrefixStr("-idax:", "", "Input-DocumentAtlasXML-File");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-o:", "Out.Bow", "Bow-Output-File (.Bow)");
  bool OutStatP=Env.GetIfArgPrefixBool("-ostat:", true, "Output-Statistics (*.Txt)");
  int Recs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents-To-Process");
  bool RecurseDirP=Env.GetIfArgPrefixBool("-recurse:", false, "Recurse-Directories");
  TStr SwSetTypeNm=Env.GetIfArgPrefixStr("-stopword:", "en523", "Stop-Word-Set "+TSwSet::GetSwSetTypeNmVStr());
  TStr SwSetFNm=Env.GetIfArgPrefixStr("-istopword:", "", "External-Stop-Word-Set-File");
  TStr StemmerTypeNm=Env.GetIfArgPrefixStr("-stemmer:", "porter", "Stemmer "+TStemmer::GetStemmerTypeNmVStr());
  int MxNGramLen=Env.GetIfArgPrefixInt("-ngramlen:", 3, "Max-NGram-Length");
  int MnNGramFq=Env.GetIfArgPrefixInt("-ngramfq:", 5, "Min-NGram-Frequency");
  bool SaveDocP=Env.GetIfArgPrefixBool("-savedoc:", false, "Save-Document-Text");
  if (Env.IsEndOfRun()){return 0;}
  // -idir:f:\data\ciawfb\print -o:CiaWfb.Bow -docs:50
  // -isvml:SvmLightTrain.Dat -o:SvmLight.Bow
  // -ir21578:f:\data\Reuters21578 -o:Reuters21578.Bow
  // -inlndoc:c:\data\yahoocompanies\CompProfilesSymbols.txt
  // -ihtml:c:\data\cordis\fp6

  // bag-of-words to create
  PBowDocBs BowDocBs;

  // load input data
  if (!InFPath.Empty()){ // directory-files
    // prepare stop-words
    PSwSet SwSet=TSwSet::GetSwSet(SwSetTypeNm);
    if (!SwSetFNm.Empty()) { SwSet->LoadFromFile(SwSetFNm); }
    // prepare stemmer
    PStemmer Stemmer=TStemmer::GetStemmer(StemmerTypeNm);
    // load bow
    BowDocBs=TBowFl::LoadHtmlTxt(InFPath, RecurseDirP, Recs,
     SwSet, Stemmer, MxNGramLen, MnNGramFq, SaveDocP);
  } else
  if (!InMtxFNm.Empty()){ // matrix-file
    PBowSimMtx BowSimMtx=TBowSimMtx::LoadTxt(InMtxFNm);
    BowDocBs=TBowFl::LoadFromSimMtx(BowSimMtx);
  } else
  if (!InTabFNm.Empty()){ // tab-file
    BowDocBs=TBowFl::LoadTabTxt(InTabFNm, Recs);
  } else
  if (!InTsactFNm.Empty()){ // transaction-file
    BowDocBs=TBowFl::LoadTsactTxt(InTsactFNm, Recs);
  } else
  if (!InSparseFNm.Empty()){ // sparse-file
    TStr DocDefFNm=TStr::PutFExt(InSparseFNm, ".tup");
    TStr WordDefFNm=TStr::PutFExt(InSparseFNm, ".var");
    TStr TrainDataFNm=InSparseFNm;
    BowDocBs=TBowFl::LoadSparseTxt(DocDefFNm, WordDefFNm, TrainDataFNm, Recs);
  } else
  if (!InSvmLightFNm.Empty()){ // SvmLight-file
    TStr DocDefFNm=TStr::PutFExt(InSparseFNm, ".tup");
    TStr WordDefFNm=TStr::PutFExt(InSparseFNm, ".var");
    TStr TrainDataFNm=InSvmLightFNm;
    BowDocBs=TBowFl::LoadSvmLightTxt(DocDefFNm, WordDefFNm, TrainDataFNm, "", Recs);
  } else
  if (!InTBsFNm.Empty()){ // Text-Base-file
    //BowDocBs=TBowFl::LoadTBsTxt(InTBsFNm, Recs);
  } else
  if (!InCpdFNm.Empty()){ // Compact-Doc-file
    BowDocBs=TBowFl::LoadCpdTxt(InCpdFNm, Recs,
     SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  } else
  if (!InLnDocFNm.Empty()){ // Line-Documents-file
    BowDocBs=TBowFl::LoadLnDocTxt(InLnDocFNm, false, Recs,
     SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq, SaveDocP);
  } else
  if (!InNmLnDocFNm.Empty()){ // Named-Line-Documents-file
    BowDocBs=TBowFl::LoadLnDocTxt(InNmLnDocFNm, true, Recs,
     SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq, SaveDocP);
  } else
  if (!InReuters21578FPath.Empty()){ // Reuters-21578-file
    BowDocBs=TBowFl::LoadReuters21578Txt(InReuters21578FPath, Recs,
     SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  } else 
  if (!InCiaWFBFPath.Empty()){ // CIA-World-Fact-Book
    BowDocBs=TBowFl::LoadCiaWFBTxt(InCiaWFBFPath, Recs,
     SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  } else 
  if (!InDaxFNm.Empty()) { // DocumentAtlasXml-File
    PSwSet SwSet=TSwSet::GetSwSet(SwSetTypeNm);
    PStemmer Stemmer=TStemmer::GetStemmer(StemmerTypeNm);
    BowDocBs=TVizMapXmlDocBs::LoadBowDocBs(InDaxFNm, 
     SwSet, Stemmer, MxNGramLen, MnNGramFq);
  } else {
    TExcept::Throw("No Input-File specified!");
  }

  // save bow-file
  if (!OutBowFNm.Empty()){
    TStr::PutFExtIfEmpty(OutBowFNm, ".Bow");
    printf("Saving Bow to '%s' ...", OutBowFNm.CStr());
    BowDocBs->SaveBin(OutBowFNm);
    printf(" Done.\n");
  }

  // save statistics
  if ((OutStatP)&&(!OutBowFNm.Empty())){
    // save bow-statistics
    TStr OutBowStatFNm=TStr::PutFExt(OutBowFNm, ".Bow.Txt");
    TStr::PutFExt(OutBowStatFNm, ".Bow.Txt");
    if (!OutBowStatFNm.Empty()){
      printf("Saving Bow-Statistics to '%s' ...", OutBowStatFNm.CStr());
      BowDocBs->SaveTxtStat(OutBowStatFNm);
      printf(" Done.\n");
    }
    // save ngram-statistics
    PNGramBs NGramBs=BowDocBs->GetNGramBs();
    TStr OutNGramStatFNm=TStr::PutFExt(OutBowFNm, ".NGram.Txt");
    if (!NGramBs.Empty()){
      printf("Saving NGram-Statistics to '%s' ...", OutNGramStatFNm.CStr());
      NGramBs->SaveTxt(OutNGramStatFNm, true);
      printf(" Done.\n");
    }
  }

  return 0;
  Catch;
  return 1;
}

