#include "mine.h"

/////////////////////////////////////////////////
// Light-Weight-Ontology
ClassTP(TLwOntoJoint, PLwOntoJoint)//{
private:
  PLwOntoCfier OntoCfier1;
  PLwOntoCfier OntoCfier2;
  TStrIntPrH NrWordStrToWId1WId2PrH;
  TIntIntH WId1ToJointWIdH;
  TIntIntH WId2ToJointWIdH;
  UndefCopyAssign(TLwOntoJoint);
public:
  TLwOntoJoint(){}
  static PLwOntoJoint New(
   const PLwOntoCfier& OntoCfier1, const PLwOntoCfier& OntoCfier2){
    PLwOntoJoint OntoJoint=new TLwOntoJoint();
    OntoJoint->OntoCfier1=OntoCfier1; OntoJoint->OntoCfier2=OntoCfier2;
    return OntoJoint;}
  TLwOntoJoint(TSIn& SIn):
    OntoCfier1(SIn), OntoCfier2(SIn){}
  static PLwOntoJoint Load(TSIn& SIn){return new TLwOntoJoint(SIn);}
  void Save(TSOut& SOut) const {
    OntoCfier1.Save(SOut); OntoCfier2.Save(SOut);}

  // componets
  PLwOntoCfier GetOntoCfier1() const {return OntoCfier1;}
  PLwOntoCfier GetOntoCfier2() const {return OntoCfier2;}

  // merge ontologies
  void JoinWordStrs();
  void FindSimTerms();

  // files
  static PLwOntoJoint LoadBin(const TStr& FNm){
    TFIn SIn(FNm); return Load(SIn);}
  void SaveBin(const TStr& FNm){
    TFOut SOut(FNm); Save(SOut);}
  void SaveTxt(const TStr& FNm);
};

void TLwOntoJoint::JoinWordStrs(){
  printf("Join Word-Strings ...\n");
  // shortcuts
  PBowDocBs BowDocBs1=OntoCfier1->GetBowDocBs();
  PBowDocBs BowDocBs2=OntoCfier2->GetBowDocBs();
  PStemmer Stemmer=TStemmer::GetStemmer(stmtPorter);
  // prepare common-vocabulary
  NrWordStrToWId1WId2PrH.Gen(BowDocBs1->GetWords()+BowDocBs2->GetWords());
  WId1ToJointWIdH.Gen(BowDocBs1->GetWords());
  WId2ToJointWIdH.Gen(BowDocBs2->GetWords());
  // normalize words-1
  printf("  Normalize Words-1 ...\n");
  for (int WId=0; WId<BowDocBs1->GetWords(); WId++){
    if (WId%10000==0){printf("    %d/%d\r", WId, BowDocBs1->GetWords());}
    if (!BowDocBs1->IsWId(WId)){continue;}
    TStr WStr=BowDocBs1->GetWordStr(WId);
    // normalize word
    TStrV SubWStrV; WStr.SplitOnAllCh('_', SubWStrV, false);
    TChA NrWChA;
    for (int SubWStrN=0; SubWStrN<SubWStrV.Len(); SubWStrN++){
      if (SubWStrN>0){NrWChA+='_';}
      NrWChA+=Stemmer->GetStem(SubWStrV[SubWStrN]);
    }
    TStr NrWStr=NrWChA;
    // add normalized word
    if (!NrWordStrToWId1WId2PrH.IsKey(NrWStr)){
      NrWordStrToWId1WId2PrH.AddDat(NrWStr, TIntPr(-1, -1));
      NrWordStrToWId1WId2PrH.AddDat(NrWStr).Val1=WId;
    }
    int JointWId=NrWordStrToWId1WId2PrH.GetKeyId(NrWStr);
    WId1ToJointWIdH.AddDat(WId, JointWId);
  }
  printf("    %d/%d\n", BowDocBs1->GetWords(), BowDocBs1->GetWords());
  printf("  Done.\n");

  // normalize words-2
  printf("  Normalize Words-2 ...\n");
  for (int WId=0; WId<BowDocBs2->GetWords(); WId++){
    if (WId%10000==0){printf("    %d/%d\r", WId, BowDocBs2->GetWords());}
    if (!BowDocBs2->IsWId(WId)){continue;}
    TStr WStr=BowDocBs2->GetWordStr(WId);
    // normalize word
    TStrV SubWStrV; WStr.SplitOnAllCh('_', SubWStrV, false);
    TChA NrWChA;
    for (int SubWStrN=0; SubWStrN<SubWStrV.Len(); SubWStrN++){
      if (SubWStrN>0){NrWChA+='_';}
      NrWChA+=Stemmer->GetStem(SubWStrV[SubWStrN]);
    }
    TStr NrWStr=NrWChA;
    // add normalized word
    if (NrWordStrToWId1WId2PrH.IsKey(NrWStr)){
      if (NrWordStrToWId1WId2PrH.GetDat(NrWStr).Val2==-1){
        NrWordStrToWId1WId2PrH.AddDat(NrWStr).Val2=WId;
      }
    } else {
      NrWordStrToWId1WId2PrH.AddDat(NrWStr, TIntPr(-1, -1));
      NrWordStrToWId1WId2PrH.AddDat(NrWStr).Val2=WId;
    }
    int JointWId=NrWordStrToWId1WId2PrH.GetKeyId(NrWStr);
    WId2ToJointWIdH.AddDat(WId, JointWId);
  }
  printf("    %d/%d\n", BowDocBs2->GetWords(), BowDocBs2->GetWords());
  printf("  Done.\n");

  /*// dump words differences
  for (int NrWordN=0; NrWordN<NrWordStrToWId1WId2PrH.Len(); NrWordN++){
    int WId1=NrWordStrToWId1WId2PrH[NrWordN].Val1;
    int WId2=NrWordStrToWId1WId2PrH[NrWordN].Val2;
    if ((WId1!=-1)&&(WId2!=-1)){
      TStr WStr1=BowDocBs1->GetWordStr(WId1);
      TStr WStr2=BowDocBs2->GetWordStr(WId2);
      if (WStr1==WStr2){
      } else {
        printf("('%s'!='%s') ", WStr1.CStr(), WStr2.CStr());
      }
    }
  }*/
  printf("Done.\n");
}

