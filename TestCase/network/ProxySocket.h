#ifndef PROXYSOCKET_H_
#define PROXYSOCKET_H_
#include "../utility/globalDefine.h"
#include "networkDefine.h"
NAMESPACE_BEGIN(network)

//֧�ִ����Socket���װ
class NETWORK_CLASS CProxySocket
{
public:
	CProxySocket();
	CProxySocket(CONST std::string strHost, UINT16 u16Port);
	~CProxySocket();
public:
	VOID SetHostInfo(CONST std::string strHost, UINT16 u16Port);
	BOOL Connect();
	VOID Close();
	INT32 RecvData(OUT CHAR* pBuf, IN INT32 i32Length);
	INT32 SendData(CHAR* pBuf, INT32 i32Length);
	BOOL IsConnected(){ return m_bConnected; }
public:
	std::string			m_strHost;		//������IP
	UINT16				m_u16Port;		//�������˿�
	SOCKET				m_u32Socket;	//�׽���
	BOOL				m_bConnected;	//�Ƿ�����
};


NAMESPACE_END(network)
#endif