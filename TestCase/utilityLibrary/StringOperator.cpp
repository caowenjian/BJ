#include "StringOperator.h"
NAMESPACE_BEGIN_T(utilityLibrary)

CSimpleBuffer::CSimpleBuffer()
{
	m_buffer = NULL;

	m_alloc_size = 0;
	m_write_offset = 0;
}

CSimpleBuffer::~CSimpleBuffer()
{
	m_alloc_size = 0;
	m_write_offset = 0;
	if (m_buffer)
	{
		free(m_buffer);
		m_buffer = NULL;
	}
}

VTT_VOID CSimpleBuffer::Extend(VTT_UINT32 len)
{
	m_alloc_size = m_write_offset + len;
	m_alloc_size += m_alloc_size >> 2;	// increase by 1/4 allocate size
	VTT_UCHAR* new_buf = (VTT_UCHAR*)realloc(m_buffer, m_alloc_size);
	if (new_buf != NULL)
	{
		m_buffer = new_buf;
	}
}

VTT_UINT32 CSimpleBuffer::Write(VTT_VOID* buf, VTT_UINT32 len)
{
	if (m_write_offset + len > m_alloc_size)
	{
		Extend(len);
	}

	if (buf)
	{
		memcpy(m_buffer + m_write_offset, buf, len);
	}

	m_write_offset += len;

	return len;
}

VTT_UINT32 CSimpleBuffer::Read(VTT_VOID* buf, VTT_UINT32 len)
{
	if (len > m_write_offset)
		len = m_write_offset;

	if (buf)
		memcpy(buf, m_buffer, len);

	m_write_offset -= len;
	memmove(m_buffer, m_buffer + len, m_write_offset);
	return len;
}

NAMESPACE_END_T(utilityLibrary)