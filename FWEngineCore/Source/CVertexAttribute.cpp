#include"CVertexAttribute.h"


using namespace FW;

CVertexAttribute::CVertexAttribute():m_nCountComponent(0),m_nSizeComponent(0),m_nOffset(0),m_nSize(0), 
m_eTypeVertexAttr(EVATYPE::VA_UNKNOW)
{
}

CVertexAttribute::CVertexAttribute(const char* pszName) : CShaderVariable(pszName), m_nCountComponent(0), 
m_nSizeComponent(0), m_nOffset(0), m_nSize(0), m_eTypeVertexAttr(EVATYPE::VA_UNKNOW)
{
}

CVertexAttribute::~CVertexAttribute()
{
}


void CVertexAttribute::Initialize(EVATYPE type, const char* pszVarName, int countComponent, int sizeComponent, int offset)
{
	m_eTypeVertexAttr = type;

	m_nOffset = offset;
	m_nCountComponent = countComponent;
	m_nSizeComponent = sizeComponent;
	m_nSize = m_nCountComponent * m_nSizeComponent;

	m_strVarName = pszVarName;
}


bool CVertexAttribute::Copy(CVertexAttribute* pSrcVA)
{
	if (nullptr == pSrcVA)
	{
		return false;
	}

	m_eTypeVertexAttr = pSrcVA->m_eTypeVertexAttr;
	m_nOffset = pSrcVA->m_nOffset;
	m_nCountComponent = pSrcVA->m_nCountComponent;
	m_nSizeComponent = pSrcVA->m_nSizeComponent;
	m_nSize = pSrcVA->m_nSize;

	m_strVarName = pSrcVA->m_strVarName;

	return true;

}