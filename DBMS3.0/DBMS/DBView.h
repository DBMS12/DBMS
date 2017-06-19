#pragma once
#include"TableView.h"
#include"Struct.h"
#include"DB_TBNameDlg.h"
// CDBView 视图

class CDBView : public CTreeView
{
	DECLARE_DYNCREATE(CDBView)

protected:
	CDBView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDBView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	CTreeCtrl* treeCtrl;
	CImageList m_treeImageList;
	HTREEITEM m_hSelectedItem;
	int num;// 字段的个数
	CString m_DaTaName;// 表名

public:
	void AddData();
	void OpenData();
	void BackupData();
	void RnameData();
	void DeleteData();

	void AddTable();
	void SelectTable();
	void ShowAllTable();
	void EmptyTable();
	void DeleteTable();
	void RnameTable();
	void OnInitialUpdate();

	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};
