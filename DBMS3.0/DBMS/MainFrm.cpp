
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���
	
	bool m_wndSplitterCreated;
	m_wndSplitterCreated = m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDBView), CSize(160, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTableView), CSize(160, 0), pContext);

	m_pTableView = (CTableView *)m_wndSplitter.GetPane(0,1);
	m_pDBView = (CDBView *)m_wndSplitter.GetPane(0,0);
	

	
	return m_wndSplitterCreated;
}
// ��ʼ����
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
	//����ɾ���ļ������ļ��� 
	CFileFind ff;
	BOOL bFound = ff.FindFile(strDir+_T("\\*"),0);
	while(bFound) 
	{
		bFound = ff.FindNextFile();
		if(ff.GetFileName()== _T(".")||ff.GetFileName()== _T(".."))continue;
		//ȥ���ļ�(��)ֻ��������
		SetFileAttributes(ff.GetFilePath(),FILE_ATTRIBUTE_NORMAL);
		if(ff.IsDirectory())
		{
			//�ݹ�ɾ�����ļ��� 
			DeleteDirectory(ff.GetFilePath());
			RemoveDirectory(ff.GetFilePath()); 
		}
		else
		{ 
		DeleteFile(ff.GetFilePath());   //ɾ���ļ� 
		} 
	} 
	ff.Close(); 
	//Ȼ��ɾ�����ļ���
	RemoveDirectory(strDir);
}
void CMainFrame::DealSql(){
	SQLDlg dlg;
	dlg.DoModal();
}

