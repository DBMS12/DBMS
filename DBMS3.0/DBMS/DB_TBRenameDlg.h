#pragma once
#include "afxwin.h"


// DB_TBRenameDlg 对话框

class DB_TBRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(DB_TBRenameDlg)

public:
	DB_TBRenameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DB_TBRenameDlg();

// 对话框数据
	enum { IDD = IDD_DB_TBRENAMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_NewName;
public:
	CEdit m_eNewName;
	afx_msg void OnBnClickedOk2();
	CString GetNewName();
};
