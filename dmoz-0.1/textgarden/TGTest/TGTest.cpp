#include "stdafx.h"
#include "TextGardenLib.h"

int main(){
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

  {int UrlId=Url_Get("../tralala.html", "http://www.IJS.si:80/F1/F2/F3/t.html?a=b&c=d");
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
  } else {
    printf("Bad Url!\n");
  }}

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

/*
Top page: http://biz.yahoo.com/p/s_conameu.html
for each industry
  for each sector
    for each company
      Profile
      Key statistics

        