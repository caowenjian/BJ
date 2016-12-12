#include "BaseSocket.h"
#include "SocketManager.h"
VOID CallbackSocket(void* callback_data, UINT8 msg, UINT32 handle, void* pParam)
{
	//NOTUSED_ARG(handle);
	//NOTUSED_ARG(pParam);

// 	CImConn* pConn = TcpSocketsManager::getInstance()->get_client_conn(handle);
// 	if (!pConn)
// 	{
// 		//LOG__(NET, _T("connection is invalied:%d"), handle);
// 		return;
// 	}
// 	pConn->AddRef();
// 
// 	//	LOG__(NET,  "msg=%d, handle=%d\n", msg, handle);
// 
// 	switch (msg)
// 	{
// 	case NETLIB_MSG_CONFIRM:
// 		pConn->onConnect();
// 		break;
// 	case NETLIB_MSG_READ:
// 		pConn->OnRead();
// 		break;
// 	case NETLIB_MSG_WRITE:
// 		pConn->OnWrite();
// 		break;
// 	case NETLIB_MSG_CLOSE:
// 		pConn->OnClose();
// 		break;
// 	default:
// 		LOG__(NET, _T("!!!imconn_callback error msg: %d"), msg);
// 		break;
// 	}
// 
// 	pConn->ReleaseRef();
}
CSimpleBuffer::CSimpleBuffer()
{
	m_buffer = NULL;

	m_alloc_size = 0;
	m_write_offset = 0;
}

CSimpleBuffer::~CSimpleBuffer()
{
	m_alloc_size = 0;
	m_write_offset = 0;
	if (m_buffer)
	{
		free(m_buffer);
		m_buffer = NULL;
	}
}

void CSimpleBuffer::Extend(UINT32 len)
{
	m_alloc_size = m_write_offset + len;
	m_alloc_size += m_alloc_size >> 2;	// increase by 1/4 allocate size
	UCHAR* new_buf = (UCHAR*)realloc(m_buffer, m_alloc_size);
	if (new_buf != NULL)
	{
		m_buffer = new_buf;
	}
}

UINT32 CSimpleBuffer::Write(void* buf, UINT32 len)
{
	if (m_write_offset + len > m_alloc_size)
	{
		Extend(len);
	}

	if (buf)
	{
		memcpy(m_buffer + m_write_offset, buf, len);
	}

	m_write_offset += len;

	return len;
}

UINT32 CSimpleBuffer::Read(void* buf, UINT32 len)
{
	if (len > m_write_offset)
		len = m_write_offset;

	if (buf)
		memcpy(buf, m_buffer, len);

	m_write_offset -= len;
	memmove(m_buffer, m_buffer + len, m_write_offset);
	return len;
}


CBaseSocket::CBaseSocket() : m_i32RefCount(1)
{
}


CBaseSocket::~CBaseSocket()
{
}


VOID CBaseSocket::AddRef()
{
	m_i32RefCount++;
}

VOID CBaseSocket::ReleaseRef()
{
	m_i32RefCount--;
	if (m_i32RefCount == 0)
			delete this;
}


/*************************************************
 // Method: IsBlock
 // Description: 判断是否函数被阻塞了。
 // Author: cwj 
 // Date: 2016/03/04
 // Returns: bool
 // Parameter: nErrorCode
 // History:
 *************************************************/
bool CBaseSocket::IsBlock(INT32 nErrorCode)
{
	return ((nErrorCode == WSAEINPROGRESS) || (nErrorCode == WSAEWOULDBLOCK));
}


/*************************************************
 // Method: SetNonblock
 // Description: 设置套接字为非阻塞模式
 // Author: cwj 
 // Date: 2016/03/04
 // Returns: VOID
 // Parameter: nSocket
 // History:
 *************************************************/
VOID CBaseSocket::SetNonblock(SOCKET nSocket)
{
	u_long nonblock = 1;
	int ret = ioctlsocket(nSocket, FIONBIO, &nonblock);

	if (ret == SOCKET_ERROR)
	{
		
	}
}

/*************************************************
 // Method: SetNoDelay
 // Description: 提升发送数据性能
 // Author: cwj 
 // Date: 2016/03/09
 // Returns: VOID
 // Parameter: nSocket
 // History:
 *************************************************/
VOID CBaseSocket::SetNoDelay(SOCKET nSocket)
{
	BOOL nodelay = TRUE;
	int ret = setsockopt(nSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));
	if (ret == SOCKET_ERROR)
	{
		
	}
}


VOID CBaseSocket::GetAddrStruct(CONST CHAR* ip, CONST UINT16 port, sockaddr_in* pAddr)
{
	memset(pAddr, 0, sizeof(sockaddr_in));
	pAddr->sin_family = AF_INET;
	pAddr->sin_port = htons(port);
	pAddr->sin_addr.s_addr = inet_addr(ip);
	if (pAddr->sin_addr.s_addr == INADDR_NONE)
	{
		hostent* host = gethostbyname(ip);
		if (host == NULL)
		{
			//LOGA__(NET, "gethostbyname failed, ip=%s", ip);
			return;
		}

		pAddr->sin_addr.s_addr = *(UINT32*)host->h_addr;
	}
}


