// DB_TBNameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "DB_TBNameDlg.h"
#include "afxdialogex.h"


// DB_TBNameDlg �Ի���

IMPLEMENT_DYNAMIC(DB_TBNameDlg, CDialog)

DB_TBNameDlg::DB_TBNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DB_TBNameDlg::IDD, pParent)
{

}

DB_TBNameDlg::~DB_TBNameDlg()
{
}

void DB_TBNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eName);
	DDX_Control(pDX, IDC_STATIC1, m_tTitle);
}


BEGIN_MESSAGE_MAP(DB_TBNameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &DB_TBNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()



CString DB_TBNameDlg::GetDBTBName()
{
	return m_DBTBName;
}

void DB_TBNameDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_eName.GetWindowTextW(m_DBTBName);
	CDialog::OnOK();
}

