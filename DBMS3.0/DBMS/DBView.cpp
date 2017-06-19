// DBView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBView.h"
#include "DB_TBRenameDlg.h"
#include "MainFrm.h"
#include "QueryDlg.h"
#include "DBEntity.h"
#include <vector>
#include "TableEntity.h"



extern CString SDBName;
extern CString STBName;

// CDBView
/* CDBView 针对左侧树视图的显示操作
 * 涉及新建库、新建表等方法
 */

IMPLEMENT_DYNCREATE(CDBView, CTreeView)

CDBView::CDBView()
{
	m_hSelectedItem = NULL;
	
}

CDBView::~CDBView()
{
}

BEGIN_MESSAGE_MAP(CDBView, CTreeView)
	ON_COMMAND(ID_DATA_ADD, &CDBView::AddData)
	ON_COMMAND(ID_DATA_OPEN, &CDBView::OpenData)
	ON_COMMAND(ID_DATA_BACKUP, &CDBView::BackupData)
	ON_COMMAND(ID_DATA_RNAME, &CDBView::RnameData)
	ON_COMMAND(ID_DATA_DELETE, &CDBView::DeleteData)

	ON_COMMAND(ID_TABLE_ADD, &CDBView::AddTable)
	ON_COMMAND(ID_TABLE_SELECT, &CDBView::SelectTable)
	ON_COMMAND(ID_TABLE_SHOWALL, &CDBView::ShowAllTable)
	ON_COMMAND(ID_TABLE_EMPTY, &CDBView::EmptyTable)
	ON_COMMAND(ID_TABLE_RENAME, &CDBView::RnameTable)
	ON_COMMAND(ID_TABLE_DELETE, &CDBView::DeleteTable)

	
	
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDBView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CDBView 诊断

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CTreeView::AssertValid();

}

#ifndef _WIN32_WCE
void CDBView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDBView 消息处理程序
// 初始化

void CDBView::OnInitialUpdate()
{
	
	CTreeView::OnInitialUpdate();

	treeCtrl = &GetTreeCtrl();
	
	DWORD dwStyles = GetWindowLong(treeCtrl->m_hWnd, GWL_STYLE);
	dwStyles |= TVS_EDITLABELS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	SetWindowLong(treeCtrl->m_hWnd, GWL_STYLE, dwStyles);
	// 加载图标
	m_treeImageList.Create(16, 16, ILC_MASK, 4, 1);
	m_treeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_DATA));
	m_treeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_TABLE));

	treeCtrl->SetImageList(&m_treeImageList, TVSIL_NORMAL);	

	//初始化树
	DBEntity entity(_T("init"));
	std::vector<CString> v = entity.GetAllDBName();
	int num = v.size() - 1;
	for(int i=0;i<num;i++)
	{
		HTREEITEM hRoot = treeCtrl->InsertItem(v[i], 0, 0);
		std::vector<CString> tmp;
		TableEntity tbe;
		tmp = tbe.GetAllTBName(v[i]);
		for(int j=0;j<tmp.size();j++)
		{
			treeCtrl->InsertItem(tmp[j], 1, 1, hRoot);
		}
	}
	
}
// 新建库
void CDBView::AddData()
{
	treeCtrl = &GetTreeCtrl();
	DB_TBNameDlg dlg;

	dlg.DoModal();
	m_DaTaName = dlg.GetDBTBName();
	if (!m_DaTaName.IsEmpty())
	{
		HTREEITEM hRoot = treeCtrl->InsertItem(m_DaTaName, 0, 0, TVI_ROOT, TVI_LAST);
		treeCtrl->Expand(hRoot, TVE_EXPAND);
	}

	DBEntity entity(m_DaTaName);
	entity.CreateDB();
}
// 打开库
void CDBView::OpenData()
{
	/*
	 *初始化树视图只列出库的名字，并不列出表的名字
	 *用户选择打开库的时候，加载选中库的所有表显示出来
	 */

	HTREEITEM hItem;
	CString m_SelectDBName;// 获得当前选中的库的名字
	
	hItem = treeCtrl->GetSelectedItem();
	m_SelectDBName = treeCtrl->GetItemText(hItem);

	treeCtrl->Expand(hItem, TVE_EXPAND);// 展开
}
// 备份库
void CDBView::BackupData()
{
	CTreeCtrl &treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetSelectedItem();
	CString m_DBname = treeCtrl.GetItemText(hItem);
	DBEntity entity(m_DBname);
	entity.BackupsDB(m_DBname);
	MessageBox(_T("备份成功！"));
}
// 重命名
void CDBView::RnameData()
{
	DB_TBRenameDlg dlg;
	CString m_newName; // 新名字
	CString m_oldName;
	HTREEITEM hItem;

	hItem = treeCtrl->GetSelectedItem();

	if (treeCtrl->GetParentItem(hItem) == 0)
	{
		dlg.DoModal();
		m_newName = dlg.GetNewName();
		m_oldName = treeCtrl->GetItemText(hItem);
		DBEntity entity(m_newName);
		entity.RenameDB(m_oldName,m_newName);
		treeCtrl->SetItemText(hItem, m_newName); // 在视图上更改名字
	}
	else
		MessageBox(_T("请对库进行重命名操作！"));
}
// 删除库
void CDBView::DeleteData()
{
	CTreeCtrl &treeCtrl = GetTreeCtrl();
	HTREEITEM hItem1;
	HTREEITEM hItem = treeCtrl.GetSelectedItem();
	
	CString m_DBname = treeCtrl.GetItemText(hItem);

	if (treeCtrl.GetParentItem(hItem) != 0)
	{
		hItem1 = treeCtrl.GetParentItem(hItem);
		treeCtrl.DeleteItem(hItem1);
	}
	else
		treeCtrl.DeleteItem(hItem);

	DBEntity entity(m_DBname);
	entity.DropDB(m_DBname);
}
/***********************************************************************************/
// 新建表
void CDBView::AddTable()
{
	treeCtrl = &GetTreeCtrl();
	//获取新建表的名字
	
	HTREEITEM hItem1;
	HTREEITEM hNode;
	HTREEITEM hItem;
	DB_TBNameDlg dlg;

	hItem = treeCtrl->GetSelectedItem();
	CString m_DBname = treeCtrl->GetItemText(hItem);

	dlg.DoModal();
	m_DaTaName = dlg.GetDBTBName();

	TableEntity TBentity(m_DaTaName,m_DBname);
	TBentity.CreateTable();

	if (!m_DaTaName.IsEmpty()){
		hItem = treeCtrl->GetSelectedItem();
		if (treeCtrl->GetParentItem(hItem) != 0)
		{

			hItem1 = treeCtrl->GetParentItem(hItem);
			hNode = treeCtrl->InsertItem(m_DaTaName, 1, 1, hItem1);
			treeCtrl->Expand(hItem1, TVE_EXPAND);
		}
		else
		{
			hNode = treeCtrl->InsertItem(m_DaTaName, 1, 1, hItem);
			treeCtrl->Expand(hItem, TVE_EXPAND);

		}
	}
	

}
// 显示表
void CDBView::ShowAllTable()
{
	CString m_SelectDBName,m_SelectTBName;
	HTREEITEM hItem,hItem1;

	// 获得当前选中的表的名字
	hItem = treeCtrl->GetSelectedItem();
	m_SelectTBName = treeCtrl->GetItemText(hItem);
	// 获得当前选中的库的名字
	hItem1 = treeCtrl->GetParentItem(hItem);
	m_SelectDBName = treeCtrl->GetItemText(hItem1);

	/************从文件中取数据**********/
	CString tbName = STBName,dbName = SDBName;
	TableEntity entity;
	std::vector<Field> v;
	entity.getAttributes(dbName,tbName,v);
	int n = v.size();
	/***********************************/
	// 清空表
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	pMainWnd->m_pTableView->ClearTable();
	// 显示表里面所有记录
	pMainWnd->m_pTableView->DisplayRecords(1); // DisplayRecords方法参数不全

}
// 查  询
void CDBView::SelectTable()
{
	QueryDlg dlg;
	dlg.DoModal();
}

