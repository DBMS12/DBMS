#pragma once
class Global
{
public:
	Global();
	~Global();

	CString DATABASENAME;//��ǰ���ݿ�����
	CString TABLENAME;   //��ǰ����
};
extern Global global;
