#include "ISocketManager.h"
#include "SocketManager.h"
NAMESPACE_BEGIN_T(utilityLibrary)

ISocketManager& GetInstance()
{
  	static CSocketManager s_instance; 
  	return (ISocketManager&)s_instance;
}


NAMESPACE_END_T(utilityLibrary)