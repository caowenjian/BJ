#include "AutoLock.h"
NAMESPACE_BEGIN_T(utilityLibrary)
CLock::CLock()
{
	InitializeCriticalSection(&m_critical_section);
}
CLock::~CLock()
{
	DeleteCriticalSection(&m_critical_section);
}

void CLock::Lock()
{
	EnterCriticalSection(&m_critical_section);
}

void CLock::Unlock()
{
	LeaveCriticalSection(&m_critical_section);
}

CAutoLock::CAutoLock(CLock* pLock)
{
	m_pLock = pLock;
	if (NULL != m_pLock)
		m_pLock->Lock();
}

CAutoLock::~CAutoLock()
{
	if (NULL != m_pLock)
		m_pLock->Unlock();
}

NAMESPACE_END_T(utilityLibrary)