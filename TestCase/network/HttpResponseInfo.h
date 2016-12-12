#ifndef HTTPRESPONSEINFO_H_
#define HTTPRESPONSEINFO_H_
#include "../utility/globalDefine.h"
#include "networkDefine.h"
NAMESPACE_BEGIN(network)

class NETWORK_CLASS CHttpResponseInfo
{
public:
	CHttpResponseInfo();
	~CHttpResponseInfo();

public:
	VOID ParseResponseData(CString strRecvData);
	VOID ParseContentLength();

	CString GetHttpHeader(){ return m_strHeader; }
	CString GetHttpBody(){ return m_strBody; }
	INT32 GetHttpCode(){ return m_i32HttpCode; }
	INT32 GetHttpCententLength(){ return m_i32ContentLength; }
private:
	CString		m_strHeader;					//Http头
	CString		m_strBody;						//Http体
	INT32		m_i32HttpCode;					//Http返回码
	INT32		m_i32ContentLength;				//Http头中Content_length的数据
};
NAMESPACE_END(network)



#endif