#include "mine.h"
#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("DMoz-Links To Contexts-Result-Sets");
  TStr InFPath=Env.GetIfArgPrefixStr("-i:", "", "Input-File-Path");
  TStr OutFPath=Env.GetIfArgPrefixStr("-o:", "", "Output-File-Path");
  TStr InDMozBinFBase=Env.GetIfArgPrefixStr("-ib:", TDMozInfo::BinFullFBase, "Input-DMoz-Binary-FileName");
  TStr RootCatNm=Env.GetIfArgPrefixStr("-c:", "Top/Science", "Root-Category-Name");
  bool ContCollectingP=Env.GetIfArgPrefixBool("-cont:", true, "Continue-Collecting");
  bool LinkCtxP=Env.GetIfArgPrefixBool("-linkctx:", true, "Retrieve-Link-Context");
  bool RelatedCtxP=Env.GetIfArgPrefixBool("-relatedctx:", true, "Related-Related-Context");
  int MxHits=Env.GetIfArgPrefixInt("-hits", 50, "Maximum-Number-Of-Context-Hits");
  int DelayMSecs=Env.GetIfArgPrefixInt("-delay", 0, "Delay-Between-Requests-Milisecs");
  if (Env.IsEndOfRun()){return 0;}

  // load DMoz-Base
  PDMozBs DMozBs=TDMozBs::LoadBin(InDMozBinFBase, InFPath);

  // prepare url-context-filename
  TStr OutCtxRSetsFNm=
   TStr::GetNrFPath(OutFPath)+TStr::GetFNmStr(RootCatNm, true)+".Ctx.RSets";
  // prepare existing url-hash-table
  TStrH CtxUrlStrH;
  // collect urls from existing url-contexts
  if (TFile::Exists(OutCtxRSetsFNm)&&ContCollectingP){
    printf("Loading already collected contexts ...\n");
    TFIn RSetsSIn(OutCtxRSetsFNm);
    while (!RSetsSIn.Eof()){
      printf("%d\r", CtxUrlStrH.Len());
      PRSet RSet(RSetsSIn);
      TStr QueryStr=RSet->GetQueryStr();
      CtxUrlStrH.AddKey(RSet->GetQueryStr());
    }
    printf("\nDone.\n");
  }
  // add new url-contexts to file
  TFOut CtxRSetsSOut(OutCtxRSetsFNm, ContCollectingP);
  TStrV SubCatNmV; TIntV CatIdV;
  //DMozBs->GetSubTreeCatIdV(RootCatNm, SubCatNmV, CatIdV);
  TIntV ExtUrlIdV; DMozBs->GetExtUrlIdV(CatIdV, ExtUrlIdV);
  for (int ExtUrlIdN=0; ExtUrlIdN<ExtUrlIdV.Len(); ExtUrlIdN++){
    int ExtUrlId=ExtUrlIdV[ExtUrlIdN];
    TStr UrlStr=DMozBs->GetExtUrlStr(ExtUrlId);
    TStr LinkCtxUrlStr=TStr("link:")+UrlStr;
    TStr RelatedCtxUrlStr=TStr("related:")+UrlStr;
    if ((LinkCtxP)&&(!CtxUrlStrH.IsKey(LinkCtxUrlStr))){
      printf("%d/%d: %s", 1+ExtUrlIdN, ExtUrlIdV.Len(), LinkCtxUrlStr.CStr());
      PRSet CtxRSet=TGg::WebSearch(LinkCtxUrlStr, MxHits);
      CtxRSet.Save(CtxRSetsSOut); CtxRSetsSOut.Flush();
      CtxUrlStrH.AddKey(LinkCtxUrlStr);
      printf(" (%d hits)\n", CtxRSet->GetHits());
      TSysProc::Sleep(DelayMSecs);
    }
    if ((RelatedCtxP)&&(!CtxUrlStrH.IsKey(RelatedCtxUrlStr))){
      printf("%d/%d: %s", 1+ExtUrlIdN, ExtUrlIdV.Len(), RelatedCtxUrlStr.CStr());
      PRSet CtxRSet=TGg::WebSearch(RelatedCtxUrlStr, MxHits);
      CtxRSet.Save(CtxRSetsSOut); CtxRSetsSOut.Flush();
      CtxUrlStrH.AddKey(RelatedCtxUrlStr);
      printf(" (%d hits)\n", CtxRSet->GetHits());
      TSysProc::Sleep(DelayMSecs);
    }
  }

  return 0;
  Catch;
  return 1;
}

