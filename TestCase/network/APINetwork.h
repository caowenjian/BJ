#ifndef APINETWORK_H_
#define APINETWORK_H_
#include "../utility/globalDefine.h"
#include "networkDefine.h"
NAMESPACE_BEGIN(network)

CONST INT32 I32_SOCKET_MAX_SEND_BUF_SIZE = 128 * 1024;	//ÿ�ε���send����������ݴ�С
CONST INT32 I32_SOCKET_MAX_RECV_BUF_SIZE = 128 * 1024;

/*************************************************
 // Method: InitWinSocket
 // Description:  ʹ��Winsock 2 DLL (Ws2_32.dll)
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API VOID
 // History:
 *************************************************/
NETWORK_API BOOL InitWinSocket();



/*************************************************
 // Method: DestoryWinSocket
 // Description: ��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��.
 // Author: cwj 
 // Date: 2016/03/31
 // Returns: NETWORK_API BOOL
 // History:
 *************************************************/
NETWORK_API BOOL DestoryWinSocket();

/*************************************************
 // Method: SetSocketBlockStatus
 // Description: �����׽����Ƿ�����
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API BOOL
 // Parameter: i32Socket
 // Parameter: bBlock
 // History:
 *************************************************/
NETWORK_API BOOL SetSocketBlock(INT32 i32Socket, BOOL bBlock);


/*************************************************
 // Method: SetSocketNagle
 // Description: �Ƿ�ʹ��Nagle�㷨������һЩ��Ҫ������Ӧ������ʱ���е�Ӧ��,
 ���細�ڳ��������Ӧ��һ�������Ҫ����Nagle�㷨��
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API BOOL
 // Parameter: nSocket
 // Parameter: bNagle
 // History:
 *************************************************/
NETWORK_API BOOL SetSocketNagle(SOCKET nSocket, BOOL bNagle);



/*************************************************
 // Method: SetSocketReuse
 // Description: �Ƿ��ظ��󶨣�һ����bind����ǰʹ�á�
 // Author: cwj 
 // Date: 2016/03/31
 // Returns: NETWORK_API BOOL
 // Parameter: nSocket
 // Parameter: bReuse
 // History:
 *************************************************/
NETWORK_API BOOL SetSocketReuse(SOCKET nSocket, BOOL bReuse);

/*************************************************
 // Method: GetAddrStruct
 // Description: ��ȡsocket��ַ�ṹ
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: VOID
 // Parameter: ip
 // Parameter: port
 // Parameter: pAddr
 // History:
 *************************************************/
NETWORK_API BOOL GetAddrStruct(CONST CHAR* ip, CONST UINT16 port, sockaddr_in* pAddr);


/*************************************************
 // Method: IsBlockError
 // Description: �ж��Ƿ�����������
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API BOOL
 // History:
 *************************************************/
NETWORK_API BOOL IsBlockError();



NETWORK_API SOCKET Connect(IN CONST CHAR* strServerip, UINT16 u16Port, UINT32 u32Timeout = 10000);


/*************************************************
 // Method: SendData
 // Description: ��������
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API INT32
 // Parameter: nSocket
 // Parameter: pBuf
 // Parameter: i32Length:ʵ�ʷ��͵�ֵ��
 // History:
 *************************************************/
NETWORK_API INT32 SendData(SOCKET nSocket, CHAR* pBuf, INT32 i32Length);



/*************************************************
 // Method: RecvData
 // Description: �Ƿ���յ�ָ�������������ŷ��ء� bIsAllRecv����ָ���Ƿ�
 // Author: cwj 
 // Date: 2016/03/31
 // Returns: NETWORK_API INT32
 // Parameter: nSocket
 // Parameter: pBuf
 // Parameter: i32Length
 // Parameter: bIsAllRecv
 // History:
 *************************************************/
NETWORK_API INT32 RecvData(IN SOCKET nSocket, OUT CHAR* pBuf, IN INT32 i32Length, BOOL bIsAllRecv = TRUE);

/*************************************************
 // Method: Listen
 // Description: �����������˿�,���ؼ����ɹ����׽���
 // Author: cwj 
 // Date: 2016/03/31
 // Returns: NETWORK_API SOCKET
 // Parameter: strServerip
 // Parameter: u16Port
 // History:
 *************************************************/
NETWORK_API SOCKET Listen(IN CONST CHAR* strServerip, UINT16 u16Port);



NETWORK_API BOOL URLParse(IN CONST CString strURL, OUT CString& strHost, OUT UINT16& u16Port, OUT CString& strObjectData);

NAMESPACE_END(network)
#endif