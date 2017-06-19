#include <afx.h>
#include <atlstr.h>
#include <windows.h>
#include <direct.h>
#include <vector>

extern CString SDBName;
extern CString STBName;

class TableEntity
{
public:
	CString tableName;
	CString belongDB;
	int record_num;
	std::vector<CString> attributes;

	TableEntity(){};
	~TableEntity(){};
	TableEntity(CString name,CString DBname)
	{
		tableName = name;
		belongDB = DBname;
	}
	bool CreateTable()
	{
		CStdioFile file;
		CString path = belongDB + _T("\\") + tableName + _T(".tbs");
		
		if(file.Open(path , CFile::modeReadWrite) == 0)
		{
			file.Open(path, CFile::modeCreate | CFile::modeReadWrite);
			file.WriteString(_T("0\n"));
		}
		file.Close();

		path = belongDB + _T("\\") + tableName + _T(".tbd");
		
		if(file.Open(path , CFile::modeReadWrite) == 0)
		{
			file.Open(path, CFile::modeCreate | CFile::modeReadWrite);
			file.WriteString(_T("0\n"));
		}
		file.Close();

		path = belongDB + _T("\\") + _T("file.txt");
		if(file.Open(path , CFile::modeReadWrite))
		{
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			int n = atoi(num);
			char a[4];
			n++;
			_itoa_s(n, a, 4, 10);
			file.SeekToBegin();
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			file.SeekToEnd();
			file.WriteString(tableName+_T("\n"));
		}
		file.Close();
		return true;
	}

