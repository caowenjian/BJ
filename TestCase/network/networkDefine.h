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


//Http���������
enum	HTTPERROR
{
	HTTPERROR_SUCCESS,		//��ȷ
	HTTPERROR_INVALID,		//HTTP�Ѿ�������
	HTTPERROR_CONNECT,		//���ӳ���
	HTTPERROR_TRANSPORT,	//����ʧ��
	HTTPERROR_IO,			//IO����
	HTTPERROR_PARAMETER		//��Ч����
};


#endif