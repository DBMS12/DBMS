
// MainFrm.h : CMainFrame 类的接口
//
#include"DBView.h"
#include"TableView.h"

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DeleteDirectory(CString strDir);
// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CSplitterWnd	  m_wndSplitter;
public:
	CTableView *m_pTableView;  //右边显示数据视图指针
	CDBView *m_pDBView;			//左边树状图窗口指针
// 生成的消息映射函数
public:
	void Initialization();
	void DealSql();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	

};


