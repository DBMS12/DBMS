// DBView.cpp : ʵ���ļ�
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
/* CDBView ����������ͼ����ʾ����
 * �漰�½��⡢�½���ȷ���
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


// CDBView ���

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


// CDBView ��Ϣ�������
// ��ʼ��

void CDBView::OnInitialUpdate()
{
	
	CTreeView::OnInitialUpdate();

	treeCtrl = &GetTreeCtrl();
	
	DWORD dwStyles = GetWindowLong(treeCtrl->m_hWnd, GWL_STYLE);
	dwStyles |= TVS_EDITLABELS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	SetWindowLong(treeCtrl->m_hWnd, GWL_STYLE, dwStyles);
	// ����ͼ��
	m_treeImageList.Create(16, 16, ILC_MASK, 4, 1);
	m_treeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_DATA));
	m_treeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_TABLE));

	treeCtrl->SetImageList(&m_treeImageList, TVSIL_NORMAL);	

	//��ʼ����
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
// �½���
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
// �򿪿�
void CDBView::OpenData()
{
	/*
	 *��ʼ������ͼֻ�г�������֣������г��������
	 *�û�ѡ��򿪿��ʱ�򣬼���ѡ�п�����б���ʾ����
	 */

	HTREEITEM hItem;
	CString m_SelectDBName;// ��õ�ǰѡ�еĿ������
	
	hItem = treeCtrl->GetSelectedItem();
	m_SelectDBName = treeCtrl->GetItemText(hItem);

	treeCtrl->Expand(hItem, TVE_EXPAND);// չ��
}
// ���ݿ�
void CDBView::BackupData()
{
	CTreeCtrl &treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetSelectedItem();
	CString m_DBname = treeCtrl.GetItemText(hItem);
	DBEntity entity(m_DBname);
	entity.BackupsDB(m_DBname);
	MessageBox(_T("���ݳɹ���"));
}
// ������
void CDBView::RnameData()
{
	DB_TBRenameDlg dlg;
	CString m_newName; // ������
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
		treeCtrl->SetItemText(hItem, m_newName); // ����ͼ�ϸ�������
	}
	else
		MessageBox(_T("��Կ����������������"));
}
// ɾ����
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
// �½���
void CDBView::AddTable()
{
	treeCtrl = &GetTreeCtrl();
	//��ȡ�½��������
	
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
// ��ʾ��
void CDBView::ShowAllTable()
{
	CString m_SelectDBName,m_SelectTBName;
	HTREEITEM hItem,hItem1;

	// ��õ�ǰѡ�еı������
	hItem = treeCtrl->GetSelectedItem();
	m_SelectTBName = treeCtrl->GetItemText(hItem);
	// ��õ�ǰѡ�еĿ������
	hItem1 = treeCtrl->GetParentItem(hItem);
	m_SelectDBName = treeCtrl->GetItemText(hItem1);

	/************���ļ���ȡ����**********/
	CString tbName = STBName,dbName = SDBName;
	TableEntity entity;
	std::vector<Field> v;
	entity.getAttributes(dbName,tbName,v);
	int n = v.size();
	/***********************************/
	// ��ձ�
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	pMainWnd->m_pTableView->ClearTable();
	// ��ʾ���������м�¼
	pMainWnd->m_pTableView->DisplayRecords(1); // DisplayRecords����������ȫ

}
// ��  ѯ
void CDBView::SelectTable()
{
	QueryDlg dlg;
	dlg.DoModal();
}

// ��ձ�
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
// ������
void CDBView::RnameTable()
{
	DB_TBRenameDlg dlg;
	CString m_newName; // ������
	HTREEITEM hItem;

	hItem = treeCtrl->GetSelectedItem();
	if (treeCtrl->GetParentItem(hItem) != 0)
	{
		dlg.DoModal();
		m_newName = dlg.GetNewName();
		treeCtrl->SetItemText(hItem, m_newName); // ����ͼ�ϸ�������
		TableEntity e;
		e.renameTable(STBName,m_newName);
	}
	else
		MessageBox(_T("��Ա����������������"));
}
// ɾ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
