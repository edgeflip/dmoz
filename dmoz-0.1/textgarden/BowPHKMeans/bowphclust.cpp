/*==========================================================================;
 *
 *  (c) 2006-07 JSI.  All rights reserved.
 *
 *  File:          bowphclust.cpp
 *  Version:       1.0
 *  Desc:		   polysecting hierarchical clustering algorithm
 *  Author:        Miha Grcar
 *  Created on:    Jul-2006?
 *  Last modified: Jul-2007
 * 
 ***************************************************************************/

#include "bowphclust.h"
#include "Win32OntoServiceStub.h"

#include <iostream>		
using namespace std;	

double SplitCritSlope;
double LeafCritIntrasim;
double LeafCritSlope;

class TCategoryStats
{
private:
	TVec<TTriple<TInt, TFlt, TStr> > m_categories;
	THash<TStr, TFlt> m_stats;
public:
	void add(const TInt &doc_id, const double &weight, const TStr &category)
	{
		m_categories.Add(TTriple<TInt, TFlt, TStr>(doc_id, weight, category));
	}
	void updateStats() 
	{
		m_stats.Clr();
		for (int i = 0; i < m_categories.Len(); i++)
		{
			double w = m_categories[i].Val2;
			TStrV lvl_str_v;
			m_categories[i].Val3.SplitOnAllCh('/', lvl_str_v);
			for (int j = 0; j < lvl_str_v.Len(); j++)
			{
				if (!m_stats.IsKey(lvl_str_v[j])) { m_stats.AddDat(lvl_str_v[j], 0); }
				m_stats(lvl_str_v[j]) += w;
			}
		}
	}
	double weight(const TStr &category, const bool &use_sqr = true) // WARNME: use_sqr
	{
		TStrV lvl_str_v;
		category.SplitOnAllCh('/', lvl_str_v);
		double sum = 0;
		for (int i = 0; i < lvl_str_v.Len(); i++)
		{
			Assert(m_stats.IsKey(lvl_str_v[i]));
			sum += use_sqr ? pow((double)m_stats(lvl_str_v[i]), 2) : (double)m_stats(lvl_str_v[i]);
		}
		Assert(lvl_str_v.Len() > 0);
		return sum / (double)lvl_str_v.Len();
	}
	void reset()
	{
		m_categories.Clr();
		m_stats.Clr();
	}
	void getBestMatch(TStr &best_match)
	{
		getBestMatch(best_match, TStr(), TStr());
	}
	void getBestMatch(TStr &best_match, TStr &ext_1, TStr &ext_2)
	{
		double dummy;
		getBestMatch(best_match, dummy, ext_1, dummy, ext_2, dummy);
	}
	void getBestMatch(TStr &best_match, double &best_match_wgt, TStr &ext_1, double &ext1_wgt, TStr &ext_2, double &ext2_wgt)
	{
		best_match = "";
		ext_1 = "";
		ext_2 = "";
		best_match_wgt = ext1_wgt = ext2_wgt = 0;
		if (m_categories.Len() <= 0) { return; }
		TFltStrKdV tmp;
		for (int i = 0; i < m_categories.Len(); i++)
		{
			tmp.Add(TFltStrKd(weight(m_categories[i].Val3), m_categories[i].Val3));
		}
		tmp.Sort(/*asc=*/false);
		best_match = tmp[0].Dat;
		best_match_wgt = tmp[0].Key;
		int j = 1;
		while (j < tmp.Len())
		{
			if (tmp[j].Dat.IsPrefix(best_match) && tmp[j].Dat != best_match) { ext_1 = tmp[j].Dat; ext1_wgt = tmp[j].Key; break; }
			j++;
		}
		while (j < tmp.Len())
		{
			if (tmp[j].Dat.IsPrefix(ext_1) && tmp[j].Dat != ext_1) { ext_2 = tmp[j].Dat; ext2_wgt = tmp[j].Key; break; }
			j++;
		}
	}
	TStr getKeywords(int num_keywords, const TStrV &stop_words = TStrV()) // WARNME: stop_words
	{
		TFltStrKdV tmp;
		for (int i = 0; i < m_stats.Len(); i++)
		{
			TStr keyword;
			TFlt weight;
			m_stats.GetKeyDat(i, keyword, weight);
			tmp.Add(TFltStrKd(weight, keyword));
		}
		tmp.Sort(/*asc=*/false);
		TStr ret_val;
		for (int i = 0; i < __min(num_keywords, tmp.Len()); i++)
		{
			if (stop_words.IsIn(tmp[i].Dat)) { num_keywords++; continue; }
			if (ret_val != "") { ret_val += ", "; }
			ret_val += tmp[i].Dat;
		}
		return ret_val;
	}
};

