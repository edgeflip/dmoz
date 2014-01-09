#include <stdio.h>
#include <assert.h>
#include <base.h>
#include <mine.h>

class NB_AL {
public:
	PBowDocBs Bow;
	TVec<TInt> cat;					// razred i-tega primera -1/0/1 negative/unknown/positive

	double uncert;					// target probability for uncertainty sampling
	int wordsN, Docs;				// stevilo besed, dokumentov
	TInt pos,neg;					// stevilo pozitivnih in negativnih primerov
	TFlt p, loglike0;				// verjetnost pozitivnega razreda
	TVec<TInt> posFreq, negFreq;	// st. pojavitev i-te besede v pozitivnih oz. negativnih primerih
	TVec<TFlt> loglike;
	TRnd rnd;
	
	NB_AL() {}
	NB_AL(PBowDocBs BowDocBsX, TIntV posSeed, TIntV negSeed, TFlt us=0.5) {
		Bow = BowDocBsX;
		Docs = Bow->GetDocs(); wordsN = Bow->GetWords();
		posFreq = TVec<TInt>(wordsN); negFreq = TVec<TInt>(wordsN); cat = TVec<TInt>(Docs); loglike = TVec<TFlt>(wordsN);
		posFreq.PutAll(0); negFreq.PutAll(0); cat.PutAll(0); loglike.PutAll(0);
		pos=1; neg=1; uncert=us;
		for (int i=0;i<posSeed.Len();i++) put(posSeed[i],1);
		for (int i=0;i<negSeed.Len();i++) put(negSeed[i],0);
	}

	NB_AL(TSIn& SIn): Bow(SIn), cat(SIn) {
		init(); calc();
	}

	NB_AL(PBowDocBs pbow, TSIn& SIn): cat(SIn) {
		Bow=pbow;
		init(); calc();
	}

	void init() {
		Docs = Bow->GetDocs(); wordsN = Bow->GetWords();
		posFreq = TVec<TInt>(wordsN); negFreq = TVec<TInt>(wordsN);
		posFreq.PutAll(0); negFreq.PutAll(0);
		pos=1; neg=1; uncert=0.5;
		loglike = TVec<TFlt>(wordsN); loglike.PutAll(0);
	}

	void calc() {
		for (int doc=0;doc<Docs;doc++) if (cat[doc]!=0) {
			if (cat[doc]==-1) neg++; else pos++;
			for (int j=0;j<Bow->GetDocWIds(doc);j++) {
				int id = Bow->GetDocWId(doc,j);
				if (cat[doc]==1) posFreq[id]++; else negFreq[id]++;
			}
		}
		calcLogLike();
	}

	void Save(TSOut& SOut) {
		Bow.Save(SOut);
		SaveCat(SOut);
	}

	void SaveCat(TSOut& SOut) {
		cat.Save(SOut);
	}

	void calcLogLike() {
		p = (double)pos/(pos+neg); loglike0 = log(p/(1-p));
		for (int id=0;id<Bow->GetWords();id++) {
			double posi = ((double)posFreq[id]+p*2)/pos;
			double negi = ((double)negFreq[id]+(1-p)*2)/neg;
			loglike[id]=log(posi/negi);
		}
	}

	void put(int doc, int c) {
		assert(c==0 || c==1);
		c=2*c-1;
		if (doc<0 || doc>=Bow->GetDocs()) return;
		cat[doc]=c;
		if (c==1) pos++; else neg++;
		for (int i=0;i<Bow->GetDocWIds(doc);i++) {
			int id=Bow->GetDocWId(doc,i);
			if (cat[doc]==1) posFreq[id]++; else negFreq[id]++;
		}
		calcLogLike();
	}

	int query() {
		double bestP=-1;
		int bestId=-1;
		for (int i=0;i<min(Docs,1000000);i++) {
			int id=rnd.GetUniDevInt(Docs);
			if (cat[id]!=0) { continue; }
			double p = get(id);
			if (abs(uncert-p)<abs(uncert-bestP)) { bestP=p; bestId=id; }
		}
		return bestId;
	}

