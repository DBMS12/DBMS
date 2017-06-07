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
	//dbname �����ݿ�����
	//������ݿ������Ƿ��ظ���   ���ظ���д���ļ���   �ظ�����ʾ��

	CFile file;
	CString dbpath = _T("db");
	//E:\\�������\\MySQL\\DBMS\\DBMS\\DBMSMFC\\

	if (!PathIsDirectory(dbpath))//Ŀ¼������
	{
		::CreateDirectory(dbpath, NULL);//����Ŀ¼,���еĻ���Ӱ�� 
	}
	else
	{
		dbpath += "\\";
		dbpath += dbname;
		
		//ShellExecute(NULL, L"open", L"db", NULL, NULL, SW_SHOWNORMAL);

		if (!PathIsDirectory(dbpath))
		{
			
			::CreateDirectory(dbpath, NULL);//����Ŀ¼,���еĻ���Ӱ�� 
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
			MessageBox(NULL, _T("���ݿ��Ѵ���"), L"�������ݿ�", MB_OK);
		}
	}

	//��ʾ��tree�ؼ�***        ʵ�ֲ��ˡ���������������

	//����ڵ�
	//�ڸ������������ݿ�����,ͼ��
	//Tree dbtr;
	//dbtr.createT1(dbname);
}



void DBMSFile::createTB(CString dbname, CString tbname)
{
	//dbname �����ݿ�����,  tbname  ����
	//���������Ƿ��ظ���   ���ظ���д���ļ���   �ظ�����ʾ��

	CFile file;
	CString tbpath = _T("db");
	tbpath += "\\";
	tbpath += dbname;


	if (!PathIsDirectory(tbpath))//Ŀ¼������
	{
		::CreateDirectory(tbpath, NULL);//����Ŀ¼,���еĻ���Ӱ�� 
	}
	else
	{
		tbpath += "\\";
		tbpath += tbname;

		if (!PathIsDirectory(tbpath))
		{

			::CreateDirectory(tbpath, NULL);//����Ŀ¼,���еĻ���Ӱ�� 
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
			MessageBox(NULL, _T("���Ѵ���"), L"������", MB_OK);
		}
	}

	//��ʾ��tree�ؼ�***        ʵ�ֲ��ˡ���������������

	//����ڵ�
	//�ڸ������������ݿ�����,ͼ��
	//Tree dbtr;
	//dbtr.createT1(dbname);
}