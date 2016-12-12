#ifndef NETWORKDEFINE_H__
#define NETWORKDEFINE_H__

#include <afxwin.h>
#include <string>

#ifndef NETWORK_DLL
#define NETWORK_API			__declspec( dllimport )
#define NETWORK_CLASS		__declspec( dllimport )
#else
#define NETWORK_API			__declspec( dllexport )
#define NETWORK_CLASS		__declspec( dllexport )
#endif


//Http传输错误码
enum	HTTPERROR
{
	HTTPERROR_SUCCESS,		//正确
	HTTPERROR_INVALID,		//HTTP已经被弃用
	HTTPERROR_CONNECT,		//连接出错
	HTTPERROR_TRANSPORT,	//传输失败
	HTTPERROR_IO,			//IO错误
	HTTPERROR_PARAMETER		//无效参数
};


#endif