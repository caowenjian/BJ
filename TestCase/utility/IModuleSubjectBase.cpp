#include "IModuleSubjectBase.h"
#include "ModuleSubject.h"
NAMESPACE_BEGIN(utility)

IModuleSubjectBase::IModuleSubjectBase()
{
	m_pSubject = new CModuleSubject();
}

IModuleSubjectBase::~IModuleSubjectBase()
{
	SAFE_DELETE_PTR(m_pSubject)
}


VOID IModuleSubjectBase::AddObserver(IN void* pObserObject, IN MKODelegate callbackFun)
{
	m_pSubject->AddObserver(pObserObject, callbackFun);
}


VOID IModuleSubjectBase::RemoveObserver(IN void* pObserObject)
{
	m_pSubject->RemoveObserver(pObserObject);
}


VOID IModuleSubjectBase::AsynNotifyObserver(IN const std::string& strKeyID)
{
	m_pSubject->AsynNotifyObserver(strKeyID);
}


VOID IModuleSubjectBase::AsynNotifyObserver(IN const std::string& strKeyID, IN std::string& mkoString)
{
	m_pSubject->AsynNotifyObserver(strKeyID, mkoString);
}


VOID IModuleSubjectBase::AsynNotifyObserver(IN const std::string& strKeyID, IN INT32 mkoInt)
{
	m_pSubject->AsynNotifyObserver(strKeyID, mkoInt);
}


VOID IModuleSubjectBase::AsynNotifyObserver(IN const std::string& strKeyID, IN VOID* pMkoVoid)
{
	m_pSubject->AsynNotifyObserver(strKeyID, pMkoVoid);
}


VOID IModuleSubjectBase::AsynNotifyObserver(IN const std::string& strKeyID, IN std::shared_ptr<void> pmkoShardVoid)
{
	m_pSubject->AsynNotifyObserver(strKeyID, pmkoShardVoid);
}

NAMESPACE_END(utility)