#pragma once
#include"Struct.h"
#include <vector>
#include <map>


// CTableView 视图

class CTableView : public CListView
{
	DECLARE_DYNCREATE(CTableView)

public:
	CTableView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTableView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	CString* field; // 字段名字
	int m_fieldNumber; // 字段个数
	Field oldField;
	bool judgeInterface; //  判断是字段界面true还是记录界面false
public:
	CListCtrl *listCtrl;
	void OnInitialUpdate();
	afx_msg void OnFieldAdd();
	afx_msg void OnFieldUpdate();
	afx_msg void OnFieldDelete();
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordDelete();
	afx_msg void OnRecordUpdate();
	afx_msg void OnRecordRollback();
	void SetFiledNumber(int totalNumber);
	int getFiledNumber();
	void DisplayField();
	void ClearTable();
	void DisplayRecords(int sum); // 显示所有记录，第一个参数是字段的总个数
								  // 第二个参数是字段名称的数组或其他类型也可（未定）
								  // 第三个参数是所有记录的信息（未定）
	void DisplayFindRecords(std::vector<std::map<CString, CString>> &vct);
	void DisplaySelectRecords(int sum);
};