TStr getClustInfo(const PBowDocPartClust &clust, const TStr &info_tag)
{
	int begin_idx = clust->GetNm().SearchStr(TStr::Fmt("(%s)", info_tag.CStr()));
	if (begin_idx == -1) { return ""; }
	begin_idx += info_tag.Len() + 2;
	int end_idx = clust->GetNm().SearchStr(TStr::Fmt("(/%s)", info_tag.CStr()));
	if (end_idx == -1) { return ""; }
	end_idx	-= 1;
	return clust->GetNm().GetSubStr(begin_idx, end_idx);
}

int getClustId(const PBowDocPartClust &clust)
{
	Assert(sizeof(void *) == sizeof(int));
	return (int)(__int64)clust();
}

int findDId(const TVec<PBowDocPartClust> &clusters, const int &d_id)
{
	for (int i = 0; i < clusters.Len(); i++)
	{
		if (clusters[i]->GetDIdVRef().IsIn(d_id)) { return i; }
	}
	return -1;
}

void refine(TSimClustParentKdVV &hierarchy, /*const*/ THash<TInt, PBowDocPartClust> &child_to_parent_map, const PBowDocWgtBs &bow_doc_wgt_bs, 
			const PBowSim &bow_sim, const PBowDocBs &bow_doc_bs)
{
	TVec<PBowDocPartClust> leaves;
	// DESC: gather leaves
	for (int lvl = 0; lvl < hierarchy.Len(); lvl++)
	{
		for (int clust = 0; clust < hierarchy[lvl].Len(); clust++)
		{
			TBowDocPartClust *cluster = hierarchy[lvl][clust].Dat.Val1();
			if (!cluster->IsSubPart() && cluster->GetNm() != "copy") 
			{
				leaves.Add(hierarchy[lvl][clust].Dat.Val1);
				leaves.Last()->PutConceptSpV(TBowClust::GetConceptSpV(bow_doc_wgt_bs, bow_sim, cluster->GetDIdVRef()));
				Assert(leaves.Last()->IsConceptSpV());
			}
		}
	}
	// DESC: for each document find its matching leaf cluster
	for (int i = 0; i < bow_doc_wgt_bs->GetDocs(); i++)
	{
		int doc_id = bow_doc_wgt_bs->GetDId(i);
		TVec<TKeyDat<TFlt, TInt> > tmp;
		for (int j = 0; j < leaves.Len(); j++)
		{	
			double sim_val = bow_sim->GetSim(leaves[j]->GetConceptSpV(), bow_doc_wgt_bs->GetSpV(doc_id));
			tmp.Add(TKeyDat<TFlt, TInt>(sim_val, j));
		}
		Assert(tmp.Len() > 0);
		tmp.Sort(/*asc=*/false); // WARNME: finding max would be sufficient here
		int src_clust_idx = findDId(leaves, doc_id);
		Assert(src_clust_idx >= 0);
		int target_clust_idx = tmp[0].Dat;
		if (src_clust_idx != target_clust_idx) // DESC: ...then we need to move the document 
		{
			STATUS(TStr::Fmt("moving the document: %s", bow_doc_bs->GetDocNm(doc_id).CStr()));
			// DESC: remove the document from the hierarchy
			TBowDocPartClust *clust = leaves[src_clust_idx]();
			Assert(clust != NULL);
			while (clust != NULL)
			{
				int clust_id = getClustId(clust);
				clust->DelDId(doc_id);
				// WARNME: it is possible to get an empty leaf cluster here but it is very unlikely
				if (clust->GetDocs() == 0) { WARNING("A leaf cluster is empty. Prunning empty leaves not implemented yet."); }
				clust = child_to_parent_map.IsKey(clust_id) ? child_to_parent_map(clust_id)() : NULL;
			}
			// DESC: re-insert the document
			clust = leaves[target_clust_idx]();
			Assert(clust != NULL);
			while (clust != NULL)
			{
				int clust_id = getClustId(clust);
				clust->PutDId(doc_id);
				clust = child_to_parent_map.IsKey(clust_id) ? child_to_parent_map(clust_id)() : NULL;
			}
		}
	}
}

