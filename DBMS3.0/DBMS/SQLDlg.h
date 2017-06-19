#pragma once
#include "afxwin.h"


// SQLDlg 对话框

class SQLDlg : public CDialog
{
	DECLARE_DYNAMIC(SQLDlg)

public:
	SQLDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SQLDlg();

// 对话框数据
	enum { IDD = IDD_SQLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eSql;
	afx_msg void OnBnClickedOk();
	void Analysis(CString,CString);

   HTREEITEM FindItem(CTreeCtrl,HTREEITEM , CString );
	CString m_db;
	CString m_sql;	
	afx_msg void OnBnClickedCancel();
	CEdit m_dbname;
};
