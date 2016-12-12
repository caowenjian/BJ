#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_
#include "../utility/globalDefine.h"
#include "networkDefine.h"
#include "../utility/APIOther.h"
NAMESPACE_BEGIN(network)
//Http���������
enum	HTTPERROR
{
	HTTPERROR_SUCCESS,		//��ȷ
	HTTPERROR_INVALID,		//HTTP�Ѿ�������
	HTTPERROR_CONNECT,		//���ӳ���
	HTTPERROR_TRANSPORT,	//����ʧ��
	HTTPERROR_IO,			//IO����
	HTTPERROR_PARAMETER		//��Ч����
};

CONST UINT32 C_U32BUFFER_SIZE = 1024 * 10; //�ϴ����ػ�������С
//������Ȼص�
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
	CString m_strHost;				//��������
	CString m_strRequestObject;		//�������
	UINT16  m_u16Port;				//����˿�

	CHttpRequestInfo*  m_pRequestInfo;					//������Ϣ����
	CHttpResponseInfo* m_pResponseInfo;					//��Ӧ��Ϣ����
	IProgressDelegate*	m_pProgressDelegate;			//Http������ȵ�ί��
	UINT8	m_u8ErrorCode;	//������

	CProxySocket*	m_proxySocket;

	utility::CLock	m_lock;
};


NAMESPACE_END(network)
#endif