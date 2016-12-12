#include "SocketManager.h"
CONST INT32 I32_EVENT_LOOP_MIN_TIME = 100; //事件循环最小时间

CSocketManager::CSocketManager()
{
}


CSocketManager::~CSocketManager()
{
}


VOID CSocketManager::AddBaseSocket(CBaseSocket* pSocket)
{
	m_mapSocket.insert(std::pair<SOCKET, CBaseSocket*>(pSocket->GetSocket(), pSocket));
}

VOID CSocketManager::RemoveBaseSocket(CBaseSocket* pSocket)
{
	m_mapSocket.erase(pSocket->GetSocket());
}

CBaseSocket* CSocketManager::FindBaseSocket(SOCKET nSocket)
{
	CBaseSocket* pSocket = NULL;

	MapBaseSocket::iterator Itmap = m_mapSocket.find(nSocket);
	if (Itmap != m_mapSocket.end())
	{
		pSocket = Itmap->second;
		pSocket->AddRef();
	}
	return pSocket;
}

VOID CSocketManager::AddEvent(SOCKET fd, UINT8 socket_event)
{
	//CAutoLock func_lock(&m_lock);

	if ((socket_event & SOCKET_READ) != 0)
	{
		FD_SET(fd, &m_tagRead_set);
	}

	if ((socket_event & SOCKET_WRITE) != 0)
	{
		FD_SET(fd, &m_tagWrite_set);
	}

	if ((socket_event & SOCKET_EXCEP) != 0)
	{
		FD_SET(fd, &m_tagExcep_set);
	}
}

VOID CSocketManager::RemoveEvent(SOCKET fd, UINT8 socket_event)
{
	//CAutoLock func_lock(&m_lock);

	if ((socket_event & SOCKET_READ) != 0)
	{
		FD_CLR(fd, &m_tagRead_set);
	}

	if ((socket_event & SOCKET_WRITE) != 0)
	{
		FD_CLR(fd, &m_tagWrite_set);
	}

	if ((socket_event & SOCKET_EXCEP) != 0)
	{
		FD_CLR(fd, &m_tagExcep_set);
	}
}

/*************************************************
 // Method: StartEvent
 // Description: 实时检测Socket并响应分发出去
 // Author: cwj 
 // Date: 2016/03/10
 // Returns: VOID
 // History:
 *************************************************/
VOID CSocketManager::StartEvent()
{
	fd_set read_set, write_set, excep_set;
	timeval timeout;
	timeout.tv_sec = 1;	//wait_timeout 1 second
	timeout.tv_usec = 0;

	while (m_bEvenRun)
	{
		//_CheckTimer();
		//_CheckLoop();

		if (!m_tagRead_set.fd_count && !m_tagWrite_set.fd_count && !m_tagExcep_set.fd_count)
		{
			Sleep(I32_EVENT_LOOP_MIN_TIME);
			continue;
		}

		//m_lock.lock();
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_ZERO(&excep_set);
		memcpy(&read_set, &m_tagRead_set, sizeof(fd_set));
		memcpy(&write_set, &m_tagWrite_set, sizeof(fd_set));
		memcpy(&excep_set, &m_tagExcep_set, sizeof(fd_set));
		//m_lock.unlock();

		if (!m_bEvenRun)
			break;

		//for (int i = 0; i < read_set.fd_count; i++) {
		//	LOG__(NET,  "read fd: %d\n", read_set.fd_array[i]);
		//}
		int nfds = select(0, &read_set, &write_set, &excep_set, &timeout);
		if (nfds == SOCKET_ERROR)
		{
			//LOG__(NET,  "select failed, error code: %d\n", GetLastError());
			Sleep(I32_EVENT_LOOP_MIN_TIME);
			continue;			// select again
		}
		if (nfds == 0)
		{
			continue;
		}
		for (u_int i = 0; i < read_set.fd_count; i++)
		{
			//LOG__(NET,  "select return read count=%d\n", read_set.fd_count);
			SOCKET fd = read_set.fd_array[i];
			CBaseSocket* pSocket = FindBaseSocket(fd);
			if (pSocket)
			{
				pSocket->OnRead();
				pSocket->ReleaseRef();
			}
		}
		for (u_int i = 0; i < write_set.fd_count; i++)
		{
			//LOG__(NET,  "select return write count=%d\n", write_set.fd_count);
			SOCKET fd = write_set.fd_array[i];
			CBaseSocket* pSocket = FindBaseSocket(fd);
			if (pSocket)
			{
				//pSocket->OnWrite();
				pSocket->ReleaseRef();
			}
		}
		for (u_int i = 0; i < excep_set.fd_count; i++)
		{
			SOCKET fd = excep_set.fd_array[i];
			CBaseSocket* pSocket = FindBaseSocket(fd);
			if (pSocket)
			{
				pSocket->OnClose();
				pSocket->ReleaseRef();
			}
		}
	}
}