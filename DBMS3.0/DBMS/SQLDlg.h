#pragma once
#include "afxwin.h"


// SQLDlg �Ի���

class SQLDlg : public CDialog
{
	DECLARE_DYNAMIC(SQLDlg)

public:
	SQLDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SQLDlg();

// �Ի�������
	enum { IDD = IDD_SQLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
