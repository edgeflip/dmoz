#include "mine.h"
#include "google.h"

/////////////////////////////////////////////////
// DMoz-Classification-Web-Server
class TDMozCfyWebSrv: public TWebSrv{
private:
  TStr BowFNm;
  PBowDocBs BowDocBs;
  PBowDocPart BowDocPart;
  PBowDocWgtBs BowDocWgtBs;
  PBowSim BowSim;
  PSOut TxtLogOut; FILE* fTxtLogOut;
  PSOut XmlLogOut; FILE* fXmlLogOut;
  TStr ProxyStr;
public:
  TDMozCfyWebSrv(
   const TStr& _BowFNm, const TStr& BowPartFNm,
   const TStr& LogTxtFNm, const TStr& LogXmlFNm, 
   const int& WebSrvPortN, const TStr& _ProxyStr);
  static PWebSrv New(
   const TStr& BowFNm, const TStr& BowPartFNm, const TStr& LogTxtFNm, 
   const TStr& LogXmlFNm, const int& WebSrvPortN, const TStr& ProxyStr){
    return PWebSrv(new TDMozCfyWebSrv(BowFNm, BowPartFNm,
     LogTxtFNm, LogXmlFNm, WebSrvPortN, ProxyStr));}

  void OnHttpRq(const int& SockId, const PHttpRq& HttpRq);

  TStr GetDMozBsNm() const {return BowFNm.GetFMid();}
  TStr GetQueryHtmlStr(const bool& FormOnlyP);
  TStr GetClassifyXmlStr(const TStr& SesId, const PBowSpV& QueryBowSpV,
   const int& MxCats, const double& KWordTsh, const bool& CtxP, const bool& XmlP);
  TStr GetClassifyXmlStr(const TStr& SesId, const TStr& UrlStr, const TStr& TextStr,
   const int& MxCats, const double& KWordTsh, const bool& CtxP, const bool& XmlP);
};

TDMozCfyWebSrv::TDMozCfyWebSrv(
 const TStr& _BowFNm, const TStr& BowPartFNm, const TStr& LogTxtFNm, 
 const TStr& LogXmlFNm, const int& WebSrvPortN, const TStr& _ProxyStr):
  TWebSrv(WebSrvPortN, true, TNotify::StdNotify),
  BowFNm(_BowFNm), BowDocBs(), BowDocPart(), BowDocWgtBs(), BowSim(),
  TxtLogOut(), fTxtLogOut(NULL), XmlLogOut(), fXmlLogOut(NULL), ProxyStr(_ProxyStr) {
  // load bow data
  printf("Loading bag-of-words data from '%s' ...", BowFNm.CStr());
  BowDocBs=TBowDocBs::LoadBin(BowFNm);
  printf(" Done.\n");
  // load bow-partition
  printf("Loading bag-of-words-partition from '%s' ...", BowPartFNm.CStr());
  BowDocPart=TBowDocPart::LoadBin(BowPartFNm);
  printf(" Done.\n");
  // prepare bow-tfidf
  BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtLogDFNrmTFIDF);
  // prepare similarity measure
  BowSim=TBowSim::New(bstCos);
  // prepare log-files
  TxtLogOut=TFOut::New(LogTxtFNm, true); fTxtLogOut=TxtLogOut->GetFileId();
  XmlLogOut=TFOut::New(LogXmlFNm, true); fXmlLogOut=XmlLogOut->GetFileId();
}

