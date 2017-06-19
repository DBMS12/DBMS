#pragma once
#include "afxwin.h"
#include"Struct.h"

// CFieldDlg 对话框

class CFieldDlg : public CDialog
{
	DECLARE_DYNAMIC(CFieldDlg)

public:
	CFieldDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFieldDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_FIELDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	int num;// 字段的个数
	Field myField;// 字段名类型结构体数组
public:
	CComboBox m_comboBox;
	CEdit m_eFieldName;
	CEdit m_Length;
	CEdit m_eHint;
	CButton m_bPrimary;
	CButton m_bNull;
	CEdit m_eMin;
	CEdit m_eMax;
	CEdit m_eFault;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnCbnSelchangeCombo1();
	Field getField();
	void ShowOldField();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	
	CString oldField[9]; // 用于更改字段的旧字段设定
	bool judge; // 判断修改是否确定/取消
	CString title; // 对话框的标题

	afx_msg void OnEnChangeEdit1();
};