SOCKET CBaseSocket::Connect(CONST CHAR* strServer_ip, UINT16 ui16Port)
{
	m_strRemoteIP = strServer_ip;
	m_usRemotePort = ui16Port;


	m_nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_nSocket == INVALID_SOCKET)
	{
		return I32_SOCKET_INVALID_HANDLE;
	}

	SetNonblock(m_nSocket);
	SetNoDelay(m_nSocket);

	sockaddr_in serv_addr;
	GetAddrStruct(strServer_ip, ui16Port, &serv_addr);
	int ret = connect(m_nSocket, (sockaddr*)&serv_addr, sizeof(serv_addr));
	if ((ret == SOCKET_ERROR) && (!IsBlock(WSAGetLastError())))
	{
		closesocket(m_nSocket);
		return I32_SOCKET_INVALID_HANDLE;
	}

	m_u8Status = SOCKET_STATE_CONNECTING;
	CSocketManager::GetInstance().AddEvent(m_nSocket, SOCKET_ALL);
	CSocketManager::GetInstance().AddBaseSocket(this);
	return m_nSocket;
}

INT32 CBaseSocket::Send(VOID* pBuf, INT32 i32Length)
{
	if (m_u8Status != SOCKET_STATE_CONNECTED)
		return I32_SOCKET_ERROR;

	int ret = send(m_nSocket, (char*)pBuf, i32Length, 0);
	if (ret == SOCKET_ERROR)
	{
		int err_code = WSAGetLastError();
		if (IsBlock(err_code))
		{
			//CEventDispatch::Instance()->AddEvent(m_socket, SOCKET_WRITE);
			ret = 0;
		}
		else
		{
			//LOG__(NET, _T("!!!send failed, error code: %d"), err_code);
		}
	}
	else
	{
		//LOGBIN_F__(SOCK, "Send", buf, len);
	}

	return ret;
}


INT32 CBaseSocket::SendLoop(VOID* pBuf, INT32 i32Length)
{
	int offset = 0;
	INT32 i32Remain = i32Length;
	while (i32Remain > 0) {
		int send_size = i32Remain;
		if (send_size > I32_SOCKET_MAX_BUF_SIZE) {
			send_size = I32_SOCKET_MAX_BUF_SIZE;
		}

		int ret = Send((char*)pBuf + offset, send_size);
		if (ret <= 0) {
			ret = 0;
			break;
		}

		offset += ret;
		i32Remain -= ret;
	}
	return i32Length;
}


VOID CBaseSocket::OnRead()
{
	if (m_u8Status == SOCKET_STATE_LISTENING)
	{
		//_AcceptNewSocket();
	}
	else
	{
		u_long avail = 0;

		if ((ioctlsocket(m_nSocket, FIONREAD, &avail) == SOCKET_ERROR) || (avail == 0))
		{
			OnClose();
		}
		else
		{
			while (true)
			{
// 				uint32_t free_buf_len = m_in_buf.GetAllocSize() - m_in_buf.GetWriteOffset();
// 				if (free_buf_len < I32_SOCKET_MAX_RECV_BUF_SIZE)
// 					m_in_buf.Extend(I32_SOCKET_MAX_RECV_BUF_SIZE);

// 				int ret = recv(m_nSocket, m_in_buf.GetBuffer() + m_in_buf.GetWriteOffset(), I32_SOCKET_MAX_RECV_BUF_SIZE, 0);
// 				if (ret <= 0)
// 					break;

// 				m_in_buf.IncWriteOffset(ret);
// 				while (m_in_buf.GetWriteOffset() >= imcore::HEADER_LENGTH)
// 				{
// 					uint32_t len = m_in_buf.GetWriteOffset();
// 					uint32_t length = CByteStream::ReadUint32(m_in_buf.GetBuffer());
// 					if (length > len)
// 						break;
// 
// 					try
// 					{
// 						imcore::FXPBHeader pbHeader;
// 						pbHeader.unSerialize((byte*)m_in_buf.GetBuffer(), imcore::HEADER_LENGTH);
// 						//LOG__(NET, _T("OnRead moduleId:0x%x,commandId:0x%x"), pbHeader.getModuleId(), pbHeader.getCommandId());
// 						if (m_pCallback)
// 							m_pCallback->onReceiveData((const char*)m_in_buf.GetBuffer(), length);
// 						//LOGBIN_F__(SOCK, "OnRead", m_in_buf.GetBuffer(), length);
// 					}
// 					catch (std::exception& ex)
// 					{
// 						//assert(FALSE);
// 						//LOGA__(NET, "std::exception,info:%s", ex.what());
// 						if (m_pCallback)
// 							m_pCallback->onReceiveError();
// 					}
// 					catch (...)
// 					{
// 						//assert(FALSE);
// 						//LOG__(NET, _T("unknown exception"));
// 						if (m_pCallback)
// 							m_pCallback->onReceiveError();
// 					}
// 					m_in_buf.Read(NULL, length);
// 				}
			}
		}
	}
}

INT32 CBaseSocket::Close()
{
	
	CSocketManager::GetInstance().RemoveEvent(m_nSocket, SOCKET_ALL);
	CSocketManager::GetInstance().RemoveBaseSocket(this);
	closesocket(m_nSocket);
	ReleaseRef();

	return 0;
}


VOID CBaseSocket::OnClose()
{
	m_u8Status = SOCKET_STATE_CLOSING;
	if (m_pCallback)
	m_pCallback->onClose();
}