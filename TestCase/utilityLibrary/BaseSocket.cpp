#include "BaseSocket.h"
#include "Encryption.h"

CBaseSocket::CBaseSocket()
{

}
CBaseSocket::~CBaseSocket()
{

}

VTT_SOCKET CBaseSocket::Connect(const VTT_CHAR* pServer, const VTT_UINT16 u16ServerPort,  VTT_CHAR* pLocal /*= NULL*/,  VTT_UINT16 u16LocalPort/* = 0*/)
{
	m_strRemoteIP = pServer;
	m_usRemotePort = u16ServerPort;


	m_nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_nSocket == INVALID_SOCKET)
	{
		return I32_SOCKET_INVALID_HANDLE;
	}

	SetNonblock(m_nSocket);
	SetNoDelay(m_nSocket);

	//对本地端口进行绑定
	if ((pLocal != NULL) && (u16LocalPort != 0))
	{
		sockaddr_in serv_addr;
		GetAddrStruct(pLocal, u16LocalPort, &serv_addr);
		int ret = ::bind(m_nSocket, (sockaddr*)&serv_addr, sizeof(serv_addr));
		if (ret == SOCKET_ERROR)
		{
			closesocket(m_nSocket);
			return I32_SOCKET_INVALID_HANDLE;
		}
	}
	

	sockaddr_in serv_addr;
	GetAddrStruct(pServer, u16ServerPort, &serv_addr);
	int ret = connect(m_nSocket, (sockaddr*)&serv_addr, sizeof(serv_addr));
	if ((ret == SOCKET_ERROR) && (!IsBlock(WSAGetLastError())))
	{
		closesocket(m_nSocket);
		return I32_SOCKET_INVALID_HANDLE;
	}


	m_u8Status = SOCKET_STATE_CONNECTING;
	return m_nSocket;
}
VTT_BOOL CBaseSocket::ConnectDone()
{
	int error = 0;
	int len = sizeof(error);
	getsockopt(m_nSocket, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
	if (error) 
	{
		return false;
	} 
	else 
	{
		m_u8Status = SOCKET_STATE_CONNECTED;
		
		sockaddr_in pLocal1;
		int len = sizeof(sockaddr_in);
		if(getsockname(m_nSocket, (sockaddr*)&pLocal1, &len))
		{
			return false;
		}
		//获取本地地址
		m_strLocalIP = inet_ntoa(pLocal1.sin_addr);
		m_usLocalPort = ntohs(pLocal1.sin_port);
		/*std::string  ssa = "abc:1223";
		std::string aa;
		utilityLibrary::Base64Encode(ssa, aa);
		int i = 0;*/
	}
	return true;
}

VTT_VOID  CBaseSocket::CloseSocket()
{
	m_u8Status = SOCKET_STATE_CLOSING;
	closesocket(m_nSocket);
}


VTT_INT32 CBaseSocket::Send(VTT_VOID* pBuf, VTT_INT32 i32Length)
{
	if (m_u8Status != SOCKET_STATE_CONNECTED)
		return I32_SOCKET_ERROR;
	if (m_busy)
	{
		m_out_buf.Write(pBuf, i32Length);
		return i32Length;
	}

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

	if (i32Remain > 0)
	{
		m_out_buf.Write((char*)pBuf + offset, i32Remain);
		m_busy = true;
		LOG__(NET,  _T("send busy, remain=%d"), m_out_buf.GetWriteOffset());
	}
	return i32Length;
}
//************************************
// Method:    GetAddrStruct
// FullName:  CBaseSocket::GetAddrStruct
// Author:    cwj
// Date:      2016/12/21
// Returns:   VTT_BOOL
// Parameter: const VTT_CHAR * ip : IP和域名
// Parameter: const VTT_UINT16 port : 端口
// Parameter: sockaddr_in * pAddr :返回的地址结构
//************************************
VTT_BOOL CBaseSocket::GetAddrStruct(const VTT_CHAR* ip, const VTT_UINT16 port, sockaddr_in* pAddr)
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
			return false;
		}

		pAddr->sin_addr.s_addr = *(UINT32*)host->h_addr;
	}
	return true;
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
VTT_BOOL CBaseSocket::IsBlock(VTT_INT32 nErrorCode)
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

VTT_VOID CBaseSocket::SetNonblock(VTT_SOCKET nSocket)
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

VTT_VOID CBaseSocket::SetNoDelay(VTT_SOCKET nSocket)
{
	VTT_BOOL nodelay = TRUE;
	int ret = setsockopt(nSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));
	if (ret == SOCKET_ERROR)
	{
		
	}
}