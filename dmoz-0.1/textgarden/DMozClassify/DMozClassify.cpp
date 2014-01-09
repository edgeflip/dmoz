#include "mine.h"

/*#include "google.h"
TStr GetLinkRelatedCtxStr(const TStr& UrlStr){
  TChA CtxStr;
  // get the context for the url link-query
  {TStr GgQueryStr=TStr("link:")+UrlStr;
  PRSet RSet=TGg::WebSearch(GgQueryStr, 50, TNotify::StdNotify);
  for (int HitN=0; HitN<RSet->GetHits(); HitN++){
    CtxStr+="["; CtxStr+=TUrl::GetDocStrFromUrlStr(RSet->GetHitUrlStr(HitN)); CtxStr+="] - ";
    CtxStr+=RSet->GetHitTitleStr(HitN); CtxStr+=" - ";
    CtxStr+=RSet->GetHitCtxStr(HitN); CtxStr+="; ";
  }}
  // get the context for the url related-query
  {TStr GgQueryStr=TStr("related:")+UrlStr;
  PRSet RSet=TGg::WebSearch(GgQueryStr, 50, TNotify::StdNotify);
  for (int HitN=0; HitN<RSet->GetHits(); HitN++){
    CtxStr+="["; CtxStr+=TUrl::GetDocStrFromUrlStr(RSet->GetHitUrlStr(HitN)); CtxStr+="] - ";
    CtxStr+=RSet->GetHitTitleStr(HitN); CtxStr+=" - ";
    CtxStr+=RSet->GetHitCtxStr(HitN); CtxStr+="; ";
  }}
  // return context-string
  return CtxStr;
}*/

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Classification into DMoz");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "", "Input-BagOfWords-FileName");
  TStr InBowPartFNm=Env.GetIfArgPrefixStr("-ipart:", "", "Input-BagOfWords-Partition-FileName");
  TStr InQueryCpdFNm=Env.GetIfArgPrefixStr("-qcpd:", "", "Input-Query-CompactDocument-FileName");
  TStr InQueryStr=Env.GetIfArgPrefixStr("-qs:", "", "Input-Query-String");
  TStr InQueryUrlStr=Env.GetIfArgPrefixStr("-qu:", "", "Input-Query-Url");
  TStr InQueryUrlStrVFNm=Env.GetIfArgPrefixStr("-quf:", "", "Input-Query-URL-Vector-FileName");
  TStr InQueryHtmlFNm=Env.GetIfArgPrefixStr("-qh:", "", "Input-Query-Html-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-ox:", "BowCfy.Xml", "Output-Classification-Xml-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-ot:", "BowCfy.Txt", "Output-Classification-Txt-File");
  int MxCats=Env.GetIfArgPrefixInt("-mxcat:", 25, "Output-Maximal-Categories");
  double KWordTsh=Env.GetIfArgPrefixFlt("-kwtsh:", 0.75, "Output-Keyword-Treshold");
  int MxDocs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents-To-Process");
printf("A");
  if (Env.IsEndOfRun()){return 0;}
