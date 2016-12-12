#pragma once
#include <map>
#include "BaseSocket.h"

typedef std::map<SOCKET, CBaseSocket*> MapBaseSocket;
enum {
	SOCKET_READ = 0x1,
	SOCKET_WRITE = 0x2,
	SOCKET_EXCEP = 0x4,
	SOCKET_ALL = 0x7
};
class CSocketManager
{
public:
	CSocketManager();
	virtual ~CSocketManager();

	static CSocketManager& GetInstance() { static CSocketManager instance; return instance; }
public:
	VOID AddEvent(SOCKET fd, UINT8 socket_event);
	VOID RemoveEvent(SOCKET fd, UINT8 socket_event);
	VOID StartEvent();


	VOID AddBaseSocket(CBaseSocket*);
	VOID RemoveBaseSocket(CBaseSocket*);
	CBaseSocket* FindBaseSocket(SOCKET nSocket);
private:
	fd_set m_tagRead_set, m_tagWrite_set, m_tagExcep_set;  //��ŷ����¼��Ķ���д���쳣�׽��ּ���
	BOOL m_bEvenRun;			//�¼��Ƿ�����
	MapBaseSocket m_mapSocket;
	
};

