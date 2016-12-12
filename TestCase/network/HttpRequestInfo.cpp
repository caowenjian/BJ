#include "HttpRequestInfo.h"
#include "APINetwork.h"
#include "../utility/APISrcCoding.h"
#include "../utility/APIOther.h"
#include "../utility/APIDirectoryFile.h"
NAMESPACE_BEGIN(network)
CONST std::string	C_STR_HTTP_FIELDNAME_ACCEPT_ = "Accept";
CONST std::string	C_STR_HTTP_FIELDNAME_CONNECT = "Connection";
CONST std::string	C_STR_HTTP_FIELDNAME_CONTENT_TYPE = "Content-Type";
CONST std::string	C_STR_HTTP_FIELDNAME_CONTENT_LENGTH = "Content-Length";

CHttpRequestInfo::CHttpRequestInfo(CONST CString strURL, CONST UINT8 u8RequestType)
{
	InitDefaultField();
	SetRequest(strURL, u8RequestType);
	CString ss;
	GenerateHeader(ss);
}


CHttpRequestInfo::~CHttpRequestInfo()
{
	InitDefaultField();
}

VOID CHttpRequestInfo::InitDefaultField()
{
	m_u8RequestType = E_HTTP_REQUEST_METHOD_GET;
	//添加一些默认Http头字段
	m_vecHeaderField.push_back(HttpField(C_STR_HTTP_FIELDNAME_ACCEPT_, "*/*"));
	m_vecHeaderField.push_back(HttpField(C_STR_HTTP_FIELDNAME_CONNECT, "Keep-Alive"));
}

BOOL CHttpRequestInfo::SetRequest(CONST CString strURL, CONST UINT8 u8RequestType)
{
	if ( (u8RequestType != E_HTTP_REQUEST_METHOD_GET) && (u8RequestType != E_HTTP_REQUEST_METHOD_POST) )
	{
		return FALSE;
	}
	m_u8RequestType = u8RequestType;

	return network::URLParse(strURL, m_strHost, m_u16Post, m_strParam);
}


INT32 CHttpRequestInfo::GenerateHeader(CString& strHeader)
{

	strHeader.Empty();

	//请求方法和实体
	CString strType = (m_u8RequestType == E_HTTP_REQUEST_METHOD_GET) ? _T("GET") : _T("POST");
	strHeader.Append(strType + _T(" "));
	strHeader.Append(m_strParam);
	strHeader.Append(_T(" HTTP/1.1\r\n"));

	//主机
	strHeader.Append(_T("Host:"));
	strHeader.Append(m_strHost);
	//add by kuaidao host增加端口
	strHeader.Append(_T(":"));
	strHeader.Append(utility::Int32ToCString(m_u16Post));
	strHeader.Append(_T("\r\n"));


	//计算Body的长度，赋值给ContentLength
	if (m_u8RequestType == E_HTTP_REQUEST_METHOD_POST)
 	{
		AddDataToHeaderField();
 	}

	//添加Header Field
	for (size_t i = 0; i < m_vecHeaderField.size(); i++)
	{
		strHeader.Append(utility::StringToCString(m_vecHeaderField[i].m_strFieldName) + _T(": ") + utility::StringToCString(m_vecHeaderField[i].m_strFieldValue) + _T("\r\n"));
	}

	//添加最后一个\r\n
	strHeader.Append(_T("\r\n"));
	return strHeader.GetLength();
}

INT32 CHttpRequestInfo::GenerateBody()
{
	m_strBody.clear();
	if (m_bIsMultipart)
	{
		m_strBoundary = utility::GenerateHttpBoundary();
		for (size_t i = 0; i < m_vecBodyField.size(); i++)
		{
			const std::string&	name = m_vecBodyField[i].m_strFieldName;
			const std::string&	value = m_vecBodyField[i].m_strFieldValue;
			std::string	field = "--" + m_strBoundary + "\r\n" + "content-disposition: form-data; name=\"" + name + "\"\r\n\r\n" + value + "\r\n";
			m_strBody += field;
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecBodyField.size(); i++)
		{
			const std::string&	name = m_vecBodyField[i].m_strFieldName;
			const std::string&	value = m_vecBodyField[i].m_strFieldValue;
			m_strBody += (name + "=" + utility::ToRFC1738(value)) + "&";
		}
	}
	return m_strBody.length();
}


/*************************************************
 // Method: AddDataToHeaderField
 // Description: 计算body长度设置给Content-Length。
 // Author: cwj 
 // Date: 2016/05/04
 // Returns: VOID
 // History:
 *************************************************/
VOID CHttpRequestInfo::AddDataToHeaderField()
{
	GenerateBody();
	INT nLength = m_strBody.size(); //Content-Length
	std::string	strContentType; //Content-Type
	if (m_bIsMultipart)
	{
		//添加Files
		for (size_t i = 0; i < m_vecHttpUploadFile.size(); i++)
		{

			std::string post_part = "--" + m_strBoundary + "\r\n" + m_vecHttpUploadFile[i]->GetDispositionPart();
			nLength += (int)post_part.size();
			nLength += utility::GetFileLength(m_vecHttpUploadFile[i]->m_strFileLocalPath);
			nLength += 2;						//在文件后需要添加\r\n
 		}
		std::string post_end = "--" + m_strBoundary + "--\r\n";
		nLength += (int)post_end.size();
		strContentType = "multipart/form-data; boundary=" + m_strBoundary;
	}
	else
	{
		//如果没有直接设置Http体，则以Field的形式构造HTTP体
		//if (m_strBody.empty())
		//{
			strContentType = "application/x-www-form-urlencoded";
// 		}
// 		else
// 		{
// 			strContentType = "text/plain";
// 		}  
	}
	AddHeaderField(C_STR_HTTP_FIELDNAME_CONTENT_TYPE, strContentType, FALSE);
	AddHeaderField(C_STR_HTTP_FIELDNAME_CONTENT_LENGTH, utility::Uint32ToString(nLength), TRUE);
}

VOID CHttpRequestInfo::AddHeaderField(CONST std::string& strName, CONST std::string& strValue, BOOL bIsCover)
{
	for (size_t i = 0; i < m_vecHeaderField.size(); i++)
	{
		if (!bIsCover)
		{
			EQUAL_INT_VOID(m_vecHeaderField[i].m_strFieldName, strName)
		}
		else
		{
			if (m_vecHeaderField[i].m_strFieldName == strName)
			{
				m_vecHeaderField[i].m_strFieldValue = strValue;
				return;
			}
		}
	}
	m_vecHeaderField.push_back(HttpField(strName, strValue));
}


VOID CHttpRequestInfo::AddFileField(CONST std::string strName, CONST CString strFileLocalPath, CONST std::string strContentType /*= "Application/oct-stream"*/)
{
	for (size_t i = 0; i < m_vecHttpUploadFile.size(); i++)
	{
		if (m_vecHttpUploadFile[i]->m_strName == strName)
		{
			//不允许重名
			return;
		}
	}
	HttpFileDispositionPart* http_file = new HttpFileDispositionPart(strName, strFileLocalPath, strContentType);
	m_vecHttpUploadFile.push_back(http_file);
	m_bIsMultipart = TRUE;
}
NAMESPACE_END(network)
