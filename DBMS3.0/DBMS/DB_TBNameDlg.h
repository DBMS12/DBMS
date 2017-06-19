#pragma once
#include "afxwin.h"


// DB_TBNameDlg 对话框

class DB_TBNameDlg : public CDialog
{
	DECLARE_DYNAMIC(DB_TBNameDlg)

public:
	DB_TBNameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DB_TBNameDlg();

// 对话框数据
	enum { IDD = IDD_DB_TBNAMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eName;
private:
	CString m_DBTBName;
	CStatic m_tTitle;
public:
	CString GetDBTBName();
	afx_msg void OnBnClickedOk();
	
};