void TLwOntoJoint::FindSimTerms(){
  // shortcuts
  PBowDocBs BowDocBs1=OntoCfier1->GetBowDocBs();
  PBowDocBs BowDocBs2=OntoCfier2->GetBowDocBs();
  PLwTermBs TermBs1=OntoCfier1->GetLwOnto()->GetTermBs();
  PLwTermBs TermBs2=OntoCfier2->GetLwOnto()->GetTermBs();

  // translate concept-vectors-1 into vocabulary-2
  printf("Translating concept vectors ...");
  THash<TInt, PBowSpV> TermId1ToConceptSpV1In2H;
  for (int TermN1=0; TermN1<TermBs1->GetTerms(); TermN1++){
    int TermId1=TermBs1->GetTermId(TermN1);
    if (OntoCfier1->IsConceptSpV(TermId1)){
      PBowSpV ConceptSpV1=OntoCfier1->GetConceptSpV(TermId1);
      PBowSpV ConceptSpV2=TBowSpV::New(-1, ConceptSpV1->GetWIds());
      for (int WIdN=0; WIdN<ConceptSpV1->GetWIds(); WIdN++){
        int WId1; double Wgt; ConceptSpV1->GetWIdWgt(WIdN, WId1, Wgt);
        int JointWId=WId1ToJointWIdH.GetDat(WId1);
        int WId2=NrWordStrToWId1WId2PrH[JointWId].Val2;
        if (WId2!=-1){
          ConceptSpV2->AddWIdWgt(WId2, Wgt);}
      }
      if (ConceptSpV2->GetWIds()>0){
        ConceptSpV2->PutUnitNorm();
        TermId1ToConceptSpV1In2H.AddDat(TermId1, ConceptSpV2);
      }
    }
  }
  printf("Done.\n");

  {printf("Joining concepts...\n");
  TFOut FOut("OntoJoint.Txt"); FILE* fOut=FOut.GetFileId();
  PBowSim BowSim=TBowSim::New(bstCos);
  for (int TermN1=0; TermN1<TermBs1->GetTerms(); TermN1++){
    printf("  %d/%d\r", 1+TermN1, TermBs1->GetTerms());
    int TermId1=TermBs1->GetTermId(TermN1);
    if (TermId1ToConceptSpV1In2H.IsKey(TermId1)){
      PBowSpV ConceptSpV1In2=TermId1ToConceptSpV1In2H.GetDat(TermId1);
      TFltIntPrV SimTermId2PrV(TermBs2->GetTerms(), 0);
      typedef TTriple<TFlt, TInt, TFltIntPrV> TSimTermId2WWPrVTr;
      TVec<TSimTermId2WWPrVTr> SimTermId2WWPrVTrV(TermBs2->GetTerms(), 0);
      for (int TermN2=0; TermN2<TermBs2->GetTerms(); TermN2++){
        int TermId2=TermBs2->GetTermId(TermN2);
        if (OntoCfier2->IsConceptSpV(TermId2)){
          PBowSpV ConceptSpV2=OntoCfier2->GetConceptSpV(TermId2);
          TFltIntPrV IntsWgtWIdPrV;
          double Sim=BowSim->GetCosSim(ConceptSpV1In2, ConceptSpV2, IntsWgtWIdPrV);
          if (IntsWgtWIdPrV.Len()<5){Sim=0;}
          if (Sim>0){
            SimTermId2WWPrVTrV.Add(TSimTermId2WWPrVTr(Sim, TermId2, IntsWgtWIdPrV));}
        }
      }
      if (SimTermId2WWPrVTrV.Len()>0){
        SimTermId2WWPrVTrV.Sort(false);
        SimTermId2WWPrVTrV.Trunc(10);
        TStr TermNm1=TermBs1->GetTerm(TermId1)->GetTermNm();
        fprintf(fOut, "'%s'\n", TermNm1.CStr());
        for (int TermIdN2=0; TermIdN2<SimTermId2WWPrVTrV.Len(); TermIdN2++){
          double Sim=SimTermId2WWPrVTrV[TermIdN2].Val1;
          int TermId2=SimTermId2WWPrVTrV[TermIdN2].Val2;
          TFltIntPrV& IntsWgtWIdPrV=SimTermId2WWPrVTrV[TermIdN2].Val3;
          TStr TermNm2=TermBs2->GetTerm(TermId2)->GetTermNm();
          fprintf(fOut, "   %2d. '%s' (%.3f)", 1+TermIdN2, TermNm2.CStr(), Sim);
          IntsWgtWIdPrV.Sort(false); IntsWgtWIdPrV.Trunc(10);
          for (int WordN=0; WordN<IntsWgtWIdPrV.Len(); WordN++){
            double WWgt=IntsWgtWIdPrV[WordN].Val1;
            int WId=IntsWgtWIdPrV[WordN].Val2;
            TStr WStr=BowDocBs2->GetWordStr(WId);
            fprintf(fOut, " [%s:%.3f]", WStr.CStr(), WWgt);
          }
          fprintf(fOut, "\n");
        }
      }
    }
  }
  printf("\nDone.\n");}
}

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Join-Ontologies", 0);
  TStr InOntoCfierFNm1=Env.GetIfArgPrefixStr("-ioc1:", "f:/Data/OntoLight/EuroVoc.OntoCfier", "Input-OntoClassifier-FileName-1");
  TStr InOntoCfierFNm2=Env.GetIfArgPrefixStr("-ioc2:", "f:/Data/OntoLight/Asfa.OntoCfier", "Input-OntoClassifier-FileName-2");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "OntoJoint.Xml", "Output-OntologyJoin-Xml-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "OntoJoint.Txt", "Output-OntologyJoin-Txt-File");
  if (Env.IsEndOfRun()){return 0;}

  printf("Loading Onto-Classifier-1 from '%s' ...", InOntoCfierFNm1.CStr());
  PLwOntoCfier OntoCfier1=TLwOntoCfier::LoadBin(InOntoCfierFNm1);
  printf(" Done.\n");

  printf("Loading Onto-Classifier-2 from '%s' ...", InOntoCfierFNm2.CStr());
  PLwOntoCfier OntoCfier2=TLwOntoCfier::LoadBin(InOntoCfierFNm2);
  printf(" Done.\n");

//  PLwOntoJoint OntoJoint=TLwOntoJoint::New(OntoCfier1, OntoCfier2);
//  OntoJoint->JoinWordStrs();
//  OntoJoint->FindSimTerms();

  return 0;
  Catch;
  return 1;
}
