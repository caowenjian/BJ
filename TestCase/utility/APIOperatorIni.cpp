#include "APIOperatorIni.h"

NAMESPACE_BEGIN(utility)

COperatorIni::COperatorIni(CString szFileName) : m_strIniFileAllPath(szFileName)
{
	
}
int COperatorIni::ReadInteger(LPCTSTR szSection, LPCTSTR szKey, int iDefaultValue)
{
	int iResult = GetPrivateProfileInt(szSection, szKey, iDefaultValue, m_strIniFileAllPath);
	return iResult;
}
float COperatorIni::ReadFloat(LPCTSTR szSection, LPCTSTR szKey, float fltDefaultValue)
{
	TCHAR szResult[255] = { 0 };
	TCHAR szDefault[255] = { 0 };
	float fltResult;
	_stprintf_s(szDefault, 255, TEXT("%f"), fltDefaultValue);
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_strIniFileAllPath);
	fltResult = (float)_tstof(szResult);
	return fltResult;
}
bool COperatorIni::ReadBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolDefaultValue)
{
	TCHAR szResult[255] = { 0 };
	TCHAR szDefault[255] = { 0 };
	bool bolResult;
	_stprintf_s(szDefault, 255, TEXT("%s"), bolDefaultValue ? TEXT("True") : TEXT("False"));
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_strIniFileAllPath);
	bolResult = (_tcscmp(szResult, TEXT("True")) == 0 ||
		_tcscmp(szResult, TEXT("true")) == 0) ? true : false;
	return bolResult;
}
CString COperatorIni::ReadString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue)
{
	TCHAR szResult[255] = { 0 };
	GetPrivateProfileString(szSection, szKey, szDefaultValue, szResult, 255, m_strIniFileAllPath);
	return CString(szResult);
}

////////////////////////////CIniWriter//////////////////////////////////////////////
void COperatorIni::WriteInteger(LPCTSTR szSection, LPCTSTR szKey, int iValue)
{
	TCHAR szValue[255] = { 0 };
	_stprintf_s(szValue, 255, TEXT("%d"), iValue);
	WritePrivateProfileString(szSection, szKey, szValue, m_strIniFileAllPath);
}
void COperatorIni::WriteFloat(LPCTSTR szSection, LPCTSTR szKey, float fltValue)
{
	TCHAR szValue[255] = { 0 };
	_stprintf_s(szValue, 255, TEXT("%f"), fltValue);
	WritePrivateProfileString(szSection, szKey, szValue, m_strIniFileAllPath);
}
void COperatorIni::WriteBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolValue)
{
	TCHAR szValue[255] = { 0 };
	_stprintf_s(szValue, 255, TEXT("%s"), bolValue ? TEXT("True") : TEXT("False"));
	WritePrivateProfileString(szSection, szKey, szValue, m_strIniFileAllPath);
}
void COperatorIni::WriteString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue)
{
	WritePrivateProfileString(szSection, szKey, szValue, m_strIniFileAllPath);
}
NAMESPACE_END(utility)
