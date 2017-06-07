#pragma once


// CreateTBDlg 对话框

class CreateTBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateTBDlg)

public:
	CreateTBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CreateTBDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CREATETB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	CString TABLENAME;
public:
	afx_msg void OnBnClickedOk();
	CString GetTBName();
};
