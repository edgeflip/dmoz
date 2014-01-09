#include "TextGardenLib.h"

#include "mine.h"
#include "google.h"
#include "nmobj.h"
#include "crawler.h"
#include "vizmap.h"
#include "odbc.h"

/////////////////////////////////////////////////
// TTextGardenState
typedef void (*TNotifyCallbackF)();

class TTextGardenState{
private:
  THash<TUInt64, char*> AddrToCStrH;
  TInt LastId;
  TInt LastMemId;
  THash<TInt, PMem> IdToMemH;
  TInt LastIntVId;
  THash<TInt, TIntV> IdToIntVH;
  TInt LastStrVId;
  THash<TInt, TStrV> IdToStrVH;
  TInt LastFltStrPrVId;
  THash<TInt, TFltStrPrV> IdToFltStrPrVH;
  TInt LastSInId;
  THash<TInt, PSIn> IdToSInH;
  TInt LastSOutId;
  THash<TInt, PSOut> IdToSOutH;
  TInt LastCpDocId;
  THash<TInt, PCpDoc> IdToCpDocH;
  TInt LastBowDocBsId;
  THash<TInt, PBowDocBs> IdToBowDocBsH;
  TInt LastBowDocWgtBsId;
  THash<TInt, PBowDocWgtBs> IdToBowDocWgtBsH;
  TInt LastBowDocPartId;
  THash<TInt, PBowDocPart> IdToBowDocPartH;
  TInt LastSemSpaceId;
  THash<TInt, PSemSpace> IdToSemSpaceH;
  TInt LastVizMapId;
  THash<TInt, PVizMap> IdToVizMapH;
  TInt LastBowMdId;
  THash<TInt, PBowMd> IdToBowMdH;
  TInt LastBowALId;
  THash<TInt, PBowAL> IdToBowALH;
  TInt LastRSetId;
  THash<TInt, PRSet> IdToRSetH;
  TInt LastNmObjBsId;
  THash<TInt, PNmObjBs> IdToNmObjBsH;
  TInt LastUrlId;
  THash<TInt, PUrl> IdToUrlH;
  TInt LastHttpRespId;
  THash<TInt, PHttpResp> IdToHttpRespH;
  TInt LastHtmlDocId;
  THash<TInt, PHtmlDoc> IdToHtmlDocH;
  TInt LastWebPgId;
  THash<TInt, PWebPg> IdToWebPgH;
  TInt LastCrawlerId;
  THash<TInt, PCrawler> IdToCrawlerH;
  TInt LastDMozBsId;
  THash<TInt, PDMozBs> IdToDMozBsH;
  TInt LastCrawlBsId;
  THash<TInt, PCrawlBs> IdToCrawlBsH;
  TInt LastBlobBsId;
  THash<TInt, PBlobBs> IdToBlobBsH;
  TInt LastBlobPtId;
  THash<TInt, TBlobPt> IdToBlobPtH;
  TInt LastOdbcDbId;
  THash<TInt, POdbcDb> IdToOdbcDbH;
  TInt LastOdbcQueryId;
  THash<TInt, POdbcQuery> IdToOdbcQueryH;
  TInt LastOdbcTbId;
  THash<TInt, POdbcTb> IdToOdbcTbH;
  TInt VerbosityLev;
  TNotifyCallbackF NotifyCallbackF;
  TChA NotifyMsgChA;
  UndefCopyAssign(TTextGardenState);
public:
  TTextGardenState():
    NotifyCallbackF(NULL){
    printf("*** Open TTextGardenState\n");}
  ~TTextGardenState(){
    printf("*** Close TTextGardenState\n");}

  // strings
  char* AddCStr(char* CStr){
    AddrToCStrH.AddDat(TUInt64(CStr), CStr); return CStr;}
  void DelCStr(char* CStr){
    AddrToCStrH.DelKey(TUInt64(CStr));}
  int GetCStrs(){
    return AddrToCStrH.Len();}
  void GetCStrV(TStrV& StrV){
    StrV.Gen(GetCStrs(), 0);
    int CStrId=AddrToCStrH.FFirstKeyId();
    while (AddrToCStrH.FNextKeyId(CStrId)){
      StrV.Add(AddrToCStrH[CStrId]);
    }
  }

  // Mem
  int AddMem(const PMem& Mem){
    LastMemId=LastId++;
    IdToMemH.AddDat(LastMemId, Mem);
    return LastMemId;}
  PMem GetMem(const int& MemId){
    return IdToMemH.GetDat(MemId);}
  void DelMem(const int& MemId){
    IdToMemH.DelKey(MemId);}

  // IntV
  int AddIntV(const TIntV& IntV){
    LastIntVId=LastId++;
    IdToIntVH.AddDat(LastIntVId, IntV);
    return LastIntVId;}
  TIntV& GetIntV(const int& IntVId){
    return IdToIntVH.GetDat(IntVId);}
  void DelIntV(const int& IntVId){
    IdToIntVH.DelKey(IntVId);}

  // StrV
  int AddStrV(const TStrV& StrV){
    LastStrVId=LastId++;
    IdToStrVH.AddDat(LastStrVId, StrV);
    return LastStrVId;}
  TStrV& GetStrV(const int& StrVId){
    return IdToStrVH.GetDat(StrVId);}
  void DelStrV(const int& StrVId){
    IdToStrVH.DelKey(StrVId);}

  // FltStrPrV
  int AddFltStrPrV(const TFltStrPrV& FltStrPrV){
    LastFltStrPrVId=LastId++;
    IdToFltStrPrVH.AddDat(LastFltStrPrVId, FltStrPrV);
    return LastFltStrPrVId;}
  TFltStrPrV& GetFltStrPrV(const int& FltStrPrVId){
    return IdToFltStrPrVH.GetDat(FltStrPrVId);}
  void DelFltStrPrV(const int& FltStrPrVId){
    IdToFltStrPrVH.DelKey(FltStrPrVId);}

  // SIn
  int AddSIn(const PSIn& SIn){
    LastSInId=LastId++;
    IdToSInH.AddDat(LastSInId, SIn);
    return LastSInId;}
  PSIn GetSIn(const int& SInId){
    return IdToSInH.GetDat(SInId);}
  void DelSIn(const int& SInId){
    IdToSInH.DelKey(SInId);}

  // SOut
  int AddSOut(const PSOut& SOut){
    LastSOutId=LastId++;
    IdToSOutH.AddDat(LastSOutId, SOut);
    return LastSOutId;}
  PSOut GetSOut(const int& SOutId){
    return IdToSOutH.GetDat(SOutId);}
  void DelSOut(const int& SOutId){
    IdToSOutH.DelKey(SOutId);}

  // CpDoc
  int AddCpDoc(const PCpDoc& CpDoc){
    LastCpDocId=LastId++;
    IdToCpDocH.AddDat(LastCpDocId, CpDoc);
    return LastCpDocId;}
  PCpDoc& GetCpDoc(const int& CpDocId){
    return IdToCpDocH.GetDat(CpDocId);}
  void DelCpDoc(const int& CpDocId){
    IdToCpDocH.DelKey(CpDocId);}

  // BowDocBs
  int AddBowDocBs(const PBowDocBs& BowDocBs){
    LastBowDocBsId=LastId++;
    IdToBowDocBsH.AddDat(LastBowDocBsId, BowDocBs);
    return LastBowDocBsId;}
  PBowDocBs GetBowDocBs(const int& BowDocBsId){
    return IdToBowDocBsH.GetDat(BowDocBsId);}
  void DelBowDocBs(const int& BowDocBsId){
    IdToBowDocBsH.DelKey(BowDocBsId);}

  // BowDocWgtBs
  int AddBowDocWgtBs(const PBowDocWgtBs& BowDocWgtBs){
    LastBowDocWgtBsId=LastId++;
    IdToBowDocWgtBsH.AddDat(LastBowDocWgtBsId, BowDocWgtBs);
    return LastBowDocWgtBsId;}
  PBowDocWgtBs GetBowDocWgtBs(const int& BowDocWgtBsId){
    return IdToBowDocWgtBsH.GetDat(BowDocWgtBsId);}
  void DelBowDocWgtBs(const int& BowDocWgtBsId){
    IdToBowDocWgtBsH.DelKey(BowDocWgtBsId);}

  // BowDocPart
  int AddBowDocPart(const PBowDocPart& BowDocPart){
    LastBowDocPartId=LastId++;
    IdToBowDocPartH.AddDat(LastBowDocPartId, BowDocPart);
    return LastBowDocPartId;}
  PBowDocPart GetBowDocPart(const int& BowDocPartId){
    return IdToBowDocPartH.GetDat(BowDocPartId);}
  void DelBowDocPart(const int& BowDocPartId){
    IdToBowDocPartH.DelKey(BowDocPartId);}

  // SemSpace
  int AddSemSpace(const PSemSpace& SemSpace){
    LastSemSpaceId=LastId++;
    IdToSemSpaceH.AddDat(LastSemSpaceId, SemSpace);
    return LastSemSpaceId;}
  PSemSpace GetSemSpace(const int& SemSpaceId){
    return IdToSemSpaceH.GetDat(SemSpaceId);}
  void DelSemSpace(const int& SemSpaceId){
    IdToSemSpaceH.DelKey(SemSpaceId);}

  // VizMap
  int AddVizMap(const PVizMap& VizMap){
    LastVizMapId=LastId++;
    IdToVizMapH.AddDat(LastVizMapId, VizMap);
    return LastVizMapId;}
  PVizMap GetVizMap(const int& VizMapId){
    return IdToVizMapH.GetDat(VizMapId);}
  void DelVizMap(const int& VizMapId){
    IdToVizMapH.DelKey(VizMapId);}

  // BowMd
  int AddBowMd(const PBowMd& BowMd){
    LastBowMdId=LastId++;
    IdToBowMdH.AddDat(LastBowMdId, BowMd);
    return LastBowMdId;}
  PBowMd GetBowMd(const int& BowMdId){
    return IdToBowMdH.GetDat(BowMdId);}
  void DelBowMd(const int& BowMdId){
    IdToBowMdH.DelKey(BowMdId);}

  // BowAL
  int AddBowAL(const PBowAL& BowAL){
    LastBowALId=LastId++;
    IdToBowALH.AddDat(LastBowALId, BowAL);
    return LastBowALId;}
  PBowAL GetBowAL(const int& BowALId){
    return IdToBowALH.GetDat(BowALId);}
  void DelBowAL(const int& BowALId){
    IdToBowALH.DelKey(BowALId);}

  // RSet
  int AddRSet(const PRSet& RSet){
    LastRSetId=LastId++;
    IdToRSetH.AddDat(LastRSetId, RSet);
    return LastRSetId;}
  PRSet GetRSet(const int& RSetId){
    return IdToRSetH.GetDat(RSetId);}
  void DelRSet(const int& RSetId){
    IdToRSetH.DelKey(RSetId);}

  // NmObjBs
  int AddNmObjBs(const PNmObjBs& NmObjBs){
    LastNmObjBsId=LastId++;
    IdToNmObjBsH.AddDat(LastNmObjBsId, NmObjBs);
    return LastNmObjBsId;}
  PNmObjBs GetNmObjBs(const int& NmObjBsId){
    return IdToNmObjBsH.GetDat(NmObjBsId);}
  void DelNmObjBs(const int& NmObjBsId){
    IdToNmObjBsH.DelKey(NmObjBsId);}

  // Url
  int AddUrl(const PUrl& Url){
    LastUrlId=LastId++;
    IdToUrlH.AddDat(LastUrlId, Url);
    return LastUrlId;}
  PUrl GetUrl(const int& UrlId){
    return IdToUrlH.GetDat(UrlId);}
  void DelUrl(const int& UrlId){
    IdToUrlH.DelKey(UrlId);}

  // HttpResp
  int AddHttpResp(const PHttpResp& HttpResp){
    LastHttpRespId=LastId++;
    IdToHttpRespH.AddDat(LastHttpRespId, HttpResp);
    return LastHttpRespId;}
  PHttpResp GetHttpResp(const int& HttpRespId){
    return IdToHttpRespH.GetDat(HttpRespId);}
  void DelHttpResp(const int& HttpRespId){
    IdToHttpRespH.DelKey(HttpRespId);}

  // HtmlDoc
  int AddHtmlDoc(const PHtmlDoc& HtmlDoc){
    LastHtmlDocId=LastId++;
    IdToHtmlDocH.AddDat(LastHtmlDocId, HtmlDoc);
    return LastHtmlDocId;}
  PHtmlDoc GetHtmlDoc(const int& HtmlDocId){
    return IdToHtmlDocH.GetDat(HtmlDocId);}
  void DelHtmlDoc(const int& HtmlDocId){
    IdToHtmlDocH.DelKey(HtmlDocId);}

  // WebPg
  int AddWebPg(const PWebPg& WebPg){
    LastWebPgId=LastId++;
    IdToWebPgH.AddDat(LastWebPgId, WebPg);
    return LastWebPgId;}
  PWebPg GetWebPg(const int& WebPgId){
    return IdToWebPgH.GetDat(WebPgId);}
  void DelWebPg(const int& WebPgId){
    IdToWebPgH.DelKey(WebPgId);}

  // Crawler
  int AddCrawler(const PCrawler& Crawler){
    LastCrawlerId=LastId++;
    IdToCrawlerH.AddDat(LastCrawlerId, Crawler);
    return LastCrawlerId;}
  PCrawler GetCrawler(const int& CrawlerId){
    return IdToCrawlerH.GetDat(CrawlerId);}
  void DelCrawler(const int& CrawlerId){
    IdToCrawlerH.DelKey(CrawlerId);}

  // DMoz
  int AddDMozBs(const PDMozBs& DMozBs){
    LastDMozBsId=LastId++;
    IdToDMozBsH.AddDat(LastDMozBsId, DMozBs);
    return LastDMozBsId;}
  PDMozBs GetDMozBs(const int& DMozBsId){
    return IdToDMozBsH.GetDat(DMozBsId);}
  void DelDMozBs(const int& DMozBsId){
    IdToDMozBsH.DelKey(DMozBsId);}

