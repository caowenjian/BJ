#ifndef _ISOCKETMANAGER_H
#define _ISOCKETMANAGER_H
#include "globalDefine.h"

NAMESPACE_BEGIN_T(utilityLibrary)



class UTILITYLIBRARY_CLASS ISocketManager
{
public:
	ISocketManager(){}
	virtual ~ISocketManager(){}
public:
    virtual VTT_VOID StartSelectLoop() = 0; 
	virtual VTT_VOID EndSelectLoop() = 0;
public:
	virtual VTT_BOOL Connect(const VTT_CHAR* pServer, const VTT_UINT16 u16Port) = 0;
};

UTILITYLIBRARY_API ISocketManager& GetInstance();

NAMESPACE_END_T(utilityLibrary)
#endif