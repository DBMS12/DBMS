#pragma once
#include"TableView.h"
#include"Struct.h"
#include"DB_TBNameDlg.h"
// CDBView ��ͼ

class CDBView : public CTreeView
{
	DECLARE_DYNCREATE(CDBView)

protected:
	CDBView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	int num;// �ֶεĸ���
	CString m_DaTaName;// ����

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