  // Blob-Base
  int AddBlobBs(const PBlobBs& BlobBs){
    LastBlobBsId=LastId++;
    IdToBlobBsH.AddDat(LastBlobBsId, BlobBs);
    return LastBlobBsId;}
  PBlobBs GetBlobBs(const int& BlobBsId){
    return IdToBlobBsH.GetDat(BlobBsId);}
  void DelBlobBs(const int& BlobBsId){
    IdToBlobBsH.DelKey(BlobBsId);}

  // Blob-Pointer
  int AddBlobPt(const TBlobPt& BlobPt){
    LastBlobPtId=LastId++;
    IdToBlobPtH.AddDat(LastBlobPtId, BlobPt);
    return LastBlobPtId;}
  void PutBlobPt(const int& BlobPtId, const TBlobPt& BlobPt){
    IdToBlobPtH.GetDat(BlobPtId)=BlobPt;}
  TBlobPt& GetBlobPt(const int& BlobPtId){
    return IdToBlobPtH.GetDat(BlobPtId);}
  void DelBlobPt(const int& BlobPtId){
    IdToBlobPtH.DelKey(BlobPtId);}

  // OdbcDb
  int AddOdbcDb(const POdbcDb& OdbcDb){
    LastOdbcDbId=LastId++;
    IdToOdbcDbH.AddDat(LastOdbcDbId, OdbcDb);
    return LastOdbcDbId;}
  POdbcDb GetOdbcDb(const int& OdbcDbId){
    return IdToOdbcDbH.GetDat(OdbcDbId);}
  void DelOdbcDb(const int& OdbcDbId){
    IdToOdbcDbH.DelKey(OdbcDbId);}

  // OdbcQuery
  int AddOdbcQuery(const POdbcQuery& OdbcQuery){
    LastOdbcQueryId=LastId++;
    IdToOdbcQueryH.AddDat(LastOdbcQueryId, OdbcQuery);
    return LastOdbcQueryId;}
  POdbcQuery GetOdbcQuery(const int& OdbcQueryId){
    return IdToOdbcQueryH.GetDat(OdbcQueryId);}
  void DelOdbcQuery(const int& OdbcQueryId){
    IdToOdbcQueryH.DelKey(OdbcQueryId);}

  // OdbcTb
  int AddOdbcTb(const POdbcTb& OdbcTb){
    LastOdbcTbId=LastId++;
    IdToOdbcTbH.AddDat(LastOdbcTbId, OdbcTb);
    return LastOdbcTbId;}
  POdbcTb GetOdbcTb(const int& OdbcTbId){
    return IdToOdbcTbH.GetDat(OdbcTbId);}
  void DelOdbcTb(const int& OdbcTbId){
    IdToOdbcTbH.DelKey(OdbcTbId);}

  // verbosity
  void SetVerbosity(int _VerbosityLev){VerbosityLev=_VerbosityLev;}
  int GetVerbosity(){return VerbosityLev;}

  // notifier
  void SetNotifyCallbackF(TNotifyCallbackF _NotifyCallbackF){
    NotifyCallbackF=_NotifyCallbackF;}
  void* GetNotifyCallbackF(){
    return NotifyCallbackF;}
  void PutNotifyMsg(char* MsgStr){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=MsgStr;
      (*NotifyCallbackF)();
    }}
  void PutNotifyMsg(char* HdStr, char* MsgStr){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=HdStr; NotifyMsgChA+=": "; NotifyMsgChA+=MsgStr;
      if (strcmp(HdStr, "FExit")!=0){(*NotifyCallbackF)();}
    }}
  void PutNotifyMsg(char* HdStr, char* MsgStr, char* ArgStr){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=HdStr; NotifyMsgChA+=": "; NotifyMsgChA+=MsgStr;
      NotifyMsgChA+=" ("; NotifyMsgChA+=ArgStr; NotifyMsgChA+=")";
      if (strcmp(HdStr, "FExit")!=0){(*NotifyCallbackF)();}
    }}
  void PutNotifyMsg(char* HdStr, char* MsgStr, int ArgNum){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=HdStr; NotifyMsgChA+=": "; NotifyMsgChA+=MsgStr;
      NotifyMsgChA+=" ("; NotifyMsgChA+=TInt::GetStr(ArgNum); NotifyMsgChA+=")";
      if (strcmp(HdStr, "FExit")!=0){(*NotifyCallbackF)();}
    }}
  void PutNotifyMsg(char* HdStr, char* MsgStr, char* ArgStr1, char* ArgStr2){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=HdStr; NotifyMsgChA+=": "; NotifyMsgChA+=MsgStr;
      NotifyMsgChA+=" ("; NotifyMsgChA+=ArgStr1; NotifyMsgChA+=", ";
      NotifyMsgChA+=ArgStr2; NotifyMsgChA+=")";
      if (strcmp(HdStr, "FExit")!=0){(*NotifyCallbackF)();}
    }}
  void PutNotifyMsg(char* HdStr, char* MsgStr, int ArgNum1, char* ArgStr2){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=HdStr; NotifyMsgChA+=": "; NotifyMsgChA+=MsgStr;
      NotifyMsgChA+=" ("; NotifyMsgChA+=TInt::GetStr(ArgNum1); NotifyMsgChA+=", ";
      NotifyMsgChA+=ArgStr2; NotifyMsgChA+=")";
      if (strcmp(HdStr, "FExit")!=0){(*NotifyCallbackF)();}
    }}
  void PutNotifyMsg(char* HdStr, char* MsgStr, int ArgNum1, int ArgNum2){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA=HdStr; NotifyMsgChA+=": "; NotifyMsgChA+=MsgStr;
      NotifyMsgChA+=" ("; NotifyMsgChA+=TInt::GetStr(ArgNum1); NotifyMsgChA+=", ";
      NotifyMsgChA+=TInt::GetStr(ArgNum2); NotifyMsgChA+=")";
      if (strcmp(HdStr, "FExit")!=0){(*NotifyCallbackF)();}
    }}
  void PutNotifyMsgRes(char* ResStr){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA+=" -> "; NotifyMsgChA+=ResStr;
      (*NotifyCallbackF)();}}
  void PutNotifyMsgRes(int ResNum){
    if (NotifyCallbackF!=NULL){
      NotifyMsgChA+=" -> "; NotifyMsgChA+=TInt::GetStr(ResNum);
      (*NotifyCallbackF)();}}

  TChA& GetNotifyMsgStr(){
    return NotifyMsgChA;}
};

static TTextGardenState* State;

/////////////////////////////////////////////////
// Dll
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved){
  switch (fwdreason){
    case DLL_PROCESS_ATTACH:
      printf("*** TextGardenLib DLL-Process-Attach\n");
      State=new TTextGardenState(); break;
    case DLL_THREAD_ATTACH:
      printf("*** TextGardenLib DLL-Thread-Attach\n"); break;
    case DLL_THREAD_DETACH:
      printf("*** TextGardenLib DLL-Thread-Detach\n"); break;
    case DLL_PROCESS_DETACH:
      printf("*** TextGardenLib DLL-Process-Detach\n");
      delete State; break;
    default: printf("*** TextGardenLib DLL-Unknown-Entry\n"); break;
  }
  return true;
}

char* CopyStrToCStr(const TStr& Str){
  int StrLen=Str.Len();
  char* CStr=new char[StrLen+1];
  strcpy(CStr, Str.CStr());
  return State->AddCStr(CStr);
}

char* CopyStrToCStr(const TChA& ChA){
  char* CStr=new char[ChA.Len()+1];
  strcpy(CStr, ChA.CStr());
  return State->AddCStr(CStr);
}

char* CopyCStrToCStr(const char* SrcCStr){
  int CStrLen=int(strlen(SrcCStr));
  char* DstCStr=new char[CStrLen+1];
  strcpy(DstCStr, SrcCStr);
  return State->AddCStr(DstCStr);
}

/////////////////////////////////////////////////
// Global
void DelCStr(char* CStr){
  if (CStr!=NULL){
    State->DelCStr(CStr);
    delete[] CStr;
  }
}

void SetVerbosity(int VerbosityLev){
  State->SetVerbosity(VerbosityLev);
}

int GetVerbosity(){
  return State->GetVerbosity();
}

/////////////////////////////////////////////////
// Notifier
void Notify_PutCallback(void* CallbackF){
  State->SetNotifyCallbackF((TNotifyCallbackF)CallbackF);
}

bool Notify_IsCallback(){
  return State->GetNotifyCallbackF()!=NULL;
}

void* Notify_GetCallback(){
  return State->GetNotifyCallbackF();
}

void Notify_DelCallback(){
  State->SetNotifyCallbackF(NULL);
}

char* Notify_GetMsg(){
  return CopyStrToCStr(State->GetNotifyMsgStr());
}

/////////////////////////////////////////////////
// Strings
int CStr_GetStrs(){
  return State->GetCStrs();
}

int CStr_GetStrV(){
  TStrV StrV; State->GetCStrV(StrV);
  return State->AddStrV(StrV);
}


/////////////////////////////////////////////////
// Memory
int Mem_Gen(){
  return State->AddMem(TMem::New());
}

int Mem_GenFromStr(char* Str){
  return State->AddMem(TMem::New(TStr(Str)));
}

int Mem_GenFromMemory(void* MemoryPt, int MemoryLen){
  return State->AddMem(TMem::New(MemoryPt, MemoryLen));
}

void Mem_Del(int MemId){
  State->DelMem(MemId);
}

void Mem_Clr(int MemId){
  State->GetMem(MemId).Clr();
}

int Mem_GetLen(int MemId){
  return State->GetMem(MemId)->Len();
}

void Mem_AddVal(int MemId, char Val){
  return State->GetMem(MemId)->Push(Val);
}

char Mem_GetVal(int MemId, int ValN){
  return State->GetMem(MemId)->operator[](ValN);
}

char* Mem_GetMemoryPt(int MemId){
  return State->GetMem(MemId)->GetBf();
}

char* Mem_GetAsStr(int MemId){
  return CopyStrToCStr(State->GetMem(MemId)->GetAsStr());
}

int Mem_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  PMem Mem; TMem::LoadMem(SIn, Mem);
  return State->AddMem(Mem);
}

void Mem_Save(int MemId, int SOutId){
  PMem Mem=State->GetMem(MemId);
  PSOut SOut=State->GetSOut(SOutId);
  Mem.Save(*SOut);
}

/////////////////////////////////////////////////
// Integer-Vector
int IntV_Gen(){return State->AddIntV(TIntV());}
void IntV_Del(int IntVId){State->DelIntV(IntVId);}
int IntV_GetLen(int IntVId){return State->GetIntV(IntVId).Len();}
int IntV_AddVal(int IntVId, int Val){return State->GetIntV(IntVId).Add(Val);}
int IntV_GetVal(int IntVId, int ValN){return State->GetIntV(IntVId)[ValN];}
void IntV_Sort(int IntVId, bool Asc){
  State->GetFltStrPrV(IntVId).Sort(Asc);}

int IntV_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  TIntV IntV; IntV.Load(*SIn);
  return State->AddIntV(IntV);
}

void IntV_Save(int IntVId, int SOutId){
  TIntV& IntV=State->GetIntV(IntVId);
  PSOut SOut=State->GetSOut(SOutId);
  IntV.Save(*SOut);
}

/////////////////////////////////////////////////
// String-Vector
int StrV_Gen(){return State->AddStrV(TStrV());}
void StrV_Del(int StrVId){State->DelStrV(StrVId);}
int StrV_GetLen(int StrVId){return State->GetStrV(StrVId).Len();}
int StrV_AddVal(int StrVId, char* Val){return State->GetStrV(StrVId).Add(Val);}
char* StrV_GetVal(int StrVId, int ValN){
  return CopyStrToCStr(State->GetStrV(StrVId)[ValN]);}
void StrV_Sort(int StrVId, bool Asc){
  State->GetFltStrPrV(StrVId).Sort(Asc);}

int StrV_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  TStrV StrV; StrV.Load(*SIn);
  return State->AddStrV(StrV);
}

void StrV_Save(int StrVId, int SOutId){
  TStrV& StrV=State->GetStrV(StrVId);
  PSOut SOut=State->GetSOut(SOutId);
  StrV.Save(*SOut);
}

/////////////////////////////////////////////////
// Float-String-Pair-Vector
int FSPrV_Gen(){return State->AddFltStrPrV(TFltStrPrV());}
void FSPrV_Del(int FSPrVId){State->DelFltStrPrV(FSPrVId);}
int FSPrV_GetLen(int FSPrVId){return State->GetFltStrPrV(FSPrVId).Len();}
int FSPrV_AddVal(int FSPrVId, double Flt, char* Str){
  return State->GetFltStrPrV(FSPrVId).Add(TFltStrPr(Flt, Str));}
double FSPrV_GetFltVal(int FSPrVId, int ValN){
  return State->GetFltStrPrV(FSPrVId)[ValN].Val1;}
void FSPrV_Sort(int FSPrVId, bool Asc){
  State->GetFltStrPrV(FSPrVId).Sort(Asc);}
char* FSPrV_GetStrVal(int FSPrVId, int ValN){
  return CopyStrToCStr(State->GetFltStrPrV(FSPrVId)[ValN].Val2);}

