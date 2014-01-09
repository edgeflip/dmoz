#include "windows.h"     
#include "stdio.h"

//#define DLLExport extern "C" __declspec(dllexport)
#ifdef TEXTGARDENLIB_EXPORTS
#define DLLExport extern "C" __declspec(dllexport)
#else
#define DLLExport extern "C" __declspec(dllimport)
#endif

/////////////////////////////////////////////////
// Global
DLLExport void DelCStr(char* CStr);

DLLExport void SetVerbosity(int VerbosityLev);
DLLExport int GetVerbosity();

/////////////////////////////////////////////////
// Notifier
//DLLExport void Notify_PutCallback(void* CallbackF);
//DLLExport bool Notify_IsCallback();
//DLLExport void* Notify_GetCallback();
//DLLExport void Notify_DelCallback();
//DLLExport char* Notify_GetMsg();

/////////////////////////////////////////////////
// Strings
DLLExport int CStr_GetStrs();
DLLExport int CStr_GetStrV();

/////////////////////////////////////////////////
// Memory
DLLExport int Mem_Gen();
DLLExport int Mem_GenFromStr(char* Str);
DLLExport int Mem_GenFromMemory(void* MemoryPt, int MemoryLen);
DLLExport void Mem_Del(int MemId);
DLLExport void Mem_Clr(int MemId);
DLLExport int Mem_GetLen(int MemId);
DLLExport void Mem_AddVal(int MemId, char Val);
DLLExport char Mem_GetVal(int MemId, int ValN);
DLLExport char* Mem_GetMemoryPt(int MemId);
DLLExport char* Mem_GetAsStr(int MemId);

DLLExport int Mem_Load(int SInId);
DLLExport void Mem_Save(int MemId, int SOutId);

/////////////////////////////////////////////////
// Integer-Vector
DLLExport int IntV_Gen();
DLLExport void IntV_Del(int IntVId);
DLLExport int IntV_GetLen(int IntVId);
DLLExport int IntV_AddVal(int IntVId, int Val);
DLLExport int IntV_GetVal(int IntVId, int ValN);
DLLExport void IntV_Sort(int IntVId, bool Asc);

DLLExport int IntV_Load(int SInId);
DLLExport void IntV_Save(int IntVId, int SOutId);

/////////////////////////////////////////////////
// String-Vector
DLLExport int StrV_Gen();
DLLExport void StrV_Del(int StrVId);
DLLExport int StrV_GetLen(int StrVId);
DLLExport int StrV_AddVal(int StrVId, char* Val);
DLLExport char* StrV_GetVal(int StrVId, int ValN);
DLLExport void FSPrV_Sort(int StrVId, bool Asc);

DLLExport int StrV_Load(int SInId);
DLLExport void StrV_Save(int StrVId, int SOutId);

/////////////////////////////////////////////////
// Float-String-Pair-Vector
DLLExport int FSPrV_Gen();
DLLExport void FSPrV_Del(int FSPrVId);
DLLExport int FSPrV_GetLen(int FSPrVId);
DLLExport int FSPrV_AddVal(int FSPrVId, double Flt, char* Str);
DLLExport double FSPrV_GetFltVal(int FSPrVId, int ValN);
DLLExport char* FSPrV_GetStrVal(int FSPrVId, int ValN);
DLLExport void FSPrV_Sort(int FSPrVId, bool Asc);
DLLExport int FSPrV_GetTopVal(int FSPrVId, double WgtPrc, int MxVals, bool UseNegWgt);

DLLExport int FSPrV_Load(int SInId);
DLLExport void FSPrV_Save(int StrVId, int SOutId);

/////////////////////////////////////////////////
// Input-Stream
DLLExport int SIn_GenStdIn();
DLLExport int SIn_GenFileIn(char* FNm);
DLLExport int SIn_GenMemIn(int MemId);
DLLExport int SIn_GenStrIn(char* Str);
DLLExport void SIn_Del(int SInId);

/////////////////////////////////////////////////
// Output-Stream
DLLExport int SOut_GenStdOut();
DLLExport int SOut_GenFileOut(char* FNm, bool Append=false);
DLLExport int SOut_GenMemOut(int MemId);
DLLExport void SOut_Del(int SOutId);

/////////////////////////////////////////////////
// conversions to and from Compact-Doc
DLLExport bool Conv_HtmlToCpd(
 char* InFPath, char* OutCpdFNm, bool RecurseDirP=false, int MxDocs=-1);
DLLExport bool Conv_Reuters21578ToCpd(
 char* InFPath, char* OutCpdFNm, int MxDocs=-1);
DLLExport bool Conv_Reuters2000ToCpd(
 char* InFPath, char* OutCpdFNm, int MxDocs=-1);
DLLExport bool Conv_AcmTechNewsToCpd(
 char* InFPath, char* OutCpdFNm, int MxDocs=-1);
DLLExport bool Conv_CiaWFBToCpd(
 char* InFPath, char* OutCpdFNm);

DLLExport bool Conv_CpdToLnDocTxt(char* InCpdFNm, char* OutLnDocFNm);

/////////////////////////////////////////////////
// conversions to Bow-Doc-Base

/**
 * <p>Loads a folder of text files and process them into a BowDocBs
 * file. If the documents are grouped together into subfolders than
 * the names of the subfolders are used as categories. This method can
 * handle any sort of ASCII text files on the input (.txt, .html, .xml,
 * etc).</p>
 *
 * <p><b>Bag-of-Words model</b> or <b>Vector-space model</b> is the most
 * popular text document representation in text mining and information
 * retrieval. In bag-of-words each document is represeanted as a sparse
 * vector in a vector space spanned by all the words from the corpus.</p>
 *
 * <p>Processing steps: tokenization of documents into a sequence of
 * word tokens, removal of stop words, replacing words with their stemms and
 * identification of frequent n-grams (words frequently appearing together).
 * The character cases, non-alphabetical characters and  HTML or XML tags
 * within are ignored during the processing. The final result is a sparse
 * vector for each document where each dimension in the vector corresponds
 * to one word from the vocabulary and its value to the frequency of the
 * word in the given document.</p>
 *
 * <p>The following information is stored about each document in the Text-Garden
 * BowDocBs object: document name, document content, list of categories
 * and sparse vector.</p>
 *
 * @param path of the input folder containing text files
 * @param output BowDocBs file name.
 * @param should the method scan subfolders for the documents
 * @param maximal number of documents to be loaded
 * @param stop-word list name(none, en8, en425, en523, german, siyuascii, siisoce)
 * @param stammer name (none, porter)
 * @param maximal length of n-grams that are calculated
 * @param minimal frequency for a sequence of words to be regarded as n-gram.
 */
