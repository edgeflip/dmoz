#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("DMoz-Topic To Text", -1);
  TStr InFPath=Env.GetIfArgPrefixStr("-i:", "", "Input-File-Path");
  TStr OutFPath=Env.GetIfArgPrefixStr("-o:", "", "Output-File-Path");
  TStr RootCatNm=Env.GetIfArgPrefixStr("-c:", "Top/Science", "Root-Category-Name");
  if (Env.IsEndOfRun()){return 0;}

  // load DMoz-Base
  PDMozBs DMozBs=TDMozBs::LoadBin(TDMozInfo::BinFullFBase, InFPath);

  // assign root category name
  //RootCatNm="Top/Computers/Software/Databases/Data_Mining";
  //RootCatNm="Top/Reference/Knowledge_Management/Knowledge_Discovery";
  //RootCatNm="Top/Computers/Artificial_Intelligence/Machine_Learning";
  //RootCatNm="Top/Computers/Artificial_Intelligence";
  //RootCatNm="Top/Recreation/Travel";

  // get root category-id
  int RootCatId=DMozBs->GetCatId(RootCatNm);
  // prepare external-url list
  TStr RootFBase=TStr::GetFNmStr(RootCatNm, true);
  TStr ExtUrlFNm=TStr::GetNrFPath(OutFPath)+RootFBase+"_ExternalUrlList.Txt";
  TFOut ExtUrlSOut(ExtUrlFNm); FILE* fExtUrlOut=ExtUrlSOut.GetFileId();
  // get topic categories
  TIntV TopicCatIdV; DMozBs->GetSubCatIdV(RootCatId, TopicCatIdV);
  for (int TopicCatIdN=0; TopicCatIdN<TopicCatIdV.Len(); TopicCatIdN++){
    // get topic id & name
    int TopicCatId=TopicCatIdV[TopicCatIdN];
    TStr TopicCatNm=DMozBs->GetCatNm(TopicCatId);
    // get subtopic subtrees and corresponding external-url-ids
    TIntV SubCatIdV; TIntV CatIdV;
    //DMozBs->GetSubTreeCatIdV(TopicCatId, SubCatIdV, CatIdV, true);
    TIntV ExtUrlIdV; DMozBs->GetExtUrlIdV(CatIdV, ExtUrlIdV);
    // output url/titles/descriptions
    TStr TopicFBase=TStr::GetFNmStr(TopicCatNm, true);
    TStr TopicFNm=TStr::GetNrFPath(OutFPath)+TopicFBase+".Txt";
    printf("Saving %s\n", TopicFNm.CStr());
    TFOut TopicSOut(TopicFNm); FILE* fTopicOut=TopicSOut.GetFileId();
    for (int ExtUrlIdN=0; ExtUrlIdN<ExtUrlIdV.Len(); ExtUrlIdN++){
      int ExtUrlId=ExtUrlIdV[ExtUrlIdN];
      TStr UrlStr=DMozBs->GetExtUrlStr(ExtUrlId);
      TStr TitleStr=DMozBs->GetExtUrlTitleStr(ExtUrlId);
      TStr DescStr=DMozBs->GetExtUrlDescStr(ExtUrlId);
      fprintf(fExtUrlOut, "%s\n", UrlStr.CStr());
      fprintf(fTopicOut, "%s - %s\n", TitleStr.CStr(), DescStr.CStr());
    }
  }
  return 0;
  Catch;
  return 1;
}