int FSPrV_GetTopVal(int FSPrVId, double WgtPrc, int MxVals, bool UseNegWgt){
  // get vector
  TFltStrPrV& SrcFSPrV=State->GetFltStrPrV(FSPrVId);
  int SrcFSPrs=SrcFSPrV.Len();
  // collect data
  TFltFltStrTrV AFFSTrV(SrcFSPrs, 0);
  double SumAbsWgt=0;
  for (int SrcFSPrN=0; SrcFSPrN<SrcFSPrs; SrcFSPrN++){
    double Wgt=SrcFSPrV[SrcFSPrN].Val1;
    if ((Wgt>=0)||UseNegWgt){
      TStr Str=SrcFSPrV[SrcFSPrN].Val2;
      SumAbsWgt+=fabs(Wgt);
      AFFSTrV.Add(TFltFltStrTr(fabs(Wgt), Wgt, Str));
    }
  }
  AFFSTrV.Sort(false);
  // determine split
  int AFFSTrs=AFFSTrV.Len();
  double SumAbsWgtSF=0;
  int DstFSPrVId=FSPrV_Gen();
  TFltStrPrV& DstFSPrV=State->GetFltStrPrV(DstFSPrVId);
  for (int AFFSTrN=0; AFFSTrN<AFFSTrs; AFFSTrN++){
    double AbsWgt=AFFSTrV[AFFSTrN].Val1;
    double Wgt=AFFSTrV[AFFSTrN].Val2;
    TStr Str=AFFSTrV[AFFSTrN].Val3;
    SumAbsWgtSF+=AbsWgt;
    if ((WgtPrc!=-1)&&(WgtPrc<=0)){break;}
    if ((MxVals!=-1)&&(MxVals<=DstFSPrV.Len())){break;}
    DstFSPrV.Add(TFltStrPr(Wgt, Str));
    if ((WgtPrc!=-1)&&(SumAbsWgt>0)&&(SumAbsWgtSF/SumAbsWgt>WgtPrc)){break;}
  }
  DstFSPrV.Sort(false);
  // return extracted vector-id
  return DstFSPrVId;
}

int FSPrV_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  TFltStrPrV FSPrV; FSPrV.Load(*SIn);
  return State->AddFltStrPrV(FSPrV);
}

void FSPrV_Save(int FSPrVId, int SOutId){
  TFltStrPrV& FSPrV=State->GetFltStrPrV(FSPrVId);
  PSOut SOut=State->GetSOut(SOutId);
  FSPrV.Save(*SOut);
}

/////////////////////////////////////////////////
// Input-Stream
int SIn_GenStdIn(){
  PSIn SIn=TStdIn::New();
  return State->AddSIn(SIn);
}

int SIn_GenFileIn(char* FNm){
  PSIn SIn=TFIn::New(FNm);
  return State->AddSIn(SIn);
}

int SIn_GenMemIn(int MemId){
  PMem Mem=State->GetMem(MemId);
  PSIn SIn=TMemIn::New(Mem);
  return State->AddSIn(SIn);
}

int SIn_GenStrIn(char* Str){
  PSIn SIn=TStrIn::New(Str);
  return State->AddSIn(SIn);
}

void SIn_Del(int SInId){
  State->DelSIn(SInId);
}

/////////////////////////////////////////////////
// Output-Stream
int SOut_GenStdOut(){
  PSOut SOut=TStdOut::New();
  return State->AddSOut(SOut);
}

int SOut_GenFileOut(char* FNm, bool Append){
  PSOut SOut=TFOut::New(FNm, Append);
  return State->AddSOut(SOut);
}

int SOut_GenMemOut(int MemId){
  PMem Mem=State->GetMem(MemId);
  PSOut SOut=TMemOut::New(Mem);
  return State->AddSOut(SOut);
}

void SOut_Del(int SOutId){
  State->DelSOut(SOutId);
}

/////////////////////////////////////////////////
// conversions to Compact-Doc
bool Conv_HtmlToCpd(char* InFPath, char* OutCpdFNm, bool RecurseDirP, int MxDocs){
  State->PutNotifyMsg("Call", "Conv_HtmlToCpd", InFPath, OutCpdFNm);
  TCpDoc::SaveHtmlToCpd(InFPath, OutCpdFNm, RecurseDirP, MxDocs);
  State->PutNotifyMsg("Exit", "Conv_HtmlToCpd", InFPath, OutCpdFNm);
  return true;
}

bool Conv_Reuters21578ToCpd(char* InFPath, char* OutCpdFNm, int MxDocs){
  State->PutNotifyMsg("Call", "Conv_Reuters21578ToCpd", InFPath, OutCpdFNm);
  TCpDoc::SaveReuters21578ToCpd(InFPath, OutCpdFNm, MxDocs);
  State->PutNotifyMsg("Exit", "Conv_Reuters21578ToCpd", InFPath, OutCpdFNm);
  return true;
}

bool Conv_Reuters2000ToCpd(char* InFPath, char* OutCpdFNm, int MxDocs){
  State->PutNotifyMsg("Call", "Conv_Reuters2000ToCpd", InFPath, OutCpdFNm);
  TCpDoc::SaveReuters2000ToCpd(InFPath, OutCpdFNm, MxDocs);
  State->PutNotifyMsg("Exit", "Conv_Reuters2000ToCpd", InFPath, OutCpdFNm);
  return true;
}

bool Conv_AcmTechNewsToCpd(char* InFPath, char* OutCpdFNm, int MxDocs){
  State->PutNotifyMsg("Call", "Conv_AcmTechNewsToCpd", InFPath, OutCpdFNm);
  TCpDoc::SaveAcmTechNewsToCpd(InFPath, OutCpdFNm, MxDocs);
  State->PutNotifyMsg("Exit", "Conv_AcmTechNewsToCpd", InFPath, OutCpdFNm);
  return true;
}

bool Conv_CiaWFBToCpd(char* InFPath, char* OutCpdFNm){
  State->PutNotifyMsg("Call", "Conv_CiaWFBToCpd", InFPath, OutCpdFNm);
  TCpDoc::SaveCiaWFBToCpd(InFPath, OutCpdFNm);
  State->PutNotifyMsg("Exit", "Conv_CiaWFBToCpd", InFPath, OutCpdFNm);
  return true;
}

bool Conv_CpdToLnDocTxt(char* InCpdFNm, char* OutLnDocFNm){
  State->PutNotifyMsg("Call", "Conv_CpdToLnDocTxt", InCpdFNm, OutLnDocFNm);
  TBowFl::SaveCpdToLnDocTxt(InCpdFNm, OutLnDocFNm);
  State->PutNotifyMsg("Exit", "Conv_CpdToLnDocTxt", InCpdFNm, OutLnDocFNm);
  return true;
}

