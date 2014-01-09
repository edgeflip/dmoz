#include "base.h"
#include "graph.h"

int main(int argc, char* argv[]){
  Try;
  // create environment
  Env=TEnv(argc, argv, TNotify::StdNotify);

  // get command line parameters
  Env.PrepArgs("Yield-Broker Log-Analyser");
  TStr InYBLogFNm=Env.GetIfArgPrefixStr("-i:", "", "Input-YBLog-FileName");
  double MxUsrHitsPrc=Env.GetIfArgPrefixFlt("-mxusrhp:", 0.1, "Max-User-Hits-Percent");
  double MxUrlHitsPrc=Env.GetIfArgPrefixFlt("-mxurlhp:", 0.1, "Max-Url-Hits-Percent");
  int TargetUsrId=Env.GetIfArgPrefixInt("-usr:", -1, "Target-User-Id");
  int TargetUrlId=Env.GetIfArgPrefixInt("-url:", -1, "Target-Url-Id");
  bool UsrStatP=Env.GetIfArgPrefixBool("-usrstat:", false, "User-Statistics");
  bool UrlStatP=Env.GetIfArgPrefixBool("-urlstat:", false, "Url-Statistics");
  int TopListLen=Env.GetIfArgPrefixInt("-top:", 10, "Top-List-Length");
  TStr HitsFNm=Env.GetIfArgPrefixStr("-hits:", "", "Output-Hits-FileName");
  if (Env.IsEndOfRun()){return 0;}

  // create user & url data-structures
  TIntPrV UsrIdUrlIdPrV;
  TIntPrV UrlIdUsrIdPrV;
  TIntH UsrIdToHitsH;
  TIntH UrlIdToHitsH;

  // open log file
  PSIn YBSIn=TFIn::New(InYBLogFNm);
  // load header line
  TStrV FldValV; TSs::LoadTxtFldV(ssfCommaSep, YBSIn, FldValV);
  int UsrIdFldN=FldValV.SearchForw("UserID");
  int UrlIdFldN=FldValV.SearchForw("URLID");
  // traverse & load file
  while (!YBSIn->Eof()){
    TSs::LoadTxtFldV(ssfCommaSep, YBSIn, FldValV);
    int UsrId=FldValV[UsrIdFldN].GetInt();
    int UrlId=FldValV[UrlIdFldN].GetInt();
    UsrIdToHitsH.AddKey(UsrId);
    UrlIdToHitsH.AddKey(UrlId);
    UsrIdUrlIdPrV.Add(TIntPr(UsrId, UrlId));
    UrlIdUsrIdPrV.Add(TIntPr(UrlId, UsrId));
  }
  // merge duplicate hits
  UsrIdUrlIdPrV.Merge();
  UrlIdUsrIdPrV.Merge();
  // create shortcuts
  int UsrIdUrlIdPrs=UsrIdUrlIdPrV.Len();
  int UrlIdUsrIdPrs=UrlIdUsrIdPrV.Len();
  int UsrIds=UsrIdToHitsH.Len();
  int UrlIds=UrlIdToHitsH.Len();
  printf("Users:%d   Urls:%d\n", UsrIds, UrlIds);
  // count users & urls
  IAssert(UsrIdUrlIdPrs==UrlIdUsrIdPrs);
  for (int PrN=0; PrN<UsrIdUrlIdPrs; PrN++){
    int UsrId=UsrIdUrlIdPrV[PrN].Val1; UsrIdToHitsH.GetDat(UsrId)++;
    int UrlId=UsrIdUrlIdPrV[PrN].Val2; UrlIdToHitsH.GetDat(UrlId)++;
  }

  // output sorted user hits
  if (UsrStatP){
    TIntPrV HitsUsrIdPrV; UsrIdToHitsH.GetDatKeyPrV(HitsUsrIdPrV);
    HitsUsrIdPrV.Sort(false);
    printf("n:[user-id:user-hits] ");
    for (int UsrIdN=0; UsrIdN<HitsUsrIdPrV.Len(); UsrIdN++){
      printf("%d:[%d:%d] ",
       1+UsrIdN, HitsUsrIdPrV[UsrIdN].Val2, HitsUsrIdPrV[UsrIdN].Val1);
    }
    printf("\n\n");
  }

  // output sorted url hits
  if (UrlStatP){
    TIntPrV HitsUrlIdPrV; UrlIdToHitsH.GetDatKeyPrV(HitsUrlIdPrV);
    HitsUrlIdPrV.Sort(false);
    printf("n:[url-id:url-hits] ");
    for (int UrlIdN=0; UrlIdN<HitsUrlIdPrV.Len(); UrlIdN++){
      printf("%d:[%d:%d] ",
       1+UrlIdN, HitsUrlIdPrV[UrlIdN].Val2, HitsUrlIdPrV[UrlIdN].Val1);
    }
    printf("\n\n");
  }

  // create user edge-list
  TIntPrFltH UsrIdPrToWgtH;
  {printf("Create Usr Graph ...\n");
  int UUPrN=0;
  while (UUPrN<UrlIdUsrIdPrs){
    if (UUPrN%100==0){
      printf("%.1f%%\r", 100*UUPrN/double(UrlIdUsrIdPrs));}
    // save current user-id, url-id
    int UrlId=UrlIdUsrIdPrV[UUPrN].Val1;
    int UrlIdHits=UrlIdToHitsH.GetDat(UrlId);
    int UsrId1=UrlIdUsrIdPrV[UUPrN].Val2;
    // skip anomalous urls
    if (UrlIdToHitsH.GetDat(UrlId)/double(UrlIdUsrIdPrs)>MxUrlHitsPrc){
      UUPrN++; continue;}
    // skip anomalous users
    if (UsrIdToHitsH.GetDat(UsrId1)/double(UsrIdUrlIdPrs)>MxUsrHitsPrc){
      UUPrN++; continue;}
    // traverse current user-id records
    int SubUUPrN=UUPrN+1;
    while ((SubUUPrN<UrlIdUsrIdPrs)&&(UrlId==UrlIdUsrIdPrV[SubUUPrN].Val1)){
      // save current url-id
      int UsrId2=UrlIdUsrIdPrV[SubUUPrN].Val2;
      // skip anomalous users
      if (UsrIdToHitsH.GetDat(UsrId2)/double(UsrIdUrlIdPrs)>MxUsrHitsPrc){
        SubUUPrN++; continue;}
      // create edge
      IAssert(UsrId1<=UsrId2);
      TIntPr UsrIdPr(UsrId1, UsrId2);
      // calculate weight
      double Wgt=1/log(1+UrlIdHits);
      // increase edge weight
      UsrIdPrToWgtH.AddDat(UsrIdPr)+=Wgt;
      SubUUPrN++;
    }
    UUPrN++;
  }
  printf("Done.\n");}

  // create url edge-list
  TIntPrFltH UrlIdPrToWgtH;
  {printf("Create Url Graph ...\n");
  int UUPrN=0;
  while (UUPrN<UsrIdUrlIdPrs){
    if (UUPrN%100==0){
      printf("%.1f%%\r", 100*UUPrN/double(UsrIdUrlIdPrs));}
    // save current user-id, user-hits, url-id
    int UsrId=UsrIdUrlIdPrV[UUPrN].Val1;
    int UsrIdHits=UsrIdToHitsH.GetDat(UsrId);
    int UrlId1=UsrIdUrlIdPrV[UUPrN].Val2;
    // skip anomalous users
    if (UsrIdToHitsH.GetDat(UsrId)/double(UsrIdUrlIdPrs)>MxUsrHitsPrc){
      UUPrN++; continue;}
    // skip anomalous urls
    if (UrlIdToHitsH.GetDat(UrlId1)/double(UrlIdUsrIdPrs)>MxUrlHitsPrc){
      UUPrN++; continue;}
    // traverse current user-id records
    int SubUUPrN=UUPrN+1;
    while ((SubUUPrN<UsrIdUrlIdPrs)&&(UsrId==UsrIdUrlIdPrV[SubUUPrN].Val1)){
      // save current url-id
      int UrlId2=UsrIdUrlIdPrV[SubUUPrN].Val2;
      // skip anomalous urls
      if (UrlIdToHitsH.GetDat(UrlId2)/double(UrlIdUsrIdPrs)>MxUrlHitsPrc){
        SubUUPrN++; continue;}
      // create edge
      IAssert(UrlId1<=UrlId2);
      TIntPr UrlIdPr(UrlId1, UrlId2);
      // calculate weight
      double Wgt=1/log(1+UsrIdHits);
      // increase edge weight
      UrlIdPrToWgtH.AddDat(UrlIdPr)+=Wgt;
      SubUUPrN++;
    }
    UUPrN++;
  }
  printf("Done.\n");}

  // calculate & output closest users
  if (TargetUsrId!=-1){
    // create weight/user-pair vector
    TFltIntPrV WgtUsrIdPrV;
    for (int UsrIdPrN=0; UsrIdPrN<UsrIdPrToWgtH.Len(); UsrIdPrN++){
      TIntPr UsrIdPr=UsrIdPrToWgtH.GetKey(UsrIdPrN);
      double Wgt=UsrIdPrToWgtH[UsrIdPrN];
      if (UsrIdPr.Val1==TargetUsrId){
        WgtUsrIdPrV.Add(TFltIntPr(Wgt, UsrIdPr.Val2));
      } else
      if (UsrIdPr.Val2==TargetUsrId){
        WgtUsrIdPrV.Add(TFltIntPr(Wgt, UsrIdPr.Val1));
      }
    }
    WgtUsrIdPrV.Sort(false);
    // output closest users
    printf("Closests users to '%d' [user-id:weight]:\n", TargetUsrId);
    int WgtUsrIdPrs=TInt::GetMn(TopListLen, WgtUsrIdPrV.Len());
    for (int WgtUsrIdPrN=0; WgtUsrIdPrN<WgtUsrIdPrs; WgtUsrIdPrN++){
      double Wgt=WgtUsrIdPrV[WgtUsrIdPrN].Val1;
      int UsrId=WgtUsrIdPrV[WgtUsrIdPrN].Val2;
      printf("[%d:%.3f] ", UsrId, Wgt);
    }
  }

  // calculate & output closest urls
  if (TargetUrlId!=-1){
    // create weight/url-pair vector
    TFltIntPrV WgtUrlIdPrV;
    for (int UrlIdPrN=0; UrlIdPrN<UrlIdPrToWgtH.Len(); UrlIdPrN++){
      TIntPr UrlIdPr=UrlIdPrToWgtH.GetKey(UrlIdPrN);
      double Wgt=UrlIdPrToWgtH[UrlIdPrN];
      if (UrlIdPr.Val1==TargetUrlId){
        WgtUrlIdPrV.Add(TFltIntPr(Wgt, UrlIdPr.Val2));
      } else
      if (UrlIdPr.Val2==TargetUrlId){
        WgtUrlIdPrV.Add(TFltIntPr(Wgt, UrlIdPr.Val1));
      }
    }
    WgtUrlIdPrV.Sort(false);
    // output closest urls
    printf("Closests urls to '%d' [url-id:weight]:\n", TargetUrlId);
    int WgtUrlIdPrs=TInt::GetMn(TopListLen, WgtUrlIdPrV.Len());
    for (int WgtUrlIdPrN=0; WgtUrlIdPrN<WgtUrlIdPrs; WgtUrlIdPrN++){
      double Wgt=WgtUrlIdPrV[WgtUrlIdPrN].Val1;
      int UrlId=WgtUrlIdPrV[WgtUrlIdPrN].Val2;
      printf("[%d:%.3f] ", UrlId, Wgt);
    }
  }

  // calculate url hits-weights
  if (!HitsFNm.Empty()){
    printf("Create Hits Graph ...\n");
    // create graph
    PGraph Graph=TGGraph::New();
    // create vertices
    TVrtxV VrtxV(UrlIds, 0);
    for (int UrlIdN=0; UrlIdN<UrlIds; UrlIdN++){
      int UrlId=UrlIdToHitsH.GetKey(UrlIdN);
      TStr VNm=TInt::GetStr(UrlId);
      PVrtx Vrtx=TGVrtx::New(VNm); Graph->AddVrtx(Vrtx);
      VrtxV.Add(Vrtx);
    }
    // create edges
    {for (int UrlIdN=0; UrlIdN<UrlIds; UrlIdN++){
      if (UrlIdN%10==0){
        printf("%.1f%%\r", 100*UrlIdN/double(UrlIds));}
      // get url-id
      int UrlId=UrlIdToHitsH.GetKey(UrlIdN);
      // create weight/url-pair vector
      TFltIntKdV WgtUrlIdKdV;
      for (int UrlIdPrN=0; UrlIdPrN<UrlIdPrToWgtH.Len(); UrlIdPrN++){
        TIntPr UrlIdPr=UrlIdPrToWgtH.GetKey(UrlIdPrN);
        double Wgt=UrlIdPrToWgtH[UrlIdPrN];
        if (UrlIdPr.Val1==UrlId){
          WgtUrlIdKdV.Add(TFltIntKd(Wgt, UrlIdPr.Val2));
        } else
        if (UrlIdPr.Val2==UrlId){
          WgtUrlIdKdV.Add(TFltIntKd(Wgt, UrlIdPr.Val1));
        }
      }
      WgtUrlIdKdV.Shuffle(TRnd(0));
      WgtUrlIdKdV.Sort(false);
      // generate closest urls
      TIntV SimUrlIdV;
      int WgtUrlIdPrs=TInt::GetMn(10, WgtUrlIdKdV.Len());
      for (int WgtUrlIdPrN=0; WgtUrlIdPrN<WgtUrlIdPrs; WgtUrlIdPrN++){
        int SimUrlId=WgtUrlIdKdV[WgtUrlIdPrN].Dat;
        SimUrlIdV.Add(SimUrlId);
      }
      // create edge
      for (int SimUrlIdN=0; SimUrlIdN<SimUrlIdV.Len(); SimUrlIdN++){
        int DstUrlId=SimUrlIdV[SimUrlIdN];
        int DstUrlIdN=UrlIdToHitsH.GetKeyId(DstUrlId);
        PEdge Edge=TGEdge::New(VrtxV[UrlIdN], VrtxV[DstUrlIdN]);
        Graph->AddEdge(Edge);
      }
    }}
    // generate hits-weights
    Graph->GetHitsW();
    // save hits-weights
    Graph->SaveTxtHits(HitsFNm);
    printf("Done.\n");
  }

  return 0;
  Catch;
  return 1;
}

