
// MainFrm.h : CMainFrame ��Ľӿ�
//
#include"DBView.h"
#include"TableView.h"

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DeleteDirectory(CString strDir);
// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CSplitterWnd	  m_wndSplitter;
public:
	CTableView *m_pTableView;  //�ұ���ʾ������ͼָ��
	CDBView *m_pDBView;			//�����״ͼ����ָ��
// ���ɵ���Ϣӳ�亯��
public:
	void Initialization();
	void DealSql();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	

};