/////////////////////////////////////////////////
// conversions to Bow-Doc-Base
bool Conv_HtmlToBow(
 char* InFPath, char* OutBowFNm,
 bool RecurseDirP, int Recs,
 char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq){
  State->PutNotifyMsg("Call", "Conv_HtmlToBow", InFPath, OutBowFNm);
  PBowDocBs BowDocBs=TBowFl::LoadHtmlTxt(InFPath, RecurseDirP, Recs,
    SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  BowDocBs->SaveBin(OutBowFNm);
  State->PutNotifyMsg("Exit", "Conv_HtmlToBow", InFPath, OutBowFNm);
  return true;
}

bool Conv_CpdToBow(
 char* InCpdFNm, char* OutBowFNm,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq){
  State->PutNotifyMsg("Call", "Conv_CpdToBow", InCpdFNm, OutBowFNm);
  PBowDocBs BowDocBs=TBowFl::LoadCpdTxt(
   InCpdFNm, Recs, SwSetTypeNm, StemmerTypeNm,
   MxNGramLen, MnNGramFq);
  BowDocBs->SaveBin(OutBowFNm);
  State->PutNotifyMsg("Exit", "Conv_CpdToBow", InCpdFNm, OutBowFNm);
  return true;
}

int Conv_GetBowFromCpd(
 int CpdSInId,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq){
  State->PutNotifyMsg("Call", "Conv_GetBowFromCpd", CpdSInId);
  PSIn CpdSIn=State->GetSIn(CpdSInId);
  PBowDocBs BowDocBs=TBowFl::LoadCpdTxt(
   CpdSIn, Recs, SwSetTypeNm, StemmerTypeNm,
   MxNGramLen, MnNGramFq);
  int BowDocBsId=State->AddBowDocBs(BowDocBs);
  State->PutNotifyMsg("FExit", "Conv_GetBowFromCpd", CpdSInId);
  State->PutNotifyMsgRes(BowDocBsId);
  return BowDocBsId;
}

bool Conv_LnDocToBow(
 char* InLnDocFNm, char* OutBowFNm,
 bool NamedP, int Recs,
 char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq){
  State->PutNotifyMsg("Call", "Conv_LnDocToBow", InLnDocFNm, OutBowFNm);
  PBowDocBs BowDocBs=TBowFl::LoadLnDocTxt(
   InLnDocFNm, NamedP, Recs, SwSetTypeNm, StemmerTypeNm,
   MxNGramLen, MnNGramFq);
  BowDocBs->SaveBin(OutBowFNm);
  State->PutNotifyMsg("Exit", "Conv_LnDocToBow", InLnDocFNm, OutBowFNm);
  return true;
}

bool Conv_Reuters21578ToBow(
 char* InFPath, char* OutBowFNm,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq){
  State->PutNotifyMsg("Call", "Conv_Reuters21578ToBow", InFPath, OutBowFNm);
  PBowDocBs BowDocBs=TBowFl::LoadReuters21578Txt(
   InFPath, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  BowDocBs->SaveBin(OutBowFNm);
  State->PutNotifyMsg("Exit", "Conv_Reuters21578ToBow", InFPath, OutBowFNm);
  return true;
}

bool Conv_CiaWFBToBow(
 char* InFPath, char* OutBowFNm,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq){
  State->PutNotifyMsg("Call", "Conv_CiaWFBToBow", InFPath, OutBowFNm);
  PBowDocBs BowDocBs=TBowFl::LoadCiaWFBTxt(
   InFPath, Recs, SwSetTypeNm, StemmerTypeNm, MxNGramLen, MnNGramFq);
  BowDocBs->SaveBin(OutBowFNm);
  State->PutNotifyMsg("Exit", "Conv_CiaWFBToBow", InFPath, OutBowFNm);
  return true;
}

/////////////////////////////////////////////////
// Bow-Doc-Base Manipulation
int BowDocBs_New(char* SwSetTypeNm, char* StemmerTypeNm){
  State->PutNotifyMsg("Call", "BowDocBs_New", SwSetTypeNm, StemmerTypeNm);
  // stop-words
  TSwSetType SwSetType=TSwSet::GetSwSetType(SwSetTypeNm);
  PSwSet SwSet=TSwSet::New(SwSetType);
  // stemmer
  TStemmerType StemmerType=TStemmer::GetStemmerType(StemmerTypeNm);
  PStemmer Stemmer=TStemmer::New(StemmerType, true);
  // n-grams dictionary
  PNGramBs NGramBs=NULL;
  // create bag-of-words
  PBowDocBs BowDocBs=TBowDocBs::New(SwSet, Stemmer, NGramBs);
  int BowDocBsId=State->AddBowDocBs(BowDocBs);
  // return
  State->PutNotifyMsg("FExit", "BowDocBs_New", SwSetTypeNm, StemmerTypeNm);
  State->PutNotifyMsgRes(BowDocBsId);
  return BowDocBsId;
}

int BowDocBs_Load(int SInId){
  State->PutNotifyMsg("Call", "BowDocBs_Load", SInId);
  PSIn SIn=State->GetSIn(SInId);
  PBowDocBs BowDocBs=TBowDocBs::Load(*SIn);
  int BowDocBsId=State->AddBowDocBs(BowDocBs);
  // return
  State->PutNotifyMsg("FExit", "BowDocBs_Load", SInId);
  State->PutNotifyMsgRes(BowDocBsId);
  return BowDocBsId;
}

void BowDocBs_Save(int BowDocBsId, int SOutId){
  State->PutNotifyMsg("Call", "BowDocBs_Save", BowDocBsId, SOutId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PSOut SOut=State->GetSOut(SOutId);
  BowDocBs->Save(*SOut);
  State->PutNotifyMsg("Exit", "BowDocBs_Save", BowDocBsId, SOutId);
}

int BowDocBs_LoadFromFile(char* FNm){
  State->PutNotifyMsg("Call", "BowDocBs_LoadFromFile", FNm);
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(FNm);
  int BowDocBsId=State->AddBowDocBs(BowDocBs);
  // return
  State->PutNotifyMsg("FExit", "BowDocBs_LoadFromFile", FNm);
  State->PutNotifyMsgRes(BowDocBsId);
  return BowDocBsId;
}

void BowDocBs_SaveToFile(int BowDocBsId, char* FNm){
  State->PutNotifyMsg("Call", "BowDocBs_SaveToFile", BowDocBsId, FNm);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  BowDocBs->SaveBin(FNm);
  State->PutNotifyMsg("Exit", "BowDocBs_SaveToFile", BowDocBsId, FNm);
}

void BowDocBs_SaveStatToFile(int BowDocBsId, char* FNm){
  State->PutNotifyMsg("Call", "BowDocBs_SaveStatToFile", BowDocBsId, FNm);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  BowDocBs->SaveTxtStat(FNm);
  State->PutNotifyMsg("Exit", "BowDocBs_SaveStatToFile", BowDocBsId, FNm);
}

void BowDocBs_Del(int BowDocBsId){
  State->PutNotifyMsg("Call", "BowDocBs_Del", BowDocBsId);
  State->DelBowDocBs(BowDocBsId);
  State->PutNotifyMsg("Exit", "BowDocBs_Del", BowDocBsId);
}

/////////////////////////////////////////////////
// Bow-Doc-Base Words
int BowDocBs_GetWords(int BowDocBsId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetWords();
}

bool BowDocBs_IsWordStr(int BowDocBsId, char* WordStr){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->IsWordStr(WordStr);
}

int BowDocBs_GetWId(int BowDocBsId, char* WordStr){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  int WId;
  if (BowDocBs->IsWordStr(WordStr, WId)){return WId;}
  else {return -1;}
}

char* BowDocBs_GetWordStr(int BowDocBsId, int WId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  TStr WordStr=BowDocBs->GetWordStr(WId);
  return CopyStrToCStr(WordStr);
}

/////////////////////////////////////////////////
// Bow-Doc-Base Categories
int BowDocBs_GetCats(int BowDocBsId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetCats();
}

bool BowDocBs_IsCatNm(int BowDocBsId, char* CatNm){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->IsCatNm(CatNm);
}

int BowDocBs_GetCId(int BowDocBsId, char* CatNm){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  int CId;
  if (BowDocBs->IsCatNm(CatNm, CId)){return CId;}
  else {return -1;}
}

char* BowDocBs_GetCatNm(int BowDocBsId, int CId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  TStr CatNm=BowDocBs->GetCatNm(CId);
  return CopyStrToCStr(CatNm);
}

/////////////////////////////////////////////////
// Bow-Doc-Base Documents
int BowDocBs_AddHtmlDocStr(int BowDocBsId,
 char* DocNm, char* HtmlDocStr, char* CatNmVStr, bool SaveDocP){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  TStrV CatNmV;
  TStr(CatNmVStr).SplitOnAllCh(';', CatNmV, true);
  int DId=BowDocBs->AddHtmlDoc(DocNm, CatNmV, HtmlDocStr, SaveDocP);
  return DId;
}

int BowDocBs_GetDocs(int BowDocBsId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocs();
}

bool BowDocBs_IsDocNm(int BowDocBsId, char* DocNm){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->IsDocNm(DocNm);
}

int BowDocBs_GetDId(int BowDocBsId, char* DocNm){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  int DId;
  if (BowDocBs->IsDocNm(DocNm, DId)){return DId;}
  else {return -1;}
}

char* BowDocBs_GetDocNm(int BowDocBsId, int DId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  TStr DocNm=BowDocBs->GetDocNm(DId);
  char* DocNmCStr=CopyStrToCStr(DocNm);
  return DocNmCStr;
}

int BowDocBs_GetDocWIds(int BowDocBsId, int DId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocWIds(DId);
}

int BowDocBs_GetDocWId(int BowDocBsId, int DId, int DocWIdN){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocWId(DId, DocWIdN);
}

int BowDocBs_GetDocWIdN(int BowDocBsId, int DId, int DocWId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocWIdN(DId, DocWId);
}

void BowDocBs_PutDocWFq(int BowDocBsId, int DId, int DocWIdN, double WFq){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  BowDocBs->PutDocWFq(DId, DocWIdN, WFq);
}

double BowDocBs_GetDocWFq(int BowDocBsId, int DId, int DocWIdN){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocWFq(DId, DocWIdN);
}

int BowDocBs_GetDocCIds(int BowDocBsId, int DId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocCIds(DId);
}

int BowDocBs_GetDocCId(int BowDocBsId, int DId, int DocCIdN){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  return BowDocBs->GetDocCId(DId, DocCIdN);
}

/////////////////////////////////////////////////
// Bow-Doc-Weight-Base Manipulation
int BowDocWgtBs_Gen(int BowDocBsId){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF);
  return State->AddBowDocWgtBs(BowDocWgtBs);
}

void BowDocWgtBs_Del(int BowDocWgtBsId){
  State->DelBowDocWgtBs(BowDocWgtBsId);
}

/////////////////////////////////////////////////
// Bow-Doc-Weight-Base
int BowDocWgtBs_GetDocs(int BowDocWgtBsId){
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  return BowDocWgtBs->GetDocs();
}

int BowDocWgtBs_GetDocId(int BowDocWgtBsId, int DIdN){
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  return BowDocWgtBs->GetDId(DIdN);
}

int BowDocWgtBs_GetDocWIds(int BowDocWgtBsId, int DId){
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  PBowSpV BowSpV=BowDocWgtBs->GetSpV(DId);
  return BowSpV->GetWIds();
}

int BowDocWgtBs_GetDocWId(int BowDocWgtBsId, int DId, int DocWIdN){
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  PBowSpV BowSpV=BowDocWgtBs->GetSpV(DId);
  return BowSpV->GetWId(DocWIdN);
}

double BowDocWgtBs_GetDocWWgt(int BowDocWgtBsId, int DId, int DocWIdN){
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  PBowSpV BowSpV=BowDocWgtBs->GetSpV(DId);
  return BowSpV->GetWgt(DocWIdN);
}

int BowDocWgtBs_GetWgtWordPrV(
 int BowDocWgtBsId, int BowDocBsId, int DId,
 int TopWords, double TopWordsWgtPrc){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  PBowSpV BowSpV=BowDocWgtBs->GetSpV(DId);
  // prepare word-weight-vector
  TStrFltPrV WordStrWgtPrV;
  BowSpV->GetWordStrWgtPrV(BowDocBs, TopWords, TopWordsWgtPrc, WordStrWgtPrV);
  // prepare weight-word-vector
  TFltStrPrV WgtWordStrPrV;
  for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
    WgtWordStrPrV.Add(TFltStrPr(WordStrWgtPrV[WordN].Val2, WordStrWgtPrV[WordN].Val1));
  }
  // prepare float-string-pair-id
  int FSPrVId=State->AddFltStrPrV(WgtWordStrPrV);
  return FSPrVId;
}

int BowDocWgtBs_Search(int BowDocWgtBsId, int BowDocBsId, char* QueryStr){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  // get query document in bow form
  PBowSpV QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(QueryStr, BowDocWgtBs);
  // calculate similarity
  PBowSim BowSim=TBowSim::New(bstCos);
  TFltIntKdV SimDIdKdV; BowDocWgtBs->GetSimDIdV(QueryBowSpV, BowSim, SimDIdKdV);
  // create result-set
  PRSet RSet=TRSet::New();
  for (int DocN=0; DocN<SimDIdKdV.Len(); DocN++){
    double Sim=SimDIdKdV[DocN].Key;
    int DId=SimDIdKdV[DocN].Dat;
    TStr DocNm=BowDocBs->GetDocNm(DId);
    PBowSpV BowSpV=BowDocBs->GetDocSpV(DId);
    TStrFltPrV WordStrWgtPrV;
    BowSpV->GetWordStrWgtPrV(BowDocBs, 25, 0.66, WordStrWgtPrV);
    TChA CtxChA;
    for (int WordN=0; WordN<WordStrWgtPrV.Len(); WordN++){
      if (WordN>0){CtxChA+=", ";}
      CtxChA+=WordStrWgtPrV[WordN].Val1.GetLc();
    }
    RSet->AddHit(DocNm, DocNm, TFlt::GetStr(Sim, "%.6f"), CtxChA);
  }
  // prepare and return result-set-id
  int RSetId=State->AddRSet(RSet);
  return RSetId;
}

/////////////////////////////////////////////////
// Bow-Doc-Partition manipulaiton
int BowDocPart_Load(int SInId){
  State->PutNotifyMsg("Call", "BowDocPart_Load", SInId);
  PSIn SIn=State->GetSIn(SInId);
  PBowDocPart BowDocPart=TBowDocPart::Load(*SIn);
  int BowDocPartId=State->AddBowDocPart(BowDocPart);
  State->PutNotifyMsg("FExit", "BowDocPart_Load", SInId);
  State->PutNotifyMsgRes(BowDocPartId);
  return BowDocPartId;
}

void BowDocPart_Save(int BowDocPartId, int SOutId){
  State->PutNotifyMsg("Call", "BowDocPart_Save", BowDocPartId, SOutId);
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PSOut SOut=State->GetSOut(SOutId);
  BowDocPart.Save(*SOut);
  State->PutNotifyMsg("Exit", "BowDocPart_Save", BowDocPartId, SOutId);
}

int BowDocPart_LoadFromFile(char* FNm){
  State->PutNotifyMsg("Call", "BowDocPart_LoadFromFile", FNm);
  PBowDocPart BowDocPart=TBowDocPart::LoadBin(FNm);
  int BowDocPartId=State->AddBowDocPart(BowDocPart);
  State->PutNotifyMsg("FExit", "BowDocPart_LoadFromFile", FNm);
  State->PutNotifyMsgRes(BowDocPartId);
  return BowDocPartId;
}

void BowDocPart_SaveToFile(int BowDocPartId, char* FNm){
  State->PutNotifyMsg("Call", "BowDocPart_SaveToFile", FNm);
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  BowDocPart->SaveBin(FNm);
  State->PutNotifyMsg("Exit", "BowDocPart_SaveToFile", FNm);
}

void BowDocPart_SaveStatToFile(int BowDocPartId, int BowDocBsId, char* FNm){
  State->PutNotifyMsg("Call", "BowDocPart_SaveStatToFile", FNm);
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  BowDocPart->SaveTxt(FNm, BowDocBs);
  State->PutNotifyMsg("Exit", "BowDocPart_SaveStatToFile", FNm);
}

void BowDocPart_Del(int BowDocPartId){
  State->PutNotifyMsg("Call", "BowDocPart_Del");
  State->DelBowDocPart(BowDocPartId);
  State->PutNotifyMsg("Exit", "BowDocPart_Del");
}

/////////////////////////////////////////////////
// Clustering into Bow-Doc-Partition
int BowDocPart_GetKMeans(
 int BowDocBsId, int Clusts,
 int ClustTrials, double ConvergEps, int MnDocsPerClust,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs){
  State->PutNotifyMsg("Call", "BowDocPart_GetKMeans", BowDocBsId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // get document-ids
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  if (RndSeed!=-1){
    TRnd Rnd(RndSeed); DIdV.Shuffle(Rnd);}
  if (MxDocs!=-1){DIdV.Trunc(MxDocs);}

  // get document-partition
  PBowSim BowSim=TBowSim::New(bstCos); // similarity object
  TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
  PBowDocPart BowDocPart=TBowClust::GetKMeansPart(
   TNotify::StdNotify, // log output
   BowDocBs, // document data
   BowSim, // similarity function
   TRnd(RndSeed), // random generator
   Clusts, // number of clusters
   ClustTrials, // trials per k-means
   ConvergEps, // convergence epsilon for k-means
   1, // min. documents per cluster
   WordWgtType, // word weighting
   CutWordWgtSumPrc, // cut-word-weights percentage
   MnWordFq, // minimal word frequency
   DIdV); // training documents

  // save partition
  int BowDocPartId=State->AddBowDocPart(BowDocPart);

  // return partition-id
  State->PutNotifyMsg("FExit", "BowDocPart_GetKMeans", BowDocBsId);
  State->PutNotifyMsgRes(BowDocPartId);
  return BowDocPartId;
}

int BowDocPart_GetHKMeans(
 int BowDocBsId, int MxDocsPerLeafClust,
 int ClustTrials, double ConvergEps, int MnDocsPerClust,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs){
  State->PutNotifyMsg("Call", "BowDocPart_GetHKMeans", BowDocBsId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // get document-ids
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  if (RndSeed!=-1){
    TRnd Rnd(RndSeed); DIdV.Shuffle(Rnd);}
  if (MxDocs!=-1){DIdV.Trunc(MxDocs);}

  // get document-partition
  PBowSim BowSim=TBowSim::New(bstCos); // similarity object
  TBowWordWgtType WordWgtType=bwwtNrmTFIDF; // define weighting
  PBowDocPart BowDocPart=TBowClust::GetHKMeansPart(
   TNotify::StdNotify, // log output
   BowDocBs, // document data
   BowSim, // similarity function
   TRnd(RndSeed), // random generator
   MxDocsPerLeafClust, // max. documents per leaf cluster
   ClustTrials, // trials per k-means
   ConvergEps, // convergence epsilon for k-means
   1, // min. documents per cluster
   WordWgtType, // word weighting
   CutWordWgtSumPrc, // cut-word-weights percentage
   MnWordFq, // minimal word frequency
   DIdV, // training documents
   false, NULL); // propagate weights, weights-base

  // save partition
  int BowDocPartId=State->AddBowDocPart(BowDocPart);

  // return partition-id
  State->PutNotifyMsg("FExit", "BowDocPart_GetHKMeans", BowDocBsId);
  State->PutNotifyMsgRes(BowDocPartId);
  return BowDocPartId;
}

/////////////////////////////////////////////////
// Bow-Doc-Partition Clusters
int BowDocPart_GetClusts(int BowDocPartId){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  return BowDocPart->GetClusts();
}

int BowDocPart_GetDocs(int BowDocPartId, int ClustN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetDocs();
}

int BowDocPart_GetDId(int BowDocPartId, int ClustN, int DIdN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetDId(DIdN);
}

double BowDocPart_GetMeanSim(int BowDocPartId, int ClustN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetMeanSim();
}

double BowDocPart_GetDCSim(int BowDocPartId, int ClustN, int DId){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetDCSim(DId);
}

int BowDocPart_GetConceptWords(int BowDocPartId, int ClustN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetConceptWords();
}

int BowDocPart_GetConceptWId(int BowDocPartId, int ClustN, int WIdN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetConceptSpV()->GetWId(WIdN);
}

double BowDocPart_GetConceptWWgt(int BowDocPartId, int ClustN, int WIdN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->GetConceptSpV()->GetWgt(WIdN);
}

bool BowDocPart_IsSubPart(int BowDocPartId, int ClustN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  return BowDocPartClust->IsSubPart();
}

int BowDocPart_GetSubPart(int BowDocPartId, int ClustN){
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowDocPartClust BowDocPartClust=BowDocPart->GetClust(ClustN);
  PBowDocPart SubPart=BowDocPartClust->GetSubPart();
  int SubPartId=State->AddBowDocPart(SubPart);
  return SubPartId;
}

/////////////////////////////////////////////////
// Semantic-Space Manipulation
int SemSpace_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  PSemSpace SemSpace=TSemSpace::Load(*SIn);
  int SemSpaceId=State->AddSemSpace(SemSpace);
  return SemSpaceId;
}

void SemSpace_Save(int SemSpaceId, int SOutId){
  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
  PSOut SOut=State->GetSOut(SOutId);
  SemSpace.Save(*SOut);
}

int SemSpace_LoadFromFile(char* FNm){
  printf("Call LoadSemSpace('%s')\n", FNm);
  PSemSpace SemSpace=TSemSpace::LoadBin(FNm);
  int SemSpaceId=State->AddSemSpace(SemSpace);
  printf("Exit LoadSemSpace\n");
  return SemSpaceId;
}

void SemSpace_SaveToFile(int SemSpaceId, char* FNm){
  printf("Call SaveSemSpace(%d, '%s')\n", SemSpaceId, FNm);
  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
  SemSpace->SaveBin(FNm);
  printf("Exit SaveSemSpace\n");
}

void SemSpace_SaveStatToFile(int SemSpaceId, int BowDocBsId, char* FNm){
  printf("Call SaveSemSpaceStat(%d, '%s')\n", SemSpaceId, FNm);
  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  SemSpace->SaveTxt(FNm, BowDocBs, 1, 100);
  printf("Exit SaveSemSpaceStat\n");
}

void SemSpace_Del(int SemSpaceId){
  printf("Call SaveSemSpaceStat(%d)\n", SemSpaceId);
  State->DelSemSpace(SemSpaceId);
  printf("Exit DelSemSpace\n");
}

/////////////////////////////////////////////////
// Semantic-Space Dimensions
int SemSpace_GetDims(int SemSpaceId){
  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
  return SemSpace->GetVecLen();
}

int SemSpace_GetDim(int SemSpaceId, int BowDocBsId, int DimN){
  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // get dimension-vector word-weights (words are aligned with BowDocBs)
  TFltV WgtV; SemSpace->GetVec(DimN, WgtV);
  TFltStrPrV WordWgtStrPrV; int WIds=WgtV.Len();
  for (int WId=0; WId<WIds; WId++){
    WordWgtStrPrV.Add(TFltStrPr(WgtV[WId], BowDocBs->GetWordStr(WId)));
  }
  WordWgtStrPrV.Sort(false);
  // store dimension-vector
  int DimFSPrVId=State->AddFltStrPrV(WordWgtStrPrV);
  // return dimension-vector-id
  return DimFSPrVId;
}

/////////////////////////////////////////////////
// Decomposition into Semantic-Space
int SemSpace_GetLSI(int BowDocBsId, int SpaceDims){
  printf("Call GetLSISemSpace(%d, %d)\n", BowDocBsId, SpaceDims);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF);
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  PSemSpace SemSpace=
   TSemSpaceAlg::CalcSparseLSI(BowDocWgtBs, DIdV, SpaceDims, 3*SpaceDims, ssotFull);
  int SemSpaceId=State->AddSemSpace(SemSpace);
  printf("Exit GetLSISemSpace\n");
  return SemSpaceId;
}

int SemSpace_GetLSIFromBowPart(int BowDocPartId, int SpaceDims){
  printf("Call GetLSISemSpaceFromBowPart(%d, %d)\n", BowDocPartId, SpaceDims);
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  // collect centroid vectors
  TVec<PBowSpV> DocSpV;
  for (int ClustN=0; ClustN<BowDocPart->GetClusts(); ClustN++){
    DocSpV.Add(BowDocPart->GetClust(ClustN)->GetConceptSpV());
  }
  PSemSpace SemSpace=
   TSemSpaceAlg::CalcSparseLSI(DocSpV, SpaceDims, 3*SpaceDims, ssotFull);
  int SemSpaceId=State->AddSemSpace(SemSpace);
  printf("Exit GetLSISemSpaceFromBowPart\n");
  return SemSpaceId;
}

int SemSpace_GetPCA(int BowDocBsId){
  printf("Call GetPCASemSpace(%d)\n", BowDocBsId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(BowDocBs, bwwtNrmTFIDF);
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  PSemSpace SemSpace=TSemSpaceAlg::CalcKPCA(BowDocWgtBs, DIdV);
  int SemSpaceId=State->AddSemSpace(SemSpace);
  printf("Exit GetPCASemSpace\n");
  return SemSpaceId;
}

/////////////////////////////////////////////////
// Visualization-Map Manipulation
//int VizMap_Load(int SInId){
//  PSIn SIn=State->GetSIn(SInId);
//  PVizMap VizMap=TVizMap::Load(*SIn);
//  int VizMapId=State->AddVizMap(VizMap);
//  return VizMapId;
//}
//
//void VizMap_Save(int VizMapId, int SOutId){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  PSOut SOut=State->GetSOut(SOutId);
//  VizMap.Save(*SOut);
//}
//
//int VizMap_LoadFromFile(char* FNm){
//  printf("Call LoadVizMap('%s')\n", FNm);
//  PVizMap VizMap=TVizMap::LoadBin(FNm);
//  int VizMapId=State->AddVizMap(VizMap);
//  printf("Exit LoadVizMap\n");
//  return VizMapId;
//}
//
//void VizMap_SaveToFile(int VizMapId, char* FNm){
//  printf("Call SaveVizMap(%d, '%s')\n", VizMapId, FNm);
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  VizMap->SaveBin(FNm);
//  printf("Exit SaveVizMap\n");
//}
//
//void VizMap_Del(int VizMapId){
//  printf("Call SaveVizMapStat(%d)\n", VizMapId);
//  State->DelVizMap(VizMapId);
//  printf("Exit DelVizMap\n");
//}

/////////////////////////////////////////////////
// Visualization-Map
//int VizMap_GetMdsClustLsi(
// int BowDocBsId, int BowDocWgtBsId, int BowDocPartId, int SemSpaceId,
// int TopClusts, double SemSpaceTsh,
// int MxSteps, int MxSecs, double MnDiff){
//  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
//  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
//  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
//  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
//  PVizMap VizMap = TVizMapFactory::DocLsiMds(BowDocWgtBs, SemSpace, 
//      TVec<TFltV>(), SemSpaceTsh, MxSteps, MxSecs, MnDiff, TStdNotify::New());
//  TVizMapFactory::AddDocMetadata(VizMap, BowDocBs, BowDocBs, BowDocWgtBs);
//  int VizMapId=State->AddVizMap(VizMap);
//  return VizMapId;
//}
//
//int VizMap_GetMdsLsi(
// int BowDocBsId, int BowDocWgtBsId, int SemSpaceId,
// double SemSpaceTsh,
// int MxSteps, int MxSecs, double MnDiff){
//  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
//  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
//  PSemSpace SemSpace=State->GetSemSpace(SemSpaceId);
//  PVizMap VizMap=TVizMapFactory::DocLsiMds(BowDocWgtBs, SemSpace, 
//      TVec<TFltV>(), SemSpaceTsh, MxSteps, MxSecs, MnDiff, 
//      TStdNotify::New());
//  TVizMapFactory::AddDocMetadata(VizMap, BowDocBs, BowDocBs, BowDocWgtBs);
//  int VizMapId=State->AddVizMap(VizMap);
//  return VizMapId;
//}
//
//int VizMap_GetBowDocBsId(int VizMapId){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  PBowDocBs BowDocBs=VizMap->GetKeyWdBow();
//  int BowDocBsId=State->AddBowDocBs(BowDocBs);
//  return BowDocBsId;
//}
//
//int VizMap_GetBowDocWgtBsId(int VizMapId){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  PBowDocWgtBs BowDocWgtBs=VizMap->GetKeyWdWgtBow();
//  int BowDocWgtBsId=State->AddBowDocWgtBs(BowDocWgtBs);
//  return BowDocWgtBsId;
//}
//
//int VizMap_GetDocs(int VizMapId){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetPoints();
//}
//
//int VizMap_GetDId(int VizMapId, int DIdN){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetPoint(DIdN)->GetDocId();
//}
//
//double VizMap_GetDocX(int VizMapId, int DIdN){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetPoint(DIdN)->GetPointX();
//}
//
//double VizMap_GetDocY(int VizMapId, int DIdN){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetPoint(DIdN)->GetPointY();
//}
//
//int VizMap_GetXYDId(int VizMapId, double X, double Y, double Radius){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  int PointN=VizMap->GetPointN(TFltV::GetV(X, Y), Radius);
//  int DId=-1;
//  if (PointN!=-1){DId=VizMap->GetPoint(PointN)->GetDocId();}
//  return DId;
//}
//
//void VizMap_GenLandscape(int VizMapId,
// int Landscapes, int Width, int Height,
// double BellSigma, double BellSigmaDecay){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  double Sigma = BellSigma;
//  for (int LandscapeN = 0; LandscapeN < Landscapes; LandscapeN++) {
//    VizMap->AddLandscape(Width, Height, Sigma, false);
//    Sigma *= BellSigmaDecay;
//  }
//}
//
//int VizMap_GetLandscapes(int VizMapId){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetLandscapes();
//}
//
//void VizMap_SaveVrmlToFile(
// int VizMapId, char* VrmlFNm, int LandscapeN,
// bool ShowDocNmP, bool ShowDocPtP, bool ShowKWordsP,
// double FontSize){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  PVizMapLandscape Landscape=VizMap->GetLandscape(LandscapeN);
//  VizMap->SaveVrml(VrmlFNm, Landscape, ShowDocNmP,
//    ShowDocPtP, ShowKWordsP, FontSize);
//}
//
//void VizMap_GenKeywords(int VizMapId,
// int KWords, double Radius, int Candidates){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  VizMap->GenKeyWds(KWords, Radius, Candidates, 1);
//}
//
//int VizMap_GetKWords(int VizMapId){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetKeyWds();
//}
//
//char* VizMap_GetKWordStr(int VizMapId, int KWordN){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return CopyStrToCStr(VizMap->GetKeyWd(KWordN)->GetKeyWdStr());
//}
//
//double VizMap_GetKWordX(int VizMapId, int KWordN){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetKeyWd(KWordN)->GetKeyWdX();
//}
//
//double VizMap_GetKWordY(int VizMapId, int KWordN){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  return VizMap->GetKeyWd(KWordN)->GetKeyWdY();
//}
//
//int VizMap_GetKWordStrV(int VizMapId, double X, double Y, double Radius, int MxKWords){
//  PVizMap VizMap=State->GetVizMap(VizMapId);
//  TStrV KWordStrV;
//  VizMap->GenKeyWd(TFltV::GetV(X, Y), Radius, MxKWords, KWordStrV);
//  int KWordStrVId=State->AddStrV(KWordStrV);
//  return KWordStrVId;
//}

/////////////////////////////////////////////////
// Bow-Model Manipulation
int BowMd_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  PBowMd BowMd=TBowMd::Load(*SIn);
  int BowMdId=State->AddBowMd(BowMd);
  return BowMdId;
}

void BowMd_Save(int BowMdId, int SOutId){
  PBowMd BowMd=State->GetBowMd(BowMdId);
  PSOut SOut=State->GetSOut(SOutId);
  BowMd.Save(*SOut);
}

int BowMd_LoadFromFile(char* FNm, int BowDocBsId){
  printf("Call LoadBowMd('%s')\n", FNm);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowMd BowMd=TBowMd::LoadBin(FNm, BowDocBs);
  int BowMdId=State->AddBowMd(BowMd);
  printf("Exit LoadBowMd\n");
  return BowMdId;
}

void BowMd_SaveToFile(int BowMdId, char* FNm){
  printf("Call SaveBowMd(%d, '%s')\n", BowMdId, FNm);
  PBowMd BowMd=State->GetBowMd(BowMdId);
  BowMd->SaveBin(FNm);
  printf("Exit SaveBowMd\n");
}

void BowMd_Del(int BowMdId){
  printf("Call SaveBowMdStat(%d)\n", BowMdId);
  State->DelBowMd(BowMdId);
  printf("Exit DelBowMd\n");
}

/////////////////////////////////////////////////
// Bow-Model Information
bool BowMd_IsCat(int BowMdId){
  PBowMd BowMd=State->GetBowMd(BowMdId);
  return BowMd->IsCat();
}

char* BowMd_GetCatNm(int BowMdId){
  PBowMd BowMd=State->GetBowMd(BowMdId);
  return CopyStrToCStr(BowMd->GetCatNm());
}

bool BowMd_IsLinComb(int BowMdId){
  PBowMd BowMd=State->GetBowMd(BowMdId);
  return BowMd->IsLinComb();
}

int BowMd_GetLinCombWgtWordPrV(int BowMdId, int BowDocBsId){
  PBowMd BowMd=State->GetBowMd(BowMdId);
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  TFltStrPrV WgtWordStrPrV; double Tsh;
  BowMd->GetLinComb(BowDocBs, WgtWordStrPrV, Tsh);
  return State->AddFltStrPrV(WgtWordStrPrV);
}

double BowMd_GetLinCombTsh(int BowMdId){
  PBowMd BowMd=State->GetBowMd(BowMdId);
  TFltStrPrV WgtWordStrPrV; double Tsh;
  BowMd->GetLinComb(NULL, WgtWordStrPrV, Tsh);
  return Tsh;
}

/////////////////////////////////////////////////
// Training into Bow-Model
int BowMd_GetBinSVM(
 int BowDocBsId, int CId, double Cost, double CostWgt,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs){
  printf("Call GetBinSVMBowMd\n");
  // get document-base
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);

  // get category-id
  TStr CatNm=BowDocBs->GetCatNm(CId);

  // get document-ids
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  if (RndSeed!=-1){
    TRnd Rnd(RndSeed); DIdV.Shuffle(Rnd);}
  if (MxDocs!=-1){DIdV.Trunc(MxDocs);}

  // get weights
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(
   BowDocBs, bwwtNrmTFIDF, CutWordWgtSumPrc, MnWordFq, DIdV);

  // get model
  PBowMd BowMd=
   TBowSVMMd::NewClsLinear(BowDocBs, BowDocWgtBs, CatNm, DIdV,
    Cost, CostWgt, false, TSVMLearnParam::Lin(60, 0, 36, 1e-3, true));

  // save model
  int BowMdId=State->AddBowMd(BowMd);

  // return model-id
  printf("Exit GetBinSVMBowMd\n");
  return BowMdId;
}

