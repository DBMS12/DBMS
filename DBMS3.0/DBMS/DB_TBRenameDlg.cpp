// DB_TBRenameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "DB_TBRenameDlg.h"
#include "afxdialogex.h"


// DB_TBRenameDlg �Ի���

IMPLEMENT_DYNAMIC(DB_TBRenameDlg, CDialog)

DB_TBRenameDlg::DB_TBRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DB_TBRenameDlg::IDD, pParent)
{

}

DB_TBRenameDlg::~DB_TBRenameDlg()
{
}

void DB_TBRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eNewName);
}


BEGIN_MESSAGE_MAP(DB_TBRenameDlg, CDialog)
	ON_BN_CLICKED(IDOK2, &DB_TBRenameDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// DB_TBRenameDlg ��Ϣ�������


void DB_TBRenameDlg::OnBnClickedOk2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	 m_eNewName.GetWindowTextW(m_NewName);
	CDialog::OnOK();
}
CString DB_TBRenameDlg::GetNewName()
{
	return m_NewName;
}