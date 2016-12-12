#ifndef IEVENTMANAGER_H
#define IEVENTMANAGER_H
#include "globalDefine.h"
#include "APIOther.h"
#include <functional>
#include <algorithm>
/*************************************************
// Class: IEventManager
// Description: �¼�����ӿ���
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
	 // Description: �����¼�����
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: BOOL
	 // History:
	 *************************************************/
	BOOL Startup();
	/*************************************************
	 // Method: Shutdown
	 // Description: �ر�ʱ�䴦��
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: VOID
	 // History:
	 *************************************************/
	VOID Shutdown();
	/*************************************************
	 // Method: asynFireUIEvent
	 // Description: �첽ִ��һ��CEventBase���е�Process����
	 // Author: cwj 
	 // Date: 2016/04/21
	 // Returns: BOOL
	 // Parameter: pEvent
	 // History:
	 *************************************************/
	BOOL AsynFireUIEvent(IN CONST CEventBase* CONST pEvent);
	/*************************************************
	 // Method: asynFireUIEventWithLambda
	 // Description: ��lambda���ʽ������Ϣ�����첽ִ�С�
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
	 // Description: ��ʱ����ִ�к���,��delay=0, u32RepeatCount = 1���൱�ڵ���asynFireUIEventWithLambda����
	 // Author: cwj 
	 // Date: 2016/04/22
	 // Returns: UINT64:�ú�����Ӧ��ID,��KillTimerLambda�رմ˺�������
	 // Parameter: std::function<VOID
	 // Parameter: eventRun
	 // Parameter: delay:��õ���һ��,��λ��
	 // Parameter: u32RepeatCount:�ظ����ô���������һ��
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
	CLambdaEvent<CEventBase>* m_pLambda;	//lambda���ʽ�¼�����
	CTimerLambdaEvent<CEventBase>* m_pTimerLambda;	//lambda���ʽ�¼�����
};
UTILITY_API  IEventManager& GetEventManagerInstance();
NAMESPACE_END(utility)
#endif // !IEVENTMANAGER_H
