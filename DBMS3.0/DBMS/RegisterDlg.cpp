// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#include "MD5Checksum.h"
#include <iostream>
// RegisterDlg 对话框

IMPLEMENT_DYNAMIC(RegisterDlg, CDialog)

RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RegisterDlg::IDD, pParent)
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eName);
	DDX_Control(pDX, IDC_EDIT2, m_ePassword);
	DDX_Control(pDX, IDC_RADIO1, m_rRead);
	DDX_Control(pDX, IDC_RADIO2, m_rWrite);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &RegisterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &RegisterDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// RegisterDlg 消息处理程序


void RegisterDlg::OnBnClickedButton1() // 确定
{
	// TODO:  在此添加控件通知处理程序代码
	CString name, password, permission, str;
	m_eName.GetWindowTextW(name);
	m_ePassword.GetWindowTextW(password);

	if (m_rRead.GetCheck())
	{
		permission = "1";
	}
	else if (m_rWrite.GetCheck())
	{
		permission = "2";
	}
	else
	{
		permission = "1";
	}
	for (int i = 0; i < num; i++)
	{
		if (name == myUsers[i].name)
		{
			MessageBox(_T("用户名已存在！"));
			nameRe = true;
		}
	}
	if (nameRe == false)
	{
		myFile.Open(L"res/login.txt", CFile::modeCreate | CFile::modeWrite);
		str.Format(_T("%d"), num + 1);
		myFile.WriteString(str + "\n");
		myFile.WriteString(name + "\n");

		CString pwd = CMD5Checksum::GetMD5(password);

		myFile.WriteString(pwd + "\n");
		myFile.WriteString(permission + "\n");
		for (int i = 0; i < num; i++)
		{
			myFile.WriteString(myUsers[i].name + "\n");
			myFile.WriteString(myUsers[i].password + "\n");
			myFile.WriteString(myUsers[i].permission + "\n");
		}


		myFile.Close();
		MessageBox(L"注册成功！");
	}
	
	
	OnOK();

}


BOOL RegisterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString totalnum;
	myFile.Open(L"res/login.txt",CFile::modeRead);
	myFile.ReadString(totalnum);
	num = _ttoi(totalnum);
	myUsers = new Users[num];

	for (int i = 0; i < num; i++)
	{
		myFile.ReadString(myUsers[i].name);
		myFile.ReadString(myUsers[i].password);
		myFile.ReadString(myUsers[i].permission);

	}
	myFile.Close();
	// TODO:  在此添加额外的初始化
	m_rRead.SetCheck(1);
	nameRe = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void RegisterDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	OnCancel();
}
