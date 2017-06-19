// TableView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "TableView.h"
#include "FieldDlg.h"
#include "Transfer.h"
#include "RecordDlg.h"
#include "TableEntity.h"
#include "RecordEntity.h"
#include "Struct.h"
#include <vector>
#include <map>

extern bool isUpdate;
extern CString SDBName;
extern CString STBName;
extern std::map<CString, CString> record;
extern std::map<CString, CString> OLDRecord;
extern int lastAct; //1 add,2 del,3update;

// CTableView
/* CTableView ����Ҳ���ͼ����ʾ����
 * �漰�½��ֶΡ���Ӽ�¼�ȷ���
 */
IMPLEMENT_DYNCREATE(CTableView, CListView)

CTableView::CTableView()
{

}

CTableView::~CTableView()
{
}

BEGIN_MESSAGE_MAP(CTableView, CListView)
	ON_COMMAND(ID_FIELD_ADD, &CTableView::OnFieldAdd)
	ON_COMMAND(ID_FIELD_UPDATE, &CTableView::OnFieldUpdate)
	ON_COMMAND(ID_FIELD_DELETE, &CTableView::OnFieldDelete)
	ON_COMMAND(ID_RECORD_ADD, &CTableView::OnRecordAdd)
	ON_COMMAND(ID_RECORD_DELETE, &CTableView::OnRecordDelete)
	ON_COMMAND(ID_RECORD_UPDATE, &CTableView::OnRecordUpdate)
	ON_COMMAND(ID_RECORD_ROLLBACK, &CTableView::OnRecordRollback)
END_MESSAGE_MAP()


// CTableView ���

#ifdef _DEBUG
void CTableView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CTableView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTableView ��Ϣ�������
void CTableView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	listCtrl = &GetListCtrl();

	LONG lStyle;
	lStyle = GetWindowLong(listCtrl->m_hWnd, GWL_STYLE);   // ��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK;                              // �����ʾ��ʽλ
	lStyle |= LVS_REPORT;
	SetWindowLong(listCtrl->m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = listCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;                          // ������
	listCtrl->SetExtendedStyle(dwStyle);                   // ������չ���

	judgeInterface = false;
}
// ��ʾ�ֶ�
void CTableView::DisplayField()
{
	this->ClearTable();
	// ��ʼ����鿴��ṹ�ı��ͷ
	listCtrl->InsertColumn(0, _T("�ֶ�����"), LVCFMT_LEFT, 100);
	listCtrl->InsertColumn(1, _T("�ֶ�����"), LVCFMT_LEFT, 100);
	listCtrl->InsertColumn(2, _T("����"), LVCFMT_LEFT, 50);
	listCtrl->InsertColumn(3, _T("�Ƿ�����"), LVCFMT_LEFT, 90);
	listCtrl->InsertColumn(4, _T("�����ֵ"), LVCFMT_LEFT, 90);
	listCtrl->InsertColumn(5, _T("Ĭ��ֵ"), LVCFMT_LEFT, 80);
	listCtrl->InsertColumn(6, _T("��Сֵ"), LVCFMT_LEFT, 80);
	listCtrl->InsertColumn(7, _T("���ֵ"), LVCFMT_LEFT, 80);
	listCtrl->InsertColumn(8, _T("��ע"), LVCFMT_LEFT, 100);
	/*************************���ļ����л�ȡ������¼Ȼ�����****************************/
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);
	for(int nItemCount=0;nItemCount<v.size();nItemCount++)
	{
		listCtrl->InsertItem(nItemCount, _T(""));
		listCtrl->SetItemText(nItemCount, 0, v[nItemCount].m_FieldName);
		listCtrl->SetItemText(nItemCount, 1, v[nItemCount].m_FieldType);
		listCtrl->SetItemText(nItemCount, 2, v[nItemCount].m_Length);
		listCtrl->SetItemText(nItemCount, 3, v[nItemCount].m_Primary);
		listCtrl->SetItemText(nItemCount, 4, v[nItemCount].m_Null);
		listCtrl->SetItemText(nItemCount, 5, v[nItemCount].m_Default);
		listCtrl->SetItemText(nItemCount, 6, v[nItemCount].m_Min);
		listCtrl->SetItemText(nItemCount, 7, v[nItemCount].m_Max);
		listCtrl->SetItemText(nItemCount, 8, v[nItemCount].m_Hint);
	}
	judgeInterface = true;
}
// ����ֶ�
void CTableView::OnFieldAdd()
{
	// ������ֶεĶԻ���
	isUpdate = false;
	CFieldDlg dlg;
	dlg.title = "����ֶ�";
	dlg.DoModal();


	DisplayField();
	
}

