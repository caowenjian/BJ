#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_
#include "../utility/globalDefine.h"
#include "networkDefine.h"
#include "../utility/APIOther.h"
NAMESPACE_BEGIN(network)
//Http传输错误码
enum	HTTPERROR
{
	HTTPERROR_SUCCESS,		//正确
	HTTPERROR_INVALID,		//HTTP已经被弃用
	HTTPERROR_CONNECT,		//连接出错
	HTTPERROR_TRANSPORT,	//传输失败
	HTTPERROR_IO,			//IO错误
	HTTPERROR_PARAMETER		//无效参数
};

CONST UINT32 C_U32BUFFER_SIZE = 1024 * 10; //上传下载缓冲区大小
//传输进度回调
class	IProgressDelegate
{
public:
	virtual	void	dataWriteProgress(int write_length, int total_length) = 0;
	virtual	void	dataReadProgress(int read_length, int total_length) = 0;
	virtual	~IProgressDelegate() {}
};

class CProxySocket;
class CHttpRequestInfo;
class CHttpResponseInfo;
class NETWORK_CLASS CHttpClient
{
public:
	CHttpClient();
	~CHttpClient();
public:
	BOOL SendRequestInfo(CHttpRequestInfo* pRequestInfo, CHttpResponseInfo* pResponseInfo);
	VOID SetProgressDelegate(IProgressDelegate* pDelegate){ m_pProgressDelegate = pDelegate; }
	UINT8 GetErrorCode();
	VOID KillSelf();
private:
	BOOL SendHttpGet();
	BOOL SendHttpPost();
	BOOL RecvHttpData();
	BOOL UploadPostFile();
	BOOL UploadFile(CString strLocalFilePath);
	BOOL SendHttpHeader();
	BOOL SendHttpBody();
	VOID SetErrorCode(UINT8 u8ErrorCode);
private:
	CString m_strHost;				//请求主机
	CString m_strRequestObject;		//请求对象
	UINT16  m_u16Port;				//请求端口

	CHttpRequestInfo*  m_pRequestInfo;					//请求信息数据
	CHttpResponseInfo* m_pResponseInfo;					//响应信息数据
	IProgressDelegate*	m_pProgressDelegate;			//Http传输进度的委托
	UINT8	m_u8ErrorCode;	//错误码

	CProxySocket*	m_proxySocket;

	utility::CLock	m_lock;
};


NAMESPACE_END(network)
#endif