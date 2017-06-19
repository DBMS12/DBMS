#pragma once
#include "afxwin.h"


// RegisterDlg �Ի���
typedef struct{
	CString name;
	CString password;
	CString permission;

}Users;
class RegisterDlg : public CDialog
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegisterDlg();

// �Ի�������
	enum { IDD = IDD_REGISTERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
