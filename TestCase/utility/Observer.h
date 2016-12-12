#ifndef OBSERVER_H_
#define OBSERVER_H_
#include "globalDefine.h"
#include "IModuleSubjectBase.h"
NAMESPACE_BEGIN(utility)
class CModuleSubject;

class CObserver 
{
public:
	CObserver(VOID* pObserverObject, MKODelegate callbackFun);
	~CObserver();
public:
	
public:
	VOID*			m_pObserverObject;	//观察对象
	CModuleSubject* m_pSubject;			//主题对象
	MKODelegate		m_callbackFun;		//回调函数
};

NAMESPACE_END(utility)
#endif