DLLExport bool Conv_HtmlToBow(
 char* InFPath, char* OutBowFNm,
 bool RecurseDirP, int Recs,
 char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq);

DLLExport bool Conv_CpdToBow(
 char* InCpdFNm, char* OutBowFNm,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq);

DLLExport int Conv_GetBowFromCpd(
 int CpdSInId,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq);

/**
 * <p>Loads documents from a single input text file and process them into a
 * BowDocBs file. Each line of the input file is regarded as one document.
 * First word in line can be regarded as the document name. Categories of the
 * document can be included after the document name and should begin with
 * exclamaition point (!). Everything that follows is regarded as the
 * content of a document.</p>
 *
 * <p><b>Example:</b>:<br>
 * Document_Name !First_Category !Second_Category This is the content.<br>
 * Another_Document !First_Category !Third_Category This is another document.<br></p>
 *
 * <p><b>Bag-of-Words model</b> or <b>Vector-space model</b> is the most
 * popular text document representation in text mining and information
 * retrieval. In bag-of-words each document is represeanted as a sparse 
 * vector in a vector space spanned by all the words from the corpus.</p>
 *
 * <p>Processing steps: tokenization of documents into a sequence of
 * word tokens, removal of stop words, replacing words with their stemms and
 * identification of frequent n-grams (words frequently appearing together).
 * The character cases, non-alphabetical characters and  HTML or XML tags 
 * within are ignored during the processing. The final result is a sparse 
 * vector for each document where each dimension in the vector corresponds 
 * to one word from the vocabulary and its value to the frequency of the 
 * word in the given document.</p>
 *
 * <p>The following information is stored about each document in the Text-Garden 
 * BowDocBs object: document name, document content, list of categories
 * and sparse vector.</p>
 *
 * @param input text file name
 * @param output BowDocBs file name.
 * @param is the first word in the line a document name.
 * @param maximal number of documents to be loaded
 * @param stop-word list name(none, en8, en425, en523, german, siyuascii, siisoce)
 * @param stammer name (none, porter)
 * @param maximal length of n-grams that are calculated
 * @param minimal frequency for a sequence of words to be regarded as n-gram.
 */
DLLExport bool Conv_LnDocToBow(
 char* InLnDocFNm, char* OutBowFNm,
 bool NamedP, int Recs,
 char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq);

DLLExport bool Conv_Reuters21578ToBow(
 char* InFPath, char* OutBowFNm,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq);

DLLExport bool Conv_CiaWFBToBow(
 char* InFPath, char* OutBowFNm,
 int Recs, char* SwSetTypeNm, char* StemmerTypeNm,
 int MxNGramLen, int MnNGramFq);

/////////////////////////////////////////////////
// Bow-Doc-Base Manipulation
/**
 * <p>Generates an empty BowDocBs object and returns its handle.</p>
 * @param stop-word list name(none, en8, en425, en523, german, siyuascii, siisoce)
 * @param stammer name (none, porter)
 * @return handle to empty BowDocBs object
 */
DLLExport int BowDocBs_New(char* SwSetTypeNm, char* StemmerTypeNm);
DLLExport int BowDocBs_Load(int SInId);
DLLExport void BowDocBs_Save(int BowDocBsId, int SOutId);
/**
 * <p>Loads BowDocBs object from a file into memory and returns its handle.</p>
 * @param Input BowDocBs file name
 * @return handle to loaded BowDocBs object
 */
DLLExport int BowDocBs_LoadFromFile(char* FNm);
/**
 * <p>Saves the given BowDocBs object from the memory into a file.</p>
 * @param handle for the BowDocBs object
 * @param output BowDocBs file name
 * @return true if saving successful
 */
DLLExport void BowDocBs_SaveToFile(int BowDocBsId, char* FNm);
/**
 * <p>Saves statistics of the given BowDocBs object to a text file.</p>
 * @param handle for the BowDocBs object
 * @param output BowDocBs statistic file name
 * @return true if saving successful
 */
DLLExport void BowDocBs_SaveStatToFile(int BowDocBsId, char* FNm);
/**
 * <p>Deletes the given BowDocBs object from the memory.</p>
 * @param handle for the BowDocBs object
 * @return true if successfuly deleted
 */
DLLExport void BowDocBs_Del(int BowDocBsId);

/////////////////////////////////////////////////
// Bow-Doc-Base Words
/**
 * <p>Returns the number of words in the vocabulary of the given BowDocBs object.</p>
 * @param handle for the BowDocBs object
 * @return number of words in the vocabulary
 */
DLLExport int BowDocBs_GetWords(int BowDocBsId);
/**
 * <p>Tells if a given word is part of the vocabulary.</p>
 * @param handle for the BowDocBs object
 * @param word string
 * @return true if word is part of vocabulary
 */
DLLExport bool BowDocBs_IsWordStr(int BowDocBsId, char* WordStr);
/**
 * <p>Returns the ID of the given word.</p>
 * @param handle for the BowDocBs object
 * @param word string
 * @return word ID, -1 if the word is not part of vocabulary
 */
DLLExport int BowDocBs_GetWId(int BowDocBsId, char* WordStr);
/**
 * <p>Returns the word string for the given word ID.</p>
 * @param handle for the BowDocBs object
 * @param word ID
 * @return word string
 */
DLLExport char* BowDocBs_GetWordStr(int BowDocBsId, int WId);

/////////////////////////////////////////////////
// Bow-Doc-Base Categories
/**
 * <p>Returns the number of categories in the given BowDocBs object.</p>
 * @param handle for the BowDocBs object
 * @return number of categories
 */
DLLExport int BowDocBs_GetCats(int BowDocBsId);
/**
 * <p>Tells if a given category is exists in the given BowDocBs object.</p>
 * @param handle for the BowDocBs object
 * @param category name
 * @return true if category exists
 */
DLLExport bool BowDocBs_IsCatNm(int BowDocBsId, char* CatNm);
/**
 * <p>Returns the ID of the given category.</p>
 * @param handle for the BowDocBs object
 * @param category name
 * @return category ID, -1 if such category does not exist
 */
DLLExport int BowDocBs_GetCId(int BowDocBsId, char* CatNm);
/**
 * <p>Returns the category name for the given category ID.</p>
 * @param handle for the BowDocBs object
 * @param category ID
 * @return category name
 */
