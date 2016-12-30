#ifndef _AUTOLOCK_H
#define _AUTOLOCK_H
#include "globalDefine.h"
NAMESPACE_BEGIN_T(utilityLibrary)
/*************************************************
// Class: CLock
// Description: 用临界区实现的锁类
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/
class UTILITYLIBRARY_CLASS CLock
{
public:
	CLock();
	~CLock();
	VOID Lock();
	VOID Unlock();
private:
	CRITICAL_SECTION m_critical_section;
};

/*************************************************
// Class: CAutoLock
// Description: 自动锁，利用构造和析构来管理锁的开关。
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/

class UTILITYLIBRARY_CLASS CAutoLock
{
public:
	CAutoLock(CLock* pLock);
	virtual ~CAutoLock();
private:
	CLock* m_pLock;
};

NAMESPACE_END_T(utilityLibrary)
#endif