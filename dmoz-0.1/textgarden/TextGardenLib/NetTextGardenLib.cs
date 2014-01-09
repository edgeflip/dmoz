using System;                         
using System.Collections.Generic;     
using System.Text;                    
using System.Runtime.InteropServices; 

namespace NetTextGardenLib
{                                     
   public class TextGardenLib
   {                                  
      private class HTextGardenLib
      {                               
         [DllImport("TextGardenLib.dll")]
         public static extern void DelCStr(IntPtr CStr);

         [DllImport("TextGardenLib.dll")]
         public static extern void SetVerbosity(int VerbosityLev);

         [DllImport("TextGardenLib.dll")]
         public static extern int GetVerbosity();

         [DllImport("TextGardenLib.dll")]
         public static extern int CStr_GetStrs();

         [DllImport("TextGardenLib.dll")]
         public static extern int CStr_GetStrV();

         [DllImport("TextGardenLib.dll")]
         public static extern int IntV_Gen();

         [DllImport("TextGardenLib.dll")]
         public static extern void IntV_Del(int IntVId);

         [DllImport("TextGardenLib.dll")]
         public static extern int IntV_GetLen(int IntVId);

         [DllImport("TextGardenLib.dll")]
         public static extern int IntV_AddVal(int IntVId, int Val);

         [DllImport("TextGardenLib.dll")]
         public static extern int IntV_GetVal(int IntVId, int ValN);

         [DllImport("TextGardenLib.dll")]
         public static extern void IntV_Sort(int IntVId, bool Asc);