DLLExport char* BowDocBs_GetCatNm(int BowDocBsId, int CId);

/////////////////////////////////////////////////
// Bow-Doc-Base Documents
/**
 * <p>Adds a new document to the BowDocBs object. HTML and XML tags are
 * ignored.</p>
 * @param handle for the BowDocBs object
 * @param name of the document
 * @param content of the document
 * @param list of categories separated by semicolon (;)
 * @param true if the document content should be saved along the sparse vector
 * @return document ID of the new document
 */
DLLExport int BowDocBs_AddHtmlDocStr(int BowDocBsId,
 char* DocNm, char* HtmlDocStr, char* CatNmVStr, bool SaveDocP=false);

/**
 * <p>Returns the number of documents in the given BowDocBs object.</p>
 * @param handle for the BowDocBs object
 * @return number of documents
 */
DLLExport int BowDocBs_GetDocs(int BowDocBsId);
/**
 * <p>Tells if a given document name exists in the given BowDocBs object.</p>
 * @param handle for the BowDocBs object
 * @param document name
 * @return true if document with such name exists
 */
DLLExport bool BowDocBs_IsDocNm(int BowDocBsId, char* DocNm);
/**
 * <p>Returns the ID of the given document.</p>
 * @param handle for the BowDocBs object
 * @param document name
 * @return document ID, -1 if such document does not exist
 */
DLLExport int BowDocBs_GetDId(int BowDocBsId, char* DocNm);
/**
 * <p>Returns the document name for the given document ID.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @return document name
 */
DLLExport char* BowDocBs_GetDocNm(int BowDocBsId, int DId);

/**
 * <p>Returns the number of different words that occur in the given document.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @return number of different words
 */
DLLExport int BowDocBs_GetDocWIds(int BowDocBsId, int DId);
/**
 * <p>Returns the document's DocWIdN-th word ID.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @param word position in the document's sparse vector
 * @return word ID
 */
DLLExport int BowDocBs_GetDocWId(int BowDocBsId, int DId, int DocWIdN);
/**
 * <p>Returns the document's DocWId's word position in the document's sparse vector (slow).</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @param word ID
 * @return word position
 */
DLLExport int BowDocBs_GetDocWIdN(int BowDocBsId, int DId, int DocWId);
/**
 * <p>Sets document's DocWIdN-th word frequency.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @param word position in the document's sparse vector
 * @param new word frequency
 */
DLLExport void BowDocBs_PutDocWFq(int BowDocBsId, int DId, int DocWIdN, double WFq);
/**
 * <p>Returns the document's DocWIdN-th word frequency.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @param word position in the document's sparse vector
 * @return word frequency
 */
DLLExport double BowDocBs_GetDocWFq(int BowDocBsId, int DId, int DocWIdN);

/**
 * <p>Returns the number of categories to which the given document belongs.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @return number of categories
 */
DLLExport int BowDocBs_GetDocCIds(int BowDocBsId, int DId);
/**
 * <p>Returns the category ID of the document's DocCIdN-th category.</p>
 * @param handle for the BowDocBs object
 * @param document ID
 * @param category position in the document's category list
 * @return category ID
 */
DLLExport int BowDocBs_GetDocCId(int BowDocBsId, int DId, int DocCIdN);

/////////////////////////////////////////////////
// Bow-Doc-Weight-Base Manipulation
/**
 * <p>Calculates TFIDF word weights based on the documents from the given
 * BowDocBs object, generates a BowDocWgtBs object and returns its handle.
 * BowDocWgtBs object stores weighted and normalized sparse vectors of the 
 * documents from the BowDocBs object.</p>
 * 
 * <p>The elements of weighted sparse vectors are computed using standard 
 * TFIDF formula: x[i] = TF[i] * log(Docs/DF[i]). Here TF[i] corresponds to
 * term frequency of i-th word in the document, DF[i] corresponds to document
 * frequency of the i-th word in the corpus and Docs is the size of vocabulary.
 * All vectors are normalized so that their lenght in Euclidian norm equals 1.</p>
 *
 * @param handle for the BowDocBs object
 * @return handle for the BowDocWgtBs object
 */
DLLExport int BowDocWgtBs_Gen(int BowDocBsId);
/**
 * <p>Deletes the given BowDocWgtBs object from the memory.</p>
 * @param handle for the BowDocWgtBs object
 * @return true if successfuly deleted
 */
DLLExport void BowDocWgtBs_Del(int BowDocWgtBsId);

/////////////////////////////////////////////////
// Bow-Doc-Weight-Base
/**
 * <p>Returns the number of documents in the given BowDocWgtBs object.</p>
 * @param handle for the BowDocWgtBs object
 * @return number of documents
 */
DLLExport int BowDocWgtBs_GetDocs(int BowDocWgtBsId);
/**
 * <p>Returns the ID of the given document.</p>
 * @param handle for the BowDocWgtBs object
 * @param document position in the list
 * @return document ID
 */
DLLExport int BowDocWgtBs_GetDocId(int BowDocWgtBsId, int DIdN);

/**
 * <p>Returns the number of different words that occur in the given document.</p>
 * @param handle for the BowDocWgtBs object
 * @param document ID
 * @return number of different words
 */
DLLExport int BowDocWgtBs_GetDocWIds(int BowDocWgtBsId, int DId);
/**
 * <p>Returns the document's DocWIdN-th word ID.</p>
 * @param handle for the BowDocWgtBs object
 * @param document ID
 * @param word position in the document's sparse vector
 * @return word ID 
 */
DLLExport int BowDocWgtBs_GetDocWId(int BowDocWgtBsId, int DId, int DocWIdN);
/**
 * <p>Returns the document's DocWIdN-th word weight.</p>
 * @param handle for the BowDocWgtBs object
 * @param document ID
 * @param word position in the document's sparse vector
 * @return word weight
 */
DLLExport double BowDocWgtBs_GetDocWWgt(int BowDocWgtBsId, int DId, int DocWIdN);

/**
 * <p>Returns a handle to the vector of the top (weight, word) pairs
 * for the given document. The elements of vector are sorted with the 
 * starting with the highest weights.</p>
 *
 * <p>The length of the vector is determined by two factors: maximal absolute 
 * number of elements (TopWords) and the percentage of the sum of the selected
 * weights relative to the total sum of the document's weights (TopWordsWgtPrc).
 *
 * @param handle for the BowDocWgtBs object
 * @param handle for the BowDocBs object
 * @param document ID
 * @param maximal number of top words to include in the vector
 * @param maximal percentage of weights to include in the vector
 * @return Float-String-Pair-Vector handle
 */
