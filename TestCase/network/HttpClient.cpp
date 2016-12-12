#include "HttpClient.h"
#include "APINetwork.h"
#include "ProxySocket.h"
#include "HttpRequestInfo.h"
#include "HttpResponseInfo.h"
#include "../utility/APISrcCoding.h"
#include "../utility/FileReader.h"
#include "../utility/APIDirectoryFile.h"
NAMESPACE_BEGIN(network)
CONST INT32 C_I32RECV_DATA_LENGTH = 1024; //��ͨ�������ݻ�������С
CHttpClient::CHttpClient()
{
	m_proxySocket = new CProxySocket();
}


CHttpClient::~CHttpClient()
{
	SAFE_DELETE_PTR(m_proxySocket)
}


VOID CHttpClient::KillSelf()
{
	m_proxySocket->Close();
}

UINT8 CHttpClient::GetErrorCode()
{
	return m_u8ErrorCode;
}



VOID CHttpClient::SetErrorCode(UINT8 u8ErrorCode)
{
	m_u8ErrorCode = u8ErrorCode;
	//�������ʧ�ܺ󣬹رյ�ǰSocket 
	//(Ϊ��֧��keep-aliveģʽ���ڷ�����������ܹ�������������)
	if (m_u8ErrorCode != HTTPERROR_SUCCESS)
	{
		m_proxySocket->Close();
	}
}

BOOL CHttpClient::SendRequestInfo(CHttpRequestInfo* pRequestInfo, CHttpResponseInfo* pResponseInfo)
{
	JUDGE_PTR_FALSE(pRequestInfo)
	JUDGE_PTR_FALSE(pResponseInfo)
	m_pRequestInfo = pRequestInfo;
	m_pResponseInfo = pResponseInfo;
	SetErrorCode(HTTPERROR_SUCCESS);
	//���ӷ�����
	m_proxySocket->SetHostInfo(utility::CStringToString(m_pRequestInfo->GetHost()), m_pRequestInfo->GetPort());
	if (!m_proxySocket->IsConnected())
	{
		if (!m_proxySocket->Connect())
		{
			SetErrorCode(HTTPERROR_CONNECT);
			return FALSE;
		}
	}
	//��������
	UINT8 u8Type = m_pRequestInfo->GetHttpType();
	if (u8Type == E_HTTP_REQUEST_METHOD_GET)
	{
		JUDGE_INT_FALSE(SendHttpGet())
	}
	else if (u8Type == E_HTTP_REQUEST_METHOD_POST)
	{
		JUDGE_INT_FALSE(SendHttpPost())
	}

	//�ر�����
	m_proxySocket->Close();

	return TRUE; 
}

BOOL CHttpClient::SendHttpGet()
{
	//����HTTPͷ����
	JUDGE_INT_FALSE(SendHttpHeader())
	return RecvHttpData();
}


BOOL CHttpClient::SendHttpPost()
{
	//����HTTPͷ����
	JUDGE_INT_FALSE(SendHttpHeader())
	JUDGE_INT_FALSE(SendHttpBody())
	if (m_pRequestInfo->IsMultipart())
	{
		JUDGE_INT_FALSE(UploadPostFile())
	}
	JUDGE_INT_FALSE(RecvHttpData())
	return TRUE;
}


BOOL CHttpClient::SendHttpHeader()
{
	CString strHeader;
	int	header_length = m_pRequestInfo->GenerateHeader(strHeader);
	if (!m_proxySocket->SendData((CHAR*)(utility::CStringToString(strHeader)).c_str(), header_length))
	{
		SetErrorCode(HTTPERROR_TRANSPORT);
		return FALSE;
	}
	return TRUE;
}


