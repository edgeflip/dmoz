/*==========================================================================;
 *
 *  (c) 2006-07 JSI.  All rights reserved.
 *
 *  File:          bowphclust.h
 *  Version:       1.0
 *  Desc:		   polysecting hierarchical clustering algorithm
 *  Author:        Miha Grcar
 *  Created on:    Jul-2006?
 *  Last modified: Jul-2006?
 * 
 ***************************************************************************/

#ifndef BOWPHCLUST_H
#define BOWPHCLUST_H

#include "mine.h"

#undef  STATUS
#undef  WARNING
#undef  ERROR
#define STATUS(status_msg)    TNotify::OnStatus(TNotify::StdNotify, status_msg)
#define WARNING(warning_msg)  TNotify::OnNotify(TNotify::StdNotify, ntWarn, warning_msg);
#define ERROR(error_msg)      TNotify::OnNotify(TNotify::StdNotify, ntErr, error_msg);

enum TClustOptions 
{	
	coNONE							= 0,
	coMIN_INSTEADOF_AVG				= 1,
	coCOPY_INSTEADOF_SPLIT			= 2,
	coPROPAGATE_WEIGHTS				= 4,  
	coREFINE						= 8,  
	coLEAF_CRITERION_PRECEDENCE		= 16,
	coDEFAULT						= coCOPY_INSTEADOF_SPLIT | coREFINE | coLEAF_CRITERION_PRECEDENCE
};

typedef TPair<PBowDocPartClust, PBowDocPartClust> TClustParentPr;
typedef TKeyDat<TFlt, TClustParentPr>			  TSimClustParentKd;
typedef TVec<TSimClustParentKd>					  TSimClustParentKdV;
typedef TVec<TSimClustParentKdV>				  TSimClustParentKdVV;

void getHierarchy(const PBowDocBs &bow_doc_bs,
				  TSimClustParentKdVV &hierarchy,
				  PBowDocPart &bow_doc_part,
				  THash<TInt, PBowDocPartClust> &child_to_parent_map,	
				  const double &split_crit_slope			= 0.3,
				  const double &leaf_crit_isim				= 0.6,
				  const double &leaf_crit_slope				= 0,
				  const TClustOptions &options				= coDEFAULT,
				  const PNotify &notify						= TNotify::StdNotify,
				  const PBowSim &bow_sim					= TBowSim::New(bstCos),
				  TRnd &rnd									= TRnd(1),
				  const int &clust_trials					= 3,
				  const double &converg_eps					= 0.01,				
				  const TBowWordWgtType &word_wgt_type		= bwwtNrmTFIDF,
				  const double &cut_word_wgt_sum_prc		= 0.5,
				  const int &mn_word_fq						= 5,
				  const TIntV &_doc_id_v					= TIntV());

void describeClusters(const TSimClustParentKdVV &hierarchy, const PBowDocBs &bow_doc_bs, const int &num_keywords);

void classifyClusters(const TSimClustParentKdVV &hierarchy, const PBowDocBs &bow_doc_bs, const int &onto_service_stub_id,
					  const int &num_medoids, const int &num_categories, const int &num_onto_keywords);

void createHtml(const TSimClustParentKdVV &hierarchy, const PBowDocBs &bow_doc_bs, const TBowWordWgtType &word_wgt_type, const double &cut_word_wgt_sum_prc,	
				const int &mn_word_fq, TStr html_dir, /*const*/ THash<TInt, PBowDocPartClust> &child_to_parent_map, const int &num_keywords);

TStr getClustInfo(const PBowDocPartClust &clust, const TStr &info_tag);

#endif