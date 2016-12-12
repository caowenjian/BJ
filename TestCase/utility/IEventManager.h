#ifndef IEVENTMANAGER_H
#define IEVENTMANAGER_H
#include "globalDefine.h"
#include "APIOther.h"
#include <functional>
#include <algorithm>
/*************************************************
// Class: IEventManager
// Description: 事件管理接口类
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/
NAMESPACE_BEGIN(utility)
class CEventBase;
template <class CEventBase> class CLambdaEvent;
template <class CEventBase> class CTimerLambdaEvent;
class UTILITY_CLASS IEventManager
{
public:
	IEventManager();
	~IEventManager();
public:
	/*************************************************
	 // Method: Startup
	 // Description: 启动事件处理。
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: BOOL
	 // History:
	 *************************************************/
	BOOL Startup();
	/*************************************************
	 // Method: Shutdown
	 // Description: 关闭时间处理。
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: VOID
	 // History:
	 *************************************************/
	VOID Shutdown();
	/*************************************************
	 // Method: asynFireUIEvent
	 // Description: 异步执行一次CEventBase类中的Process函数
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: BOOL
	 // Parameter: pEvent
	 // History:
	 *************************************************/
	BOOL AsynFireUIEvent(IN CONST CEventBase* CONST pEvent);
	/*************************************************
	 // Method: asynFireUIEventWithLambda
	 // Description: 将lambda表达式加入消息队列异步执行。
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: BOOL
	 // Parameter: std::function<VOID
	 // Parameter: eventRun
	 // History:
	 *************************************************/
	BOOL AsynFireUIEventWithLambda(IN std::function<VOID()> eventRun);

	/*************************************************
	 // Method: asynFireUIEventWithTimerLambda
	 // Description: 定时定量执行函数,若delay=0, u32RepeatCount = 1则相当于调用asynFireUIEventWithLambda函数
	 // Author: cwj 
	 // Date: 2016/04/22
	 // Returns: UINT64:该函数对应的ID,用KillTimerLambda关闭此函数调用
	 // Parameter: std::function<VOID
	 // Parameter: eventRun
	 // Parameter: delay:多久调用一次,单位秒
	 // Parameter: u32RepeatCount:重复调用次数，至少一次
	 // History:
	 *************************************************/
	UINT64 AsynFireUIEventWithTimerLambda(IN std::function<VOID()> eventRun, IN UINT32 delay = 0, IN UINT32 u32RepeatCount = 1);
	BOOL KillTimerLambda(UINT64 u64LambdaID);

private:
	BOOL RegisterClass();
private:
	static LRESULT _stdcall WindowProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
private:
	VOID ProcessEvent(CEventBase* pEvent, BOOL bRelease);
	VOID ProcessTimer();
private:
	HWND                    m_hWnd;
	CLambdaEvent<CEventBase>* m_pLambda;	//lambda表达式事件对象
	CTimerLambdaEvent<CEventBase>* m_pTimerLambda;	//lambda表达式事件对象
};
UTILITY_API  IEventManager& GetEventManagerInstance();
NAMESPACE_END(utility)
#endif // !IEVENTMANAGER_H
