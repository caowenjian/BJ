#ifndef _SOCKETMANAGER_H
#define _SOCKETMANAGER_H
#include "ISocketManager.h"
#include "AutoLock.h"
enum {
	SOCKET_READ = 0x1,
	SOCKET_WRITE = 0x2,
	SOCKET_EXCEP = 0x4,
	SOCKET_ALL = 0x7
};
class CBaseSocket;
typedef std::map<SOCKET, CBaseSocket*> MapBaseSocket;
class CSocketManager : public utilityLibrary::ISocketManager
{
public:
	CSocketManager();
  virtual ~CSocketManager();
public:
	virtual VTT_VOID StartSelectLoop(); 
	virtual VTT_VOID EndSelectLoop();
	virtual VTT_BOOL Connect(const VTT_CHAR* pServer, const VTT_UINT16 u16Port);
private:
	CBaseSocket* FindBaseSocket(VTT_SOCKET nSocket);
	VTT_VOID AddBaseSocket(CBaseSocket*);
	VTT_VOID RemoveBaseSocket(CBaseSocket*);
	VTT_VOID AddEvent(VTT_SOCKET nSocket, VTT_UINT8 socket_event);
	VTT_VOID RemoveEvent(VTT_SOCKET nSocket, VTT_UINT8 socket_event);
	VTT_VOID EventWrite(VTT_SOCKET nSocket);
	VTT_VOID EventRead(VTT_SOCKET nSocket);
	VTT_VOID EventExcept(VTT_SOCKET nSocket);
	
private:
	utilityLibrary::CLock	m_lock; //锁对象
	VTT_BOOL m_bSelectRun;          //Select模型是否允许中。
	fd_set	m_read_set;  //
	fd_set	m_write_set;
	fd_set	m_excep_set;
	MapBaseSocket m_mapSocket;  //存放套接字
};

#endif 