void TDMozCfyWebSrv::OnHttpRq(const int& SockId, const PHttpRq& HttpRq){
  // log fields
  TStr LogStatStr, LogTmStr, LogPeerHostNm, LogCmNm, LogSesId, LogUrlStr;
  TStr LogQUrlStr, LogQTextStr, LogQResultXmlStr;
  LogStatStr="Undefined";
  LogTmStr=TTm::GetCurUniTm().GetWebLogDateTimeStr().CStr();
  LogPeerHostNm=GetConn(SockId)->GetSock()->GetPeerIpNum();
  // result fields
  TStr UrlCmNm; TStr OutStr; TStrPrV AnnFldNmValPrV;
  bool OutXmlFormatP=false; bool OutPlainTextMimeTypeP=false;
  if (HttpRq->IsOk()){
    PUrl HttpRqUrl=HttpRq->GetUrl();
    PUrlEnv HttpRqUrlEnv=HttpRq->GetUrlEnv();
    if (HttpRqUrl->IsOk(usHttp)){
      LogUrlStr=HttpRqUrl->GetUrlStr();
      UrlCmNm=HttpRqUrl->GetPathSeg(0);
      if (UrlCmNm.Empty()){
        // output string
        OutStr=GetQueryHtmlStr(false);
        // update log fields
        LogStatStr="Ok";
        LogCmNm="Default";
      } else
      if ((UrlCmNm=="Classify")||(UrlCmNm=="XClassify")){
        // get parameters from POST request
        TStr SesId=HttpRqUrlEnv->GetVal("SesId");
        TStr UrlStr=HttpRqUrlEnv->GetVal("Url");
        TStr TextStr=HttpRqUrlEnv->GetVal("Text");
        int MxCats=HttpRqUrlEnv->GetVal("MxCats").GetInt(25);
        double KWordTsh=HttpRqUrlEnv->GetVal("KWordTsh").GetFlt(0.75);
        bool CtxP=HttpRqUrlEnv->GetVal("Context")=="T";
        OutXmlFormatP=HttpRqUrlEnv->GetVal("XmlFormat")=="T";
        OutPlainTextMimeTypeP=HttpRqUrlEnv->GetVal("PlainTextMimeType")=="T";
        if (UrlCmNm=="XClassify"){OutXmlFormatP=true;}
        // create classification in html or xml format
        OutStr=GetClassifyXmlStr(SesId, UrlStr, TextStr, MxCats, KWordTsh, CtxP, OutXmlFormatP);
        // update log fields
        LogStatStr="Ok";
        LogCmNm=UrlCmNm;
        LogSesId=HttpRqUrlEnv->GetVal("SesId");
        LogQUrlStr=UrlStr;
        LogQTextStr=THtmlDoc::GetTxtLnDoc(TextStr);
        if (OutXmlFormatP){LogQResultXmlStr=OutStr;}
      } else
      if (UrlCmNm=="Annotate"){
        // prepare annotation
        TStr AnnSesId;
        for (int KeyN=0; KeyN<HttpRqUrlEnv->GetKeys(); KeyN++){
          TStr KeyNm=HttpRqUrlEnv->GetKeyNm(KeyN);
          if (KeyNm=="SesId"){
            // get session-id
            AnnSesId=HttpRqUrlEnv->GetVal(KeyN);
          } else {
            // get keywords & categories
            for (int KeyValN=0; KeyValN<HttpRqUrlEnv->GetVals(KeyN); KeyValN++){
              TStr KeyVal=HttpRqUrlEnv->GetVal(KeyN, KeyValN);
              AnnFldNmValPrV.Add(TStrPr(KeyNm, KeyVal));
              //printf("%s=%s\n", KeyNm.CStr(), KeyVal.CStr());
            }
          }
        }
        // output string
        OutStr=GetQueryHtmlStr(false);
        // update log fields
        LogStatStr="Ok";
        LogCmNm=UrlCmNm;
        LogSesId=AnnSesId;
      } else {
        // invalid command
        OutStr="<html><head><title>Error</title></head><body>Invalid Command</body></html>";
        LogStatStr="Error-InvCm";
      }
    } else {
      // invalid http-request-url
      OutStr="<html><head><title>Error</title></head><body>Invalid HTTP-Request-URL</body></html>";
      LogStatStr="Error-InvHttpRqUrl";
    }
  } else {
    // invalid http-request
    OutStr="<html><head><title>Error</title></head><body>Invalid HTTP-Request</body></html>";
    LogStatStr="Error-InvHttpRq";
  }

  // prepare appropriate content-type
  TStr ContTypeVal;
  if (OutPlainTextMimeTypeP){ContTypeVal=THttp::TextPlainFldVal;}
  else if (OutXmlFormatP){ContTypeVal=THttp::TextXmlFldVal;}
  else {ContTypeVal=THttp::TextHtmlFldVal;}
  // create http-response
  PHttpResp HttpResp=THttpResp::New(
   THttp::OkStatusCd, ContTypeVal, false, TStrIn::New(OutStr));
  // send http-response
  SendHttpResp(SockId, HttpResp);

  // logging
  if ((UrlCmNm=="Classify")||(UrlCmNm=="XClassify")){
    printf(
     "Status=%s Time=%s PeerHost=%s Url=%s SesId=%s Cm=%s QUrl=%s QText=%s\n",
     LogStatStr.CStr(), LogTmStr.CStr(), LogPeerHostNm.CStr(), LogUrlStr.CStr(),
     LogSesId.CStr(), LogCmNm.CStr(), LogQUrlStr.CStr(), LogQTextStr.CStr());
    fprintf(fTxtLogOut,
     "Status=%s\tTime=%s\tPeerHost=%s\tUrl=%s\tSesId=%s\tCm=%s\tQUrl=%s\tQText=%s\n",
     LogStatStr.CStr(), LogTmStr.CStr(), LogPeerHostNm.CStr(), LogUrlStr.CStr(),
     LogSesId.CStr(), LogCmNm.CStr(), LogQUrlStr.CStr(), LogQTextStr.CStr());
    fprintf(fXmlLogOut,
     "<Query><Time>%s</Time><PeerHost>%s</PeerHost><Url>%s</Url>"
     "<SesId>%s</SesId><Cm>%s</Cm><QUrl>%s</QUrl><QText>%s</QText><QResult>%s</QResult></Query>\n",
     TXmlLx::GetXmlStrFromPlainStr(LogTmStr).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogPeerHostNm).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogUrlStr).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogSesId).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogCmNm).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogQUrlStr).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogQTextStr).CStr(),
     LogQResultXmlStr.CStr());
  } else
  if (UrlCmNm=="Annotate"){
    printf(
     "Status=%s Time=%s PeerHost=%s Url=%s SesId=%s Cm=%s",
     LogStatStr.CStr(), LogTmStr.CStr(), LogPeerHostNm.CStr(), LogUrlStr.CStr(),
     LogSesId.CStr(), LogCmNm.CStr());
    fprintf(fTxtLogOut,
     "Status=%s\tTime=%s\tPeerHost=%s\tUrl=%s\tSesId=%s\tCm=%s",
     LogStatStr.CStr(), LogTmStr.CStr(), LogPeerHostNm.CStr(), LogUrlStr.CStr(),
     LogSesId.CStr(), LogCmNm.CStr());
    fprintf(fXmlLogOut,
     "<Annotation><Time>%s</Time><PeerHost>%s</PeerHost><Url>%s</Url>"
     "<SesId>%s</SesId><Cm>%s</Cm>",
     TXmlLx::GetXmlStrFromPlainStr(LogTmStr).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogPeerHostNm).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogUrlStr).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogSesId).CStr(),
     TXmlLx::GetXmlStrFromPlainStr(LogCmNm).CStr());
    for (int AnnN=0; AnnN<AnnFldNmValPrV.Len(); AnnN++){
      TStr AnnFldNm=AnnFldNmValPrV[AnnN].Val1;
      TStr AnnFldVal=AnnFldNmValPrV[AnnN].Val2;
      printf(" %s=%s", AnnFldNm.CStr(), AnnFldVal.CStr());
      fprintf(fTxtLogOut, "\t%s=%s", AnnFldNm.CStr(), AnnFldVal.CStr());
      fprintf(fXmlLogOut, "<%s>%s</%s>",
       AnnFldNm.CStr(),
       TXmlLx::GetXmlStrFromPlainStr(AnnFldVal).CStr(),
       AnnFldNm.CStr());
    }
    printf("\n");
    fprintf(fTxtLogOut, "\n");
    fprintf(fXmlLogOut, "</Annotation>\n");
  } else {
    printf(
     "Status=%s Time=%s PeerHost=%s Url=%s\n",
     LogStatStr.CStr(), LogTmStr.CStr(), LogPeerHostNm.CStr(), LogUrlStr.CStr());
    fprintf(fTxtLogOut,
     "Status=%s\tTime=%s\tPeerHost=%s\tUrl=%s\n",
     LogStatStr.CStr(), LogTmStr.CStr(), LogPeerHostNm.CStr(), LogUrlStr.CStr());
  }
  fflush(fTxtLogOut);
  fflush(fXmlLogOut);
}

