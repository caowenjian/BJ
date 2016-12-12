#pragma once
#include <string>
#include <WinSock2.h>

CONST INT32 I32_SOCKET_INVALID_HANDLE = -1;
CONST INT32 I32_SOCKET_ERROR = -1;
CONST INT32 I32_SOCKET_MAX_BUF_SIZE = 128 * 1024;
CONST INT32 I32_SOCKET_MAX_RECV_BUF_SIZE = 128 * 1024;
enum
{
	SOCKET_STATE_IDLE,
	SOCKET_STATE_LISTENING,
	SOCKET_STATE_CONNECTING,
	SOCKET_STATE_CONNECTED,
	SOCKET_STATE_CLOSING
};

struct ICallbackTcpSocket
{
	virtual void onClose() = 0;
	virtual void onReceiveData(const char* data, INT32 size) = 0;
	virtual void onConnectDone() = 0;
	virtual void onReceiveError() = 0;
};

class CSimpleBuffer
{
public:
	CSimpleBuffer();
	~CSimpleBuffer();
	UCHAR*  GetBuffer() { return m_buffer; }
	UINT32 GetAllocSize() { return m_alloc_size; }
	UINT32 GetWriteOffset() { return m_write_offset; }
	void IncWriteOffset(UINT32 len) { m_write_offset += len; }

	void Extend(UINT32 len);
	UINT32 Write(void* buf, UINT32 len);
	UINT32 Read(void* buf, UINT32 len);
private:
	UCHAR*	m_buffer;		//存放数据
	UINT32	m_alloc_size;	//要重新申请的空间大小
	UINT32	m_write_offset; //使用的空间大小
};

class CBaseSocket
{
public:
	CBaseSocket();
	virtual ~CBaseSocket();
public:
	SOCKET Connect(CONST CHAR* strServer_ip, UINT16 ui16Port);
	INT32 SendLoop(VOID* pBuf, INT32 i32Length);

	VOID OnRead();

	INT32 Close();
	VOID OnClose();

	SOCKET GetSocket() { return m_nSocket; }
	VOID SetSocket(SOCKET nSocket) { m_nSocket = nSocket; }
	bool IsBlock(INT32 nErrorCode);
	VOID SetNonblock(SOCKET nSocket);
	VOID SetNoDelay(SOCKET nSocket);
	VOID AddRef();
	VOID ReleaseRef();
private:
	INT32 Send(VOID* pBuf, INT32 i32Length);
	VOID GetAddrStruct(CONST CHAR* ip, CONST UINT16 port, sockaddr_in* pAddr);
private:
	std::string m_strRemoteIP;
	std::string m_strLocalIP;
	UINT16 m_usRemotePort;
	UINT16 m_usLocalPort;
	SOCKET m_nSocket;

	UINT8  m_u8Status;	//Socket״̬
	INT32 m_i32RefCount;

	ICallbackTcpSocket* m_pCallback;
};

