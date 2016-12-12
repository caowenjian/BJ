#include "APIDirectoryFile.h"

NAMESPACE_BEGIN(utility)

UINT32 GetFileLength(IN CONST CString strFileAllPath)
{
	HANDLE handle = CreateFile(strFileAllPath, FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	DWORD dwFileSize = 0;
	if (handle != INVALID_HANDLE_VALUE)
	{
		dwFileSize = GetFileSize(handle, NULL);
		CloseHandle(handle);
	}
	return dwFileSize;
}



BOOL IsFileExist(IN CONST LPCTSTR csFileName)
{
	ASSERT(csFileName);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(csFileName, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	else
	{
		FindClose(hFind);
	}
	return TRUE;
}


VOID ParseFileAllPath(IN CString strFileAllPath, OUT CString& strPath, OUT CString &strFileName, OUT CString& strExtendName)
{
	int iFindnumber;
	iFindnumber = strFileAllPath.ReverseFind('\\');
	if (iFindnumber == -1)
	{
		iFindnumber = strFileAllPath.ReverseFind('/');
	}
	strPath = strFileAllPath.Mid(0, iFindnumber);

	CString FileTitle = strFileAllPath.Right(strFileAllPath.GetLength() - 1 - iFindnumber);
	int Which = FileTitle.ReverseFind('.');
	strExtendName = FileTitle.Right(FileTitle.GetLength() - Which - 1);
	if (Which != -1)
	{
		FileTitle = FileTitle.Left(Which);
	}
	strFileName = FileTitle;
}



CString GetAppPath()
{
	static CString g_sDllPath = _T("");

	if (g_sDllPath.IsEmpty())
	{
		TCHAR	buffer[MAX_PATH];
		ZeroMemory(buffer, sizeof(TCHAR)* MAX_PATH);
		HMODULE h = GetModuleHandle(NULL);
		::GetModuleFileName(h, buffer, MAX_PATH);
		::PathRemoveFileSpec(buffer);
		g_sDllPath = buffer;
		g_sDllPath += _T("\\");
	}
	return g_sDllPath;
}



BOOL CreateTempFile(IN CString strFileAllPath, IN UINT32 u32FileSize, OUT CString& strTempAllPath)
{
	/***创建一个临时文件***/
	CString strFileName;
	CString strFileExtend;
	CString strTempPath;
	CString strPath;
	ParseFileAllPath(strFileAllPath, strPath, strFileName, strFileExtend);
	strTempPath = strTempAllPath;
	strTempPath += strFileName;
	strTempPath += _T(".temp");

	if (IsFileExist(strTempPath))
	{
		strTempAllPath = strTempPath;
		return FALSE;
	}

	FILE * pFile = NULL;
	_tfopen_s(&pFile, strTempPath, _T("wb"));
	if (pFile == NULL)
	{
		return FALSE;
	}
	UCHAR *pTempData = NULL;
	UINT32 u32TotalSize = 0;			//已经写入文件总大小
	UINT32 uRealSize = 0;
	UINT32 u32Size = 1024 * 1024 * 10;	//每次写入文件大小
	UINT32 u32RemainSize = 0;			//剩下未写入文件总大小
	while (u32TotalSize != u32FileSize)
	{
		u32RemainSize = u32FileSize - u32TotalSize;
		if (u32RemainSize > u32Size)
		{
			pTempData = new UCHAR[u32Size];
			memset(pTempData, 0, u32Size);
			uRealSize = fwrite(pTempData, 1, u32Size, pFile);
		}
		else
		{
			pTempData = new UCHAR[u32RemainSize];
			memset(pTempData, 0, u32RemainSize);
			uRealSize = fwrite(pTempData, 1, u32RemainSize, pFile);
		}
		u32TotalSize += uRealSize;
	}
	fclose(pFile);
	strTempAllPath = strTempPath;
	return TRUE;
}





/*************************************************
 // Method: SetFileData
 // Description: 对指定文件中某一段数据进行设置替换
 // Author: cwj 
 // Date: 2016/05/04
 // Returns: BOOL
 // Parameter: strFileAllPath
 // Parameter: u32Offset
 // Parameter: u32DataSize
 // Parameter: pData
 // History:
 *************************************************/
BOOL SetFileData(IN CString strFileAllPath, IN UINT32 u32Offset, IN UINT32 u32DataSize, IN UCHAR* pData)
{
	FILE* pFile = NULL;

	if (!u32Offset && !u32DataSize)
	{
		return FALSE;
	}

	//TRACE("offset=%u, datasize=%u\n", u32Offset, u32DataSize);
	_tfopen_s(&pFile, strFileAllPath, _T("rb+"));
	if (pFile == NULL)
	{
		return FALSE;
	}

	if (fseek(pFile, u32Offset, SEEK_SET))
	{
		fclose(pFile);
		return FALSE;
	}
	//long l = ftell(pFile);

	UINT32 uWriteSize = fwrite(pData, 1, u32DataSize, pFile);
	//l = ftell(pFile);

	fclose(pFile);
	if (uWriteSize != u32DataSize)
	{
		return FALSE;
	}
	return TRUE;
}


/*************************************************
 // Method: GetFileData
 // Description: 获取指定文件中某一段的数据
 // Author: cwj 
 // Date: 2016/05/04
 // Returns: BOOL
 // Parameter: strFileAllPath
 // Parameter: u32Offset
 // Parameter: u32DataSize
 // Parameter: pData
 // History:
 *************************************************/
BOOL GetFileData(IN CString strFileAllPath, IN UINT32 u32Offset, IN UINT32& u32DataSize, IN OUT UCHAR* pData)
{

	FILE* pFile = NULL;
	UINT32 uRealSize = 0;
	_tfopen_s(&pFile, strFileAllPath, _T("rb"));
	if (pFile == NULL)
	{
		return FALSE;
	}
	if (fseek(pFile, u32Offset, SEEK_SET))
	{
		fclose(pFile);
		return FALSE;
	}

	u32DataSize = fread(pData, 1, u32DataSize, pFile);

	fclose(pFile);
	return TRUE;
}


BOOL CreateAllDirectories(CString csDir)
{
	if (csDir.Right(1) == _T("\\"))
	{
		csDir = csDir.Left(csDir.GetLength() - 1);
	}

	if (::GetFileAttributes(csDir) != INVALID_FILE_ATTRIBUTES)
	{
		return TRUE;
	}

	int nFound = csDir.ReverseFind('\\');
	CreateAllDirectories(csDir.Left(nFound));

	if (!::CreateDirectory(csDir, NULL))
	{
		return FALSE;
	}

	return TRUE;
}


CString ByteSizeToString(UINT32 size)
{
	const TCHAR* units[] = { _T("字节"), _T("KB"), _T("MB"), _T("GB"), _T("TB"), _T("PB"), _T("EB"), _T("ZB"), _T("YB") };
	//const char* units[] = { "字节", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	int i = 0;
	float fSize = (float)size;
	while (fSize > 1024)
	{
		fSize /= 1024;
		i++;
	}
	//TCHAR buf[1024];
	//_stprintf_s(buf, 1024, _T("%.*f %s"), i, fSize, units[i]);
	//_sprintf_s(buf, 1024, "%.*f %s", i, fSize, units[i]);
	CString strBuf;
	strBuf.Format(_T("%.*f %s"), i, fSize, units[i]);
	return strBuf;
}



VOID DeleteAllFile(CString strPathFileName)
{
	if (strPathFileName.ReverseFind('*'))
	{
		CString strDelPath = strPathFileName;
		::PathRemoveFileSpec(strDelPath.GetBuffer(0));
		strDelPath = strDelPath.GetBufferSetLength(strDelPath.GetLength());
		strDelPath += _T("\\");
		WIN32_FIND_DATA wfd = { 0 };
		HANDLE hFile = ::FindFirstFile(strPathFileName, &wfd);
		::DeleteFile(strDelPath + wfd.cFileName);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		while (::FindNextFile(hFile, &wfd))
		{
			::DeleteFile(strDelPath + wfd.cFileName);
		}
		::FindClose(hFile);
	}
	else
	{
		DeleteFile(strPathFileName);
	}

}
NAMESPACE_END(utility)