TStr TDMozCfyWebSrv::GetQueryHtmlStr(const bool& FormOnlyP){
  TStr SesId=TTm::GetCurUniTm().GetIdStr();
  TChA ChA;
  if (FormOnlyP){
    ChA+="<HTML>\n";
    ChA+="<HEAD><TITLE>Classification into DMoz</TITLE></HEAD>";
    ChA+="<BODY>\n";
  }
  ChA+=TStr::GetStr(GetDMozBsNm(), "<H2>Classification into DMoz %s</H2>\n");
  ChA+="<FORM METHOD=POST ACTION=\"/Classify\">\n";
  ChA+=TStr::GetStr(SesId, "<INPUT TYPE=HIDDEN NAME=\"SesId\" VALUE=\"%s\">");
  ChA+="URL:<BR>";
  ChA+="<INPUT TYPE=TEXT NAME=\"Url\" MAXLENGTH=256 SIZE=65><BR>";
  ChA+="Text:<BR>";
  ChA+="<TEXTAREA NAME=\"Text\" ROWS=15 COLS=50>\n";
  ChA+="</TEXTAREA><BR>\n";
  ChA+="Categories: ";
  ChA+="<INPUT TYPE=TEXT NAME=\"MxCats\" VALUE=25 MAXLENGTH=10 SIZE=10><BR>";
  ChA+="Keyword Threshold (0=None, 1=All): ";
  ChA+="<INPUT TYPE=TEXT NAME=\"KWordTsh\" VALUE=0.75 MAXLENGTH=10 SIZE=10><BR>";
  ChA+="Context: ";
  ChA+="<INPUT TYPE=CHECKBOX NAME=\"Context\" VALUE=\"T\" CHECKED><BR>";
  ChA+="XML Format: ";
  ChA+="<INPUT TYPE=CHECKBOX NAME=\"XmlFormat\" VALUE=\"T\"><BR>";
  ChA+="Plain-Text Mime-Type: ";
  ChA+="<INPUT TYPE=CHECKBOX NAME=\"PlainTextMimeType\" VALUE=\"T\"><BR>";
  ChA+="<INPUT TYPE=SUBMIT VALUE=\"Submit\">\n";
  ChA+="<INPUT TYPE=RESET VALUE=\"Reset\"><BR>\n";
  ChA+="</FORM>\n";
  if (FormOnlyP){
    ChA+="</BODY></HTML>\n";
  }
  return ChA;
}