void buildBowDocPart(const TSimClustParentKdVV &hierarchy, THash<TInt, PBowDocPartClust> &child_to_parent_map, const TClustOptions &options, 
					 PBowDocPart &bow_doc_part, const PBowDocBs &bow_doc_bs, const TBowWordWgtType &word_wgt_type, const double &cut_word_wgt_sum_prc, 
					 const int &mn_word_fq, const PBowSim &bow_sim)
{
	child_to_parent_map.Clr();
	for (int lvl = 0; lvl < hierarchy.Len(); lvl++)
	{
		for (int clust = 0; clust < hierarchy[lvl].Len(); clust++)
		{
			TBowDocPartClust *cluster = hierarchy[lvl][clust].Dat.Val1();
			TBowDocPartClust *parent = hierarchy[lvl][clust].Dat.Val2();
			child_to_parent_map.AddDat(getClustId(cluster), hierarchy[lvl][clust].Dat.Val2); 
			if (parent != NULL)
			{
				if (!parent->IsSubPart()) 
				{
					parent->PutSubPart(TBowDocPart::New());
				}
				parent->GetSubPart()->AddClust(cluster);     
			}
		}
	}
	// DESC: exclude cluster copies from the hierarchy
	if ((options & coCOPY_INSTEADOF_SPLIT) != 0)
	{
		for (int lvl = 0; lvl < hierarchy.Len(); lvl++)
		{
			for (int clust = 0; clust < hierarchy[lvl].Len(); clust++)
			{
				TBowDocPartClust *cluster = hierarchy[lvl][clust].Dat.Val1();
				if (cluster->IsSubPart() && cluster->GetSubPart()->GetClusts() == 1 && cluster->GetNm() != "copy")
				{
					Assert(cluster->GetSubPart()->GetClust(0)->GetNm() == "copy");
					TBowDocPart *sub_part = cluster->GetSubPart()();
					while (sub_part->GetClusts() == 1 && sub_part->GetClust(0)->IsSubPart()) 
					{	
						sub_part = sub_part->GetClust(0)->GetSubPart()();
					}
					if (sub_part->GetClusts() > 1)
					{
						cluster->DelSubPart();
						// WARNME: would cluster->PutSubPart(sub_part) work properly here (smart pointers issue)?
						// DESC: clone the sub-part of the last cluster copy 
						cluster->PutSubPart(TBowDocPart::New());
						for (int i = 0; i < sub_part->GetClusts(); i++)
						{
							Assert(child_to_parent_map.IsKey(getClustId(sub_part->GetClust(i))));
							child_to_parent_map(getClustId(sub_part->GetClust(i))) = cluster;
							cluster->GetSubPart()->AddClust(sub_part->GetClust(i));
						}
					}
					else
					{
						cluster->DelSubPart();
					}
				}
			}
		}		
	}
	// DESC: create TBowDocPart instance
	Assert(hierarchy.Len() >= 1 && hierarchy[0].Len() == 1);
	bow_doc_part = TBowDocPart::New();
	bow_doc_part->AddClust(hierarchy[0][0].Dat.Val1);
}

TStr getDocKeywords(const PBowDocBs &bow_doc_bs, const int &doc_id, const int &num_keywords)
{
	int num_words = bow_doc_bs->GetDocWIds(doc_id);
	TStr ret_val;
	TVec<TKeyDat<TFlt, TInt> > tmp;
	for (int i = 0; i < num_words; i++)
	{
		double word_fq = 0;
		int word_id = -1;
		bow_doc_bs->GetDocWIdFq(doc_id, i, word_id, word_fq);
		tmp.Add(TKeyDat<TFlt, TInt>(word_fq, word_id));
	}
	tmp.Sort(/*asc=*/false);
	for (int i = 0; i < __min(num_keywords, tmp.Len()); i++)
	{
		if (ret_val != "") { ret_val += ", "; }
		ret_val += bow_doc_bs->GetWordStr(tmp[i].Dat);
	}
	return ret_val;
}

TStr getClusterKeywords(const PBowDocBs &bow_doc_bs, const PBowDocPartClust &cluster, const int &num_keywords)
{
	TStr ret_val;
	THash<TInt, TFlt> tmp0;
	for (int i = 0; i < cluster->GetDocs(); i++)
	{
		int doc_id = cluster->GetDId(i);
		for (int j = 0; j < bow_doc_bs->GetDocWIds(doc_id); j++)
		{
			double word_fq = 0;
			int word_id = -1;
			bow_doc_bs->GetDocWIdFq(doc_id, j, word_id, word_fq);
			if (!tmp0.IsKey(word_id)) { tmp0.AddDat(word_id, 0); }
			tmp0(word_id) += word_fq;
		}
	}
	TFltIntKdV tmp;
	for (int i = 0; i < tmp0.Len(); i++)
	{
		TInt word_id;
		TFlt word_fq;
		tmp0.GetKeyDat(i, word_id, word_fq);
		tmp.Add(TFltIntKd(word_fq, word_id));
	}
	tmp.Sort(/*asc=*/false);
	for (int i = 0; i < __min(num_keywords, tmp.Len()); i++)
	{
		if (ret_val != "") { ret_val += ", "; }
		ret_val += bow_doc_bs->GetWordStr(tmp[i].Dat);
	}
	return ret_val;
}

