#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Graph To Bag-Of-Words", -1);
  TStr InBowFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Bow-FileName");
  TStr OutWordsTabFNm=Env.GetIfArgPrefixStr("-ow:", "Words.Tab", "Output-Words-Table-FileName");
  TStr OutCatsTabFNm=Env.GetIfArgPrefixStr("-oc:", "Cats.Tab", "Output-Cats-Table-FileName");
  TStr OutDocWordsTabFNm=Env.GetIfArgPrefixStr("-odw:", "DocWords.Tab", "Output-DocumentWords-Table-FileName");
  TStr OutDocCatsTabFNm=Env.GetIfArgPrefixStr("-odw:", "DocCats.Tab", "Output-DocumentCats-Table-FileName");
  if (Env.IsEndOfRun()){return 0;}

  // load graph data
  if (InBowFNm.Empty()){TExcept::Throw("No Input Graph File!");}
  printf("Load Bag-Of-Words from File '%s' ... ", InBowFNm.CStr());
  PBowDocBs BowDocBs=TBowDocBs::LoadBin(InBowFNm);
  printf("Done.\n");

  // save words table
  if (!OutWordsTabFNm.Empty()){
    printf("Save Words to '%s' ...\n", OutWordsTabFNm.CStr());
    TFOut SOut(OutWordsTabFNm); FILE* fOut=SOut.GetFileId();
    int Words=BowDocBs->GetWords();
    for (int WId=0; WId<Words; WId++){
      if (WId%100==0){printf("%d/%d\r", 1+WId, Words);}
      TStr WordStr=BowDocBs->GetWordStr(WId);
      int Fq=BowDocBs->GetWordFq(WId);
      fprintf(fOut, "%d,\"%s\",%d\r\n", WId, WordStr.CStr(), Fq);
    }
    printf("%d/%d\n", Words, Words);
    printf("Done.\n");
  }

  // save categories table
  if (!OutCatsTabFNm.Empty()){
    printf("Save Categories to '%s' ...\n", OutCatsTabFNm.CStr());
    TFOut SOut(OutCatsTabFNm); FILE* fOut=SOut.GetFileId();
    int Cats=BowDocBs->GetCats();
    for (int CId=0; CId<Cats; CId++){
      if (CId%100==0){printf("%d/%d\r", 1+CId, Cats);}
      TStr CatNm=BowDocBs->GetCatNm(CId);
      int Fq=BowDocBs->GetCatFq(CId);
      fprintf(fOut, "%d,\"%s\",%d\r\n", CId, CatNm.CStr(), Fq);
    }
    printf("%d/%d\n", Cats, Cats);
    printf("Done.\n");
  }

  // save document-words table
  if (!OutDocWordsTabFNm.Empty()){
    printf("Save Documents to '%s' ...\n", OutDocWordsTabFNm.CStr());
    TFOut SOut(OutDocWordsTabFNm); FILE* fOut=SOut.GetFileId();
    int Docs=BowDocBs->GetDocs();
    for (int DId=0; DId<Docs; DId++){
      if (DId%100==0){printf("%d/%d\r", 1+DId, Docs);}
      TStr DocNm=BowDocBs->GetDocNm(DId);
      int DocWIds=BowDocBs->GetDocWIds(DId);
      for (int DocWIdN=0; DocWIdN<DocWIds; DocWIdN++){
        int WId; double WordFq;
        BowDocBs->GetDocWIdFq(DId, DocWIdN, WId, WordFq);
        fprintf(fOut, "%s,%d,%g\r\n", DocNm.CStr(), WId, WordFq);
      }
    }
    printf("%d/%d\n", Docs, Docs);
    printf("Done.\n");
  }

  // save document-categories table
  if (!OutDocCatsTabFNm.Empty()){
    printf("Save Documents to '%s' ...\n", OutDocCatsTabFNm.CStr());
    TFOut SOut(OutDocCatsTabFNm); FILE* fOut=SOut.GetFileId();
    int Docs=BowDocBs->GetDocs();
    for (int DId=0; DId<Docs; DId++){
      if (DId%100==0){printf("%d/%d\r", 1+DId, Docs);}
      TStr DocNm=BowDocBs->GetDocNm(DId);
      int DocCIds=BowDocBs->GetDocCIds(DId);
      for (int DocCIdN=0; DocCIdN<DocCIds; DocCIdN++){
        int CId=BowDocBs->GetDocCId(DId, DocCIdN);
        fprintf(fOut, "%s,%d\r\n", DocNm.CStr(), CId);
      }
    }
    printf("%d/%d\n", Docs, Docs);
    printf("Done.\n");
  }

  return 0;
  Catch;
  return 1;
}
