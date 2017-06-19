// FieldDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "FieldDlg.h"
#include "afxdialogex.h"
#include "Transfer.h"
#include "MainFrm.h"
#include "DBView.h"
#include "TableEntity.h"

extern CString SDBName;
extern CString STBName;
extern bool isUpdate;

// CFieldDlg 对话框
/* 添加字段对话框
*/

IMPLEMENT_DYNAMIC(CFieldDlg, CDialog)

CFieldDlg::CFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFieldDlg::IDD, pParent)
{
}

CFieldDlg::~CFieldDlg()
{
}

void CFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Control(pDX, IDC_EDIT1, m_eFieldName);
	DDX_Control(pDX, IDC_EDIT3, m_Length);
	DDX_Control(pDX, IDC_EDIT6, m_eHint);
	DDX_Control(pDX, IDC_CHECK1, m_bPrimary);
	DDX_Control(pDX, IDC_CHECK2, m_bNull);
	DDX_Control(pDX, IDC_EDIT4, m_eMin);
	DDX_Control(pDX, IDC_EDIT5, m_eMax);
	DDX_Control(pDX, IDC_EDIT2, m_eFault);
}


BEGIN_MESSAGE_MAP(CFieldDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CFieldDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFieldDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CFieldDlg::OnBnClickedCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFieldDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CFieldDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CFieldDlg 消息处理程序
BOOL CFieldDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetWindowTextW(title);
	m_comboBox.AddString(_T("Varchar"));
	m_comboBox.AddString(_T("Number"));
	m_comboBox.AddString(_T("Integer"));
	m_comboBox.AddString(_T("Double"));
	m_comboBox.AddString(_T("Bool"));
	m_comboBox.AddString(_T("DateTime"));
	
	m_comboBox.SelectString(0, _T("Varchar"));
	m_eMin.EnableWindow(false);
	m_eMax.EnableWindow(false);
	ShowOldField();
	num = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	
}
void CFieldDlg::ShowOldField()
{

	m_eFieldName.SetWindowTextW(oldField[0]);
	m_comboBox.SetWindowTextW(oldField[1]);
	m_Length.SetWindowTextW(oldField[2]);
	m_eHint.SetWindowTextW(oldField[3]);
	m_eMin.SetWindowTextW(oldField[6]);
	m_eMax.SetWindowTextW(oldField[7]);
	m_eFault.SetWindowTextW(oldField[8]);

	if (oldField[4] == "Y")
	{
		m_bPrimary.SetCheck(true);
		m_bNull.EnableWindow(false);
	}
	else
		m_bPrimary.SetCheck(false);
	if (oldField[5] == "Y")
		m_bNull.SetCheck(true);
	else
		m_bNull.SetCheck(false);

}

void CFieldDlg::OnBnClickedButton1()// 确定
{
	// TODO:  在此添加控件通知处理程序代码
	// 获取用户选择的字段名字类型
	bool m_bp = false ,m_bn=false;
	bool allright = true;
    m_eFieldName.GetWindowTextW(myField.m_FieldName);
	m_comboBox.GetWindowTextW(myField.m_FieldType);
	m_Length.GetWindowTextW(myField.m_Length);
	m_eHint.GetWindowTextW(myField.m_Hint);
	m_eMin.GetWindowTextW(myField.m_Min);
	m_eMax.GetWindowTextW(myField.m_Max);
	m_eFault.GetWindowTextW(myField.m_Default);

	m_bp = m_bPrimary.GetCheck();
	if (m_bp)
		myField.m_Primary = "Y";
	else
		myField.m_Primary = "N";
	m_bn = m_bNull.GetCheck();
	if (m_bn)
		myField.m_Null = "Y";
	else
		myField.m_Null = "N";
	
	num++;

	//OnOK();
	judge = true; // 确定修改

	CString tbName = STBName,dbName = SDBName;
	if(isUpdate==false)
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(SDBName, STBName, v);
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].m_FieldName == myField.m_FieldName)
			{
				allright = false;
				MessageBox(L"字段名重复！");
				break;
			}
				

		}
		if (allright == true)
		{
			TableEntity entity;
			entity.addAttribute(myField, dbName, tbName);
			OnOK();
		}
		

	}
	else
	{
		Field field;
		field.m_FieldName = oldField[0];
		field.m_FieldType = oldField[1];
		field.m_Length = oldField[2];
		field.m_Hint = oldField[3];
		field.m_Primary = oldField[4];
		field.m_Null = oldField[5];
		field.m_Min = oldField[6];
		field.m_Max = oldField[7];
		field.m_Default = oldField[8];
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(SDBName, STBName, v);
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].m_FieldName == myField.m_FieldName)
			{
				allright = false;
				MessageBox(L"字段名重复！");
				break;
			}


		}
		if (allright == true)
		{
			TableEntity entity;
			entity.updateTable(field, myField, dbName, tbName);
			OnOK();
		}
		
	}
}


void CFieldDlg::OnBnClickedButton2()// 取消
{
	// TODO:  在此添加控件通知处理程序代码
	judge = false;
	OnCancel();
}


void CFieldDlg::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	bool judgePm = false;
	if (m_bPrimary.GetCheck())
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(SDBName, STBName, v);
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].m_Primary == "Y")
			{
				judgePm = true;
				m_bPrimary.SetCheck(false);
				MessageBox(L"该表已存在主键了！");

				break;
			}
		}
		if (judgePm == false)
		{
			m_bNull.EnableWindow(false);
		}
		
	}
		
	else
		m_bNull.EnableWindow(true);
}


void CFieldDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	int select = m_comboBox.GetCurSel();// 选择的类型下标

	switch (select)
	{
	case 0:
		m_Length.EnableWindow(true);
		m_eMin.EnableWindow(false);
		m_eMax.EnableWindow(false);
		break;
	case 1:
		m_Length.EnableWindow(true);
		m_eMin.EnableWindow(true);
		m_eMax.EnableWindow(true);
		break;
	case 2:
		m_Length.EnableWindow(false);
		m_eMin.EnableWindow(true);
		m_eMax.EnableWindow(true);
		break;
	case 3:
		m_Length.EnableWindow(false);
		m_eMin.EnableWindow(true);
		m_eMax.EnableWindow(true);
		break;
	case 4:
		m_Length.EnableWindow(false);
		m_eMin.EnableWindow(false);
		m_eMax.EnableWindow(false); 
		break;
	case 5:
		m_Length.EnableWindow(false);
		m_eMin.EnableWindow(false);
		m_eMax.EnableWindow(false);
		break;
	}
}
Field CFieldDlg::getField()
{
	return myField;
}


BOOL CFieldDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CFieldDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}
