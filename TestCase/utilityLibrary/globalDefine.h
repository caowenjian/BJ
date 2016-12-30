#ifndef GLOBALDEFINE_H__
#define GLOBALDEFINE_H__

#include <string>
#include <list>
#include <map>
#include <vector>
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")

#ifndef UTILITYLIBRARY_DLL
#define UTILITYLIBRARY_API			__declspec( dllimport )
#define UTILITYLIBRARY_CLASS		__declspec( dllimport )
#else
#define UTILITYLIBRARY_API			__declspec( dllexport )
#define UTILITYLIBRARY_CLASS		__declspec( dllexport )
#endif

#define NAMESPACE_BEGIN_T(n)		namespace n {
#define NAMESPACE_END_T(n)		}




//≈–∂œ÷∏’Î»Ùø’‘Ú∑µªÿfalse
#define ASSERT_PTR_NULL(p)				{ assert(p); if (0 == p) { return 0; } }
#define ASSERT_PTR_VOID(p)				{ assert(p); if (0 == p) { return; } }
#define ASSERT_PTR_FALSE(p)				{ assert(p); if (0 == p) { return FALSE; } }
#define ASSERT_STR_VOID(p)				{ assert(p); if (0 == p || 0 == _tcslen(p)) { return; } }

#define JUDGE_PTR_NULL(p)				{ if (0 == p) { return 0; } }
#define JUDGE_PTR_VOID(p)				{ if (0 == p) { return; } }
#define JUDGE_PTR_FALSE(p)				{ if (0 == p) { return FALSE; } }
#define JUDGE_STR_VOID(p)				{ if (0 == p || 0 == _tcslen(p)) { return; } }

#define JUDGE_INT_VOID(p)				{ if (0 == p) { return;}}
#define JUDGE_INT_FALSE(p)				{ if (FALSE == p) { return FALSE;}}

#define EQUAL_INT_VOID(c1, c2)			{ if (c1 == c2) {return;}}
#define EQUAL_INT_FALSE(c1, c2)			{ if (c1 == c2) {return FALSE;}}
#define EQUAL_INT_TRUE(c1, c2)			{ if (c1 == c2) {return TRUE;}}
//…æ≥˝÷∏’Î
#define SAFE_DELETE_PTR(pointer)	{if(pointer) {delete pointer; pointer = 0;}}




typedef void			   VTT_VOID;
typedef char			   VTT_CHAR;
typedef signed char        VTT_INT8;
typedef short              VTT_INT16;
typedef int                VTT_INT32;
typedef long long          VTT_INT64;
typedef unsigned char      VTT_UINT8;
typedef unsigned char      VTT_UCHAR;
typedef unsigned short     VTT_UINT16;
typedef unsigned int       VTT_UINT32;
typedef unsigned long long VTT_UINT64;
typedef bool VTT_BOOL;
const bool C_TRUE = true;
const bool C_FALSE = false;
typedef SOCKET VTT_SOCKET;
#endif