TStr getClusterConceptKeywords(const PBowDocBs &bow_doc_bs, const PBowDocPartClust &cluster, const int &num_keywords)
{
	PBowSpV sp_v = cluster->GetConceptSpV();
	TFltIntKdV tmp;
	// DESC: re-arrange
	for (int i = 0; i < sp_v->Len(); i++) { tmp.Add(TFltIntKd((float)sp_v->GetWgt(i), sp_v->GetWId(i))); }
	TStr ret_val;
	tmp.Sort(/*asc=*/false);
	for (int i = 0; i < __min(num_keywords, tmp.Len()); i++)
	{
		if (ret_val != "") { ret_val += ", "; }
		ret_val += bow_doc_bs->GetWordStr(tmp[i].Dat);
	}
	return ret_val;
}

void getClusterMedoids(const PBowDocPartClust &cluster, const int &num_docs, TFltIntKdV &doc_wgt_id_v)
{
	doc_wgt_id_v.Clr();
	for (int i = 0; i < cluster->GetDocs(); i++)
	{
		doc_wgt_id_v.Add(TFltIntKd(cluster->GetDCSim(i), cluster->GetDId(i)));
	}
	doc_wgt_id_v.Sort(/*asc=*/false);
	doc_wgt_id_v.Trunc(num_docs);
}

TStr getDocDistinctKeywords(const PBowDocBs &bow_doc_bs, const TBowWordWgtType &word_wgt_type, const double &cut_word_wgt_sum_prc,	
							const int &mn_word_fq, const TIntV &cluster_docs_id_v, int doc_id, int num_keywords)
{
	PBowDocWgtBs bow_doc_wgt_bs = TBowDocWgtBs::New(bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, cluster_docs_id_v);
	PBowSpV sp_v = bow_doc_wgt_bs->GetSpV(doc_id);
	TFltIntKdV tmp;
	// DESC: re-arrange
	for (int i = 0; i < sp_v->Len(); i++) { tmp.Add(TFltIntKd((float)sp_v->GetWgt(i), sp_v->GetWId(i))); }
	TStr ret_val;
	tmp.Sort(/*asc=*/false);
	for (int i = 0; i < __min(num_keywords, tmp.Len()); i++)
	{
		if (ret_val != "") { ret_val += ", "; }
		ret_val += bow_doc_bs->GetWordStr(tmp[i].Dat);
	}
	return ret_val;
}

int classifyWithRetry(const int &onto_service_stub_id, const TStr &txt, const int &num_categories, const int &num_retries = 3, 
					  const int &delay_between_retries = 3000)
{
	int retry = 0;
	while (retry <= num_retries)
	{
		try
		{
			int result_id = classify(onto_service_stub_id, NULL, txt.CStr(), num_categories, /*kwd_tsh=*/0);
			if (result_id == -1) { throw -1; }
			return result_id;
		}
		catch (...)
		{
			Sleep(delay_between_retries); 
			retry++;
		}
	}
	return -1;
}

void createCategoryStats(const PBowDocPartClust &cluster, const PBowDocBs &bow_doc_bs, TCategoryStats &stats, const int &onto_service_stub_id,
						 const int &num_medoids, const int &num_categories)
{
	TFltIntKdV medoid_wgt_id_v;
	getClusterMedoids(cluster, num_medoids, medoid_wgt_id_v);
	stats.reset();
	for (int i = 0; i < medoid_wgt_id_v.Len(); i++)
	{
		//cout << "*** MEDOID " << i + 1 << " ***" << endl;
		TStr doc_str = bow_doc_bs->GetDocStr(medoid_wgt_id_v[i].Dat);
		double medoid_wgt = (double)medoid_wgt_id_v[i].Key;
		//cout << "MEDOID WGT: " << medoid_wgt << endl;
		if (doc_str != "") 
		{
			//cout << "(((" << doc_str.CStr() << ")))" << endl;
			int result_id = classifyWithRetry(onto_service_stub_id, doc_str, num_categories);
			if (result_id != -1)
			{
				for (int j = 0; j < getNumCategories(result_id); j++)
				{
					double weight = getCategoryWeight(result_id, j);
					STRING category = getCategoryStr(result_id, j);
					//cout << weight << "\t" << category << endl;
					stats.add(medoid_wgt_id_v[i].Dat, medoid_wgt * weight, TStr(category));
					GlobalFree((HGLOBAL)category);
				}
			}
		}
	}
	stats.updateStats();
}

