#include "medline.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Get Web-Page");
  bool ContinueP=Env.GetIfArgPrefixBool("-cont:", false, "Continue-Fetch");
  int StartDocId=Env.GetIfArgPrefixInt("-startdocid:", 1, "Start-DocumentId");
  int StartMDocId=Env.GetIfArgPrefixInt("-mdid:", -1, "Start-Mega-DocumentId");
  int Docs=Env.GetIfArgPrefixInt("-docs:", 12500000, "FetchDocuments");
  int DocSetLen=Env.GetIfArgPrefixInt("-docsetlen:", 100, "Document-Set-Length");
  int WaitSecs=Env.GetIfArgPrefixInt("-waitsecs:", 1, "Wait-Seconds");
  TStr OutFPath=Env.GetIfArgPrefixStr("-o:", ".", "Output-File-Path");
  if (Env.IsEndOfRun()){return 0;}

  // adapt setting if mega-request
  if (StartMDocId!=-1){
    StartDocId=StartMDocId*1000000+1; Docs=1000000;
  }
  // get data to continue fecting
  if (ContinueP){
    StartDocId=TMedlineWebFetch::GetNextStartDocId(OutFPath);
  }

  // go-fetch
  TMedlineWebFetch::Go(StartDocId, Docs, DocSetLen, WaitSecs, OutFPath);

  return 0;
  Catch;
  return 1;
}                                  

