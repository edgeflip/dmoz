#include "mine.h"
#include "webtxtbs.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Text-Base Search");
  TStr InTBsFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-TextBase-FileName");
  TStr QueryStr=Env.GetIfArgPrefixStr("-q:", "", "Query");
  int HitDocs=Env.GetIfArgPrefixInt("-mxhits:", 10, "Max-Hits");
  int MxDocTitleLen=Env.GetIfArgPrefixInt("-mxdtl:", 65, "Max-Document-Title-Length");
  int MxDocCtxLen=Env.GetIfArgPrefixInt("-mxdcl:", 200, "Max-Document-Context-Length");
  if (Env.IsEndOfRun()){return 0;}

  // notification
  PNotify Notify=TNotify::StdNotify;

  // load text-base
  TStr TxtBsNm=InTBsFNm.GetFBase();
  TStr TxtBsFPath=InTBsFNm.GetFPath();
  PTxtBs TxtBs=TTxtBs::New(TxtBsNm, TxtBsFPath);

  // execute query
  PTxtBsRes TxtBsRes=TxtBs->Search(QueryStr);
  if (TxtBsRes->IsOk()){
    printf("Results for query: '%s'\n", TxtBsRes->GetWixExpStr().CStr());
    for (int DocN=0; DocN<TInt::GetMn(HitDocs, TxtBsRes->GetDocs()); DocN++){
      TStr DocNm; TStr DocTitleStr; TStr DocStr; TStr DocCtxStr;
      TxtBsRes->GetDocInfo(
       DocN, MxDocTitleLen, MxDocCtxLen, DocNm, DocTitleStr, DocStr, DocCtxStr);
      printf("-------------------------\n");
      printf("%d. %s\n", DocN+1, DocTitleStr.CStr());
      printf("%s\n", DocCtxStr.CStr());
      printf("[Document-Id: '%s']\n", DocNm.CStr());
    }
    if (TxtBsRes->GetDocs()>0){
      printf("---End-------------------\n");}
  } else {
    printf("Error: %s\n", TxtBsRes->GetErrMsg().CStr());
  }

  return 0;
  Catch;
  return 1;
}

