#pragma once


// CreateDBDlg 对话框

class CreateDBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDBDlg)

public:
	CreateDBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CreateDBDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CREATEDB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString DATABASE;
public:
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
	CString GetDBName();
};
