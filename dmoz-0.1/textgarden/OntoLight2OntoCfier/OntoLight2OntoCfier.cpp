#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Ontology-Light To Ontology-Classifier", 0);
  TStr InOntoLightFNm=Env.GetIfArgPrefixStr("-iol:", "f:/Data/OntoLight/EuroVoc.OntoLight", "Input-OntoLight-FileName");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "f:/Data/OntoLight/Acquis.Bow", "Input-BagOfWords-FileName");
  TStr OutOntoCfierFNm=Env.GetIfArgPrefixStr("-oom:", "f:/Data/OntoLight/EuroVoc.OntoCfier", "Output-OntoClassifier-FileName");
  TStr OutOntoCfierTxtFNm=Env.GetIfArgPrefixStr("-oom:", "f:/Data/OntoLight/EuroVoc.OntoCfier.Txt", "Output-OntoClassifier-Text-FileName");
  TStr LangNm=Env.GetIfArgPrefixStr("-lang:", "EN", "Language-Name");
  bool DocCatIsTermIdP=Env.GetIfArgPrefixBool("-catisid:", true, "DocumentCategory-Is-TermId");
  double CutWordWgtSumPrc=Env.GetIfArgPrefixFlt("-cwwprc:", 0.33, "Cut-Word-Weight-Sum-Percent");
  if (Env.IsEndOfRun()){return 0;}
/*  InOntoLightFNm="f:/Data/OntoLight/Asfa.OntoLight";
  InBowFNm="f:/Data/OntoLight/Asfa.Bow";
  OutOntoCfierFNm="f:/Data/OntoLight/Asfa.OntoCfier";
  OutOntoCfierTxtFNm="f:/Data/OntoLight/Asfa.OntoCfier.Txt";
  DocCatIsTermIdP=false;*/

  printf("Loading Onto-Light from '%s' ...", InOntoLightFNm.CStr());
  PLwOnto LwOnto=TLwOnto::LoadBin(InOntoLightFNm);
  printf(" Done.\n");

  printf("Loading Bag-Of-Words from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf(" Done.\n");

  // generate ontology-classifier
  PLwOntoCfier LwOntoCfier=TLwOntoCfier::GetOntoCfier(
   LwOnto, BowDocBs, LangNm, DocCatIsTermIdP, CutWordWgtSumPrc);

  printf("Saving Onto-Classifier to '%s' ...", OutOntoCfierFNm.CStr());
  LwOntoCfier->SaveBin(OutOntoCfierFNm);
  printf(" Done.\n");

  printf("Saving Text to '%s' ...", OutOntoCfierTxtFNm.CStr());
  LwOntoCfier->SaveTxt(OutOntoCfierTxtFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}
