#ifndef APIOPERATORINI_H_
#define APIOPERATORINI_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)

class UTILITY_CLASS COperatorIni
{
public:
	COperatorIni(CString szFileName);
	~COperatorIni();
	int ReadInteger(LPCTSTR szSection, LPCTSTR szKey, int iDefaultValue);
	float ReadFloat(LPCTSTR szSection, LPCTSTR szKey, float fltDefaultValue);
	bool ReadBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolDefaultValue);
	CString ReadString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue);
	void WriteInteger(LPCTSTR szSection, LPCTSTR szKey, int iValue);
	void WriteFloat(LPCTSTR szSection, LPCTSTR szKey, float fltValue);
	void WriteBoolean(LPCTSTR szSection, LPCTSTR szKey, bool bolValue);
	void WriteString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue);
private:
	CString m_strIniFileAllPath;
};



NAMESPACE_END(utility)
#endif