#include "mine.h"
#include "nmobj.h"

void GetKWordV(const TStr& NmObjConceptStr,
 const PBowDocBs& DMozBowDocBs, const PBowDocWgtBs& DMozBowDocWgtBs, 
 const PBowDocPart& DMozBowDocPart, const PBowSim DMozBowSim, 
 const int& DMozMxCats, const double& DMozKWordTsh, TStrFltPrV& NmObj_KWordStrWgtPrV){
  // get sparse-vector
  PBowSpV DMozBowSpV=DMozBowDocBs->GetSpVFromHtmlStr(NmObjConceptStr, DMozBowDocWgtBs);
  // classify sparse-vector
  TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV;
  TDMozBs::GetBestClustV(DMozBowDocPart, DMozBowSim, DMozBowSpV, DMozMxCats, WgtClustKdV, WgtWIdPrVV);
  TDMozBs::GetBestKWordV(WgtClustKdV, DMozKWordTsh, true, -1, -1, NmObj_KWordStrWgtPrV);
}

void SaveSpV(FILE* fTxt, FILE* fXml, 
 const PBowDocBs& BowDocBs, const TTm& MnDateTm, const TTm& MxDateTm,
 const TStr& NmObjNm, const TStr& SubNmObjNm, 
 const int& NmObjFq, const double& NmObjPrc, 
 const PBowSpV& SpV, const double& TopWordsWgtPrc, 
 const TStrFltPrV& KWordStrWgtPrV){
  TStr MnDateStr=MnDateTm.GetWebLogDateStr(); 
  TStr MxDateStr=MxDateTm.GetWebLogDateStr();
  TStr NmObjXmlNm=TXmlLx::GetXmlStrFromPlainStr(NmObjNm);
  TStr SubNmObjXmlNm=TXmlLx::GetXmlStrFromPlainStr(SubNmObjNm);
  // open tag
  if (SubNmObjNm.Empty()){
    fprintf(fTxt, "%s [%d] (%s:%s)", 
     NmObjNm.CStr(), NmObjFq, MnDateStr.CStr(), MxDateStr.CStr());
    fprintf(fXml, "<Instance Nm=\"%s\" Fq=\"%d\" Prc=\"%.5f\" MnDate=\"%s\" MxDate=\"%s\">",
     NmObjXmlNm.CStr(), NmObjFq, NmObjPrc, MnDateStr.CStr(), MxDateStr.CStr());
  } else {
    fprintf(fTxt, "   %s => %s [%d] (%s:%s)", 
     NmObjNm.CStr(), SubNmObjNm.CStr(), NmObjFq, MnDateStr.CStr(), MxDateStr.CStr());
    fprintf(fXml, "<Relation SrcNm=\"%s\" DstNm=\"%s\" Fq=\"%d\" Prc=\"%.5f\" MnDate=\"%s\" MxDate=\"%s\">",
     NmObjXmlNm.CStr(), SubNmObjXmlNm.CStr(), NmObjFq, NmObjPrc, MnDateStr.CStr(), MxDateStr.CStr());
  }
  fprintf(fXml, "\n");
  // keywords
  fprintf(fXml, "   ");
  for (int KWordN=0; KWordN<KWordStrWgtPrV.Len(); KWordN++){
    TStr KWordStr=KWordStrWgtPrV[KWordN].Val1;
    TStr KWordNm; TStr KWordLevStr; KWordStr.SplitOnLastCh(KWordNm, '-', KWordLevStr);
    int KWordLev=KWordLevStr.GetInt(999);
    TStr KWordXmlNm=TXmlLx::GetXmlStrFromPlainStr(KWordNm);
    double KWordWgt=KWordStrWgtPrV[KWordN].Val2;
    fprintf(fTxt, " [%s:%.3f]", KWordStr.CStr(), KWordWgt);
    fprintf(fXml, " <KWord Str=\"%s\" Lev=\"%d\" Wgt=\"%.3f\"/>", KWordXmlNm.CStr(), KWordLev, KWordWgt);
  }
  fprintf(fTxt, "\n");
  fprintf(fXml, "\n");
  // words
  if (SubNmObjNm.Empty()){
    fprintf(fTxt, "%s [%d] (%s:%s)", 
     NmObjNm.CStr(), NmObjFq, MnDateStr.CStr(), MxDateStr.CStr());
  } else {
    fprintf(fTxt, "   %s => %s [%d] (%s:%s)", 
     NmObjNm.CStr(), SubNmObjNm.CStr(), NmObjFq, MnDateStr.CStr(), MxDateStr.CStr());
  }
  TStrFltPrV WordStrWgtPrV; SpV->GetWordStrWgtPrV(BowDocBs, -1, TopWordsWgtPrc, WordStrWgtPrV);
  fprintf(fXml, "   ");
  for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
    TStr WordStr=WordStrWgtPrV[WordN].Val1;
    TStr WordXmlStr=TXmlLx::GetXmlStrFromPlainStr(WordStr);
    double WWgt=WordStrWgtPrV[WordN].Val2;
    fprintf(fTxt, " %s:%.3f", WordStr.CStr(), WWgt);
    fprintf(fXml, " <Word Str=\"%s\" Wgt=\"%.3f\"/>", WordXmlStr.CStr(), WWgt);
  }
  fprintf(fTxt, "\n");
  fprintf(fXml, "\n");
  // close tag
  if (SubNmObjNm.Empty()){
    fprintf(fXml, "</Instance>");
  } else {
    fprintf(fXml, "</Relation>");
  }
  fprintf(fXml, "\n");
}

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Named-Objects To Time-Profile", 0);
  TStr InTxtBowFNm=Env.GetIfArgPrefixStr("-itb:", "", "Input-Text-BagOfWords-FileName");
  TStr InNmObjFNm=Env.GetIfArgPrefixStr("-in:", "", "Input-NamedObjects-FileName");
  TStr InNmObjBowFNm=Env.GetIfArgPrefixStr("-inb:", "", "Input-NamedObjects-BagOfWords-FileName");
  TStr InDMozBowFNm=Env.GetIfArgPrefixStr("-idb:", "", "Input-DMoz-BagOfWords-FileName");
  TStr InDMozBowPartFNm=Env.GetIfArgPrefixStr("-idbp:", "", "Input-DMoz-BagOfWords-Partition-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "TimeProfile.Txt", "Output-TimeProfile-Txt-FileName");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "TimeProfile.Xml", "Output-TimeProfile-Xml-FileName");
  int MnNmObjFq=Env.GetIfArgPrefixInt("-mnnofq:", 100, "Minimum-NamedObjects-Frequency"); 
  double MnNmObjPrc=Env.GetIfArgPrefixFlt("-mnnop:", 0.01, "Minimum-NamedObjects-Documents-Percentage"); 
  double MnSubNmObjPrc=Env.GetIfArgPrefixFlt("-mnsnop:", 0.03, "Minimum-SubNamedObjects-Documents-Percentage"); 
  int DMozMxCats=Env.GetIfArgPrefixInt("-dmmxc:", 25, "DMoz-Maximum-Categories"); 
  double DMozKWordTsh=Env.GetIfArgPrefixFlt("-dmkwt:", 0.66, "DMoz-Keyword-Threshold"); 
  int TmProfileWnDays=Env.GetIfArgPrefixInt("-tpwn:", 10, "Time-Profile-Window-Size (Days)"); 
  int TmProfileStepDays=Env.GetIfArgPrefixInt("-tpstep:", 3, "Time-Profile-Step-Size (Days)"); 
  double ConceptTopWordsWgtPrc=Env.GetIfArgPrefixFlt("-ctwwp:", 0.5, "Concept-TopWordsWeight-Percentage"); 
  bool DumpP=Env.GetIfArgPrefixBool("-dump:", false, "Dump"); 
  if (Env.IsEndOfRun()){return 0;}

  InTxtBowFNm="/Data/Reuters2K/R2K-100K.Bow";
  InNmObjFNm="/Data/Reuters2K/R2K-100K.NmObj";
  InNmObjBowFNm="/Data/Reuters2K/R2K-100K.NmObj.Bow";
  InDMozBowFNm="/Data/DMoz/Top-En100.Bow";
  InDMozBowPartFNm="/Data/DMoz/Top-En100.BowPart";

  // loading input-files
  // text
  printf("Loading Text Bag-Of-Words File %s ...", InTxtBowFNm.CStr());
  PBowDocBs TxtBowDocBs=TBowDocBs::LoadBin(InTxtBowFNm);
  printf(" Done.\n");
  printf("Creating Text Bag-Of-Words-Weights ...");
  PBowDocWgtBs TxtBowDocWgtBs=TBowDocWgtBs::New(TxtBowDocBs, bwwtNrmTFIDF);
  printf(" Done.\n");

  // named-objects
  printf("Loading Named-Objects File %s ...", InNmObjFNm.CStr());
  PNmObjBs NmObjBs=TNmObjBs::LoadBin(InNmObjFNm);
  printf(" Done.\n");
  printf("Loading Named-Objects Bag-Of-Words File %s ...", InNmObjBowFNm.CStr());
  PBowDocBs NmObjBowDocBs=TBowDocBs::LoadBin(InNmObjBowFNm);
  printf(" Done.\n");
  printf("Creating Named-Objects Bag-Of-Words-Weights ...");
  PBowDocWgtBs NmObjBowDocWgtBs=TBowDocWgtBs::New(NmObjBowDocBs, bwwtNrmTFIDF);
  printf(" Done.\n");

  // dmoz
  printf("Loading DMoz Bag-Of-Words data from '%s' ...", InDMozBowFNm.CStr());
  PBowDocBs DMozBowDocBs=TBowDocBs::LoadBin(InDMozBowFNm);
  printf(" Done.\n");
  printf("Creating DMoz Bag-Of-Words-Weights ...");
  PBowDocWgtBs DMozBowDocWgtBs=TBowDocWgtBs::New(DMozBowDocBs, bwwtLogDFNrmTFIDF);
  printf(" Done.\n");
  printf("Loading DMoz Bag-Of-Words-Partition from '%s' ...", InDMozBowPartFNm.CStr());
  PBowDocPart DMozBowDocPart=TBowDocPart::LoadBin(InDMozBowPartFNm);
  PBowSim DMozBowSim=TBowSim::New(bstCos);
  printf(" Done.\n");

  printf("\n");

  // output files
  PSOut TxtSOut=TFOut::New(OutTxtFNm); FILE* fTxt=TxtSOut->GetFileId();
  PSOut XmlSOut=TFOut::New(OutXmlFNm); FILE* fXml=XmlSOut->GetFileId();

  // dates 
  printf("Extracting Dates ...\n");
  THash<TTm, TIntV> DateTmToDIdVH;
  TIntV AllDIdV; TxtBowDocBs->GetAllDIdV(AllDIdV);
  for (int DIdN=0; DIdN<AllDIdV.Len(); DIdN++){
    int DId=AllDIdV[DIdN];
    TStr DateTimeStr=TxtBowDocBs->GetDateStr(DId);
    TTm DateTimeTm=TTm::GetTmFromWebLogDateTimeStr(DateTimeStr);
    EAssertRA(DateTimeTm.IsDef(), "Date Information Expected", DateTimeStr);
    TStr DateStr=DateTimeTm.GetWebLogDateStr();
    TTm DateTm=TTm::GetTmFromWebLogDateTimeStr(DateStr);
    IAssert(DateTm.IsDef());
    DateTmToDIdVH.AddDat(DateTm).Add(DId);
  }
  TTmV DateTmV; DateTmToDIdVH.GetKeyV(DateTmV);
  TTm MnDateTm=DateTmV[0];
  TTm MxDateTm=DateTmV.Last();
  printf("   Minimal Date: %s\n", MnDateTm.GetWebLogDateStr().CStr());
  printf("   Maximal Date: %s\n", MxDateTm.GetWebLogDateStr().CStr());
  printf("Done.\n");

  // retrieve named-objects
  printf("Retrieving Named-Objects...\n");
  TIntStrPrV NmObjFqStrPrV; NmObjBs->GetNmObjFqStrPrV(NmObjFqStrPrV, MnNmObjFq);
  TStrV NmObjNmV;
  for (int NmObjIdN=0; NmObjIdN<NmObjFqStrPrV.Len(); NmObjIdN++){
    int NmObjFq=NmObjFqStrPrV[NmObjIdN].Val1;
    TStr NmObjNm=NmObjFqStrPrV[NmObjIdN].Val2;
    if (NmObjBs->IsNmObjAttr(NmObjNm, noaCountry)||(double(NmObjFq)/NmObjBs->GetDocs()>MnNmObjPrc)){
      NmObjNmV.Add(NmObjNm);
    }
  }
  printf("   %d Named Entities Selected\n", NmObjNmV.Len());
  printf("Done.\n");

  printf("Retrieving Named-Objects-Profiles...\n");
  for (int NmObjN=0; NmObjN<NmObjNmV.Len(); NmObjN++){
    TStr NmObjNm=NmObjNmV[NmObjN];
    int NmObjId=NmObjBs->GetNmObjId(NmObjNm);
    printf("%d/%d (%.1f%%) (%s)\n", 
     1+NmObjN, NmObjNmV.Len(), 100*double(1+NmObjN)/NmObjNmV.Len(), NmObjNm.CStr());
    // time-loop
    TTm MnTmProfileDateTm=MnDateTm;
    TTm MxTmProfileDateTm=MnTmProfileDateTm; MxTmProfileDateTm.AddDays(TmProfileWnDays);
    while (MxTmProfileDateTm<=MxDateTm){
      printf("Analysing Time-Period %s - %s\n", 
       MnTmProfileDateTm.GetWebLogDateStr().CStr(), MxTmProfileDateTm.GetWebLogDateStr().CStr());
      // collect profile doc-ids
      TIntV TmProfileDIdV;
      TTm CurTmProfileDateTm=MnTmProfileDateTm;
      while (CurTmProfileDateTm<=MxTmProfileDateTm){
        if (DateTmToDIdVH.IsKey(CurTmProfileDateTm)){
          TmProfileDIdV.AddV(DateTmToDIdVH.GetDat(CurTmProfileDateTm));}
        CurTmProfileDateTm.AddDays(1);
      }
      TmProfileDIdV.Sort();
      printf("Analysing %d Docs\n", TmProfileDIdV.Len());
      // named-object concept-vector
      TIntV NmObjDIdV; NmObjBs->GetNmObjDIdV(TxtBowDocBs, NmObjDIdV, NmObjNm);
      NmObjDIdV.Sort(); NmObjDIdV.Intrs(TmProfileDIdV);
      PBowSpV NmObjConceptSpV=TBowClust::GetConceptSpV(TxtBowDocWgtBs, NULL, NmObjDIdV);
      TStr NmObjConceptStr=NmObjConceptSpV->GetStr(TxtBowDocBs, -1, ConceptTopWordsWgtPrc, "<br>", false, false);
      // get dmoz keywords
      TStrFltPrV NmObj_KWordStrWgtPrV;
      GetKWordV(NmObjConceptStr, DMozBowDocBs, DMozBowDocWgtBs, DMozBowDocPart, 
       DMozBowSim, DMozMxCats, DMozKWordTsh, NmObj_KWordStrWgtPrV);
      // save concept-vector & keywords
      double NmObjPrc=double(NmObjDIdV.Len())/TmProfileDIdV.Len();
      SaveSpV(fTxt, fXml, TxtBowDocBs, MnTmProfileDateTm, MxTmProfileDateTm,
       NmObjNm, "", NmObjDIdV.Len(), NmObjPrc, 
       NmObjConceptSpV, ConceptTopWordsWgtPrc, NmObj_KWordStrWgtPrV);
      // traverse sub-named-objects
      for (int SubNmObjN=0; SubNmObjN<NmObjNmV.Len(); SubNmObjN++){
        if (NmObjN==SubNmObjN){continue;}
        TStr SubNmObjNm=NmObjNmV[SubNmObjN];
        int SubNmObjId=NmObjBs->GetNmObjId(SubNmObjNm);
        // sub-named-object concept-vector
        TIntV SubNmObjDIdV; NmObjBs->GetNmObjDIdV(TxtBowDocBs, SubNmObjDIdV, NmObjNm, SubNmObjNm);
        SubNmObjDIdV.Sort(); SubNmObjDIdV.Intrs(TmProfileDIdV);
        PBowSpV SubNmObjConceptSpV=TBowClust::GetConceptSpV(TxtBowDocWgtBs, NULL, SubNmObjDIdV);
        TStr SubNmObjConceptStr=SubNmObjConceptSpV->GetStr(TxtBowDocBs, -1, ConceptTopWordsWgtPrc, "<br>", false, false);
        double SubNmObjPrc=double(SubNmObjDIdV.Len())/NmObjDIdV.Len();
        if (SubNmObjPrc>=MnSubNmObjPrc){
          // get dmoz keywords
          TStrFltPrV SubNmObj_KWordStrWgtPrV;
          GetKWordV(SubNmObjConceptStr, DMozBowDocBs, DMozBowDocWgtBs, DMozBowDocPart, 
           DMozBowSim, DMozMxCats, DMozKWordTsh, SubNmObj_KWordStrWgtPrV);
          // save concept-vector & keywords
          SaveSpV(fTxt, fXml, TxtBowDocBs, MnTmProfileDateTm, MxTmProfileDateTm,
           NmObjNm, SubNmObjNm, SubNmObjDIdV.Len(), SubNmObjPrc, 
           SubNmObjConceptSpV, ConceptTopWordsWgtPrc, SubNmObj_KWordStrWgtPrV);
        }
      }
      // time-step
      MnTmProfileDateTm.AddDays(TmProfileStepDays); 
      MxTmProfileDateTm.AddDays(TmProfileStepDays);
    }
  }

  // close output
  TxtSOut=NULL;
  XmlSOut=NULL;

  return 0;
  Catch;
  return 1;
}