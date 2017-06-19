#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// QueryDlg 对话框

class QueryDlg : public CDialog
{
	DECLARE_DYNAMIC(QueryDlg)

public:
	QueryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~QueryDlg();

// 对话框数据
	enum { IDD = IDD_QUERYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtrl;
	int m_nRow;
	int m_nColumn;
	int m_compType;
	CComboBox m_combobox;
	CEdit m_edit;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