int BowMd_GetOneClassSVM(
 int BowDocBsId, int CId, double Nu,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs){
  printf("Call GetOneClassSVMBowMd\n");
  // get document-base
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);

  // get category-id
  TStr CatNm=BowDocBs->GetCatNm(CId);

  // get document-ids
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  if (RndSeed!=-1){
    TRnd Rnd(RndSeed); DIdV.Shuffle(Rnd);}
  if (MxDocs!=-1){DIdV.Trunc(MxDocs);}

  // get weights
  PBowDocWgtBs BowDocWgtBs=TBowDocWgtBs::New(
   BowDocBs, bwwtNrmTFIDF, CutWordWgtSumPrc, MnWordFq, DIdV);

  // get model
  PBowMd BowMd=TBowSVMMd::NewOneClassLinear(BowDocBs, BowDocWgtBs, CatNm, DIdV,
   Nu, TSVMLearnParam::Lin(-1, 0, 36, 1e-3, true));

  // save model
  int BowMdId=State->AddBowMd(BowMd);

  // return model-id
  printf("Exit GetOneClassSVMBowMd\n");
  return BowMdId;
}

int BowMd_GetWinnow(
 int BowDocBsId, int CId, double Beta,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs){
  printf("Call GetWinnowBowMd\n");
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // get category-id
  TStr CatNm=BowDocBs->GetCatNm(CId);
  // get document-ids
  TIntV DIdV; BowDocBs->GetAllDIdV(DIdV);
  if (RndSeed!=-1){
    TRnd Rnd(RndSeed); DIdV.Shuffle(Rnd);}
  if (MxDocs!=-1){DIdV.Trunc(MxDocs);}

  // get model
  PBowMd BowMd=TBowWinnowMd::New(BowDocBs, CatNm, Beta);

  // save model
  int BowMdId=State->AddBowMd(BowMd);

  // return model-id
  printf("Exit GetWinnowBowMd\n");
  return BowMdId;
}

