#include "APIOther.h"

NAMESPACE_BEGIN(utility)

BOOL RegisterComDll(const CString& sFilePath)
{
	if (!PathFileExists(sFilePath))
		return FALSE;

	typedef LRESULT(*DllRegisterServerProc)(void);
	BOOL retVal = FALSE;
	HINSTANCE hDll = LoadLibrary(sFilePath);
	while (TRUE)
	{
		if (hDll == NULL)
			break;
		DllRegisterServerProc DllRegisterServer;
		DllRegisterServer = (DllRegisterServerProc)GetProcAddress(hDll, "DllRegisterServer");
		if (DllRegisterServer == NULL)
			break;

		int temp = DllRegisterServer();
		if (temp != S_OK)
			break;

		retVal = TRUE;
		break;
	}

	if (retVal == FALSE)
	{
		//LOG__(ERR, _T("register dll failed,%s"), sFilePath);
	}

	FreeLibrary(hDll);
	return retVal;
}

CString GetLastErrorString()
{
	int iStringLength = 0;
	TCHAR szErrorString[1024] = {0};//存放信息字符串的线程局部内存
	iStringLength = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, szErrorString, sizeof(szErrorString), NULL);
	if (iStringLength > 0)//如果成功获取到错误信息字符串，去掉字符串末尾的“\r\n”
	{
		if (szErrorString[iStringLength - 2] == '\r')
		{
			if (szErrorString[iStringLength - 1] == '\n')
			{
				iStringLength -= 2;
			}
			else
			{
				iStringLength--;
			}

			szErrorString[iStringLength] = '\0';
		}

		return szErrorString;
	}
	else
	{
		return _T("");
	}
}


std::string GenerateHttpBoundary()
{
	std::string strBoundary = "----";

	std::string random_number;
	unsigned char c;
	srand((unsigned int)time(0));
	for (int i = 1; i < 15; i++)
	{
		c = int(rand() * 127);
		if (isalpha(c) || isdigit(c))
		{
			random_number += std::string(1, (char)c);
		}
		else
		{
			i--;
		}
	}
	strBoundary += "__" + random_number;
	return strBoundary;
}


BOOL IsExitApp(CONST CString strAppName)
{
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, strAppName);
	if (hMutex != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return TRUE;
	}
	return TRUE;
}


CLock::CLock()
{
	InitializeCriticalSection(&m_critical_section);
}
CLock::~CLock()
{
	DeleteCriticalSection(&m_critical_section);
}

void CLock::Lock()
{
	EnterCriticalSection(&m_critical_section);
}

void CLock::Unlock()
{
	LeaveCriticalSection(&m_critical_section);
 }

CAutoLock::CAutoLock(CLock* pLock)
{
	m_pLock = pLock;
	if (NULL != m_pLock)
		m_pLock->Lock();
}

CAutoLock::~CAutoLock()
{
	if (NULL != m_pLock)
		m_pLock->Unlock();
}

NAMESPACE_END(utility)