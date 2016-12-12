#include "APISrcCoding.h"

NAMESPACE_BEGIN(utility)

BOOL IsIncludeChinese(const std::string& strChs)
{
	for (UINT n = 0; n < strChs.length(); n++)
	{
		TCHAR ch[3] = { 0 };
		ch[0] = strChs[n];
		ch[1] = strChs[n+1];
		ch[2] = '\0';
		if ((ch[0] & 0x80) && (ch[1] & 0x80))
		{
			return TRUE;
		}
	}
 	return FALSE;

}


std::string	CStringToString(IN CONST CString& src, UINT codepage /*= CP_UTF8*/)
{
	std::string dst;
	if (src.IsEmpty())
	{
		dst.clear();
		return "";
	}
	int length = ::WideCharToMultiByte(codepage, 0, src, src.GetLength(), NULL, 0, NULL, NULL);
	dst.resize(length);
	::WideCharToMultiByte(codepage, 0, src, src.GetLength(), &dst[0], (int)dst.size(), NULL, NULL);

	return dst;
}


CString StringToCString(const std::string& src, UINT codepage /*= CP_UTF8*/)
{
	CString dst;
	int length = ::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), NULL, 0);
	WCHAR* pBuffer = dst.GetBufferSetLength(length);
	::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), pBuffer, length);

	return dst;
}


UTILITY_API std::wstring StringToWString(IN CONST std::string& src, UINT codepage /*= CP_UTF8*/)
{
	//std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	//return conv.from_bytes(src);
	std::wstring dst;
	int length = ::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), NULL, 0);
	dst.resize(length);
	::MultiByteToWideChar(codepage, 0, src.data(), (int)src.size(), (WCHAR*)dst.c_str(), length);
	return dst;
}

UTILITY_API std::string	WStringToString(IN CONST std::wstring& wstr, UINT codepage /*= CP_UTF8*/)
{
	//std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	//return conv.to_bytes(src);

	std::string dst;
	
	int length = ::WideCharToMultiByte(codepage, 0, (LPCWSTR)wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
	dst.resize(length);
	::WideCharToMultiByte(codepage, 0, (LPCWSTR)wstr.c_str(), wstr.length(), &dst[0], (int)dst.size(), NULL, NULL);
	return dst;

}


UTILITY_API CString	Int32ToCString(INT32 n)
{
	CString	 str;
	str.Format(_T("%d"), n);
	return str;
}
UTILITY_API std::string Uint32ToString(UINT32 n)
{
	char szBuufer[MAX_PATH] = { 0 };
	sprintf_s(szBuufer, MAX_PATH, "%d", n);
	return std::string(szBuufer);
}
UTILITY_API INT32	StringToInt32(const std::string& src)
{
	return std::atoi(src.c_str());
}
UTILITY_API INT32	CStringToInt32(LPCTSTR buff)
{
	if (nullptr == buff)
	{
		return 0;
	}
	std::wstring str(buff);
	return std::stoi(str);
}


UTILITY_API std::string	ToRFC1738(const std::string& source)
{
	static	char hex[] = "0123456789ABCDEF";
	std::string dst;
	for (size_t i = 0; i < source.size(); ++i)
	{
		if (isalnum(source[i]))
		{
			dst += source[i];
		}
		else
			if (source[i] == ' ')
			{
				dst += '+';
			}
			else
			{
				unsigned char c = static_cast<unsigned char>(source[i]);
				dst += '%';
				dst += hex[c / 16];
				dst += hex[c % 16];
			}
	}
	return dst;
}
NAMESPACE_END(utility)