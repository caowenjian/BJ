#ifndef APIDATETIME_H_
#define APIDATETIME_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)


/*************************************************
 // Method: U32TimeToCString
 // Description: ��10λʱ���ת�����ַ�����ʽ�ġ�(13λ��ʱ�������1000)
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API CString
 // Parameter: u32Time
 // Parameter: nFormat
 // Parameter: bTimeZone
 // Parameter: bDaylight
 // History:
 *************************************************/
UTILITY_API CString	U32TimeToCString(UINT32 u32Time, INT nFormat, BOOL bTimeZone = FALSE, BOOL bDaylight = FALSE);

NAMESPACE_END(utility)
#endif