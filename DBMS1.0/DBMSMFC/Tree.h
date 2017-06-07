#pragma once
#include "afxcmn.h"
#include <afxcview.h>


// Tree 对话框

class Tree : public CTreeView//CDialogEx
{
	DECLARE_DYNAMIC(Tree)

public:
	Tree();   // 标准构造函数,CWnd* pParent = NULL
	virtual ~Tree();

// 对话框数据
	//enum { IDD = IDD_DBMSMFC_DIALOG };

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


protected:
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
