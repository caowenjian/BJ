#ifndef APIDIRECTORYFILE_H_
#define APIDIRECTORYFILE_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)

/*************************************************
 // Method: GetFileLength
 // Description: ��ȡ�ļ��Ĵ�С
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API UINT32
 // Parameter: strFileAllPath
 // History:
 *************************************************/
UTILITY_API UINT32 GetFileLength(IN CONST CString strFileAllPath);


/*************************************************
 // Method: IsFileExist
 // Description: �ж��ļ��Ƿ����
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API BOOL
 // Parameter: csFileName
 // History:
 *************************************************/
UTILITY_API BOOL IsFileExist(IN CONST LPCTSTR csFileName);


/*************************************************
 // Method: ParseFileAllPath
 // Description: �����ļ�ȫ·��
 // Author: cwj 
 // Date: 2016/03/24
 // Returns: UTILITY_API VOID
 // Parameter: strFileAllPath
 // Parameter: strPath
 // Parameter: strFileName
 // Parameter: strExtendName
 // History:
 *************************************************/
UTILITY_API VOID ParseFileAllPath(IN CString strFileAllPath, OUT CString& strPath, OUT CString &strFileName, OUT CString& strExtendName);


/*************************************************
 // Method: GetAppPath
 // Description: ��ȡӦ�ó���·��
 // Author: cwj 
 // Date: 2016/03/24
 // Returns: UTILITY_API CString
 // History:
 *************************************************/
UTILITY_API CString	GetAppPath();



/*************************************************
 // Method: CreateTempFile
 // Description: ����ĳһ���ļ�����ʱ�ļ�������ʱ�ļ���ԭ�ļ���С���������������ݡ�һ�������ļ����ء�
 // Author: cwj 
 // Date: 2016/03/24
 // Returns: UTILITY_API BOOL
 // Parameter: strFileAllPath
 // Parameter: u32FileSize
 // Parameter: strTempAllPath
 // History:
 *************************************************/
UTILITY_API BOOL CreateTempFile(IN CString strFileAllPath, IN UINT32 u32FileSize, OUT CString& strTempAllPath);


/*************************************************
 // Method: SetFileData
 // Description: ��һ���ļ��е�ָ��λ��д��ָ��������,�ļ����������ݲ��䡣
 // Author: cwj 
 // Date: 2016/03/24
 // Returns: UTILITY_API BOOL
 // Parameter: strFileAllPath
 // Parameter: u32Offset
 // Parameter: u32DataSize
 // Parameter: pData
 // History:
 *************************************************/
UTILITY_API BOOL SetFileData(IN CString strFileAllPath, IN UINT32 u32Offset, IN UINT32 u32DataSize, IN UCHAR* pData);


/*************************************************
 // Method: GetFileData
 // Description: ��ȡһ���ļ��е�ָ��λ�õ����ݡ�
 // Author: cwj 
 // Date: 2016/03/24
 // Returns: UTILITY_API BOOL
 // Parameter: strFileAllPath
 // Parameter: u32Offset
 // Parameter: u32DataSize
 // Parameter: pData
 // History:
 *************************************************/
UTILITY_API BOOL GetFileData(IN CString strFileAllPath, IN UINT32 u32Offset, IN OUT UINT32& u32DataSize, IN OUT UCHAR* pData);



/*************************************************
 // Method: CreateAllDirectories
 // Description: �����༶Ŀ¼
 // Author: cwj 
 // Date: 2016/03/25
 // Returns: UTILITY_API BOOL
 // Parameter: csDir
 // History:
 *************************************************/
UTILITY_API BOOL CreateAllDirectories(CString csDir);


/*************************************************
 // Method: ByteSizeToString
 // Description: ���ֽ�����ת��Ϊ�ַ����ɶ���λ
 // Author: cwj 
 // Date: 2016/03/25
 // Returns: UTILITY_API CString
 // Parameter: size
 // History:
 *************************************************/
UTILITY_API CString	ByteSizeToString(UINT32 size);


/*************************************************
 // Method: DeleteAllFile
 // Description: ɾ��ָ��Ŀ¼�µ��ļ���֧��ͨ���
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: UTILITY_API VOID
 // Parameter: strPathFileName
 // History:
 *************************************************/
UTILITY_API VOID DeleteAllFile(IN CString strPathFileName);
NAMESPACE_END(utility)

#endif