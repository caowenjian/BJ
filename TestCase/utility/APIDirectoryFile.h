#ifndef APIDIRECTORYFILE_H_
#define APIDIRECTORYFILE_H_
#include "globalDefine.h"

NAMESPACE_BEGIN(utility)

/*************************************************
 // Method: GetFileLength
 // Description: 获取文件的大小
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API UINT32
 // Parameter: strFileAllPath
 // History:
 *************************************************/
UTILITY_API UINT32 GetFileLength(IN CONST CString strFileAllPath);


/*************************************************
 // Method: IsFileExist
 // Description: 判断文件是否存在
 // Author: cwj 
 // Date: 2016/03/16
 // Returns: UTILITY_API BOOL
 // Parameter: csFileName
 // History:
 *************************************************/
UTILITY_API BOOL IsFileExist(IN CONST LPCTSTR csFileName);


/*************************************************
 // Method: ParseFileAllPath
 // Description: 解析文件全路径
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
 // Description: 获取应用程序路径
 // Author: cwj 
 // Date: 2016/03/24
 // Returns: UTILITY_API CString
 // History:
 *************************************************/
UTILITY_API CString	GetAppPath();



/*************************************************
 // Method: CreateTempFile
 // Description: 创建某一个文件的临时文件，该临时文件是原文件大小，内容是垃圾数据。一般用于文件下载。
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
 // Description: 向一个文件中的指定位置写入指定的数据,文件中其他数据不变。
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
 // Description: 获取一个文件中的指定位置的数据。
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
 // Description: 创建多级目录
 // Author: cwj 
 // Date: 2016/03/25
 // Returns: UTILITY_API BOOL
 // Parameter: csDir
 // History:
 *************************************************/
UTILITY_API BOOL CreateAllDirectories(CString csDir);


/*************************************************
 // Method: ByteSizeToString
 // Description: 将字节数量转换为字符串可读单位
 // Author: cwj 
 // Date: 2016/03/25
 // Returns: UTILITY_API CString
 // Parameter: size
 // History:
 *************************************************/
UTILITY_API CString	ByteSizeToString(UINT32 size);


/*************************************************
 // Method: DeleteAllFile
 // Description: 删除指定目录下的文件。支持通配符
 // Author: cwj 
 // Date: 2016/03/30
 // Returns: UTILITY_API VOID
 // Parameter: strPathFileName
 // History:
 *************************************************/
UTILITY_API VOID DeleteAllFile(IN CString strPathFileName);
NAMESPACE_END(utility)

#endif