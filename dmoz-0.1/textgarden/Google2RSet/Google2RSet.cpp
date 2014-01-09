#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Google Search To Result-Set", 1);
  TStr WebQueryStr=Env.GetIfArgPrefixStr("-iwq:", "", "Google-Web-Query-String");
  TStr NewsQueryStr=Env.GetIfArgPrefixStr("-inq:", "", "Google-News-Query-String");
  TStr ScholarQueryStr=Env.GetIfArgPrefixStr("-isq:", "", "Google-Scholar-Query-String");
  TStr ScholarAuthorQueryStr=Env.GetIfArgPrefixStr("-isaq:", "", "Google-Scholar-Author-Query-String");
  TStr ScholarPublicationQueryStr=Env.GetIfArgPrefixStr("-ispq:", "", "Google-Scholar-Publication-Query-String");
  TStr InWebFNm=Env.GetIfArgPrefixStr("-iwf:", "", "Input-Web-Html-Google-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-oxml:", "Google.Xml", "Output-ResultSet-Xml-File");
  TStr OutBinFNm=Env.GetIfArgPrefixStr("-obin:", "Google.RSet", "Output-ResultSet-Binary-File");
  TStr OutBowFNm=Env.GetIfArgPrefixStr("-obow:", "Google.Bow", "Output-ResultSet-BagOfWords-File");
  int MxHits=Env.GetIfArgPrefixInt("-hits:", -1, "Maximal-Number-Of-Hits");
  if (Env.IsEndOfRun()){return 0;}

  // creating result-set
  PRSet RSet;
  PGgSchRSet SchRSet;
  if (!InWebFNm.Empty()){
    RSet=TRSet::NewWeb("", TStr::LoadTxt(InWebFNm));
  } else
  if (!WebQueryStr.Empty()){
    RSet=TGg::WebSearch(WebQueryStr, MxHits);
  } else
  if (!NewsQueryStr.Empty()){
    RSet=TGg::NewsSearch(NewsQueryStr);
  } else
  if (!ScholarQueryStr.Empty()){
    SchRSet=TGg::ScholarSearch(ScholarQueryStr);
  } else
  if (!ScholarAuthorQueryStr.Empty()){
    SchRSet=TGg::ScholarAuthorSearch(ScholarAuthorQueryStr);
  } else
  if (!ScholarPublicationQueryStr.Empty()){
    SchRSet=TGg::ScholarPublicationSearch(ScholarPublicationQueryStr);
  }

  // saving result-set
  if (!RSet.Empty()){
    if (!OutXmlFNm.Empty()){
      TRSet::SaveXml(OutXmlFNm, RSet);}
    if (!OutBinFNm.Empty()){
      TRSet::SaveBin(OutBinFNm, RSet);}
    if (!OutBowFNm.Empty()){
      PBowDocBs BowDocBs=RSet->GetBowDocBs();
      BowDocBs->SaveBin(OutBowFNm);
    }
  }
  // saving scholar-result-set
  if (!SchRSet.Empty()){
    if (!OutXmlFNm.Empty()){
      TGgSchRSet::SaveXml(OutXmlFNm, SchRSet);}
    if (!OutBinFNm.Empty()){
      TGgSchRSet::SaveBin(OutBinFNm, SchRSet);}
    if (!OutBowFNm.Empty()){
      PBowDocBs BowDocBs=SchRSet->GetBowDocBs();
      BowDocBs->SaveBin(OutBowFNm);
    }
  }

  return 0;
  Catch;
  return 1;
}

