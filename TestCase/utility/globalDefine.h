#ifndef GLOBALDEFINE_H__
#define GLOBALDEFINE_H__

#include <afxwin.h>
#include <string>
#include <list>
#include <map>
#include <vector>


#ifndef UTILITY_DLL
#define UTILITY_API			__declspec( dllimport )
#define UTILITY_CLASS		__declspec( dllimport )
#else
#define UTILITY_API			__declspec( dllexport )
#define UTILITY_CLASS		__declspec( dllexport )
#endif

#define NAMESPACE_BEGIN(n)		namespace n {
#define NAMESPACE_END(n)		}




//�ж�ָ�������򷵻�false
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
//ɾ��ָ��
#define SAFE_DELETE_PTR(pointer)	{if(pointer) {delete pointer; pointer = 0;}}



/*
typedef void			   VT_VOID;
typedef signed char        VT_CHAR;
typedef signed char        VT_INT8;
typedef short              VT_INT16;
typedef int                VT_INT32;
typedef long long          VT_INT64;
typedef unsigned char      VT_UINT8;
typedef unsigned char      VT_UCHAR;
typedef unsigned short     VT_UINT16;
typedef unsigned int       VT_UINT32;
typedef unsigned long long VT_UINT64;
typedef bool VT_BOOL;
const bool C_TRUE = true;
const bool C_FALSE = false;
typedef SOCKET VT_SOCKET;*/
#endif