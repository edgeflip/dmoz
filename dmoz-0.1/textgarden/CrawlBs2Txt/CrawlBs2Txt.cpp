#include "base.h"

bool IsCTxtHttpResp(const PUrl& Url, const PHttpResp& HttpResp, const int& MnCTxtToks){
  if (HttpResp->IsStatusCd_Ok()){
    PWebPg WebPg=TWebPg::New(Url->GetUrlStr(), HttpResp);
    if (HttpResp->IsContType(THttp::TextHtmlFldVal)){
      TMem BodyMem=HttpResp->GetBodyAsMem();
      PSIn BodyMemIn=TMemIn::New(BodyMem);
      // prepare html-tokens
      PHtmlDoc HtmlDoc=THtmlDoc::New(BodyMemIn, hdtAll, false);
      int Toks=HtmlDoc->GetToks(); THtmlLxSym TokSym; TStr TokStr;
      // prepare continuous-text indicators
      int CTxtToks=0; TChA CTxtChA; bool CTxtP=false;
      // prepare script & style flag
      bool InScript=false; bool InStyle=false; 
      // traverse tokens
      for (int TokN=0; TokN<Toks; TokN++){
        // get token data
        HtmlDoc->GetTok(TokN, TokSym, TokStr);
        switch (TokSym){
          case hsyStr:
          case hsyNum:
          case hsySSym:
            if (!InScript&&!InStyle){
              // text token
              CTxtToks++; CTxtChA+=TokStr; CTxtChA+=' '; 
            }
            break;
          case hsyBTag:
            if (!InScript&&!InStyle){
              if (TokStr=="<SCRIPT>"){
                // start of script
                InScript=true; CTxtToks=0; CTxtChA.Clr();
              } else 
              if (TokStr=="<STYLE>"){
                // start of style
                InStyle=true; CTxtToks=0; CTxtChA.Clr();
              } else {
                if ((TokStr=="<P>")||(TokStr=="<B>")||(TokStr=="<I>")){
                  // skip in-text-tags
                } else {
                  // non-text-tags - break continuous-text
                  CTxtToks=0; CTxtChA.Clr();
                }
              }
            }
            break;
          case hsyETag:
            if (InScript||InStyle){
              if (TokStr=="<SCRIPT>"){
                // end of script
                InScript=false;
              } else
              if (TokStr=="<STYLE>"){
                // end of style
                InStyle=false;
              }
            }
            break;
          default: 
            // non-text-token - break continuous-text
            CTxtToks=0; CTxtChA.Clr();
            break;
        }
        // stop if enough continuous-text
        if (CTxtToks>MnCTxtToks){
          CTxtP=true; break;
        }
      }
      if (CTxtP){
        printf("%s\n", Url->GetUrlStr().CStr());
      }
      return CTxtP;
    }
  }
  return false;
}

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);
  // get command line parameters
  Env.PrepArgs("Crawl-Base to Text", 0);
  TStr InCrawlBsFNm=Env.GetIfArgPrefixStr("-i:", "", "Crawl-Base-FileName");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "Crawl.Txt", "Output-Text-Filename");
  TStr OutStatFNm=Env.GetIfArgPrefixStr("-os:", "Crawl.Stat.Txt", "Output-Statistics-Text-Filename");
  bool SaveContP=Env.GetIfArgPrefixBool("-sc:", false, "Save-Content");
  bool SaveContOutUrlP=Env.GetIfArgPrefixBool("-scou:", true, "Save-Content-Outgoing-Urls");
  bool SaveContTagP=Env.GetIfArgPrefixBool("-sct:", true, "Save-Content-Tags");
  bool SaveOutUrlP=Env.GetIfArgPrefixBool("-sou:", false, "Save-Outgoing-Urls");
  bool SaveCTxtP=Env.GetIfArgPrefixBool("-sctc:", false, "Save-Continuos-Text-Content");
  int MnCTxtToks=Env.GetIfArgPrefixInt("-mctt:", 100, "Minimal-Continuos-Text-Tokens");
  TStrV BlockedDmNmV=Env.GetIfArgPrefixStrV("-bd:", "Blocked-Domain-Names (multiple)");
  if (Env.IsEndOfRun()){return 0;}
  // -i:si -sc:t -scou:n -sct:n -sctc:t -bd:.delo.si -bd:.dnevnik.si -bd:.vecer.si

  TStr BlobBsFMid=InCrawlBsFNm.GetFMid();
  // output file
  TFOut TxtFOut(OutTxtFNm); FILE* fTxt=TxtFOut.GetFileId();
  fprintf(fTxt, "Comment:input=%s\n", InCrawlBsFNm.CStr());
  fprintf(fTxt, "Comment:output=%s\n", OutTxtFNm.CStr());
  fprintf(fTxt, "BlobBaseName:%s\n", BlobBsFMid.CStr());
  // statistics
  TStrIntH HostNmToFqH;
  TStrIntH StatusCdToFqH;
  TStrIntH ContTypeToFqH;
  PMom HttpContLenMom=TMom::New();

  PBlobBs CrawlBBs=TMBlobBs::New(InCrawlBsFNm);
  TBlobPt TrvCrawlBPt=CrawlBBs->FFirstBlobPt();
  TBlobPt CrawlBPt; PSIn CrawlBlobSIn; int CrawlBlobN=0;
  while (CrawlBBs->FNextBlobPt(TrvCrawlBPt, CrawlBPt, CrawlBlobSIn)){
    CrawlBlobN++; printf("%d\r", CrawlBlobN);
    TStr DateTimeStr(*CrawlBlobSIn); //TStr DateTimeStr;
    TStr UrlStr(*CrawlBlobSIn);
    PUrl Url=TUrl::New(UrlStr); IAssert(Url->IsOk(usHttp));
    TMem HttpRespMem(*CrawlBlobSIn);
    PSIn HttpRespSIn=HttpRespMem.GetSIn();
    PHttpResp HttpResp=THttpResp::New(HttpRespSIn);
    // statistics
    HostNmToFqH.AddDat(Url->GetHostNm())++;
    StatusCdToFqH.AddDat(TInt::GetStr(HttpResp->GetStatusCd()))++;
    ContTypeToFqH.AddDat(HttpResp->GetFldVal(THttp::ContTypeFldNm))++;
    int ContLen=HttpResp->GetFldVal(THttp::ContLenFldNm).GetInt(-1);
    if (ContLen!=-1){
      HttpContLenMom->Add(ContLen);}
    // check blocked domain-names
    if (!BlockedDmNmV.Empty()){
      TStr DmNm=Url->GetDmNm(); int BlockedDmP=false;
      for (int BDmNmN=0; BDmNmN<BlockedDmNmV.Len(); BDmNmN++){
        if (DmNm.IsSuffix(BlockedDmNmV[BDmNmN])){
          BlockedDmP=true; break;
        }
      }
      if (BlockedDmP){
        continue;
      }
    }
    // check continuos-text
    if (SaveCTxtP&&IsCTxtHttpResp(Url, HttpResp, MnCTxtToks)){continue;}
    if (HttpResp->IsStatusCd_Ok()){
      PWebPg WebPg=TWebPg::New(UrlStr, HttpResp);
      fprintf(fTxt, "Start:HttpOk\n");
      fprintf(fTxt, "BlobBaseAddress:bb://%s/%d/%d\n",
       BlobBsFMid.CStr(), CrawlBPt.GetSeg(), CrawlBPt.GetAddr());
      fprintf(fTxt, "DateTime:%s\n", DateTimeStr.CStr());
      fprintf(fTxt, "Url:%s\n", UrlStr.CStr());
      fprintf(fTxt, "UrlMd5:%s\n", TMd5Sig(UrlStr).GetStr().CStr());
      fprintf(fTxt, "AtomName:%s\n", TUrl::GetTopDownDocNm(UrlStr).CStr());
      for (int FldN=0; FldN<HttpResp->GetFlds(); FldN++){
        TStr FldNm; TStr FldVal; HttpResp->GetFldNmVal(FldN, FldNm, FldVal);
        fprintf(fTxt, "HttpField:%s=%s\n", FldNm.CStr(), FldVal.CStr());
      }
      TMem BodyMem=HttpResp->GetBodyAsMem();
      fprintf(fTxt, "BodyMd5:%s\n", TMd5Sig(BodyMem).GetStr().CStr());
      // text
      if (SaveContP){
        if (HttpResp->IsContType(THttp::TextHtmlFldVal)){
          TStr HtmlStr=BodyMem.GetAsStr();
          TStr TxtStr=THtmlDoc::GetTxtLnDoc(HtmlStr, UrlStr, SaveContOutUrlP, SaveContTagP);
          fprintf(fTxt, "Content:%s\n", TxtStr.CStr());
        }
      }
      // outgoing-urls
      if (SaveOutUrlP){
        TUrlV OutUrlV; WebPg->GetOutUrlV(OutUrlV);
        for (int OutUrlN=0; OutUrlN<OutUrlV.Len(); OutUrlN++){
          TStr OutUrlStr=OutUrlV[OutUrlN]->GetUrlStr();
          fprintf(fTxt, "OutUrl:%s\n", OutUrlStr.CStr());
        }
      }
      fprintf(fTxt, "End:HttpOk\n");
    } else
    if (HttpResp->IsStatusCd_Redir()){
      TStr RedirUrlStr=HttpResp->GetFldVal(THttp::LocFldNm);
      PUrl RedirUrl=TUrl::New(RedirUrlStr, UrlStr);
      if (RedirUrl->IsOk(usHttp)){
        TStr RedirUrlStr=RedirUrl->GetUrlStr();
        fprintf(fTxt, "Start:HttpRedirection\n");
        fprintf(fTxt, "BlobBaseAddress:bb://%s/%d/%d\n",
         BlobBsFMid.CStr(), CrawlBPt.GetSeg(), CrawlBPt.GetAddr());
        fprintf(fTxt, "DateTime:%s\n", DateTimeStr.CStr());
        fprintf(fTxt, "Url:%s\n", UrlStr.CStr());
        fprintf(fTxt, "UrlMd5:%s\n", TMd5Sig(UrlStr).GetStr().CStr());
        fprintf(fTxt, "AtomName:%s\n", TUrl::GetTopDownDocNm(UrlStr).CStr());
        fprintf(fTxt, "RedirectionUrl:%s\n", RedirUrlStr.CStr());
        for (int FldN=0; FldN<HttpResp->GetFlds(); FldN++){
          TStr FldNm; TStr FldVal; HttpResp->GetFldNmVal(FldN, FldNm, FldVal);
          fprintf(fTxt, "HttpField:%s=%s\n", FldNm.CStr(), FldVal.CStr());
        }
        fprintf(fTxt, "End:HttpRedirection\n");
      }
    }
  }

  // statistics
  HttpContLenMom->Def();
  if (!OutStatFNm.Empty()){
    TFOut StatFOut(OutStatFNm); FILE* fStat=StatFOut.GetFileId();
    TIntStrPrV FqStatusCdPrV; StatusCdToFqH.GetDatKeyPrV(FqStatusCdPrV);
    TIntStrPrV FqContTypePrV; ContTypeToFqH.GetDatKeyPrV(FqContTypePrV);
    // hosts
    {fprintf(fStat, "================================================\n");
    TIntStrPrV FqHostNmPrV; HostNmToFqH.GetDatKeyPrV(FqHostNmPrV);
    FqHostNmPrV.Sort(false); int HostNmsSum=0;
    fprintf(fStat, "Hosts (%d):\n", FqHostNmPrV.Len());
    for (int HostNmN=0; HostNmN<FqHostNmPrV.Len(); HostNmN++){
      fprintf(fStat, "%7d   '%s'\n",
       FqHostNmPrV[HostNmN].Val1, FqHostNmPrV[HostNmN].Val2.CStr());
      HostNmsSum+=FqHostNmPrV[HostNmN].Val1;
    }
    fprintf(fStat, "----------\n");
    fprintf(fStat, "%7d   %s\n", HostNmsSum, "Sum");
    fprintf(fStat, "================================================\n");}
    // status-code
    {fprintf(fStat, "================================================\n");
    TIntStrPrV FqStatusCdPrV; StatusCdToFqH.GetDatKeyPrV(FqStatusCdPrV);
    FqStatusCdPrV.Sort(false); int StatusCdsSum=0;
    fprintf(fStat, "Status-Codes (%d):\n", FqStatusCdPrV.Len());
    for (int StatusCdN=0; StatusCdN<FqStatusCdPrV.Len(); StatusCdN++){
      fprintf(fStat, "%7d   '%s'\n",
       FqStatusCdPrV[StatusCdN].Val1, FqStatusCdPrV[StatusCdN].Val2.CStr());
      StatusCdsSum+=FqStatusCdPrV[StatusCdN].Val1;
    }
    fprintf(fStat, "----------\n");
    fprintf(fStat, "%7d   %s\n", StatusCdsSum, "Sum");
    fprintf(fStat, "================================================\n");}
    // content-type
    {fprintf(fStat, "================================================\n");
    TIntStrPrV FqContTypePrV; ContTypeToFqH.GetDatKeyPrV(FqContTypePrV);
    FqContTypePrV.Sort(false); int ContTypesSum=0;
    fprintf(fStat, "Content-Types (%d):\n", FqContTypePrV.Len());
    for (int ContTypeN=0; ContTypeN<FqContTypePrV.Len(); ContTypeN++){
      fprintf(fStat, "%7d   '%s'\n",
       FqContTypePrV[ContTypeN].Val1, FqContTypePrV[ContTypeN].Val2.CStr());
      ContTypesSum+=FqContTypePrV[ContTypeN].Val1;
    }
    fprintf(fStat, "----------\n");
    fprintf(fStat, "%7d   %s\n", ContTypesSum, "Sum");
    fprintf(fStat, "================================================\n");}
    // content-length
    {fprintf(fStat, "================================================\n");
    fprintf(fStat, "Content-length:\n");
    if (HttpContLenMom->IsUsable()){
      TStr MomStr=HttpContLenMom->GetStr('\n', ':', true, false, "%g");
      fprintf(fStat, "%s\n", MomStr.CStr());
    } else {
      fprintf(fStat, "Statistics not usable.\n");
    }
    fprintf(fStat, "================================================\n");}
  }

  return 0;
  Catch;
  return 1;
}