void createHtml(const TSimClustParentKdVV &hierarchy, const PBowDocBs &bow_doc_bs, const TBowWordWgtType &word_wgt_type, const double &cut_word_wgt_sum_prc,	
				const int &mn_word_fq, TStr html_dir, /*const*/ THash<TInt, PBowDocPartClust> &child_to_parent_map, const int &num_keywords)
{
	if (html_dir.LastCh() != '\\') { html_dir += "\\"; }
	for (int lvl = 0; lvl < hierarchy.Len(); lvl++)
	{
		for (int clust = 0; clust < hierarchy[lvl].Len(); clust++)
		{
			TBowDocPartClust *cluster = hierarchy[lvl][clust].Dat.Val1();
			TStr cluster_id = getClustInfo(hierarchy[lvl][clust].Dat.Val1, "Id");
			if (cluster->GetNm() == "copy") { continue; }
			int clust_id = getClustId(hierarchy[lvl][clust].Dat.Val1);
			TBowDocPartClust *parent = child_to_parent_map.IsKey(clust_id) ? child_to_parent_map(clust_id)() : NULL;
			TFOut html_fl(html_dir + cluster_id + ".htm");
			html_fl.PutStrLn("<html>");
			html_fl.PutStrLn("<head>");
			html_fl.PutStrLn(TStr::Fmt("<title>%s</title>", cluster_id.CStr()));
			html_fl.PutStrLn("</head>");
			html_fl.PutStrLn("<body>");
			if (parent != NULL)
			{
				html_fl.PutStrLn(TStr::Fmt("<p><h1><a href=\"%s.htm\">..</a>/%s</h1></p>", getClustInfo(parent, "Id").CStr(), cluster_id.CStr()));
			}
			else
			{
				html_fl.PutStrLn(TStr::Fmt("<p><h1>%s</h1></p>", cluster_id.CStr()));
			}
			if (cluster->IsSubPart())
			{
				html_fl.PutStrLn("<hr>");
				html_fl.PutStrLn("<p><h2>Subcategories</h2></p>");
				html_fl.PutStrLn("<ul>");
				for (int i = 0; i < cluster->GetSubPart()->GetClusts(); i++)
				{
					TStr keywords = getClustInfo(cluster->GetSubPart()->GetClust(i), "Keywords");
					TStr concept_keywords = getClustInfo(cluster->GetSubPart()->GetClust(i), "ConceptKeywords");
					TStr child_id = getClustInfo(cluster->GetSubPart()->GetClust(i), "Id");
					html_fl.PutStrLn(TStr::Fmt("<li><a href=\"%s\">%s</a> (%f)<br>", (child_id + ".htm").CStr(), 
						child_id.CStr(), cluster->GetSubPart()->GetClust(i)->GetMeanSim())); 
					html_fl.PutStrLn(TStr::Fmt("<font size=\"2\">Talking about %s...<br>", keywords.CStr())); 
					html_fl.PutStr(TStr::Fmt("Concept keywords: %s...<br>", concept_keywords.CStr())); 
					TStr category = getClustInfo(cluster->GetSubPart()->GetClust(i), "Category");
					TStr ext_1 = getClustInfo(cluster->GetSubPart()->GetClust(i), "CategoryExt1");
					TStr ext_2 = getClustInfo(cluster->GetSubPart()->GetClust(i), "CategoryExt2");
					TStr onto_keywords = getClustInfo(cluster->GetSubPart()->GetClust(i), "OntoKeywords");
					html_fl.PutStrLn(TStr::Fmt("Classification: %s<font color=gray>%s</font><font color=silver>%s</font><br>", 
						category.CStr(), ext_1.CStr(), ext_2.CStr()));
					html_fl.PutStrLn(TStr::Fmt("Onto-keywords: %s...</font></li>", onto_keywords.CStr()));
				}
				html_fl.PutStrLn("</ul>");
			}
			html_fl.PutStrLn("<hr>");
			html_fl.PutStrLn("<p><h2>Documents</h2></p>");
			html_fl.PutStrLn("<ul>");
			for (int i = 0; i < cluster->GetDocs(); i++)
			{
				int doc_id = cluster->GetDId(i);
				TStr doc_nm = bow_doc_bs->GetDocNm(doc_id);
				TStr doc_desc = bow_doc_bs->GetDocDescStr(doc_id);
				TStr doc_str = bow_doc_bs->GetDocStr(doc_id);
				html_fl.PutStrLn(TStr::Fmt("<li>%s<br>", doc_nm.CStr()));
				//html_fl.PutStrLn(TStr::Fmt("<font size=\"2\">Desc: %s<br>", doc_desc.CStr()));
				//html_fl.PutStrLn(TStr::Fmt("Str: %s<br>", doc_str.CStr()));
				//html_fl.PutStrLn(TStr::Fmt("<font size=\"2\">Talking about %s...<br>", getDocKeywords(bow_doc_bs, doc_id, num_keywords).CStr()));
				//html_fl.PutStrLn(TStr::Fmt("Distinctive keywords: %s...</font></li>", 
					//getDocDistinctKeywords(bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, cluster->GetDIdVRef(), doc_id, num_keywords).CStr()));
				//html_fl.PutStrLn(TStr::Fmt("Distinctive keywords (global): %s...</font></li>", 
				//	getDocDistinctKeywords(bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, TIntV(), doc_id, num_keywords).CStr()));
			}
			html_fl.PutStrLn("</ul>");
			html_fl.PutStrLn("<hr>");
			if (parent != NULL)
			{
				html_fl.PutStrLn("<p><a href=\"root_clust.htm\">back to root</a></p>");
			}
			html_fl.PutStrLn("</body>");
			html_fl.PutStrLn("</html>");
		}
	}
}

