#include "APINetwork.h"
#include "../utility/APISrcCoding.h"
NAMESPACE_BEGIN(network)

BOOL InitWinSocket()
{
	static BOOL initialization = false;
	if (!initialization)
	{
		WSADATA wsd;
		initialization = (WSAStartup(MAKEWORD(1, 1), &wsd) == 0);
	}
	return initialization;
}

BOOL DestoryWinSocket()
{
	return !WSACleanup();
}


BOOL SetSocketBlock(SOCKET i32Socket, BOOL bBlock)
{
	u_long nonBlocking = !bBlock;
	return  (ioctlsocket(i32Socket, FIONBIO, &nonBlocking) == 0);
}


BOOL SetSocketNagle(SOCKET nSocket, BOOL bNagle)
{
	BOOL nodelay = !bNagle;
	return (setsockopt(nSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay)) == 0);
}



BOOL SetSocketReuse(SOCKET nSocket, BOOL bReuse)
{
	BOOL reuse = bReuse;
	return (setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) == 0);
}


BOOL GetAddrStruct(CONST CHAR* ip, CONST UINT16 port, sockaddr_in* pAddr)
{
// 	memset(pAddr, 0, sizeof(sockaddr_in));
// 	pAddr->sin_family = AF_INET;
// 	pAddr->sin_port = htons(port);
// 	pAddr->sin_addr.s_addr = inet_addr(ip);
// 	if (pAddr->sin_addr.s_addr == INADDR_NONE)
// 	{
// 		hostent* host = gethostbyname(ip);
// 		if (host == NULL)
// 		{
// 			//LOGA__(NET, "gethostbyname failed, ip=%s", ip);
// 			return;
// 		}
// 
// 		pAddr->sin_addr.s_addr = *(UINT32*)host->h_addr;
// 	}

	struct hostent* const host_ent = gethostbyname(ip);

	if (host_ent == 0)
		return FALSE;
	memset(pAddr, 0, sizeof(sockaddr_in));
	struct in_addr target_address;
	memcpy(&target_address.s_addr, *(host_ent->h_addr_list), sizeof(target_address.s_addr));

	pAddr->sin_family = PF_INET;
	pAddr->sin_addr = target_address;
	pAddr->sin_port = htons((u_short)port);
	return TRUE;
}


BOOL IsBlockError()
{
	INT32 nErrorCode = WSAGetLastError();
	return ((nErrorCode == WSAEINPROGRESS) || (nErrorCode == WSAEWOULDBLOCK));
}


SOCKET Connect(IN CONST CHAR* strServerip, UINT16 u16Port, UINT32 u32Timeout /*= 10000*/)
{
	sockaddr_in serv_addr;
	if (!GetAddrStruct(strServerip, u16Port, &serv_addr))
	{
		return INVALID_SOCKET;
	}
	SOCKET nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nSocket == INVALID_SOCKET)
	{
		return nSocket;
	}

	SetSocketBlock(nSocket, FALSE);

	int ret = connect(nSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if ((ret == SOCKET_ERROR) && (!IsBlockError())) //若不是阻塞错误则返回立马返回失败
	{
		closesocket(nSocket);
		return INVALID_SOCKET;
	}
	//等待连接超时
	INT nCount = u32Timeout / 1000 + 1; //超时分片， 在超时范围内取消。
	for (int i = 0; i < nCount; i++)
	{
		fd_set tagWfd;
		FD_ZERO(&tagWfd);
		FD_SET(nSocket, &tagWfd);
		timeval timeout = { 1, 0 };
		if (select(0, NULL, &tagWfd, NULL, &timeout) < 0)
		{
			closesocket(nSocket);
			return INVALID_SOCKET;
		}
		int opt = 0;
		int len = 4;
		if (getsockopt(nSocket, SOL_SOCKET, SO_ERROR, (char*)&opt, &len) < 0 || opt != 0)
		{
			closesocket(nSocket);
			return INVALID_SOCKET;
		}
		if (FD_ISSET(nSocket, &tagWfd))
		{
			SetSocketBlock(nSocket, TRUE);
			return nSocket;
		}
// 		if (Http::g_bCancelConnect) 用来取消本次连接
// 		{
// 			return 0;
// 		}
	}
	closesocket(nSocket);
	return INVALID_SOCKET;
}


INT32 SendData(SOCKET nSocket, CHAR* pBuf, INT32 i32Length)
{
	int offset = 0;
	INT32 i32Remain = i32Length;
	while (i32Remain > 0) {
		int send_size = i32Remain;
		if (send_size > I32_SOCKET_MAX_SEND_BUF_SIZE) {
			send_size = I32_SOCKET_MAX_SEND_BUF_SIZE;
		}

		int ret = send(nSocket, (char*)pBuf + offset, send_size, 0);
		if (ret <= 0) {
			ret = 0;
			break;
		}

		offset += ret;
		i32Remain -= ret;
	}
	return offset;
}


INT32 RecvData(SOCKET nSocket, CHAR* pBuf, INT32 i32Length, BOOL bIsAllRecv/* = TRUE*/)
{

	INT32 bytes_read = 0; //已读取数据量

	while (bytes_read < i32Length)
	{
		int bytes_this_time;

		bytes_this_time = recv(nSocket, pBuf + bytes_read, i32Length - bytes_read, 0);

		if (bytes_this_time <= 0)
		{
			if (bytes_read == 0)
				bytes_read = -1;
			break;
		}

		bytes_read += bytes_this_time;

		if (!bIsAllRecv)
			break;

	}

	return bytes_read;
}



SOCKET Listen(IN CONST CHAR* strServerip, UINT16 u16Port)
{
	SOCKET nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nSocket == INVALID_SOCKET)
	{
		return 0;
	}

	SetSocketReuse(nSocket, TRUE);
	SetSocketBlock(nSocket, FALSE);

	sockaddr_in serv_addr;
	GetAddrStruct(strServerip, u16Port, &serv_addr);
	int ret = ::bind(nSocket, (sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret == SOCKET_ERROR)
	{
		closesocket(nSocket);
		return 0;
	}

	ret = listen(nSocket, 64);
	if (ret == SOCKET_ERROR)
	{
		closesocket(nSocket);
		return 0;
	}
	return nSocket;
}


BOOL URLParse(IN CONST CString strURL, OUT CString& strHost, OUT UINT16& u16Port, OUT CString& strObjectData)
{
	size_t	length = strURL.GetLength();
	if (length < 6)	//过短的URL可以认为是无效的
	{
		return FALSE;
	}
	else
	{
		CString	protocal = strURL.Left(7);
		CString	format_url = strURL;
		if (protocal == _T("http://"))
		{
			format_url = format_url.Mid(7, length - 7);
		}
		INT32 spliPos = format_url.Find('/');
		//获取请求数据
		if (spliPos > 0 && spliPos != format_url.GetLength() - 1)
		{
			strObjectData = format_url.Right(format_url.GetLength()-spliPos);
			format_url = format_url.Left(spliPos);
		}

		spliPos = format_url.Find(':');
		if (spliPos == -1)
		{
			strHost = format_url;
		}
		else
		{
			strHost = format_url.Left(spliPos);
			u16Port = utility::CStringToInt32(format_url.Right(format_url.GetLength() - spliPos - 1));
		}
		
		//splitURL(format_url);
	}
	return TRUE;
}
NAMESPACE_END(network)

