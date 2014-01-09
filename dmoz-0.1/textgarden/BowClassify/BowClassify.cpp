#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Bag-Of-Words To Bag-Of-Word-Weights");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "", "Input-BagOfWords-FileName");
  TStr InBowMdFNm=Env.GetIfArgPrefixStr("-imd:", "", "Input-BagOfWords-Model-FileName");
  TStr InQueryStr=Env.GetIfArgPrefixStr("-qs:", "", "Input-Query-String");
  TStr InQueryHtmlFNm=Env.GetIfArgPrefixStr("-qh:", "", "Input-Query-Html-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "BowCfy.Xml", "Output-Classification-Xml-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "BowCfy.Txt", "Output-Classification-Txt-File");
  bool OutScrP=Env.GetIfArgPrefixBool("-os:", true, "Output-Classification-To-Screen");
  int MxCats=Env.GetIfArgPrefixInt("-mxcat:", -1, "Maximal-Number-of-Categories");
  if (Env.IsEndOfRun()){return 0;}

  // load bow data
  printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  // load bow-model
  printf("Loading bag-of-words-model from '%s' ...", InBowMdFNm.CStr());
  PBowMd BowMd=TBowMd::LoadBin(InBowMdFNm, BowDocBs);
  printf(" Done.\n");

  // get query document in bow form
  PBowSpV QueryBowSpV;
  PBowDocWgtBs BowDocWgtBs = TBowDocWgtBs::New(BowDocBs, bwwtLogDFNrmTFIDF);
  if (!InQueryStr.Empty()){
    QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(InQueryStr, BowDocWgtBs);
  } else
  if (!InQueryHtmlFNm.Empty()){
    QueryBowSpV=BowDocBs->GetSpVFromHtmlFile(InQueryHtmlFNm, BowDocWgtBs);
  } else {
    TExcept::Throw("No Input-Query specified!");
  }

  // classification
  TFltStrPrV WgtCatNmPrV;
  BowMd->GetCfy(QueryBowSpV, WgtCatNmPrV);
  if (MxCats > 0 && WgtCatNmPrV.Len() > MxCats) { WgtCatNmPrV.Trunc(MxCats); }

  if (BowMd->IsLinComb()) {
    TFltStrPrV WgtStrPrV; double Thresh;
	BowMd->GetLinComb(BowDocBs, WgtStrPrV, Thresh);
	printf("%d\n", WgtStrPrV.Len());
	TFOut FOut(TFile::GetUniqueFNm("why.csv"));
	for (int WIdN = 0; WIdN < QueryBowSpV->GetWIds(); WIdN++) {
		const int WId = QueryBowSpV->GetWId(WIdN);
		const double Wgt = QueryBowSpV->GetWgt(WIdN);
		if (WId < WgtStrPrV.Len()) { 
			FOut.PutStr(TStr::Fmt("%s,%g\n",
				BowDocBs->GetWordStr(WId).CStr(), 
				Wgt * WgtStrPrV[WId].Val1.Val));
		} else {
			FOut.PutStr(TStr::Fmt("%s,0.0\n", BowDocBs->GetWordStr(WId).CStr()));
		}
	}
  }

  // output classification results
  // output xml
  if (!OutXmlFNm.Empty()){
    PSOut SOut=TFOut::New(OutXmlFNm);
    TBowMd::SaveXmlCfy(SOut, WgtCatNmPrV);
  }
  // output text
  if (!OutTxtFNm.Empty()){
    PSOut SOut=TFOut::New(OutTxtFNm);
    TBowMd::SaveTxtCfy(SOut, WgtCatNmPrV);
  }
  // output to screen
  if (OutScrP){
    PSOut SOut=TSOut::StdOut;
    TBowMd::SaveTxtCfy(SOut, WgtCatNmPrV);
  }

  return 0;
  Catch;
  return 1;
}

