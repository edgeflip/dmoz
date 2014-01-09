#include "base.h"
#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Bag-Of-Words To Keywords", 0);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "../Deploy/Pub.Bow", "Input-BagOfWords-FileName");
  TStr OutKWordTxtFNm=Env.GetIfArgPrefixStr("-ot:", "Keywords.Txt", "Keywords-Output-Text-File");
  TStr OutKWordXmlFNm=Env.GetIfArgPrefixStr("-ox:", "Keywords.Xml", "Keywords-Output-Xml-File");
  TStr OutKWordBinFNm=Env.GetIfArgPrefixStr("-ob:", "Keywords.KWord", "Keywords-Output-Binary-File");
  if (Env.IsEndOfRun()){return 0;}

  // preparing bag-of-words
  printf("Loading Bow '%s' ... ", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf("Done.\n");
  printf("Generating Bow-Weights ... ");
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF);
  printf("Done.\n");
  PBowSim BowSim=TBowSim::New(bstCos);

  printf("Generating Document Lists... ");
  TIntIntVH CIdToDidVH;
  int Docs=BowDocBs->GetDocs();
  for (int DId=0; DId<Docs; DId++){
    int DocCIds=BowDocBs->GetDocCIds(DId);
    for (int DocCIdN=0; DocCIdN<DocCIds; DocCIdN++){
      int CId=BowDocBs->GetDocCId(DId, DocCIdN);
      CIdToDidVH.AddDat(CId).Add(DId);
    }
  }
  printf("Done.\n");

  // generating keywords
  printf("Generating Keywords ...\n");
  PBowKWordBs KWordBs=TBowKWordBs::New();
  for (int CIdN=0; CIdN<CIdToDidVH.Len(); CIdN++){
    // get category-data
    int CId=CIdToDidVH.GetKey(CIdN);
    TStr CatNm=BowDocBs->GetCatNm(CId);
    TIntV& CatDIdV=CIdToDidVH[CIdN];
    printf("[%s] ", CatNm.CStr());
    // centroid keywords
    PBowSpV ConceptSpV=TBowClust::GetConceptSpV(BowDocWgtBs, BowSim, CatDIdV);
    PBowKWordSet ConceptKWordSet=ConceptSpV->GetKWordSet(BowDocBs);
    ConceptKWordSet->PutNm(CatNm+"/"+"Centroid");
    KWordBs->AddKWordSet(ConceptKWordSet);
    // svm-model keywords
    PBowKWordSet SvmMdKWordSet=TBowKWordSet::New();
    {double SvmC=1.0; double SvmJ=1.0;
    TIntV AllDIdV; BowDocBs->GetAllDIdV(AllDIdV);
    PBowMd BowMd=TBowSVMMd::NewClsLinear(BowDocBs, BowDocWgtBs, CatNm, AllDIdV, SvmC, SvmJ);
    TFltStrPrV WWgtWStrPrV; double Tsh;
    BowMd->GetLinComb(BowDocBs, WWgtWStrPrV, Tsh);
    for (int WordN=0; WordN<WWgtWStrPrV.Len(); WordN++){
      TStr WStr=WWgtWStrPrV[WordN].Val2;
      double WWgt=WWgtWStrPrV[WordN].Val1;
      SvmMdKWordSet->AddKWord(WStr, WWgt);
    }}
    SvmMdKWordSet->PutNm(CatNm+"/"+"SvmModel");
    KWordBs->AddKWordSet(SvmMdKWordSet);
  }
  printf("\nDone.\n");

  // save keywords
  printf("Saving Keywords as Text-File '%s' ... ", OutKWordTxtFNm.CStr());
  KWordBs->SaveTxt(OutKWordTxtFNm);
  printf("Done.\n");
  printf("Saving Keywords as Xml-File '%s' ... ", OutKWordXmlFNm.CStr());
  KWordBs->SaveXml(OutKWordXmlFNm);
  printf("Done.\n");
  printf("Saving Keywords as Binary-File '%s' ... ", OutKWordBinFNm.CStr());
  KWordBs->SaveBin(OutKWordBinFNm);
  printf("Done.\n");

  return 0;
  Catch;
  return 1;
}