#pragma once
#include "afxwin.h"


// DB_TBRenameDlg �Ի���

class DB_TBRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(DB_TBRenameDlg)

public:
	DB_TBRenameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DB_TBRenameDlg();

// �Ի�������
	enum { IDD = IDD_DB_TBRENAMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_NewName;
public:
	CEdit m_eNewName;
	afx_msg void OnBnClickedOk2();
	CString GetNewName();
};
