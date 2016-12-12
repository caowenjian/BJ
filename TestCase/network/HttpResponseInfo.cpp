#include "HttpResponseInfo.h"
#include "../utility/APISrcCoding.h"
NAMESPACE_BEGIN(network)

CHttpResponseInfo::CHttpResponseInfo()
{

}


CHttpResponseInfo::~CHttpResponseInfo()
{

}


VOID CHttpResponseInfo::ParseResponseData(CString strRecvData)
{
	strRecvData = strRecvData.MakeLower();
	size_t end_index = strRecvData.Find(_T("\r\n\r\n"));	//所以也不需要计算偏移来提高搜索速度
	if (end_index != -1)
	{
		m_strHeader = strRecvData.Mid(0, end_index + 4);
		m_strBody = strRecvData.Mid(end_index + 4, strRecvData.GetLength() - end_index - 4);
		ParseContentLength();
		if (m_strHeader.GetLength() >= 12)
		{
			m_i32HttpCode = utility::CStringToInt32(m_strHeader.Mid(9, 3));
		}
	}
}

VOID CHttpResponseInfo::ParseContentLength()
{

	CString conLenSplit = _T("content-length:");
	size_t start_index = m_strHeader.Find(conLenSplit);
	EQUAL_INT_VOID(start_index, -1)
	m_i32ContentLength = utility::CStringToInt32(m_strHeader.Mid(start_index + conLenSplit.GetLength(), m_strHeader.GetLength()));

}


NAMESPACE_END(network)
