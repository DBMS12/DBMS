#pragma once
#include"Struct.h"
#include <vector>
#include <map>


// CTableView ��ͼ

class CTableView : public CListView
{
	DECLARE_DYNCREATE(CTableView)

public:
	CTableView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	CString* field; // �ֶ�����
	int m_fieldNumber; // �ֶθ���
	Field oldField;
	bool judgeInterface; //  �ж����ֶν���true���Ǽ�¼����false
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
	void DisplayRecords(int sum); // ��ʾ���м�¼����һ���������ֶε��ܸ���
								  // �ڶ����������ֶ����Ƶ��������������Ҳ�ɣ�δ����
								  // ���������������м�¼����Ϣ��δ����
	void DisplayFindRecords(std::vector<std::map<CString, CString>> &vct);
	void DisplaySelectRecords(int sum);
};


