#include <afx.h>
#include <atlstr.h>
#include <windows.h>
#include <direct.h>
#include <map>
#include <vector>
#include "Struct.h"
#include <algorithm>

extern CString P;

class RecordEntity
{
public:
	RecordEntity()
	{
	}
	~RecordEntity(){};
	
	//std::map<CString,CString> record;
	static bool comparer(std::map<CString, CString> &a, std::map<CString, CString> &b)
	{
		return (a[P] < b[P]);
	}
	
	bool writeRecord(CString DBname,CString TBname,std::map<CString, CString> &mp)
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(DBname,TBname,v);

		// ================================================================
		// 建索引文件
		std::vector<std::map<CString, CString>> allrcrds;
		int count;
		readRecord(DBname, TBname, allrcrds, count);
		
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].m_Primary == "Y")
			{
				P = v[i].m_FieldName;
				break;
			}
		}
		allrcrds.push_back(mp);
		sort(allrcrds.begin(), allrcrds.end(), &RecordEntity::comparer);
		CStdioFile index;
		CString indexpath = DBname + _T("\\") + TBname + _T(".ndx");
		if (index.Open(indexpath, CFile::modeCreate | CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			index.SeekToBegin();
			int fl = 0;
			for (int i = 0; i < allrcrds.size(); i++)
			{
				USES_CONVERSION;
				CString value = allrcrds[i][P];
				char* z = T2A(value);
				index.Write(z, allrcrds[i][P].GetLength());
				index.Write("\n", strlen("\n"));
				for (int j = 0; j < i; j++)
				{
					for (int k = 0; k < v.size(); k++)
					{
						fl += allrcrds[j][v[k].m_FieldName].GetLength();
					}
				}
				char a[4];
				_itoa_s(fl, a, 4, 10);
				index.Write(a, sizeof(int));
				index.Write("\n", strlen("\n"));
			}
		}
		index.Close();
		// ==========================================================索引文件创建完成/

		CStdioFile file;
		CString path = DBname + _T("\\") + TBname + _T(".tbd");

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

			for(int i=0;i<v.size();i++)
			{
				USES_CONVERSION;
				CString value = mp[v[i].m_FieldName];
				char* z = T2A(value);
				file.Write(z, value.GetLength());
				file.Write("\n", strlen("\n"));
			}
		}
		file.Close();
		return true;
	}

	bool readRecord(CString DBname,CString TBname,std::vector<std::map<CString, CString>> &vct,int &n)
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(DBname,TBname,v);

		CStdioFile file;
		vct.clear();
		CString path = DBname + _T("\\") + TBname + _T(".tbd");

		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			n = atoi(num);
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				std::map<CString, CString> mp;
				mp.clear();
				for(int j=0;j<v.size();j++)
				{
					file.ReadString(str);
					CString key = v[j].m_FieldName;
					mp.insert(std::make_pair(key,str));
				}
				vct.push_back(mp);
			}
			file.Close();
		}
		return true;
	}

	bool deleteRecord(CString DBname,CString TBname,std::map<CString,CString> &Map)
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(DBname,TBname,v);

		CStdioFile file;
		
		std::vector<std::map<CString, CString>> vct;
		vct.clear();

		CString path = DBname + _T("\\") + TBname + _T(".tbd");

		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			int n = atoi(num);
			file.ReadString(str);
			for (int i = 0; i < n; i++)
			{
				std::map<CString, CString> mp;
				mp.clear();
				for(int j=0;j<v.size();j++)
				{
					file.ReadString(str);
					CString key = v[j].m_FieldName;
					mp.insert(std::make_pair(key,str));
				}
				vct.push_back(mp);
			}
			file.Close();
			file.Open(path, CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n-1, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));

			for(int i=0;i<n;i++)
			{
				std::map<CString,CString> mp;
				mp = vct[i];
				bool flag = false;

				for(int j=0;j<v.size();j++)
				{
					CString p = mp[v[j].m_FieldName];
					CString primary = Map[v[j].m_FieldName];
					if(p==primary)
					{
						flag = false;
					}
					else
					{
						flag = true;
						break;
					}
				}

				if(flag)
				{
					for(int j=0;j<v.size();j++)
					{
						USES_CONVERSION;
						CString value = mp[v[j].m_FieldName];
						char* z = T2A(value);
						file.Write(z, value.GetLength());
						file.Write("\n", strlen("\n"));
					}
				}
			}

			file.Close();
		}
	}

	bool updateRecord(CString DBname,CString TBname,std::map<CString,CString> &newMap,std::map<CString,CString> &oldMap)
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(DBname,TBname,v);

		CStdioFile file;
		
		std::vector<std::map<CString, CString>> vct;
		vct.clear();

		CString path = DBname + _T("\\") + TBname + _T(".tbd");

		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			int n = atoi(num);
			file.ReadString(str);
			for (int i = 0; i < n ; i++)
			{
				std::map<CString, CString> mp;
				mp.clear();
				for(int j=0;j<v.size();j++)
				{
					file.ReadString(str);
					CString key = v[j].m_FieldName;
					mp.insert(std::make_pair(key,str));
				}
				vct.push_back(mp);
			}
			file.Close();
			file.Open(path, CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));

			for(int i=0;i<n ;i++)
			{
				std::map<CString,CString> mp;
				mp = vct[i];
				bool flag = false;

				for(int j=0;j<v.size();j++)
				{
					CString p = mp[v[j].m_FieldName];
					CString primary = oldMap[v[j].m_FieldName];
					if(p==primary)
					{
						flag = false;
					}
					else
					{
						flag = true;
						break;
					}
				}

				if(flag)
				{
					for(int j=0;j<v.size();j++)
					{
						USES_CONVERSION;
						CString value = mp[v[j].m_FieldName];
						char* z = T2A(value);
						file.Write(z, value.GetLength());
						file.Write("\n", strlen("\n"));
					}
				}
				else
				{
					for(int j=0;j<v.size();j++)
					{
						USES_CONVERSION;
						CString value = newMap[v[j].m_FieldName];
						char* z = T2A(value);
						file.Write(z, value.GetLength());
						file.Write("\n", strlen("\n"));
					}
				}
			}

			file.Close();
		}
	}

	bool findRecord(CString DBname,CString TBname,std::vector<std::map<CString, CString>> &vct,std::map<CString, CString> Map)
	{
		std::vector<Field> v;
		TableEntity te;
		te.getAttributes(DBname,TBname,v);

		CStdioFile file;
		
		vct.clear();

		CString path = DBname + _T("\\") + TBname + _T(".tbd");

		if (file.Open(path, CFile::modeReadWrite) == 0)
		{
			return false;
		}
		else
		{
			CString str;
			CString* s;
			char num[4];
			file.SeekToBegin();
			file.Read(&num, sizeof(int));
			int n = atoi(num);
			file.ReadString(str);
			for (int i = 0; i < n ; i++)
			{
				std::map<CString, CString> mp;
				mp.clear();
				bool flag = true;
				for(int j=0;j<v.size();j++)
				{
					file.ReadString(str);
					CString key = v[j].m_FieldName;
					mp.insert(std::make_pair(key,str));
					if(flag)
					{
						if(str!=Map[key])
						{
							flag = false;
						}
					}
				}
				if(flag)vct.push_back(mp);
			}
			file.Close();
		}
	}

	int binary_search(std::vector<std::map<CString, CString>> vct, int len, CString Map)
	{
		int low = 0;
		int high = len - 1;
		while (low <= high)
		{
			int middle = (low + high) / 2;
			if (vct[middle][P] == Map)
				return middle;
			//在左半边
			else if (vct[middle][P] > Map)
				high = middle - 1;
			//在右半边
			else
				low = middle + 1;
		}
		//没找到
		return -1;
	}
};