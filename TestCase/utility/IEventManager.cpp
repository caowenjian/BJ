#include "IEventManager.h"
#include "EventBase.h"

#define UI_TIMER_ID					WM_USER + 1004
#define UI_EVENT_MSG				WM_USER + 1005
static const wchar_t uiEventWndClass[] = _T("uiEventManager_class");

NAMESPACE_BEGIN(utility)
//用来处理匿名函数异步执行类
template<class base>
class CLambdaEvent : public base
{
public:
	virtual VOID Process()
	{
		JUDGE_INT_VOID(m_listLambdaFun.size())
			m_listLambdaFun.front()();
		m_listLambdaFun.pop_front();
	}

	virtual VOID Release()
	{
		//delete this;
	}
public:
	VOID AddLambdaFun(std::function<void()> LambdaFun)
	{
		m_listLambdaFun.push_back(LambdaFun);
	}
	VOID Clear()
	{
		m_listLambdaFun.clear();
	}

private:
	std::list<std::function<void()>>  m_listLambdaFun;
};
//用来处理定时执行函数类
struct TimerParam
{
	UINT64 m_u64TimerID;					//定时执行函数的ID,唯一
	UINT32 m_u32Delay;						//延迟执行， 单位秒
	std::function < VOID() > m_pCallFun;	//定时执行函数
	UINT32   m_u32RepeatCount;				//重复执行函数的次数
	UINT32 m_u32Elapse;						//逝去的时间
};

template<class base>
class CTimerLambdaEvent : public base
{
public:
	virtual VOID Process()
	{
		CAutoLock lock(&m_lock);
		for (auto iter = m_listTimerParam.begin(); iter != m_listTimerParam.end();)
		{
			if ((iter->m_u32Elapse)++ == iter->m_u32Delay) //时间已到
			{
				iter->m_u32Elapse = 0;
				iter->m_pCallFun();
				iter->m_u32RepeatCount--;
				if (iter->m_u32RepeatCount == 0)
				{
					iter = m_listTimerParam.erase(iter);
					continue;
				}
			}
			++iter;
		}
	}

	virtual VOID Release()
	{
		//delete this;
	}
public:
	VOID AddTimerLambda(IN std::function<VOID()> eventRun, IN UINT32 u32Delay, IN UINT32 u32RepeatCount, IN UINT64 u64TimerID)
	{
		CAutoLock lock(&m_lock);
		TimerParam timerParam;
		timerParam.m_u32RepeatCount = u32RepeatCount;
		timerParam.m_u32Delay = u32Delay;
		timerParam.m_pCallFun = eventRun;
		timerParam.m_u32Elapse = 0;
		timerParam.m_u64TimerID = u64TimerID;
		for (TimerParam& timer : m_listTimerParam)
		{
			if (timerParam.m_u64TimerID == timer.m_u64TimerID)
			{
				timer = timerParam;
				return;
			}
		}
		m_listTimerParam.push_back(timerParam);
	}

	BOOL DelTimerLambda(UINT64 u64LambdaID)
	{
		CAutoLock lock(&m_lock);
		auto iter = std::remove_if(m_listTimerParam.begin(), m_listTimerParam.end()
			, [=](TimerParam& ttime)
		{
			return (u64LambdaID == ttime.m_u64TimerID);
		});
		if (iter != m_listTimerParam.end())
		{
			m_listTimerParam.erase(iter, m_listTimerParam.end());
			return TRUE;
		}
		return FALSE;
	}

	VOID Clear()
	{
		m_listTimerParam.clear();
	}

private:
	CLock m_lock;
	std::list<TimerParam> m_listTimerParam;
};

IEventManager& GetEventManagerInstance()
{
	static IEventManager instanceEventManager;
	return instanceEventManager;
}
IEventManager::IEventManager()
{
	m_pLambda = new CLambdaEvent < CEventBase >();
	m_pTimerLambda = new CTimerLambdaEvent<CEventBase>();
}


IEventManager::~IEventManager()
{
	try
	{
		Shutdown();
		SAFE_DELETE_PTR(m_pLambda)
		SAFE_DELETE_PTR(m_pTimerLambda)
	}
	catch (...)
	{
		
	}
}


BOOL IEventManager::Startup()
{
	EQUAL_INT_TRUE(!m_hWnd, 0)
	JUDGE_INT_FALSE(RegisterClass())
	m_hWnd = ::CreateWindowW(uiEventWndClass, _T("uiEvnetManager_window"),
		0, 0, 0, 0, 0, HWND_MESSAGE, 0, GetModuleHandle(0), 0);
	if (m_hWnd)
	{
		::SetTimer(m_hWnd, reinterpret_cast<UINT_PTR>(this), 1000, NULL);
	}
	JUDGE_INT_FALSE(::IsWindow(m_hWnd))
	return TRUE;
}


