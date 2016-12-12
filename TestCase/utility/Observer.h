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
	VOID*			m_pObserverObject;	//�۲����
	CModuleSubject* m_pSubject;			//�������
	MKODelegate		m_callbackFun;		//�ص�����
};

NAMESPACE_END(utility)
#endif