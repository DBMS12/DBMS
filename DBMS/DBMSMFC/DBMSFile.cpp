#include "stdafx.h"
#include "DBMSFile.h"
#include "DBMSMFC.h"
#include "DBMSMFCDlg.h"
#include "afxdialogex.h"
#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")
#include "shlwapi.h"  
#pragma comment(lib, "shlwapi.lib")
#include "Tree.h"
#include "Global.h"


DBMSFile::DBMSFile()
{
}


DBMSFile::~DBMSFile()
{
}

void DBMSFile::createDB(CString dbname)
{
	//dbname 是数据库名字
	//检查数据库名字是否重复。   不重复，写入文件。   重复，提示。

	CFile file;
	CString dbpath = _T("db");
	//E:\\软件工程\\MySQL\\DBMS\\DBMS\\DBMSMFC\\

	if (!PathIsDirectory(dbpath))//目录不存在
	{
		::CreateDirectory(dbpath, NULL);//创建目录,已有的话不影响 
	}
	else
	{
		dbpath += "\\";
		dbpath += dbname;
		
		//ShellExecute(NULL, L"open", L"db", NULL, NULL, SW_SHOWNORMAL);

		if (!PathIsDirectory(dbpath))
		{
			
			::CreateDirectory(dbpath, NULL);//创建目录,已有的话不影响 
			if (!file.Open(_T("DBNAME.db"), CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
			{
				return;
			}
			file.SeekToEnd();
			dbname += "#";
			file.Write((unsigned char*)(dbname.GetBuffer(0)), sizeof(dbname));
			file.Flush();
			file.Close();
		}
		else
		{
			MessageBox(NULL, _T("数据库已存在"), L"创建数据库", MB_OK);
		}
	}

	//显示在tree控件***        实现不了。。。。。。。。

	//插入节点
	//在根结点上添加数据库名字,图标
	//Tree dbtr;
	//dbtr.createT1(dbname);
}



void DBMSFile::createTB(CString dbname, CString tbname)
{
	//dbname 是数据库名字,  tbname  表名
	//检查表名字是否重复。   不重复，写入文件。   重复，提示。

	CFile file;
	CString tbpath = _T("db");
	tbpath += "\\";
	tbpath += dbname;


	if (!PathIsDirectory(tbpath))//目录不存在
	{
		::CreateDirectory(tbpath, NULL);//创建目录,已有的话不影响 
	}
	else
	{
		tbpath += "\\";
		tbpath += tbname;

		if (!PathIsDirectory(tbpath))
		{

			::CreateDirectory(tbpath, NULL);//创建目录,已有的话不影响 
			if (!file.Open(_T("TBNAME.tb"), CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
			{
				return;
			}
			file.SeekToEnd();
			tbname += "#";
			file.Write((unsigned char*)(tbname.GetBuffer(0)), sizeof(tbname));
			file.Flush();
			file.Close();
		}
		else
		{
			MessageBox(NULL, _T("表已存在"), L"创建表", MB_OK);
		}
	}

	//显示在tree控件***        实现不了。。。。。。。。

	//插入节点
	//在根结点上添加数据库名字,图标
	//Tree dbtr;
	//dbtr.createT1(dbname);
}