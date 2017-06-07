// CreateTBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "CreateTBDlg.h"
#include "CreateDBDlg.h"
#include "DBMSFile.h"
#include "afxdialogex.h"
#include "Global.h"


// CreateTBDlg �Ի���

IMPLEMENT_DYNAMIC(CreateTBDlg, CDialogEx)

CreateTBDlg::CreateTBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CreateTBDlg::IDD, pParent)
{

}

CreateTBDlg::~CreateTBDlg()
{
}

void CreateTBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateTBDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateTBDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CreateTBDlg ��Ϣ�������


void CreateTBDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���EDIT  
	CEdit* createTBedit;
	createTBedit = (CEdit*)GetDlgItem(IDC_EDIT_CREATETB);
	//��ֵ  
	//createDBedit-> SetWindowText( _T("FOO ") );  
	//ȡֵ  
	CString str;
	createTBedit->GetWindowText(str);

	global.TABLENAME = str;

	if (str.IsEmpty())
	{
		MessageBox(_T("���ֲ���Ϊ��"), MB_OK);
	}
	else
	{
		//������ݿ������Ƿ��ظ������ظ���д���ļ����ظ�����ʾ

		//CreateDBDlg db;
		//CString dbname = db.GetDBName();
		CString dbname = global.DATABASENAME;

		DBMSFile creaTB;
		creaTB.createTB(dbname,str);//dbname,tbname
	}



	CDialogEx::OnOK();
}

CString CreateTBDlg::GetTBName()
{
	return TABLENAME;
}