#include "mine.h"

/*
/////////////////////////////////////////////////
// Stream-NGram-Hash-Table-Key-Data
typedef TMd5Sig TSNGHashKey;
typedef TUInt TSNGHashDat;

#pragma pack(push, 1) // pack class size
class TStreamNGramHashKeyDat{
public:
  TUInt TimePrev, TimeNext;
  TUInt Next;
  TUInt HashCd;
  //TMd5Sig Key;
  TSNGHashDat Dat;
public:
  TStreamNGramHashKeyDat():
    TimePrev(0), TimeNext(0), Next(0), HashCd(0), Dat(){}
  TStreamNGramHashKeyDat(
   const uint& _TimePrev, const uint& _TimeNext, const uint& _Next, const uint& _HashCd):
    TimePrev(_TimePrev), TimeNext(_TimeNext), Next(_Next), HashCd(_HashCd), Dat(){}
  explicit TStreamNGramHashKeyDat(TSIn& SIn):
    TimePrev(SIn), TimeNext(SIn), Next(SIn), HashCd(SIn), Dat(SIn){}
  void Load(TSIn& SIn){
    TimePrev.Load(SIn); TimeNext.Load(SIn); Next.Load(SIn); 
    HashCd.Load(SIn); Dat.Load(SIn);}
  void Save(TSOut& SOut) const {
    TimePrev.Save(SOut); TimeNext.Save(SOut); Next.Save(SOut); 
    HashCd.Save(SOut); Dat.Save(SOut);}

  bool operator==(const TStreamNGramHashKeyDat& KeyDat) const {
    return (this==&KeyDat)||(HashCd==KeyDat.HashCd);}
  TStreamNGramHashKeyDat& operator=(const TStreamNGramHashKeyDat& KeyDat){
    if (this!=&KeyDat){
      TimePrev=KeyDat.TimePrev; TimeNext=KeyDat.TimeNext; Next=KeyDat.Next; 
      HashCd=KeyDat.HashCd; Dat=KeyDat.Dat;}
    return *this;}
};
#pragma pack(pop)

/////////////////////////////////////////////////
// Stream-NGram-Hash-Table
ClassTP(TStreamNGramHash, PStreamNGramHash)//{
private:
  TUIntV PortV;
  TVec<TStreamNGramHashKeyDat> KeyDatV;
  TUInt TimeFirst, TimeLast;
  UndefCopyAssign(TStreamNGramHash);
private:
  TStreamNGramHashKeyDat& GetHashKeyDat(const uint& KeyId){return KeyDatV[KeyId];}
public:
  TStreamNGramHash(const uint& MxKeys):
    PortV(), KeyDatV(), TimeFirst(), TimeLast(){Gen(MxKeys);}
  static PStreamNGramHash New(const uint& MxKeys){
    return PStreamNGramHash(new TStreamNGramHash(MxKeys));}
  TStreamNGramHash(TSIn& SIn):
    PortV(SIn), KeyDatV(SIn), TimeFirst(SIn), TimeLast(SIn){SIn.LoadCs();}
  void Load(TSIn& SIn){
    PortV.Load(SIn); KeyDatV.Load(SIn); 
    TimeFirst.Load(SIn); TimeLast.Load(SIn); SIn.LoadCs();}
  void Save(TSOut& SOut) const {
    PortV.Save(SOut); KeyDatV.Save(SOut); 
    TimeFirst.Save(SOut); TimeLast.Save(SOut); SOut.SaveCs();}

  TSNGHashDat& operator[](const uint& KeyId){return GetHashKeyDat(KeyId).Dat;}
  ::TSize GetMemUsed() const {Fail; return 0;} // 

  void Gen(const uint& MxKeys){
    // get number of ports
    uint PortsAsPow2=0; uint _MxKeys=MxKeys; 
    while (_MxKeys!=0){_MxKeys=_MxKeys/2; PortsAsPow2++;}
    uint Ports=(uint(1) << (PortsAsPow2-1));
    // create ports & keydata
    PortV.Gen(Ports); KeyDatV.Gen(MxKeys, 0);
    TimeFirst=0; TimeLast=0;  
    KeyDatV.Add(TStreamNGramHashKeyDat()); // zeroth element is guard
  }

  void Clr(){
    PortV.PutAll(0); KeyDatV.Clr(false); 
    TimeFirst=0; TimeLast=0; 
    KeyDatV.Add(TStreamNGramHashKeyDat());}
  bool Empty() const {return Len()==0;}
  uint Len() const {return KeyDatV.Len();}
  uint GetPorts() const {return PortV.Len();}
  uint GetMxKeys() const {return KeyDatV.Reserved();}
  
  uint AddKey(const TSNGHashKey& Key);
  TSNGHashDat& AddDat(const TSNGHashKey& Key){
    return GetHashKeyDat(AddKey(Key)).Dat;}
  TSNGHashDat& AddDat(const TSNGHashKey& Key, const TSNGHashDat& Dat){
    return GetHashKeyDat(AddKey(Key)).Dat=Dat;}
};

/////////////////////////////////////////////////
// Stream-NGram-Hash-Table
uint TStreamNGramHash::AddKey(const TSNGHashKey& Key){
  uint PrimHashCd; Key.GetUInt(0, PrimHashCd);
  uint SecHashCd; Key.GetUInt(4, SecHashCd);
  const uint PortN=PrimHashCd%PortV.Len();
  const TUInt HashCd=SecHashCd;
  uint PrevKeyId=0;
  uint KeyId=PortV[PortN];
  while ((KeyId!=0)&&(KeyDatV[KeyId].HashCd!=HashCd)){
    PrevKeyId=KeyId; KeyId=KeyDatV[KeyId].Next;}

  //if (KeyId!=0){
  //  if ((KeyDatV[KeyId].HashCd==HashCd)&&!(KeyDatV[KeyId].Key==Key)){
  //    printf("[%d]", KeyId);
  //  }
  //}

  if (KeyId==0){
    if (KeyDatV.Len()<KeyDatV.Reserved()){
      KeyId=KeyDatV.Add(TStreamNGramHashKeyDat(0, TimeFirst, 0, HashCd));
      //KeyDatV[KeyId].Key=Key;
      TimeFirst=KeyId; if (TimeLast==0){TimeLast=KeyId;}
    } else {
      KeyId=TimeLast;
      TimeLast=KeyDatV[KeyId].TimePrev; KeyDatV[TimeLast].TimeNext=0;
      KeyDatV[KeyId]=TStreamNGramHashKeyDat(0, TimeFirst, 0, HashCd);
      //KeyDatV[KeyId].Key=Key;
      KeyDatV[TimeFirst].TimePrev=KeyId; TimeFirst=KeyId;
    }
    if (PrevKeyId==0){
      PortV[PortN]=KeyId;
    } else {
      KeyDatV[PrevKeyId].Next=KeyId;
    }
  }
  return KeyId;
}

/////////////////////////////////////////////////
// NGram-Descriptor
ClassTPV(TNGramDesc, PNGramDesc, TNGramDescV)//{
public:
  TMd5Sig Sig;
  TInt Fq;
  TInt Pos;
  TIntV TokIdV;
  TStrV TokStrV;
  TStr Str;
public:
  TNGramDesc(){}
  static PNGramDesc New(){
    return PNGramDesc(new TNGramDesc());}
  TNGramDesc(const TNGramDesc& NGramDesc): 
    Sig(NGramDesc.Sig), Fq(NGramDesc.Fq), Pos(NGramDesc.Pos), 
    TokIdV(NGramDesc.TokIdV), TokStrV(NGramDesc.TokStrV), Str(NGramDesc.Str){}
  TNGramDesc(TSIn& SIn){Fail;}
  void Save(TSOut& SOut) const {Fail;}

  bool operator==(const TNGramDesc& NGramDesc) const {return Sig==NGramDesc.Sig;}
  bool operator<(const TNGramDesc& NGramDesc) const {return Sig<NGramDesc.Sig;}
  int GetPrimHashCd() const {return Sig.GetPrimHashCd();}
  int GetSecHashCd() const {return Sig.GetSecHashCd();}
};

/////////////////////////////////////////////////
// Stream-NGram-Base
ClassTP(TStreamNGramBs, PStreamNGramBs)//{
private:
  TInt MxNGramLen;
  TStrH TokStrH;
  TStreamNGramHash StreamNGramHash;
  UndefCopyAssign(TStreamNGramBs);
private:
  TIntQV TokIdQV;
public:
  TStreamNGramBs(const int& _MxNGramLen, const int& MxCachedNGrams):
    MxNGramLen(_MxNGramLen), 
    TokStrH(), StreamNGramHash(MxCachedNGrams),
    TokIdQV(_MxNGramLen){
    IAssert(MxNGramLen>=1); TokStrH.AddKey("");}
  static PStreamNGramBs New(const int& MxNGramLen, const int& MxCachedNGrams){
    return PStreamNGramBs(new TStreamNGramBs(MxNGramLen, MxCachedNGrams));}
  TStreamNGramBs(TSIn& SIn):
    MxNGramLen(SIn), TokStrH(SIn), StreamNGramHash(SIn){}
  static PStreamNGramBs Load(TSIn& SIn){return new TStreamNGramBs(SIn);}
  void Save(TSOut& SOut){
    MxNGramLen.Save(SOut); TokStrH.Save(SOut); StreamNGramHash.Save(SOut);}

  bool IsTokStr() const {return TokStrH.Len()>1;}
  TStr GetTokStr(const int& TokId) const {
    return TokStrH.GetKey(TokId);}

  void AddTokId(const int& TokId, const int& TokPos, const bool& OutputNGramsP, TNGramDescV& OutputNGramDescV);
  void AddTokIdV(const TIntV& TokIdV, const int& FirstTokPos, const bool& OutputNGramsP, TNGramDescV& OutputNGramDescV);
  void AddTokStr(const TStr& TokStr, const int& TokPos, const bool& OutputNGramsP, TNGramDescV& OutputNGramDescV);
  void BreakTokStream();

  void AddDocTokIdV(const TIntV& DocTokIdV, TNGramDescV& OutputNGramDescV);
  void AddDocHtmlStr(const TStr& DocHtmlStr, TNGramDescV& OutputNGramDescV); 
};

/////////////////////////////////////////////////
// Stream-NGram-Base
void TStreamNGramBs::BreakTokStream(){
  int TokIdQVLen=TokIdQV.Len();
  for (int TokIdQN=0; TokIdQN<TokIdQVLen; TokIdQN++){
    TokIdQV[TokIdQN].Clr(false);
  }
}

void TStreamNGramBs::AddTokId(
 const int& TokId, const int& TokPos,
 const bool& OutputNGramsP, TNGramDescV& OutputNGramDescV){
  if (TokId==0){BreakTokStream(); return;}
  // shortcuts
  int TokIdQVLen=TokIdQV.Len();
  TMem NGramMem(MxNGramLen*sizeof(int));
  // traverse token-queues
  for (int TokIdQN=0; TokIdQN<TokIdQVLen; TokIdQN++){
    int NGramLen=1+TokIdQN; // TokIdQV[0]==Uniram
    TIntQ& TokIdQ=TokIdQV[TokIdQN];
    if (TokIdQ.Len()==NGramLen){TokIdQ.Pop();}
    TokIdQ.Push(TokId);
    // if queue is ready 
    if (TokIdQ.Len()==NGramLen){
      // construct memory-footprint for ngram
      NGramMem.Clr(false);
      for (int TokIdN=0; TokIdN<NGramLen; TokIdN++){
        int TokId=TokIdQ[TokIdN];
        NGramMem.AddBf(&TokId, sizeof(TokId));
      }
      // create md5-signature for ngram
      TMd5Sig NGramSig(NGramMem);
      // increment ngram-frequency
      int Fq=StreamNGramHash.AddDat(NGramSig)++;
      // create output-ngram-descriptor
      if (OutputNGramsP){
        PNGramDesc NGramDesc=TNGramDesc::New();
        NGramDesc->Sig=NGramSig;
        NGramDesc->Fq=Fq;
        NGramDesc->Pos=TokPos;
        TChA NGramChA;
        for (int TokIdN=0; TokIdN<NGramLen; TokIdN++){
          int TokId=TokIdQ[TokIdN];
          NGramDesc->TokIdV.Add(TokId);
          if (IsTokStr()){
            TStr TokStr=GetTokStr(TokId);
            NGramDesc->TokStrV.Add(TokStr);
            if (TokIdN>0){NGramChA+=' ';}
            NGramChA+=TokStr;
          }
        }
        if (IsTokStr()){
          NGramDesc->Str=NGramChA;}
        OutputNGramDescV.Add(NGramDesc);
      }
    }
  }
}

void TStreamNGramBs::AddTokIdV(
 const TIntV& TokIdV, const int& FirstTokPos,
 const bool& OutputNGramsP, TNGramDescV& OutputNGramDescV){
  for (int TokIdN=0; TokIdN<TokIdV.Len(); TokIdN++){
    AddTokId(TokIdV[TokIdN], FirstTokPos+TokIdN, OutputNGramsP, OutputNGramDescV);
  }
}

void TStreamNGramBs::AddTokStr(
 const TStr& TokStr, const int& TokPos,
 const bool& OutputNGramsP, TNGramDescV& OutputNGramDescV){
  int TokId=TokStrH.AddKey(TokStr);
  //TMd5Sig TokSig(TokStr);
  //uint TokId; TokSig.GetUInt(0, TokId);
  AddTokId(TokId, TokPos, OutputNGramsP, OutputNGramDescV);
}

void TStreamNGramBs::AddDocTokIdV(
 const TIntV& DocTokIdV, TNGramDescV& OutputNGramDescV){
  BreakTokStream(); OutputNGramDescV.Clr();
  AddTokIdV(DocTokIdV, 0, true, OutputNGramDescV);
}

void TStreamNGramBs::AddDocHtmlStr(
 const TStr& DocHtmlStr, TNGramDescV& OutputNGramDescV){
  BreakTokStream(); OutputNGramDescV.Clr();
  // prepare html parsing
  PSIn HtmlSIn=TStrIn::New(DocHtmlStr);
  PHtmlDoc HtmlDoc=THtmlDoc::New(HtmlSIn, hdtAll, true);
  PHtmlTok Tok; THtmlLxSym TokSym; TStr TokStr;
  bool InScript=false;
  // traverse html tokens
  for (int TokN=0; TokN<HtmlDoc->GetToks(); TokN++){
    PHtmlTok Tok=HtmlDoc->GetTok(TokN);
    HtmlDoc->GetTok(TokN, TokSym, TokStr);
    switch (TokSym){
      case hsyUndef: break;
      case hsySSym:
      case hsyStr:
      case hsyNum:
        if (InScript){break;}
        // printf("."); //printf("[%s] ", TokStr.CStr());
        AddTokStr(TokStr, TokN, true, OutputNGramDescV);
        break;
      case hsyBTag:
      case hsyETag:
        if (TokStr=="<SCRIPT>"){
          InScript=(TokSym==hsyBTag); BreakTokStream();}
        break;
      case hsyEof: break;
      default: break;
    }
  }
}*/

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Text to Stream-NGrams", 0);
  TStr InCpdFNm=Env.GetIfArgPrefixStr("-icpd:", "E:/Data/Reuters2K/R2Kx.Cpd", "Input-CompactDocs-File");
  int MxNGramLen=Env.GetIfArgPrefixInt("-mxngl:", 10, "Max-NGram-Lenghts");
  if (Env.IsEndOfRun()){return 0;}

  // create stream-ngram-base
  PStreamNGramBs StreamNGramBs=TStreamNGramBs::New(MxNGramLen, 10000000);

  printf("Processing file '%s' ...\n", InCpdFNm.CStr());
  PSIn CpdSIn=TCpDoc::FFirstCpd(InCpdFNm); PCpDoc CpDoc; int CpDocN=0;
  while (TCpDoc::FNextCpd(CpdSIn, CpDoc)){
    printf("%d\r", ++CpDocN);
    if (CpDocN==10000){break;}
    TNGramDescV NGramDescV;
    StreamNGramBs->AddDocHtmlStr(CpDoc->GetHtmlStr(), NGramDescV);
    if (CpDocN>1000){
      for (int NGramN=0; NGramN<NGramDescV.Len(); NGramN++){
        if (NGramDescV[NGramN]->Fq>5){
          printf("['%s':%d]", NGramDescV[NGramN]->Str.CStr(), NGramDescV[NGramN]->Fq);}
      }
      printf("\n");
      break;
    }
  }
  printf("\nDone.\n");

  return 0;
  Catch;
  return 1;
}