DLLExport int BowDocWgtBs_GetWgtWordPrV(
 int BowDocWgtBsId, int BowDocBsId, int DId,
 int TopWords, double TopWordsWgtPrc);

/**
 * <p>Performs a nearest-neighbor search the between the a query and 
 * a collection of weighted documents using cosine similairty.</p>
 * @param handle for the BowDocWgtBs object
 * @param handle for the BowDocBs object
 * @param query string
 * @return Result-Set handle
 */
DLLExport int BowDocWgtBs_Search(
 int BowDocWgtBsId, int BowDocBsId, char* QueryStr);

/////////////////////////////////////////////////
// Bow-Doc-Partition Manipulation
/**
 * <p>Loads BowDocPart object from a file into memory and returns its handle.</p>
 * @param Input BowDocPart file name
 * @return handle to loaded BowDocPart object
 */
DLLExport int BowDocPart_Load(int SInId);
DLLExport void BowDocPart_Save(int BowDocPartId, int SOutId);
DLLExport int BowDocPart_LoadFromFile(char* FNm);
/**
 * <p>Saves the given BowDocPart object from the memory into a file.</p>
 * @param handle for the BowDocPart object
 * @param output BowDocPart file name
 * @return true if saving successful
 */
DLLExport void BowDocPart_SaveToFile(int BowDocPartId, char* FNm);
/**
 * <p>Saves statistics of the given BowDocPart object to a text file.</p>
 * @param handle for the BowDocPart object
 * @param handle for the BowDocBs object
 * @param output BowDocPart statistic file name
 * @return true if saving successful
 */
DLLExport void BowDocPart_SaveStatToFile(int BowDocPartId, int BowDocBsId, char* FNm);
/**
 * <p>Deletes the given BowDocPart object from the memory.</p>
 * @param handle for the BowDocPart object
 * @return true if successfuly deleted
 */
DLLExport void BowDocPart_Del(int BowDocPartId);

/////////////////////////////////////////////////
// Clustering into Bow-Doc-Partition
/**
 * <p>Performs hierarchical k-means clustering on the documents and stores
 * clustering information into BowDocPart object; TFIDF
 * together with cosine similarity is used for the similarity measure.</p>
 *
 * <p>The elements of weighted sparse vectors are computed using standard 
 * TFIDF formula: x[i] = TF[i] * log(Docs/DF[i]). Here TF[i] corresponds to
 * term frequency of i-th word in the document, DF[i] corresponds to document
 * frequency of the i-th word in the corpus and Docs is the size of vocabulary.
 * All vectors are normalized so that their lenght in Euclidian norm equals 1.</p>
 *
 * @param handle for the BowDocPart object
 * @param the number of clusters
 * @param the number of different runs/trials of K-Means algorithm in a search for the best solution 
 * @param convergence epsilon value which influences the stopping criterium for the K-Means algorithm (recommended 10)
 * @param the minimal size of the clusters
 * @param minimal value for the weight in the sparse vectors (if lower than replaced with 0)
 * @param minimal frequency for the word to be included in the sparse vector
 * @param seed for the random number generator
 * @param maximal number of documents to be clusterd
 * @return handle to created BowDocPart object
 */
DLLExport int BowDocPart_GetKMeans(
 int BowDocBsId, int Clusts,
 int ClustTrials, double ConvergEps, int MnDocsPerClust,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);
/**
 * <p>Performs hierarchical k-means clustering on the documents and stores
 * clustering information into BowDocPart object; TFIDF 
 * weighting together with cosine similarity is used for the similarity 
 * measure. The algorith starts with spliting the given document collections
 * into two clusters. Clusters with more than MxDocsPerLeafClust documents 
 * are than further split into two clusters.</p>
 *
 * <p>The elements of weighted sparse vectors are computed using standard 
 * TFIDF formula: x[i] = TF[i] * log(Docs/DF[i]). Here TF[i] corresponds to
 * term frequency of i-th word in the document, DF[i] corresponds to document
 * frequency of the i-th word in the corpus and Docs is the size of vocabulary.
 * All vectors are normalized so that their lenght in Euclidian norm equals 1.</p>
 *
 * @param handle for the BowDocPart object
 * @param maximal number of documents for leaf clusters
 * @param the number of different runs/trials of K-Means algorithm in a search for the best solution
 * @param convergence epsilon value which influences the stopping criterium for the K-Means algorithm
 * @param the minimal size of the clusters in number of documents
 * @param minimal value for the weight in the sparse vectors (if lower than replaced with 0)
 * @param minimal frequency for the word to be included in the sparse vector
 * @param seed for the random number generator
 * @param maximal number of documents to be clusterd
 * @return handle to created BowDocPart object
 */
DLLExport int BowDocPart_GetHKMeans(
 int BowDocBsId, int MxDocsPerLeafClust,
 int ClustTrials, double ConvergEps, int MnDocsPerClust,
 double CutWordWgtSumPrc, int MnWordFq, int RndSeed, int MxDocs);

/////////////////////////////////////////////////
// Bow-Doc-Partition Clusters
/**
 * <p>Returns the number of clusters in the given BowDocPart object.</p>
 * @param handle for the BowDocPart object
 * @return number of clusters
 */
DLLExport int BowDocPart_GetClusts(int BowDocPartId);
/**
 * <p>Returns the number of documents of a cluster.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @return number of documents
 */
DLLExport int BowDocPart_GetDocs(int BowDocPartId, int ClustN);
/**
 * <p>Returns the document ID in the given document of a cluster.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @param position of document in the cluster's document list
 * @return documents ID
 */
DLLExport int BowDocPart_GetDId(int BowDocPartId, int ClustN, int DIdN);
/**
 * <p>Returns the average similarity between cluster's documents and centroid.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @return mean similarity
 */
DLLExport double BowDocPart_GetMeanSim(int BowDocPartId, int ClustN);
/**
 * <p>Returns the similarity between a document and the cluster's centroid.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @param position of document in the cluster's document list
 * @return documents ID
 */
DLLExport double BowDocPart_GetDCSim(int BowDocPartId, int ClustN, int DId);
/**
 * <p>Returns the number of words that occur in the given cluster's centroid 
 * sparse vector.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @return number of words in the centroid
 */
