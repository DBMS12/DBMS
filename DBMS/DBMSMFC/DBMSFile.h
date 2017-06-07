#pragma once
#include "shlwapi.h"  
#pragma comment(lib, "shlwapi.lib")

class DBMSFile
{
public:
	//CTreeCtrl m_tcdb;
public:
	DBMSFile();
	~DBMSFile();
	void createDB(CString dbname);
	void createTB(CString dbname, CString tbname);
};

