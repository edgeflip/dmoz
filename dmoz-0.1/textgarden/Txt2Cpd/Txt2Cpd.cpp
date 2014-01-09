#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Text To Compact-Documents");
  TStr InHtmlFPath=Env.GetIfArgPrefixStr("-ihtml:", "", "Input-Html-Path");
  TStr InTBsFNm=Env.GetIfArgPrefixStr("-itbs:", "", "Input-TextBase-File");
  TStr InLnDocFNm=Env.GetIfArgPrefixStr("-ilndoc:", "", "Input-LineDocuments-File");
  TStr InNmLnDocFNm=Env.GetIfArgPrefixStr("-inlndoc:", "", "Input-Named-LineDocuments-File");
  TStr InReuters2000FPath=Env.GetIfArgPrefixStr("-ir2000:", "", "Input-Reuters2000-Path");
  TStr InReuters21578FPath=Env.GetIfArgPrefixStr("-ir21578:", "", "Input-Reuters21578-Path");
  TStr InAcmTechNewsFPath=Env.GetIfArgPrefixStr("-iacmtechnews:", "", "Input-ACMTechNews-Path");
  TStr InCiaWFBFPath=Env.GetIfArgPrefixStr("-iciawfb:", "", "Input-CIA-World-Factbook-Path");
  TStr InCordisFPath=Env.GetIfArgPrefixStr("-icordis:", "", "Input-Cordis-Project-Descriptions-Path");
  TStr InAsfaFPath=Env.GetIfArgPrefixStr("-iasfa:", "", "Input-Asfa-Path");
  TStr OutCpdFNm=Env.GetIfArgPrefixStr("-o:", "Out.Cpd", "Output-Cpd-FileName");
  bool RecurseDirP=Env.GetIfArgPrefixBool("-recurse:", false, "Recurse-Directories");
  int MxDocs=Env.GetIfArgPrefixInt("-docs:", -1, "Documents");
  bool TestP=Env.GetIfArgPrefixBool("-test:", false, "Testing");
  if (Env.IsEndOfRun()){return 0;}
  //-itbs:../Cpd2TBs/Reuters21578 -itbs:../Crawl2TBs/aspire -ir21578:../ReutersData/ -ir2000:F:/Reuters2K/Xml -o:F:/Reuters2K/Bin/ -docs:100000 -test
  //-ir2000:F:\Data\Reuters2K\Xml -o:F:\Data\Reuters2K\R2K.Cpd
  //-ihtml:c:\data\cordis\fp6
  //-ir2000:F:\Data\Reuters2K\Xml -o:R2K.Cpd -docs:10000

  // create output file
  OutCpdFNm=TStr::GetNrFNm(OutCpdFNm);
  if (!InHtmlFPath.Empty()){
    TCpDoc::SaveHtmlToCpd(InHtmlFPath, OutCpdFNm, RecurseDirP, MxDocs);
  } else
  if (!InTBsFNm.Empty()){
    TCpDoc::SaveTBsToCpd(InTBsFNm, OutCpdFNm, MxDocs);
  } else
  if (!InLnDocFNm.Empty()){ // Line-Documents-file
    TCpDoc::SaveLnDocToCpd(InLnDocFNm, OutCpdFNm, false, MxDocs);
  } else
  if (!InNmLnDocFNm.Empty()){ // Named-Line-Documents-file
    TCpDoc::SaveLnDocToCpd(InNmLnDocFNm, OutCpdFNm, true, MxDocs);
  } else
  if (!InReuters21578FPath.Empty()){
    OutCpdFNm=TStr::PutFBaseIfEmpty(OutCpdFNm, TCpDoc::Reuters21578CpdFBase);
    TCpDoc::SaveReuters21578ToCpd(InReuters21578FPath, OutCpdFNm, MxDocs);
  } else
  if (!InReuters2000FPath.Empty()){
    OutCpdFNm=TStr::PutFBaseIfEmpty(OutCpdFNm, TCpDoc::Reuters2000CpdFBase);
    TCpDoc::SaveReuters2000ToCpd(InReuters2000FPath, OutCpdFNm, MxDocs);
  } else
  if (!InAcmTechNewsFPath.Empty()){
    OutCpdFNm=TStr::PutFBaseIfEmpty(OutCpdFNm, TCpDoc::AcmTechNewsCpdFBase);
    TCpDoc::SaveAcmTechNewsToCpd(InAcmTechNewsFPath, OutCpdFNm, MxDocs);
  } else
  if (!InCiaWFBFPath.Empty()){
    OutCpdFNm=TStr::PutFBaseIfEmpty(OutCpdFNm, TCpDoc::CiaWFBCpdFBase);
    TCpDoc::SaveCiaWFBToCpd(InCiaWFBFPath, OutCpdFNm, MxDocs);
  } else
  if (!InAsfaFPath.Empty()){
    OutCpdFNm=TStr::PutFBaseIfEmpty(OutCpdFNm, TCpDoc::AsfaFBase);
    TCpDoc::SaveAsfaToCpd(InAsfaFPath, OutCpdFNm);
  } else {
    TExcept::Throw("No Input-File specified!");
  }

  // test created text-binary file
  if (TestP||(!OutCpdFNm.Empty())){
    printf("Testing '%s' ...\n", OutCpdFNm.CStr());
    PSIn CpdSIn=TCpDoc::FFirstCpd(OutCpdFNm); PCpDoc CpDoc; int FileN=0;
    while (TCpDoc::FNextCpd(CpdSIn, CpDoc)){
      printf("%d\r", ++FileN);
    }
    printf("\nDone.\n");
  }

  return 0;
  Catch;
  return 1;
}

