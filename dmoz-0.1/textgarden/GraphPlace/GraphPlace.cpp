#include "graph.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // command line parameters
  Env.PrepArgs("Graph Place", 0);
  TStr InGraphFNm=Env.GetIfArgPrefixStr("-i:", "Graph.Xml", "Input-Graph-FileName");
  TStr OutGraphFNm=Env.GetIfArgPrefixStr("-o:", "Graph.Xml", "Output-Graph-FileName");
  double BorderFac=Env.GetIfArgPrefixFlt("-bf:", 0.1, "Border-Factor");
  if (Env.IsEndOfRun()){return 0;}

  printf("Loading from '%s' ...", InGraphFNm.CStr());
  PGraph Graph=TGraph::LoadXml(InGraphFNm);
  printf(" Done.\n");

  printf("Placing ...");
  // place graph
  TRnd Rnd(0);
  Graph->PlaceSimAnnXY(Rnd, NULL);
  // reascale coordinates to fit
  Graph->RescaleXY(BorderFac);
  printf(" Done.\n");

  printf("Saving to '%s' ...", OutGraphFNm.CStr());
  Graph->SaveXml(OutGraphFNm);
  printf(" Done.\n");

  return 0;
  Catch;
  return 1;
}

