#ifndef APIOTHER_H_
#define APIOTHER_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)



/*************************************************
 // Method: IsExitApp
 // Description: �ж�ĳ��Ӧ�ó����Ƿ����
 // Author: cwj 
 // Date: 2016/03/29
 // Returns: UTILITY_API BOOL
 // Parameter: strAPPName�� �Զ����һ��Ӧ������
 // History:
 *************************************************/
UTILITY_API BOOL IsExitApp(CONST CString strAppName);


/*************************************************
 // Method: RegisterComDll
 // Description: ע��һ�����
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
 // Description: ����Http�ָ���
 // Author: cwj 
 // Date: 2016/04/27
 // Returns: UTILITY_API std::string
 // History:
 *************************************************/
UTILITY_API std::string GenerateHttpBoundary();

/*************************************************
// Class: CLock
// Description: ���ٽ���ʵ�ֵ�����
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
// Description: �Զ��������ù�����������������Ŀ��ء�
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