#ifndef FILEREADER_H_
#define FILEREADER_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)
class UTILITY_CLASS CFileReader
{
public:
	CFileReader(CONST CString strFileAllPath);
	~CFileReader();
public:
	BOOL Open();
	BOOL Read(CHAR* pBuf, UINT32 i32Size);
	VOID Close();
private:
	FILE* m_pFile;
	CString m_strFileAllPath;
	BOOL m_bReady;
};

NAMESPACE_END(utility)

#endif