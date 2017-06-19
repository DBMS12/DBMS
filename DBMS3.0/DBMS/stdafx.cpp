
// stdafx.cpp : 只包括标准包含文件的源文件
// DBMS.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include <map>

CString SDBName;
CString STBName;
bool isUpdate = false;
std::map<CString, CString> record;
std::map<CString, CString> OLDRecord;
int lastAct = -1; //1 add,2 del,3update
CString P;