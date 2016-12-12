#include "APIDateTime.h"

NAMESPACE_BEGIN(utility)
CString	U32TimeToCString(UINT32 u32Time, INT nFormat, BOOL bTimeZone /*= FALSE*/, BOOL bDaylight /*= FALSE*/)
{
	FILETIME ft;
	SYSTEMTIME pst;
	LONGLONG nLL = Int32x32To64(u32Time, 10000000) + 116444736000000000;//后面数字表示是UTC时间
	ft.dwLowDateTime = (DWORD)nLL;
	ft.dwHighDateTime = (DWORD)(nLL >> 32);
	FileTimeToSystemTime(&ft, &pst);


	CString strFormat;
	switch (nFormat)
	{
	case 0:
		strFormat.Format(_T("%02d月%02d日"), pst.wMonth, pst.wDay);
		break;
	case 1:
		strFormat.Format(_T("%04d年%02d月%02d日"), pst.wYear, pst.wMonth, pst.wDay);
	case 2:
		strFormat.Format(_T("%04d-%02d-%02d"), pst.wYear, pst.wMonth, pst.wDay);
		break;
	default:

		break;
	}
	return strFormat;
}

NAMESPACE_END(utility)
