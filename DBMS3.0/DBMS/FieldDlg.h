#pragma once
#include "afxwin.h"
#include"Struct.h"

// CFieldDlg �Ի���

class CFieldDlg : public CDialog
{
	DECLARE_DYNAMIC(CFieldDlg)

public:
	CFieldDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFieldDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_FIELDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	int num;// �ֶεĸ���
	Field myField;// �ֶ������ͽṹ������
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
	
	CString oldField[9]; // ���ڸ����ֶεľ��ֶ��趨
	bool judge; // �ж��޸��Ƿ�ȷ��/ȡ��
	CString title; // �Ի���ı���

	afx_msg void OnEnChangeEdit1();
};
