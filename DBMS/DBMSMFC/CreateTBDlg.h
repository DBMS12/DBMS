#pragma once


// CreateTBDlg �Ի���

class CreateTBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateTBDlg)

public:
	CreateTBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CreateTBDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CREATETB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
protected:
	CString TABLENAME;
public:
	afx_msg void OnBnClickedOk();
	CString GetTBName();
};
