#include "../TextGardenLib/TextGardenLib.h"

void DumpBowDocBs(int BowDocBsId){
  int Docs=GetBowDocBs_Docs(BowDocBsId);
  printf("Docs (%d):", Docs);
  for (int DId=0; DId<Docs; DId++){
    char* DocNm=GetBowDocBs_DocNm(BowDocBsId, DId);
    printf("Document: '%s':\n", DocNm);
    DelCStr(DocNm);
    // document categories
    printf("Categories:");
    int DocCIds=GetBowDocBs_DocCIds(BowDocBsId, DId);
    for (int DocCIdN=0; DocCIdN<DocCIds; DocCIdN++){
      int DocCId=GetBowDocBs_DocCId(BowDocBsId, DId, DocCIdN);
      char* DocCatNm=GetBowDocBs_CatNm(BowDocBsId, DocCId);
      double DocWFq=GetBowDocBs_DocWFq(BowDocBsId, DId, DocCIdN);
      printf(" [%s:%.3f]", DocCatNm, DocWFq);
      DelCStr(DocCatNm);
    }
    printf("\n");
    // document words
    printf("Words:");
    int DocWIds=GetBowDocBs_DocWIds(BowDocBsId, DId);
    for (int DocWIdN=0; DocWIdN<DocWIds; DocWIdN++){
      int DocWId=GetBowDocBs_DocWId(BowDocBsId, DId, DocWIdN);
      double DocWFq=GetBowDocBs_DocWFq(BowDocBsId, DId, DocWIdN);
      char* DocWordStr=GetBowDocBs_WordStr(BowDocBsId, DocWId);
      printf(" [%s:%.3f]", DocWordStr, DocWFq);
      DelCStr(DocWordStr);
    }
    printf("\n");
  }
  printf("\n\n");
}

void DumpBowDocPart(int BowDocPartId, int BowDocBsId){
  int Clusts=GetBowDocPart_Clusts(BowDocPartId);
  printf("Clusters: %d\n", Clusts);
  for (int ClustN=0; ClustN<Clusts; ClustN++){
    int Docs=GetBowDocPart_Docs(BowDocPartId, ClustN);
    double MeanSim=GetBowDocPart_MeanSim(BowDocPartId, ClustN);
    printf("Cluster %d (MeanSim:%.3f)\n", ClustN, MeanSim);
    printf("Documents (%d):", Docs);
    for (int DIdN=0; DIdN<Docs; DIdN++){
      int DId=GetBowDocPart_DId(BowDocPartId, ClustN, DIdN);
      char* DocNm=GetBowDocBs_DocNm(BowDocBsId, DId);
      double DCSim=GetBowDocPart_DCSim(BowDocPartId, ClustN, DIdN);
      printf(" [%s:%.3f]", DocNm, DCSim);
      DelCStr(DocNm);
    }
    printf("\n");
    int ConceptWords=GetBowDocPart_ConceptWords(BowDocPartId, ClustN);
    printf("Centroid (%d Words):", ConceptWords);
    for (int WIdN=0; WIdN<ConceptWords; WIdN++){
      int WId=GetBowDocPart_ConceptWId(BowDocPartId, ClustN, WIdN);
      char* WordStr=GetBowDocBs_WordStr(BowDocBsId, WId);
      double WWgt=GetBowDocPart_ConceptWWgt(BowDocPartId, ClustN, WIdN);
      printf(" [%s:%.3f]", WordStr, WWgt);
      DelCStr(WordStr);
    }
    printf("\n");
    if (IsBowDocPart_SubPart(BowDocPartId, ClustN)){
      int SubPartId=GetBowDocPart_SubPart(BowDocPartId, ClustN);
      DumpBowDocPart(SubPartId, BowDocBsId);
      DelBowDocPart(SubPartId);
    }
  }
}