printf("A");
  // load bow data
  printf("Loading bag-of-words data from '%s' ...", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtLogDFNrmTFIDF);
  PBowSim BowSim=TBowSim::New(bstCos);
  printf(" Done.\n");

  // load bow-model
  printf("Loading bag-of-words-partition from '%s' ...", InBowPartFNm.CStr());
  PBowDocPart BowDocPart=TBowDocPart::LoadBin(InBowPartFNm);
  printf(" Done.\n");

  // open output files
  TFOut FXml(OutXmlFNm); FILE* fXml=FXml.GetFileId();
  TFOut FTxt(OutTxtFNm); FILE* fTxt=FTxt.GetFileId();

  if (!InQueryUrlStrVFNm.Empty()){
    TStrV UrlStrV;
    // collect urls from the file
    PSIn SIn=TFIn::New(InQueryUrlStrVFNm);
    TILx Lx(SIn, TFSet(iloRetEoln));
    Lx.GetSym(syLn, syEof);
    while (Lx.Sym!=syEof){
      UrlStrV.Add(TStr(Lx.Str).GetTrunc());
      Lx.GetSym(syLn, syEof);
    }
    // traverse urls
    for (int UrlN=0; UrlN<UrlStrV.Len(); UrlN++){
      TStr UrlStr=UrlStrV[UrlN];
      printf("%d/%d %s\n", 1+UrlN, UrlStrV.Len(), UrlStr.CStr());
      // prepare query-string
      TStr QueryStr=UrlStr;//GetLinkRelatedCtxStr(UrlStr);
      // create bow
      PBowSpV QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(QueryStr, BowDocWgtBs);
      // classify
      TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV; TStrFltPrV KWordStrWgtPrV;
      TDMozBs::GetBestClustV(BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
      TDMozBs::GetBestKWordV(WgtClustKdV, KWordTsh, false, -1, -1, KWordStrWgtPrV);
      // output classification
      fprintf(fXml, "<Classification Doc=\"%s\">\n", UrlStr.CStr());
      fprintf(fTxt, "#F %s\n", UrlStr.CStr());
      // output keywords
      fprintf(fXml, "<Keywords>\n");
      for (int KWordN=0; KWordN<KWordStrWgtPrV.Len(); KWordN++){
        TStr KWordStr=KWordStrWgtPrV[KWordN].Val1;
        TStr KWordXmlStr=TXmlLx::GetXmlStrFromPlainStr(KWordStr);
        double KWordWgt=KWordStrWgtPrV[KWordN].Val2;
        fprintf(fXml, "  <Keyword String=\"%s\" Weight=\"%.3f\"/>\n",
         KWordXmlStr.CStr(), KWordWgt);
        fprintf(fTxt, "#K %s %.3f\n", KWordXmlStr.CStr(), KWordWgt);
      }
      fprintf(fXml, "</Keywords>\n");
      // output categories
      fprintf(fXml, "<Categories>\n");
      for (int CatClustN=0; CatClustN<WgtClustKdV.Len(); CatClustN++){
        // retrieve fields
        int RankN=1+CatClustN;
        PBowDocPartClust Clust=WgtClustKdV[CatClustN].Dat;
        TStr CatNm=Clust->GetNm();
        TStr CatXmlNm=TXmlLx::GetXmlStrFromPlainStr(CatNm);
        TStr DMozCatUrlStr=TStr("http://www.dmoz.org/")+CatNm.GetSubStr(4, CatNm.Len());
        double CatWgt=WgtClustKdV[CatClustN].Key;
        fprintf(fXml, "  <Category Rank=\"%d\" Category=\"%s\" Weight=\"%5.3f\"/>\n",
         RankN, CatXmlNm.CStr(), CatWgt);
        fprintf(fTxt, "#C %d %s %5.3f\n", RankN, CatXmlNm.CStr(), CatWgt);
      }
      fprintf(fXml, "</Categories>\n");
      fprintf(fXml, "</Classification>\n");
      fprintf(fTxt, "#E %s\n", UrlStr.CStr());
    }
  } else
  if (!InQueryCpdFNm.Empty()){
    // open input Cpd file
    PSIn CpdSIn=TCpDoc::FFirstCpd(InQueryCpdFNm); PCpDoc CpDoc; int Docs=0;
    while (TCpDoc::FNextCpd(CpdSIn, CpDoc)){
      if ((MxDocs!=-1)&&(Docs>MxDocs)){break;}
      TStr DocNm=CpDoc->GetDocNm();
      TStr XmlDocNm=TXmlLx::GetXmlStrFromPlainStr(DocNm);
      TStr HtmlStr=CpDoc->GetTxtStr();
      Docs++; printf("%d\r", Docs);
      // get sparse vector
      PBowSpV QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(HtmlStr, BowDocWgtBs);
      // classify
      TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV; TStrFltPrV KWordStrWgtPrV;
      TDMozBs::GetBestClustV(BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
      TDMozBs::GetBestKWordV(WgtClustKdV, KWordTsh, false, -1, -1, KWordStrWgtPrV);
      // output classification
      fprintf(fXml, "<Classification Doc=\"%s\">\n", XmlDocNm.CStr());
      fprintf(fTxt, "#F %s\n", XmlDocNm.CStr());
      // output keywords
      fprintf(fXml, "<Keywords>\n");
      for (int KWordN=0; KWordN<KWordStrWgtPrV.Len(); KWordN++){
        TStr KWordStr=KWordStrWgtPrV[KWordN].Val1;
        TStr KWordXmlStr=TXmlLx::GetXmlStrFromPlainStr(KWordStr);
        double KWordWgt=KWordStrWgtPrV[KWordN].Val2;
        fprintf(fXml, "  <Keyword String=\"%s\" Weight=\"%.3f\"/>\n",
         KWordXmlStr.CStr(), KWordWgt);
        fprintf(fTxt, "#K %s %.3f\n", KWordXmlStr.CStr(), KWordWgt);
      }
      fprintf(fXml, "</Keywords>\n");
      // output categories
      fprintf(fXml, "<Categories>\n");
      for (int CatClustN=0; CatClustN<WgtClustKdV.Len(); CatClustN++){
        // retrieve fields
        int RankN=1+CatClustN;
        PBowDocPartClust Clust=WgtClustKdV[CatClustN].Dat;
        TStr CatNm=Clust->GetNm();
        TStr CatXmlNm=TXmlLx::GetXmlStrFromPlainStr(CatNm);
        TStr DMozCatUrlStr=TStr("http://www.dmoz.org/")+CatNm.GetSubStr(4, CatNm.Len());
        double CatWgt=WgtClustKdV[CatClustN].Key;
        fprintf(fXml, "  <Category Rank=\"%d\" Category=\"%s\" Weight=\"%5.3f\"/>\n",
         RankN, CatXmlNm.CStr(), CatWgt);
        fprintf(fTxt, "#C %d %s %5.3f\n", RankN, CatXmlNm.CStr(), CatWgt);
      }
      fprintf(fXml, "</Categories>\n");
      fprintf(fXml, "</Classification>\n");
      fprintf(fTxt, "#E %s\n", XmlDocNm.CStr());
    }
  } else {
    // single document classification
    // convert query document in bow-sparse-vector form
    PBowSpV QueryBowSpV;
    if (!InQueryUrlStr.Empty()){
      // prepare query-string
      TStr QueryStr=InQueryUrlStr;//GetLinkRelatedCtxStr(InQueryUrlStr);
      // create bow
      QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(QueryStr, BowDocWgtBs);
    } else
    if (!InQueryStr.Empty()){
      QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(InQueryStr, BowDocWgtBs);
    } else
    if (!InQueryHtmlFNm.Empty()){
      QueryBowSpV=BowDocBs->GetSpVFromHtmlFile(InQueryHtmlFNm, BowDocWgtBs);
    } else {
      TExcept::Throw("No Input-Query specified!");
    }
    // classify
    TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV; TStrFltPrV KWordStrWgtPrV;
    TDMozBs::GetBestClustV(BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
    TDMozBs::GetBestKWordV(WgtClustKdV, KWordTsh, false, -1, -1, KWordStrWgtPrV);
    // output classification
    fprintf(fXml, "<Classification>\n");
    fprintf(fTxt, "#C\n");
    // output keywords
    fprintf(fXml, "<Keywords>\n");
    for (int KWordN=0; KWordN<KWordStrWgtPrV.Len(); KWordN++){
      TStr KWordStr=KWordStrWgtPrV[KWordN].Val1;
      TStr KWordXmlStr=TXmlLx::GetXmlStrFromPlainStr(KWordStr);
      double KWordWgt=KWordStrWgtPrV[KWordN].Val2;
      fprintf(fXml, "  <Keyword String=\"%s\" Weight=\"%.3f\"/>\n",
       KWordXmlStr.CStr(), KWordWgt);
      fprintf(fTxt, "#K %s %.3f\n", KWordXmlStr.CStr(), KWordWgt);
      printf("%s %.3f\n", KWordXmlStr.CStr(), KWordWgt);
    }
    fprintf(fXml, "</Keywords>\n");
    // output categories
    fprintf(fXml, "<Categories>\n");
    for (int CatClustN=0; CatClustN<WgtClustKdV.Len(); CatClustN++){
      // retrieve fields
      int RankN=1+CatClustN;
      PBowDocPartClust Clust=WgtClustKdV[CatClustN].Dat;
      TStr CatNm=Clust->GetNm();
      TStr CatXmlNm=TXmlLx::GetXmlStrFromPlainStr(CatNm);
      TStr DMozCatUrlStr=TStr("http://www.dmoz.org/")+CatNm.GetSubStr(4, CatNm.Len());
      double CatWgt=WgtClustKdV[CatClustN].Key;
      fprintf(fXml, "  <Category Rank=\"%d\" Category=\"%s\" Weight=\"%5.3f\"/>\n",
       RankN, CatXmlNm.CStr(), CatWgt);
      fprintf(fTxt, "#C %d %s %5.3f\n", RankN, CatXmlNm.CStr(), CatWgt);
      printf("%d %s %5.3f\n", RankN, CatXmlNm.CStr(), CatWgt);
    }
    fprintf(fXml, "</Categories>\n");
    fprintf(fXml, "</Classification>\n");
    fprintf(fTxt, "#E\n");
  }

  return 0;
  Catch;
  return 1;
}

