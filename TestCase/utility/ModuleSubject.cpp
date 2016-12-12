#include "ModuleSubject.h"
#include "Observer.h"
#include "IEventManager.h"
NAMESPACE_BEGIN(utility)

CModuleSubject::CModuleSubject()
{

}

CModuleSubject::~CModuleSubject()
{
	try
	{
		RemoveAllObservers();
	}
	catch (...)
	{
		//assert(FALSE);
	}
}

BOOL CModuleSubject::IsExistObserver(IN CONST VOID* pObserObject)
{
 	CAutoLock lock(&m_lockObserver);
 	auto iterObserver = std::find_if(m_listObserver.begin(), m_listObserver.end(),
		[=](CObserver* pObserver)
 	{
		return(pObserObject == pObserver->m_pObserverObject);
 	});

	return (iterObserver != m_listObserver.end());
}


VOID CModuleSubject::AddObserver(IN VOID* pObserObject, IN MKODelegate callbackFun)
{
	if (IsExistObserver(pObserObject))
		return;
	CObserver* pObserver = new CObserver(pObserObject, callbackFun);
	{
		CAutoLock lock(&m_lockObserver);
		m_listObserver.push_back(pObserver);
	}
}


VOID CModuleSubject::RemoveObserver(IN VOID* pObserObject)
{
	CAutoLock lock(&m_lockObserver);
	auto iter = std::remove_if(m_listObserver.begin(), m_listObserver.end(),
		[=](CObserver* pObserver)
	{
		bool b = (pObserObject == pObserver->m_pObserverObject);

		if (b)
		{
			SAFE_DELETE_PTR(pObserver)
		}
		return b;
	}
	);
	if (iter != m_listObserver.end())
	{
		m_listObserver.erase(iter, m_listObserver.end());
	}
}


VOID CModuleSubject::RemoveAllObservers()
{
	CAutoLock lock(&m_lockObserver);
	for (CObserver* pObserver : m_listObserver)
	{
		SAFE_DELETE_PTR(pObserver)
	}
	m_listObserver.clear();
}


VOID CModuleSubject::AsynNotifyObserver(IN CONST std::string& keyId)
{
	m_strKeyID = keyId;
	utility::GetEventManagerInstance().AsynFireUIEvent(this);
}


VOID CModuleSubject::AsynNotifyObserver(IN CONST std::string& keyId, IN std::string& mkoString)
{
	m_strKeyID = keyId;
	std::string strData = mkoString;
	INT32 i32Data = 0;
	std::shared_ptr<VOID> sharePData = NULL;
	VOID* pData = NULL;
	m_tupleMkoParam = std::tie(mkoString, i32Data, sharePData, pData);
	utility::GetEventManagerInstance().AsynFireUIEvent(this);
}


VOID CModuleSubject::AsynNotifyObserver(IN CONST std::string& keyId, IN INT32 mkoInt)
{
	m_strKeyID = keyId;
	std::string strData;
	INT32 i32Data = mkoInt;
	std::shared_ptr<VOID> sharePData = NULL;
	VOID* pData = NULL;
	m_tupleMkoParam = std::tie(strData, i32Data, sharePData, pData);
	utility::GetEventManagerInstance().AsynFireUIEvent(this);
}


VOID CModuleSubject::AsynNotifyObserver(IN CONST std::string& keyId, IN VOID* pmkoVoid)
{
	m_strKeyID = keyId;
	std::string strData;
	INT32 i32Data = 0;
	std::shared_ptr<VOID> sharePData = NULL;
	VOID* pData = pmkoVoid;
	m_tupleMkoParam = std::tie(strData, i32Data, sharePData, pData);
	utility::GetEventManagerInstance().AsynFireUIEvent(this);
}


VOID CModuleSubject::AsynNotifyObserver(IN CONST std::string& keyId, IN std::shared_ptr<VOID> pmkoShardVoid)
{
	m_strKeyID = keyId;
	std::string strData;
	INT32 i32Data = 0;
	std::shared_ptr<VOID> sharePData = pmkoShardVoid;
	VOID* pData = NULL;
	m_tupleMkoParam = std::tie(strData, i32Data, sharePData, pData);
	utility::GetEventManagerInstance().AsynFireUIEvent(this);
}


VOID CModuleSubject::Process()
{
	for (CObserver* pObserver : m_listObserver)
	{
		try
		{
			pObserver->m_callbackFun(m_strKeyID, m_tupleMkoParam);
		}
		catch (...)
		{
			//LOG__(ERR, _T("unknown exception"));
		}
	}
}


VOID CModuleSubject::Release()
{

}
NAMESPACE_END(utility)