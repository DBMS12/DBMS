// QueryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "QueryDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TableEntity.h"
#include "RecordEntity.h"
#include <vector>
#include <map>

extern bool isUpdate;
extern CString SDBName;
extern CString STBName;
extern std::map<CString, CString> record;
extern std::map<CString, CString> OLDRecord;
extern int lastAct; //1 add,2 del,3update;

// QueryDlg �Ի���

IMPLEMENT_DYNAMIC(QueryDlg, CDialog)

QueryDlg::QueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(QueryDlg::IDD, pParent)
{
	
}

QueryDlg::~QueryDlg()
{
}

void QueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_COMBO2, m_combobox);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(QueryDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &QueryDlg::OnLvnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &QueryDlg::OnCbnSelchangeCombo2)
	ON_EN_CHANGE(IDC_EDIT1, &QueryDlg::OnEnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &QueryDlg::OnKillfocusEdit1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &QueryDlg::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &QueryDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// QueryDlg ��Ϣ�������


void QueryDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


BOOL QueryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

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
	m_listCtrl.InsertColumn(1, CString("����"), LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(2, CString("ֵ"), LVCFMT_LEFT, 100);

	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	// �б��һ��  ��̬��ȡ�ֶ�����
	for (int i = 0; i<v.size(); i++)
	{
		m_listCtrl.InsertItem(i, v[i].m_FieldName);
		m_listCtrl.SetItemText(i, 1, L"=");
	}
	
	/*m_listCtrl.InsertItem(0, _T("gag"));
	m_listCtrl.SetItemText(0, 1, L"=");
	m_combobox.InsertString(0, L"=");
	m_combobox.InsertString(1, L">");
	m_combobox.InsertString(2, L"<");*/

	m_edit.ShowWindow(FALSE);
	m_combobox.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void QueryDlg::OnCbnSelchangeCombo2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_compType = m_combobox.GetCurSel();
	CString value;
	switch (m_compType)
	{
	case 0:value = L"="; break;
	case 1:value = L">"; break;
	case 2:value = L"<"; break;
	default: break;
	}
	m_combobox.ShowWindow(SW_HIDE);
	m_listCtrl.SetItemText(m_nRow, m_nColumn, value);
}


void QueryDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	
}


void QueryDlg::OnKillfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// ���û����������ͬ�����б���
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


void QueryDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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

		if (m_nColumn == 2)
		{
			CString strTemp = m_listCtrl.GetItemText(m_nRow, m_nColumn);
			int nLength = strTemp.GetLength();
			m_edit.SetWindowText(strTemp);
			m_edit.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, 100, 20, SWP_SHOWWINDOW);
			m_edit.SetSel(nLength, nLength);
			m_edit.ShowWindow(TRUE);
			m_edit.SetFocus();
		}
		else if (m_nColumn == 1)
		{
			m_combobox.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, 40, 20, SWP_SHOWWINDOW);
			//m_edit.SetSel(nLength, nLength);
			m_combobox.ShowWindow(TRUE);
			m_combobox.SetFocus();
		}



	}
	*pResult = 0;
}


void QueryDlg::OnBnClickedOk() // ȷ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//m_listCtrl.GetItemText(i, 1) ��ȡ��i�еĵ�2������Ҳ���Ƿ���
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();

	//CString type = m_listCtrl.GetItemText(i, 1);
	//CString type = m_listCtrl.GetItemText(i, 1);
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	std::map<CString, CString> mp;
	mp.clear();
	for(int i=0;i<v.size();i++)
	{
		CString type = m_listCtrl.GetItemText(i, 1);
		CString value = m_listCtrl.GetItemText(i, 2);
		mp.insert(std::make_pair(v[i].m_FieldName,value));
	}

	std::vector<std::map<CString, CString>> vct;

	RecordEntity entity;
	entity.findRecord(SDBName,STBName,vct,mp);

	pMainWnd->m_pTableView->DisplayFindRecords(vct); // ����������ȫ
	CDialog::OnOK();
}
