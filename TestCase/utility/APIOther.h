#ifndef APIOTHER_H_
#define APIOTHER_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)



/*************************************************
 // Method: IsExitApp
 // Description: 判断某个应用程序是否存在
 // Author: cwj 
 // Date: 2016/03/29
 // Returns: UTILITY_API BOOL
 // Parameter: strAPPName： 自定义的一个应用名。
 // History:
 *************************************************/
UTILITY_API BOOL IsExitApp(CONST CString strAppName);


/*************************************************
 // Method: RegisterComDll
 // Description: 注册一个组件
 // Author: cwj 
 // Date: 2016/03/31
 // Returns: UTILITY_API BOOL
 // Parameter: sFilePath
 // History:
 *************************************************/
UTILITY_API BOOL RegisterComDll(const CString& sFilePath);



UTILITY_API CString GetLastErrorString();


/*************************************************
 // Method: GenerateHttpBoundary
 // Description: 生成Http分隔符
 // Author: cwj 
 // Date: 2016/04/27
 // Returns: UTILITY_API std::string
 // History:
 *************************************************/
UTILITY_API std::string GenerateHttpBoundary();

/*************************************************
// Class: CLock
// Description: 用临界区实现的锁类
// Author: cwj
// Date: 2016/03/16
// History:
*************************************************/
class UTILITY_CLASS CLock
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
class UTILITY_CLASS CAutoLock
{
public:
	CAutoLock(CLock* pLock);
	virtual ~CAutoLock();
private:
	CLock* m_pLock;
};

NAMESPACE_END(utility)

#endif