DLLExport int BowDocPart_GetConceptWords(int BowDocPartId, int ClustN);
/**
 * <p>Returns the centroids's WIdN-th word ID.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @param word position in the centroid's sparse vector
 * @return word ID 
 */
DLLExport int BowDocPart_GetConceptWId(int BowDocPartId, int ClustN, int WIdN);
/**
 * <p>Returns the centroids's WIdN-th word weight.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @param word position in the centroid's sparse vector
 * @return word weight 
 */
DLLExport double BowDocPart_GetConceptWWgt(int BowDocPartId, int ClustN, int WIdN);
/**
 * <p>Tells if a cluster is further partitioned into sub-clusters.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @return true if cluster is partitioned
 */
DLLExport bool BowDocPart_IsSubPart(int BowDocPartId, int ClustN);
/**
 * <p>Returnes clusters partition in a form of BowDocPart object.</p>
 * @param handle for the BowDocPart object
 * @param position of cluster in the partition list
 * @return handle to BowDocPart object
 */
DLLExport int BowDocPart_GetSubPart(int BowDocPartId, int ClustN);

/////////////////////////////////////////////////
// Semantic-Space Manipulation
DLLExport int SemSpace_Load(int SInId);
DLLExport void SemSpace_Save(int SemSpaceId, int SOutId);
DLLExport int SemSpace_LoadFromFile(char* FNm);
DLLExport void SemSpace_SaveToFile(int SemSpaceId, char* FNm);
DLLExport void SemSpace_SaveStatToFile(int SemSpaceId, int BowDocBsId, char* FNm);
DLLExport void SemSpace_Del(int SemSpaceId);

/////////////////////////////////////////////////
// Semantic-Space Dimensions
DLLExport int SemSpace_GetDims(int SemSpaceId);
DLLExport int SemSpace_GetDim(int SemSpaceId, int BowDocBsId, int DimN);

/////////////////////////////////////////////////
// Decomposition into Semantic-Space
DLLExport int SemSpace_GetLSI(int BowDocBsId, int SpaceDims);
DLLExport int SemSpace_GetLSIFromBowPart(int BowDocPartId, int SpaceDims);
DLLExport int SemSpace_GetPCA(int BowDocBsId);

/////////////////////////////////////////////////
// Visualization-Map Manipulation
DLLExport int VizMap_Load(int SInId);
DLLExport void VizMap_Save(int VizMapId, int SOutId);
DLLExport int VizMap_LoadFromFile(char* FNm);
DLLExport void VizMap_SaveToFile(int VizMapId, char* FNm);
DLLExport void VizMap_Del(int VizMapId);

/////////////////////////////////////////////////
// Visualization-Map
DLLExport int VizMap_GetMdsClustLsi(
 int BowDocBsId, int BowDocWgtBsId, int BowDocPartId, int SemSpaceId,
 int TopClusts=3, double SemSpaceTsh=0.7,
 int MxSteps=10000, int MxSecs=100, double MnDiff=0.0001);
DLLExport int VizMap_GetMdsLsi(
 int BowDocBsId, int BowDocWgtBsId, int SemSpaceId,
 double SemSpaceTsh=0.7,
 int MxSteps=10000, int MxSecs=100, double MnDiff=0.0001);

DLLExport int VizMap_GetBowDocBsId(int VizMapId);
DLLExport int VizMap_GetBowDocWgtBsId(int VizMapId);
DLLExport int VizMap_GetDocs(int VizMapId);
DLLExport int VizMap_GetDId(int VizMapId, int DIdN);
DLLExport double VizMap_GetDocX(int VizMapId, int DIdN);
DLLExport double VizMap_GetDocY(int VizMapId, int DIdN);
DLLExport int VizMap_GetXYDId(
 int VizMapId, double X, double Y, double Radius=0.01);

DLLExport void VizMap_GenLandscape(int VizMapId,
 int Landscapes=1, int Width=500, int Height=500,
 double BellSigma=0.01, double BellSigmaDecay=0.5);
DLLExport int VizMap_GetLandscapes(int VizMapId);
DLLExport void VizMap_SaveVrmlToFile(
 int VizMapId, char* VrmlFNm, int LandscapeN,
 bool ShowDocNmP, bool ShowDocPtP, bool ShowKWordsP,
 double FontSize);

DLLExport void VizMap_GenKeywords(int VizMapId,
 int KWords=1000, double Radius=0.2, int Candidates=3);
DLLExport int VizMap_GetKWords(int VizMapId);
DLLExport char* VizMap_GetKWordStr(int VizMapId, int KWordN);
DLLExport double VizMap_GetKWordX(int VizMapId, int KWordN);
DLLExport double VizMap_GetKWordY(int VizMapId, int KWordN);
DLLExport int VizMap_GetKWordStrV(
 int VizMapId, double X, double Y, double Radius, int MxKWords);

/////////////////////////////////////////////////
// Bow-Model Manipulation
DLLExport int BowMd_Load(int SInId);
DLLExport void BowMd_Save(int BowMdId, int SOutId);
DLLExport int BowMd_LoadFromFile(char* FNm, int BowDocBsId);
DLLExport void BowMd_SaveToFile(int BowMdId, char* FNm);
DLLExport void BowMd_Del(int BowMdId);

/////////////////////////////////////////////////
// Bow-Model Information
DLLExport bool BowMd_IsCat(int BowMdId);
DLLExport char* BowMd_GetCatNm(int BowMdId);
DLLExport bool BowMd_IsLinComb(int BowMdId);
DLLExport int BowMd_GetLinCombWgtWordPrV(int BowMdId, int BowDocBsId);
DLLExport double BowMd_GetLinCombTsh(int BowMdId);

/////////////////////////////////////////////////
// Training into Bow-Model
DLLExport int BowMd_GetBinSVM(
 int BowDocBsId, int CId, double Cost=1, double CostWgt=1,
 double CutWordWgtSumPrc=0, int MnWordFq=0, int RndSeed=0, int MxDocs=-1);
DLLExport int BowMd_GetOneClassSVM(
 int BowDocBsId, int CId, double Nu=0.1,
 double CutWordWgtSumPrc=0, int MnWordFq=0, int RndSeed=0, int MxDocs=-1);
DLLExport int BowMd_GetWinnow(
 int BowDocBsId, int CId, double Beta=0.95,
 double CutWordWgtSumPrc=0, int MnWordFq=0, int RndSeed=0, int MxDocs=-1);