BOOL CHttpClient::SendHttpBody()
{
	const std::string&	body = m_pRequestInfo->GetHttpBody();
	size_t	length = body.length();
	if (length == 0)
	{
		return TRUE;	//���body��û������ ֱ�ӷ���true
		//(�ϴ��ļ���ʱ��body�����Ƕ�̬���ɣ�body���ݿ���Ϊ��) 
	}
	if (!m_proxySocket->SendData((CHAR*)body.c_str(), length))
	{
		SetErrorCode(HTTPERROR_TRANSPORT);
		return FALSE;
	}
	return TRUE;
}


BOOL CHttpClient::UploadPostFile()
{
	//�����ļ�
	const std::vector<HttpFileDispositionPart*> vecPostFileList = m_pRequestInfo->GetFileUploadList();
	const std::string&	boundary = m_pRequestInfo->GetBoundary();
	for (size_t i = 0; i < vecPostFileList.size(); i++)
	{
		std::string file_header = "--" + boundary + "\r\n" + vecPostFileList[i]->GetDispositionPart();
		if (!m_proxySocket->SendData((CHAR*)file_header.c_str(), file_header.size()))
		{
			SetErrorCode(HTTPERROR_TRANSPORT);
			return false;
		}

		if (!UploadFile(vecPostFileList[i]->m_strFileLocalPath))
		{
			SetErrorCode(HTTPERROR_TRANSPORT);
			return false;
		}

		std::string file_tailer = "\r\n";
		if (!m_proxySocket->SendData((CHAR*)file_tailer.c_str(), file_tailer.size()))
		{
			SetErrorCode(HTTPERROR_TRANSPORT);
			return  false;
		}
	}

	//����boundary�������
	std::string post_tailer = "--" + boundary + "--\r\n";
	if (!m_proxySocket->SendData((CHAR*)post_tailer.c_str(), post_tailer.size()))
	{
		SetErrorCode(HTTPERROR_TRANSPORT);
		return FALSE;
	}

	return TRUE;
}


BOOL CHttpClient::UploadFile(CString strLocalFilePath)
{
	JUDGE_INT_FALSE(m_proxySocket)
	UINT32 u32FileSize = utility::GetFileLength(strLocalFilePath);	//�ļ���С
	JUDGE_INT_FALSE(u32FileSize)
	utility::CFileReader fileReader(strLocalFilePath);
	JUDGE_INT_FALSE(fileReader.Open())
	UINT32 u32UnSendSize = u32FileSize;	//δ�ϴ��ļ���С
	CHAR buffer[C_U32BUFFER_SIZE] = { 0 };
	while (u32UnSendSize > 0)
	{
		INT32 i32ReadSize = fileReader.Read(buffer, C_U32BUFFER_SIZE);
		if (i32ReadSize < 0)
		{
			SetErrorCode(HTTPERROR_IO);
			return FALSE;
		}
		if (m_proxySocket->SendData(buffer, i32ReadSize) != i32ReadSize)
		{
			SetErrorCode(HTTPERROR_TRANSPORT);
			return FALSE;
		}
		u32UnSendSize -= i32ReadSize;
		if (m_pProgressDelegate)
		{
			m_pProgressDelegate->dataWriteProgress(u32FileSize - u32UnSendSize, u32FileSize);
		}
	}
	return TRUE;
}


BOOL CHttpClient::RecvHttpData()
{

	char buff[C_I32RECV_DATA_LENGTH] = { 0 };
	std::string	header;
	while (TRUE)
	{
		int ret = m_proxySocket->RecvData(buff, C_I32RECV_DATA_LENGTH);
		if (ret <= 0)
		{
			SetErrorCode(HTTPERROR_TRANSPORT);
			return FALSE;
		}
		header.append(buff, ret);					//��ΪHeader�����̣ܶ�����һ�ο�������
		size_t end_index = header.find("\r\n\r\n");	//����Ҳ����Ҫ����ƫ������������ٶ�
		if (end_index != std::string::npos)
		{
			m_pResponseInfo->ParseResponseData(utility::StringToCString(header));
			break;
		}
	}
	return TRUE;
}


NAMESPACE_END(network)
