/*==========================================================================;
 *
 *  (c) 2006-07 JSI.  All rights reserved.
 *
 *  File:          Win32OntoServiceStub.h
 *  Version:       1.0
 *  Desc:		   OntoService stub
 *  Author:        Miha Grcar
 *  Created on:    Jul-2006?
 *  Last modified: Jul-2006?
 * 
 ***************************************************************************/

#ifndef WIN32ONTOSERVICESTUB_H
#define WIN32ONTOSERVICESTUB_H

#define STRING const char *

#ifndef NO_CLASSIFY
    #define DLLImport extern "C"
#else
    #define DLLImport
#endif

DLLImport int createStub(STRING url, STRING proxy_url);

DLLImport bool deleteObject(int object_id);
DLLImport void deleteAllObjects();

DLLImport int classify(int stub_id, STRING url, STRING text, int mx_cats, double kwd_tsh);

DLLImport STRING getLastExceptionMessage(int stub_id);
DLLImport STRING getLastExceptionStr(int stub_id);

DLLImport int getNumKeywords(int data_obj_id);
DLLImport STRING getKeywordStr(int data_obj_id, int keyword_idx);
DLLImport double getKeywordWeight(int data_obj_id, int keyword_idx);

DLLImport int getNumCategories(int data_obj_id);
DLLImport STRING getCategoryStr(int data_obj_id, int category_idx);
DLLImport double getCategoryWeight(int data_obj_id, int category_idx);

#endif