void getNextLevel(const PNotify &notify,
				  const TSimClustParentKdV &clusters, 
				  const double &required_intra_sim, 
				  const double &leaf_intra_sim,
				  const double &next_lvl_leaf_intra_sim,
				  const TClustOptions &options,	
				  TSimClustParentKdV &next_level,
				  const PBowDocBs &bow_doc_bs,
				  const PBowSim &bow_sim,
				  TRnd &rnd,
				  const int &clust_trials,
				  const double &converg_eps,
				  const TBowWordWgtType &word_wgt_type,
				  const double &cut_word_wgt_sum_prc,	
				  const int &mn_word_fq,					
				  const PBowDocWgtBs &_bow_doc_wgt_bs,
				  int &id,
				  bool &finished)
{
	Assert(clusters.Len() > 0);
	next_level = TSimClustParentKdV();
	PBowDocWgtBs bow_doc_wgt_bs;
	finished = true;
	// DESC: split/copy clusters 
	for (int i = 0; i < clusters.Len(); i++) 
	{
		TBowDocPartClust *cluster = clusters[i].Dat.Val1();
		if ((options & coCOPY_INSTEADOF_SPLIT) != 0)
		{
			if (cluster->GetMeanSim() < leaf_intra_sim)
			{
				PBowDocPartClust tmp = new TBowDocPartClust(); *tmp = *cluster;
				tmp->PutNm("copy");
				next_level.Add(TSimClustParentKd(clusters[i].Key, TClustParentPr(tmp, cluster)));
			}
		}
		else
		{
			if (cluster->GetMeanSim() < leaf_intra_sim && cluster->GetDocs() >= 2)
			{
				if (_bow_doc_wgt_bs.Empty())
				{
					bow_doc_wgt_bs = TBowDocWgtBs::New(bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, cluster->GetDIdVRef());
				}
				else
				{
					bow_doc_wgt_bs = _bow_doc_wgt_bs->GetSubSet(cluster->GetDIdVRef());
				}
				PBowDocPart part = TBowClust::GetKMeansPartForDocWgtBs(notify, bow_doc_wgt_bs, bow_doc_bs, bow_sim, rnd, 2, clust_trials, converg_eps, 1, true);
				finished = false;
				Assert(part->GetClusts() == 2);
				PBowDocPartClust tmp = new TBowDocPartClust(); *tmp = *part->GetClust(0);
				tmp->PutNm(TStr::Fmt("(Id)%s(/Id)", TInt::GetStr(id++).CStr()));
				next_level.Add(TSimClustParentKd(tmp->GetMeanSim(), TClustParentPr(tmp, cluster)));
				tmp = new TBowDocPartClust(); *tmp = *part->GetClust(1);
				tmp->PutNm(TStr::Fmt("(Id)%s(/Id)", TInt::GetStr(id++).CStr()));
				next_level.Add(TSimClustParentKd(tmp->GetMeanSim(), TClustParentPr(tmp, cluster)));
			}
		}
	}	
	if (next_level.Len() == 0) { return; }
	// DESC: main loop
	while (true)
	{
		if ((options & coMIN_INSTEADOF_AVG) != 0)
		{
			// DESC: check min intra-sim of the clusters
			double intra_sim_min = TFlt::Mx;
			for (int i = 0; i < next_level.Len(); i++)
			{
				if ((double)next_level[i].Key < intra_sim_min) { intra_sim_min = next_level[i].Key; }
			}
			if (intra_sim_min >= required_intra_sim) { return; }
		}
		else
		{
			// DESC: check avg intra-sim of the clusters
			double intra_sim_sum = 0;
			for (int i = 0; i < next_level.Len(); i++)
			{
				intra_sim_sum += (double)next_level[i].Key;
			}
			double intra_sim_avg = intra_sim_sum == 0 ? 0 : intra_sim_sum / (double)next_level.Len();
			if (intra_sim_avg >= required_intra_sim) { return; }
		}
		// DESC: sort clusters according to their intra-sim
		next_level.Sort(/*asc=*/true); // WARNME: get min would be sufficient here (...but then you need to change Del(0) below)
		// DESC: split the most dirty cluster
		TBowDocPartClust *dirty_cluster = next_level[0].Dat.Val1();
		TBowDocPartClust *dirty_cluster_parent = next_level[0].Dat.Val2();
		cout << dirty_cluster->GetMeanSim() << " vs " << next_lvl_leaf_intra_sim << endl;
		if (((options & coLEAF_CRITERION_PRECEDENCE) == 0 || dirty_cluster->GetMeanSim() < next_lvl_leaf_intra_sim) && dirty_cluster->GetDocs() >= 2)
		{
			if (_bow_doc_wgt_bs.Empty())
			{
				bow_doc_wgt_bs = TBowDocWgtBs::New(bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, dirty_cluster->GetDIdVRef());
			}
			else
			{
				bow_doc_wgt_bs = _bow_doc_wgt_bs->GetSubSet(dirty_cluster->GetDIdVRef());
			}
			PBowDocPart part = TBowClust::GetKMeansPartForDocWgtBs(notify, bow_doc_wgt_bs, bow_doc_bs, bow_sim, rnd, 2, clust_trials, converg_eps, 1, true);
			finished = false;
			Assert(part->GetClusts() == 2);
			PBowDocPartClust tmp = new TBowDocPartClust(); *tmp = *part->GetClust(0);
			tmp->PutNm(TStr::Fmt("(Id)%s(/Id)", TInt::GetStr(id++).CStr()));
			next_level.Add(TSimClustParentKd(tmp->GetMeanSim(), TClustParentPr(tmp, dirty_cluster_parent)));
			tmp = new TBowDocPartClust(); *tmp = *part->GetClust(1);
			tmp->PutNm(TStr::Fmt("(Id)%s(/Id)", TInt::GetStr(id++).CStr()));
			next_level.Add(TSimClustParentKd(tmp->GetMeanSim(), TClustParentPr(tmp, dirty_cluster_parent)));
			next_level.Del(0);
		}
		else
		{
			return;
		}
	}
}

