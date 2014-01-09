#include "mine.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("DMoz-Binary To Text", -1);
  TStr InFPath=Env.GetIfArgPrefixStr("-i:", "", "Input-File-Path");
  TStr OutFPath=Env.GetIfArgPrefixStr("-o:", "", "Output-File-Path");
  TStr InDMozBinFBase=Env.GetIfArgPrefixStr("-ib:", TDMozInfo::BinFullFBase, "Input-DMoz-Binary-FileName");
  TStr OutDumpFBase=Env.GetIfArgPrefixStr("-od:", "DMozDump.Txt", "Output-Dump-FileName");
  TStr OutLnDocsFBase=Env.GetIfArgPrefixStr("-ol:", "DMozLnDocs.Txt", "Output-LineDocuments-FileName");
  TStr OutUrlCatFBase=Env.GetIfArgPrefixStr("-ou:", "DMozUrlCat.Txt", "Output-Url-Categories-FileName");
  TStr OutSampleFBase=Env.GetIfArgPrefixStr("-os:", "DMozSample.Txt", "Output-Sample-FileName");
  TStr RootCatNm=Env.GetIfArgPrefixStr("-c:", "Top", "Root-Category-Name");
  bool SaveDumpP=Env.GetIfArgPrefixBool("-dump:", false, "Save-Dump");
  bool SaveLnDocsP=Env.GetIfArgPrefixBool("-lnd:", false, "Save-Line-Documents");
  bool SaveMd5P=Env.GetIfArgPrefixBool("-md5:", true, "Save-Url-Md5");
  bool SaveUrlCatP=Env.GetIfArgPrefixBool("-urlcat:", true, "Save-Url-Categories");
  bool SaveSampleP=Env.GetIfArgPrefixBool("-sample:", true, "Save-Sample");
  int SampleRndSeed=Env.GetIfArgPrefixInt("-srnd:", 1, "Sample-Random-Seed");
  int SampleSize=Env.GetIfArgPrefixInt("-ssize:", 100000, "Sample-Size");
  bool SampleSiteUrlP=Env.GetIfArgPrefixBool("-ssites:", true, "Sample-Site-URLs-Only");
  bool SampleStructP=Env.GetIfArgPrefixBool("-sstruct:", false, "Sample-Structure");
  if (Env.IsEndOfRun()){return 0;}

  // load DMoz-Base
  PDMozBs DMozBs=TDMozBs::LoadBin(InDMozBinFBase, InFPath);

  // output to text-file
  if (SaveDumpP){
    TDMozBs::SaveTxt(DMozBs, RootCatNm, OutDumpFBase, OutFPath);
  }
  if (SaveLnDocsP){
    TDMozBs::SaveLnDocTxt(DMozBs, RootCatNm, OutLnDocsFBase, OutFPath, SaveMd5P);
  }
  if (SaveSampleP){
    TDMozBs::SaveSampleTxt(DMozBs, RootCatNm, OutSampleFBase, OutFPath,
     SampleRndSeed, SampleSize, SampleSiteUrlP, SampleStructP);
  }

  return 0;
  Catch;
  return 1;
}

