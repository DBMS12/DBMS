// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include "Struct.h"
#include "RegisterDlg.h"
#include <Windows.h>
#include "MainFrm.h"
#include "MD5Checksum.h"
// UserDlg �Ի���

IMPLEMENT_DYNAMIC(UserDlg, CDialog)

UserDlg::UserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(UserDlg::IDD, pParent)
	
{

}

UserDlg::~UserDlg()
{
}

void UserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eUser);
	DDX_Control(pDX, IDC_EDIT2, m_ePassword);
	
}


BEGIN_MESSAGE_MAP(UserDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &UserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &UserDlg::OnBnClickedButton2)
//	ON_WM_CLOSE()
ON_WM_CLOSE()
END_MESSAGE_MAP()


// UserDlg ��Ϣ�������


void UserDlg::OnBnClickedButton1() // ��½
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString name, password, totalnum;
	m_eUser.GetWindowTextW(name);
	m_ePassword.GetWindowTextW(password);
	CString pwd = CMD5Checksum::GetMD5(password);
	myFile.Open(L"res/login.txt", CFile::modeRead);
	myFile.ReadString(totalnum);
	num = _ttoi(totalnum);
	myUsers = new User[num];
	for (int i = 0; i < num; i++)
	{
		myFile.ReadString(myUsers[i].name);
		myFile.ReadString(myUsers[i].password);
		myFile.ReadString(myUsers[i].permission);

	}
	myFile.Close();
	for (int i = 0; i < num;i++)
	{
		if (myUsers[i].name == name)
		{
			if (myUsers[i].password == pwd)
			{
				if (myUsers[i].permission == "1")
				{
					login = 1;
					loginSuccess = true;
				}
				else if (myUsers[i].permission == "2")
				{
					login = 2;
					loginSuccess = true;
				}
			}
		}
	}

	if (loginSuccess == true)
		OnOK();
	else
	{
		MessageBox(L"�û������������");
		m_eUser.SetWindowTextW(_T(""));
		m_ePassword.SetWindowTextW(_T(""));
	}
		

}


void UserDlg::OnBnClickedButton2() // ע��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	RegisterDlg dlg;
	dlg.DoModal();
	
}


BOOL UserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	

	login = 0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



void UserDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	exit(0);
}


BOOL UserDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