/////////////////////////////////////////////////
// Classification using Bow-Model
double BowMd_GetCfyFromDocBs(int BowMdId, int BowDocBsId, int DId){
  // prepare model
  PBowMd BowMd=State->GetBowMd(BowMdId);
  // prepare document-base
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // prepare sparse vector from text
  PBowSpV BowSpV=BowDocBs->GetDocSpV(DId);
  // classification
  TFltStrPrV WgtCatNmPrV; BowMd->GetCfy(BowSpV, WgtCatNmPrV);
  // return
  return WgtCatNmPrV[0].Val1;
}

double BowMd_GetCfyFromHtml(int BowMdId, int BowDocBsId, char* HtmlStr){
  // prepare model
  PBowMd BowMd=State->GetBowMd(BowMdId);
  // prepare document-base
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // create sparse vector from text
  PBowSpV BowSpV=BowDocBs->GetSpVFromHtmlStr(HtmlStr);
  // classification
  TFltStrPrV WgtCatNmPrV; BowMd->GetCfy(BowSpV, WgtCatNmPrV);
  // return
  return WgtCatNmPrV[0].Val1;
}

/////////////////////////////////////////////////
// Bow-Active-Learning
int BowAL_New(
 int BowDocBsId, int CId, double Cost, double CostWgt){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  // create active-learning object
  PBowAL BowAL=TBowAL::NewFromCat(BowDocBs, CId, Cost, CostWgt);
  // add to state & get active-learning-id
  int BowALId=State->AddBowAL(BowAL);
  // return active-learning-id
  return BowALId;
}

void BowAL_Del(int BowALId){
  State->DelBowAL(BowALId);
}

int BowAL_GetCId(int BowALId){
  PBowAL BowAL=State->GetBowAL(BowALId);
  return BowAL->GetCId();
}

bool BowAL_IsQueryDIdV(int BowALId){
  PBowAL BowAL=State->GetBowAL(BowALId);
  return BowAL->GenQueryDIdV();
}

int BowAL_GetQueries(int BowALId){
  PBowAL BowAL=State->GetBowAL(BowALId);
  return BowAL->GetQueryDIds();
}

double BowAL_GetQueryDist(int BowALId, int QueryN){
  PBowAL BowAL=State->GetBowAL(BowALId);
  double Dist; int DId; BowAL->GetQueryDistDId(QueryN, Dist, DId);
  return Dist;
}

int BowAL_GetQueryDId(int BowALId, int QueryN){
  PBowAL BowAL=State->GetBowAL(BowALId);
  double Dist; int DId; BowAL->GetQueryDistDId(QueryN, Dist, DId);
  return DId;
}

void BowAL_MarkQueryDId(int BowALId, int QueryDId, bool AssignToCatP){
  PBowAL BowAL=State->GetBowAL(BowALId);
  BowAL->MarkQueryDoc(QueryDId, AssignToCatP);
}

void BowAL_MarkUnlabeledPosDocs(int BowALId){
  PBowAL BowAL=State->GetBowAL(BowALId);
  BowAL->MarkUnlabeledPosDocs();
}

/////////////////////////////////////////////////
// Result-Set Manipulation
int RSet_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  PRSet RSet=TRSet::Load(*SIn);
  int RSetId=State->AddRSet(RSet);
  return RSetId;
}

void RSet_Save(int RSetId, int SOutId){
  PRSet RSet=State->GetRSet(RSetId);
  PSOut SOut=State->GetSOut(SOutId);
  RSet.Save(*SOut);
}

int RSet_LoadFromFile(char* FNm){
  printf("Call LoadRSet('%s')\n", FNm);
  PRSet RSet=TRSet::LoadBin(FNm);
  int RSetId=State->AddRSet(RSet);
  printf("Exit LoadRSet\n");
  return RSetId;
}

void RSet_SaveToFile(int RSetId, char* FNm){
  printf("Call SaveRSet(%d, '%s')\n", RSetId, FNm);
  PRSet RSet=State->GetRSet(RSetId);
  RSet->SaveBin(FNm);
  printf("Exit SaveRSet\n");
}

void RSet_SaveXmlToFile(int RSetId, char* FNm){
  printf("Call SaveRSetXml(%d, '%s')\n", RSetId, FNm);
  PRSet RSet=State->GetRSet(RSetId);
  RSet->SaveXml(FNm);
  printf("Exit SaveRSetXml\n");
}

void RSet_Del(int RSetId){
  printf("Call SaveRSetStat(%d)\n", RSetId);
  State->DelRSet(RSetId);
  printf("Exit DelRSet\n");
}

/////////////////////////////////////////////////
// Result-Set
char* RSet_GetUrlStr(int RSetId){
  PRSet RSet=State->GetRSet(RSetId);
  TStr UrlStr=RSet->GetUrlStr();
  char* UrlCStr=CopyStrToCStr(UrlStr);
  return UrlCStr;
}

char* RSet_GetNextUrlStr(int RSetId){
  PRSet RSet=State->GetRSet(RSetId);
  TStr UrlStr=RSet->GetNextUrlStr();
  char* UrlCStr=CopyStrToCStr(UrlStr);
  return UrlCStr;
}

char* RSet_GetQueryStr(int RSetId){
  PRSet RSet=State->GetRSet(RSetId);
  TStr QueryStr=RSet->GetQueryStr();
  char* QueryCStr=CopyStrToCStr(QueryStr);
  return QueryCStr;
}

int RSet_GetAllHits(int RSetId){
  PRSet RSet=State->GetRSet(RSetId);
  return RSet->GetAllHits();
}

int RSet_GetHits(int RSetId){
  PRSet RSet=State->GetRSet(RSetId);
  return RSet->GetHits();
}

int RSet_GetHitN(int RSetId, char* UrlStr, bool LcP){
  PRSet RSet=State->GetRSet(RSetId);
  return RSet->GetHitN(UrlStr, LcP);
}

char* RSet_GetHitUrlStr(int RSetId, int HitN){
  PRSet RSet=State->GetRSet(RSetId);
  TStr UrlStr=RSet->GetHitUrlStr(HitN);
  char* UrlCStr=CopyStrToCStr(UrlStr);
  return UrlCStr;
}

char* RSet_GetHitTitleStr(int RSetId, int HitN){
  PRSet RSet=State->GetRSet(RSetId);
  TStr TitleStr=RSet->GetHitTitleStr(HitN);
  char* TitleCStr=CopyStrToCStr(TitleStr);
  return TitleCStr;
}

char* RSet_GetHitSrcNm(int RSetId, int HitN){
  PRSet RSet=State->GetRSet(RSetId);
  TStr SrcNm=RSet->GetHitSrcNm(HitN);
  char* SrcCStr=CopyStrToCStr(SrcNm);
  return SrcCStr;
}

char* RSet_GetHitCtxStr(int RSetId, int HitN){
  PRSet RSet=State->GetRSet(RSetId);
  TStr CtxStr=RSet->GetHitCtxStr(HitN);
  char* CtxCStr=CopyStrToCStr(CtxStr);
  return CtxCStr;
}

/////////////////////////////////////////////////
// Google
int Google_WebSearch(char* QueryStr, int MxHits){
  PRSet RSet=TGg::WebSearch(QueryStr, MxHits);
  int RSetId=State->AddRSet(RSet);
  return RSetId;
}

int Google_NewsSearch(char* QueryStr, int MxHits){
  PRSet RSet=TGg::NewsSearch(QueryStr, MxHits);
  int RSetId=State->AddRSet(RSet);
  return RSetId;
}

/////////////////////////////////////////////////
// Named-Object-Base Manipulation
int NmObjBs_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  PNmObjBs NmObjBs=TNmObjBs::Load(*SIn);
  int NmObjBsId=State->AddNmObjBs(NmObjBs);
  return NmObjBsId;
}

void NmObjBs_Save(int NmObjBsId, int SOutId){
  PNmObjBs NmObjBs=State->GetNmObjBs(NmObjBsId);
  PSOut SOut=State->GetSOut(SOutId);
  NmObjBs.Save(*SOut);
}

int NmObjBs_LoadFromFile(char* FNm){
  printf("Call LoadNmObjBs('%s')\n", FNm);
  PNmObjBs NmObjBs=TNmObjBs::LoadBin(FNm);
  int NmObjBsId=State->AddNmObjBs(NmObjBs);
  printf("Exit LoadNmObjBs\n");
  return NmObjBsId;
}

void NmObjBs_SaveToFile(int NmObjBsId, char* FNm){
  printf("Call SaveNmObjBs(%d, '%s')\n", NmObjBsId, FNm);
  PNmObjBs NmObjBs=State->GetNmObjBs(NmObjBsId);
  NmObjBs->SaveBin(FNm);
  printf("Exit SaveNmObjBs\n");
}

void NmObjBs_SaveTxtToFile(int NmObjBsId,
 char* FqFNm, char* SwFNm, char* AbcFNm, char* DocFNm){
  printf("Call SaveNmObjBsTxt(%d)\n", NmObjBsId);
  PNmObjBs NmObjBs=State->GetNmObjBs(NmObjBsId);
  NmObjBs->SaveTxtNmObj(FqFNm, SwFNm, AbcFNm, DocFNm);
  printf("Exit SaveNmObjBsTxt\n");
}

void NmObjBs_Del(int NmObjBsId){
  printf("Call SaveNmObjBsStat(%d)\n", NmObjBsId);
  State->DelNmObjBs(NmObjBsId);
  printf("Exit DelNmObjBs\n");
}

/////////////////////////////////////////////////
// Named-Object-Base
int Conv_CpdToNmObjBs(
 int CpdSInId, char* SwSetTypeNm, int CustSwSetSInId,
 int NrWordBsSInId, int WordTypeBsSInId, int MxDocs){
  TSwSetType SwSetType=TSwSet::GetSwSetType(SwSetTypeNm);
  PSIn CpdSIn=State->GetSIn(CpdSInId);
  PSIn CustSwSetSIn=State->GetSIn(CustSwSetSInId);
  PSIn NrWordBsSIn=State->GetSIn(NrWordBsSInId);
  PSIn WordTypeBsSIn=State->GetSIn(WordTypeBsSInId);
  PNmObjBs NmObjBs=TNmObjBs::GetFromCpd(
   CpdSIn, SwSetType, CustSwSetSIn,
   NrWordBsSIn, WordTypeBsSIn, "", MxDocs, false);
  int NmObjBsId=State->AddNmObjBs(NmObjBs);
  return NmObjBsId;
}

int Conv_CpdToNmObjBsFromFile(
 char* CpdFNm, char* SwSetTypeNm, char* CustSwSetFNm,
 char* NrWordBsFNm, char* WordTypeBsFNm, int MxDocs){
  TSwSetType SwSetType=TSwSet::GetSwSetType(SwSetTypeNm);
  PNmObjBs NmObjBs=TNmObjBs::GetFromCpd(
   CpdFNm, SwSetType, CustSwSetFNm,
   NrWordBsFNm, WordTypeBsFNm, "", MxDocs, false);
  int NmObjBsId=State->AddNmObjBs(NmObjBs);
  return NmObjBsId;
}

int Conv_NmObjBsToBow(int NmObjBsId, int MnNmObjFq){
  PNmObjBs NmObjBs=State->GetNmObjBs(NmObjBsId);
  PBowDocBs BowDocBs=NmObjBs->GetBowDocBs(MnNmObjFq);
  int BowDocBsId=State->AddBowDocBs(BowDocBs);
  return BowDocBsId;
}

/////////////////////////////////////////////////
// Url
int Url_Get(char* RelUrlStr, char* BaseUrlStr){
  PUrl Url=TUrl::New(RelUrlStr, BaseUrlStr);
  int UrlId=State->AddUrl(Url);
  return UrlId;
}

void Url_Del(int UrlId){
  State->DelUrl(UrlId);
}

bool Url_IsOk(int UrlId, int Scheme){
  PUrl Url=State->GetUrl(UrlId);
  return Url->IsOk(TUrlScheme(Scheme));
}

bool Url_IsOkHttp(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  return Url->IsOk(usHttp);
}

int Url_GetScheme(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  return int(Url->GetScheme());
}

char* Url_GetUrlStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetUrlStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetRelUrlStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetRelUrlStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

bool Url_IsBaseUrl(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  return Url->IsBaseUrl();
}