         [DllImport("TextGardenLib.dll")]
         public static extern int IntV_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void IntV_Save(int IntVId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int StrV_Gen();

         [DllImport("TextGardenLib.dll")]
         public static extern void StrV_Del(int StrVId);

         [DllImport("TextGardenLib.dll")]
         public static extern int StrV_GetLen(int StrVId);

         [DllImport("TextGardenLib.dll")]
         public static extern int StrV_AddVal(int StrVId, String Val);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr StrV_GetVal(int StrVId, int ValN);

         [DllImport("TextGardenLib.dll")]
         public static extern void StrV_Sort(int StrVId, bool Asc);

         [DllImport("TextGardenLib.dll")]
         public static extern int StrV_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void StrV_Save(int StrVId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int FSPrV_Gen();

         [DllImport("TextGardenLib.dll")]
         public static extern void FSPrV_Del(int FSPrVId);

         [DllImport("TextGardenLib.dll")]
         public static extern int FSPrV_GetLen(int FSPrVId);

         [DllImport("TextGardenLib.dll")]
         public static extern int FSPrV_AddVal(int FSPrVId, double Flt, String Str);

         [DllImport("TextGardenLib.dll")]
         public static extern double FSPrV_GetFltVal(int FSPrVId, int ValN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr FSPrV_GetStrVal(int FSPrVId, int ValN);

         [DllImport("TextGardenLib.dll")]
         public static extern void FSPrV_Sort(int FSPrVId, bool Asc);

         [DllImport("TextGardenLib.dll")]
         public static extern int FSPrV_GetTopVal(int FSPrVId, double WgtPrc, int MxVals, bool UseNegWgt);

         [DllImport("TextGardenLib.dll")]
         public static extern int FSPrV_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void FSPrV_Save(int StrVId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int SIn_GenStdIn();

         [DllImport("TextGardenLib.dll")]
         public static extern int SIn_GenFileIn(String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int SIn_GenMemIn(int MemId);

         [DllImport("TextGardenLib.dll")]
         public static extern int SIn_GenStrIn(String Str);

         [DllImport("TextGardenLib.dll")]
         public static extern void SIn_Del(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern int SOut_GenStdOut();

         [DllImport("TextGardenLib.dll")]
         public static extern int SOut_GenFileOut(String FNm, bool Append);

         [DllImport("TextGardenLib.dll")]
         public static extern int SOut_GenMemOut(int MemId);

         [DllImport("TextGardenLib.dll")]
         public static extern void SOut_Del(int SOutId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_HtmlToCpd(String InFPath, String OutCpdFNm, bool RecurseDirP, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_Reuters21578ToCpd(String InFPath, String OutCpdFNm, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_Reuters2000ToCpd(String InFPath, String OutCpdFNm, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_AcmTechNewsToCpd(String InFPath, String OutCpdFNm, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_CiaWFBToCpd(String InFPath, String OutCpdFNm);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_CpdToLnDocTxt(String InCpdFNm, String OutLnDocFNm);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_HtmlToBow(String InFPath, String OutBowFNm, bool RecurseDirP, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_CpdToBow(String InCpdFNm, String OutBowFNm, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq);

         [DllImport("TextGardenLib.dll")]
         public static extern int Conv_GetBowFromCpd(int CpdSInId, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_LnDocToBow(String InLnDocFNm, String OutBowFNm, bool NamedP, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_Reuters21578ToBow(String InFPath, String OutBowFNm, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Conv_CiaWFBToBow(String InFPath, String OutBowFNm, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_New(String SwSetTypeNm, String StemmerTypeNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocBs_Save(int BowDocBsId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_LoadFromFile(String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocBs_SaveToFile(int BowDocBsId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocBs_SaveStatToFile(int BowDocBsId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocBs_Del(int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetWords(int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowDocBs_IsWordStr(int BowDocBsId, String WordStr);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetWId(int BowDocBsId, String WordStr);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr BowDocBs_GetWordStr(int BowDocBsId, int WId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetCats(int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowDocBs_IsCatNm(int BowDocBsId, String CatNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetCId(int BowDocBsId, String CatNm);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr BowDocBs_GetCatNm(int BowDocBsId, int CId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_AddHtmlDocStr(int BowDocBsId, String DocNm, String HtmlDocStr, String CatNmVStr, bool SaveDocP);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDocs(int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowDocBs_IsDocNm(int BowDocBsId, String DocNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDId(int BowDocBsId, String DocNm);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr BowDocBs_GetDocNm(int BowDocBsId, int DId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDocWIds(int BowDocBsId, int DId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDocWId(int BowDocBsId, int DId, int DocWIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDocWIdN(int BowDocBsId, int DId, int DocWId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocBs_PutDocWFq(int BowDocBsId, int DId, int DocWIdN, double WFq);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowDocBs_GetDocWFq(int BowDocBsId, int DId, int DocWIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDocCIds(int BowDocBsId, int DId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocBs_GetDocCId(int BowDocBsId, int DId, int DocCIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_Gen(int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocWgtBs_Del(int BowDocWgtBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_GetDocs(int BowDocWgtBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_GetDocId(int BowDocWgtBsId, int DIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_GetDocWIds(int BowDocWgtBsId, int DId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_GetDocWId(int BowDocWgtBsId, int DId, int DocWIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowDocWgtBs_GetDocWWgt(int BowDocWgtBsId, int DId, int DocWIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_GetWgtWordPrV(int BowDocWgtBsId, int BowDocBsId, int DId, int TopWords, double TopWordsWgtPrc);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocWgtBs_Search(int BowDocWgtBsId, int BowDocBsId, String QueryStr);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocPart_Save(int BowDocPartId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_LoadFromFile(String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocPart_SaveToFile(int BowDocPartId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocPart_SaveStatToFile(int BowDocPartId, int BowDocBsId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowDocPart_Del(int BowDocPartId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetKMeans(int BowDocBsId, int Clusts, int ClustTrials, double ConvergEps, int MnDocsPerClust, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetHKMeans(int BowDocBsId, int MxDocsPerLeafClust, int ClustTrials, double ConvergEps, int MnDocsPerClust, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetClusts(int BowDocPartId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetDocs(int BowDocPartId, int ClustN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetDId(int BowDocPartId, int ClustN, int DIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowDocPart_GetMeanSim(int BowDocPartId, int ClustN);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowDocPart_GetDCSim(int BowDocPartId, int ClustN, int DId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetConceptWords(int BowDocPartId, int ClustN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetConceptWId(int BowDocPartId, int ClustN, int WIdN);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowDocPart_GetConceptWWgt(int BowDocPartId, int ClustN, int WIdN);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowDocPart_IsSubPart(int BowDocPartId, int ClustN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowDocPart_GetSubPart(int BowDocPartId, int ClustN);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void SemSpace_Save(int SemSpaceId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_LoadFromFile(String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void SemSpace_SaveToFile(int SemSpaceId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void SemSpace_SaveStatToFile(int SemSpaceId, int BowDocBsId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void SemSpace_Del(int SemSpaceId);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_GetDims(int SemSpaceId);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_GetDim(int SemSpaceId, int BowDocBsId, int DimN);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_GetLSI(int BowDocBsId, int SpaceDims);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_GetLSIFromBowPart(int BowDocPartId, int SpaceDims);

         [DllImport("TextGardenLib.dll")]
         public static extern int SemSpace_GetPCA(int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowMd_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowMd_Save(int BowMdId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowMd_LoadFromFile(String FNm, int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowMd_SaveToFile(int BowMdId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowMd_Del(int BowMdId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowMd_IsCat(int BowMdId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr BowMd_GetCatNm(int BowMdId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowMd_IsLinComb(int BowMdId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowMd_GetLinCombWgtWordPrV(int BowMdId, int BowDocBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowMd_GetLinCombTsh(int BowMdId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost, double CostWgt, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowMd_GetOneClassSVM(int BowDocBsId, int CId, double Nu, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowMd_GetWinnow(int BowDocBsId, int CId, double Beta, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowMd_GetCfyFromDocBs(int BowMdId, int BowDocBsId, int DId);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowMd_GetCfyFromHtml(int BowMdId, int BowDocBsId, String HtmlStr);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowAL_New(int BowDocBsId, int CId, double Cost, double CostWgt);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowAL_Del(int BowALId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowAL_GetCId(int BowALId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BowAL_IsQueryDIdV(int BowALId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowAL_GetQueries(int BowALId);

         [DllImport("TextGardenLib.dll")]
         public static extern double BowAL_GetQueryDist(int BowALId, int QueryN);

         [DllImport("TextGardenLib.dll")]
         public static extern int BowAL_GetQueryDId(int BowALId, int QueryN);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowAL_MarkQueryDId(int BowALId, int QueryDId, bool AssignToCatP);

         [DllImport("TextGardenLib.dll")]
         public static extern void BowAL_MarkUnlabeledPosDocs(int BowALId);

         [DllImport("TextGardenLib.dll")]
         public static extern int RSet_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void RSet_Save(int RSetId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int RSet_LoadFromFile(String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void RSet_SaveToFile(int RSetId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void RSet_SaveXmlToFile(int RSetId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void RSet_Del(int RSetId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetUrlStr(int RSetId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetNextUrlStr(int RSetId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetQueryStr(int RSetId);

         [DllImport("TextGardenLib.dll")]
         public static extern int RSet_GetAllHits(int RSetId);

         [DllImport("TextGardenLib.dll")]
         public static extern int RSet_GetHits(int RSetId);

         [DllImport("TextGardenLib.dll")]
         public static extern int RSet_GetHitN(int RSetId, String UrlStr, bool LcP);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetHitUrlStr(int RSetId, int HitN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetHitTitleStr(int RSetId, int HitN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetHitSrcNm(int RSetId, int HitN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr RSet_GetHitCtxStr(int RSetId, int HitN);

         [DllImport("TextGardenLib.dll")]
         public static extern int Google_WebSearch(String QueryStr, int MxHits);

         [DllImport("TextGardenLib.dll")]
         public static extern int Google_NewsSearch(String QueryStr, int MxHits);

         [DllImport("TextGardenLib.dll")]
         public static extern int NmObjBs_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void NmObjBs_Save(int NmObjBsId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int NmObjBs_LoadFromFile(String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void NmObjBs_SaveToFile(int NmObjBsId, String FNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void NmObjBs_SaveTxtToFile(int NmObjBsId, String FqFNm, String SwFNm, String AbcFNm, String DocFNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void NmObjBs_Del(int NmObjBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int Conv_CpdToNmObjBs(int CpdSInId, String SwSetTypeNm, String CustSwSetFNm, String NrWordBsFNm, String WordTypeBsFNm, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern int Conv_CpdToNmObjBsFromFile(String CpdFNm, String SwSetTypeNm, String CustSwSetFNm, String NrWordBsFNm, String WordTypeBsFNm, int MxDocs);

         [DllImport("TextGardenLib.dll")]
         public static extern int Conv_NmObjBsToBow(int NmObjBsId, int MnNmObjFq);

         [DllImport("TextGardenLib.dll")]
         public static extern int Url_Get(String RelUrlStr, String BaseUrlStr);

         [DllImport("TextGardenLib.dll")]
         public static extern void Url_Del(int UrlId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Url_IsOk(int UrlId, int Scheme);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Url_IsOkHttp(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern int Url_GetScheme(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetUrlStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetRelUrlStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool Url_IsBaseUrl(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetBaseUrlStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetSchemeNm(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetHostNm(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetDmNm(int UrlId, int MxDmSegs);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetPortStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern int Url_GetPortN(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetPathStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern int Url_GetPathSegs(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetPathSeg(int UrlId, int PathSegN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetSearchStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr Url_GetFragIdStr(int UrlId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HttpResp_GetFromStr(String HttpRespStr);

         [DllImport("TextGardenLib.dll")]
         public static extern int HttpResp_GetFromFile(String HttpRespFNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void HttpResp_Del(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HttpResp_IsOk(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HttpResp_Len(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HttpResp_GetHdStr(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HttpResp_GetBodyAsMem(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HttpResp_GetBodyAsStr(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HttpResp_GetStatusCd(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HttpResp_IsStatusCd_Ok(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HttpResp_IsStatusCd_Redir(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HttpResp_GetReasonPhrase(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HttpResp_GetFlds(int HttpRespId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HttpResp_GetFldNm(int HttpRespId, int FldN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HttpResp_GetFldVal(int HttpRespId, int FldN);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HttpResp_IsFldNm(int HttpRespId, String FldNm);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HttpResp_GetFldValByNm(int HttpRespId, String FldNm);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HttpResp_IsFldVal(int HttpRespId, String FldNm, String FldVal);

         [DllImport("TextGardenLib.dll")]
         public static extern int HtmlDoc_GetFromStr(String HtmlStr);

         [DllImport("TextGardenLib.dll")]
         public static extern int HtmlDoc_GetFromFile(String HtmlFNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void HtmlDoc_Del(int HtmlDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HtmlDoc_GetToks(int HtmlDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern int HtmlDoc_GetTokSym(int HtmlDocId, int TokN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HtmlDoc_GetTokStr(int HtmlDocId, int TokN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HtmlDoc_GetTokFullStr(int HtmlDocId, int TokN);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HtmlDoc_IsTokArg(int HtmlDocId, int TokN, String ArgNm);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HtmlDoc_GetTokArg(int HtmlDocId, int TokN, String ArgNm, String DfArgVal);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HtmlDoc_IsTokUrl(int HtmlDocId, int TokN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HtmlDoc_GetTokUrlStr(int HtmlDocId, int TokN);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool HtmlDoc_IsBreakTag(String TagNm);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr HtmlDoc_GetSymStr(int Sym);

         [DllImport("TextGardenLib.dll")]
         public static extern int WebPg_Fetch(String UrlStr);

         [DllImport("TextGardenLib.dll")]
         public static extern void WebPg_Del(int WebPgId);

         [DllImport("TextGardenLib.dll")]
         public static extern int WebPg_GetUrls(int WebPgId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr WebPg_GetUrl(int WebPgId, int UrlN);

         [DllImport("TextGardenLib.dll")]
         public static extern int WebPg_GetHttpResp(int WebPgId);

         [DllImport("TextGardenLib.dll")]
         public static extern int WebPg_GetOutUrlStrV(int WebPgId);

         [DllImport("TextGardenLib.dll")]
         public static extern int Crawler_Gen();

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_Del(int CrawlerId);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_AddStartUrlStr(int CrawlerId, String StartUrlStr);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxUrls(int CrawlerId, int MxUrls);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxConns(int CrawlerId, int MxConns);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMnConns(int CrawlerId, int MnConns);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxConnsPerSrv(int CrawlerId, int MxConnsPerSrv);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutAfterFetchDelay(int CrawlerId, int AfterFetchDelaySecs);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxLev(int CrawlerId, int MxLev);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxDep(int CrawlerId, int MxDep);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMnQLen(int CrawlerId, int MnQLen);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutQResetMod(int CrawlerId, int QResetMod);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxContLen(int CrawlerId, int MxContLen);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxRetries(int CrawlerId, int MxRetries);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutMxQSegLen(int CrawlerId, int MxQSegLen);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutRevisitSecs(int CrawlerId, int RevisitSecs);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_PutRedirDmAllowed(int CrawlerId, bool RedirDmAllowedP);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_AddRqDmNm(int CrawlerId, String RqDmNmV);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_AddRqContTypeNm(int CrawlerId, String ContTypeNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_AddBadFExt(int CrawlerId, String FExt);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_OptHtmlCrawling(int CrawlerId);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_DefCrawlBs(int CrawlerId, String CrawlBsNm, String CrawlBsFPath, String CrawlBsFAccessNm, int CrawlBsMxSegLen);

         [DllImport("TextGardenLib.dll")]
         public static extern void Crawler_StartCrawling(int CrawlerId);

         [DllImport("TextGardenLib.dll")]
         public static extern int DMoz_GetCategories(int BowDocBsId, int BowDocWgtBsId, int BowDocPartId, String QueryStr, int MxCats);

         [DllImport("TextGardenLib.dll")]
         public static extern int DMoz_GetKeywords(int BowDocBsId, int BowDocWgtBsId, int BowDocPartId, String QueryStr, int MxCats, double KWordTsh);

         [DllImport("TextGardenLib.dll")]
         public static extern int BlobPt_New();

         [DllImport("TextGardenLib.dll")]
         public static extern void BlobPt_Del(int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern int CrawlBs_Open(String CrawlBsFNm);

         [DllImport("TextGardenLib.dll")]
         public static extern void CrawlBs_Close(int CrawlBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int CrawlBs_FFirstBlobPt(int CrawlBsId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool CrawlBs_FNextBlobPt(int CrawlBsId, int TrvBlobPtId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CrawlBs_GetDateTimeStr(int CrawlBsId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CrawlBs_GetUrlStr(int CrawlBsId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern int CrawlBs_GetHttpResp(int CrawlBsId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BlobBs_Open(String BlobBsFNm, int BlobBsFAccess);

         [DllImport("TextGardenLib.dll")]
         public static extern void BlobBs_Close(int BlobBsId);

         [DllImport("TextGardenLib.dll")]
         public static extern int BlobBs_GetFAccessCreate();

         [DllImport("TextGardenLib.dll")]
         public static extern int BlobBs_GetFAccessUpdate();

         [DllImport("TextGardenLib.dll")]
         public static extern int BlobBs_GetFAccessReadOnly();

         [DllImport("TextGardenLib.dll")]
         public static extern int BlobBs_FFirstBlobPt(int BlobBsId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool BlobBs_FNextBlobPt(int BlobBsId, int TrvBlobPtId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BlobBs_AddBlob(int BlobBsId, int MemId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BlobBs_PutBlob(int BlobBsId, int MemId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BlobBs_GetBlob(int BlobBsId, int BlobPtId, int MemId);

         [DllImport("TextGardenLib.dll")]
         public static extern void BlobBs_DelBlob(int BlobBsId, int BlobPtId);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_Load(int SInId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_Save(int CpDocId, int SOutId);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_New();

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_Del(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_FFirstCpd(int SInId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool CpDoc_FFNextCpd(int SInId, int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_PutDocNm(int CpDocId, String DocNm);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetDocNm(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_PutDateStr(int CpDocId, String DateStr);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetDateStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_AddCatNm(int CpDocId, String CatNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_GetCats(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetCatNm(int CpDocId, int CatN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetTxtStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetHtmlStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_PutTitleStr(int CpDocId, String TitleStr);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetTitleStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_PutHeadlineStr(int CpDocId, String HeadlineStr);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetHeadlineStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_PutBylineStr(int CpDocId, String BylineStr);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetBylineStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_PutDatelineStr(int CpDocId, String DatelineStr);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetDatelineStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_AddParStr(int CpDocId, String ParStr);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_GetPars(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetParStr(int CpDocId, int ParN);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetAllParStr(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_AddTopCdNm(int CpDocId, String TopCdNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_GetTopCds(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetTopCdNm(int CpDocId, int TopCdN);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_AddGeoCdNm(int CpDocId, String GeoCdNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_GetGeoCds(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetGeoCdNm(int CpDocId, int GeoCdN);

         [DllImport("TextGardenLib.dll")]
         public static extern void CpDoc_AddIndCdNm(int CpDocId, String IndCdNm);

         [DllImport("TextGardenLib.dll")]
         public static extern int CpDoc_GetIndCds(int CpDocId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr CpDoc_GetIndCdNm(int CpDocId, int IndCdN);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcDb_New();

         [DllImport("TextGardenLib.dll")]
         public static extern void OdbcDb_Del(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcDb_GetDataSourceNmV(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcDb_GetTbNmV(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcDb_GetColNmV(int OdbcDbId, String TbNm);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcDb_Connect(int OdbcDbId, String SrvNm, String UsrNm, String PwdStr);

         [DllImport("TextGardenLib.dll")]
         public static extern void OdbcDb_Disconnect(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcDb_IsConnected(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcDb_IsOk(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr OdbcDb_GetMsgStr(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcQuery_New(int OdbcDbId);

         [DllImport("TextGardenLib.dll")]
         public static extern void OdbcQuery_Del(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_ExeSql(int OdbcQueryId, String SqlStr, int ParamStrVId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_ExeSqlP1(int OdbcQueryId, String SqlStr, String ParamStr);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_ExeSqlP2(int OdbcQueryId, String SqlStr, String ParamStr1, String ParamStr2);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_ExeSqlP3(int OdbcQueryId, String SqlStr, String ParamStr1, String ParamStr2, String ParamStr3);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_IsResultSet(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcQuery_GetCols(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         public static extern int OdbcQuery_GetRowsAffected(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr OdbcQuery_GetColNm(int OdbcQueryId, int ColN);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_NextRow(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr OdbcQuery_GetColVal(int OdbcQueryId, int ColN, int MxValStrLen);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_IsOk(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         [return:MarshalAs(UnmanagedType.I1)]
         public static extern bool OdbcQuery_IsOpOk(int OdbcQueryId);

         [DllImport("TextGardenLib.dll")]
         public static extern IntPtr OdbcQuery_GetMsgStr(int OdbcQueryId);

      }//inner class



      public static void SetVerbosity(int VerbosityLev)
      {
          HTextGardenLib.SetVerbosity(VerbosityLev);
      }

      public static int GetVerbosity()
      {
         return HTextGardenLib.GetVerbosity();
      }

      public static int CStr_GetStrs()
      {
         return HTextGardenLib.CStr_GetStrs();
      }

      public static int CStr_GetStrV()
      {
         return HTextGardenLib.CStr_GetStrV();
      }

      public static int IntV_Gen()
      {
         return HTextGardenLib.IntV_Gen();
      }

      public static void IntV_Del(int IntVId)
      {
          HTextGardenLib.IntV_Del(IntVId);
      }

      public static int IntV_GetLen(int IntVId)
      {
         return HTextGardenLib.IntV_GetLen(IntVId);
      }

      public static int IntV_AddVal(int IntVId, int Val)
      {
         return HTextGardenLib.IntV_AddVal(IntVId, Val);
      }

      public static int IntV_GetVal(int IntVId, int ValN)
      {
         return HTextGardenLib.IntV_GetVal(IntVId, ValN);
      }

      public static void IntV_Sort(int IntVId, bool Asc)
      {
          HTextGardenLib.IntV_Sort(IntVId, Asc);
      }

      public static int IntV_Load(int SInId)
      {
         return HTextGardenLib.IntV_Load(SInId);
      }

      public static void IntV_Save(int IntVId, int SOutId)
      {
          HTextGardenLib.IntV_Save(IntVId, SOutId);
      }

      public static int StrV_Gen()
      {
         return HTextGardenLib.StrV_Gen();
      }

      public static void StrV_Del(int StrVId)
      {
          HTextGardenLib.StrV_Del(StrVId);
      }

      public static int StrV_GetLen(int StrVId)
      {
         return HTextGardenLib.StrV_GetLen(StrVId);
      }

      public static int StrV_AddVal(int StrVId, String Val)
      {
         return HTextGardenLib.StrV_AddVal(StrVId, Val);
      }

      public static String StrV_GetVal(int StrVId, int ValN)
      {
         IntPtr i = HTextGardenLib.StrV_GetVal(StrVId, ValN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void StrV_Sort(int StrVId, bool Asc)
      {
          HTextGardenLib.StrV_Sort(StrVId, Asc);
      }

      public static int StrV_Load(int SInId)
      {
         return HTextGardenLib.StrV_Load(SInId);
      }

      public static void StrV_Save(int StrVId, int SOutId)
      {
          HTextGardenLib.StrV_Save(StrVId, SOutId);
      }

      public static int FSPrV_Gen()
      {
         return HTextGardenLib.FSPrV_Gen();
      }

      public static void FSPrV_Del(int FSPrVId)
      {
          HTextGardenLib.FSPrV_Del(FSPrVId);
      }

      public static int FSPrV_GetLen(int FSPrVId)
      {
         return HTextGardenLib.FSPrV_GetLen(FSPrVId);
      }

      public static int FSPrV_AddVal(int FSPrVId, double Flt, String Str)
      {
         return HTextGardenLib.FSPrV_AddVal(FSPrVId, Flt, Str);
      }

      public static double FSPrV_GetFltVal(int FSPrVId, int ValN)
      {
         return HTextGardenLib.FSPrV_GetFltVal(FSPrVId, ValN);
      }

      public static String FSPrV_GetStrVal(int FSPrVId, int ValN)
      {
         IntPtr i = HTextGardenLib.FSPrV_GetStrVal(FSPrVId, ValN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void FSPrV_Sort(int FSPrVId, bool Asc)
      {
          HTextGardenLib.FSPrV_Sort(FSPrVId, Asc);
      }

      public static int FSPrV_GetTopVal(int FSPrVId, double WgtPrc, int MxVals, bool UseNegWgt)
      {
         return HTextGardenLib.FSPrV_GetTopVal(FSPrVId, WgtPrc, MxVals, UseNegWgt);
      }

      public static int FSPrV_Load(int SInId)
      {
         return HTextGardenLib.FSPrV_Load(SInId);
      }

      public static void FSPrV_Save(int StrVId, int SOutId)
      {
          HTextGardenLib.FSPrV_Save(StrVId, SOutId);
      }

      public static int SIn_GenStdIn()
      {
         return HTextGardenLib.SIn_GenStdIn();
      }

      public static int SIn_GenFileIn(String FNm)
      {
         return HTextGardenLib.SIn_GenFileIn(FNm);
      }

      public static int SIn_GenMemIn(int MemId)
      {
         return HTextGardenLib.SIn_GenMemIn(MemId);
      }

      public static int SIn_GenStrIn(String Str)
      {
         return HTextGardenLib.SIn_GenStrIn(Str);
      }

      public static void SIn_Del(int SInId)
      {
          HTextGardenLib.SIn_Del(SInId);
      }

      public static int SOut_GenStdOut()
      {
         return HTextGardenLib.SOut_GenStdOut();
      }

      public static int SOut_GenFileOut(String FNm, bool Append)
      {
         return HTextGardenLib.SOut_GenFileOut(FNm, Append);
      }

      public static int SOut_GenFileOut(String FNm)
      {
         return SOut_GenFileOut(FNm,false);
      }

      public static int SOut_GenMemOut(int MemId)
      {
         return HTextGardenLib.SOut_GenMemOut(MemId);
      }

      public static void SOut_Del(int SOutId)
      {
          HTextGardenLib.SOut_Del(SOutId);
      }

      public static bool Conv_HtmlToCpd(String InFPath, String OutCpdFNm, bool RecurseDirP, int MxDocs)
      {
         return HTextGardenLib.Conv_HtmlToCpd(InFPath, OutCpdFNm, RecurseDirP, MxDocs);
      }

      public static bool Conv_HtmlToCpd(String InFPath, String OutCpdFNm, bool RecurseDirP)
      {
         return Conv_HtmlToCpd(InFPath, OutCpdFNm, RecurseDirP,-1);
      }

      public static bool Conv_HtmlToCpd(String InFPath, String OutCpdFNm)
      {
         return Conv_HtmlToCpd(InFPath, OutCpdFNm,false);
      }

      public static bool Conv_Reuters21578ToCpd(String InFPath, String OutCpdFNm, int MxDocs)
      {
         return HTextGardenLib.Conv_Reuters21578ToCpd(InFPath, OutCpdFNm, MxDocs);
      }

      public static bool Conv_Reuters21578ToCpd(String InFPath, String OutCpdFNm)
      {
         return Conv_Reuters21578ToCpd(InFPath, OutCpdFNm,-1);
      }

      public static bool Conv_Reuters2000ToCpd(String InFPath, String OutCpdFNm, int MxDocs)
      {
         return HTextGardenLib.Conv_Reuters2000ToCpd(InFPath, OutCpdFNm, MxDocs);
      }

      public static bool Conv_Reuters2000ToCpd(String InFPath, String OutCpdFNm)
      {
         return Conv_Reuters2000ToCpd(InFPath, OutCpdFNm,-1);
      }

      public static bool Conv_AcmTechNewsToCpd(String InFPath, String OutCpdFNm, int MxDocs)
      {
         return HTextGardenLib.Conv_AcmTechNewsToCpd(InFPath, OutCpdFNm, MxDocs);
      }

      public static bool Conv_AcmTechNewsToCpd(String InFPath, String OutCpdFNm)
      {
         return Conv_AcmTechNewsToCpd(InFPath, OutCpdFNm,-1);
      }

      public static bool Conv_CiaWFBToCpd(String InFPath, String OutCpdFNm)
      {
         return HTextGardenLib.Conv_CiaWFBToCpd(InFPath, OutCpdFNm);
      }

      public static bool Conv_CpdToLnDocTxt(String InCpdFNm, String OutLnDocFNm)
      {
         return HTextGardenLib.Conv_CpdToLnDocTxt(InCpdFNm, OutLnDocFNm);
      }

      public static bool Conv_HtmlToBow(String InFPath, String OutBowFNm, bool RecurseDirP, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq)
      {
         return HTextGardenLib.Conv_HtmlToBow(InFPath, OutBowFNm, RecurseDirP, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
      }

      public static bool Conv_CpdToBow(String InCpdFNm, String OutBowFNm, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq)
      {
         return HTextGardenLib.Conv_CpdToBow(InCpdFNm, OutBowFNm, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
      }

      public static int Conv_GetBowFromCpd(int CpdSInId, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq)
      {
         return HTextGardenLib.Conv_GetBowFromCpd(CpdSInId, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
      }

      public static bool Conv_LnDocToBow(String InLnDocFNm, String OutBowFNm, bool NamedP, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq)
      {
         return HTextGardenLib.Conv_LnDocToBow(InLnDocFNm, OutBowFNm, NamedP, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
      }

      public static bool Conv_Reuters21578ToBow(String InFPath, String OutBowFNm, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq)
      {
         return HTextGardenLib.Conv_Reuters21578ToBow(InFPath, OutBowFNm, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
      }

      public static bool Conv_CiaWFBToBow(String InFPath, String OutBowFNm, int Recs, String SwSetTypeNm, String StemmerTypeNm, int MxNGramLen, int MnNGramFq)
      {
         return HTextGardenLib.Conv_CiaWFBToBow(InFPath, OutBowFNm, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
      }

      public static int BowDocBs_New(String SwSetTypeNm, String StemmerTypeNm)
      {
         return HTextGardenLib.BowDocBs_New(SwSetTypeNm, StemmerTypeNm);
      }

      public static int BowDocBs_Load(int SInId)
      {
         return HTextGardenLib.BowDocBs_Load(SInId);
      }

      public static void BowDocBs_Save(int BowDocBsId, int SOutId)
      {
          HTextGardenLib.BowDocBs_Save(BowDocBsId, SOutId);
      }

      public static int BowDocBs_LoadFromFile(String FNm)
      {
         return HTextGardenLib.BowDocBs_LoadFromFile(FNm);
      }

      public static void BowDocBs_SaveToFile(int BowDocBsId, String FNm)
      {
          HTextGardenLib.BowDocBs_SaveToFile(BowDocBsId, FNm);
      }

      public static void BowDocBs_SaveStatToFile(int BowDocBsId, String FNm)
      {
          HTextGardenLib.BowDocBs_SaveStatToFile(BowDocBsId, FNm);
      }

      public static void BowDocBs_Del(int BowDocBsId)
      {
          HTextGardenLib.BowDocBs_Del(BowDocBsId);
      }

      public static int BowDocBs_GetWords(int BowDocBsId)
      {
         return HTextGardenLib.BowDocBs_GetWords(BowDocBsId);
      }

      public static bool BowDocBs_IsWordStr(int BowDocBsId, String WordStr)
      {
         return HTextGardenLib.BowDocBs_IsWordStr(BowDocBsId, WordStr);
      }

      public static int BowDocBs_GetWId(int BowDocBsId, String WordStr)
      {
         return HTextGardenLib.BowDocBs_GetWId(BowDocBsId, WordStr);
      }

      public static String BowDocBs_GetWordStr(int BowDocBsId, int WId)
      {
         IntPtr i = HTextGardenLib.BowDocBs_GetWordStr(BowDocBsId, WId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int BowDocBs_GetCats(int BowDocBsId)
      {
         return HTextGardenLib.BowDocBs_GetCats(BowDocBsId);
      }

      public static bool BowDocBs_IsCatNm(int BowDocBsId, String CatNm)
      {
         return HTextGardenLib.BowDocBs_IsCatNm(BowDocBsId, CatNm);
      }

      public static int BowDocBs_GetCId(int BowDocBsId, String CatNm)
      {
         return HTextGardenLib.BowDocBs_GetCId(BowDocBsId, CatNm);
      }

      public static String BowDocBs_GetCatNm(int BowDocBsId, int CId)
      {
         IntPtr i = HTextGardenLib.BowDocBs_GetCatNm(BowDocBsId, CId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int BowDocBs_AddHtmlDocStr(int BowDocBsId, String DocNm, String HtmlDocStr, String CatNmVStr, bool SaveDocP)
      {
         return HTextGardenLib.BowDocBs_AddHtmlDocStr(BowDocBsId, DocNm, HtmlDocStr, CatNmVStr, SaveDocP);
      }

      public static int BowDocBs_AddHtmlDocStr(int BowDocBsId, String DocNm, String HtmlDocStr, String CatNmVStr)
      {
         return BowDocBs_AddHtmlDocStr(BowDocBsId, DocNm, HtmlDocStr, CatNmVStr,false);
      }

      public static int BowDocBs_GetDocs(int BowDocBsId)
      {
         return HTextGardenLib.BowDocBs_GetDocs(BowDocBsId);
      }

      public static bool BowDocBs_IsDocNm(int BowDocBsId, String DocNm)
      {
         return HTextGardenLib.BowDocBs_IsDocNm(BowDocBsId, DocNm);
      }

      public static int BowDocBs_GetDId(int BowDocBsId, String DocNm)
      {
         return HTextGardenLib.BowDocBs_GetDId(BowDocBsId, DocNm);
      }

      public static String BowDocBs_GetDocNm(int BowDocBsId, int DId)
      {
         IntPtr i = HTextGardenLib.BowDocBs_GetDocNm(BowDocBsId, DId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int BowDocBs_GetDocWIds(int BowDocBsId, int DId)
      {
         return HTextGardenLib.BowDocBs_GetDocWIds(BowDocBsId, DId);
      }

      public static int BowDocBs_GetDocWId(int BowDocBsId, int DId, int DocWIdN)
      {
         return HTextGardenLib.BowDocBs_GetDocWId(BowDocBsId, DId, DocWIdN);
      }

      public static int BowDocBs_GetDocWIdN(int BowDocBsId, int DId, int DocWId)
      {
         return HTextGardenLib.BowDocBs_GetDocWIdN(BowDocBsId, DId, DocWId);
      }

      public static void BowDocBs_PutDocWFq(int BowDocBsId, int DId, int DocWIdN, double WFq)
      {
          HTextGardenLib.BowDocBs_PutDocWFq(BowDocBsId, DId, DocWIdN, WFq);
      }

      public static double BowDocBs_GetDocWFq(int BowDocBsId, int DId, int DocWIdN)
      {
         return HTextGardenLib.BowDocBs_GetDocWFq(BowDocBsId, DId, DocWIdN);
      }

      public static int BowDocBs_GetDocCIds(int BowDocBsId, int DId)
      {
         return HTextGardenLib.BowDocBs_GetDocCIds(BowDocBsId, DId);
      }

      public static int BowDocBs_GetDocCId(int BowDocBsId, int DId, int DocCIdN)
      {
         return HTextGardenLib.BowDocBs_GetDocCId(BowDocBsId, DId, DocCIdN);
      }

      public static int BowDocWgtBs_Gen(int BowDocBsId)
      {
         return HTextGardenLib.BowDocWgtBs_Gen(BowDocBsId);
      }

      public static void BowDocWgtBs_Del(int BowDocWgtBsId)
      {
          HTextGardenLib.BowDocWgtBs_Del(BowDocWgtBsId);
      }

      public static int BowDocWgtBs_GetDocs(int BowDocWgtBsId)
      {
         return HTextGardenLib.BowDocWgtBs_GetDocs(BowDocWgtBsId);
      }

      public static int BowDocWgtBs_GetDocId(int BowDocWgtBsId, int DIdN)
      {
         return HTextGardenLib.BowDocWgtBs_GetDocId(BowDocWgtBsId, DIdN);
      }

      public static int BowDocWgtBs_GetDocWIds(int BowDocWgtBsId, int DId)
      {
         return HTextGardenLib.BowDocWgtBs_GetDocWIds(BowDocWgtBsId, DId);
      }

      public static int BowDocWgtBs_GetDocWId(int BowDocWgtBsId, int DId, int DocWIdN)
      {
         return HTextGardenLib.BowDocWgtBs_GetDocWId(BowDocWgtBsId, DId, DocWIdN);
      }

      public static double BowDocWgtBs_GetDocWWgt(int BowDocWgtBsId, int DId, int DocWIdN)
      {
         return HTextGardenLib.BowDocWgtBs_GetDocWWgt(BowDocWgtBsId, DId, DocWIdN);
      }

      public static int BowDocWgtBs_GetWgtWordPrV(int BowDocWgtBsId, int BowDocBsId, int DId, int TopWords, double TopWordsWgtPrc)
      {
         return HTextGardenLib.BowDocWgtBs_GetWgtWordPrV(BowDocWgtBsId, BowDocBsId, DId, TopWords, TopWordsWgtPrc);
      }

      public static int BowDocWgtBs_Search(int BowDocWgtBsId, int BowDocBsId, String QueryStr)
      {
         return HTextGardenLib.BowDocWgtBs_Search(BowDocWgtBsId, BowDocBsId, QueryStr);
      }

      public static int BowDocPart_Load(int SInId)
      {
         return HTextGardenLib.BowDocPart_Load(SInId);
      }

      public static void BowDocPart_Save(int BowDocPartId, int SOutId)
      {
          HTextGardenLib.BowDocPart_Save(BowDocPartId, SOutId);
      }

      public static int BowDocPart_LoadFromFile(String FNm)
      {
         return HTextGardenLib.BowDocPart_LoadFromFile(FNm);
      }

      public static void BowDocPart_SaveToFile(int BowDocPartId, String FNm)
      {
          HTextGardenLib.BowDocPart_SaveToFile(BowDocPartId, FNm);
      }

      public static void BowDocPart_SaveStatToFile(int BowDocPartId, int BowDocBsId, String FNm)
      {
          HTextGardenLib.BowDocPart_SaveStatToFile(BowDocPartId, BowDocBsId, FNm);
      }

      public static void BowDocPart_Del(int BowDocPartId)
      {
          HTextGardenLib.BowDocPart_Del(BowDocPartId);
      }

      public static int BowDocPart_GetKMeans(int BowDocBsId, int Clusts, int ClustTrials, double ConvergEps, int MnDocsPerClust, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs)
      {
         return HTextGardenLib.BowDocPart_GetKMeans(BowDocBsId, Clusts, ClustTrials, ConvergEps, MnDocsPerClust, CutWordWgtSumPrc, MnWordFq, RndSeed, MxDocs);
      }

      public static int BowDocPart_GetHKMeans(int BowDocBsId, int MxDocsPerLeafClust, int ClustTrials, double ConvergEps, int MnDocsPerClust, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs)
      {
         return HTextGardenLib.BowDocPart_GetHKMeans(BowDocBsId, MxDocsPerLeafClust, ClustTrials, ConvergEps, MnDocsPerClust, CutWordWgtSumPrc, MnWordFq, RndSeed, MxDocs);
      }

      public static int BowDocPart_GetClusts(int BowDocPartId)
      {
         return HTextGardenLib.BowDocPart_GetClusts(BowDocPartId);
      }

      public static int BowDocPart_GetDocs(int BowDocPartId, int ClustN)
      {
         return HTextGardenLib.BowDocPart_GetDocs(BowDocPartId, ClustN);
      }

      public static int BowDocPart_GetDId(int BowDocPartId, int ClustN, int DIdN)
      {
         return HTextGardenLib.BowDocPart_GetDId(BowDocPartId, ClustN, DIdN);
      }

      public static double BowDocPart_GetMeanSim(int BowDocPartId, int ClustN)
      {
         return HTextGardenLib.BowDocPart_GetMeanSim(BowDocPartId, ClustN);
      }

      public static double BowDocPart_GetDCSim(int BowDocPartId, int ClustN, int DId)
      {
         return HTextGardenLib.BowDocPart_GetDCSim(BowDocPartId, ClustN, DId);
      }

      public static int BowDocPart_GetConceptWords(int BowDocPartId, int ClustN)
      {
         return HTextGardenLib.BowDocPart_GetConceptWords(BowDocPartId, ClustN);
      }

      public static int BowDocPart_GetConceptWId(int BowDocPartId, int ClustN, int WIdN)
      {
         return HTextGardenLib.BowDocPart_GetConceptWId(BowDocPartId, ClustN, WIdN);
      }

      public static double BowDocPart_GetConceptWWgt(int BowDocPartId, int ClustN, int WIdN)
      {
         return HTextGardenLib.BowDocPart_GetConceptWWgt(BowDocPartId, ClustN, WIdN);
      }

      public static bool BowDocPart_IsSubPart(int BowDocPartId, int ClustN)
      {
         return HTextGardenLib.BowDocPart_IsSubPart(BowDocPartId, ClustN);
      }

      public static int BowDocPart_GetSubPart(int BowDocPartId, int ClustN)
      {
         return HTextGardenLib.BowDocPart_GetSubPart(BowDocPartId, ClustN);
      }

      public static int SemSpace_Load(int SInId)
      {
         return HTextGardenLib.SemSpace_Load(SInId);
      }

      public static void SemSpace_Save(int SemSpaceId, int SOutId)
      {
          HTextGardenLib.SemSpace_Save(SemSpaceId, SOutId);
      }

      public static int SemSpace_LoadFromFile(String FNm)
      {
         return HTextGardenLib.SemSpace_LoadFromFile(FNm);
      }

      public static void SemSpace_SaveToFile(int SemSpaceId, String FNm)
      {
          HTextGardenLib.SemSpace_SaveToFile(SemSpaceId, FNm);
      }

      public static void SemSpace_SaveStatToFile(int SemSpaceId, int BowDocBsId, String FNm)
      {
          HTextGardenLib.SemSpace_SaveStatToFile(SemSpaceId, BowDocBsId, FNm);
      }

      public static void SemSpace_Del(int SemSpaceId)
      {
          HTextGardenLib.SemSpace_Del(SemSpaceId);
      }

      public static int SemSpace_GetDims(int SemSpaceId)
      {
         return HTextGardenLib.SemSpace_GetDims(SemSpaceId);
      }

      public static int SemSpace_GetDim(int SemSpaceId, int BowDocBsId, int DimN)
      {
         return HTextGardenLib.SemSpace_GetDim(SemSpaceId, BowDocBsId, DimN);
      }

      public static int SemSpace_GetLSI(int BowDocBsId, int SpaceDims)
      {
         return HTextGardenLib.SemSpace_GetLSI(BowDocBsId, SpaceDims);
      }

      public static int SemSpace_GetLSIFromBowPart(int BowDocPartId, int SpaceDims)
      {
         return HTextGardenLib.SemSpace_GetLSIFromBowPart(BowDocPartId, SpaceDims);
      }

      public static int SemSpace_GetPCA(int BowDocBsId)
      {
         return HTextGardenLib.SemSpace_GetPCA(BowDocBsId);
      }

      public static int BowMd_Load(int SInId)
      {
         return HTextGardenLib.BowMd_Load(SInId);
      }

      public static void BowMd_Save(int BowMdId, int SOutId)
      {
          HTextGardenLib.BowMd_Save(BowMdId, SOutId);
      }

      public static int BowMd_LoadFromFile(String FNm, int BowDocBsId)
      {
         return HTextGardenLib.BowMd_LoadFromFile(FNm, BowDocBsId);
      }

      public static void BowMd_SaveToFile(int BowMdId, String FNm)
      {
          HTextGardenLib.BowMd_SaveToFile(BowMdId, FNm);
      }

      public static void BowMd_Del(int BowMdId)
      {
          HTextGardenLib.BowMd_Del(BowMdId);
      }

      public static bool BowMd_IsCat(int BowMdId)
      {
         return HTextGardenLib.BowMd_IsCat(BowMdId);
      }

      public static String BowMd_GetCatNm(int BowMdId)
      {
         IntPtr i = HTextGardenLib.BowMd_GetCatNm(BowMdId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool BowMd_IsLinComb(int BowMdId)
      {
         return HTextGardenLib.BowMd_IsLinComb(BowMdId);
      }

      public static int BowMd_GetLinCombWgtWordPrV(int BowMdId, int BowDocBsId)
      {
         return HTextGardenLib.BowMd_GetLinCombWgtWordPrV(BowMdId, BowDocBsId);
      }

      public static double BowMd_GetLinCombTsh(int BowMdId)
      {
         return HTextGardenLib.BowMd_GetLinCombTsh(BowMdId);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost, double CostWgt, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs)
      {
         return HTextGardenLib.BowMd_GetBinSVM(BowDocBsId, CId, Cost, CostWgt, CutWordWgtSumPrc, MnWordFq, RndSeed, MxDocs);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost, double CostWgt, double CutWordWgtSumPrc, int MnWordFq, int RndSeed)
      {
         return BowMd_GetBinSVM(BowDocBsId, CId, Cost, CostWgt, CutWordWgtSumPrc, MnWordFq, RndSeed,-1);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost, double CostWgt, double CutWordWgtSumPrc, int MnWordFq)
      {
         return BowMd_GetBinSVM(BowDocBsId, CId, Cost, CostWgt, CutWordWgtSumPrc, MnWordFq,0);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost, double CostWgt, double CutWordWgtSumPrc)
      {
         return BowMd_GetBinSVM(BowDocBsId, CId, Cost, CostWgt, CutWordWgtSumPrc,0);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost, double CostWgt)
      {
         return BowMd_GetBinSVM(BowDocBsId, CId, Cost, CostWgt,0);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId, double Cost)
      {
         return BowMd_GetBinSVM(BowDocBsId, CId, Cost,1);
      }

      public static int BowMd_GetBinSVM(int BowDocBsId, int CId)
      {
         return BowMd_GetBinSVM(BowDocBsId, CId,1);
      }

      public static int BowMd_GetOneClassSVM(int BowDocBsId, int CId, double Nu, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs)
      {
         return HTextGardenLib.BowMd_GetOneClassSVM(BowDocBsId, CId, Nu, CutWordWgtSumPrc, MnWordFq, RndSeed, MxDocs);
      }

      public static int BowMd_GetOneClassSVM(int BowDocBsId, int CId, double Nu, double CutWordWgtSumPrc, int MnWordFq, int RndSeed)
      {
         return BowMd_GetOneClassSVM(BowDocBsId, CId, Nu, CutWordWgtSumPrc, MnWordFq, RndSeed,-1);
      }

      public static int BowMd_GetOneClassSVM(int BowDocBsId, int CId, double Nu, double CutWordWgtSumPrc, int MnWordFq)
      {
         return BowMd_GetOneClassSVM(BowDocBsId, CId, Nu, CutWordWgtSumPrc, MnWordFq,0);
      }

      public static int BowMd_GetOneClassSVM(int BowDocBsId, int CId, double Nu, double CutWordWgtSumPrc)
      {
         return BowMd_GetOneClassSVM(BowDocBsId, CId, Nu, CutWordWgtSumPrc,0);
      }

      public static int BowMd_GetOneClassSVM(int BowDocBsId, int CId, double Nu)
      {
         return BowMd_GetOneClassSVM(BowDocBsId, CId, Nu,0);
      }

      public static int BowMd_GetOneClassSVM(int BowDocBsId, int CId)
      {
         return BowMd_GetOneClassSVM(BowDocBsId, CId,0.1);
      }

      public static int BowMd_GetWinnow(int BowDocBsId, int CId, double Beta, double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs)
      {
         return HTextGardenLib.BowMd_GetWinnow(BowDocBsId, CId, Beta, CutWordWgtSumPrc, MnWordFq, RndSeed, MxDocs);
      }

      public static int BowMd_GetWinnow(int BowDocBsId, int CId, double Beta, double CutWordWgtSumPrc, int MnWordFq, int RndSeed)
      {
         return BowMd_GetWinnow(BowDocBsId, CId, Beta, CutWordWgtSumPrc, MnWordFq, RndSeed,-1);
      }

      public static int BowMd_GetWinnow(int BowDocBsId, int CId, double Beta, double CutWordWgtSumPrc, int MnWordFq)
      {
         return BowMd_GetWinnow(BowDocBsId, CId, Beta, CutWordWgtSumPrc, MnWordFq,0);
      }

      public static int BowMd_GetWinnow(int BowDocBsId, int CId, double Beta, double CutWordWgtSumPrc)
      {
         return BowMd_GetWinnow(BowDocBsId, CId, Beta, CutWordWgtSumPrc,0);
      }

      public static int BowMd_GetWinnow(int BowDocBsId, int CId, double Beta)
      {
         return BowMd_GetWinnow(BowDocBsId, CId, Beta,0);
      }

      public static int BowMd_GetWinnow(int BowDocBsId, int CId)
      {
         return BowMd_GetWinnow(BowDocBsId, CId,0.95);
      }

      public static double BowMd_GetCfyFromDocBs(int BowMdId, int BowDocBsId, int DId)
      {
         return HTextGardenLib.BowMd_GetCfyFromDocBs(BowMdId, BowDocBsId, DId);
      }

      public static double BowMd_GetCfyFromHtml(int BowMdId, int BowDocBsId, String HtmlStr)
      {
         return HTextGardenLib.BowMd_GetCfyFromHtml(BowMdId, BowDocBsId, HtmlStr);
      }

      public static int BowAL_New(int BowDocBsId, int CId, double Cost, double CostWgt)
      {
         return HTextGardenLib.BowAL_New(BowDocBsId, CId, Cost, CostWgt);
      }

      public static int BowAL_New(int BowDocBsId, int CId, double Cost)
      {
         return BowAL_New(BowDocBsId, CId, Cost,1);
      }

      public static int BowAL_New(int BowDocBsId, int CId)
      {
         return BowAL_New(BowDocBsId, CId,1);
      }

      public static void BowAL_Del(int BowALId)
      {
          HTextGardenLib.BowAL_Del(BowALId);
      }

      public static int BowAL_GetCId(int BowALId)
      {
         return HTextGardenLib.BowAL_GetCId(BowALId);
      }

      public static bool BowAL_IsQueryDIdV(int BowALId)
      {
         return HTextGardenLib.BowAL_IsQueryDIdV(BowALId);
      }

      public static int BowAL_GetQueries(int BowALId)
      {
         return HTextGardenLib.BowAL_GetQueries(BowALId);
      }

      public static double BowAL_GetQueryDist(int BowALId, int QueryN)
      {
         return HTextGardenLib.BowAL_GetQueryDist(BowALId, QueryN);
      }

      public static int BowAL_GetQueryDId(int BowALId, int QueryN)
      {
         return HTextGardenLib.BowAL_GetQueryDId(BowALId, QueryN);
      }

      public static void BowAL_MarkQueryDId(int BowALId, int QueryDId, bool AssignToCatP)
      {
          HTextGardenLib.BowAL_MarkQueryDId(BowALId, QueryDId, AssignToCatP);
      }

      public static void BowAL_MarkUnlabeledPosDocs(int BowALId)
      {
          HTextGardenLib.BowAL_MarkUnlabeledPosDocs(BowALId);
      }

      public static int RSet_Load(int SInId)
      {
         return HTextGardenLib.RSet_Load(SInId);
      }

      public static void RSet_Save(int RSetId, int SOutId)
      {
          HTextGardenLib.RSet_Save(RSetId, SOutId);
      }

      public static int RSet_LoadFromFile(String FNm)
      {
         return HTextGardenLib.RSet_LoadFromFile(FNm);
      }

      public static void RSet_SaveToFile(int RSetId, String FNm)
      {
          HTextGardenLib.RSet_SaveToFile(RSetId, FNm);
      }

      public static void RSet_SaveXmlToFile(int RSetId, String FNm)
      {
          HTextGardenLib.RSet_SaveXmlToFile(RSetId, FNm);
      }

      public static void RSet_Del(int RSetId)
      {
          HTextGardenLib.RSet_Del(RSetId);
      }

      public static String RSet_GetUrlStr(int RSetId)
      {
         IntPtr i = HTextGardenLib.RSet_GetUrlStr(RSetId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String RSet_GetNextUrlStr(int RSetId)
      {
         IntPtr i = HTextGardenLib.RSet_GetNextUrlStr(RSetId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String RSet_GetQueryStr(int RSetId)
      {
         IntPtr i = HTextGardenLib.RSet_GetQueryStr(RSetId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int RSet_GetAllHits(int RSetId)
      {
         return HTextGardenLib.RSet_GetAllHits(RSetId);
      }

      public static int RSet_GetHits(int RSetId)
      {
         return HTextGardenLib.RSet_GetHits(RSetId);
      }

      public static int RSet_GetHitN(int RSetId, String UrlStr, bool LcP)
      {
         return HTextGardenLib.RSet_GetHitN(RSetId, UrlStr, LcP);
      }

      public static String RSet_GetHitUrlStr(int RSetId, int HitN)
      {
         IntPtr i = HTextGardenLib.RSet_GetHitUrlStr(RSetId, HitN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String RSet_GetHitTitleStr(int RSetId, int HitN)
      {
         IntPtr i = HTextGardenLib.RSet_GetHitTitleStr(RSetId, HitN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String RSet_GetHitSrcNm(int RSetId, int HitN)
      {
         IntPtr i = HTextGardenLib.RSet_GetHitSrcNm(RSetId, HitN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String RSet_GetHitCtxStr(int RSetId, int HitN)
      {
         IntPtr i = HTextGardenLib.RSet_GetHitCtxStr(RSetId, HitN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int Google_WebSearch(String QueryStr, int MxHits)
      {
         return HTextGardenLib.Google_WebSearch(QueryStr, MxHits);
      }

      public static int Google_WebSearch(String QueryStr)
      {
         return Google_WebSearch(QueryStr,-1);
      }

      public static int Google_NewsSearch(String QueryStr, int MxHits)
      {
         return HTextGardenLib.Google_NewsSearch(QueryStr, MxHits);
      }

      public static int Google_NewsSearch(String QueryStr)
      {
         return Google_NewsSearch(QueryStr,-1);
      }

      public static int NmObjBs_Load(int SInId)
      {
         return HTextGardenLib.NmObjBs_Load(SInId);
      }

      public static void NmObjBs_Save(int NmObjBsId, int SOutId)
      {
          HTextGardenLib.NmObjBs_Save(NmObjBsId, SOutId);
      }

      public static int NmObjBs_LoadFromFile(String FNm)
      {
         return HTextGardenLib.NmObjBs_LoadFromFile(FNm);
      }

      public static void NmObjBs_SaveToFile(int NmObjBsId, String FNm)
      {
          HTextGardenLib.NmObjBs_SaveToFile(NmObjBsId, FNm);
      }

      public static void NmObjBs_SaveTxtToFile(int NmObjBsId, String FqFNm, String SwFNm, String AbcFNm, String DocFNm)
      {
          HTextGardenLib.NmObjBs_SaveTxtToFile(NmObjBsId, FqFNm, SwFNm, AbcFNm, DocFNm);
      }

      public static void NmObjBs_Del(int NmObjBsId)
      {
          HTextGardenLib.NmObjBs_Del(NmObjBsId);
      }

      public static int Conv_CpdToNmObjBs(int CpdSInId, String SwSetTypeNm, String CustSwSetFNm, String NrWordBsFNm, String WordTypeBsFNm, int MxDocs)
      {
         return HTextGardenLib.Conv_CpdToNmObjBs(CpdSInId, SwSetTypeNm, CustSwSetFNm, NrWordBsFNm, WordTypeBsFNm, MxDocs);
      }

      public static int Conv_CpdToNmObjBs(int CpdSInId, String SwSetTypeNm, String CustSwSetFNm, String NrWordBsFNm, String WordTypeBsFNm)
      {
         return Conv_CpdToNmObjBs(CpdSInId, SwSetTypeNm, CustSwSetFNm, NrWordBsFNm, WordTypeBsFNm,-1);
      }

      public static int Conv_CpdToNmObjBsFromFile(String CpdFNm, String SwSetTypeNm, String CustSwSetFNm, String NrWordBsFNm, String WordTypeBsFNm, int MxDocs)
      {
         return HTextGardenLib.Conv_CpdToNmObjBsFromFile(CpdFNm, SwSetTypeNm, CustSwSetFNm, NrWordBsFNm, WordTypeBsFNm, MxDocs);
      }

      public static int Conv_CpdToNmObjBsFromFile(String CpdFNm, String SwSetTypeNm, String CustSwSetFNm, String NrWordBsFNm, String WordTypeBsFNm)
      {
         return Conv_CpdToNmObjBsFromFile(CpdFNm, SwSetTypeNm, CustSwSetFNm, NrWordBsFNm, WordTypeBsFNm,-1);
      }

      public static int Conv_NmObjBsToBow(int NmObjBsId, int MnNmObjFq)
      {
         return HTextGardenLib.Conv_NmObjBsToBow(NmObjBsId, MnNmObjFq);
      }

      public static int Conv_NmObjBsToBow(int NmObjBsId)
      {
         return Conv_NmObjBsToBow(NmObjBsId,-1);
      }

      public static int Url_Get(String RelUrlStr, String BaseUrlStr)
      {
         return HTextGardenLib.Url_Get(RelUrlStr, BaseUrlStr);
      }

      public static void Url_Del(int UrlId)
      {
          HTextGardenLib.Url_Del(UrlId);
      }

      public static bool Url_IsOk(int UrlId, int Scheme)
      {
         return HTextGardenLib.Url_IsOk(UrlId, Scheme);
      }

      public static bool Url_IsOk(int UrlId)
      {
         return Url_IsOk(UrlId,0);
      }

      public static bool Url_IsOkHttp(int UrlId)
      {
         return HTextGardenLib.Url_IsOkHttp(UrlId);
      }

      public static int Url_GetScheme(int UrlId)
      {
         return HTextGardenLib.Url_GetScheme(UrlId);
      }

      public static String Url_GetUrlStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetUrlStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetRelUrlStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetRelUrlStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool Url_IsBaseUrl(int UrlId)
      {
         return HTextGardenLib.Url_IsBaseUrl(UrlId);
      }

      public static String Url_GetBaseUrlStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetBaseUrlStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetSchemeNm(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetSchemeNm(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetHostNm(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetHostNm(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetDmNm(int UrlId, int MxDmSegs)
      {
         IntPtr i = HTextGardenLib.Url_GetDmNm(UrlId, MxDmSegs);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetDmNm(int UrlId)
      {
         return Url_GetDmNm(UrlId,-1);
      }

      public static String Url_GetPortStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetPortStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int Url_GetPortN(int UrlId)
      {
         return HTextGardenLib.Url_GetPortN(UrlId);
      }

      public static String Url_GetPathStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetPathStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int Url_GetPathSegs(int UrlId)
      {
         return HTextGardenLib.Url_GetPathSegs(UrlId);
      }

      public static String Url_GetPathSeg(int UrlId, int PathSegN)
      {
         IntPtr i = HTextGardenLib.Url_GetPathSeg(UrlId, PathSegN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetSearchStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetSearchStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String Url_GetFragIdStr(int UrlId)
      {
         IntPtr i = HTextGardenLib.Url_GetFragIdStr(UrlId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int HttpResp_GetFromStr(String HttpRespStr)
      {
         return HTextGardenLib.HttpResp_GetFromStr(HttpRespStr);
      }

      public static int HttpResp_GetFromFile(String HttpRespFNm)
      {
         return HTextGardenLib.HttpResp_GetFromFile(HttpRespFNm);
      }

      public static void HttpResp_Del(int HttpRespId)
      {
          HTextGardenLib.HttpResp_Del(HttpRespId);
      }

      public static bool HttpResp_IsOk(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_IsOk(HttpRespId);
      }

      public static int HttpResp_Len(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_Len(HttpRespId);
      }

      public static String HttpResp_GetHdStr(int HttpRespId)
      {
         IntPtr i = HTextGardenLib.HttpResp_GetHdStr(HttpRespId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int HttpResp_GetBodyAsMem(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_GetBodyAsMem(HttpRespId);
      }

      public static String HttpResp_GetBodyAsStr(int HttpRespId)
      {
         IntPtr i = HTextGardenLib.HttpResp_GetBodyAsStr(HttpRespId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int HttpResp_GetStatusCd(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_GetStatusCd(HttpRespId);
      }

      public static bool HttpResp_IsStatusCd_Ok(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_IsStatusCd_Ok(HttpRespId);
      }

      public static bool HttpResp_IsStatusCd_Redir(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_IsStatusCd_Redir(HttpRespId);
      }

      public static String HttpResp_GetReasonPhrase(int HttpRespId)
      {
         IntPtr i = HTextGardenLib.HttpResp_GetReasonPhrase(HttpRespId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int HttpResp_GetFlds(int HttpRespId)
      {
         return HTextGardenLib.HttpResp_GetFlds(HttpRespId);
      }

      public static String HttpResp_GetFldNm(int HttpRespId, int FldN)
      {
         IntPtr i = HTextGardenLib.HttpResp_GetFldNm(HttpRespId, FldN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String HttpResp_GetFldVal(int HttpRespId, int FldN)
      {
         IntPtr i = HTextGardenLib.HttpResp_GetFldVal(HttpRespId, FldN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool HttpResp_IsFldNm(int HttpRespId, String FldNm)
      {
         return HTextGardenLib.HttpResp_IsFldNm(HttpRespId, FldNm);
      }

      public static String HttpResp_GetFldValByNm(int HttpRespId, String FldNm)
      {
         IntPtr i = HTextGardenLib.HttpResp_GetFldValByNm(HttpRespId, FldNm);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool HttpResp_IsFldVal(int HttpRespId, String FldNm, String FldVal)
      {
         return HTextGardenLib.HttpResp_IsFldVal(HttpRespId, FldNm, FldVal);
      }

      public static int HtmlDoc_GetFromStr(String HtmlStr)
      {
         return HTextGardenLib.HtmlDoc_GetFromStr(HtmlStr);
      }

      public static int HtmlDoc_GetFromFile(String HtmlFNm)
      {
         return HTextGardenLib.HtmlDoc_GetFromFile(HtmlFNm);
      }

      public static void HtmlDoc_Del(int HtmlDocId)
      {
          HTextGardenLib.HtmlDoc_Del(HtmlDocId);
      }

      public static int HtmlDoc_GetToks(int HtmlDocId)
      {
         return HTextGardenLib.HtmlDoc_GetToks(HtmlDocId);
      }

      public static int HtmlDoc_GetTokSym(int HtmlDocId, int TokN)
      {
         return HTextGardenLib.HtmlDoc_GetTokSym(HtmlDocId, TokN);
      }

      public static String HtmlDoc_GetTokStr(int HtmlDocId, int TokN)
      {
         IntPtr i = HTextGardenLib.HtmlDoc_GetTokStr(HtmlDocId, TokN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String HtmlDoc_GetTokFullStr(int HtmlDocId, int TokN)
      {
         IntPtr i = HTextGardenLib.HtmlDoc_GetTokFullStr(HtmlDocId, TokN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool HtmlDoc_IsTokArg(int HtmlDocId, int TokN, String ArgNm)
      {
         return HTextGardenLib.HtmlDoc_IsTokArg(HtmlDocId, TokN, ArgNm);
      }

      public static String HtmlDoc_GetTokArg(int HtmlDocId, int TokN, String ArgNm, String DfArgVal)
      {
         IntPtr i = HTextGardenLib.HtmlDoc_GetTokArg(HtmlDocId, TokN, ArgNm, DfArgVal);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool HtmlDoc_IsTokUrl(int HtmlDocId, int TokN)
      {
         return HTextGardenLib.HtmlDoc_IsTokUrl(HtmlDocId, TokN);
      }

      public static String HtmlDoc_GetTokUrlStr(int HtmlDocId, int TokN)
      {
         IntPtr i = HTextGardenLib.HtmlDoc_GetTokUrlStr(HtmlDocId, TokN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool HtmlDoc_IsBreakTag(String TagNm)
      {
         return HTextGardenLib.HtmlDoc_IsBreakTag(TagNm);
      }

      public static String HtmlDoc_GetSymStr(int Sym)
      {
         IntPtr i = HTextGardenLib.HtmlDoc_GetSymStr(Sym);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int WebPg_Fetch(String UrlStr)
      {
         return HTextGardenLib.WebPg_Fetch(UrlStr);
      }

      public static void WebPg_Del(int WebPgId)
      {
          HTextGardenLib.WebPg_Del(WebPgId);
      }

      public static int WebPg_GetUrls(int WebPgId)
      {
         return HTextGardenLib.WebPg_GetUrls(WebPgId);
      }

      public static String WebPg_GetUrl(int WebPgId, int UrlN)
      {
         IntPtr i = HTextGardenLib.WebPg_GetUrl(WebPgId, UrlN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String WebPg_GetUrl(int WebPgId)
      {
         return WebPg_GetUrl(WebPgId,0);
      }

      public static int WebPg_GetHttpResp(int WebPgId)
      {
         return HTextGardenLib.WebPg_GetHttpResp(WebPgId);
      }

      public static int WebPg_GetOutUrlStrV(int WebPgId)
      {
         return HTextGardenLib.WebPg_GetOutUrlStrV(WebPgId);
      }

      public static int Crawler_Gen()
      {
         return HTextGardenLib.Crawler_Gen();
      }

      public static void Crawler_Del(int CrawlerId)
      {
          HTextGardenLib.Crawler_Del(CrawlerId);
      }

      public static void Crawler_AddStartUrlStr(int CrawlerId, String StartUrlStr)
      {
          HTextGardenLib.Crawler_AddStartUrlStr(CrawlerId, StartUrlStr);
      }

      public static void Crawler_PutMxUrls(int CrawlerId, int MxUrls)
      {
          HTextGardenLib.Crawler_PutMxUrls(CrawlerId, MxUrls);
      }

      public static void Crawler_PutMxConns(int CrawlerId, int MxConns)
      {
          HTextGardenLib.Crawler_PutMxConns(CrawlerId, MxConns);
      }

      public static void Crawler_PutMnConns(int CrawlerId, int MnConns)
      {
          HTextGardenLib.Crawler_PutMnConns(CrawlerId, MnConns);
      }

      public static void Crawler_PutMxConnsPerSrv(int CrawlerId, int MxConnsPerSrv)
      {
          HTextGardenLib.Crawler_PutMxConnsPerSrv(CrawlerId, MxConnsPerSrv);
      }

      public static void Crawler_PutAfterFetchDelay(int CrawlerId, int AfterFetchDelaySecs)
      {
          HTextGardenLib.Crawler_PutAfterFetchDelay(CrawlerId, AfterFetchDelaySecs);
      }

      public static void Crawler_PutMxLev(int CrawlerId, int MxLev)
      {
          HTextGardenLib.Crawler_PutMxLev(CrawlerId, MxLev);
      }

      public static void Crawler_PutMxDep(int CrawlerId, int MxDep)
      {
          HTextGardenLib.Crawler_PutMxDep(CrawlerId, MxDep);
      }

      public static void Crawler_PutMnQLen(int CrawlerId, int MnQLen)
      {
          HTextGardenLib.Crawler_PutMnQLen(CrawlerId, MnQLen);
      }

      public static void Crawler_PutQResetMod(int CrawlerId, int QResetMod)
      {
          HTextGardenLib.Crawler_PutQResetMod(CrawlerId, QResetMod);
      }

      public static void Crawler_PutMxContLen(int CrawlerId, int MxContLen)
      {
          HTextGardenLib.Crawler_PutMxContLen(CrawlerId, MxContLen);
      }

      public static void Crawler_PutMxRetries(int CrawlerId, int MxRetries)
      {
          HTextGardenLib.Crawler_PutMxRetries(CrawlerId, MxRetries);
      }

      public static void Crawler_PutMxQSegLen(int CrawlerId, int MxQSegLen)
      {
          HTextGardenLib.Crawler_PutMxQSegLen(CrawlerId, MxQSegLen);
      }

      public static void Crawler_PutRevisitSecs(int CrawlerId, int RevisitSecs)
      {
          HTextGardenLib.Crawler_PutRevisitSecs(CrawlerId, RevisitSecs);
      }

      public static void Crawler_PutRedirDmAllowed(int CrawlerId, bool RedirDmAllowedP)
      {
          HTextGardenLib.Crawler_PutRedirDmAllowed(CrawlerId, RedirDmAllowedP);
      }

      public static void Crawler_AddRqDmNm(int CrawlerId, String RqDmNmV)
      {
          HTextGardenLib.Crawler_AddRqDmNm(CrawlerId, RqDmNmV);
      }

      public static void Crawler_AddRqContTypeNm(int CrawlerId, String ContTypeNm)
      {
          HTextGardenLib.Crawler_AddRqContTypeNm(CrawlerId, ContTypeNm);
      }

      public static void Crawler_AddBadFExt(int CrawlerId, String FExt)
      {
          HTextGardenLib.Crawler_AddBadFExt(CrawlerId, FExt);
      }

      public static void Crawler_OptHtmlCrawling(int CrawlerId)
      {
          HTextGardenLib.Crawler_OptHtmlCrawling(CrawlerId);
      }

      public static void Crawler_DefCrawlBs(int CrawlerId, String CrawlBsNm, String CrawlBsFPath, String CrawlBsFAccessNm, int CrawlBsMxSegLen)
      {
          HTextGardenLib.Crawler_DefCrawlBs(CrawlerId, CrawlBsNm, CrawlBsFPath, CrawlBsFAccessNm, CrawlBsMxSegLen);
      }

      public static void Crawler_StartCrawling(int CrawlerId)
      {
          HTextGardenLib.Crawler_StartCrawling(CrawlerId);
      }

      public static int DMoz_GetCategories(int BowDocBsId, int BowDocWgtBsId, int BowDocPartId, String QueryStr, int MxCats)
      {
         return HTextGardenLib.DMoz_GetCategories(BowDocBsId, BowDocWgtBsId, BowDocPartId, QueryStr, MxCats);
      }

      public static int DMoz_GetKeywords(int BowDocBsId, int BowDocWgtBsId, int BowDocPartId, String QueryStr, int MxCats, double KWordTsh)
      {
         return HTextGardenLib.DMoz_GetKeywords(BowDocBsId, BowDocWgtBsId, BowDocPartId, QueryStr, MxCats, KWordTsh);
      }

      public static int BlobPt_New()
      {
         return HTextGardenLib.BlobPt_New();
      }

      public static void BlobPt_Del(int BlobPtId)
      {
          HTextGardenLib.BlobPt_Del(BlobPtId);
      }

      public static int CrawlBs_Open(String CrawlBsFNm)
      {
         return HTextGardenLib.CrawlBs_Open(CrawlBsFNm);
      }

      public static void CrawlBs_Close(int CrawlBsId)
      {
          HTextGardenLib.CrawlBs_Close(CrawlBsId);
      }

      public static int CrawlBs_FFirstBlobPt(int CrawlBsId)
      {
         return HTextGardenLib.CrawlBs_FFirstBlobPt(CrawlBsId);
      }

      public static bool CrawlBs_FNextBlobPt(int CrawlBsId, int TrvBlobPtId, int BlobPtId)
      {
         return HTextGardenLib.CrawlBs_FNextBlobPt(CrawlBsId, TrvBlobPtId, BlobPtId);
      }

      public static String CrawlBs_GetDateTimeStr(int CrawlBsId, int BlobPtId)
      {
         IntPtr i = HTextGardenLib.CrawlBs_GetDateTimeStr(CrawlBsId, BlobPtId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String CrawlBs_GetUrlStr(int CrawlBsId, int BlobPtId)
      {
         IntPtr i = HTextGardenLib.CrawlBs_GetUrlStr(CrawlBsId, BlobPtId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int CrawlBs_GetHttpResp(int CrawlBsId, int BlobPtId)
      {
         return HTextGardenLib.CrawlBs_GetHttpResp(CrawlBsId, BlobPtId);
      }

      public static int BlobBs_Open(String BlobBsFNm, int BlobBsFAccess)
      {
         return HTextGardenLib.BlobBs_Open(BlobBsFNm, BlobBsFAccess);
      }

      public static void BlobBs_Close(int BlobBsId)
      {
          HTextGardenLib.BlobBs_Close(BlobBsId);
      }

      public static int BlobBs_GetFAccessCreate()
      {
         return HTextGardenLib.BlobBs_GetFAccessCreate();
      }

      public static int BlobBs_GetFAccessUpdate()
      {
         return HTextGardenLib.BlobBs_GetFAccessUpdate();
      }

      public static int BlobBs_GetFAccessReadOnly()
      {
         return HTextGardenLib.BlobBs_GetFAccessReadOnly();
      }

      public static int BlobBs_FFirstBlobPt(int BlobBsId)
      {
         return HTextGardenLib.BlobBs_FFirstBlobPt(BlobBsId);
      }

      public static bool BlobBs_FNextBlobPt(int BlobBsId, int TrvBlobPtId, int BlobPtId)
      {
         return HTextGardenLib.BlobBs_FNextBlobPt(BlobBsId, TrvBlobPtId, BlobPtId);
      }

      public static void BlobBs_AddBlob(int BlobBsId, int MemId, int BlobPtId)
      {
          HTextGardenLib.BlobBs_AddBlob(BlobBsId, MemId, BlobPtId);
      }

      public static void BlobBs_PutBlob(int BlobBsId, int MemId, int BlobPtId)
      {
          HTextGardenLib.BlobBs_PutBlob(BlobBsId, MemId, BlobPtId);
      }

      public static void BlobBs_GetBlob(int BlobBsId, int BlobPtId, int MemId)
      {
          HTextGardenLib.BlobBs_GetBlob(BlobBsId, BlobPtId, MemId);
      }

      public static void BlobBs_DelBlob(int BlobBsId, int BlobPtId)
      {
          HTextGardenLib.BlobBs_DelBlob(BlobBsId, BlobPtId);
      }

      public static int CpDoc_Load(int SInId)
      {
         return HTextGardenLib.CpDoc_Load(SInId);
      }

      public static void CpDoc_Save(int CpDocId, int SOutId)
      {
          HTextGardenLib.CpDoc_Save(CpDocId, SOutId);
      }

      public static int CpDoc_New()
      {
         return HTextGardenLib.CpDoc_New();
      }

      public static void CpDoc_Del(int CpDocId)
      {
          HTextGardenLib.CpDoc_Del(CpDocId);
      }

      public static void CpDoc_FFirstCpd(int SInId)
      {
          HTextGardenLib.CpDoc_FFirstCpd(SInId);
      }

      public static bool CpDoc_FFNextCpd(int SInId, int CpDocId)
      {
         return HTextGardenLib.CpDoc_FFNextCpd(SInId, CpDocId);
      }

      public static void CpDoc_PutDocNm(int CpDocId, String DocNm)
      {
          HTextGardenLib.CpDoc_PutDocNm(CpDocId, DocNm);
      }

      public static String CpDoc_GetDocNm(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetDocNm(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_PutDateStr(int CpDocId, String DateStr)
      {
          HTextGardenLib.CpDoc_PutDateStr(CpDocId, DateStr);
      }

      public static String CpDoc_GetDateStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetDateStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_AddCatNm(int CpDocId, String CatNm)
      {
          HTextGardenLib.CpDoc_AddCatNm(CpDocId, CatNm);
      }

      public static int CpDoc_GetCats(int CpDocId)
      {
         return HTextGardenLib.CpDoc_GetCats(CpDocId);
      }

      public static String CpDoc_GetCatNm(int CpDocId, int CatN)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetCatNm(CpDocId, CatN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String CpDoc_GetTxtStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetTxtStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String CpDoc_GetHtmlStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetHtmlStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_PutTitleStr(int CpDocId, String TitleStr)
      {
          HTextGardenLib.CpDoc_PutTitleStr(CpDocId, TitleStr);
      }

      public static String CpDoc_GetTitleStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetTitleStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_PutHeadlineStr(int CpDocId, String HeadlineStr)
      {
          HTextGardenLib.CpDoc_PutHeadlineStr(CpDocId, HeadlineStr);
      }

      public static String CpDoc_GetHeadlineStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetHeadlineStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_PutBylineStr(int CpDocId, String BylineStr)
      {
          HTextGardenLib.CpDoc_PutBylineStr(CpDocId, BylineStr);
      }

      public static String CpDoc_GetBylineStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetBylineStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_PutDatelineStr(int CpDocId, String DatelineStr)
      {
          HTextGardenLib.CpDoc_PutDatelineStr(CpDocId, DatelineStr);
      }

      public static String CpDoc_GetDatelineStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetDatelineStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_AddParStr(int CpDocId, String ParStr)
      {
          HTextGardenLib.CpDoc_AddParStr(CpDocId, ParStr);
      }

      public static int CpDoc_GetPars(int CpDocId)
      {
         return HTextGardenLib.CpDoc_GetPars(CpDocId);
      }

      public static String CpDoc_GetParStr(int CpDocId, int ParN)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetParStr(CpDocId, ParN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String CpDoc_GetAllParStr(int CpDocId)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetAllParStr(CpDocId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_AddTopCdNm(int CpDocId, String TopCdNm)
      {
          HTextGardenLib.CpDoc_AddTopCdNm(CpDocId, TopCdNm);
      }

      public static int CpDoc_GetTopCds(int CpDocId)
      {
         return HTextGardenLib.CpDoc_GetTopCds(CpDocId);
      }

      public static String CpDoc_GetTopCdNm(int CpDocId, int TopCdN)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetTopCdNm(CpDocId, TopCdN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_AddGeoCdNm(int CpDocId, String GeoCdNm)
      {
          HTextGardenLib.CpDoc_AddGeoCdNm(CpDocId, GeoCdNm);
      }

      public static int CpDoc_GetGeoCds(int CpDocId)
      {
         return HTextGardenLib.CpDoc_GetGeoCds(CpDocId);
      }

      public static String CpDoc_GetGeoCdNm(int CpDocId, int GeoCdN)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetGeoCdNm(CpDocId, GeoCdN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static void CpDoc_AddIndCdNm(int CpDocId, String IndCdNm)
      {
          HTextGardenLib.CpDoc_AddIndCdNm(CpDocId, IndCdNm);
      }

      public static int CpDoc_GetIndCds(int CpDocId)
      {
         return HTextGardenLib.CpDoc_GetIndCds(CpDocId);
      }

      public static String CpDoc_GetIndCdNm(int CpDocId, int IndCdN)
      {
         IntPtr i = HTextGardenLib.CpDoc_GetIndCdNm(CpDocId, IndCdN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int OdbcDb_New()
      {
         return HTextGardenLib.OdbcDb_New();
      }

      public static void OdbcDb_Del(int OdbcDbId)
      {
          HTextGardenLib.OdbcDb_Del(OdbcDbId);
      }

      public static int OdbcDb_GetDataSourceNmV(int OdbcDbId)
      {
         return HTextGardenLib.OdbcDb_GetDataSourceNmV(OdbcDbId);
      }

      public static int OdbcDb_GetTbNmV(int OdbcDbId)
      {
         return HTextGardenLib.OdbcDb_GetTbNmV(OdbcDbId);
      }

      public static int OdbcDb_GetColNmV(int OdbcDbId, String TbNm)
      {
         return HTextGardenLib.OdbcDb_GetColNmV(OdbcDbId, TbNm);
      }

      public static bool OdbcDb_Connect(int OdbcDbId, String SrvNm, String UsrNm, String PwdStr)
      {
         return HTextGardenLib.OdbcDb_Connect(OdbcDbId, SrvNm, UsrNm, PwdStr);
      }

      public static void OdbcDb_Disconnect(int OdbcDbId)
      {
          HTextGardenLib.OdbcDb_Disconnect(OdbcDbId);
      }

      public static bool OdbcDb_IsConnected(int OdbcDbId)
      {
         return HTextGardenLib.OdbcDb_IsConnected(OdbcDbId);
      }

      public static bool OdbcDb_IsOk(int OdbcDbId)
      {
         return HTextGardenLib.OdbcDb_IsOk(OdbcDbId);
      }

      public static String OdbcDb_GetMsgStr(int OdbcDbId)
      {
         IntPtr i = HTextGardenLib.OdbcDb_GetMsgStr(OdbcDbId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static int OdbcQuery_New(int OdbcDbId)
      {
         return HTextGardenLib.OdbcQuery_New(OdbcDbId);
      }

      public static void OdbcQuery_Del(int OdbcQueryId)
      {
          HTextGardenLib.OdbcQuery_Del(OdbcQueryId);
      }

      public static bool OdbcQuery_ExeSql(int OdbcQueryId, String SqlStr, int ParamStrVId)
      {
         return HTextGardenLib.OdbcQuery_ExeSql(OdbcQueryId, SqlStr, ParamStrVId);
      }

      public static bool OdbcQuery_ExeSql(int OdbcQueryId, String SqlStr)
      {
         return OdbcQuery_ExeSql(OdbcQueryId, SqlStr,-1);
      }

      public static bool OdbcQuery_ExeSqlP1(int OdbcQueryId, String SqlStr, String ParamStr)
      {
         return HTextGardenLib.OdbcQuery_ExeSqlP1(OdbcQueryId, SqlStr, ParamStr);
      }

      public static bool OdbcQuery_ExeSqlP2(int OdbcQueryId, String SqlStr, String ParamStr1, String ParamStr2)
      {
         return HTextGardenLib.OdbcQuery_ExeSqlP2(OdbcQueryId, SqlStr, ParamStr1, ParamStr2);
      }

      public static bool OdbcQuery_ExeSqlP3(int OdbcQueryId, String SqlStr, String ParamStr1, String ParamStr2, String ParamStr3)
      {
         return HTextGardenLib.OdbcQuery_ExeSqlP3(OdbcQueryId, SqlStr, ParamStr1, ParamStr2, ParamStr3);
      }

      public static bool OdbcQuery_IsResultSet(int OdbcQueryId)
      {
         return HTextGardenLib.OdbcQuery_IsResultSet(OdbcQueryId);
      }

      public static int OdbcQuery_GetCols(int OdbcQueryId)
      {
         return HTextGardenLib.OdbcQuery_GetCols(OdbcQueryId);
      }

      public static int OdbcQuery_GetRowsAffected(int OdbcQueryId)
      {
         return HTextGardenLib.OdbcQuery_GetRowsAffected(OdbcQueryId);
      }

      public static String OdbcQuery_GetColNm(int OdbcQueryId, int ColN)
      {
         IntPtr i = HTextGardenLib.OdbcQuery_GetColNm(OdbcQueryId, ColN);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static bool OdbcQuery_NextRow(int OdbcQueryId)
      {
         return HTextGardenLib.OdbcQuery_NextRow(OdbcQueryId);
      }

      public static String OdbcQuery_GetColVal(int OdbcQueryId, int ColN, int MxValStrLen)
      {
         IntPtr i = HTextGardenLib.OdbcQuery_GetColVal(OdbcQueryId, ColN, MxValStrLen);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

      public static String OdbcQuery_GetColVal(int OdbcQueryId, int ColN)
      {
         return OdbcQuery_GetColVal(OdbcQueryId, ColN,10000);
      }

      public static bool OdbcQuery_IsOk(int OdbcQueryId)
      {
         return HTextGardenLib.OdbcQuery_IsOk(OdbcQueryId);
      }

      public static bool OdbcQuery_IsOpOk(int OdbcQueryId)
      {
         return HTextGardenLib.OdbcQuery_IsOpOk(OdbcQueryId);
      }

      public static String OdbcQuery_GetMsgStr(int OdbcQueryId)
      {
         IntPtr i = HTextGardenLib.OdbcQuery_GetMsgStr(OdbcQueryId);
         string s = Marshal.PtrToStringAnsi(i);
         HTextGardenLib.DelCStr(i);
         return s;
      }

   }
}
