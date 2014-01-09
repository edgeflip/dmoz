#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Ontology-Classify", 0);
  TStr InOntoCfierFNm=Env.GetIfArgPrefixStr("-ioc:", "f:/Data/OntoLight/EuroVoc.OntoCfier", "Input-OntoClassifier-FileName");
  TStr InQueryStr=Env.GetIfArgPrefixStr("-qs:", "Slovenia and Croatia are having a fishing industry.", "Input-Query-String");
  TStr InQueryHtmlFNm=Env.GetIfArgPrefixStr("-qh:", "", "Input-Query-Html-File");
  TStr InQueryCpdFNm=Env.GetIfArgPrefixStr("-qcpd:", "", "Input-Query-CompactDocument-FileName");
  TStr InQueryUrlStr=Env.GetIfArgPrefixStr("-qu:", "", "Input-Query-Url");
  TStr InQueryUrlStrVFNm=Env.GetIfArgPrefixStr("-quf:", "", "Input-Query-URL-Vector-FileName");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "OntoCfy.Xml", "Output-Classification-Xml-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "OntoCfy.Txt", "Output-Classification-Txt-File");
  if (Env.IsEndOfRun()){return 0;}
//  InQueryStr="Slovenia and Croatia are having a fishing industry.";

  printf("Loading Onto-Classifier from '%s' ...", InOntoCfierFNm.CStr());
  PLwOntoCfier OntoCfier=TLwOntoCfier::LoadBin(InOntoCfierFNm);
  printf(" Done.\n");

  // process query
  TSimTermIdPrV SimTermIdPrV;
  if (!InQueryStr.Empty()){
    OntoCfier->ClassifyStr(InQueryStr, SimTermIdPrV);
  } else
  if (!InQueryHtmlFNm.Empty()){
    OntoCfier->ClassifyHtmlFNm(InQueryHtmlFNm, SimTermIdPrV);
  } else {
    TExcept::Throw("No Input-Query specified!");
  }

  // save to xml
  {TFOut FXml(OutXmlFNm); FILE* fXml=FXml.GetFileId();
  OntoCfier->SaveCfySetXml(fXml, SimTermIdPrV);}

  // save to txt
  {TFOut FTxt(OutTxtFNm); FILE* fTxt=FTxt.GetFileId();
  OntoCfier->SaveCfySetTxt(fTxt, SimTermIdPrV);}

  return 0;
  Catch;
  return 1;
}
