#ifndef APINETWORK_H_
#define APINETWORK_H_
#include "../utility/globalDefine.h"
#include "networkDefine.h"
NAMESPACE_BEGIN(network)

CONST INT32 I32_SOCKET_MAX_SEND_BUF_SIZE = 128 * 1024;	//每次调用send函数最大数据大小
CONST INT32 I32_SOCKET_MAX_RECV_BUF_SIZE = 128 * 1024;

/*************************************************
 // Method: InitWinSocket
 // Description:  使用Winsock 2 DLL (Ws2_32.dll)
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API VOID
 // History:
 *************************************************/
NETWORK_API BOOL InitWinSocket();



/*************************************************
 // Method: DestoryWinSocket
 // Description: 终止Winsock 2 DLL (Ws2_32.dll) 的使用.
 // Author: cwj 
 // Date: 2016/03/31
 // Returns: NETWORK_API BOOL
 // History:
 *************************************************/
NETWORK_API BOOL DestoryWinSocket();

/*************************************************
 // Method: SetSocketBlockStatus
 // Description: 设置套接字是否阻塞
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
 // Description: 是否使用Nagle算法。对于一些需要快速响应，对延时敏感的应用,
 比如窗口程序，鼠标响应，一般而言需要禁用Nagle算法。
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
 // Description: 是否重复绑定，一般在bind函数前使用。
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
 // Description: 获取socket地址结构
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
 // Description: 判断是否是阻塞错误
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API BOOL
 // History:
 *************************************************/
NETWORK_API BOOL IsBlockError();



NETWORK_API SOCKET Connect(IN CONST CHAR* strServerip, UINT16 u16Port, UINT32 u32Timeout = 10000);


/*************************************************
 // Method: SendData
 // Description: 发送数据
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: NETWORK_API INT32
 // Parameter: nSocket
 // Parameter: pBuf
 // Parameter: i32Length:实际发送的值。
 // History:
 *************************************************/
NETWORK_API INT32 SendData(SOCKET nSocket, CHAR* pBuf, INT32 i32Length);



/*************************************************
 // Method: RecvData
 // Description: 是否接收到指定接收数据量才返回。 bIsAllRecv用来指定是否。
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
 // Description: 监听服务器端口,返回监听成功的套接字
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