#include "APIThread.h"

NAMESPACE_BEGIN(utility)
CThread::CThread()
:m_hThread(0)
{

}

// -----------------------------------------------------------------------------

CThread::~CThread()
{
	if (m_hThread)
		::CloseHandle(m_hThread);
	m_hThread = 0;
}

BOOL CThread::CreateThread()
{
	m_hThread = (HANDLE)_beginthreadex(0, 0, ThreadProc, this, 0, (unsigned*)&m_dwThreadID);

	if (m_hThread < (HANDLE)2)
	{
		m_hThread = 0;
		m_dwThreadID = 0;
	}

	return m_hThread >(HANDLE)1;
}

void CThread::DestoryThread()
{
	if (m_hThread)
	{
		::TerminateThread(m_hThread, 0);
		WaitForSingleObject(m_hThread, 500);
		::CloseHandle(m_hThread);
		m_hThread = 0;
		m_dwThreadID = 0;
	}
}

BOOL CThread::WaitThread(DWORD dwWaitTime)
{
	if (m_hThread == 0)
		return TRUE;
	return (::WaitForSingleObject(m_hThread, dwWaitTime) != WAIT_TIMEOUT);
}

UINT32 CThread::ThreadFunPro()
{
	return 0;
}

UINT32 __stdcall CThread::ThreadProc(void *lpParam)
{
	CThread* pThread = (CThread*)lpParam;
	if (pThread != 0)
	{
		pThread->ThreadFunPro();
	}
	return 0;
}

NAMESPACE_END(utility)