// 清空表
void CDBView::EmptyTable()
{
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	pMainWnd->m_pTableView->ClearTable();
	HTREEITEM hItem,hParent;
	hItem = treeCtrl->GetSelectedItem();
	hParent = treeCtrl->GetParentItem(hItem);
	CString DBname,tableName;
	DBname = treeCtrl->GetItemText(hParent);
	tableName = treeCtrl->GetItemText(hItem);
	TableEntity entity;
	entity.clearTable(DBname,tableName);
}
// 重命名
void CDBView::RnameTable()
{
	DB_TBRenameDlg dlg;
	CString m_newName; // 新名字
	HTREEITEM hItem;

	hItem = treeCtrl->GetSelectedItem();
	if (treeCtrl->GetParentItem(hItem) != 0)
	{
		dlg.DoModal();
		m_newName = dlg.GetNewName();
		treeCtrl->SetItemText(hItem, m_newName); // 在视图上更改名字
		TableEntity e;
		e.renameTable(STBName,m_newName);
	}
	else
		MessageBox(_T("请对表进行重命名操作！"));
}
// 删除表
void CDBView::DeleteTable()
{
	CTreeCtrl &treeCtrl = GetTreeCtrl();
	
	HTREEITEM hItem = treeCtrl.GetSelectedItem();

	CString tableName = treeCtrl.GetItemText(hItem);
	HTREEITEM hParent = treeCtrl.GetParentItem(hItem);
	CString DBname = treeCtrl.GetItemText(hParent);
	if (treeCtrl.GetParentItem(hItem) != 0)
		treeCtrl.DeleteItem(hItem);

	TableEntity entity;
	entity.DropTable(DBname,tableName);
}


void CDBView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	HTREEITEM hItem = treeCtrl->GetSelectedItem();
	STBName = treeCtrl->GetItemText(hItem);
	HTREEITEM hParent = treeCtrl->GetParentItem(hItem);
	SDBName = treeCtrl->GetItemText(hParent);
	/*if(STBName == SDBName)
	{
		STBName = _T("");
	}*/
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	pMainWnd->m_pTableView->DisplayField();
}
