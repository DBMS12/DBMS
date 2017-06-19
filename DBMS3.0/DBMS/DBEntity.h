#include <afx.h>
#include <atlstr.h>
#include <windows.h>
#include <direct.h>
#include <vector>


class DBEntity
{
public:
	DBEntity(CString DBName){name = DBName;};
	DBEntity(){};
	~DBEntity(){};

	bool CreateDB()
	{
		CStdioFile file;

		if (file.Open(_T("file.txt"), CFile::modeReadWrite) == 0)
		{
			file.Open(_T("file.txt"), CFile::modeCreate | CFile::modeReadWrite);
			file.Write("1", sizeof(int));
			file.Write("\n", strlen("\n"));
		}
		else
		{
			CString str;
			file.ReadString(str);
			file.ReadString(str);
			while (str != "")
			{
				if (str.Compare(name) == 0)
				{
					return false;
				}
				file.ReadString(str);
			}
			int n;
			file.SeekToBegin();
			file.Read(&n, sizeof(int));
			n++;
			file.SeekToBegin();
			file.Write(&n, sizeof(int));
		}
		file.SeekToEnd();
		USES_CONVERSION;
		char* z = T2A(name);
		file.Write(z, name.GetLength());
		file.Write("\n", strlen("\n"));
		file.Close();

		_mkdir(z);

		CString path = name + _T("\\") + _T("file.txt");
		
		if(file.Open(path , CFile::modeReadWrite) == 0)
		{
			file.Open(path, CFile::modeCreate | CFile::modeReadWrite);
			file.WriteString(_T("0\n"));
		}

		return true;
	}

	bool RenameDB(CString oldname,CString newname)
	{
		CFile::Rename(oldname,newname);
		CStdioFile file;
		if (file.Open(_T("file.txt"), CFile::modeReadWrite) == 0)
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
			file.Open(_T("file.txt"), CFile::modeCreate|CFile::modeReadWrite);
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
		return 0;
	}

	bool DropDB(CString DBname)
	{
		CStdioFile file;
		if (file.Open(_T("file.txt"), CFile::modeReadWrite) == 0)
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
			file.Open(_T("file.txt"), CFile::modeCreate|CFile::modeReadWrite);
			file.SeekToBegin();
			char a[4];
			_itoa_s(n, a, 4, 10);
			file.Write(a, sizeof(int));
			file.Write("\n", strlen("\n"));
			for (int i = 0; i < n+1; i++)
			{
				if (s[i].Compare(DBname) != 0)
				{
					USES_CONVERSION;
					char* z = T2A(s[i]);
					file.Write(z, s[i].GetLength());
					file.Write("\n", strlen("\n"));
				}
			}
		}
		file.Close();
		DeleteDirectory(DBname);
		return true;
	}
	void DeleteDirectory(CString strDir)
	{
		if(strDir.IsEmpty())
		{ 
			RemoveDirectory(strDir);
			return;
		} 
		 //首先删除文件及子文件夹 
		 CFileFind ff;
		 BOOL bFound = ff.FindFile(strDir+_T("\\*"),0);
		 while(bFound) 
		 {
			  bFound = ff.FindNextFile();
			  if(ff.GetFileName()== _T(".")||ff.GetFileName()== _T(".."))continue;
			  //去掉文件(夹)只读等属性
			  SetFileAttributes(ff.GetFilePath(),FILE_ATTRIBUTE_NORMAL);
			  if(ff.IsDirectory())
			  {
				   //递归删除子文件夹 
				   DeleteDirectory(ff.GetFilePath());
				   RemoveDirectory(ff.GetFilePath()); 
			  }
			  else
			  { 
				DeleteFile(ff.GetFilePath());   //删除文件 
			  } 
		 } 
		 ff.Close(); 
		 //然后删除该文件夹
		 RemoveDirectory(strDir);
	}
	
	bool BackupsDB(CString dbName)
	{
		CString targetName = dbName+_T("B");
		CopyDirectory(dbName,targetName);
		return true;
	}


	void CopyDirectory(CString source, CString target)
	{  
		CreateDirectory(target,NULL); //创建目标文件夹  
		CFileFind finder;  
		CString path;  
		path.Format(_T("%s/*.*"),source);
		bool bWorking = finder.FindFile(path);  
		while(bWorking)
		{  
			bWorking = finder.FindNextFile();  
			if(finder.IsDirectory() && !finder.IsDots())
			{ //是文件夹 而且 名称不含 . 或 ..  
				CopyDirectory(finder.GetFilePath(),target+"/"+finder.GetFileName()); 
				//递归创建文件夹+"/"+finder.GetFileName()  
			}  
			else
			{ //是文件 则直接复制  
				CopyFile(finder.GetFilePath(),target+"/"+finder.GetFileName(),FALSE);  
			}  
		}  
	}

	std::vector<CString> GetAllDBName()
	{
		std::vector<CString> v;
		v.clear();
		CStdioFile file;
		if (file.Open(_T("file.txt"), CFile::modeReadWrite) == 0)
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
			for (int i = 0; i < n+1; i++)
			{
				v.push_back(str);
				file.ReadString(str);
			}
			file.Close();
		}
		return v;
	}
private:
	CString name;
};
