#ifndef HTTPREQUESTINFO_H_
#define HTTPREQUESTINFO_H_
#include "../utility/globalDefine.h"
#include "../utility/APISrcCoding.h"
#include "networkDefine.h"
NAMESPACE_BEGIN(network)
class IHttpPostFile;

//Http�ֶ�
struct	HttpField
{
	std::string	m_strFieldName;
	std::string	m_strFieldValue;
	HttpField(const std::string& name, const std::string& value)
		:m_strFieldName(name), m_strFieldValue(value){}
};

//Http�ϴ��ļ�����
struct HttpFileDispositionPart
{
	std::string		m_strName;			//name�ֶ�
	std::string		m_strContentType;	//Content-Type:�ֶ�
	CString			m_strFileLocalPath;	//filename�ֶ�
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
	 // Description: ����ֶ����ݵ�httpͷ�б���
	 // Author: cwj 
	 // Date: 2016/04/27
	 // Returns: VOID
	 // Parameter: strName
	 // Parameter: strValue
	 // Parameter: bIsCover:�Ƿ񸲸������ֶε����ݣ� ��false,�Ҵ�����ͬ����ֱ�ӷ��ء�
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
	UINT8		 m_u8RequestType;	//��������E_HTTP_REQUEST_METHOD_GET, E_HTTP_REQUEST_METHOD_POST
	CString		 m_strHost;			//��������
	CString		 m_strParam;		//�������
	UINT16		 m_u16Post;			//����˿�
	CString		 m_strHeader;		//����ͷ����
	std::vector<HttpField>			m_vecHeaderField;		//HTTPͷ�ֶ�
	std::vector<HttpField>			m_vecBodyField;			//HTTP�����
	std::string						m_strBody;				//HTTP��
	std::vector<HttpFileDispositionPart*>		m_vecHttpUploadFile;		//�ϴ��ļ�����ȫ·���б�

	BOOL							m_bIsMultipart;			//�Ƿ���Multipart����
	std::string						m_strBoundary;			//�ָ���
};
NAMESPACE_END(network)



#endif