#pragma once
#include "afxwin.h"


// UserDlg 对话框
typedef struct{
	CString name;
	CString password;
	CString permission;

}User;
class UserDlg : public CDialog
{
	DECLARE_DYNAMIC(UserDlg)

public:
	UserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UserDlg();

// 对话框数据
	enum { IDD = IDD_USERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_tPermission;
//	int m_rRead;
//	int m_rWrite;
	CEdit m_eUser;
	CEdit m_ePassword;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CButton m_rRead;
	CButton m_rWrite;
//	afx_msg void OnClose();
private:
	int num;
	CStdioFile myFile;
	User* myUsers;
	bool fileEmpty;
	bool loginSuccess;
	
public:
	int login;
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
