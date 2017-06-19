// TableView.cpp : 实现文件
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
/* CTableView 针对右侧视图的显示操作
 * 涉及新建字段、添加记录等方法
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


// CTableView 诊断

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


// CTableView 消息处理程序
void CTableView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	listCtrl = &GetListCtrl();

	LONG lStyle;
	lStyle = GetWindowLong(listCtrl->m_hWnd, GWL_STYLE);   // 获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK;                              // 清除显示方式位
	lStyle |= LVS_REPORT;
	SetWindowLong(listCtrl->m_hWnd, GWL_STYLE, lStyle);

	DWORD dwStyle = listCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // 选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;                          // 网格线
	listCtrl->SetExtendedStyle(dwStyle);                   // 设置扩展风格

	judgeInterface = false;
}
// 显示字段
void CTableView::DisplayField()
{
	this->ClearTable();
	// 初始界面查看表结构的表格头
	listCtrl->InsertColumn(0, _T("字段名称"), LVCFMT_LEFT, 100);
	listCtrl->InsertColumn(1, _T("字段类型"), LVCFMT_LEFT, 100);
	listCtrl->InsertColumn(2, _T("长度"), LVCFMT_LEFT, 50);
	listCtrl->InsertColumn(3, _T("是否主键"), LVCFMT_LEFT, 90);
	listCtrl->InsertColumn(4, _T("允许空值"), LVCFMT_LEFT, 90);
	listCtrl->InsertColumn(5, _T("默认值"), LVCFMT_LEFT, 80);
	listCtrl->InsertColumn(6, _T("最小值"), LVCFMT_LEFT, 80);
	listCtrl->InsertColumn(7, _T("最大值"), LVCFMT_LEFT, 80);
	listCtrl->InsertColumn(8, _T("备注"), LVCFMT_LEFT, 100);
	/*************************从文件件中获取各条记录然后输出****************************/
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
// 添加字段
void CTableView::OnFieldAdd()
{
	// 打开添加字段的对话框
	isUpdate = false;
	CFieldDlg dlg;
	dlg.title = "添加字段";
	dlg.DoModal();


	DisplayField();
	
}

// 更新字段
void CTableView::OnFieldUpdate()
{
	// TODO:  在此添加命令处理程序代码
	if (judgeInterface == false)
	{
		MessageBox(_T("请在正确的界面进行修改！"));
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

		dlg.title = "修改字段";
		dlg.DoModal();
		

		// 获取对话框用户输入的新建字段的数值显示在表格里格式(测试用，只能写一条)
		DisplayField();
		
	}
}
// 删除字段
void CTableView::OnFieldDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (judgeInterface == false)
	{
		MessageBox(_T("请在正确的界面进行删除！"));
	}
	else{
		// 获得选中的行
		int nItem = listCtrl->GetNextItem(-1, LVNI_SELECTED);
		CString fname = listCtrl->GetItemText(nItem, 0);
		// 删除选中行
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
// 添加记录
void CTableView::OnRecordAdd()
{
	// TODO:  在此添加命令处理程序代码
	lastAct = 1;

	RecordDlg dlg;
	dlg.title = "添加记录";

	// 从表文件中获得该表的字段个数,8是测试用
	std::vector<Field> v;
	TableEntity te;
	te.getAttributes(SDBName,STBName,v);

	dlg.totalNumber = v.size();
	dlg.DoModal();
	// 获取对话框用户输入的新建字段的数值显示在表格里格式(测试用，只能写一条)
	//DisplayRecords(8);
	int nItemCount = listCtrl->GetItemCount();

	listCtrl->InsertItem(nItemCount, _T(""));
	for (int i = 0; i < dlg.totalNumber; i++)
	{
		listCtrl->SetItemText(nItemCount, i, dlg.newRecord[i]);
	}
	// 把获取的数值，写到文件里然后displayRecord

	RecordEntity re;
	re.writeRecord(SDBName,STBName,record);
	DisplayRecords(dlg.totalNumber);
}

// 修改记录
void CTableView::OnRecordUpdate()
{
	// TODO:  在此添加命令处理程序代码
	if (judgeInterface == true)
	{
		MessageBox(_T("请在正确的界面进行修改！"));
	}
	else{
		lastAct = 3;
		RecordDlg dlg;
		dlg.title = "修改记录";
		// 从表文件中获得该表的字段个数,8是测试用
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

		//// 获取对话框用户输入的新建字段的数值显示在表格里格式(测试用，只能写一条)
		RecordEntity re;
		re.updateRecord(SDBName,STBName,record,OLDRecord);

		DisplayRecords(dlg.totalNumber);
		// 把获取的数值，写到文件里然后displayRecord
		//DisplayRecords(dlg.totalNumber);
	}
}
// 回退记录
void CTableView::OnRecordRollback()
{
	// TODO:  在此添加命令处理程序代码
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
// 删除记录
void CTableView::OnRecordDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (judgeInterface == true)
	{
		MessageBox(_T("请在正确的界面进行删除！"));
	}
	else{
		lastAct = 2;

		// 获得选中的行
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
		// 删除选中行
		listCtrl->DeleteItem(nItem);
	}
}


void CTableView::ClearTable()
{
	//清空表数据及表头

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
	// 初始界面显示记录结构的表格头
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
	// 初始界面显示记录结构的表格头
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
	// 初始界面显示记录结构的表格头
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