// �����ֶ�
void CTableView::OnFieldUpdate()
{
	// TODO:  �ڴ���������������
	if (judgeInterface == false)
	{
		MessageBox(_T("������ȷ�Ľ�������޸ģ�"));
	}
	else{
		isUpdate = true;

		CFieldDlg dlg;
		POSITION ps;
		int nIndex;

		ps = listCtrl->GetFirstSelectedItemPosition();
		nIndex = listCtrl->GetNextSelectedItem(ps);
		dlg.oldField[0] = listCtrl->GetItemText(nIndex, 0);
		dlg.oldField[1] = listCtrl->GetItemText(nIndex, 1);
		dlg.oldField[2] = listCtrl->GetItemText(nIndex, 2);
		dlg.oldField[4] = listCtrl->GetItemText(nIndex, 3);
		dlg.oldField[5] = listCtrl->GetItemText(nIndex, 4);
		dlg.oldField[8] = listCtrl->GetItemText(nIndex, 5);
		dlg.oldField[6] = listCtrl->GetItemText(nIndex, 6);
		dlg.oldField[7] = listCtrl->GetItemText(nIndex, 7);
		dlg.oldField[3] = listCtrl->GetItemText(nIndex, 8);

		dlg.title = "�޸��ֶ�";
		dlg.DoModal();
		

		// ��ȡ�Ի����û�������½��ֶε���ֵ��ʾ�ڱ�����ʽ(�����ã�ֻ��дһ��)
		DisplayField();
		
	}
}
// ɾ���ֶ�
void CTableView::OnFieldDelete()
{
	// TODO:  �ڴ���������������
	if (judgeInterface == false)
	{
		MessageBox(_T("������ȷ�Ľ������ɾ����"));
	}
	else{
		// ���ѡ�е���
		int nItem = listCtrl->GetNextItem(-1, LVNI_SELECTED);
		CString fname = listCtrl->GetItemText(nItem, 0);
		// ɾ��ѡ����
		listCtrl->DeleteItem(nItem);
		CString tbName = STBName,dbName = SDBName;
		TableEntity entity;
		entity.dropAttribute(dbName,tbName,fname);

	}
}
void CTableView::SetFiledNumber(int totalNumber)
{
	m_fieldNumber = totalNumber;
}
int CTableView::getFiledNumber()
{
	return m_fieldNumber;
}
/*********************************************************************************/
// ��Ӽ�¼
void CTableView::OnRecordAdd()
{
	// TODO:  �ڴ���������������
	lastAct = 1;

	RecordDlg dlg;
	dlg.title = "��Ӽ�¼";

	// �ӱ��ļ��л�øñ���ֶθ���,8�ǲ�����
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	dlg.totalNumber = v.size();
	dlg.DoModal();
	// ��ȡ�Ի����û�������½��ֶε���ֵ��ʾ�ڱ�����ʽ(�����ã�ֻ��дһ��)
	//DisplayRecords(8);
	int nItemCount = listCtrl->GetItemCount();

	listCtrl->InsertItem(nItemCount, _T(""));
	for (int i = 0; i < dlg.totalNumber; i++)
	{
		listCtrl->SetItemText(nItemCount, i, dlg.newRecord[i]);
	}
	// �ѻ�ȡ����ֵ��д���ļ���Ȼ��displayRecord

	RecordEntity re;
	re.writeRecord(SDBName,STBName,record);
	DisplayRecords(dlg.totalNumber);
}

