#include "base.h"
#include "graph.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);
  // get command line parameters
  Env.PrepArgs("Crawl-Base to Graph", 1);
  TStr InCrawlBsFNm=Env.GetIfArgPrefixStr("-i:", ""/*"../CrawlWeb/bled.mbb"*/, "Crawl-Base-FileName");
  TStr OutGraphFNm=Env.GetIfArgPrefixStr("-og:", "Graph.Net", "Output-Graph-Filename");
  if (Env.IsEndOfRun()){return 0;}

  TStrIntVH UrlStrToOutUrlIdVH;
  TStrStrH UrlStrToRedirUrlStrH;
  // create vertices
  printf("Create Vertices ...");
  {PBlobBs CrawlBBs=TMBlobBs::New(InCrawlBsFNm);
  TBlobPt TrvCrawlBPt=CrawlBBs->FFirstBlobPt();
  TBlobPt CrawlBPt; PSIn CrawlBlobSIn;
  while (CrawlBBs->FNextBlobPt(TrvCrawlBPt, CrawlBPt, CrawlBlobSIn)){
    TStr DateTimeStr(*CrawlBlobSIn);
    TStr UrlStr(*CrawlBlobSIn);
    TMem HttpRespMem(*CrawlBlobSIn);
    PSIn HttpRespSIn=HttpRespMem.GetSIn();
    PHttpResp HttpResp=THttpResp::New(HttpRespSIn);
    if (HttpResp->IsStatusCd_Ok()){
      if (HttpResp->IsContType(THttp::TextHtmlFldVal)){
        UrlStrToOutUrlIdVH.AddKey(UrlStr);
      }
    } else
    if (HttpResp->IsStatusCd_Redir()){
      TStr RedirUrlStr=HttpResp->GetFldVal(THttp::LocFldNm);
      PUrl RedirUrl=TUrl::New(RedirUrlStr, UrlStr);
      if (RedirUrl->IsOk(usHttp)){
        TStr RedirUrlStr=RedirUrl->GetUrlStr();
        UrlStrToRedirUrlStrH.AddDat(UrlStr, RedirUrlStr);
      }
    }
  }}
  printf(" Done.\n");
  // create links
  printf("Create Links ...");
  {PBlobBs CrawlBBs=TMBlobBs::New(InCrawlBsFNm);
  TBlobPt TrvCrawlBPt=CrawlBBs->FFirstBlobPt();
  TBlobPt CrawlBPt; PSIn CrawlBlobSIn;
  while (CrawlBBs->FNextBlobPt(TrvCrawlBPt, CrawlBPt, CrawlBlobSIn)){
    TStr DateTimeStr(*CrawlBlobSIn);
    TStr UrlStr(*CrawlBlobSIn);
    TMem HttpRespMem(*CrawlBlobSIn);
    PSIn HttpRespSIn=HttpRespMem.GetSIn();
    PHttpResp HttpResp=THttpResp::New(HttpRespSIn);
    if (HttpResp->IsStatusCd_Ok()){
      if (HttpResp->IsContType(THttp::TextHtmlFldVal)){
        int UrlId=UrlStrToOutUrlIdVH.GetKeyId(UrlStr);
        PWebPg WebPg=TWebPg::New(UrlStr, HttpResp);
        TUrlV OutUrlV; WebPg->GetOutUrlV(OutUrlV);
        for (int OutUrlN=0; OutUrlN<OutUrlV.Len(); OutUrlN++){
          TStr OutUrlStr=OutUrlV[OutUrlN]->GetUrlStr();
          // check redirection
          int RedirUrlStrId;
          while (UrlStrToRedirUrlStrH.IsKey(OutUrlStr, RedirUrlStrId)){
            OutUrlStr=UrlStrToRedirUrlStrH[RedirUrlStrId];}
          // check vertex
          int OutUrlId;
          if (UrlStrToOutUrlIdVH.IsKey(OutUrlStr, OutUrlId)){
            UrlStrToOutUrlIdVH[UrlId].Add(OutUrlId);
          }
        }
        //printf("%s\n", UrlStr.CStr());
      }
    }
  }}
  printf(" Done.\n");
  // create graph
  printf("Create Graph ...");
  PGraph Graph=TGraph::New();
  printf(" Done.\n");
  // create graph-vertices
  printf("Create Graph Vertices ...");
  for (int UrlN=0; UrlN<UrlStrToOutUrlIdVH.Len(); UrlN++){
    TStr UrlStr=UrlStrToOutUrlIdVH.GetKey(UrlN);
    PVrtx Vrtx=TGVrtx::New(UrlStr);
    Graph->AddVrtx(Vrtx);
  }
  printf(" Done.\n");
  // create graph-edges
  printf("Create Graph Links ...");
  for (int UrlN=0; UrlN<UrlStrToOutUrlIdVH.Len(); UrlN++){
    TStr UrlStr=UrlStrToOutUrlIdVH.GetKey(UrlN);
    PVrtx SrcVrtx=Graph->GetVrtx(UrlStr);
    TIntV& OutUrlIdV=UrlStrToOutUrlIdVH[UrlN];
    for (int OutUrlN=0; OutUrlN<OutUrlIdV.Len(); OutUrlN++){
      TStr OutUrlStr=UrlStrToOutUrlIdVH.GetKey(OutUrlIdV[OutUrlN]);
      PVrtx DstVrtx=Graph->GetVrtx(OutUrlStr);
      PEdge Edge=TGEdge::New(SrcVrtx, DstVrtx);
      Graph->AddEdge(Edge);
    }
  }
  printf(" Done.\n");
  // save graph
  printf("Saving Graph To %s ...", OutGraphFNm.CStr());
  Graph->SaveTxtPajek(OutGraphFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}
