#ifndef EVENTBASE_H_
#define EVENTBASE_H_
#include "globalDefine.h"
NAMESPACE_BEGIN(utility)

class CEventBase
{
public:
	CEventBase(){}
	~CEventBase(){}
public:
	virtual VOID Process() = 0;
// 	virtual void onException(imcore::Exception* e)
// 	{
// 		LOG__(ERR, _T("IEvent exception,%d"));
// 		assert(FALSE);
// 	}
	virtual VOID Release() = 0;
};

NAMESPACE_END(utility)
#endif