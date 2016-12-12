#ifndef ITHREADMANAGER_H
#define ITHREADMANAGER_H
#include "globalDefine.h"
#include <condition_variable>
#include <mutex>
#include <functional>
#include <algorithm>
#include <thread>
/*************************************************
// Class: IThreadManager
// Description: 线程管理接口类
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/
NAMESPACE_BEGIN(utility)
class CEventBase;
class UTILITY_CLASS IThreadManager
{
public:
	IThreadManager();
	~IThreadManager();

public:
	BOOL Startup();
	VOID Shutdown();
	BOOL StartOperation(IN CEventBase* pOperation);
	BOOL StartOperationWithLambda(std::function<VOID()> operationRun);

private:
	std::list<CEventBase*>      m_listOperations;

	std::mutex					m_cvMutex;			// 互斥锁.
	std::condition_variable		m_CV;				// 条件变量
	std::mutex					m_mutexOperation;

	bool                        m_bContinue;
	std::thread					m_operationThread;
};
UTILITY_API  IThreadManager& GetThreadManagerInstance();
NAMESPACE_END(utility)
#endif // !IEVENTMANAGER_H
