#include "FileReader.h"

NAMESPACE_BEGIN(utility)
CFileReader::CFileReader(CONST CString strFileAllPath) : m_strFileAllPath(strFileAllPath)
{

}

CFileReader::~CFileReader()
{
	Close();
}


BOOL CFileReader::Open()
{
	m_bReady = (_wfopen_s(&m_pFile, m_strFileAllPath, _T("rb")) == 0);
	return	m_bReady;
}


BOOL CFileReader::Read(CHAR* pBuf, UINT32 i32Size)
{
	return m_bReady ? fread(pBuf, 1, i32Size, m_pFile): -1;
}


VOID CFileReader::Close()
{
	JUDGE_INT_VOID(m_bReady)
	fclose(m_pFile);
	m_bReady = FALSE;
}
NAMESPACE_END(utility)
