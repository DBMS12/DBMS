
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// DBMS.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
#include <map>

CString SDBName;
CString STBName;
bool isUpdate = false;
std::map<CString, CString> record;
std::map<CString, CString> OLDRecord;
int lastAct = -1; //1 add,2 del,3update
CString P;