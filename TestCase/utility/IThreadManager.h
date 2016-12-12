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
// Description: �̹߳���ӿ���
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

	std::mutex					m_cvMutex;			// ������.
	std::condition_variable		m_CV;				// ��������
	std::mutex					m_mutexOperation;

	bool                        m_bContinue;
	std::thread					m_operationThread;
};
UTILITY_API  IThreadManager& GetThreadManagerInstance();
NAMESPACE_END(utility)
#endif // !IEVENTMANAGER_H
