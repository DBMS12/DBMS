#include "stdafx.h"
#include "Global.h"


Global::Global()
{
	DATABASENAME = "";     //初始化
	TABLENAME = "";
}


Global::~Global()
{
}
Global global = Global();  //将此类变为全局类