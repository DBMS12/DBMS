// CreateDBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "CreateDBDlg.h"
#include "DBMSFile.h"
#include "afxdialogex.h"
#include "Global.h"


// CreateDBDlg �Ի���

IMPLEMENT_DYNAMIC(CreateDBDlg, CDialogEx)

CreateDBDlg::CreateDBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CreateDBDlg::IDD, pParent)
{

}

CreateDBDlg::~CreateDBDlg()
{
}

void CreateDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateDBDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateDBDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CreateDBDlg ��Ϣ�������



BOOL CreateDBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


INT_PTR CreateDBDlg::DoModal()
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CDialogEx::DoModal();
}


void CreateDBDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//���EDIT  
	CEdit* createDBedit;
	createDBedit = (CEdit*)GetDlgItem(IDC_EDIT_CREATEDB);
	//��ֵ  
	//createDBedit-> SetWindowText( _T("FOO ") );  
	//ȡֵ  
	CString str;
	createDBedit->GetWindowText(str);

	global.DATABASENAME = str;

	//MessageBox(str, _T("�������н��"), MB_OK);
	//str.ReleaseBuffer();

	if (str.IsEmpty())
	{
		MessageBox(_T("���ֲ���Ϊ��"), MB_OK);
	}
	else
	{
		//������ݿ������Ƿ��ظ������ظ���д���ļ����ظ�����ʾ
		DBMSFile creaDB;
		creaDB.createDB(str);
	}

	CDialogEx::OnOK();
}


