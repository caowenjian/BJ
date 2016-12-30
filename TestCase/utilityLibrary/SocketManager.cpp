#include "SocketManager.h"
#include "ISocketManager.h"
#include "BaseSocket.h"
#define MIN_TIMER_DURATION	100	// miliseconds
CSocketManager::CSocketManager()
{
	m_bSelectRun = true;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{WSACleanup();} 
}
CSocketManager::~CSocketManager()
{

}


VTT_BOOL CSocketManager::Connect(const VTT_CHAR* pServer, const VTT_UINT16 u16Port)
{
	CBaseSocket* pSocket = new CBaseSocket();
	if (!pSocket)
		return false;
	if (I32_SOCKET_INVALID_HANDLE == pSocket->Connect(pServer, u16Port, (VTT_CHAR*)pServer, 5000))
	{
		return false;
	}
	AddEvent(pSocket->GetSocket(), SOCKET_ALL); //监听这个连接套接字所有事件
	AddBaseSocket(pSocket);
	return true;
}


VTT_VOID CSocketManager::StartSelectLoop()
{
	m_bSelectRun = true;
	fd_set read_set, write_set, excep_set;
	timeval timeout;
	timeout.tv_sec = 1;	//wait_timeout 1 second
	timeout.tv_usec = 0;


	while (m_bSelectRun)
	{

		if (!m_read_set.fd_count && !m_write_set.fd_count && !m_excep_set.fd_count)
		{
			Sleep(MIN_TIMER_DURATION);
			continue;
		}

		m_lock.Lock();
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_ZERO(&excep_set);
		memcpy(&read_set, &m_read_set, sizeof(fd_set));
		memcpy(&write_set, &m_write_set, sizeof(fd_set));
		memcpy(&excep_set, &m_excep_set, sizeof(fd_set));
		m_lock.Unlock();

		if (!m_bSelectRun)
			break;

		int nfds = select(0, &read_set, &write_set, &excep_set, &timeout);
		if (nfds == SOCKET_ERROR)
		{
			Sleep(MIN_TIMER_DURATION);
			continue;			// select again
		}
		if (nfds == 0)
		{
			continue;
		}
		for (u_int i = 0; i < read_set.fd_count; i++)
		{
			EventRead(read_set.fd_array[i]);
		}
		for (u_int i = 0; i < write_set.fd_count; i++)
		{
			EventWrite(write_set.fd_array[i]);
		}
		for (u_int i = 0; i < excep_set.fd_count; i++)
		{
			EventExcept(excep_set.fd_array[i]);
		}
	}
}

VTT_VOID CSocketManager::EndSelectLoop()
{
	m_bSelectRun = false;
}

CBaseSocket* CSocketManager::FindBaseSocket(VTT_SOCKET nSocket)
{
	CBaseSocket* pSocket = NULL;
	m_lock.Lock();
	MapBaseSocket::iterator Itmap = m_mapSocket.find(nSocket);
	if (Itmap != m_mapSocket.end())
	{
		pSocket = Itmap->second;
	}
	m_lock.Unlock();
	return pSocket;
}

VTT_VOID CSocketManager::EventWrite(VTT_SOCKET nSocket)
{
	CBaseSocket* pSocket = FindBaseSocket(nSocket);
	JUDGE_PTR_VOID(pSocket)
	//移除写事件
	RemoveEvent(pSocket->GetSocket(), SOCKET_WRITE);
	//获取此时套接字状态
	if (pSocket->GetSocketStatus() == SOCKET_STATE_CONNECTING)
	{
		if (!pSocket->ConnectDone())
		{
			//关闭套接字
			pSocket->CloseSocket();
			//移除该套接字事件
			RemoveEvent(pSocket->GetSocket(), SOCKET_ALL);
			//移除套接字对象
			RemoveBaseSocket(pSocket);
			//删除套接字指针
			SAFE_DELETE_PTR(pSocket)
			return;
		}
		else
		{
			//回调函数
		}
	}
	else
	{

	}
}
VTT_VOID CSocketManager::EventRead(VTT_SOCKET nSocket)
{

}
VTT_VOID CSocketManager::EventExcept(VTT_SOCKET nSocket)
{

}

VTT_VOID CSocketManager::AddEvent(VTT_SOCKET nSocket, VTT_UINT8 socket_event)
{
	m_lock.Lock();
	if ((socket_event & SOCKET_READ) != 0)
	{
		FD_SET(nSocket, &m_read_set);
	}

	if ((socket_event & SOCKET_WRITE) != 0)
	{
		FD_SET(nSocket, &m_write_set);
	}

	if ((socket_event & SOCKET_EXCEP) != 0)
	{
		FD_SET(nSocket, &m_excep_set);
	}
	m_lock.Unlock();
}

VTT_VOID CSocketManager::RemoveEvent(VTT_SOCKET nSocket, VTT_UINT8 socket_event)
{
	m_lock.Lock();
	if ((socket_event & SOCKET_READ) != 0)
	{
		FD_CLR(nSocket, &m_read_set);
	}

	if ((socket_event & SOCKET_WRITE) != 0)
	{
		FD_CLR(nSocket, &m_write_set);
	}

	if ((socket_event & SOCKET_EXCEP) != 0)
	{
		FD_CLR(nSocket, &m_excep_set);
	}
	m_lock.Unlock();
}

VTT_VOID CSocketManager::AddBaseSocket(CBaseSocket* pSocket)
{
	m_lock.Lock();
	m_mapSocket.insert(std::pair<VTT_SOCKET, CBaseSocket*>(pSocket->GetSocket(), pSocket));
	m_lock.Unlock();
}

VTT_VOID CSocketManager::RemoveBaseSocket(CBaseSocket* pSocket)
{
	m_lock.Lock();
 	m_mapSocket.erase(pSocket->GetSocket());
	m_lock.Unlock();

}