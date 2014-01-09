#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Text To Text-Base");
  TStr InCpdFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Cpd-FileName");
  TStr OutTBsFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-TextBase-FileName");
  int MxDocs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents");
  bool IndexP=Env.GetIfArgPrefixBool("-index:", false, "Create-Index");
  bool MemStatP=Env.GetIfArgPrefixBool("-memstat:", false, "Memory-Statistics");
  int CacheSizeMb=Env.GetIfArgPrefixInt("-cache:", 100, "Cache-Size-in-MB");
  if (Env.IsEndOfRun()){return 0;}

  // create text-base
  TStr TxtBsNm=OutTBsFNm.GetFBase();
  TStr TxtBsFPath=OutTBsFNm.GetFPath();
  PTxtBs TxtBs=TTxtBs::New(TxtBsNm, TxtBsFPath, faCreate, faUndef, CacheSizeMb * 1000000);

  // traverse cpd file
  TSecTm StartTm=TSecTm::GetCurTm();
  PSIn CpdSIn=TCpDoc::GetFirstCpd(InCpdFNm); PCpDoc CpDoc; int CpDocs=0;
  while (TCpDoc::GetNextCpd(CpdSIn, CpDoc)){
    CpDocs++; if (CpDocs%100==0){printf("%d\r", CpDocs);}
    if ((MxDocs!=-1)&&(CpDocs>=MxDocs)){break;}
    // get document-id & text
    TStr DocId=CpDoc->GetDocId();
    TStr HtmlStr=CpDoc->GetHtmlStr();
    // index text
    TxtBs->AddDocMem(DocId, TMem(HtmlStr), IndexP);
    // statistics
    if (CpDocs%100==0){
      int MemUsed=TxtBs->GetMemUsed();
      int SecsSf=TSecTm::GetDSecs(StartTm, TSecTm::GetCurTm());
      if (MemStatP){
        printf("%d docs / %d secs: MemUsed:%s [%s]\n", CpDocs, SecsSf,
         TInt::GetMegaStr(MemUsed).CStr(), TxtBs->GetMemUsedStr().CStr());
      } else {
        printf("%d docs / %d secs\n", CpDocs, SecsSf);
      }
    }
  }
  return 0;
  Catch;
  return 1;
}

