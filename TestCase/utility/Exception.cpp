#include "Exception.h"
#include <dbghelp.h>
#pragma comment( lib, "DbgHelp" )
NAMESPACE_BEGIN(utility)

LONG CrashCallFun(EXCEPTION_POINTERS *pException)  
{     


	HANDLE lhDumpFile = CreateFile(_T("DumpFile.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);

	MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;
	loExceptionInfo.ExceptionPointers = pException;
	loExceptionInfo.ThreadId = GetCurrentThreadId();
	loExceptionInfo.ClientPointers = TRUE;
	BOOL bRes = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),lhDumpFile, MiniDumpNormal, &loExceptionInfo, NULL, NULL);
	
	CloseHandle(lhDumpFile);

	AfxMessageBox(_T("程序出现异常,即将退出！"));
	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL InitException()
{
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashCallFun);
	return TRUE;
}



NAMESPACE_END(utility)