	std::vector<CString> GetAllTBName(CString dbName)
	{
		std::vector<CString> v;
		v.clear();
		CStdioFile file;
		CString path = dbName + _T("\\file.txt");
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return v;
		}
		else
		{
			CString str;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			file.ReadString(str);
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				v.push_back(str);
				file.ReadString(str);
			}
			file.Close();
		}
		return v;
	}

	bool clearTable(CString DBname,CString tableName)
	{
		CStdioFile file;
		CString path = DBname + _T("\\") + tableName + _T(".tbd");
		DeleteFile(path);
		if(file.Open(path , CFile::modeReadWrite) == 0)
		{
			file.Open(path, CFile::modeCreate | CFile::modeReadWrite);
			file.WriteString(_T("0\n"));
		}
		file.Close();
		return true;
	}

	bool DropTable(CString DBname,CString tableName)
	{
		CStdioFile file;
		CString path = DBname + _T("\\") + _T("file.txt");
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			s = new CString[n];
			n--;
			file.ReadString(str);
			file.ReadString(str);
			for (int i = 0; i < n+1; i++)
			{
				s[i] = str;
				file.ReadString(str);
			}
			file.Close();
			file.Open(path, CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			for (int i = 0; i < n+1; i++)
			{
				if (s[i].Compare(tableName) != 0)
				{
					USES_CONVERSION;
					char* z = T2A(s[i]);
					file.Write(z, s[i].GetLength());
					file.Write("\n", strlen("\n"));
				}
			}
		}
		file.Close();
		path = DBname + _T("\\") + tableName + _T(".tbd");
		DeleteFile(path);
		path = DBname + _T("\\") + tableName + _T(".tbs");
		DeleteFile(path);
		return true;
	}
	bool addAttribute(Field &field, CString DBname,CString TBname)
	{
		CStdioFile file;
		CString path = DBname + _T("\\") + TBname + _T(".tbs");
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			s = new CString[n];
			n++;
			file.SeekToBegin();
			char a[4];
			_itoa_s(n, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			file.SeekToEnd();
			USES_CONVERSION;
			char* z = T2A(field.m_FieldName);
			file.Write(z, field.m_FieldName.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_FieldType);
			file.Write(z, field.m_FieldType.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Length);
			file.Write(z, field.m_Length.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Hint);
			file.Write(z, field.m_Hint.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Primary);
			file.Write(z, field.m_Primary.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Null);
			file.Write(z, field.m_Null.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Min);
			file.Write(z, field.m_Min.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Max);
			file.Write(z, field.m_Max.GetLength());
			file.Write("\n", strlen("\n"));

			z = T2A(field.m_Default);
			file.Write(z, field.m_Default.GetLength());
			file.Write("\n", strlen("\n"));
			file.Close();
		}
		return true;
	}

	bool getAttributes(CString DBname,CString TBname,std::vector<Field> &v)
	{
		CStdioFile file;
		v.clear();
		CString path = DBname + _T("\\") + TBname + _T(".tbs");
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			Field tmp;
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				file.ReadString(tmp.m_FieldName);
				file.ReadString(tmp.m_FieldType);
				file.ReadString(tmp.m_Length);
				file.ReadString(tmp.m_Hint);
				file.ReadString(tmp.m_Primary);
				file.ReadString(tmp.m_Null);
				file.ReadString(tmp.m_Min);
				file.ReadString(tmp.m_Max);
				file.ReadString(tmp.m_Default);
				v.push_back(tmp);
			}
			file.Close();
		}
		return true;
	}

	bool updateTable(Field oldField,Field newField,CString DBname,CString TBname)
	{
		CStdioFile file;
		std::vector<Field> v;
		Field field;
		v.clear();
		CString path = DBname + _T("\\") + TBname + _T(".tbs");
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			Field tmp;
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				file.ReadString(tmp.m_FieldName);
				file.ReadString(tmp.m_FieldType);
				file.ReadString(tmp.m_Length);
				file.ReadString(tmp.m_Hint);
				file.ReadString(tmp.m_Primary);
				file.ReadString(tmp.m_Null);
				file.ReadString(tmp.m_Min);
				file.ReadString(tmp.m_Max);
				file.ReadString(tmp.m_Default);
				v.push_back(tmp);
			}
			file.Close();
			file.Open(path, CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			for (int i = 0; i < n; i++)
			{
				if (v[i].m_FieldName.Compare(oldField.m_FieldName) != 0)
				{
					field.m_FieldName = v[i].m_FieldName;
					field.m_FieldType = v[i].m_FieldType;
					field.m_Length = v[i].m_Length;
					field.m_Hint = v[i].m_Hint;
					field.m_Primary = v[i].m_Primary;
					field.m_Null = v[i].m_Null;
					field.m_Min = v[i].m_Min;
					field.m_Max = v[i].m_Max;
					field.m_Default = v[i].m_Default;
				}
				else
				{
					field.m_FieldName = newField.m_FieldName;
					field.m_FieldType = newField.m_FieldType;
					field.m_Length = newField.m_Length;
					field.m_Hint = newField.m_Hint;
					field.m_Primary = newField.m_Primary;
					field.m_Null = newField.m_Null;
					field.m_Min = newField.m_Min;
					field.m_Max = newField.m_Max;
					field.m_Default = newField.m_Default;
				}
				USES_CONVERSION;
				char* z = T2A(field.m_FieldName);
				file.Write(z, field.m_FieldName.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_FieldType);
				file.Write(z, field.m_FieldType.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Length);
				file.Write(z, field.m_Length.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Hint);
				file.Write(z, field.m_Hint.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Primary);
				file.Write(z, field.m_Primary.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Null);
				file.Write(z, field.m_Null.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Min);
				file.Write(z, field.m_Min.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Max);
				file.Write(z, field.m_Max.GetLength());
				file.Write("\n", strlen("\n"));

				z = T2A(field.m_Default);
				file.Write(z, field.m_Default.GetLength());
				file.Write("\n", strlen("\n"));
			}
		}
		file.Close();
		return true;
	}

	bool dropAttribute(CString DBname,CString TBname,CString fieldName)
	{
		CStdioFile file;
		std::vector<Field> v;
		Field field;
		v.clear();
		CString path = DBname + _T("\\") + TBname + _T(".tbs");
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			Field tmp;
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				file.ReadString(tmp.m_FieldName);
				file.ReadString(tmp.m_FieldType);
				file.ReadString(tmp.m_Length);
				file.ReadString(tmp.m_Hint);
				file.ReadString(tmp.m_Primary);
				file.ReadString(tmp.m_Null);
				file.ReadString(tmp.m_Min);
				file.ReadString(tmp.m_Max);
				file.ReadString(tmp.m_Default);
				v.push_back(tmp);
			}
			file.Close();
			file.Open(path, CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n-1, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			for (int i = 0; i < n; i++)
			{
				if (v[i].m_FieldName.Compare(fieldName) != 0)
				{
					field.m_FieldName = v[i].m_FieldName;
					field.m_FieldType = v[i].m_FieldType;
					field.m_Length = v[i].m_Length;
					field.m_Hint = v[i].m_Hint;
					field.m_Primary = v[i].m_Primary;
					field.m_Null = v[i].m_Null;
					field.m_Min = v[i].m_Min;
					field.m_Max = v[i].m_Max;
					field.m_Default = v[i].m_Default;

					USES_CONVERSION;
					char* z = T2A(field.m_FieldName);
					file.Write(z, field.m_FieldName.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_FieldType);
					file.Write(z, field.m_FieldType.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Length);
					file.Write(z, field.m_Length.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Hint);
					file.Write(z, field.m_Hint.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Primary);
					file.Write(z, field.m_Primary.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Null);
					file.Write(z, field.m_Null.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Min);
					file.Write(z, field.m_Min.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Max);
					file.Write(z, field.m_Max.GetLength());
					file.Write("\n", strlen("\n"));

					z = T2A(field.m_Default);
					file.Write(z, field.m_Default.GetLength());
					file.Write("\n", strlen("\n"));
				}
			}
		}
		file.Close();
		return true;
	}

	bool renameTable(CString oldname,CString newname)
	{
		CString path = SDBName + _T("\\file.txt");
		CString oldpath,newpath;
		oldpath = SDBName + _T("\\") + oldname + _T(".tbs");
		newpath = SDBName + _T("\\") + newname + _T(".tbs");
		CFile::Rename(oldpath,newpath);
		oldpath = SDBName + _T("\\") + oldname + _T(".tbd");
		newpath = SDBName + _T("\\") + newname + _T(".tbd");
		CFile::Rename(oldpath,newpath);

		CStdioFile file;
		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			int n;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			s = new CString[n];
			file.ReadString(str);
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				s[i] = str;
				file.ReadString(str);
			}
			file.Close();
			file.Open(path, CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			for (int i = 0; i < n; i++)
			{
				if (s[i].Compare(oldname) != 0)
				{
					USES_CONVERSION;
					char* z = T2A(s[i]);
					file.Write(z, s[i].GetLength());
					file.Write("\n", strlen("\n"));
				}
				else
				{
					USES_CONVERSION;
					char* z = T2A(newname);
					file.Write(z, newname.GetLength());
					file.Write("\n", strlen("\n"));
				}
			}
		}
		file.Close();
		STBName = newname;
		return 0;
	}
};