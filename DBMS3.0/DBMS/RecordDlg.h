#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// RecordDlg �Ի���

class RecordDlg : public CDialog
{
	DECLARE_DYNAMIC(RecordDlg)

public:
	RecordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RecordDlg();

// �Ի�������
	enum { IDD = IDD_RECORDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	int m_nRow, m_nColumn;
public:
	CListCtrl m_listCtrl;
	CEdit m_edit;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ShowOldRecord();
	CString GetNewRecord();
public:
	CString title; // �Ի���ı�����Ӽ�¼�����޸ļ�¼
	int totalNumber; // �ñ��ֶε����������ڸ��ļ�¼
	CString oldRecord[50];
	bool judge;
	CString *newRecord;
	bool allright;
};