	double get(int doc) {
		double like = loglike0;
		for (int j=0;j<Bow->GetDocWIds(doc);j++) {
			int id = Bow->GetDocWId(doc,j);
			like += loglike[id];
		}
		return exp(like)/(1+exp(like));
	}
};

class NB_AL_Senti {
public:
	PBowDocBs Bow;
	NB_AL NBp, NBn, NBo;
	TInt qCount;

	NB_AL_Senti() {}
	NB_AL_Senti(PBowDocBs BowDocBs0, TIntV posEx, TIntV negEx, TIntV objEx) {
		TIntV posNegEx = posEx; posNegEx.AddV(negEx);
		TIntV posObjEx = posEx; posObjEx.AddV(objEx);
		TIntV negObjEx = negEx; negObjEx.AddV(objEx);
		NBp = NB_AL(BowDocBs0, posEx, negObjEx);
		NBn = NB_AL(BowDocBs0, negEx, posObjEx);
		NBo = NB_AL(BowDocBs0, objEx, posNegEx);
		qCount = 0;
	}

	NB_AL_Senti(TSIn& SIn) { // load
		Bow = PBowDocBs(SIn);
		qCount = TInt(SIn);
		NBp = NB_AL(Bow, SIn); NBn = NB_AL(Bow, SIn); NBo = NB_AL(Bow, SIn);
	}

	void Save(TSOut& SOut) { // save
		NBp.Bow.Save(SOut);
		qCount.Save(SOut);
		NBp.SaveCat(SOut); NBn.SaveCat(SOut); NBo.SaveCat(SOut);
	}
	
	void put(int id, int c) {
		if (c==-1) {		NBp.put(id,0); NBn.put(id,1); NBo.put(id,0); } 
		else if (c==1) {	NBp.put(id,1); NBn.put(id,0); NBo.put(id,0); } 
		else {				NBp.put(id,0); NBn.put(id,0); NBo.put(id,1); }
	}

	int query() {
		qCount++;
		if (qCount%3==0) return NBp.query();
		else if (qCount%3==1) return NBn.query();
		else return NBo.query();
	}

	TPair<TFlt, TInt> get(int id) {
		double pP = NBp.get(id);
		double pN = NBn.get(id);
		double pO = NBo.get(id);
		if (pP>=pN && pP>=pO) return TPair<TFlt,TInt>(pP,1);
		if (pN>=pP && pN>=pO) return TPair<TFlt,TInt>(pN,-1);
		return TPair<TFlt,TInt>(pO,0);
	}
};


void readLines(TStr InF, TStrV &v) {
	PSIn SIn = TFIn::New(InF);
	TStr line;
	while (SIn->GetNextLn(line)) v.Add(line);
}

void addDocs(TStr InF, PBowDocBs bow, TIntV &v) {
	TStrV ex;
	readLines(InF,ex);
	for (int i=0; i<ex.Len(); i++) {
		int DocN = bow->GetDocs();
		bow->AddHtmlDoc(TInt::GetStr(DocN), TStrV(), ex[i].GetUc(), true);
		v.Add(DocN);
	}
}

void output(TVec<TPair<TFlt, TStr> > &seq, TSOut &SOut) {
	for (int i=0;i<seq.Len();i++) SOut.PutStrLn(seq[i].Val2);
}

