// SQLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "SQLDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"

#include "DBEntity.h"
#include "TableEntity.h"

// SQLDlg �Ի���

IMPLEMENT_DYNAMIC(SQLDlg, CDialog)

SQLDlg::SQLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SQLDlg::IDD, pParent)
{

}

SQLDlg::~SQLDlg()
{
}

void SQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eSql);
	DDX_Control(pDX, IDC_EDIT2, m_dbname);
}


BEGIN_MESSAGE_MAP(SQLDlg, CDialog)
	ON_BN_CLICKED(IDOK, &SQLDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SQLDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// SQLDlg ��Ϣ�������


void SQLDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_dbname.GetWindowTextW(m_db);
	m_eSql.GetWindowTextW(m_sql);
	Analysis(m_db,m_sql);
	// ��ȡm_pTableView���󣬺����pMainWnd->m_pTableView->
	// ��ȡm_pDBView���󣬺����pMainWnd->m_pDBView->


	CDialog::OnOK();
}
void SQLDlg::Analysis(CString db,CString sql){
	CString output;
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	 CTreeCtrl *tree=&pMainWnd->m_pDBView->GetTreeCtrl();
	
	AfxExtractSubString(output,sql,0,' ');


	if(output=="create"){//������߽���
		 AfxExtractSubString(output,sql,1,' ');
		 
		 if(output=="database"){
	       
	       AfxExtractSubString(output,sql,2,' ');
            if (!output.IsEmpty())
	        {
		    HTREEITEM hRoot = tree->InsertItem(output, 0, 0, TVI_ROOT, TVI_LAST);
		    tree->Expand(hRoot, TVE_EXPAND);
	        }

	        DBEntity entity(output);
	        entity.CreateDB();
		  }else if(output=="table"){
			HTREEITEM hItem1;
	       HTREEITEM hNode;
	       HTREEITEM hItem;
	           
		    AfxExtractSubString(output,sql,2,' ');
		    
	      
	           if (!output.IsEmpty()){
		       hItem = tree->GetSelectedItem();
		       if (tree->GetParentItem(hItem) != 0)
		      {

			    hItem1 = tree->GetParentItem(hItem);
			    hNode = tree->InsertItem(output, 1, 1, hItem1);
			    tree->Expand(hItem1, TVE_EXPAND);
		       }
		      else
		       {
			      hNode = tree->InsertItem(output, 1, 1, hItem);
			      tree->Expand(hItem, TVE_EXPAND);
		       }
	        }
		
	           TableEntity TBentity(output,db);
	           TBentity .CreateTable();	
		   }
		  
}else if(output=="drop"){  //ɾ��
	     AfxExtractSubString(output,sql,1,' ');
		
		 if(output=="database"){
	       
	       AfxExtractSubString(output,sql,2,' ');  
		   HTREEITEM hItem1;
	       HTREEITEM hItem = tree->GetSelectedItem();

	       if (tree->GetParentItem(hItem) != 0)
	     {
		 hItem1 = tree->GetParentItem(hItem);
		 tree->DeleteItem(hItem1);
	      }
	      else
		 tree->DeleteItem(hItem);

	     DBEntity entity(output);
	     entity.DropDB(output);
		 }else if(output=="table"){
		 AfxExtractSubString(output,sql,2,' ');
		
	
	     HTREEITEM hItem = tree->GetSelectedItem();

	      CString tableName = tree->GetItemText(hItem);
	     HTREEITEM hParent = tree->GetParentItem(hItem);
	   CString DBname = tree->GetItemText(hParent);
	   if (tree->GetParentItem(hItem) != 0)
		  tree->DeleteItem(hItem);

	   TableEntity entity;
	  entity.DropTable(DBname,tableName);
		 
		 }
	}
	
else if (output=="select"){
	AfxExtractSubString(output,sql,1,' ');
	if(output=="*"){
	CString m_SelectDBName,m_SelectTBName;
	HTREEITEM hItem,hItem1;

	// ��õ�ǰѡ�еı������
	hItem = tree->GetSelectedItem();
	m_SelectTBName = tree->GetItemText(hItem);
	// ��õ�ǰѡ�еĿ������
	hItem1 = tree->GetParentItem(hItem);
	m_SelectDBName = tree->GetItemText(hItem1);

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
	
	pMainWnd->m_pTableView->DisplayRecords(1); // DisplayRecords����������ȫ
	
	
	}else{
	CString m_SelectDBName,m_SelectTBName;
	HTREEITEM hItem,hItem1;

	// ��õ�ǰѡ�еı������
	hItem = tree->GetSelectedItem();
	m_SelectTBName = tree->GetItemText(hItem);
	// ��õ�ǰѡ�еĿ������
	hItem1 = tree->GetParentItem(hItem);
	m_SelectDBName = tree->GetItemText(hItem1);

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
	
	pMainWnd->m_pTableView->DisplaySelectRecords(1); // DisplayRecords����������ȫ
	
	
	}

}
	}
	

void SQLDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
