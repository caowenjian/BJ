#ifndef MODULESUBJECT_H_
#define MODULESUBJECT_H_
#include "globalDefine.h"
#include "IModuleSubjectBase.h"
#include "APIOther.h"
#include "EventBase.h"
NAMESPACE_BEGIN(utility)
class CObserver;

class CModuleSubject final : public CEventBase
{
public:
	CModuleSubject();
	~CModuleSubject();
public:
	virtual VOID Process();
	virtual VOID Release();
public:
	BOOL IsExistObserver(IN CONST VOID* pObserObject);
	VOID AddObserver(IN VOID* pObserObject, IN MKODelegate callbackFun);
	VOID RemoveObserver(IN VOID* pObserObject);
	VOID RemoveAllObservers();
	VOID AsynNotifyObserver(IN CONST std::string& keyId);
	VOID AsynNotifyObserver(IN CONST std::string& keyId, IN std::string& mkoString);
	VOID AsynNotifyObserver(IN CONST std::string& keyId, IN INT32 mkoInt);
	VOID AsynNotifyObserver(IN CONST std::string& keyId, IN VOID* pmkoVoid);
	VOID AsynNotifyObserver(IN CONST std::string& keyId, IN std::shared_ptr<VOID> pmkoShardVoid);
private:
	CLock	m_lockObserver;
	std::list<CObserver*> m_listObserver;
	std::string		m_strKeyID;			
	MKO_TUPLE_PARAM m_tupleMkoParam;	//回调参数
};

NAMESPACE_END(utility)
#endif