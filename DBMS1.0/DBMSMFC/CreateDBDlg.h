#pragma once


// CreateDBDlg �Ի���

class CreateDBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDBDlg)

public:
	CreateDBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CreateDBDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CREATEDB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString DATABASE;
public:
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
	CString GetDBName();
};
