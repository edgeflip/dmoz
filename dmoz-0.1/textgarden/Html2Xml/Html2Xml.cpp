#include "base.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Html To XML");
  TStr InHtmlFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-Html-File");
  TStr OutXmlFNm=Env.GetIfArgPrefixStr("-o:", "", "Output-XML-File");
  TStr BaseUrlStr=Env.GetIfArgPrefixStr("-u:", "", "Base-Url");
  bool OutTextP=Env.GetIfArgPrefixBool("-otxt:", true, "Output-Text");
  bool OutUrlP=Env.GetIfArgPrefixBool("-ourl:", true, "Output-Urls");
  bool OutToksP=Env.GetIfArgPrefixBool("-otok:", true, "Output-Tokens");
  bool OutTagsP=Env.GetIfArgPrefixBool("-otag:", true, "Output-Tags");
  bool OutArgsP=Env.GetIfArgPrefixBool("-oarg:", true, "Output-Arguments");
  if (Env.IsEndOfRun()){return 0;}

  // prepare output file-name
  if (OutXmlFNm.Empty()){
    TStr FExt=".xml";
    if (InHtmlFNm.GetFExt().GetUc()==".XML"){FExt=".xxml";}
    OutXmlFNm=TStr::PutFExt(InHtmlFNm, FExt);
  }
  // load input file
  TStr HtmlStr=TStr::LoadTxt(InHtmlFNm);
  // save html to xml
  THtmlDoc::SaveHtmlToXml(
   HtmlStr, OutXmlFNm, BaseUrlStr,
   OutTextP, OutUrlP, OutToksP, OutTagsP, OutArgsP);
  printf("Html-File %s saved to XML-File %s.\n",
   InHtmlFNm.CStr(), OutXmlFNm.CStr());

  return 0;
  Catch;
  return 1;
}

