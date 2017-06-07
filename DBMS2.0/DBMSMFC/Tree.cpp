// Tree.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "Tree.h"
#include "afxdialogex.h"


// Tree 对话框

IMPLEMENT_DYNAMIC(Tree, CTreeView)

//Tree::Tree(CWnd* pParent /*=NULL*/)
//	: CTreeView(Tree::IDD, pParent)
//{
//
//}

Tree::Tree()
{
}

Tree::~Tree()
{
}

//void Tree::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_TREE1, m_tc);
//}

BEGIN_MESSAGE_MAP(Tree, CTreeView)
END_MESSAGE_MAP()

// CDBView 诊断

#ifdef _DEBUG
void Tree::AssertValid() const
{
	CTreeView::AssertValid();
	CString ss;
}

#ifndef _WIN32_WCE
void Tree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG

// Tree 消息处理程序


void Tree::OnInitialUpdate()
{
	//CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CTreeView::OnInitialUpdate();
	m_tc = &this->GetTreeCtrl();

	HICON hIcon[3];      // 图标句柄数组   
	// 加载三个图标，并将它们的句柄保存到数组   
	hIcon[0] = theApp.LoadIcon(IDI_DB_ICON);
	hIcon[1] = theApp.LoadIcon(IDI_TABLE_ICON);
	hIcon[2] = theApp.LoadIcon(IDI_DOC_ICON);

	// 创建图像序列CImageList对象   
	m_imageList.Create(16, 16, ILC_COLOR32, 3, 3);
	// 将三个图标添加到图像序列   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// 为树形控件设置图像序列   
	m_tc->SetImageList(&m_imageList, TVSIL_NORMAL);

	//初始化为NULL
	m_hCurrDBItem = NULL;
	m_hCurrTBItem = NULL;

	//显示已有的数据库列表
	this->DisplayDBList();

}


void Tree::DisplayDBList()
{
	//显示数据库列表

	//删除树状图中的数据库显示
	HTREEITEM hNextItem;
	HTREEITEM hPreItem = m_tc->GetRootItem();
	while (hPreItem != NULL)
	{
		hNextItem = m_tc->GetNextItem(hPreItem, TVGN_NEXT);
		m_tc->DeleteItem(hPreItem);
		hPreItem = hNextItem;
	}

	//for (vector<CDBEntity>::iterator ite = dbList.begin(); ite != dbList.end(); ++ite)
	//{
	//	HTREEITEM hRoot = m_tc->InsertItem(ite->GetName(), 0, 0, TVI_ROOT, TVI_LAST);
	//	m_tc->SetItemData(hRoot, 0);
	//}
}

void Tree::createT1(CString dbname)
{
	//声明指向节点的句柄
	HTREEITEM hItem;

	//treeImage();

	//插入节点
	//在根结点上添加
	hItem = m_tc->InsertItem(L"dbname", 0, 0, TVI_ROOT);
	m_tc->SetItemData(hItem, 1);  //图标
	//m_tc.UpdateData();
	//RedrawWindow();
	//UpdateWindow();
	//UpdateData(false);
}

void Tree::createT2(HTREEITEM hItem, CString tbname)
{
	//HTREEITEM hItem 父节点
	HTREEITEM hSubItem;

	// 添加一个子结点
	hSubItem = m_tc->InsertItem(tbname, hItem);
	m_tc->SetItemImage(hSubItem, 1, 1);//变成表图标
}

void Tree::createT3(HTREEITEM hSubItem, CString fieldname)
{
	HTREEITEM hSubThreeItem;

	hSubThreeItem = m_tc->InsertItem(fieldname, hSubItem);//第三级--字段
	m_tc->SetItemImage(hSubThreeItem, 2, 2);//变成DOC图标
}

CString Tree::GetSelectedDBName()
{
	if (m_hCurrDBItem)
	{
		return GetTreeCtrl().GetItemText(m_hCurrDBItem);
	}
	else
	{
		//如果当前没有选择database，则返回第一个数据库名
		return GetTreeCtrl().GetItemText(m_tc->GetRootItem());;
	}

}

CString Tree::GetSelectedTBName()
{
	if (this->m_hCurrTBItem)
		return m_tc->GetItemText(m_hCurrTBItem);
	else
		return NULL;
}