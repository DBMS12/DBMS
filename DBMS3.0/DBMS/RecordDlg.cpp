// RecordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include <vector>
#include <map>
#include "TableEntity.h"
#include "Struct.h"
#include "RecordEntity.h"

extern bool isUpdate;
extern CString SDBName;
extern CString STBName;
extern std::map<CString, CString> record;
extern std::map<CString, CString> OLDRecord;
// RecordDlg �Ի���

IMPLEMENT_DYNAMIC(RecordDlg, CDialog)

RecordDlg::RecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RecordDlg::IDD, pParent)
{

}

RecordDlg::~RecordDlg()
{
}

void RecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(RecordDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT1, &RecordDlg::OnEnKillfocusEdit1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &RecordDlg::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &RecordDlg::OnBnClickedOk)
//	ON_WM_UNICHAR()
END_MESSAGE_MAP()


// RecordDlg ��Ϣ�������


BOOL RecordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this-> SetWindowTextW(title);
	//��ʼ��listCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);   // ��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK;                              // �����ʾ��ʽλ
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;                          // ������
	m_listCtrl.SetExtendedStyle(dwStyle);                 // ������չ���

	m_listCtrl.InsertColumn(0, CString("�ֶ�����"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(1, CString("�ֶ�����"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(2, CString("����"), LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(3, CString("Ϊ��"), LVCFMT_LEFT, 58);
	m_listCtrl.InsertColumn(4, CString("������ֵ"), LVCFMT_LEFT, 100);
	
	newRecord = new CString[totalNumber];
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);
	totalNumber = v.size();
	for(int i=0;i<totalNumber;i++)
	{
		m_listCtrl.InsertItem(i, v[i].m_FieldName);
		m_listCtrl.SetItemText(i, 1, v[i].m_FieldType);
		m_listCtrl.SetItemText(i, 2, v[i].m_Primary);
		m_listCtrl.SetItemText(i, 3, v[i].m_Null);
	}
	// ������ֵ
	//ShowOldRecord();
	m_edit.ShowWindow(FALSE);
	judge = false;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void RecordDlg::ShowOldRecord()
{
	m_listCtrl.InsertItem(0, _T(""));
	for (int i = 0; i < totalNumber; i++)
	{
		m_listCtrl.SetItemText(i, 4, oldRecord[i]);
	}
}


void RecordDlg::OnEnKillfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// ���û����������ͬ�����б���
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


void RecordDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtrl.GetItemCount();

	if (m_nRow >= 0 && m_nRow <= nCount)
	{
		// ���ý��տ��б��Ӧλ��
		CRect rtEdit, rtClient;
		m_listCtrl.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		m_listCtrl.GetSubItemRect(m_nRow, m_nColumn, LVIR_LABEL, rtEdit);
		rtEdit.left += rtClient.left + 0;
		rtEdit.top += rtClient.top + 0;
		rtEdit.bottom += 0;

		if (m_nColumn == 4)
		{
			CString strTemp = m_listCtrl.GetItemText(m_nRow, m_nColumn);
			int nLength = strTemp.GetLength();
			m_edit.SetWindowText(strTemp);
			m_edit.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, 100, 20, SWP_SHOWWINDOW);
			m_edit.SetSel(nLength, nLength);
			m_edit.ShowWindow(TRUE);
			m_edit.SetFocus();
		}

	}
	*pResult = 0;
}


void RecordDlg::OnBnClickedOk() // ȷ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�û�������߸��ĺ����ֵ
	allright = true;
	RecordEntity entity;
	int rnum;
	std::vector<std::map<CString, CString>> vct;
	entity.readRecord(SDBName, STBName,vct,rnum);
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);
	
	for (int i = 0; i < v.size(); i++)
	{
		if (m_listCtrl.GetItemText(i, 2) == "Y")
		{
			for (int n = 0; n < rnum; n++)
			{
				std::map<CString, CString> tmp = vct[n];
				if (m_listCtrl.GetItemText(i, 4) == tmp[v[i].m_FieldName] || m_listCtrl.GetItemText(i, 4) == "")
				{
					allright = false;
					MessageBox(L"Υ������Ψһ������");
					break;
				}
				
			}
			
		}
		if (m_listCtrl.GetItemText(i, 3) == "Y")
		{
			if (m_listCtrl.GetItemText(i, 4) == "")
			{
				allright = false;
				MessageBox(L"Υ���ǿ�Լ��������");
				break;
			}
		}
		
		
	}
	record.clear();
	if (allright == true)
	{
		for (int i = 0; i < v.size(); i++)
		{
			newRecord[i] = m_listCtrl.GetItemText(i, 4);
			record.insert(std::make_pair(v[i].m_FieldName, newRecord[i]));
		}
		CDialog::OnOK();
		
	}
	else
	{
		for (int i = 0; i < v.size(); i++)
		{
			m_listCtrl.SetItemText(i, 4, L"");
		}
	}
	judge = true;
	
}

BOOL RecordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
