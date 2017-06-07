
// DBMSMFCDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CDBMSMFCDlg 对话框
class CDBMSMFCDlg : public CDialogEx
{
// 构造
public:
	CDBMSMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DBMSMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CToolBar m_wndToolBar;
public:
	CTreeCtrl m_tc;
	CImageList m_imageList;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);

	//状态栏  杜
	CStatusBar m_StatusBar;
	CListCtrl m_programLangList;

public:
	afx_msg void OnDatabaseCreatedatabase();
	afx_msg void OnTableCreatetable();
	afx_msg void OnSystemExit();
	afx_msg void OnHelpAboutdbms();
};