/////////////////////////////////////////////////
// Classification using Bow-Model
DLLExport double BowMd_GetCfyFromDocBs(int BowMdId, int BowDocBsId, int DId);
DLLExport double BowMd_GetCfyFromHtml(int BowMdId, int BowDocBsId, char* HtmlStr);

/////////////////////////////////////////////////
// Bow-Active-Learning
DLLExport int BowAL_New(int BowDocBsId, int CId, double Cost=1, double CostWgt=1);
DLLExport void BowAL_Del(int BowALId);

DLLExport int BowAL_GetCId(int BowALId);
DLLExport bool BowAL_IsQueryDIdV(int BowALId);
DLLExport int BowAL_GetQueries(int BowALId);
DLLExport double BowAL_GetQueryDist(int BowALId, int QueryN);
DLLExport int BowAL_GetQueryDId(int BowALId, int QueryN);
DLLExport void BowAL_MarkQueryDId(int BowALId, int QueryDId, bool AssignToCatP);
DLLExport void BowAL_MarkUnlabeledPosDocs(int BowALId);

/////////////////////////////////////////////////
// Result-Set Manipulation
DLLExport int RSet_Load(int SInId);
DLLExport void RSet_Save(int RSetId, int SOutId);
DLLExport int RSet_LoadFromFile(char* FNm);
DLLExport void RSet_SaveToFile(int RSetId, char* FNm);
DLLExport void RSet_SaveXmlToFile(int RSetId, char* FNm);
DLLExport void RSet_Del(int RSetId);

/////////////////////////////////////////////////
// Result-Set
DLLExport char* RSet_GetUrlStr(int RSetId);
DLLExport char* RSet_GetNextUrlStr(int RSetId);
DLLExport char* RSet_GetQueryStr(int RSetId);
DLLExport int RSet_GetAllHits(int RSetId);

DLLExport int RSet_GetHits(int RSetId);
DLLExport int RSet_GetHitN(int RSetId, char* UrlStr, bool LcP);
DLLExport char* RSet_GetHitUrlStr(int RSetId, int HitN);
DLLExport char* RSet_GetHitTitleStr(int RSetId, int HitN);
DLLExport char* RSet_GetHitSrcNm(int RSetId, int HitN);
DLLExport char* RSet_GetHitCtxStr(int RSetId, int HitN);

/////////////////////////////////////////////////
// Google
DLLExport int Google_WebSearch(char* QueryStr, int MxHits=-1);
DLLExport int Google_NewsSearch(char* QueryStr, int MxHits=-1);

/////////////////////////////////////////////////
// Named-Object-Base Manipulation
DLLExport int NmObjBs_Load(int SInId);
DLLExport void NmObjBs_Save(int NmObjBsId, int SOutId);
DLLExport int NmObjBs_LoadFromFile(char* FNm);
DLLExport void NmObjBs_SaveToFile(int NmObjBsId, char* FNm);
DLLExport void NmObjBs_SaveTxtToFile(int NmObjBsId,
 char* FqFNm, char* SwFNm, char* AbcFNm, char* DocFNm);
DLLExport void NmObjBs_Del(int NmObjBsId);

/////////////////////////////////////////////////
// Named-Object-Base
DLLExport int Conv_CpdToNmObjBs(
 int CpdSInId, char* SwSetTypeNm, char* CustSwSetFNm,
 char* NrWordBsFNm, char* WordTypeBsFNm, int MxDocs=-1);
DLLExport int Conv_CpdToNmObjBsFromFile(
 char* CpdFNm, char* SwSetTypeNm, char* CustSwSetFNm,
 char* NrWordBsFNm, char* WordTypeBsFNm, int MxDocs=-1);
DLLExport int Conv_NmObjBsToBow(int NmObjBsId, int MnNmObjFq=-1);

/////////////////////////////////////////////////
// Url
DLLExport int Url_Get(char* RelUrlStr, char* BaseUrlStr);
DLLExport void Url_Del(int UrlId);

DLLExport bool Url_IsOk(int UrlId, int Scheme=0);
DLLExport bool Url_IsOkHttp(int UrlId);
DLLExport int Url_GetScheme(int UrlId);
DLLExport char* Url_GetUrlStr(int UrlId);
DLLExport char* Url_GetRelUrlStr(int UrlId);
DLLExport bool Url_IsBaseUrl(int UrlId);
DLLExport char* Url_GetBaseUrlStr(int UrlId);
DLLExport char* Url_GetSchemeNm(int UrlId);
DLLExport char* Url_GetHostNm(int UrlId);
DLLExport char* Url_GetDmNm(int UrlId, int MxDmSegs=-1);
DLLExport char* Url_GetPortStr(int UrlId);
DLLExport int Url_GetPortN(int UrlId);
DLLExport char* Url_GetPathStr(int UrlId);
DLLExport int Url_GetPathSegs(int UrlId);
DLLExport char* Url_GetPathSeg(int UrlId, int PathSegN);
DLLExport char* Url_GetSearchStr(int UrlId);
DLLExport char* Url_GetFragIdStr(int UrlId);

/////////////////////////////////////////////////
// Http-Response
DLLExport int HttpResp_GetFromStr(char* HttpRespStr);
DLLExport int HttpResp_GetFromFile(char* HttpRespFNm);
DLLExport void HttpResp_Del(int HttpRespId);

DLLExport bool HttpResp_IsOk(int HttpRespId);
DLLExport int HttpResp_Len(int HttpRespId);
DLLExport char* HttpResp_GetHdStr(int HttpRespId);
DLLExport int HttpResp_GetBodyAsMem(int HttpRespId);
DLLExport char* HttpResp_GetBodyAsStr(int HttpRespId);
DLLExport int HttpResp_GetStatusCd(int HttpRespId);
DLLExport bool HttpResp_IsStatusCd_Ok(int HttpRespId);
DLLExport bool HttpResp_IsStatusCd_Redir(int HttpRespId);
DLLExport char* HttpResp_GetReasonPhrase(int HttpRespId);
DLLExport int HttpResp_GetFlds(int HttpRespId);
DLLExport char* HttpResp_GetFldNm(int HttpRespId, int FldN);
DLLExport char* HttpResp_GetFldVal(int HttpRespId, int FldN);
DLLExport bool HttpResp_IsFldNm(int HttpRespId, char* FldNm);
DLLExport char* HttpResp_GetFldValByNm(int HttpRespId, char* FldNm);
DLLExport bool HttpResp_IsFldVal(int HttpRespId, char* FldNm, char* FldVal);

