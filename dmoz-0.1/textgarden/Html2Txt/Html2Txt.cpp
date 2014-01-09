#include "base.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Html To Text", 0);
  TStr InHtmlFNm=Env.GetIfArgPrefixStr("-i:", "ijs.html", "Input-Html-File");
  TStr OutTxtFNm=Env.GetIfArgPrefixStr("-o:", "html.txt", "Output-Text-File");
  TStr BaseUrlStr=Env.GetIfArgPrefixStr("-u:", "http://www.ijs.si/", "Base-Url");
  bool SaveOutUrlP=Env.GetIfArgPrefixBool("-sou:", false, "Save-Outgoing-Urls");
  bool SaveTagP=Env.GetIfArgPrefixBool("-st:", false, "Save-Tags");
  if (Env.IsEndOfRun()){return 0;}

  // prepare output file-name
  if (OutTxtFNm.Empty()){
    TStr FExt=".txt";
    if (InHtmlFNm.GetFExt().GetUc()==".TXT"){FExt=".ttxt";}
    OutTxtFNm=TStr::PutFExt(InHtmlFNm, FExt);
  }
  // load input file
  TStr HtmlStr=TStr::LoadTxt(InHtmlFNm);
  // save html to text
  THtmlDoc::SaveHtmlToTxt(
   HtmlStr, OutTxtFNm, BaseUrlStr,
   SaveOutUrlP, SaveTagP);
  printf("Html-File %s saved to Text-File %s.\n",
   InHtmlFNm.CStr(), OutTxtFNm.CStr());

  return 0;
  Catch;
  return 1;
}
