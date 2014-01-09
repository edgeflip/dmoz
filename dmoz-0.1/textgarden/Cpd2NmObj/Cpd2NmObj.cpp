#include "mine.h"
#include "nmobj.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Compact-Documents To Named-Objects", 0);
  TStr InCpdFNm=Env.GetIfArgPrefixStr("-icpd:", "", "Input-Cpd-FileName");
  TStr InCustSwSetFNm=Env.GetIfArgPrefixStr("-isw:", "StopWord.Txt", "Input-CustomStopWords-FileName");
  TStr InNrWordBsFNm=Env.GetIfArgPrefixStr("-inw:", "WordStem.Txt", "Input-NormalizedWords-FileName");
  TStr InWordTypeBsFNm=Env.GetIfArgPrefixStr("-iwt:", "WordType.Txt", "Input-WordType-FileName");
  TStr OutNmObjFNm=Env.GetIfArgPrefixStr("-ono:", "Out.NmObj", "Output-NamedObject");
  TStr OutNmObjBowFNm=Env.GetIfArgPrefixStr("-onobow:", "Out.NmObj.Bow", "Output-NamedObject-BagOfWords");
  TStr OutNmObjBowStatFNm=Env.GetIfArgPrefixStr("-onobows:", "Out.NmObj.Bow.Stat.Txt", "Output-NamedObject-BagOfWords-Statistics");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-obow:", "Out.Bow", "Output-BagOfWords");
  TStr OutBowStatFNm=Env.GetIfArgPrefixStr("-obows:", "Out.Bow.Stat.Txt", "Output-BagOfWords-Statistics");
  TStr OutNmObjFqFNm=Env.GetIfArgPrefixStr("-ofq:", "NmObjFq.Txt", "Output-Frequency-File");
  TStr OutNmObjSwFNm=Env.GetIfArgPrefixStr("-osw:", "NmObjSw.Txt", "Output-StopWords-File");
  TStr OutNmObjAbcFNm=Env.GetIfArgPrefixStr("-oabc:", "NmObjAbc.Txt", "Output-Alphabetic-File");
  TStr OutNmObjDocFNm=Env.GetIfArgPrefixStr("-odoc:", "NmObjDoc.Txt", "Output-Documents-File");
  TStr SwSetTypeNm=Env.GetIfArgPrefixStr("-stopword:", "en523", "Stop-Word-Set "+TSwSet::GetSwSetTypeNmVStr());
  TStr StemmerTypeNm=Env.GetIfArgPrefixStr("-stemmer:", "porter", "Stemmer "+TStemmer::GetStemmerTypeNmVStr());
  int MxNGramLen=Env.GetIfArgPrefixInt("-ngramlen:", 3, "Max-NGram-Length");
  int MnNGramFq=Env.GetIfArgPrefixInt("-ngramfq:", 5, "Min-NGram-Frequency");
  int MxDocs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents"); 
  bool DumpP=Env.GetIfArgPrefixBool("-dump:", false, "Dump"); 
  if (Env.IsEndOfRun()){return 0;}

  //InCpdFNm="/data/reuters2k/R2K.Cpd";
  //InCustSwSetFNm="/data/reuters2k/R2K-StopWord.Txt";
  //InNrWordBsFNm="/data/reuters2k/R2K-WordStem.Txt";
  //InWordTypeBsFNm="/data/reuters2k/R2K-WordType.Txt";
  //MxDocs=10000;
  //DumpP=false;

  // named-objects to create
  TSwSetType SwSetType=TSwSet::GetSwSetType(SwSetTypeNm); // stop-words-type
  PNmObjBs NmObjBs=TNmObjBs::GetFromCpd(
   InCpdFNm, SwSetType, InCustSwSetFNm, InNrWordBsFNm, InWordTypeBsFNm, "", MxDocs, DumpP);

  // save binary named-objects
  NmObjBs->SaveBin(OutNmObjFNm);
  // save textual named-objects
  NmObjBs->SaveTxtNmObj(OutNmObjFqFNm, OutNmObjSwFNm, OutNmObjAbcFNm, OutNmObjDocFNm);

  // save bag-of-words named-objects
  {PBowDocBs NmObjBowDocBs=NmObjBs->GetBowDocBs();
  NmObjBowDocBs->SaveBin(OutNmObjBowFNm);
  NmObjBowDocBs->SaveTxtStat(OutNmObjBowStatFNm);}

  // save bag-of-words
  {PBowDocBs BowDocBs=TBowFl::LoadCpdTxt(InCpdFNm, MxDocs,
   SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  BowDocBs->SaveBin(OutBowFNm);
  BowDocBs->SaveTxtStat(OutBowStatFNm);}

  return 0;
  Catch;
  return 1;
}