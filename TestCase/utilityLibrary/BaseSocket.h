#ifndef _BASESOCKET_H
#define _BASESOCKET_H

#include "globalDefine.h"
#include "StringOperator.h"
const VTT_INT32 I32_SOCKET_INVALID_HANDLE = -1;
const VTT_INT32 I32_SOCKET_ERROR = -1;
//��ǰ�׽�������״̬
enum
{
	SOCKET_STATE_IDLE,       //����
	SOCKET_STATE_LISTENING,  //������
	SOCKET_STATE_CONNECTING, //������
	SOCKET_STATE_CONNECTED,   //�������
	SOCKET_STATE_CLOSING     //�رա�
};
CONST INT32 I32_SOCKET_MAX_BUF_SIZE = 128 * 1024;
class CBaseSocket
{
public:
	CBaseSocket();
	virtual ~CBaseSocket();
public:
	VTT_SOCKET GetSocket(){return m_nSocket;}
	VTT_SOCKET GetSocketStatus(){return m_u8Status;}
	VTT_SOCKET Connect(const VTT_CHAR* pServer, const VTT_UINT16 u16ServerPort,  VTT_CHAR* pLocal = NULL,  VTT_UINT16 u16LocalPort = 0);
	VTT_BOOL   ConnectDone();
	VTT_VOID   CloseSocket();

	VTT_INT32 Send(VTT_VOID* pBuf, VTT_INT32 i32Length);
private:
	VTT_BOOL GetAddrStruct(const VTT_CHAR* ip, const VTT_UINT16 port, sockaddr_in* pAddr);
	VTT_BOOL IsBlock(VTT_INT32 nErrorCode);
	VTT_VOID SetNonblock(VTT_SOCKET nSocket);
	VTT_VOID SetNoDelay(VTT_SOCKET nSocket);
private:
	VTT_SOCKET m_nSocket;  //�׽���
	std::string m_strRemoteIP;
	std::string m_strLocalIP;
	VTT_UINT16 m_usRemotePort;
	VTT_UINT16 m_usLocalPort;
	BOOL  m_busy;
	UINT8  m_u8Status;
	utilityLibrary::CSimpleBuffer	m_in_buf,m_out_buf;
};
#endif