double requiredIntraSim(int level)
{
	return __min(SplitCritSlope * (double)level, 1);
}

double requiredLeafIntraSim(int level)
{
	return __max(LeafCritIntrasim + LeafCritSlope * (double)level, 0);
}

void getHierarchy(const PBowDocBs &bow_doc_bs,
				  TSimClustParentKdVV &hierarchy,
				  PBowDocPart &bow_doc_part,
				  THash<TInt, PBowDocPartClust> &child_to_parent_map,				  
				  const double &split_crit_slope,
				  const double &leaf_crit_isim,
				  const double &leaf_crit_slope,
				  const TClustOptions &options,
				  const PNotify &notify,
				  const PBowSim &bow_sim,
				  TRnd &rnd,
				  const int &clust_trials,
				  const double &converg_eps,				
				  const TBowWordWgtType &word_wgt_type,
				  const double &cut_word_wgt_sum_prc,
				  const int &mn_word_fq,
				  const TIntV &_doc_id_v)
{
	// DESC: set criteria
	SplitCritSlope   = split_crit_slope;
	LeafCritIntrasim = leaf_crit_isim;
	LeafCritSlope    = leaf_crit_slope;
    // DESC: create document-id vector
	TIntV doc_id_v;
	if (_doc_id_v.Empty()) { bow_doc_bs->GetAllDIdV(doc_id_v); } else { doc_id_v = _doc_id_v; }
	// DESC: compute weights
	PBowDocWgtBs bow_doc_wgt_bs = TBowDocWgtBs::New(bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, doc_id_v);
	// DESC: create root cluster and init the hierarchy
	PBowDocPartClust root = TBowDocPartClust::New(bow_doc_bs, "(Id)root_clust(/Id)", 0, doc_id_v, TBowClust::GetConceptSpV(bow_doc_wgt_bs, bow_sim, doc_id_v), NULL);
	hierarchy = TSimClustParentKdVV();
	// DESC: get the hierarchy level by level
	bool propagate_weights = (options & coPROPAGATE_WEIGHTS) != 0;
	int level = 0;
	int id = 0;
	TSimClustParentKdV next_level_clusters = TSimClustParentKdV() + TSimClustParentKd(0, TClustParentPr(root, NULL));
	bool finished = true;
	do
	{
		level++;
		STATUS(TStr::Fmt("*** LEVEL %d ***", level));
		hierarchy.Add(next_level_clusters);
		getNextLevel(notify, hierarchy.Last(), requiredIntraSim(level), requiredLeafIntraSim(level - 1), requiredLeafIntraSim(level), 
			options, next_level_clusters, bow_doc_bs, bow_sim, rnd, clust_trials, converg_eps, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, 
			propagate_weights ? bow_doc_wgt_bs : NULL, id, finished);	
	} while (!finished);

	buildBowDocPart(hierarchy, child_to_parent_map, options, bow_doc_part, bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, bow_sim);
	
	if ((options & coREFINE) != 0) 
	{
		// DESC: refine hierarchy
		STATUS("Refining...");
		refine(hierarchy, child_to_parent_map, bow_doc_wgt_bs, bow_sim, bow_doc_bs);
	}
	
	// DESC: update hierarchy
	STATUS("Updating hierarchy...");
	if (!propagate_weights)
	{
		bow_doc_part->Update(NULL, bow_doc_bs, word_wgt_type, cut_word_wgt_sum_prc, mn_word_fq, bow_sim);
	}
	else
	{
		bow_doc_part->Update(bow_doc_bs, bow_doc_wgt_bs, bow_sim);
	}
	STATUS("Done.");
}

