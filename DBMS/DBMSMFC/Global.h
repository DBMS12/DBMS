#pragma once
class Global
{
public:
	Global();
	~Global();

	CString DATABASENAME;//当前数据库名字
	CString TABLENAME;   //当前表名
};
extern Global global;
