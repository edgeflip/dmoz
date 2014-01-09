#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  TStr HtmlFPath="F:/Data/print";
  PCiaWFBBs CiaWFBBs=TCiaWFBBs::LoadBin("../CiaWFBToBow/CiaWFB.Bin");

  {TFOut SOut("CiaWFB.Tab"); FILE* fOut=SOut.GetFileId();
  for (int CountryN=0; CountryN<CiaWFBBs->GetCountries(); CountryN++){
    PCiaWFBCountry CiaWFBCountry=CiaWFBBs->GetCountry(CountryN);
    TStr CountryNm=CiaWFBCountry->GetCountryNm();
    printf("Country: %s\n", CountryNm.CStr());
    for (int FldN=0; FldN<CiaWFBCountry->GetFlds(); FldN++){
      TStr FldNm; TStr FldVal;
      CiaWFBCountry->GetFldNmVal(FldN, FldNm, FldVal);
      TStr SecFldNm=CiaWFBCountry->GetSecNm(FldNm);
      //printf("%d. '%s' - '%s': '%s'\n",
      // FldN, SecFldNm.CStr(), FldNm.CStr(), FldVal.CStr());
      fprintf(fOut, "%s\t%s\t%s\t%s\n",
       CountryNm.CStr(), SecFldNm.CStr(), FldNm.CStr(), FldVal.CStr());
    }
    //printf("\n");
  }}


  PCiaWFBCountry CiaWFBCountry=CiaWFBBs->GetCountry("Slovenia");
  CiaWFBCountry->GetFldValNum("Population");
  CiaWFBCountry->GetFldValNum("GDP - per capita");

  return 0;
  Catch;
  return 1;
}

