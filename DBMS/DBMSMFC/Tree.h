#pragma once
#include "afxcmn.h"
#include <afxcview.h>


// Tree �Ի���

class Tree : public CTreeView//CDialogEx
{
	DECLARE_DYNAMIC(Tree)

public:
	Tree();   // ��׼���캯��,CWnd* pParent = NULL
	virtual ~Tree();

// �Ի�������
	//enum { IDD = IDD_DBMSMFC_DIALOG };

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


protected:
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	CTreeCtrl *m_tc;
	CImageList m_imageList;

	HTREEITEM m_hCurrDBItem;
	HTREEITEM m_hCurrTBItem;

public:
	void createT1(CString dbname);
	void createT2(HTREEITEM hItem, CString tbname);
	void createT3(HTREEITEM hSubItem, CString fieldname);
	void DisplayDBList();
	//virtual BOOL OnInitDialog();
	void OnInitialUpdate();
	CString GetSelectedDBName();
	CString GetSelectedTBName();
};
