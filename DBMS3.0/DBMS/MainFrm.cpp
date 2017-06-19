
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "DBMS.h"
#include <afx.h>
#include <atlstr.h>
#include <windows.h>
#include <direct.h>
#include "MainFrm.h"
#include "SQLDlg.h"
#include "UserDlg.h"
#include "UserDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_SYS_INIT, &CMainFrame::Initialization)
	ON_COMMAND(ID_SYSTEM_SQL, &CMainFrame::DealSql)
	

	ON_WM_CREATE()
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));


	SetTitle(_T("DBMS"));
	m_bAutoMenuEnable = FALSE;
	UserDlg dlg;
	dlg.DoModal();
	if (dlg.login == 1)
	{
		GetMenu()->GetSubMenu(0)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(1)->EnableMenuItem(2, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(1)->EnableMenuItem(3, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(1)->EnableMenuItem(5, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(2)->EnableMenuItem(3, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(2)->EnableMenuItem(4, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(2)->EnableMenuItem(6, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(3)->EnableMenuItem(3, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(4)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(4)->EnableMenuItem(2, MF_BYPOSITION | MF_DISABLED);
		GetMenu()->GetSubMenu(4)->EnableMenuItem(4, MF_BYPOSITION | MF_DISABLED);
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类
	
	bool m_wndSplitterCreated;
	m_wndSplitterCreated = m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDBView), CSize(160, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTableView), CSize(160, 0), pContext);

	m_pTableView = (CTableView *)m_wndSplitter.GetPane(0,1);
	m_pDBView = (CDBView *)m_wndSplitter.GetPane(0,0);
	

	
	return m_wndSplitterCreated;
}
// 初始化库
void CMainFrame::Initialization()
{
	CTreeCtrl &treeCtrl = m_pDBView->GetTreeCtrl();
	m_pTableView->ClearTable();
	treeCtrl.DeleteAllItems();
	CStdioFile file;
	if (file.Open(_T("file.txt"), CFile::modeReadWrite) == 0)
	{
		return ;
	}
	else
	{
		CString str;
		int n;
		char num[4];
		file.SeekToBegin();
		file.Read(&num, sizeof(int));
		n = atoi(num);
		n--;
		file.ReadString(str);
		file.ReadString(str);
		for (int i = 0; i < n+1; i++)
		{
			DeleteDirectory(str);
			file.ReadString(str);
		}
		file.Close();
		DeleteFile(_T("file.txt"));
	}

}

void CMainFrame::DeleteDirectory(CString strDir)
{
	if(strDir.IsEmpty())
	{ 
		RemoveDirectory(strDir);
		return;
	} 
	//首先删除文件及子文件夹 
	CFileFind ff;
	BOOL bFound = ff.FindFile(strDir+_T("\\*"),0);
	while(bFound) 
	{
		bFound = ff.FindNextFile();
		if(ff.GetFileName()== _T(".")||ff.GetFileName()== _T(".."))continue;
		//去掉文件(夹)只读等属性
		SetFileAttributes(ff.GetFilePath(),FILE_ATTRIBUTE_NORMAL);
		if(ff.IsDirectory())
		{
			//递归删除子文件夹 
			DeleteDirectory(ff.GetFilePath());
			RemoveDirectory(ff.GetFilePath()); 
		}
		else
		{ 
		DeleteFile(ff.GetFilePath());   //删除文件 
		} 
	} 
	ff.Close(); 
	//然后删除该文件夹
	RemoveDirectory(strDir);
}
void CMainFrame::DealSql(){
	SQLDlg dlg;
	dlg.DoModal();
}

