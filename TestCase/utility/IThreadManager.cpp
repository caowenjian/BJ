#include "IThreadManager.h"
#include "EventBase.h"

NAMESPACE_BEGIN(utility)
class CLambdaOperation : public CEventBase
{
public:
	CLambdaOperation(std::function<void()> operationRun)
		:m_operationRun(operationRun)
	{
	}

	virtual void Process()
	{
		m_operationRun();
	}
	virtual void Release()
	{
		delete this;
	}

private:
	std::function<void()> m_operationRun;
};


IThreadManager& GetThreadManagerInstance()
{
	static IThreadManager manager;
	return manager;
}

IThreadManager::IThreadManager()
{
	m_bContinue = true;
}
IThreadManager::~IThreadManager()
{
	try
	{
		Shutdown();
	}
	catch (...)
	{
// 		LOG__(ERR, _T("OperationManager: shutdown throw unknown exception"));
// 		assert(FALSE);
	}
}

BOOL IThreadManager::Startup()
{
	m_operationThread = std::thread([&]
	{
		std::unique_lock <std::mutex> lck(m_cvMutex);
		CEventBase* pOperation = nullptr;
		while (m_bContinue)
		{
			if (!m_bContinue)
				break;
			if (m_listOperations.empty())
				m_CV.wait(lck);
			if (!m_bContinue)
				break;
			{
				std::lock_guard<std::mutex> lock(m_mutexOperation);
				if (m_listOperations.empty())
					continue;
				pOperation = m_listOperations.front();
				m_listOperations.pop_front();
			}

			if (!m_bContinue)
				break;

			if (pOperation)
			{
				pOperation->Process();
				pOperation->Release();
			}
		}
	});
	return TRUE;
}


VOID IThreadManager::Shutdown()
{
	m_bContinue = false;
	m_CV.notify_one();
	//Sleep(10000);
	//todo kuaidao ...join may be infinite waiting
	if (m_operationThread.joinable())
		m_operationThread.join();

	{
		std::lock_guard<std::mutex> locker(m_mutexOperation);
		for (CEventBase* pOper : m_listOperations)
		{
			try
			{
				pOper->Release();
			}
			catch (...)
			{

			}
		}
		m_listOperations.clear();
	}
}


BOOL IThreadManager::StartOperation(IN CEventBase* pOperation)
{
	JUDGE_PTR_FALSE(pOperation)
	std::lock_guard<std::mutex> locker(m_mutexOperation);
	m_listOperations.push_back(pOperation);
	m_CV.notify_one();
	return TRUE;
}
BOOL IThreadManager::StartOperationWithLambda(std::function<VOID()> operationRun)
{
	CLambdaOperation* pLambdaOper = new CLambdaOperation(operationRun);
	return StartOperation(pLambdaOper);
	return TRUE;
}
NAMESPACE_END(utility)