void classifyClusters(const TSimClustParentKdVV &hierarchy, const PBowDocBs &bow_doc_bs, const int &onto_service_stub_id,
					  const int &num_medoids, const int &num_categories, const int &num_onto_keywords)
{
	for (int lvl = 0; lvl < hierarchy.Len(); lvl++)
	{
		for (int clust = 0; clust < hierarchy[lvl].Len(); clust++)
		{
			TBowDocPartClust *cluster = hierarchy[lvl][clust].Dat.Val1();
			if (cluster->GetNm() == "copy") { continue; }
			TCategoryStats stats;
			STATUS(TStr::Fmt("*** CLASSIFYING CLUSTER %s ***", getClustInfo(cluster, "Id").CStr()));
			createCategoryStats(cluster, bow_doc_bs, stats, onto_service_stub_id, num_medoids, num_categories); 
			TStr best_match, ext_1, ext_2;
			double best_match_wgt, ext1_wgt, ext2_wgt;
			stats.getBestMatch(best_match, best_match_wgt, ext_1, ext1_wgt, ext_2, ext2_wgt);
			if (ext_2 != "") { ext_2 = ext_2.GetSubStr(ext_1.Len(), ext_2.Len() - 1); }
			if (ext_1 != "") { ext_1 = ext_1.GetSubStr(best_match.Len(), ext_1.Len() - 1); }
			TStr onto_keywords = stats.getKeywords(num_onto_keywords, TStrV());
			cluster->PutNm(TStr::Fmt("%s(Category)%s(/Category)(CategoryWgt)%f(/CategoryWgt)(CategoryExt1)%s(/CategoryExt1)(CategoryExt1Wgt)%f(/CategoryExt1Wgt)(CategoryExt2)%s(/CategoryExt2)(CategoryExt2Wgt)%f(/CategoryExt2Wgt)(OntoKeywords)%s(/OntoKeywords)", 
			 cluster->GetNm().CStr(), best_match.CStr(), best_match_wgt, ext_1.CStr(), ext1_wgt, ext_2.CStr(), ext2_wgt, onto_keywords.CStr()));
		}
	}
}

void describeClusters(const TSimClustParentKdVV &hierarchy, const PBowDocBs &bow_doc_bs, const int &num_keywords)
{
	for (int lvl = 0; lvl < hierarchy.Len(); lvl++)
	{
		for (int clust = 0; clust < hierarchy[lvl].Len(); clust++)
		{
			TBowDocPartClust *cluster = hierarchy[lvl][clust].Dat.Val1();
			if (cluster->GetNm() == "copy") { continue; }
			TStr keywords = getClusterKeywords(bow_doc_bs, cluster, num_keywords);
			TStr concept_keywords = getClusterConceptKeywords(bow_doc_bs, cluster, num_keywords);
			cluster->PutNm(TStr::Fmt("%s(Keywords)%s(/Keywords)(ConceptKeywords)%s(/ConceptKeywords)", 
				cluster->GetNm().CStr(), keywords.CStr(), concept_keywords.CStr()));
		}
	}
}