#include "net.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("IP To Geo-Location", 1);
  TStr IpNumStr=Env.GetIfArgPrefixStr("-ip:", "", "IP-Number-String");
  TStr GeoIpFNm=Env.GetIfArgPrefixStr("-ig:", "Country.GeoIp", "GeoIP-FileName");
  if (Env.IsEndOfRun()){return 0;}

  PGeoIpBs GeoIpBs=TGeoIpBs::LoadBin(GeoIpFNm);
  TStr CountrySNm; TStr CountryLNm;
  GeoIpBs->GetCountryNm(IpNumStr, CountrySNm, CountryLNm);
  printf("'%s' -> '%s' / '%s'\n",
   IpNumStr.CStr(), CountrySNm.CStr(), CountryLNm.CStr());

  return 0;
  Catch;
  return 1;
}

