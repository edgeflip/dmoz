/*==========================================================================;
 *
 *  (c) 2006-07 JSI.  All rights reserved.
 *
 *  File:          BowPHKMeans.cpp
 *  Version:       1.0
 *  Desc:		   polysecting hierarchical clustering utility
 *  Author:        Miha Grcar
 *  Created on:    Jul-2006?
 *  Last modified: Jul-2006?
 * 
 ***************************************************************************/

#include "bowphclust.h"
#include "Win32OntoServiceStub.h"

//#include <iostream>
//using namespace std;

int main(int argc, char *argv[])
{
	Try;

	// DESC: create environment
	Env = TEnv(argc, argv, TNotify::StdNotify);

	// DESC: parse command line parameters
	Env.PrepArgs("Bag-Of-Words Polysecting-Hierarchical-K-Means");
	TStr InFNm = Env.GetIfArgPrefixStr("-i:", "", "Input-Bow-File");
	TStr OutPartFNm = Env.GetIfArgPrefixStr("-op:", "HKMeans.BowPart", "Output-BowPartition-File");
	TStr OutTxtFNm = Env.GetIfArgPrefixStr("-ot:", "HKMeans.Txt", "Output-Txt-File");
	TStr OutXmlFNm = Env.GetIfArgPrefixStr("-ox:", "HKMeans.Xml", "Output-Xml-File");
	TStr OutHtmlDirNm = Env.GetIfArgPrefixStr("-oh:", "", "Output-Html-Dir");
	int Docs = Env.GetIfArgPrefixInt("-docs:", -1, "Number-Of-Documents");
	int RndSeed = Env.GetIfArgPrefixInt("-rseed:", 1, "RNG-Seed");
	int ClustTrials = Env.GetIfArgPrefixInt("-ctrials:", 3, "Clustering-Trials");
	double ConvergEps = Env.GetIfArgPrefixFlt("-nceps:", 0.01, "Normalized!-Convergence-Epsilon");
	double CutWordWgtSumPrc = Env.GetIfArgPrefixFlt("-cutww:", 0.5, "Cut-Word-Weight-Sum-Percentage");
	int MnWordFq = Env.GetIfArgPrefixInt("-mnwfq:", 5, "Minimal-Word-Frequency");
	bool PropBowDocWgtBsP = Env.GetIfArgPrefixBool("-propwgt:", false, "Propagate-Weights");
//	bool ExtractKeywordsP = Env.GetIfArgPrefixBool("-extkw:", true, "Extract-Keywords");
	int NumKeywords = Env.GetIfArgPrefixInt("-kw:", 5, "Number-Of-Extracted-Keywords");
	bool SplitCritMinInsteadOfAvgP = Env.GetIfArgPrefixBool("-sc_min:", false, "Min-InsteadOf-Avg-Split-Criterion");
	bool RefineP = Env.GetIfArgPrefixBool("-refine:", true, "Refine-Clusters");
	TStr OntoServiceUrl = Env.GetIfArgPrefixStr("-cws_url:", "", "Classification-Web-Service-Url");
	double SplitCritSlope = Env.GetIfArgPrefixFlt("-sc_k:", 0.3, "Split-Criterion-Slope");
	double LeafCritIntrasim = Env.GetIfArgPrefixFlt("-lc_ism:", 0.6, "Leaf-Criterion-Initial-Intrasim");
	double LeafCritSlope = Env.GetIfArgPrefixFlt("-lc_k:", 0, "Leaf-Criterion-Slope");
	int CwsMedoids = Env.GetIfArgPrefixInt("-cws_medoids:", 2, "Number-Of-Medoids-For-Classification");
	int CwsNumCats = Env.GetIfArgPrefixInt("-cws_cats:", 3, "Number-Of-Returned-Categories");
//	TStr CwsStopWords = Env.GetIfArgPrefixStr("-cws_sw:", "", "OntoKeywords-Stop-Words (comma-separated)");
	if (Env.IsEndOfRun()) { return 0; }

	int OntoServiceStubId = -1;

	// DESC: load data
	if (InFNm.Empty()) 
	{
		TExcept::Throw("No Input-Bow-File specified!");
	}
	PBowDocBs BowDocBs = TBowDocBs::LoadBin(InFNm);

	// DESC: get doc-ids
	TIntV AllDIdV; BowDocBs->GetAllDIdV(AllDIdV);
	if (Docs != -1) { AllDIdV.Trunc(Docs); }

	if (AllDIdV.Len() == 0) 
	{ 
		TExcept::Throw("No documents to process!"); 
	}

	// DESC: options
	TClustOptions Options = (TClustOptions)(coCOPY_INSTEADOF_SPLIT | coLEAF_CRITERION_PRECEDENCE);
	if (PropBowDocWgtBsP) Options = (TClustOptions)((int)Options | coPROPAGATE_WEIGHTS);
	if (RefineP) Options = (TClustOptions)((int)Options | coREFINE);
	if (SplitCritMinInsteadOfAvgP) Options = (TClustOptions)((int)Options | coMIN_INSTEADOF_AVG);
	if (!OntoServiceUrl.Empty()) 
	{
		// DESC: create onto service stub
		OntoServiceStubId = createStub(OntoServiceUrl.CStr(), NULL);
		if (OntoServiceStubId == -1) 
		{ 
			TExcept::Throw("Invalid Classification-Web-Service-Url or Internet connection problems!"); 
		}
	}

	TSimClustParentKdVV Hierarchy;
	PBowDocPart BowDocPart;
	THash<TInt, PBowDocPartClust> ChildToParentMap;
	getHierarchy(BowDocBs, Hierarchy, BowDocPart, ChildToParentMap, SplitCritSlope, LeafCritIntrasim, LeafCritSlope, (TClustOptions)Options, 
		TNotify::StdNotify, TBowSim::New(bstCos), TRnd(RndSeed), ClustTrials, ConvergEps, bwwtNrmTFIDF, CutWordWgtSumPrc, MnWordFq, AllDIdV);

	if (NumKeywords > 0)
	{
		describeClusters(Hierarchy, BowDocBs, NumKeywords);
	}

	if (!OntoServiceUrl.Empty()) 
	{
		classifyClusters(Hierarchy, BowDocBs, OntoServiceStubId, CwsMedoids, CwsNumCats, NumKeywords);
	}

	if (!OutHtmlDirNm.Empty())
	{
		createHtml(Hierarchy, BowDocBs, bwwtNrmTFIDF, CutWordWgtSumPrc, MnWordFq, OutHtmlDirNm, ChildToParentMap, NumKeywords);
	}

	// DESC: output the partition
	STATUS("Saving the partition...");
	if (!OutPartFNm.Empty())
	{
		TFOut SOut(OutPartFNm); 
		BowDocPart->Save(SOut);
	}
	if (!OutTxtFNm.Empty())
	{
		BowDocPart->SaveTxt(OutTxtFNm, BowDocBs, true, 15, 0.5, true);
	}
	if (!OutXmlFNm.Empty())
	{
		BowDocPart->SaveXml(OutXmlFNm, BowDocBs);
	}

	STATUS("Done.");

	deleteAllObjects();
	return 0;

	Catch;

	deleteAllObjects();
	return 1;
}