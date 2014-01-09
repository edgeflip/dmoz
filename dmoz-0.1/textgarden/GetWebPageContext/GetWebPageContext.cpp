#include "google.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Get Web Page Context");
  TStr FocusUrlStr=Env.GetIfArgPrefixStr("-i:", "", "Focus-Url");
  //TStr OutXmlCtxGraphFNm=Env.GetIfArgPrefixStr("-ox:", "WebPageContext.Xml", "Output-Xml-WebPageContext-File");
  TStr OutTxtCtxGraphFNm=Env.GetIfArgPrefixStr("-ot:", "WebPageContext.Txt", "Output-Txt-WebPageContext-File");
  if (Env.IsEndOfRun()){return 0;}

  // get context-graph
  PGgCtxGraph CtxGraph=TGgCtxGraph::GetCtxGraph(FocusUrlStr);
  // save context-Graph to text
  //if (!OutXmlCtxGraphFNm.Empty()){
  //  CtxGraph->SaveTxt(OutXmlCtxGraphFNm);}
  if (!OutTxtCtxGraphFNm.Empty()){
    CtxGraph->SaveTxt(OutTxtCtxGraphFNm);}

  return 0;
  Catch;
  return 1;
}

