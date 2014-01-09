#include "base.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);
  // get command line parameters
  Env.PrepArgs("Crawl-Base to Meta-Data", 0);
  TStr InCrawlBsFNm=Env.GetIfArgPrefixStr("-i:", "../CrawlWeb/Data/si.mbb", "Crawl-Base-FileName");
  TStr OutSimCodesFNm=Env.GetIfArgPrefixStr("-ot:", "SimCodes.Txt", "Output-SimilarityCodes-Filename");
  if (Env.IsEndOfRun()){return 0;}

  TStr BlobBsFMid=InCrawlBsFNm.GetFMid();
  TFOut SimCodesFOut(OutSimCodesFNm); FILE* fSimCodes=SimCodesFOut.GetFileId();
  fprintf(fSimCodes, "Comment:input=%s\n", InCrawlBsFNm.CStr());
  fprintf(fSimCodes, "Comment:output=%s\n", OutSimCodesFNm.CStr());
  fprintf(fSimCodes, "BlobBaseName:%s\n", BlobBsFMid.CStr());

  // open crawl-base
  PBlobBs CrawlBBs=TMBlobBs::New(InCrawlBsFNm);
  // traverse crawl-base-records
  TBlobPt TrvCrawlBPt=CrawlBBs->FFirstBlobPt();
  TBlobPt CrawlBPt; PSIn CrawlBlobSIn; int CrawlBlobN=0;
  while (CrawlBBs->FNextBlobPt(TrvCrawlBPt, CrawlBPt, CrawlBlobSIn)){
    CrawlBlobN++; printf("%d\r", CrawlBlobN);
    // read & prepare url
    TStr UrlStr(*CrawlBlobSIn);
    PUrl Url=TUrl::New(UrlStr); IAssert(Url->IsOk(usHttp));
    // read http-reponse
    TMem HttpRespMem(*CrawlBlobSIn);
    PSIn HttpRespSIn=HttpRespMem.GetSIn();
    PHttpResp HttpResp=THttpResp::New(HttpRespSIn);
    // if status=ok and content-type==text/html
    if ((HttpResp->IsStatusCd_Ok())&&(HttpResp->IsContType(THttp::TextHtmlFldVal))){
      TStr BodyStr=HttpResp->GetBodyAsMem(); // get string from http-body
      PSIn BodySIn=TStrIn::New(BodyStr); // get input-stream from string
      PHtmlDoc HtmlDoc=THtmlDoc::New(BodySIn); // get html-document from input-stream
      PBSet HtmlBSet=TBSet::New(64); // create 64bit bit-set
      // traverse html tokens
      THtmlLxSym TokSym; TStr TokStr; TChA TokChA; TChA HtmlChA;
      for (int TokN=0; TokN<HtmlDoc->GetToks(); TokN++){
        HtmlDoc->GetTok(TokN, TokSym, TokStr); // get token
        if ((TokSym==hsyStr)||(TokSym==hsyNum)){
          // token is string or number
          printf("'%s' ", TokStr.CStr());
          // add token-string to html-string
          if (!HtmlChA.Empty()){HtmlChA+=' ';}
          HtmlChA+=TokStr;
          // calculate bit-index from token-string
          TokChA=TokStr; int TokChALen=TokChA.Len(); 
          uchar ChSum=0;
          for (int ChN=0; ChN<TokChALen; ChN++){
            ChSum+=uchar(TokChA[ChN]);}
          int BitN=(ChSum & 0x3F);
          // toggle bit under bit-index
          HtmlBSet->SwitchBit(BitN);
        }
      }
      printf("\n");
      // get 64-bit code for current html-document
      printf("Binary Code: "); HtmlBSet->Wr(); printf("\n");
      uint64 UInt64=HtmlBSet->GetUInt64();
      printf("Document String: %s\n", HtmlChA.CStr());
      printf("\n");
    }
  }

  return 0;
  Catch;
  return 1;
}
