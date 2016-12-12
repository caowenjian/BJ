#ifndef APITHREAD_H_
#define APITHREAD_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)

/*************************************************
// Class: CThread
// Description: 线程类，用于被继承后实现ThreadFunPro调用。
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/
class UTILITY_CLASS CThread
{
public:
	CThread();
	~CThread();
public:
	BOOL CreateThread();	//创建线程
	void DestoryThread();	//结束线程
	BOOL WaitThread(DWORD dwWaitTime); //等待线程结束
	inline DWORD GetThreadID() { return m_dwThreadID; }

protected:
	virtual UINT32 ThreadFunPro();

private:
	static UINT32 __stdcall ThreadProc(void *lpParam);

private:
	HANDLE		m_hThread;
	DWORD		m_dwThreadID;
};

NAMESPACE_END(utility)
#endif