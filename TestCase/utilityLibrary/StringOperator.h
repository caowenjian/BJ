#ifndef _STRINGOPERATOR_H
#define _STRINGOPERATOR_H
#include "globalDefine.h"
NAMESPACE_BEGIN_T(utilityLibrary)

class UTILITYLIBRARY_CLASS CSimpleBuffer
{
public:
	CSimpleBuffer();
	~CSimpleBuffer();
	VTT_UCHAR*  GetBuffer() { return m_buffer; }
	VTT_UINT32 GetAllocSize() { return m_alloc_size; }
	VTT_UINT32 GetWriteOffset() { return m_write_offset; }
	VTT_VOID IncWriteOffset(VTT_UINT32 len) { m_write_offset += len; }

	VTT_VOID Extend(VTT_UINT32 len);
	VTT_UINT32 Write(VTT_VOID* buf, VTT_UINT32 len);
	VTT_UINT32 Read(VTT_VOID* buf, VTT_UINT32 len);
private:
	VTT_UCHAR*	m_buffer;		//�������
	VTT_UINT32	m_alloc_size;	//Ҫ��������Ŀռ��С
	VTT_UINT32	m_write_offset; //ʹ�õĿռ��С
};
	
NAMESPACE_END_T(utilityLibrary)
#endif