TStr TDMozCfyWebSrv::GetClassifyXmlStr(const TStr& SesId, const PBowSpV& QueryBowSpV,
 const int& MxCats, const double& KWordTsh, const bool& CtxP, const bool& OutXmlFormatP){
  // prepare output-string
  TChA XmlChA;
  if (OutXmlFormatP){
    XmlChA+=TStr::GetStr(SesId, "<Classification SesId=\"%s\">");
  } else {
    XmlChA+="<HTML><HEAD><TITLE>Classification</TITLE></HEAD><BOSY>\n";
    XmlChA+=TStr::GetStr(GetDMozBsNm(), "<H2>Results of Classification into DMoz %s</H2>\n");
    XmlChA+="<FORM METHOD=POST ACTION=\"/Annotate\">\n";
    XmlChA+=TStr::GetStr(SesId, "<INPUT TYPE=HIDDEN NAME=\"SesId\" VALUE=\"%s\">");
  }
  // classify
  TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV; TStrFltPrV KWordStrWgtPrV;
  TDMozBs::GetBestClustV(BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
  TDMozBs::GetBestKWordV(WgtClustKdV, KWordTsh, false, -1, -1, KWordStrWgtPrV); //B: added missing parameters
  // generate keywords
  if (OutXmlFormatP){XmlChA+="<Keywords>";} else {XmlChA+="<b>Keywords:</b><br>";}
  for (int KWordN=0; KWordN<KWordStrWgtPrV.Len(); KWordN++){
    TStr KWordStr=KWordStrWgtPrV[KWordN].Val1;
    TStr KWordXmlStr=TXmlLx::GetXmlStrFromPlainStr(KWordStr);
    double KWordWgt=KWordStrWgtPrV[KWordN].Val2;
    if (OutXmlFormatP){
      XmlChA+=TFlt::GetStr(KWordWgt, "<Keyword Weight=\"%.3f\">");
      XmlChA+=KWordXmlStr;
      XmlChA+="</Keyword>";
    } else {
      //if (KWordN>0){XmlChA+=", ";}
      XmlChA+=TStr::GetStr(KWordStr, "<INPUT TYPE=CHECKBOX NAME=\"Keyword\" VALUE=\"%s\">");
      XmlChA+=KWordStr;
      XmlChA+=TFlt::GetStr(KWordWgt, " (%.3f)");
      XmlChA+="<br>";
    }
  }
  if (OutXmlFormatP){XmlChA+="</Keywords>";} else {XmlChA+="<br>";}
  // generate result in xml or html
  if (!OutXmlFormatP){XmlChA+="<b>Categories:</b><table border=3>\n";}
  for (int CatClustN=0; CatClustN<WgtClustKdV.Len(); CatClustN++){
    // retrieve fields
    int RankN=1+CatClustN;
    PBowDocPartClust Clust=WgtClustKdV[CatClustN].Dat;
    TStr CatNm=Clust->GetNm();
    TStr CatXmlNm=TXmlLx::GetXmlStrFromPlainStr(CatNm);
    TStr DMozCatUrlStr=TStr("http://www.dmoz.org/")+CatNm.GetSubStr(4, CatNm.Len());
    double CatWgt=WgtClustKdV[CatClustN].Key;
    if (OutXmlFormatP){
      // generate xml
      XmlChA+=TStr::Fmt("<Category Rank=\"%d\" Category=\"%s\" Weight=\"%5.3f\"/>",
       RankN, CatXmlNm.CStr(), CatWgt);
    } else {
      // generate html
      XmlChA+="<tr>";
      XmlChA+=TInt::GetStr(RankN, "<td>%d</td>");
      XmlChA+="<td>";
      XmlChA+=TStr::GetStr(CatNm, "<INPUT TYPE=CHECKBOX NAME=\"Category\" VALUE=\"%s\">");
      XmlChA+="</td>";
      XmlChA+=TFlt::GetStr(CatWgt, "<td>%5.3f</td>");
      XmlChA+=TStr::Fmt("<td><a href=\"%s\">%s</a></td>", DMozCatUrlStr.CStr(), CatXmlNm.CStr());
      //XmlChA+=TStr::GetStr(CatXmlNm, "<td>%s</td>");
      XmlChA+="<td>";
      XmlChA+="<select>";
      for (int WIdN=0; WIdN<WgtWIdPrVV[CatClustN].Len(); WIdN++){
        double Wgt=WgtWIdPrVV[CatClustN][WIdN].Val1;
        int WId=WgtWIdPrVV[CatClustN][WIdN].Val2;
        TStr WordStr=BowDocBs->GetWordStr(WId);
        XmlChA+=TStr::Fmt("  <option>%s (%.2f%%)</option>", WordStr.CStr(), 100*Wgt);
      }
      XmlChA+="</select>\n";
      XmlChA+="</td>";
      XmlChA+="</tr>\n";
    }
  }
  if (!OutXmlFormatP){XmlChA+="</table>\n";}
  // finish html
  if (OutXmlFormatP){
    XmlChA+="</Classification>";
  } else {
    XmlChA+="<INPUT TYPE=SUBMIT VALUE=\"Submit\">\n";
    XmlChA+="<INPUT TYPE=RESET VALUE=\"Reset\"><BR>\n";
    XmlChA+="</FORM>\n";
    XmlChA+=GetQueryHtmlStr(true);
    XmlChA+="</BODY></HTML>";
  }
  // return result
  return XmlChA;
}

TStr TDMozCfyWebSrv::GetClassifyXmlStr(
 const TStr& SesId, const TStr& UrlStr, const TStr& TextStr,
 const int& MxCats, const double& KWordTsh, const bool& CtxP, const bool& OutXmlFormatP){
  // prepare output-string
  TChA XmlChA;
  // prepare query-string
  TChA QueryChA;
  // add document-text to query-string
  if (!TextStr.Empty()){
    QueryChA+=TextStr;
  }
  // add results from link-query query-string
  if (CtxP){
    // add url as document
    QueryChA+=TUrl::GetDocStrFromUrlStr(UrlStr); QueryChA+="; ";
    // prepare url
    TStr NrUrlStr=UrlStr.GetTrunc();
    PUrl Url;
    if (!NrUrlStr.Empty()){
      Url=TUrl::New(NrUrlStr);
      if (!Url->IsOk(usHttp)){
        Url=TUrl::New(TStr("http://")+NrUrlStr);}
    }
    // retrieve url-context
    if ((!Url.Empty())&&(Url->IsOk(usHttp))){
      // link-query to google
      {TStr GgQueryStr=TStr("link:")+NrUrlStr;
      PRSet RSet=TGg::WebSearchExternal(GgQueryStr, 50, TNotify::NullNotify, ProxyStr);
      // compose document from link-query
      for (int HitN=0; HitN<RSet->GetHits(); HitN++){
        QueryChA+=TUrl::GetDocStrFromUrlStr(RSet->GetHitUrlStr(HitN)); QueryChA+=" - ";
        QueryChA+=RSet->GetHitTitleStr(HitN); QueryChA+=" - ";
        QueryChA+=RSet->GetHitCtxStr(HitN); QueryChA+="; ";
      }}
      // related-query to google
      {TStr GgQueryStr=TStr("related:")+UrlStr;
      PRSet RSet=TGg::WebSearchExternal(GgQueryStr, 50, TNotify::NullNotify, ProxyStr);
      // compose document from link-query
      for (int HitN=0; HitN<RSet->GetHits(); HitN++){
        QueryChA+=TUrl::GetDocStrFromUrlStr(RSet->GetHitUrlStr(HitN)); QueryChA+=" - ";
        QueryChA+=RSet->GetHitTitleStr(HitN); QueryChA+=" - ";
        QueryChA+=RSet->GetHitCtxStr(HitN); QueryChA+="; ";
      }}
    }
  }
  // create sparse-vector
  PBowSpV QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(QueryChA, BowDocWgtBs);
  // classify & create result
  XmlChA+=GetClassifyXmlStr(SesId, QueryBowSpV, MxCats, KWordTsh, CtxP, OutXmlFormatP);
  // return
  return XmlChA;
}

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Classification into DMoz - Server");
  TStr InBowFNm=Env.GetIfArgPrefixStr("-ibow:", "", "Input-BagOfWords-FileName");
  TStr InBowPartFNm=Env.GetIfArgPrefixStr("-ipart:", "", "Input-BagOfWords-Partition-FileName");
  TStr OutLogTxtFNm=Env.GetIfArgPrefixStr("-ot:", "DMozClassifyLog.Txt", "Output-Logging-Txt-File");
  TStr OutLogXmlFNm=Env.GetIfArgPrefixStr("-ox:", "DMozClassifyLog.Xml", "Output-Logging-Xml-File");
  int WebSrvPortN=Env.GetIfArgPrefixInt("-port:", 8080, "Server-Port");
  TStr ProxySrvStr=Env.GetIfArgPrefixStr("-proxy:", "", "Proxy-Server-Name");
  if (Env.IsEndOfRun()){return 0;}
  //-ibow:f:\Data\DMoz\Top_Recreation.Bow -ipart:f:\Data\DMoz\Top_Recreation.BowPart  -silent
  //-ibow:f:\Data\DMoz\Top_Business.Bow -ipart:f:\Data\DMoz\Top_Business.BowPart  -silent

  // activate server
  PWebSrv DMozCfyWebSrv=TDMozCfyWebSrv::New(
   InBowFNm, InBowPartFNm, OutLogTxtFNm, OutLogXmlFNm, WebSrvPortN, ProxySrvStr);
  TSysMsg::Loop();

  return 0;
  Catch;
  return 1;
}

