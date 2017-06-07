// CreateDBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "CreateDBDlg.h"
#include "DBMSFile.h"
#include "afxdialogex.h"
#include "Global.h"


// CreateDBDlg 对话框

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


// CreateDBDlg 消息处理程序



BOOL CreateDBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


INT_PTR CreateDBDlg::DoModal()
{
	// TODO:  在此添加专用代码和/或调用基类

	return CDialogEx::DoModal();
}


void CreateDBDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	//获得EDIT  
	CEdit* createDBedit;
	createDBedit = (CEdit*)GetDlgItem(IDC_EDIT_CREATEDB);
	//赋值  
	//createDBedit-> SetWindowText( _T("FOO ") );  
	//取值  
	CString str;
	createDBedit->GetWindowText(str);

	global.DATABASENAME = str;

	//MessageBox(str, _T("程序运行结果"), MB_OK);
	//str.ReleaseBuffer();

	if (str.IsEmpty())
	{
		MessageBox(_T("名字不能为空"), MB_OK);
	}
	else
	{
		//检查数据库名字是否重复。不重复，写入文件。重复，提示
		DBMSFile creaDB;
		creaDB.createDB(str);
	}

	CDialogEx::OnOK();
}


