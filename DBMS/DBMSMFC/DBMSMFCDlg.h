
// DBMSMFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CDBMSMFCDlg �Ի���
class CDBMSMFCDlg : public CDialogEx
{
// ����
public:
	CDBMSMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DBMSMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	//״̬��  ��
	CStatusBar m_StatusBar;
	CListCtrl m_programLangList;

public:
	afx_msg void OnDatabaseCreatedatabase();
	afx_msg void OnTableCreatetable();
	afx_msg void OnSystemExit();
	afx_msg void OnHelpAboutdbms();
};