char* Url_GetBaseUrlStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetBaseUrlStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetSchemeNm(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetSchemeNm();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetHostNm(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetHostNm();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetDmNm(int UrlId, int MxDmSegs){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetDmNm(MxDmSegs);
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetPortStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetPortStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int Url_GetPortN(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  return Url->GetPortN();
}

char* Url_GetPathStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetPathStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int Url_GetPathSegs(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  return Url->GetPathSegs();
}

char* Url_GetPathSeg(int UrlId, int PathSegN){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetPathSeg(PathSegN);
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetSearchStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetSearchStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* Url_GetFragIdStr(int UrlId){
  PUrl Url=State->GetUrl(UrlId);
  TStr Str=Url->GetFragIdStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

/////////////////////////////////////////////////
// Http-Response
int HttpResp_GetFromStr(char* HttpRespStr){
  PSIn SIn=TStrIn::New(HttpRespStr);
  PHttpResp HttpResp=THttpResp::New(SIn);
  int HttpRespId=State->AddHttpResp(HttpResp);
  return HttpRespId;
}

int HttpResp_GetFromFile(char* HttpRespFNm){
  PSIn SIn=TFIn::New(HttpRespFNm);
  PHttpResp HttpResp=THttpResp::New(SIn);
  int HttpRespId=State->AddHttpResp(HttpResp);
  return HttpRespId;
}

void HttpResp_Del(int HttpRespId){
  State->DelHttpResp(HttpRespId);
}

bool HttpResp_IsOk(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->IsOk();
}

int HttpResp_Len(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->Len();
}

char* HttpResp_GetHdStr(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TStr Str=HttpResp->GetHdStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int HttpResp_GetBodyAsMem(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TMem _Mem=HttpResp->GetBodyAsMem();
  PMem Mem=TMem::New(_Mem);
  int MemId=State->AddMem(Mem);
  return MemId;
}

char* HttpResp_GetBodyAsStr(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TStr Str=HttpResp->GetBodyAsStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int HttpResp_GetStatusCd(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->GetStatusCd();
}

bool HttpResp_IsStatusCd_Ok(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->IsStatusCd_Ok();
}

bool HttpResp_IsStatusCd_Redir(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->IsStatusCd_Redir();
}

char* HttpResp_GetReasonPhrase(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TStr Str=HttpResp->GetReasonPhrase();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int HttpResp_GetFlds(int HttpRespId){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->GetFlds();
}

char* HttpResp_GetFldNm(int HttpRespId, int FldN){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TStr FldNm; TStr FldVal; HttpResp->GetFldNmVal(FldN, FldNm, FldVal);
  TStr Str=FldNm;
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* HttpResp_GetFldVal(int HttpRespId, int FldN){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TStr FldNm; TStr FldVal; HttpResp->GetFldNmVal(FldN, FldNm, FldVal);
  TStr Str=FldVal;
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

bool HttpResp_IsFldNm(int HttpRespId, char* FldNm){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->IsFldNm(FldNm);
}

char* HttpResp_GetFldValByNm(int HttpRespId, char* FldNm){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  TStr Str=HttpResp->GetFldVal(FldNm);
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

bool HttpResp_IsFldVal(int HttpRespId, char* FldNm, char* FldVal){
  PHttpResp HttpResp=State->GetHttpResp(HttpRespId);
  return HttpResp->IsFldVal(FldNm,FldVal); 
}

/////////////////////////////////////////////////
// Html
int HtmlDoc_GetFromStr(char* HtmlStr){
  PSIn SIn=TStrIn::New(HtmlStr);
  PHtmlDoc HtmlDoc=THtmlDoc::New(SIn);
  int HtmlDocId=State->AddHtmlDoc(HtmlDoc);
  return HtmlDocId;
}

int HtmlDoc_GetFromFile(char* HtmlFNm){
  PSIn SIn=TFIn::New(HtmlFNm);
  PHtmlDoc HtmlDoc=THtmlDoc::New(SIn);
  int HtmlDocId=State->AddHtmlDoc(HtmlDoc);
  return HtmlDocId;
}

void HtmlDoc_Del(int HtmlDocId){
  State->DelHtmlDoc(HtmlDocId);
}

int HtmlDoc_GetToks(int HtmlDocId){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  return HtmlDoc->GetToks();
}

int HtmlDoc_GetTokSym(int HtmlDocId, int TokN){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  THtmlLxSym Sym=HtmlDoc->GetTok(TokN)->GetSym();
  return int(Sym);
}

char* HtmlDoc_GetTokStr(int HtmlDocId, int TokN){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  TStr Str=HtmlDoc->GetTok(TokN)->GetStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* HtmlDoc_GetTokFullStr(int HtmlDocId, int TokN){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  TStr Str=HtmlDoc->GetTok(TokN)->GetFullStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

bool HtmlDoc_IsTokArg(int HtmlDocId, int TokN, char* ArgNm){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  return HtmlDoc->GetTok(TokN)->IsArg(ArgNm);
}

char* HtmlDoc_GetTokArg(int HtmlDocId, int TokN, char* ArgNm, char* DfArgVal){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  TStr Str=HtmlDoc->GetTok(TokN)->GetArg(ArgNm, DfArgVal);
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

bool HtmlDoc_IsTokUrl(int HtmlDocId, int TokN){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  TStr RelUrlStr;
  return HtmlDoc->GetTok(TokN)->IsUrlTok(RelUrlStr);
}

char* HtmlDoc_GetTokUrlStr(int HtmlDocId, int TokN){
  PHtmlDoc HtmlDoc=State->GetHtmlDoc(HtmlDocId);
  TStr RelUrlStr;
  if (HtmlDoc->GetTok(TokN)->IsUrlTok(RelUrlStr)){
  } else {
    RelUrlStr="";
  }
  char* CStr=CopyStrToCStr(RelUrlStr);
  return CStr;
}

bool HtmlDoc_IsBreakTag(char* TagNm){
  return THtmlTok::IsBreakTag(TagNm);
}

char* HtmlDoc_GetSymStr(int Sym){
  TStr Str=THtmlLx::GetSymStr(THtmlLxSym(Sym));
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

/////////////////////////////////////////////////
// Web-Page
int WebPg_Fetch(char* UrlStr){
  PWebPg WebPg; bool Ok; TStr MsgStr;
  TWebFetchBlocking::GetWebPg(UrlStr, Ok, MsgStr, WebPg);
  if (Ok){
    int WebPgId=State->AddWebPg(WebPg);
    return WebPgId;
  } else {
    return -1;
  }
}

void WebPg_Del(int WebPgId){
  State->DelWebPg(WebPgId);
}

int WebPg_GetUrls(int WebPgId){
  PWebPg WebPg=State->GetWebPg(WebPgId);
  return WebPg->GetUrls();
}

char* WebPg_GetUrl(int WebPgId, int UrlN){
  PWebPg WebPg=State->GetWebPg(WebPgId);
  TStr Str=WebPg->GetUrl(UrlN)->GetUrlStr();
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int WebPg_GetHttpResp(int WebPgId){
  PWebPg WebPg=State->GetWebPg(WebPgId);
  PHttpResp HttpResp=WebPg->GetHttpResp();
  int HttpRespId=State->AddHttpResp(HttpResp);
  return HttpRespId;
}

int WebPg_GetOutUrlStrV(int WebPgId){
  PWebPg WebPg=State->GetWebPg(WebPgId);
  TUrlV OutUrlV; WebPg->GetOutUrlV(OutUrlV);
  TStrV UrlStrV(OutUrlV.Len(), 0);
  for (int UrlN=0; UrlN<OutUrlV.Len(); UrlN++){
    UrlStrV.Add(OutUrlV[UrlN]->GetUrlStr());}
  int UrlStrVId=State->AddStrV(UrlStrV);
  return UrlStrVId;
}

/////////////////////////////////////////////////
// Web-Crawler
int Crawler_Gen(){
  PCrawler Crawler=TCrawler::New();
  int CrawlerId=State->AddCrawler(Crawler);
  return CrawlerId;
}

void Crawler_Del(int CrawlerId){
  State->DelCrawler(CrawlerId);
}

void Crawler_AddStartUrlStr(int CrawlerId, char* StartUrlStr){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->AddStartUrlStr(StartUrlStr);
}

void Crawler_PutMxUrls(int CrawlerId, int MxUrls){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxUrls(MxUrls);
}

void Crawler_PutMxConns(int CrawlerId, int MxConns){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxConns(MxConns);
}

void Crawler_PutMnConns(int CrawlerId, int MnConns){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMnConns(MnConns);
}

void Crawler_PutMxConnsPerSrv(int CrawlerId, int MxConnsPerSrv){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxConnsPerSrv(MxConnsPerSrv);
}

void Crawler_PutAfterFetchDelay(int CrawlerId, int AfterFetchDelaySecs){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutAfterFetchDelaySecs(AfterFetchDelaySecs);
}

void Crawler_PutMxLev(int CrawlerId, int MxLev){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxLev(MxLev);
}

void Crawler_PutMxDep(int CrawlerId, int MxDep){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxDep(MxDep);
}

void Crawler_PutMnQLen(int CrawlerId, int MnQLen){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMnQLen(MnQLen);
}

void Crawler_PutQResetMod(int CrawlerId, int QResetMod){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutQResetMod(QResetMod);
}

void Crawler_PutMxContLen(int CrawlerId, int MxContLen){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxContLen(MxContLen);
}

void Crawler_PutMxRetries(int CrawlerId, int MxRetries){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxRetries(MxRetries);
}

void Crawler_PutMxQSegLen(int CrawlerId, int MxQSegLen){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutMxQSegLen(MxQSegLen);
}

void Crawler_PutRevisitSecs(int CrawlerId, int RevisitSecs){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutRevisitSecs(RevisitSecs);
}

void Crawler_PutRedirDmAllowed(int CrawlerId, bool RedirDmAllowedP){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->PutRedirDmAllowed(RedirDmAllowedP);
}

void Crawler_AddRqDmNm(int CrawlerId, char* RqDmNmV){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->AddRqDmNm(RqDmNmV);
}

void Crawler_AddRqContTypeNm(int CrawlerId, char* ContTypeNm){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->AddRqContTypeNm(ContTypeNm);
}

void Crawler_AddBadFExt(int CrawlerId, char* FExt){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->AddBadFExt(FExt);
}

void Crawler_OptHtmlCrawling(int CrawlerId){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->GetDef()->OptHtmlCrawling();
}

void Crawler_DefCrawlBs(int CrawlerId,
 char* CrawlBsNm, char* CrawlBsFPath, char* CrawlBsFAccessNm, int CrawlBsMxSegLen){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  Crawler->DefCrawlBs(CrawlBsNm, CrawlBsFPath, CrawlBsFAccessNm, CrawlBsMxSegLen);
}

void Crawler_StartCrawling(int CrawlerId){
  PCrawler Crawler=State->GetCrawler(CrawlerId);
  // start-crawling
  Crawler->StartCrawling();
  // message-loop
  TSysMsg::Loop();
  // stop-crawling
  Crawler->StopCrawling();
}

/////////////////////////////////////////////////
// DMoz-Base
int DMoz_GetCategories(
 int BowDocBsId, int BowDocWgtBsId, int BowDocPartId,
 char* QueryStr, int MxCats){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowSim BowSim=TBowSim::New(bstCos);
  // get query-document as bow-sparse-vector
  PBowSpV QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(QueryStr, BowDocWgtBs);
  // prepare category-vector
  TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV;
  TDMozBs::GetBestClustV(
   BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
  // prepare category-vector
  TFltStrPrV CatWgtNmPrV(WgtClustKdV.Len(), 0);
  for (int CatClustN=0; CatClustN<WgtClustKdV.Len(); CatClustN++){
    PBowDocPartClust Clust=WgtClustKdV[CatClustN].Dat;
    TStr CatNm=Clust->GetNm();
    double CatWgt=WgtClustKdV[CatClustN].Key;
    CatWgtNmPrV.Add(TFltStrPr(CatWgt, CatNm));
  }
  // store category-vector
  int CatWgtNmFSPrVId=State->AddFltStrPrV(CatWgtNmPrV);
  // return category-vector-id
  return CatWgtNmFSPrVId;
}

int DMoz_GetKeywords(
 int BowDocBsId, int BowDocWgtBsId, int BowDocPartId,
 char* QueryStr, int MxCats, double KWordTsh){
  PBowDocBs BowDocBs=State->GetBowDocBs(BowDocBsId);
  PBowDocWgtBs BowDocWgtBs=State->GetBowDocWgtBs(BowDocWgtBsId);
  PBowDocPart BowDocPart=State->GetBowDocPart(BowDocPartId);
  PBowSim BowSim=TBowSim::New(bstCos);
  // get query-document as bow-sparse-vector
  PBowSpV QueryBowSpV=BowDocBs->GetSpVFromHtmlStr(QueryStr, BowDocWgtBs);
  // prepare category-vector
  TFltBowDocPartClustKdV WgtClustKdV; TVec<TFltIntPrV> WgtWIdPrVV;
  TDMozBs::GetBestClustV(
   BowDocPart, BowSim, QueryBowSpV, MxCats, WgtClustKdV, WgtWIdPrVV);
  TStrFltPrV KWordStrWgtPrV;
  TDMozBs::GetBestKWordV(WgtClustKdV, KWordTsh, false, -1, -1, KWordStrWgtPrV);
  // prepare category-vector
  TFltStrPrV KWordWgtNmPrV;
  for (int KWordN=0; KWordN<KWordStrWgtPrV.Len(); KWordN++){
    TStr KWordStr=KWordStrWgtPrV[KWordN].Val1;
    double KWordWgt=KWordStrWgtPrV[KWordN].Val2;
    KWordWgtNmPrV.Add(TFltStrPr(KWordWgt, KWordStr));
  }
  // store category-vector
  int KWordWgtNmFSPrVId=State->AddFltStrPrV(KWordWgtNmPrV);
  // return category-vector-id
  return KWordWgtNmFSPrVId;
}

/////////////////////////////////////////////////
// Blob-Pointer
int BlobPt_New(){
  int BlobPtId=State->AddBlobPt(TBlobPt());
  return BlobPtId;
}

void BlobPt_Del(int BlobPtId){
  State->DelBlobPt(BlobPtId);
}

/////////////////////////////////////////////////
// Crawl-Base
int CrawlBs_Open(char* CrawlBsFNm){
  PCrawlBs CrawlBs=TMBlobBs::New(CrawlBsFNm);
  int CrawlBsId=State->AddBlobBs(CrawlBs);
  return CrawlBsId;
}

void CrawlBs_Close(int CrawlBsId){
  State->DelBlobBs(CrawlBsId);
}

int CrawlBs_FFirstBlobPt(int CrawlBsId){
  PCrawlBs CrawlBs=State->GetBlobBs(CrawlBsId);
  TBlobPt TrvBlobPt=CrawlBs->GetFirstBlobPt();
  int TrvBlobPtId=State->AddBlobPt(TrvBlobPt);
  return TrvBlobPtId;
}

bool CrawlBs_FNextBlobPt(int CrawlBsId, int TrvBlobPtId, int BlobPtId){
  PCrawlBs CrawlBs=State->GetBlobBs(CrawlBsId);
  TBlobPt& TrvBlobPt=State->GetBlobPt(TrvBlobPtId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PSIn SIn;
  return CrawlBs->FNextBlobPt(TrvBlobPt, BlobPt, SIn);
}

char* CrawlBs_GetDateTimeStr(int CrawlBsId, int BlobPtId){
  PCrawlBs CrawlBs=State->GetBlobBs(CrawlBsId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PSIn BlobSIn=CrawlBs->GetBlob(BlobPt);
  TStr DateTimeStr(*BlobSIn);
  TStr UrlStr(*BlobSIn);
  TStr Str=DateTimeStr;
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

char* CrawlBs_GetUrlStr(int CrawlBsId, int BlobPtId){
  PCrawlBs CrawlBs=State->GetBlobBs(CrawlBsId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PSIn BlobSIn=CrawlBs->GetBlob(BlobPt);
  TStr DateTimeStr(*BlobSIn);
  TStr UrlStr(*BlobSIn);
  TStr Str=UrlStr;
  char* CStr=CopyStrToCStr(Str);
  return CStr;
}

int CrawlBs_GetHttpResp(int CrawlBsId, int BlobPtId){
  PCrawlBs CrawlBs=State->GetBlobBs(CrawlBsId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PSIn BlobSIn=CrawlBs->GetBlob(BlobPt);
  TStr DateTimeStr(*BlobSIn);
  TStr UrlStr(*BlobSIn);
  TMem HttpRespMem(*BlobSIn);
  PSIn HttpRespSIn=HttpRespMem.GetSIn();
  PHttpResp HttpResp=THttpResp::New(HttpRespSIn);
  int HttpRespId=State->AddHttpResp(HttpResp);
  return HttpRespId;
}

/////////////////////////////////////////////////
// Blob-Base
int BlobBs_Open(char* BlobBsFNm, int BlobBsFAccess){
  PBlobBs BlobBs=TGBlobBs::New(BlobBsFNm, TFAccess(BlobBsFAccess));
  int BlobBsId=State->AddBlobBs(BlobBs);
  return BlobBsId;
}

void BlobBs_Close(int BlobBsId){
  State->DelBlobBs(BlobBsId);
}

int BlobBs_GetFAccessCreate(){return faCreate;}
int BlobBs_GetFAccessUpdate(){return faUpdate;}
int BlobBs_GetFAccessReadOnly(){return faRdOnly;}

int BlobBs_FFirstBlobPt(int BlobBsId){
  PBlobBs BlobBs=State->GetBlobBs(BlobBsId);
  TBlobPt TrvBlobPt=BlobBs->GetFirstBlobPt();
  int TrvBlobPtId=State->AddBlobPt(TrvBlobPt);
  return TrvBlobPtId;
}

bool BlobBs_FNextBlobPt(int BlobBsId, int TrvBlobPtId, int BlobPtId){
  PBlobBs BlobBs=State->GetBlobBs(BlobBsId);
  TBlobPt& TrvBlobPt=State->GetBlobPt(TrvBlobPtId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PSIn SIn;
  return BlobBs->FNextBlobPt(TrvBlobPt, BlobPt, SIn);
}

void BlobBs_AddBlob(int BlobBsId, int MemId, int BlobPtId){
  PBlobBs BlobBs=State->GetBlobBs(BlobBsId);
  PMem Mem=State->GetMem(MemId);
  PSIn SIn=Mem->GetSIn();
  TBlobPt BlobPt=BlobBs->PutBlob(SIn);
  State->GetBlobPt(BlobPtId)=BlobPt;
}

void BlobBs_PutBlob(int BlobBsId, int MemId, int BlobPtId){
  PBlobBs BlobBs=State->GetBlobBs(BlobBsId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PMem Mem=State->GetMem(MemId);
  PSIn SIn=Mem->GetSIn();
  BlobBs->PutBlob(BlobPt, SIn);
}

void BlobBs_GetBlob(int BlobBsId, int BlobPtId, int MemId){
  PBlobBs BlobBs=State->GetBlobBs(BlobBsId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  PSIn BlobSIn=BlobBs->GetBlob(BlobPt);
  PMem Mem=State->GetMem(MemId);
  TMem::LoadMem(BlobSIn, Mem);
}

void BlobBs_DelBlob(int BlobBsId, int BlobPtId){
  PBlobBs BlobBs=State->GetBlobBs(BlobBsId);
  TBlobPt& BlobPt=State->GetBlobPt(BlobPtId);
  BlobBs->DelBlob(BlobPt);
}

/////////////////////////////////////////////////
// Compact-Document
int CpDoc_Load(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  PCpDoc CpDoc=TCpDoc::Load(*SIn);
  int CpDocId=State->AddCpDoc(CpDoc);
  return CpDocId;
}

void CpDoc_Save(int CpDocId, int SOutId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  PSOut SOut=State->GetSOut(SOutId);
  CpDoc->Save(*SOut);
}

int CpDoc_New(){
  int CpDocId=State->AddCpDoc(PCpDoc::New());
  return CpDocId;
}

void CpDoc_Del(int CpDocId){
  State->DelCpDoc(CpDocId);
}

void CpDoc_FFirstCpd(int SInId){
  PSIn SIn=State->GetSIn(SInId);
  TCpDoc::FFirstCpd(SIn);
}

bool CpDoc_FFNextCpd(int SInId, int CpDocId){
  PSIn SIn=State->GetSIn(SInId);
  PCpDoc CpDoc;
  bool FNextOk=TCpDoc::FNextCpd(SIn, CpDoc);
  State->GetCpDoc(CpDocId)=NULL;
  if (FNextOk){
    State->GetCpDoc(CpDocId)=CpDoc;}
  return FNextOk;
}

void CpDoc_PutDocNm(int CpDocId, char* DocNm){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->PutDocNm(DocNm);
}

char* CpDoc_GetDocNm(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetDocNm());
}

void CpDoc_PutDateStr(int CpDocId, char* DateStr){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->PutDateStr(DateStr);
}

char* CpDoc_GetDateStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetDateStr());
}

void CpDoc_AddCatNm(int CpDocId, char* CatNm){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->AddCatNm(CatNm);
}

int CpDoc_GetCats(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CpDoc->GetCats();
}

char* CpDoc_GetCatNm(int CpDocId, int CatN){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetCatNm(CatN));
}

char* CpDoc_GetTxtStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  TStr TxtStr=CpDoc->GetTxtStr();
  return CopyStrToCStr(TxtStr);
}

char* CpDoc_GetHtmlStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  TStr HtmlStr=CpDoc->GetHtmlStr();
  return CopyStrToCStr(HtmlStr);
}

void CpDoc_PutTitleStr(int CpDocId, char* TitleStr){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->PutTitleStr(TitleStr);
}

char* CpDoc_GetTitleStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetTitleStr());
}

void CpDoc_PutHeadlineStr(int CpDocId, char* HeadlineStr){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->PutHeadlineStr(HeadlineStr);
}

char* CpDoc_GetHeadlineStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetHeadlineStr());
}

void CpDoc_PutBylineStr(int CpDocId, char* BylineStr){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->PutBylineStr(BylineStr);
}

char* CpDoc_GetBylineStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetBylineStr());
}

void CpDoc_PutDatelineStr(int CpDocId, char* DatelineStr){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->PutDatelineStr(DatelineStr);
}

char* CpDoc_GetDatelineStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetDatelineStr());
}

void CpDoc_AddParStr(int CpDocId, char* ParStr){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->AddParStr(ParStr);
}

int CpDoc_GetPars(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CpDoc->GetPars();
}

char* CpDoc_GetParStr(int CpDocId, int ParN){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetParStr(ParN));
}

char* CpDoc_GetAllParStr(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetAllParStr());
}

void CpDoc_AddTopCdNm(int CpDocId, char* TopCdNm){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->AddTopCdNm(TopCdNm);
}

int CpDoc_GetTopCds(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CpDoc->GetTopCds();
}

char* CpDoc_GetTopCdNm(int CpDocId, int TopCdN){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetTopCdNm(TopCdN));
}

void CpDoc_AddGeoCdNm(int CpDocId, char* GeoCdNm){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->AddGeoCdNm(GeoCdNm);
}

int CpDoc_GetGeoCds(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CpDoc->GetGeoCds();
}

char* CpDoc_GetGeoCdNm(int CpDocId, int GeoCdN){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetGeoCdNm(GeoCdN));
}

void CpDoc_AddIndCdNm(int CpDocId, char* IndCdNm){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  CpDoc->AddIndCdNm(IndCdNm);
}

int CpDoc_GetIndCds(int CpDocId){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CpDoc->GetIndCds();
}

char* CpDoc_GetIndCdNm(int CpDocId, int IndCdN){
  PCpDoc CpDoc=State->GetCpDoc(CpDocId);
  return CopyStrToCStr(CpDoc->GetIndCdNm(IndCdN));
}

/////////////////////////////////////////////////
// OdbcDb
int OdbcDb_New(){
  POdbcDb OdbcDb=TOdbcDb::New();
  int OdbcDbId=State->AddOdbcDb(OdbcDb);
  return OdbcDbId;
}

void OdbcDb_Del(int OdbcDbId){
  State->DelOdbcDb(OdbcDbId);
}

int OdbcDb_GetDataSourceNmV(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  TStrV DataSourceNmV; OdbcDb->GetDataSourceNmV(DataSourceNmV);
  return State->AddStrV(DataSourceNmV);
}

int OdbcDb_GetTbNmV(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  TStrV TbNmV; OdbcDb->GetTbNmV(TbNmV);
  return State->AddStrV(TbNmV);
}

int OdbcDb_GetColNmV(int OdbcDbId, char* TbNm){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  TStrV ColNmV; OdbcDb->GetColNmV(TbNm, ColNmV);
  return State->AddStrV(ColNmV);
}

bool OdbcDb_Connect(int OdbcDbId, char* SrvNm, char* UsrNm, char* PwdStr){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  return OdbcDb->Connect(SrvNm, UsrNm, PwdStr);
}

void OdbcDb_Disconnect(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  OdbcDb->Disconnect();
}

bool OdbcDb_IsConnected(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  return OdbcDb->IsConnected();
}

bool OdbcDb_IsOk(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  return OdbcDb->IsOk();
}

char* OdbcDb_GetMsgStr(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  char* MsgCStr=CopyStrToCStr(OdbcDb->GetMsgStr());
  return MsgCStr;
}

/////////////////////////////////////////////////
// Odbc-Query
int OdbcQuery_New(int OdbcDbId){
  POdbcDb OdbcDb=State->GetOdbcDb(OdbcDbId);
  POdbcQuery OdbcQuery=TOdbcQuery::New(OdbcDb);
  int OdbcQueryId=State->AddOdbcQuery(OdbcQuery);
  return OdbcQueryId;
}

void OdbcQuery_Del(int OdbcQueryId){
  State->DelOdbcQuery(OdbcQueryId);
}

bool OdbcQuery_ExeSql(int OdbcQueryId, char* SqlStr, int ParamStrVId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  if (ParamStrVId==-1){
    return OdbcQuery->ExeSql(SqlStr);
  } else {
    TStrV& ParamStrV=State->GetStrV(ParamStrVId);
    return OdbcQuery->ExeSql(SqlStr, ParamStrV);
  }
}

bool OdbcQuery_ExeSqlP1(int OdbcQueryId,
 char* SqlStr, char* ParamStr){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  TStrV ParamStrV; ParamStrV.Add(ParamStr);
  return OdbcQuery->ExeSql(SqlStr, ParamStrV);
}

bool OdbcQuery_ExeSqlP2(int OdbcQueryId,
 char* SqlStr, char* ParamStr1, char* ParamStr2){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  TStrV ParamStrV; ParamStrV.Add(ParamStr1); ParamStrV.Add(ParamStr2);
  return OdbcQuery->ExeSql(SqlStr, ParamStrV);
}

bool OdbcQuery_ExeSqlP3(int OdbcQueryId,
 char* SqlStr, char* ParamStr1, char* ParamStr2, char* ParamStr3){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  TStrV ParamStrV; ParamStrV.Add(ParamStr1);
  ParamStrV.Add(ParamStr2); ParamStrV.Add(ParamStr3);
  return OdbcQuery->ExeSql(SqlStr, ParamStrV);
}

bool OdbcQuery_IsResultSet(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  return OdbcQuery->IsResultSet();
}

int OdbcQuery_GetCols(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  return OdbcQuery->GetCols();
}

int OdbcQuery_GetRowsAffected(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  return OdbcQuery->GetRowsAffected();
}

char* OdbcQuery_GetColNm(int OdbcQueryId, int ColN){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  TStr ColNm=OdbcQuery->GetColNm(ColN);
  char* ColCNm=CopyStrToCStr(ColNm);
  return ColCNm;
}

bool OdbcQuery_NextRow(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  return OdbcQuery->NextRow();
}

char* OdbcQuery_GetColVal(int OdbcQueryId, int ColN, int MxValStrLen){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  TStr ValStr=OdbcQuery->GetColVal(ColN, MxValStrLen);
  char* ValCStr=CopyStrToCStr(ValStr);
  return ValCStr;
}

bool OdbcQuery_IsOk(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  return OdbcQuery->IsOk();
}

bool OdbcQuery_IsOpOk(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  return OdbcQuery->IsOpOk();
}

char* OdbcQuery_GetMsgStr(int OdbcQueryId){
  POdbcQuery OdbcQuery=State->GetOdbcQuery(OdbcQueryId);
  char* MsgCStr=CopyStrToCStr(OdbcQuery->GetMsgStr());
  return MsgCStr;
}
