#include "ProxySocket.h"
#include "APINetwork.h"
NAMESPACE_BEGIN(network)

CProxySocket::CProxySocket() :m_bConnected(FALSE)
{

}

CProxySocket::CProxySocket(CONST std::string strHost, UINT16 u16Port):
m_strHost(strHost),
m_u16Port(u16Port),
m_bConnected(FALSE)
{

}

CProxySocket::~CProxySocket()
{
	Close();
}
VOID CProxySocket::SetHostInfo(CONST std::string strHost, UINT16 u16Port)
{
	m_strHost = strHost;
	m_u16Port = u16Port;
}


BOOL CProxySocket::Connect()
{
	m_u32Socket = network::Connect(m_strHost.c_str(), m_u16Port);
	EQUAL_INT_FALSE(m_u32Socket, INVALID_SOCKET)
	m_bConnected = TRUE;
	return TRUE;
// 	ProxyType	proxy_type = _proxy_config._proxy_type;
// 
// 	if (proxy_type == PROXY_NULL)
// 	{
// 		return _socket.connect(_host_name, _port_number);
// 	}
// 	else
// 	{
// 		std::string	host_name = _proxy_config._host_name;
// 		int	port_number = _proxy_config._port_number;
// 		bool connect_proxy = _socket.connect(host_name, port_number);
// 
// 		if (!connect_proxy)
// 		{
// 			return false;
// 		}
// 		else
// 		{
// 			bool connect_host = false;
// 			switch (proxy_type)
// 			{
// 			case PROXY_HTTP:
// 				connect_host = handShakeWithHttpProxy();
// 				break;
// 			case PROXY_SOCK4:
// 				connect_host = handShakeWithSock4Proxy();
// 				break;
// 			case PROXY_SOCK5:
// 				connect_host = handShakeWithSock5Proxy();
// 				break;
// 			default:
// 				assert(false);
// 				break;
// 			}
// 			return connect_host;
// 		}
// 	}
}


VOID CProxySocket::Close()
{
	if (m_bConnected || m_u32Socket != SOCKET_ERROR)
	closesocket(m_u32Socket);
	m_bConnected = FALSE;
	m_strHost = "";
	m_u16Port = 0;
	m_u32Socket = SOCKET_ERROR;
}


INT32 CProxySocket::RecvData(OUT CHAR* pBuf, IN INT32 i32Length)
{
	return m_bConnected ? network::RecvData(m_u32Socket, pBuf, i32Length) : -1;
}



INT32 CProxySocket::SendData(CHAR* pBuf, INT32 i32Length)
{
	return m_bConnected ? network::SendData(m_u32Socket, pBuf, i32Length) : -1;
}
NAMESPACE_END(network)