VOID IEventManager::Shutdown()
{
	JUDGE_INT_VOID(m_hWnd)
	m_pLambda->Clear();
	m_pTimerLambda->Clear();
	::KillTimer(m_hWnd, UI_TIMER_ID);
	::DestroyWindow(m_hWnd);
	::UnregisterClassW(uiEventWndClass, ::GetModuleHandle(NULL));
	m_hWnd = 0;
	
}


BOOL IEventManager::RegisterClass()
{
	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = ::GetModuleHandle(0);
	wc.lpszClassName = uiEventWndClass;
	ATOM ret = ::RegisterClassExW(&wc);
	JUDGE_INT_FALSE(ret)
	EQUAL_INT_FALSE(::GetLastError(), ERROR_CLASS_ALREADY_EXISTS)
	return TRUE;
} 


LRESULT _stdcall IEventManager::WindowProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	/*ProcessEvent与ProcessTimer在同一线程中*/
	switch (message)
	{
	case UI_EVENT_MSG:
		reinterpret_cast<IEventManager*>(wparam)->ProcessEvent(reinterpret_cast<CEventBase*>(lparam), TRUE); 
		break;
	case WM_TIMER:
		reinterpret_cast<IEventManager*>(wparam)->ProcessTimer();
		break;
	default:
		break;
	}
	return ::DefWindowProc(hWnd, message, wparam, lparam);
}

VOID IEventManager::ProcessEvent(CEventBase* pEvent, BOOL bRelease)
{
	JUDGE_PTR_VOID(pEvent)
	try
	{
		pEvent->Process();
		JUDGE_INT_VOID(bRelease)
		pEvent->Release();
	}
// 	catch (imcore::Exception *e)
// 	{
// 		LOG__(ERR, _T("event run exception"));
// 		pEvent->onException(e);
// 		if (bRelease)
// 			pEvent->release();
// 		if (e)
// 		{
// 			LOG__(ERR, _T("event run exception:%s"), utility::stringToCString(e->m_msg));
// 			assert(FALSE);
// 		}
// 	}
	catch (...)
	{
// 		LOG__(ERR, _T("operation run exception,unknown reason"));
// 		if (bRelease)
// 			pEvent->release();
// 		assert(FALSE);
	}
}

VOID IEventManager::ProcessTimer()
{
	m_pTimerLambda->Process();
}

BOOL IEventManager::AsynFireUIEvent(IN CONST CEventBase* CONST pEvent)
{
	JUDGE_INT_FALSE(m_hWnd)
	JUDGE_INT_FALSE(pEvent)
	JUDGE_INT_FALSE(::PostMessage(m_hWnd, UI_EVENT_MSG, reinterpret_cast<WPARAM>(this), reinterpret_cast<WPARAM>(pEvent)))
	return TRUE;
}

BOOL IEventManager::AsynFireUIEventWithLambda(IN std::function<VOID()> eventRun)
{
	JUDGE_INT_FALSE(m_hWnd)
	JUDGE_PTR_FALSE(m_pLambda)
	m_pLambda->AddLambdaFun(eventRun);
	return AsynFireUIEvent(m_pLambda);
}


UINT64 IEventManager::AsynFireUIEventWithTimerLambda(IN std::function<VOID()> eventRun, IN UINT32 delay /*= 0*/, IN UINT32 u32RepeatCount /*= 1*/)
{
	JUDGE_INT_FALSE(u32RepeatCount)
	//立刻只执行一次
	if ((delay == 0) && (u32RepeatCount == 1))
	{
		AsynFireUIEventWithLambda(eventRun);
		return 1;
	}
	if (delay == 0)
	{
		AsynFireUIEventWithLambda(eventRun); //立刻执行一次,走UI_EVENT_MSG
	}
	static UINT64 s_u64ID = 0;
	if (s_u64ID > 100 * 10000)
	{
		s_u64ID = 0;
	}
	m_pTimerLambda->AddTimerLambda(eventRun, delay, u32RepeatCount, ++s_u64ID);
	return s_u64ID;
}


BOOL IEventManager::KillTimerLambda(UINT64 u64LambdaID)
{
	return m_pTimerLambda->DelTimerLambda(u64LambdaID);
}
NAMESPACE_END(utility)