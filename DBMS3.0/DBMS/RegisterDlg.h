#pragma once
#include "afxwin.h"


// RegisterDlg 对话框
typedef struct{
	CString name;
	CString password;
	CString permission;

}Users;
class RegisterDlg : public CDialog
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RegisterDlg();

// 对话框数据
	enum { IDD = IDD_REGISTERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eName;
	CEdit m_ePassword;
	CButton m_rRead;
	CButton m_rWrite;
	afx_msg void OnBnClickedButton1();
private:
	int num;
	CStdioFile myFile;
	bool nameRe;
public:
	Users* myUsers;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
};