/////////////////////////////////////////////////
// Html
DLLExport int HtmlDoc_GetFromStr(char* HtmlStr);
DLLExport int HtmlDoc_GetFromFile(char* HtmlFNm);
DLLExport void HtmlDoc_Del(int HtmlDocId);

DLLExport int HtmlDoc_GetToks(int HtmlDocId);
DLLExport int HtmlDoc_GetTokSym(int HtmlDocId, int TokN);
DLLExport char* HtmlDoc_GetTokStr(int HtmlDocId, int TokN);
DLLExport char* HtmlDoc_GetTokFullStr(int HtmlDocId, int TokN);
DLLExport bool HtmlDoc_IsTokArg(int HtmlDocId, int TokN, char* ArgNm);
DLLExport char* HtmlDoc_GetTokArg(int HtmlDocId, int TokN, char* ArgNm, char* DfArgVal);
DLLExport bool HtmlDoc_IsTokUrl(int HtmlDocId, int TokN);
DLLExport char* HtmlDoc_GetTokUrlStr(int HtmlDocId, int TokN);
DLLExport bool HtmlDoc_IsBreakTag(char* TagNm);
DLLExport char* HtmlDoc_GetSymStr(int Sym);

/////////////////////////////////////////////////
// Web-Page
DLLExport int WebPg_Fetch(char* UrlStr);
DLLExport void WebPg_Del(int WebPgId);

DLLExport int WebPg_GetUrls(int WebPgId);
DLLExport char* WebPg_GetUrl(int WebPgId, int UrlN=0);
DLLExport int WebPg_GetHttpResp(int WebPgId);
DLLExport int WebPg_GetOutUrlStrV(int WebPgId);

/////////////////////////////////////////////////
// Web-Crawler
//$ creates & returns handle to crawler
DLLExport int Crawler_Gen();
//$ deletes crawler with handle CrawlerId
DLLExport void Crawler_Del(int CrawlerId);

//$ adds start-url StartUrlStr to crawler with handle CrawlerId
DLLExport void Crawler_AddStartUrlStr(int CrawlerId, char* StartUrlStr);
//$ sets maximal number of urls MxUrls to crawler with handle CrawlerId
DLLExport void Crawler_PutMxUrls(int CrawlerId, int MxUrls);
//$ sets maximal number of connections MxUrls to crawler with handle CrawlerId
DLLExport void Crawler_PutMxConns(int CrawlerId, int MxConns);
DLLExport void Crawler_PutMnConns(int CrawlerId, int MnConns);
DLLExport void Crawler_PutMxConnsPerSrv(int CrawlerId, int MxConnsPerSrv);
DLLExport void Crawler_PutAfterFetchDelay(int CrawlerId, int AfterFetchDelaySecs);
DLLExport void Crawler_PutMxLev(int CrawlerId, int MxLev);
DLLExport void Crawler_PutMxDep(int CrawlerId, int MxDep);
DLLExport void Crawler_PutMnQLen(int CrawlerId, int MnQLen);
DLLExport void Crawler_PutQResetMod(int CrawlerId, int QResetMod);
DLLExport void Crawler_PutMxContLen(int CrawlerId, int MxContLen);
DLLExport void Crawler_PutMxRetries(int CrawlerId, int MxRetries);
DLLExport void Crawler_PutMxQSegLen(int CrawlerId, int MxQSegLen);
DLLExport void Crawler_PutRevisitSecs(int CrawlerId, int RevisitSecs);
DLLExport void Crawler_PutRedirDmAllowed(int CrawlerId, bool RedirDmAllowedP);
DLLExport void Crawler_AddRqDmNm(int CrawlerId, char* RqDmNmV);
DLLExport void Crawler_AddRqContTypeNm(int CrawlerId, char* ContTypeNm);
DLLExport void Crawler_AddBadFExt(int CrawlerId, char* FExt);
DLLExport void Crawler_OptHtmlCrawling(int CrawlerId);
DLLExport void Crawler_DefCrawlBs(int CrawlerId,
 char* CrawlBsNm, char* CrawlBsFPath,
 char* CrawlBsFAccessNm, int CrawlBsMxSegLen);

//$ starts crawler with handle CrawlerId
DLLExport void Crawler_StartCrawling(int CrawlerId);

/////////////////////////////////////////////////
// DMoz-Base
DLLExport int DMoz_GetCategories(
 int BowDocBsId, int BowDocWgtBsId, int BowDocPartId,
 char* QueryStr, int MxCats);

DLLExport int DMoz_GetKeywords(
 int BowDocBsId, int BowDocWgtBsId, int BowDocPartId,
 char* QueryStr, int MxCats, double KWordTsh);

/////////////////////////////////////////////////
// Blob-Pointer
//$ creates and returns handle to blob-base pointer
DLLExport int BlobPt_New();
//$ deletes blob-base pointer with handle BlobPtId
DLLExport void BlobPt_Del(int BlobPtId);

/////////////////////////////////////////////////
// Crawl-Base
//$ opens crawl-base with filename CrawlBsFNm and returns handle to CrawlBs object
DLLExport int CrawlBs_Open(char* CrawlBsFNm);
//$ closes crawl-base with handle CrawlBsId
DLLExport void CrawlBs_Close(int CrawlBsId);

//$ positions & returns traverse-pointer to crawl-base with handle CrawlBsId on-to the first crawl record
DLLExport int CrawlBs_FFirstBlobPt(int CrawlBsId);
//$ positions traverse-pointer TrvBlobPtId to crawl-base with handle CrawlBsId on-to the next crawl record and returns handle BlobPtId to current crawl record
DLLExport bool CrawlBs_FNextBlobPt(int CrawlBsId, int TrvBlobPtId, int BlobPtId);

//$ returns date-time string from crawl-base with handle CrawlBsId from record under handle BlobPtId
DLLExport char* CrawlBs_GetDateTimeStr(int CrawlBsId, int BlobPtId);
//$ returns url string from crawl-base with handle CrawlBsId from record under handle BlobPtId
DLLExport char* CrawlBs_GetUrlStr(int CrawlBsId, int BlobPtId);
//$ returns handle to http-response from crawl-base with handle CrawlBsId from record under handle BlobPtId
DLLExport int CrawlBs_GetHttpResp(int CrawlBsId, int BlobPtId);

