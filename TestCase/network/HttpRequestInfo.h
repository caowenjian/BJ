#ifndef HTTPREQUESTINFO_H_
#define HTTPREQUESTINFO_H_
#include "../utility/globalDefine.h"
#include "../utility/APISrcCoding.h"
#include "networkDefine.h"
NAMESPACE_BEGIN(network)
class IHttpPostFile;

//Http字段
struct	HttpField
{
	std::string	m_strFieldName;
	std::string	m_strFieldValue;
	HttpField(const std::string& name, const std::string& value)
		:m_strFieldName(name), m_strFieldValue(value){}
};

//Http上传文件定义
struct HttpFileDispositionPart
{
	std::string		m_strName;			//name字段
	std::string		m_strContentType;	//Content-Type:字段
	CString			m_strFileLocalPath;	//filename字段
	HttpFileDispositionPart(const std::string strName, CString strFileLocalPath, std::string strContentType) :m_strName(strName), m_strFileLocalPath(strFileLocalPath), m_strContentType(strContentType){}
	~HttpFileDispositionPart();
	std::string GetDispositionPart()
	{
		std::string file_header = "Content-Disposition: form-data; name=\"" + m_strName + "\"; filename=\"" +
			utility::CStringToString(m_strFileLocalPath) + "\"\r\n" +
			"Content-Type: " + m_strContentType + "\r\n\r\n";
		return file_header;
	}
};


enum
{
	E_HTTP_REQUEST_METHOD_GET = 1,
	E_HTTP_REQUEST_METHOD_POST = 2
};
class NETWORK_CLASS CHttpRequestInfo
{
public:
	CHttpRequestInfo(CONST CString strURL, CONST UINT8 u8RequestType);
	~CHttpRequestInfo();
	VOID InitDefaultField();
	BOOL SetRequest(CONST CString strURL, CONST UINT8 u8RequestType);
	CString GetHost(){ return m_strHost; }
	UINT16  GetPort(){ return m_u16Post; }
	UINT8	GetHttpType(){ return m_u8RequestType; }
	std::string GetHttpBody(){ return m_strBody; }
	BOOL  IsMultipart(){ return m_bIsMultipart; }
	std::string GetBoundary(){ return m_strBoundary; }
	std::vector<HttpFileDispositionPart*> GetFileUploadList(){ return m_vecHttpUploadFile; }
	/*************************************************
	 // Method: AddHeaderField
	 // Description: 添加字段数据到http头列表中
	 // Author: cwj 
	 // Date: 2016/04/27
	 // Returns: VOID
	 // Parameter: strName
	 // Parameter: strValue
	 // Parameter: bIsCover:是否覆盖已有字段的数据， 若false,且存在相同的则直接返回。
	 // History:
	 *************************************************/
	VOID AddHeaderField(CONST std::string& strName, CONST std::string& strValue, BOOL bIsCover);

	/*************************************************
	 // Method: AddFileField
	 // Description: 
	 // Author: cwj 
	 // Date: 2016/05/04
	 // Returns: VOID
	 // Parameter: strName
	 // Parameter: strFileLocalPath
	 // Parameter: strContentType
	 // History:
	 *************************************************/
	VOID AddFileField(CONST std::string strName, CONST CString strFileLocalPath, CONST std::string strContentType = "Application/oct-stream");

	INT32 GenerateHeader(CString& strHeader); 
	INT32 GenerateBody();
private:
	VOID AddDataToHeaderField();
	VOID GenerateBoundary();
private:
	UINT8		 m_u8RequestType;	//请求类型E_HTTP_REQUEST_METHOD_GET, E_HTTP_REQUEST_METHOD_POST
	CString		 m_strHost;			//请求域名
	CString		 m_strParam;		//请求参数
	UINT16		 m_u16Post;			//请求端口
	CString		 m_strHeader;		//请求头数据
	std::vector<HttpField>			m_vecHeaderField;		//HTTP头字段
	std::vector<HttpField>			m_vecBodyField;			//HTTP体参数
	std::string						m_strBody;				//HTTP体
	std::vector<HttpFileDispositionPart*>		m_vecHttpUploadFile;		//上传文件本地全路径列表

	BOOL							m_bIsMultipart;			//是否是Multipart请求
	std::string						m_strBoundary;			//分隔符
};
NAMESPACE_END(network)



#endif