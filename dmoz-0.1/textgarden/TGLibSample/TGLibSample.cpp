#include "stdafx.h"
#include "../TextGardenLib/TextGardenLib.h"

/*
DLLExport int HtmlDoc_GetFromStr(char* HtmlStr);
DLLExport int HtmlDoc_GetFromFile(char* HtmlFNm);
DLLExport void HtmlDoc_Del(int HtmlDocId);

DLLExport int HtmlDoc_GetToks(int HtmlDocId);
DLLExport int HtmlDoc_GetTokSym(int HtmlDocId, int TokN);
DLLExport char* HtmlDoc_GetTokStr(int HtmlDocId, int TokN);
DLLExport char* HtmlDoc_GetTokFullStr(int HtmlDocId, int TokN);
DLLExport bool HtmlDoc_IsTokArg(int HtmlDocId, int TokN, char* ArgNm);
DLLExport char* HtmlDoc_GetTokArg(int HtmlDocId, int TokN, char* ArgNm, char* DfArgVal);
DLLExport bool HtmlDoc_IsTokUrl(int HtmlDocId, int TokN);
DLLExport char* HtmlDoc_GetTokUrlStr(int HtmlDocId, int TokN);
DLLExport bool HtmlDoc_IsBreakTag(char* TagNm);
DLLExport char* HtmlDoc_GetSymStr(int Sym);
*/

/*
/////////////////////////////////////////////////
// Url
DLLExport int Url_Get(char* RelUrlStr, char* BaseUrlStr);
DLLExport void Url_Del(int UrlId);

DLLExport bool Url_IsOk(int UrlId, int Scheme=0);
DLLExport bool Url_IsOkHttp(int UrlId);
DLLExport int Url_GetScheme(int UrlId);
DLLExport char* Url_GetUrlStr(int UrlId);
DLLExport char* Url_GetRelUrlStr(int UrlId);
DLLExport bool Url_IsBaseUrl(int UrlId);
DLLExport char* Url_GetBaseUrlStr(int UrlId);
DLLExport char* Url_GetSchemeNm(int UrlId);
DLLExport char* Url_GetHostNm(int UrlId);
DLLExport char* Url_GetDmNm(int UrlId, int MxDmSegs=-1);
DLLExport char* Url_GetPortStr(int UrlId);
DLLExport int Url_GetPortN(int UrlId);
DLLExport char* Url_GetPathStr(int UrlId);
DLLExport int Url_GetPathSegs(int UrlId);
DLLExport char* Url_GetPathSeg(int UrlId, int PathSegN);
DLLExport char* Url_GetSearchStr(int UrlId);
DLLExport char* Url_GetFragIdStr(int UrlId);
*/

int main(){
  // url
  {int UrlId=Url_Get("Tralala/Hopsasa.html?A=B", "http://www.ijs.si/HmHmHm");
  if (Url_IsOkHttp(UrlId)){
    // url-string
    char* UrlStr=Url_GetUrlStr(UrlId);
    printf("Url: %s\n", UrlStr);
    DelCStr(UrlStr);
    // scheme
    char* SchemeNm=Url_GetSchemeNm(UrlId);
    printf("Scheme: %s\n", SchemeNm);
    DelCStr(SchemeNm);
    // host
    char* HostNm=Url_GetHostNm(UrlId);
    printf("Host: %s\n", HostNm);
    DelCStr(HostNm);
    // path
    char* PathStr=Url_GetPathStr(UrlId);
    printf("Path: %s\n", PathStr);
    DelCStr(PathStr);
    // search
    char* SearchStr=Url_GetSearchStr(UrlId);
    printf("Search: %s\n", SearchStr);
    DelCStr(SearchStr);
  }
  Url_Del(UrlId);}

  // html
  {int HtmlDocId=HtmlDoc_GetFromFile("ijs.html");
  int Toks=HtmlDoc_GetToks(HtmlDocId);
  for (int TokN=0; TokN<Toks; TokN++){
    int Sym=HtmlDoc_GetTokSym(HtmlDocId, TokN);
    char* SymStr=HtmlDoc_GetSymStr(Sym);
    char* Str=HtmlDoc_GetTokStr(HtmlDocId, TokN);
    printf("[%s:%s] ", SymStr, Str);
    if (HtmlDoc_IsTokUrl(HtmlDocId, TokN)){
      char* UrlStr=HtmlDoc_GetTokUrlStr(HtmlDocId, TokN);
      printf("[Url:%s] ", UrlStr);
      DelCStr(UrlStr);
    }
    DelCStr(SymStr);
    DelCStr(Str);
  }
  HtmlDoc_Del(HtmlDocId);}

  // web-page
  char* FetchUrlStr="http://www.ijs.si/";
  printf("FetchUrl=%s\n", FetchUrlStr);
  int WebPgId=WebPg_Fetch(FetchUrlStr);
  if (WebPgId!=-1){
    printf("Successful fetch\n");
    // urls
    int Urls=WebPg_GetUrls(WebPgId);
    for (int UrlN=0; UrlN<Urls; UrlN++){
      char* UrlStr=WebPg_GetUrl(WebPgId, UrlN);
      printf("Url: %s\n", UrlStr);
      DelCStr(UrlStr);
    }
    // out-urls
    int OutUrlStrVId=WebPg_GetOutUrlStrV(WebPgId);
    for (int OutUrlN=0; OutUrlN<StrV_GetLen(OutUrlStrVId); OutUrlN++){
      char* OutUrlCStr=StrV_GetVal(OutUrlStrVId, OutUrlN);
      printf("OutUrl: %s\n", OutUrlCStr);
      DelCStr(OutUrlCStr);
    }
    StrV_Del(OutUrlStrVId);
    // http-response
    int HttpRespId=WebPg_GetHttpResp(WebPgId);
    if (HttpResp_IsOk(HttpRespId)){
      char* ContTypeStr=HttpResp_GetFldValByNm(HttpRespId, "content-type");
      if (strcmp(ContTypeStr, "text/html;charset=utf-8")==0){
        char* HtmlStr=HttpResp_GetBodyAsStr(HttpRespId);
        // process html
        int HtmlDocId=HtmlDoc_GetFromStr(HtmlStr);
        int Toks=HtmlDoc_GetToks(HtmlDocId);
        for (int TokN=0; TokN<Toks; TokN++){
          int Sym=HtmlDoc_GetTokSym(HtmlDocId, TokN);
          char* SymStr=HtmlDoc_GetSymStr(Sym);
          char* Str=HtmlDoc_GetTokStr(HtmlDocId, TokN);
          printf("[%s:%s] ", SymStr, Str);
          if (HtmlDoc_IsTokUrl(HtmlDocId, TokN)){
            char* UrlStr=HtmlDoc_GetTokUrlStr(HtmlDocId, TokN);
            printf("[Url:%s] ", UrlStr);
            DelCStr(UrlStr);
          }
          DelCStr(SymStr);
          DelCStr(Str);
        }
        HtmlDoc_Del(HtmlDocId);
        DelCStr(HtmlStr);
      }
      DelCStr(ContTypeStr);
    }
    HttpResp_Del(HttpRespId);
    // delete web-page
    WebPg_Del(WebPgId);
  } else {
    printf("Unsuccessful fetch\n");
  }

  return 0;
}