int main(int argc, char* argv[]) {
	Env=TEnv(argc, argv, TNotify::StdNotify);
	// command line parameters
	Env.PrepArgs("Naive Bayes - Active Learning");
	bool senti=Env.GetIfArgPrefixBool("-senti:", false, "Sentiment-Classifiaction");
	TStr InF=Env.GetIfArgPrefixStr("-in:", "", "Input-File");
	TStr InFPos=Env.GetIfArgPrefixStr("-pos:", "", "Positive-Seed-File");
	TStr InFNeg=Env.GetIfArgPrefixStr("-neg:", "", "Negative-Seed-File");
	TStr InFObj=Env.GetIfArgPrefixStr("-obj:", "", "Neutral-Seed-File");
	TStr InFDat=Env.GetIfArgPrefixStr("-state:", "", "Load-State-File");
	TStr InFBow=Env.GetIfArgPrefixStr("-bow:", "", "Load-Only-Bow-From-State-File");
	TFlt InUncert=Env.GetIfArgPrefixFlt("-uncert:", 0.5, "Uncertainty-Sampling");
	if (Env.IsEndOfRun()){return 0;}

	/*
	-senti -in:senti.txt -pos:pos.txt -neg:neg.txt -obj:obj.txt
	-senti -state:state.dat
	-in:topic_in.txt -pos:topic_pos.txt -neg:topic_neg.txt
	-state:state.dat -uncert 0.6
	-bow:state.dat -pos:topic_pos.txt -neg:topic_neg.txt
	*/

	TStrV DocV;
	PBowDocBs BowDocBs;
	PSwSet SwSet = TSwSet::New(swstEn523);
	PStemmer Stemmer = TStemmer::New(stmtPorter, true);

	if (senti) { // sentiment classification
		printf("Sentiment classification\n");
		NB_AL_Senti nbs;

		if (InFDat.Empty() && InFBow.Empty()) { // new
			if (InF.Empty()) { printf("Missing input file\n"); return 0; }
			if (InFPos.Empty()) { printf("Missing positive seed\n"); return 0; }
			if (InFNeg.Empty()) { printf("Missing negative seed\n"); return 0; }
			if (InFObj.Empty()) { printf("Missing neutral seed\n"); return 0; }

			BowDocBs = TBowDocBs::New(SwSet, Stemmer, NULL);
			readLines(InF,DocV);
			for (int DocN = 0; DocN < DocV.Len(); DocN++) {
				BowDocBs->AddHtmlDoc(TInt::GetStr(DocN), TStrV(), DocV[DocN].GetUc(), true);
			}
			TIntV posEx, negEx, objEx;
			addDocs(InFPos,BowDocBs,posEx);
			addDocs(InFNeg,BowDocBs,negEx);
			addDocs(InFObj,BowDocBs,objEx);
			nbs = NB_AL_Senti(BowDocBs,posEx,negEx,objEx);

		} else if (!InFBow.Empty()) { // load bow
			BowDocBs = PBowDocBs(TFIn(InFBow));

			if (InFPos.Empty()) { printf("Missing positive seed\n"); return 0; }
			if (InFNeg.Empty()) { printf("Missing negative seed\n"); return 0; }
			if (InFObj.Empty()) { printf("Missing neutral seed\n"); return 0; }
			TIntV posEx, negEx, objEx;
			addDocs(InFPos,BowDocBs,posEx);
			addDocs(InFNeg,BowDocBs,negEx);
			addDocs(InFObj,BowDocBs,objEx);
			nbs = NB_AL_Senti(BowDocBs,posEx,negEx,objEx);

		} else { // load
			nbs = NB_AL_Senti(TFIn(InFDat));
			BowDocBs = nbs.Bow;
		}

		int stop=0;
		while (!stop) {
			int id = nbs.query();
			if (id==-1) { printf("done\n"); break; }
			printf("%s\n",BowDocBs->GetDocStr(id).CStr());
			while (1) {
				printf("[p]ositive/[n]egative/[o]bjective/[b]reak: ");
				char x;
				scanf(" %c",&x);
				if (x=='p') { nbs.put(id,1); break; }
				else if (x=='n') { nbs.put(id,-1); break; }
				else if (x=='o') { nbs.put(id,0); break; }
				else if (x=='b') { stop=1; break; }
				else printf("Invalid option\n");
			}
		}

		// save
		nbs.Save(TFOut("state.dat"));
		TVec<TPair<TFlt, TStr> > pos, neg, obj;
		for (int id=0;id<BowDocBs->GetDocs();id++) {
			TPair<TFlt, TInt> prediction = nbs.get(id);
			if (prediction.Val2==0) obj.Add(TPair<TFlt,TStr>(prediction.Val1, BowDocBs->GetDocStr(id)));
			if (prediction.Val2==1) pos.Add(TPair<TFlt,TStr>(prediction.Val1, BowDocBs->GetDocStr(id)));
			if (prediction.Val2==-1) neg.Add(TPair<TFlt,TStr>(prediction.Val1, BowDocBs->GetDocStr(id)));
		}
		pos.Sort(false); neg.Sort(false); obj.Sort(false);
		output(pos,TFOut("pos.txt")); output(neg,TFOut("neg.txt")); output(obj,TFOut("obj.txt"));
		printf("Classifications saved to pos.txt, neg.txt, obj.txt\n");


	} else { // topic classification
		printf("Topic classification\n");
		NB_AL nb;

		if (InFDat.Empty() && InFBow.Empty()) { // new
			if (InF.Empty()) { printf("Missing input file\n"); return 0; }
			if (InFPos.Empty()) { printf("Missing positive seed\n"); return 0; }
			if (InFNeg.Empty()) { printf("Missing negative seed\n"); return 0; }

			BowDocBs = TBowDocBs::New(SwSet, Stemmer, NULL);
			readLines(InF,DocV);
			for (int DocN = 0; DocN < DocV.Len(); DocN++) {
				BowDocBs->AddHtmlDoc(TInt::GetStr(DocN), TStrV(), DocV[DocN].GetUc(), true);
			}
			TIntV posEx, negEx, objEx;
			addDocs(InFPos,BowDocBs,posEx);
			addDocs(InFNeg,BowDocBs,negEx);
			nb = NB_AL(BowDocBs, posEx, negEx, InUncert);

		} else if (!InFBow.Empty()) { // load just bow
			BowDocBs = PBowDocBs(TFIn(InFBow));

			if (InFPos.Empty()) { printf("Missing positive seed\n"); return 0; }
			if (InFNeg.Empty()) { printf("Missing negative seed\n"); return 0; }
			TIntV posEx, negEx, objEx;
			addDocs(InFPos,BowDocBs,posEx);
			addDocs(InFNeg,BowDocBs,negEx);
			nb = NB_AL(BowDocBs, posEx, negEx, InUncert);

		} else { // load
			nb = NB_AL(TFIn(InFDat));
			nb.uncert = InUncert;
			BowDocBs = nb.Bow;
		}

		int stop=0;
		while (!stop) {
			int id = nb.query();
			if (id==-1) { printf("done\n"); break; }
			printf("%s\n",BowDocBs->GetDocStr(id).CStr());
			while (1) {
				printf("[p]ositive/[n]egative/[b]reak: ");
				char x;
				scanf(" %c",&x);
				if (x=='p') { nb.put(id,1); break; }
				else if (x=='n') { nb.put(id,0); break; }
				else if (x=='b') { stop=1; break; }
				else printf("Invalid option\n");
			}
		}

		// save
		nb.Save(TFOut("state.dat"));
		TVec<TPair<TFlt, TStr> > pos, neg;
		for (int id=0;id<BowDocBs->GetDocs();id++) {
			TFlt p = nb.get(id);
			if (p>0.6) pos.Add(TPair<TFlt,TStr>(p, BowDocBs->GetDocStr(id)));
			else neg.Add(TPair<TFlt,TStr>(1-p, BowDocBs->GetDocStr(id)));
		}
		pos.Sort(false); neg.Sort(false);
		output(pos,TFOut("topic.txt")); output(neg,TFOut("nottopic.txt"));
		printf("Classifications saved to topic.txt, nottopic.txt\n");
	}

	return 0;
}