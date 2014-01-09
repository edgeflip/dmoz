#include "mine.h"

TStr GetCountryDescStr(PCiaWFBCountry CiaWFBCountry, const TStrV& FldNmV) {
    TChA DescChA = "";
    for (int FldNmN = 0; FldNmN < FldNmV.Len(); FldNmN++) {
        TStr FldVal;
        if (CiaWFBCountry->IsFld(FldNmV[FldNmN], FldVal)) {
            if (!DescChA.Empty()) DescChA += "\n";
            DescChA += FldVal;
        } else {
            //printf("'%s' is not a valid field name!\n", FldNmV[FldNmN].CStr());
        }
    }
    return TStr(DescChA);
}

int main(int argc, char* argv[]){
  Try;

  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Text To Bag-Of-Words");
  TStr InBinFNm=Env.GetIfArgPrefixStr("-ibin:", "CiaWFB.Bin", "Input-Binary-FileName");
  TStr InHtmlFPath=Env.GetIfArgPrefixStr("-ihtml:", "", "Input-Html-Path");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-obow:", "", "Output-BagOfWords");
  TStr OutLnDocFNm=Env.GetIfArgPrefixStr("-olndoc:", "", "Output-Named-Line-Documents");
  bool StatP=Env.GetIfArgPrefixBool("-ostat:", false, "Output-BagOfWords-Statistics");
  TStrV FldNmV=Env.GetIfArgPrefixStrV("-fld:", TStrV::GetV("Background"), "Description-Field-Name");
  int MnPopulation=Env.GetIfArgPrefixInt("-mnpop:", 1000000, "Minimal-Population-Size");
  if (Env.IsEndOfRun()){return 0;}

  // load ciawfb data
  PCiaWFBBs CiaWFBBs=TCiaWFBBs::LoadBinOrHtml(InBinFNm, InHtmlFPath);

  // create ngrams
  TStrV HtmlStrV;
  for (int CountryN=0; CountryN<CiaWFBBs->GetCountries(); CountryN++){
    PCiaWFBCountry CiaWFBCountry=CiaWFBBs->GetCountry(CountryN);
    if (CiaWFBCountry->GetFldValNum("Population") > MnPopulation) {
        HtmlStrV.Add(GetCountryDescStr(CiaWFBCountry, FldNmV));
    }
  }
  PSwSet SwSet=TSwSet::GetSwSet(swstEn523);
  PNGramBs NGramBs=TNGramBs::GetNGramBsFromHtmlStrV(HtmlStrV, 3, 3, SwSet);

  // create bow
  PBowDocBs BowDocBs=TBowDocBs::New();
  BowDocBs->PutNGramBs(NGramBs);
  for (int CountryN=0; CountryN<CiaWFBBs->GetCountries(); CountryN++){
    PCiaWFBCountry CiaWFBCountry=CiaWFBBs->GetCountry(CountryN);
    if (CiaWFBCountry->GetFldValNum("Population") > MnPopulation) {
        TStr CountryNm=CiaWFBCountry->GetCountryNm();
        TStr DescStr=GetCountryDescStr(CiaWFBCountry, FldNmV);
        TStrV CatNmV; CatNmV.Add(CiaWFBCountry->GetFldVal("Map references").ToTrunc());
        BowDocBs->AddHtmlDoc(CountryNm, CatNmV, DescStr, true);
    }
  }
  BowDocBs->AssertOk();

  // save bow
  if (!OutBowFNm.Empty()) { 
    BowDocBs->SaveBin(OutBowFNm); 
    if (StatP) { BowDocBs->SaveTxtStat(TStr::PutFExt(OutBowFNm, ".stat.txt"), true, true, true); }
  }
  if (!OutLnDocFNm.Empty()) { TBowFl::SaveLnDocTxt(BowDocBs, OutLnDocFNm, true); }


  return 0;
  Catch;
  return 1;
}

