// FieldDlg.cpp : ʵ���ļ�
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

// CFieldDlg �Ի���
/* ����ֶζԻ���
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


// CFieldDlg ��Ϣ�������
BOOL CFieldDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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

void CFieldDlg::OnBnClickedButton1()// ȷ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�û�ѡ����ֶ���������
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
	judge = true; // ȷ���޸�

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
				MessageBox(L"�ֶ����ظ���");
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
				MessageBox(L"�ֶ����ظ���");
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


void CFieldDlg::OnBnClickedButton2()// ȡ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	judge = false;
	OnCancel();
}


void CFieldDlg::OnBnClickedCheck1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
				MessageBox(L"�ñ��Ѵ��������ˣ�");

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int select = m_comboBox.GetCurSel();// ѡ��������±�

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
	// TODO:  �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CFieldDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}
