#ifndef IMODULESUBJECTBASE_H
#define IMODULESUBJECTBASE_H
#include "globalDefine.h"
#include <functional>
#include <memory>
#include <tuple>
#include <algorithm>
/*************************************************
// Class: IModuleSubjectBase
// Description: 观察者接口类
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/
enum
{
	MKO_STRING = 0,
	MKO_INT,
	MKO_SHARED_VOIDPTR,
	MKO_VOIDPTR,
};
typedef std::tuple<std::string, INT32, std::shared_ptr<VOID>, VOID*> MKO_TUPLE_PARAM;
typedef std::function<VOID(std::string, MKO_TUPLE_PARAM)> MKODelegate;

#define BIND_CALLBACK_1(func)   std::bind(&func, this, std::placeholders::_1)
#define BIND_CALLBACK_2(func)	std::bind(&func, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_CALLBACK_3(func)	std::bind(&func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_CALLBACK_4(func)	std::bind(&func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define BIND_CALLBACK_5(func)	std::bind(&func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
NAMESPACE_BEGIN(utility)
class CModuleSubject;
class UTILITY_CLASS IModuleSubjectBase
{
public:
	IModuleSubjectBase();
	~IModuleSubjectBase();
public:
	VOID AddObserver(IN VOID* pObserObject, IN MKODelegate callbackFun);
	VOID RemoveObserver(IN VOID* pObserObject);
	VOID AsynNotifyObserver(IN CONST std::string& strKeyId);
	VOID AsynNotifyObserver(IN CONST std::string& strKeyId, IN std::string& mkoString);
	VOID AsynNotifyObserver(IN CONST std::string& strKeyId, IN INT32 mkoInt);
	VOID AsynNotifyObserver(IN CONST std::string& strKeyId, IN VOID* pmkoVoid);
	VOID AsynNotifyObserver(IN CONST std::string& strKeyId, IN std::shared_ptr<VOID> pmkoShardVoid);
private:
	CModuleSubject* m_pSubject;
};

NAMESPACE_END(utility)
#endif // !_CMODULESUBJECTBASE_H
