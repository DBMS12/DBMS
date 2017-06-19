#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// RecordDlg 对话框

class RecordDlg : public CDialog
{
	DECLARE_DYNAMIC(RecordDlg)

public:
	RecordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RecordDlg();

// 对话框数据
	enum { IDD = IDD_RECORDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_nRow, m_nColumn;
public:
	CListCtrl m_listCtrl;
	CEdit m_edit;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ShowOldRecord();
	CString GetNewRecord();
public:
	CString title; // 对话框的标题添加记录还是修改记录
	int totalNumber; // 该表字段的总数，用于更改记录
	CString oldRecord[50];
	bool judge;
	CString *newRecord;
	bool allright;
};
