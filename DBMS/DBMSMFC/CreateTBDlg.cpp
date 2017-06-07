// CreateTBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "CreateTBDlg.h"
#include "CreateDBDlg.h"
#include "DBMSFile.h"
#include "afxdialogex.h"
#include "Global.h"


// CreateTBDlg 对话框

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


// CreateTBDlg 消息处理程序


void CreateTBDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//获得EDIT  
	CEdit* createTBedit;
	createTBedit = (CEdit*)GetDlgItem(IDC_EDIT_CREATETB);
	//赋值  
	//createDBedit-> SetWindowText( _T("FOO ") );  
	//取值  
	CString str;
	createTBedit->GetWindowText(str);

	global.TABLENAME = str;

	if (str.IsEmpty())
	{
		MessageBox(_T("名字不能为空"), MB_OK);
	}
	else
	{
		//检查数据库名字是否重复。不重复，写入文件。重复，提示

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