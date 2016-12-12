#ifndef APITHREAD_H_
#define APITHREAD_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)

/*************************************************
// Class: CThread
// Description: �߳��࣬���ڱ��̳к�ʵ��ThreadFunPro���á�
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
	BOOL CreateThread();	//�����߳�
	void DestoryThread();	//�����߳�
	BOOL WaitThread(DWORD dwWaitTime); //�ȴ��߳̽���
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