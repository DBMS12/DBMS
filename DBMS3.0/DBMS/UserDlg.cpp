// UserDlg.cpp : 实现文件
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
// UserDlg 对话框

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


// UserDlg 消息处理程序


void UserDlg::OnBnClickedButton1() // 登陆
{
	// TODO:  在此添加控件通知处理程序代码
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
		MessageBox(L"用户名或密码错误！");
		m_eUser.SetWindowTextW(_T(""));
		m_ePassword.SetWindowTextW(_T(""));
	}
		

}


void UserDlg::OnBnClickedButton2() // 注册
{
	// TODO:  在此添加控件通知处理程序代码
	
	RegisterDlg dlg;
	dlg.DoModal();
	
}


BOOL UserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	

	login = 0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void UserDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	exit(0);
}


BOOL UserDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
