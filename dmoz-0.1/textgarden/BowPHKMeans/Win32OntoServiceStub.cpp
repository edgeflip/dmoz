#include "Win32OntoServiceStub.h"

#ifdef NO_CLASSIFY
    int createStub(STRING url, STRING proxy_url) { return 0; }

    bool deleteObject(int object_id) { return false; }
    void deleteAllObjects() { }

    int classify(int stub_id, STRING url, STRING text, int mx_cats, double kwd_tsh) { return 0; }

    STRING getLastExceptionMessage(int stub_id) { return 0; }
    STRING getLastExceptionStr(int stub_id) { return 0; }

    int getNumKeywords(int data_obj_id) { return 0; }
    STRING getKeywordStr(int data_obj_id, int keyword_idx) { return 0; }
    double getKeywordWeight(int data_obj_id, int keyword_idx) { return 0.0; }

    int getNumCategories(int data_obj_id) { return 0; }
    STRING getCategoryStr(int data_obj_id, int category_idx) { return 0; }
    double getCategoryWeight(int data_obj_id, int category_idx) { return 0.0; }
#endif