int main(int argc, char* argv[]){
/*
  ConvAcmTechNewsToCpd("c:/Data/ACMTechNews/Html", "ACMTechNews.Cpd", -1);
  ConvHtmlToCpd("c:/Data/CiaWFB/print", "CiaWFB.Cpd");
*/

/*
  ConvHtmlToBow("c:/Data/CiaWFB/print", "CiaWFB.Bow",
   true, -1, "en523", "porter", 3, 5);
  ConvCpdToBow("ACMTechNews.Cpd", "ACMTechNews.Bow",
   -1, "en523", "porter", 3, 5);
  ConvReuters21578ToBow("f:/Data/Reuters21578", "Reuters21578.Bow",
   -1, "en523", "porter", 3, 5);
  ConvCiaWFBToBow("c:/Data/CiaWFB/print", "CiaWFB.Bow",
   -1, "en523", "porter", 3, 5);
*/

/*
  ConvCiaWFBToCpd("c:/Data/CiaWFB/print", "CiaWFB.Cpd");
  ConvCpdToLnDocTxt("CiaWFB.Cpd", "CiaWFB.Txt");
  ConvLnDocToBow("CiaWFB.Txt", "CiaWFB.Bow", true, -1, "en523", "porter", 3, 5);
*/

  int CiaWFB_BowDocBsId=LoadBowDocBs("CiaWFB.Bow");
//  int BowDocBsId=LoadBowDocBs("Reuters21578.Bow");
//  SaveBowDocBs(BowDocBsId, "Test.Bow");
//  SaveBowDocBsStat(BowDocBsId, "Reuters21578.Stat.Txt");

  int InMem_BowDocsBsId=NewBowDocBs("en523", "porter");
  int IMDId1=AddBowDocBs_HtmlDocStr(InMem_BowDocsBsId,
   "d1", "City of London to go WiFi - The City of London, one of the biggest financial centres in the world, is to be provided with comprehensive wireless coverage over the entire area.", "", true);
  int IMDId2=AddBowDocBs_HtmlDocStr(InMem_BowDocsBsId,
   "d2", "WiFi coming to London's center city - The City of London plans to launch WiFi access throughout the city's Square Mile area later this year. Officials announced this", "", true);
  int IMDId3=AddBowDocBs_HtmlDocStr(InMem_BowDocsBsId,
   "d3", "City of London to get wireless coverage - THE CITY of London - the square mile filled with financial houses, men in bowler hats and the ghost of Dick Whittington, is to install a wi-fi network which", "", true);
  int IMDId4=AddBowDocBs_HtmlDocStr(InMem_BowDocsBsId,
   "d4", "City of London gets Wi-Fi - The Corporation of the City of London has chosen The Cloud to install a Wi-Fi network to cover the Square Mile. The project will", "", true);
  int IMDId5=AddBowDocBs_HtmlDocStr(InMem_BowDocsBsId,
   "d5", "City of London switches to Wi-Fi - The City of London Corporation today announced plans to install a dense and comprehensive Wi-Fi internet network throughout London's Square Mile", "", true);

/*
  // words
  {int Words=GetBowDocBs_Words(BowDocBsId);
  printf("Words (%d):", Words);
  for (int WId=0; WId<Words; WId++){
    char* WordStr=GetBowDocBs_WordStr(BowDocBsId, WId);
    printf(" %s", WordStr);
    DelCStr(WordStr);
  }
  printf("\n\n");}
*/

/*
  // categories
  {int Cats=GetBowDocBs_Cats(BowDocBsId);
  printf("Cats (%d):", Cats);
  for (int CId=0; CId<Cats; CId++){
    char* CatNm=GetBowDocBs_CatNm(BowDocBsId, CId);
    printf(" %s", CatNm);
    DelCStr(CatNm);
  }
  printf("\n\n");}
*/

/*
  DumpBowDocBs(BowDocBsId);
*/

/*
  // KMeans clustering
  int BowDocPartId=GetKMeansBowDocPart(BowDocBsId, 10, 3, 1, 1, 1, 1, 1, 1000);
  SaveBowDocPartStat(BowDocPartId, BowDocBsId, "BowDocPart.Stat.Txt");
  DumpBowDocPart(BowDocPartId, BowDocBsId);

  // Hierarchical-KMeans clustering
  int BowDocHPartId=GetHKMeansBowDocPart(BowDocBsId, 100, 3, 1, 1, 1, 1, 1, 1000);
  SaveBowDocPartStat(BowDocHPartId, BowDocBsId, "BowDocHPart.Stat.Txt");
  DumpBowDocPart(BowDocHPartId, BowDocBsId);
*/

/*
  // Binary-SVM training & classification
  int CornCId=GetBowDocBs_CId(BowDocBsId, "corn");
  // binary-svm
  int BinSVMBowMdId=GetBinSVMBowMd(BowDocBsId, CornCId);
  SaveBowMd(BinSVMBowMdId, "CornBinSVM.BowMd");
  // one-class-svm
  int OneClassSVMBowMdId=GetOneClassSVMBowMd(BowDocBsId, CornCId, 0.5);
  SaveBowMd(OneClassSVMBowMdId, "CornOneClassSVM.BowMd");

  int BowMdId=BinSVMBowMdId;
  //int BowMdId=OneClassSVMBowMdId;
  if (IsBowMdLinComb(BinSVMBowMdId)){
    if (IsBowMdCat(BowMdId)){
      char* CatNm=GetBowMdCatNm(BowMdId);
      printf("---Model for Category '%s'-------------\n", CatNm);
      DelCStr(CatNm);
    } else {
      printf("---No Category for Model---------------\n");
      printf("---------------------------------------\n");
    }
    int WgtWordPrVId=GetBowMdLinComb(BowMdId, BowDocBsId);
    int TopWgtWordPrVId=GetTopValFSPrV(WgtWordPrVId, 0.5, 10, true);
    int TopWgtWordPrs=GetFSPrVLen(TopWgtWordPrVId);
    for (int TopWgtWordPrN=0; TopWgtWordPrN<TopWgtWordPrs; TopWgtWordPrN++){
      double WWgt=GetFSPrV_FltVal(TopWgtWordPrVId, TopWgtWordPrN);
      char* WStr=GetFSPrV_StrVal(TopWgtWordPrVId, TopWgtWordPrN);
      printf("%3d. %6.3f %s\n", 1+TopWgtWordPrN, WWgt, WStr);
      DelCStr(WStr);
    }
    printf("---------------------------------------\n");
    DelFSPrV(WgtWordPrVId);
    DelFSPrV(TopWgtWordPrVId);
  }*/

/*
  // classification from document-base
  {int Docs=GetBowDocBs_Docs(BowDocBsId);
  int CfyDocs=Docs>25?25:Docs;
  for (int DId=0; DId<CfyDocs; DId++){
    {double Cfy=GetBowMdCfyFromDocBs(BinSVMBowMdId, BowDocBsId, DId);
    char* DocNm=GetBowDocBs_DocNm(BowDocBsId, DId);
    printf("['%s':%d --Bin-------> %.3f]\n", DocNm, DId, Cfy);
    DelCStr(DocNm);}
    {double Cfy=GetBowMdCfyFromDocBs(OneClassSVMBowMdId, BowDocBsId, DId);
    char* DocNm=GetBowDocBs_DocNm(BowDocBsId, DId);
    printf("['%s':%d --OneClass--> %.3f]\n", DocNm, DId, Cfy);
    DelCStr(DocNm);}
  }
  printf("\n");}*/

/*  // classification from html
  {char* HtmlCStr=
   "The U.S. Agriculture Department has"
   " accepted 10,572,402 more acres of highly erodable cropland into"
   " the Conservation Reserve Program, USDA announced."
   "    In the latest signup, farmers on 101,020 farms submitted"
   " bids on a total of 11,254,837 acres."
   "    The accepted bids for annual rental payments ranged up to"
   " 90 dlrs per acre with an average of 51.17 dlrs per acre."
   "    Land entered into the Conservation Reserve Program will be"
   " ineligible for farming for ten years and must be planted with"
   " permanent vegetative cover."
   "    Producers enrolled 1,894,764 acres of corn base acreage in"
   " the conservation program to take advantage of a corn bonus"
   " rental payment that was offered by USDA.";
  {double Cfy=GetBowMdCfyFromHtml(BinSVMBowMdId, BowDocBsId, HtmlCStr);
  printf("Classification: %.3f <--Bin------- %.50s...\n", Cfy, HtmlCStr);}
  {double Cfy=GetBowMdCfyFromHtml(OneClassSVMBowMdId, BowDocBsId, HtmlCStr);
  printf("Classification: %.3f <--OneClass-- %.50s...\n", Cfy, HtmlCStr);}}

  // classification from html
  {char* HtmlCStr=
   "Goldman Sachs International Corp"
   " received forged bonds of a unit of Exxon Corp &lt;XON> in a trade,"
   " a spokesman for Goldman Sachs and Co Inc said in a telephone"
   " conversation from New York."
   "    He said the transaction left Goldman Sachs International"
   " with an exposure of about 2.2 mln dlrs but that it had"
   " insurance to cover the loss."
   "    The spokesman was responding to an enquiry about an item in"
   " the London Standard newspaper, which said Goldman Sachs is"
   " feared to be the victim of a new multi-million pound City"
   " scandal."
   "    The newspaper also said, The firm (Goldman Sachs) is"
   " believed to be the paying agent for some 900 bonds issued in"
   " the name of oil giant Exxon which were deposited at banks in"
   " Brussels and have now been found to be forgeries.";
  {double Cfy=GetBowMdCfyFromHtml(BinSVMBowMdId, BowDocBsId, HtmlCStr);
  printf("Classification: %.3f <--Bin------- %.50s...\n", Cfy, HtmlCStr);}
  {double Cfy=GetBowMdCfyFromHtml(OneClassSVMBowMdId, BowDocBsId, HtmlCStr);
  printf("Classification: %.3f <--OneClass-- %.50s...\n", Cfy, HtmlCStr);}}*/

/*  int SiWeb_RSetId=GoogleWebSearch("slovenia", -1);
  int SiWeb_RSetLen=GetRSet_Hits(SiWeb_RSetId);
  printf("'slovenia' appears %d times on web.\n", SiWeb_RSetLen);
  DelRSet(SiWeb_RSetId);*/

/*  int SiNews_RSetId=GoogleNewsSearch("slovenia");
  int SiNews_RSetLen=GetRSet_Hits(SiNews_RSetId);
  printf("'slovenia' appears %d times in news.\n", SiNews_RSetLen);
  int Hits=GetRSet_Hits(SiNews_RSetId);
  for (int HitN=0; HitN<Hits; HitN++){
    char* UrlStr=GetRSet_HitUrlStr(SiNews_RSetId, HitN);
    char* TitleStr=GetRSet_HitTitleStr(SiNews_RSetId, HitN);
    char* SrcNm=GetRSet_HitSrcNm(SiNews_RSetId, HitN);
    char* CtxStr=GetRSet_HitCtxStr(SiNews_RSetId, HitN);
    printf("%d. %s - %s - %s - %s\n", 1+Hits, UrlStr, TitleStr, SrcNm, CtxStr);
    DelCStr(UrlStr); DelCStr(TitleStr); DelCStr(SrcNm); DelCStr(CtxStr);
  }
  DelRSet(SiNews_RSetId);
*/

/*  // url
  {int UrlId=GetUrl("Tralala/Hopsasa.html", "http://www.ijs.si/HmHmHm");
  if (Url_IsOkHttp(UrlId)){
    char* UrlStr=Url_GetUrlStr(UrlId);
    printf("Url: %s\n", UrlStr);
    DelCStr(UrlStr);
  }
  DelUrl(UrlId);}*/

/*  // html
  {int HtmlDocId=GetHtmlDocFromFile("ijs.html");
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
  DelHtmlDoc(HtmlDocId);}*/

/*  // web-page
  char* FetchUrlStr="http://www.ijs.si/";
  printf("FetchUrl=%s\n", FetchUrlStr);
  int WebPgId=FetchWebPg(FetchUrlStr);
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
    for (int OutUrlN=0; OutUrlN<GetStrVLen(OutUrlStrVId); OutUrlN++){
      char* OutUrlCStr=GetStrVVal(OutUrlStrVId, OutUrlN);
      printf("OutUrl: %s\n", OutUrlCStr);
      DelCStr(OutUrlCStr);
    }
    DelStrV(OutUrlStrVId);
    // http-response
    int HttpRespId=WebPg_GetHttpResp(WebPgId);
    if (HttpResp_IsOk(HttpRespId)){
      char* ContTypeStr=HttpResp_GetFldValByNm(HttpRespId, "content-type");
      if (strcmp(ContTypeStr, "text/html;charset=utf-8")==0){
        char* HtmlStr=HttpResp_GetBodyAsStr(HttpRespId);
        // process html
        int HtmlDocId=GetHtmlDocFromStr(HtmlStr);
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
        DelHtmlDoc(HtmlDocId);
        DelCStr(HtmlStr);
      }
      DelCStr(ContTypeStr);
    }
    DelHttpResp(HttpRespId);
    // delete web-page
    DelWebPg(WebPgId);
  } else {
    printf("Unsuccessful fetch\n");
  }*/

/*  // web-crawler
  // create crawler
  int CrawlerId=GenCrawler();
  // set parameters
  Crawler_AddStartUrlStr(CrawlerId, "http://www.miva.si/");
  Crawler_PutMxUrls(CrawlerId, 100000);
  Crawler_PutMxConns(CrawlerId, 10);
  Crawler_PutMnConns(CrawlerId, 1);
  Crawler_PutMxConnsPerSrv(CrawlerId, 1);
  Crawler_PutAfterFetchDelay(CrawlerId, 1);
  Crawler_PutMxLev(CrawlerId, 2);
  Crawler_PutMnQLen(CrawlerId, 1000);
  Crawler_PutQResetMod(CrawlerId, 1000);
  Crawler_PutMxContLen(CrawlerId, 1000000);
  Crawler_PutMxRetries(CrawlerId, 2);
  Crawler_PutMxQSegLen(CrawlerId, 1000000);
  Crawler_PutRevisitSecs(CrawlerId, 1000000);
  Crawler_AddRqDmNm(CrawlerId, ".miva.si");
  Crawler_DefCrawlBs(CrawlerId, "miva", "Data", "new", 10000000);
  // start crawling
  Crawler_StartCrawling(CrawlerId);
  // delete craw;er
  DelCrawler(CrawlerId);*/

  // crawl-base
  {int CrawlBsId=OpenCrawlBs("Data/a11");
  int TrvBlobPtId=CrawlBs_FFirstBlobPt(CrawlBsId);
  int BlobPtId=NewBlobPt();
  while (CrawlBs_FNextBlobPt(CrawlBsId, TrvBlobPtId, BlobPtId)){
    char* DateTimeStr=CrawlBs_GetDateTimeStr(CrawlBsId, BlobPtId);
    char* UrlStr=CrawlBs_GetUrlStr(CrawlBsId, BlobPtId);
    int HttpRespId=CrawlBs_GetHttpResp(CrawlBsId, BlobPtId);
    if (HttpResp_IsOk(HttpRespId)){
      char* ContTypeStr=HttpResp_GetFldValByNm(HttpRespId, "content-type");
      char* ContLenStr=HttpResp_GetFldValByNm(HttpRespId, "content-length");
      printf("Url:'%s'   Content-Type:'%s'   Content-Length'%s'\n",
       UrlStr, ContTypeStr, ContLenStr);
      DelCStr(ContTypeStr);
    } else {
      printf("Url:'%s'   Http-Response Invalid\n");
    }
    DelCStr(DateTimeStr);
    DelCStr(UrlStr);
    DelHttpResp(HttpRespId);
  }
  DelBlobPt(BlobPtId);
  DelBlobPt(TrvBlobPtId);
  CloseCrawlBs(CrawlBsId);}

/*  // search
  {int BowDocWgtBsId=GenBowDocWgtBs(BowDocBsId);
  int RSetId=BowDocWgtBs_Search(BowDocWgtBsId, BowDocBsId, "slovenia");
  int Hits=GetRSet_Hits(RSetId);
  if (Hits>10){Hits=10;}
  for (int HitN=0; HitN<Hits; HitN++){
    char* UrlStr=GetRSet_HitUrlStr(RSetId, HitN);
    char* TitleStr=GetRSet_HitTitleStr(RSetId, HitN);
    char* SrcNm=GetRSet_HitSrcNm(RSetId, HitN);
    char* CtxStr=GetRSet_HitCtxStr(RSetId, HitN);
    printf("%d. %s - %s - %s - %s\n", 1+HitN, UrlStr, TitleStr, SrcNm, CtxStr);
    DelCStr(UrlStr); DelCStr(TitleStr); DelCStr(SrcNm); DelCStr(CtxStr);
  }
  DelRSet(RSetId);
  DelBowDocWgtBs(BowDocWgtBsId);}*/

/*
  int NmObjBsId=GetNmObjBsFromCpd("ACMTechNews.Cpd", "en523", "", "", "", 1000);
  int NmObjBowDocBsId=GetBowDocBsFromNmObjBs(NmObjBsId, 3);
  DumpBowDocBs(NmObjBowDocBsId);
*/

/*
  int AL_BowDocBsId=CiaWFB_BowDocBsId;
  char* AL_CatNm="Europe";
  int AL_CId=GetBowDocBs_CId(AL_BowDocBsId, AL_CatNm);
  int BowALId=NewBowAL(AL_BowDocBsId, AL_CId);
  while(true){
    // stop if everything labled
    if (!GetBowAL_QueryDIdV(BowALId)){break;}

    // write the question
    double QueryMnDist=GetBowAL_QueryDist(BowALId, 0);
    int QueryDId=GetBowAL_QueryDId(BowALId, 0);
    char* DocNm=GetBowDocBs_DocNm(AL_BowDocBsId, QueryDId);
    printf("Does the following document belong to the \'%s\' category?\n", AL_CatNm);
    printf("=======================================================================\n");
    printf("%s:\n", DocNm);
    printf("=======================================================================\n");
    printf("Distance from the hyperplane is %g.\n", QueryMnDist);
    printf(" 1 - yes\n"); printf(" 2 - no\n"); printf(" 3 - exit\n");
    DelCStr(DocNm);

    // read the answer
    int UserResponse=0;
    do {scanf("%d", &UserResponse);}
    while (!(1<=UserResponse && UserResponse<=3));
    // user had enough?
    if (UserResponse == 3) break;

    // add the category information to Bow and to TrainSet
    if (UserResponse == 1) {
      printf("Adding to category %s!\n", AL_CatNm);
      MarkBowAL_QueryDId(BowALId, QueryDId, true);
    } else if (UserResponse == 2) {
      printf("Taking note that it is not in the category %s!\n", AL_CatNm);
      MarkBowAL_QueryDId(BowALId, QueryDId, false);
    }
  }
  printf("\n");
  // if user wants, we mark the rest of the positive documents with this category
  printf("Mark the rest of the documents? (1 - yes, 2 - no)");
  int UserResponse=0; do{scanf("%d", &UserResponse);}
  while (!(1<=UserResponse&&UserResponse<=2));
  if (UserResponse==1){
    MarkBowAL_UnlabeledPosDocs(BowALId);
    int Docs=GetBowDocBs_Docs(AL_BowDocBsId);
    for (int DId=0; DId<Docs; DId++){
      char* DocNm=GetBowDocBs_DocNm(AL_BowDocBsId, DId);
      int DocCIds=GetBowDocBs_DocCIds(AL_BowDocBsId, DId);
      for (int DocCIdN=0; DocCIdN<DocCIds; DocCIdN++){
        int DocCId=GetBowDocBs_DocCId(AL_BowDocBsId, DId, DocCIdN);
        char* DocCatNm=GetBowDocBs_CatNm(AL_BowDocBsId, DocCId);
        if (strcmp(DocCatNm, AL_CatNm)==0){
          printf("[%s]", DocNm);}
        DelCStr(DocCatNm);
      }
      DelCStr(DocNm);
    }
    SaveBowDocBsStat(AL_BowDocBsId, "ActiveLearning.Stat.Txt");
  }*/

  /*//int VizMap_BowDocBsId=CiaWFB_BowDocBsId;
  int VizMap_BowDocBsId=InMem_BowDocsBsId;
  int VizMap_BowDocWgtBsId=GenBowDocWgtBs(VizMap_BowDocBsId);
  int VizMap_BowDocPartId=GetKMeansBowDocPart(VizMap_BowDocBsId, 3, 3, 1, 1, 1, 1, 1, 1000);
  int VizMap_SemSpaceId=GetLSISemSpaceFromBowPart(VizMap_BowDocPartId, 3);
  int VizMapId=GetMdsClustLsiVizMap(
   VizMap_BowDocBsId, VizMap_BowDocWgtBsId, VizMap_BowDocPartId, VizMap_SemSpaceId,
   3, 0.7, 10000, 100);
  //int VizMapId=GetMdsLsiVizMap(
  // VizMap_BowDocBsId, VizMap_BowDocWgtBsId, VizMap_SemSpaceId, 0.7, 10);
  GenVizMapLandscape(VizMapId);
  SaveVizMap(VizMapId, "Sample.VizMap");
  SaveVizMapAsVrml(VizMapId, "VizMap.vrml", 0, true, false, true, 1.0);
  {int BowDocBsId=GetVizMapBowDocBsId(VizMapId);
  int BowDocWgtBsId=GetVizMapBowDocWgtBsId(VizMapId);
  for (int DIdN=0; DIdN<GetVizMapDocs(VizMapId); DIdN++){
    int DId=GetVizMapDId(VizMapId, DIdN);
    double X=GetVizMapDocX(VizMapId, DIdN);
    double Y=GetVizMapDocY(VizMapId, DIdN);
    char* DocNm=GetBowDocBs_DocNm(BowDocBsId, DId);
    printf("====================================\n");
    printf("%s [%d] (%.2f,%.2f)\n", DocNm, DId, X, Y);
    DelCStr(DocNm);
    {printf("  Frequency View:");
    int DocWIds=GetBowDocBs_DocWIds(BowDocBsId, DId);
    for (int DocWIdN=0; DocWIdN<DocWIds; DocWIdN++){
      int DocWId=GetBowDocBs_DocWId(BowDocBsId, DId, DocWIdN);
      double DocWFq=GetBowDocBs_DocWFq(BowDocBsId, DId, DocWIdN);
      char* DocWordStr=GetBowDocBs_WordStr(BowDocBsId, DocWId);
      printf(" [%s:%g]", DocWordStr, DocWFq);
      DelCStr(DocWordStr);
    }
    printf("\n");}
    {printf("  Weights View:");
    int WgtWord_FSPrVId=GetBowWgtDocBs_WgtWordPrV(BowDocWgtBsId, BowDocBsId, DId, 100, 0.5);
    int WIds=GetFSPrVLen(WgtWord_FSPrVId);
    for (int WIdN=0; WIdN<WIds; WIdN++){
      double Wgt=GetFSPrV_FltVal(WgtWord_FSPrVId, WIdN);
      char* WordStr=GetFSPrV_StrVal(WgtWord_FSPrVId, WIdN);
      printf(" [%s:%.3f]", WordStr, Wgt);
      DelCStr(WordStr);
    }
    DelFSPrV(WgtWord_FSPrVId);
    printf("\n");}
  }
  DelBowDocBs(BowDocBsId);}*/

  // dmoz
/*  int DMoz_BowDocBsId=LoadBowDocBs("Top_Science.Bow");
  int DMoz_BowDocWgtBsId=GenBowDocWgtBs(DMoz_BowDocBsId);
  int DMoz_BowDocPartId=LoadBowDocPart("Top_Science.BowPart");
  char* DMoz_QueryStr="fermat";
  // dmoz-categories
  {int CatWgtNm_FSPrVId=GetDMozCategories(
   DMoz_BowDocBsId, DMoz_BowDocWgtBsId, DMoz_BowDocPartId, DMoz_QueryStr, 25);
  int DMozCats=GetFSPrVLen(CatWgtNm_FSPrVId);
  printf("===DMoz-Begin-Categories-Demo===================\n");
  printf("Query: '%s'\n", DMoz_QueryStr);
  for (int CatN=0; CatN<DMozCats; CatN++){
    double CatWgt=GetFSPrV_FltVal(CatWgtNm_FSPrVId, CatN);
    char* CatNm=GetFSPrV_StrVal(CatWgtNm_FSPrVId, CatN);
    printf("%3d. %.3f %s\n", 1+CatN, CatWgt, CatNm);
    DelCStr(CatNm);
  }
  DelFSPrV(CatWgtNm_FSPrVId);
  printf("===DMoz-End-Categories-Demo===================\n");}
  // dmoz-keywords
  {int KWordWgtNm_FSPrVId=GetDMozKeywords(
   DMoz_BowDocBsId, DMoz_BowDocWgtBsId, DMoz_BowDocPartId, DMoz_QueryStr, 25, 0.75);
  int DMozKWords=GetFSPrVLen(KWordWgtNm_FSPrVId);
  printf("===DMoz-Begin-Keywords-Demo===================\n");
  printf("Query: '%s'\n", DMoz_QueryStr);
  for (int KWordN=0; KWordN<DMozKWords; KWordN++){
    double KWordWgt=GetFSPrV_FltVal(KWordWgtNm_FSPrVId, KWordN);
    char* KWordNm=GetFSPrV_StrVal(KWordWgtNm_FSPrVId, KWordN);
    printf("%3d. %.3f %s\n", 1+KWordN, KWordWgt, KWordNm);
    DelCStr(KWordNm);
  }
  DelFSPrV(KWordWgtNm_FSPrVId);
  printf("===DMoz-End-Keywords-Demo===================\n");}*/

  /*
    TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV; TStrFltPrV KWordStrWgtPrV;
    TDMozBs::GetBestClustV(BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
    TDMozBs::GetBestKWordV(WgtClustKdV, KWordTsh, false, KWordStrWgtPrV);
  */

  // compact-documents-base
  {int CpDocBsId=CpDocBs_Open("CiaWFB.Cpd");
  int CpDocId=NewCpDoc();
  CpDocBs_FFirst(CpDocBsId);
  while (CpDocBs_FNext(CpDocBsId, CpDocId)){
    char* HtmlCStr=CpDoc_GetHtmlStr(CpDocId);
    DelCStr(HtmlCStr);
  }
  DelCpDoc(CpDocId);
  CpDocBs_Close(CpDocBsId);}

  // write to blob-base
  {int BlobBsId=BlobBs_Open("CiaWFBBlobBs", BlobBs_GetFAccessCreate());
  int BlobPtId=NewBlobPt();
  int CpDocBsId=CpDocBs_Open("CiaWFB.Cpd");
  CpDocBs_FFirst(CpDocBsId);
  int CpDocId=NewCpDoc();
  while (CpDocBs_FNext(CpDocBsId, CpDocId)){
    char* HtmlCStr=CpDoc_GetHtmlStr(CpDocId);
    int MemId=GenMemFromStr(HtmlCStr);
    BlobBs_AddBlob(BlobBsId, MemId, BlobPtId);
    DelMem(MemId);
    DelCStr(HtmlCStr);
  }
  DelCpDoc(CpDocId);
  CpDocBs_Close(CpDocBsId);
  DelBlobPt(BlobPtId);
  BlobBs_Close(BlobBsId);}

  // read from blob-base
  {int BlobBsId=BlobBs_Open("CiaWFBBlobBs", BlobBs_GetFAccessReadOnly());
  int TrvBlobPtId=BlobBs_FFirstBlobPt(BlobBsId);
  int BlobPtId=NewBlobPt();
  while (BlobBs_FNextBlobPt(BlobBsId, TrvBlobPtId, BlobPtId)){
    int MemId=GenMem();
    BlobBs_GetBlob(BlobBsId, BlobPtId, MemId);
    char* HtmlCStr=GetMemAsStr(MemId);
    DelCStr(HtmlCStr);
    DelMem(MemId);
  }
  DelBlobPt(BlobPtId);
  DelBlobPt(TrvBlobPtId);
  BlobBs_Close(BlobBsId);}
}