/////////////////////////////////////////////////
// Blob-Base
DLLExport int BlobBs_Open(char* BlobBsFNm, int BlobBsFAccess);
DLLExport void BlobBs_Close(int BlobBsId);

DLLExport int BlobBs_GetFAccessCreate();
DLLExport int BlobBs_GetFAccessUpdate();
DLLExport int BlobBs_GetFAccessReadOnly();

DLLExport int BlobBs_FFirstBlobPt(int BlobBsId);
DLLExport bool BlobBs_FNextBlobPt(int BlobBsId, int TrvBlobPtId, int BlobPtId);

DLLExport void BlobBs_AddBlob(int BlobBsId, int MemId, int BlobPtId);
DLLExport void BlobBs_PutBlob(int BlobBsId, int MemId, int BlobPtId);
DLLExport void BlobBs_GetBlob(int BlobBsId, int BlobPtId, int MemId);
DLLExport void BlobBs_DelBlob(int BlobBsId, int BlobPtId);

/////////////////////////////////////////////////
// Compact-Document
DLLExport int CpDoc_Load(int SInId);
DLLExport void CpDoc_Save(int CpDocId, int SOutId);
DLLExport int CpDoc_New();
DLLExport void CpDoc_Del(int CpDocId);

// traversal
DLLExport void CpDoc_FFirstCpd(int SInId);
DLLExport bool CpDoc_FFNextCpd(int SInId, int CpDocId);

// document-id
DLLExport void CpDoc_PutDocNm(int CpDocId, char* DocNm);
DLLExport char* CpDoc_GetDocNm(int CpDocId);

// date
DLLExport void CpDoc_PutDateStr(int CpDocId, char* DateStr);
DLLExport char* CpDoc_GetDateStr(int CpDocId);

// categories
DLLExport void CpDoc_AddCatNm(int CpDocId, char* CatNm);
DLLExport int CpDoc_GetCats(int CpDocId);
DLLExport char* CpDoc_GetCatNm(int CpDocId, int CatN);

// get full-document
DLLExport char* CpDoc_GetTxtStr(int CpDocId);
DLLExport char* CpDoc_GetHtmlStr(int CpDocId);

// title/headline/byline/dateline
DLLExport void CpDoc_PutTitleStr(int CpDocId, char* TitleStr);
DLLExport char* CpDoc_GetTitleStr(int CpDocId);
DLLExport void CpDoc_PutHeadlineStr(int CpDocId, char* HeadlineStr);
DLLExport char* CpDoc_GetHeadlineStr(int CpDocId);
DLLExport void CpDoc_PutBylineStr(int CpDocId, char* BylineStr);
DLLExport char* CpDoc_GetBylineStr(int CpDocId);
DLLExport void CpDoc_PutDatelineStr(int CpDocId, char* DatelineStr);
DLLExport char* CpDoc_GetDatelineStr(int CpDocId);

// paragraphs/statements
DLLExport void CpDoc_AddParStr(int CpDocId, char* ParStr);
DLLExport int CpDoc_GetPars(int CpDocId);
DLLExport char* CpDoc_GetParStr(int CpDocId, int ParN);
DLLExport char* CpDoc_GetAllParStr(int CpDocId);

// topic codes
DLLExport void CpDoc_AddTopCdNm(int CpDocId, char* TopCdNm);
DLLExport int CpDoc_GetTopCds(int CpDocId);
DLLExport char* CpDoc_GetTopCdNm(int CpDocId, int TopCdN);

// country codes
DLLExport void CpDoc_AddGeoCdNm(int CpDocId, char* GeoCdNm);
DLLExport int CpDoc_GetGeoCds(int CpDocId);
DLLExport char* CpDoc_GetGeoCdNm(int CpDocId, int GeoCdN);

// industry codes
DLLExport void CpDoc_AddIndCdNm(int CpDocId, char* IndCdNm);
DLLExport int CpDoc_GetIndCds(int CpDocId);
DLLExport char* CpDoc_GetIndCdNm(int CpDocId, int IndCdN);

/////////////////////////////////////////////////
// Odbc-Database
DLLExport int OdbcDb_New();
DLLExport void OdbcDb_Del(int OdbcDbId);

// metadata
DLLExport int OdbcDb_GetDataSourceNmV(int OdbcDbId);
DLLExport int OdbcDb_GetTbNmV(int OdbcDbId);
DLLExport int OdbcDb_GetColNmV(int OdbcDbId, char* TbNm);

// connection
DLLExport bool OdbcDb_Connect(int OdbcDbId, char* SrvNm, char* UsrNm, char* PwdStr);
DLLExport void OdbcDb_Disconnect(int OdbcDbId);
DLLExport bool OdbcDb_IsConnected(int OdbcDbId);

// diagnostics handling
DLLExport bool OdbcDb_IsOk(int OdbcDbId);
DLLExport char* OdbcDb_GetMsgStr(int OdbcDbId);

/////////////////////////////////////////////////
// Odbc-Query
DLLExport int OdbcQuery_New(int OdbcDbId);
DLLExport void OdbcQuery_Del(int OdbcQueryId);

// statement execution
DLLExport bool OdbcQuery_ExeSql(int OdbcQueryId, char* SqlStr, int ParamStrVId=-1);
DLLExport bool OdbcQuery_ExeSqlP1(int OdbcQueryId, char* SqlStr, char* ParamStr);
DLLExport bool OdbcQuery_ExeSqlP2(int OdbcQueryId, char* SqlStr, char* ParamStr1, char* ParamStr2);
DLLExport bool OdbcQuery_ExeSqlP3(int OdbcQueryId, char* SqlStr, char* ParamStr1, char* ParamStr2, char* ParamStr3);
DLLExport bool OdbcQuery_IsResultSet(int OdbcQueryId);
DLLExport int OdbcQuery_GetCols(int OdbcQueryId);
DLLExport int OdbcQuery_GetRowsAffected(int OdbcQueryId);
DLLExport char* OdbcQuery_GetColNm(int OdbcQueryId, int ColN);
DLLExport bool OdbcQuery_NextRow(int OdbcQueryId);
DLLExport char* OdbcQuery_GetColVal(int OdbcQueryId, int ColN, int MxValStrLen=10000);

// diagnostics handling
DLLExport bool OdbcQuery_IsOk(int OdbcQueryId);
DLLExport bool OdbcQuery_IsOpOk(int OdbcQueryId);
DLLExport char* OdbcQuery_GetMsgStr(int OdbcQueryId);
