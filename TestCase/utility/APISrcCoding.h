#ifndef APISRCCODING_H_
#define APISRCCODING_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)

/*************************************************
// Method: IsIncludeChinese
// Description: �ж��ַ������Ƿ��������
// Author: cwj
// Date: 2016/03/16
// Returns: BOOL
// Parameter: strChs
// History:
*************************************************/
UTILITY_API BOOL IsIncludeChinese(IN CONST std::string& strChs);


/*************************************************
 // Method: CStringToString
 // Description: ��CString����ת��string����
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API std::string
 // Parameter: src
 // Parameter: codepage
 // History:
 *************************************************/
UTILITY_API std::string	CStringToString(IN CONST CString& src, UINT codepage = CP_UTF8);


/*************************************************
 // Method: StringToCString
 // Description: ��string����ת��CString����
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API CString
 // Parameter: src
 // Parameter: codepage
 // History:
 *************************************************/
UTILITY_API CString	StringToCString(IN CONST std::string& src, UINT codepage = CP_UTF8);



/*************************************************
 // Method: StringToWString
 // Description: ��string����ת��wstring����
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API std::wstring
 // Parameter: src
 // Parameter: codepage
 // History:
 *************************************************/
UTILITY_API std::wstring StringToWString(IN CONST std::string& src, UINT codepage = CP_UTF8);

/*************************************************
 // Method: WStringToString
 // Description: ��wstring����ת��string����
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API std::string
 // Parameter: src
 // Parameter: codepage
 // History:
 *************************************************/
UTILITY_API std::string	WStringToString(IN CONST std::wstring& src, UINT codepage = CP_UTF8);



/*************************************************
 // Method: ToRFC1738
 // Description: ת��RFC1738����
 // Author: cwj 
 // Date: 2016/04/27
 // Returns: UTILITY_API std::string
 // Parameter: source
 // History:
 *************************************************/
UTILITY_API std::string	ToRFC1738(const std::string& source);

UTILITY_API CString		Int32ToCString(INT32 n);
UTILITY_API std::string Uint32ToString(UINT32 n);
UTILITY_API INT32		StringToInt32(const std::string& src);
UTILITY_API INT32		CStringToInt32(LPCTSTR buff);
NAMESPACE_END(utility)

#endif