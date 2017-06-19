// QueryDlg.cpp : 实现文件
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

// QueryDlg 对话框

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


// QueryDlg 消息处理程序


void QueryDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL QueryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化listCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);   // 获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK;                              // 清除显示方式位
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // 选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;                          // 网格线
	m_listCtrl.SetExtendedStyle(dwStyle);                 // 设置扩展风格

	m_listCtrl.InsertColumn(0, CString("字段名称"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(1, CString("符号"), LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(2, CString("值"), LVCFMT_LEFT, 100);

	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	// 列表第一段  动态获取字段名称
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
	// 异常:  OCX 属性页应返回 FALSE
}


void QueryDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	
}


void QueryDlg::OnKillfocusEdit1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// 把用户输入的内容同步到列表上
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


void QueryDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtrl.GetItemCount();

	if (m_nRow >= 0 && m_nRow <= nCount)
	{
		// 设置接收框到列表对应位置
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


void QueryDlg::OnBnClickedOk() // 确定
{
	// TODO:  在此添加控件通知处理程序代码

	//m_listCtrl.GetItemText(i, 1) 获取第i行的第2个数，也就是符号
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

	pMainWnd->m_pTableView->DisplayFindRecords(vct); // 方法参数不全
	CDialog::OnOK();
}
