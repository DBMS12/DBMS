#pragma once
#include "afxwin.h"


// DB_TBNameDlg �Ի���

class DB_TBNameDlg : public CDialog
{
	DECLARE_DYNAMIC(DB_TBNameDlg)

public:
	DB_TBNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DB_TBNameDlg();

// �Ի�������
	enum { IDD = IDD_DB_TBNAMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
