// Tree.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "Tree.h"
#include "afxdialogex.h"


// Tree �Ի���

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

// CDBView ���

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

// Tree ��Ϣ�������


void Tree::OnInitialUpdate()
{
	//CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CTreeView::OnInitialUpdate();
	m_tc = &this->GetTreeCtrl();

	HICON hIcon[3];      // ͼ��������   
	// ��������ͼ�꣬�������ǵľ�����浽����   
	hIcon[0] = theApp.LoadIcon(IDI_DB_ICON);
	hIcon[1] = theApp.LoadIcon(IDI_TABLE_ICON);
	hIcon[2] = theApp.LoadIcon(IDI_DOC_ICON);

	// ����ͼ������CImageList����   
	m_imageList.Create(16, 16, ILC_COLOR32, 3, 3);
	// ������ͼ����ӵ�ͼ������   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// Ϊ���οؼ�����ͼ������   
	m_tc->SetImageList(&m_imageList, TVSIL_NORMAL);

	//��ʼ��ΪNULL
	m_hCurrDBItem = NULL;
	m_hCurrTBItem = NULL;

	//��ʾ���е����ݿ��б�
	this->DisplayDBList();

}


void Tree::DisplayDBList()
{
	//��ʾ���ݿ��б�

	//ɾ����״ͼ�е����ݿ���ʾ
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
	//����ָ��ڵ�ľ��
	HTREEITEM hItem;

	//treeImage();

	//����ڵ�
	//�ڸ���������
	hItem = m_tc->InsertItem(L"dbname", 0, 0, TVI_ROOT);
	m_tc->SetItemData(hItem, 1);  //ͼ��
	//m_tc.UpdateData();
	//RedrawWindow();
	//UpdateWindow();
	//UpdateData(false);
}

void Tree::createT2(HTREEITEM hItem, CString tbname)
{
	//HTREEITEM hItem ���ڵ�
	HTREEITEM hSubItem;

	// ���һ���ӽ��
	hSubItem = m_tc->InsertItem(tbname, hItem);
	m_tc->SetItemImage(hSubItem, 1, 1);//��ɱ�ͼ��
}

void Tree::createT3(HTREEITEM hSubItem, CString fieldname)
{
	HTREEITEM hSubThreeItem;

	hSubThreeItem = m_tc->InsertItem(fieldname, hSubItem);//������--�ֶ�
	m_tc->SetItemImage(hSubThreeItem, 2, 2);//���DOCͼ��
}

CString Tree::GetSelectedDBName()
{
	if (m_hCurrDBItem)
	{
		return GetTreeCtrl().GetItemText(m_hCurrDBItem);
	}
	else
	{
		//�����ǰû��ѡ��database���򷵻ص�һ�����ݿ���
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