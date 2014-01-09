#include "net.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Text-GeoIP To Binary-GeoIP", 0);
  TStr InGeoIpTxtFNm=Env.GetIfArgPrefixStr("-it:", "GeoIPCountryWhois.csv", "Input-GeoIP-Text-FileName");
  TStr OutGeoIpBinFNm=Env.GetIfArgPrefixStr("-ob:", "Country.GeoIp", "Input-GeoIP-Binary-FileName");
  if (Env.IsEndOfRun()){return 0;}

  PGeoIpBs GeoIpBs=TGeoIpBs::LoadTxt(InGeoIpTxtFNm);
  GeoIpBs->SaveBin(OutGeoIpBinFNm);

  return 0;
  Catch;
  return 1;
}

