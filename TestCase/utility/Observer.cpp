#include "Observer.h"

NAMESPACE_BEGIN(utility)

CObserver::CObserver(VOID* pObserverObject, MKODelegate callbackFun) 
: m_pObserverObject(pObserverObject),
m_callbackFun(callbackFun)
{

}
CObserver::~CObserver()
{

}

NAMESPACE_END(utility)