// �޸ļ�¼
void CTableView::OnRecordUpdate()
{
	// TODO:  �ڴ���������������
	if (judgeInterface == true)
	{
		MessageBox(_T("������ȷ�Ľ�������޸ģ�"));
	}
	else{
		lastAct = 3;
		RecordDlg dlg;
		dlg.title = "�޸ļ�¼";
		// �ӱ��ļ��л�øñ���ֶθ���,8�ǲ�����
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(SDBName,STBName,v);

		dlg.totalNumber = v.size();
		POSITION ps;
		int nIndex;

		ps = listCtrl->GetFirstSelectedItemPosition();
		nIndex = listCtrl->GetNextSelectedItem(ps);

		OLDRecord.clear();
		for (int i = 0; i < dlg.totalNumber; i++)
		{
			dlg.oldRecord[i] = listCtrl->GetItemText(nIndex, i);
			OLDRecord.insert(std::make_pair(v[i].m_FieldName,dlg.oldRecord[i]));
		}
		dlg.DoModal();

		//if (dlg.judge)
			//OnRecordDelete();

		//// ��ȡ�Ի����û�������½��ֶε���ֵ��ʾ�ڱ�����ʽ(�����ã�ֻ��дһ��)
		RecordEntity re;
		re.updateRecord(SDBName,STBName,record,OLDRecord);

		DisplayRecords(dlg.totalNumber);
		// �ѻ�ȡ����ֵ��д���ļ���Ȼ��displayRecord
		//DisplayRecords(dlg.totalNumber);
	}
}
// ���˼�¼
void CTableView::OnRecordRollback()
{
	// TODO:  �ڴ���������������
	RecordEntity re;
	switch(lastAct)
	{
		case 1:
			re.deleteRecord(SDBName,STBName,record);
			break;
		case 2:
			re.writeRecord(SDBName,STBName,record);
			break;
		case 3:
			re.updateRecord(SDBName,STBName,OLDRecord,record);
			break;
	}
	lastAct = 0;
	DisplayRecords(0);
}
// ɾ����¼
void CTableView::OnRecordDelete()
{
	// TODO:  �ڴ���������������
	if (judgeInterface == true)
	{
		MessageBox(_T("������ȷ�Ľ������ɾ����"));
	}
	else{
		lastAct = 2;

		// ���ѡ�е���
		int nItem = listCtrl->GetNextItem(-1, LVNI_SELECTED);

		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(SDBName,STBName,v);

		std::map<CString,CString> Map;
		for(int i=0;i<v.size();i++)
		{
			CString str = listCtrl->GetItemText(nItem, i);
			Map.insert(std::make_pair(v[i].m_FieldName,str));
		}
		RecordEntity re;
		re.deleteRecord(SDBName,STBName,Map);
		record = Map;
		// ɾ��ѡ����
		listCtrl->DeleteItem(nItem);
	}
}


void CTableView::ClearTable()
{
	//��ձ����ݼ���ͷ

	listCtrl->DeleteAllItems();

	while (listCtrl->GetHeaderCtrl()->GetItemCount())
	{
		listCtrl->DeleteColumn(0);
	}

}
void CTableView::DisplayRecords(int sum)
{
	this->ClearTable();
	int number1 = 0, number2 = 0;
	// ��ʼ������ʾ��¼�ṹ�ı��ͷ
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	sum = v.size();

	for(int i=0;i<sum;i++)
	{
		listCtrl->InsertColumn(i, v[i].m_FieldName, LVCFMT_LEFT, 100);
	}

	std::vector<std::map<CString, CString>> vct;
	RecordEntity re;
	re.readRecord(SDBName,STBName,vct,sum);

	for(int i=0;i<sum;i++)
	{
		std::map<CString, CString> tmp = vct[i];
		listCtrl->InsertItem(i , tmp[v[0].m_FieldName]);
		for(int j=1;j<v.size();j++)
		{
			listCtrl->SetItemText(i, j, tmp[v[j].m_FieldName]);
		}
	}
	
	
	judgeInterface = false;
}

void CTableView::DisplaySelectRecords(int sum)
{
	this->ClearTable();
	int number1 = 0, number2 = 0;
	// ��ʼ������ʾ��¼�ṹ�ı��ͷ
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	sum = 2;

	for(int i=0;i<sum;i++)
	{
		listCtrl->InsertColumn(i, v[i].m_FieldName, LVCFMT_LEFT, 100);
	}

	std::vector<std::map<CString, CString>> vct;
	RecordEntity re;
	re.readRecord(SDBName,STBName,vct,sum);

	for(int i=0;i<sum;i++)
	{
		std::map<CString, CString> tmp = vct[i];
		listCtrl->InsertItem(i , tmp[v[0].m_FieldName]);
		for(int j=1;j<v.size();j++)
		{
			listCtrl->SetItemText(i, j, tmp[v[j].m_FieldName]);
		}
	}
	
	
	judgeInterface = false;
}
void CTableView::DisplayFindRecords(std::vector<std::map<CString, CString>> &vct)
{
	this->ClearTable();
	int number1 = 0, number2 = 0;
	// ��ʼ������ʾ��¼�ṹ�ı��ͷ
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	int sum = v.size();

	for(int i=0;i<sum;i++)
	{
		listCtrl->InsertColumn(i, v[i].m_FieldName, LVCFMT_LEFT, 100);
	}

	for(int i=0;i<vct.size();i++)
	{
		std::map<CString, CString> tmp = vct[i];
		listCtrl->InsertItem(i , tmp[v[0].m_FieldName]);
		for(int j=1;j<v.size();j++)
		{
			listCtrl->SetItemText(i, j, tmp[v[j].m_FieldName]);
		}
	}
}