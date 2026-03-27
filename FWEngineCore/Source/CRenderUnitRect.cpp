#include"CRenderUnitRect.h"
#include"CVertexAttribute.h"


using namespace FW;


CRenderUnitRect::CRenderUnitRect(CConstruct* pHost) :CRenderUnit(pHost)
{
}

CRenderUnitRect::CRenderUnitRect(const char* pszName, CConstruct* pHost):CRenderUnit(pszName, pHost)
{
}

CRenderUnitRect::~CRenderUnitRect()
{ 
}


void CRenderUnitRect::Initialize(int countVertexBuffer, int countIndexBuffer)
{
	m_matWorld.Identity();

	m_nSizeVertex = 0;
	m_nCountVertexComponent = 0;
	for (VTVA_ITER iter = m_vtVertexAttrib.begin(); iter != m_vtVertexAttrib.end(); ++iter)
	{
		m_nSizeVertex += (*iter)->size();
		m_nCountVertexComponent += (*iter)->count();
	}


	//the count of vertex attribute equal the count of a vertex's component.
	m_nCountVertexArray = countVertexBuffer * m_nCountVertexComponent;

	m_outVT = new float[m_nCountVertexArray];
	memset(m_outVT, 0, m_nCountVertexArray);

	m_nSizeVertexBuffer = sizeof(float) * m_nCountVertexArray;


	m_nCountIndexArray = countIndexBuffer * countSurfaceComponent();
	m_outSI = new unsigned int[m_nCountIndexArray];
	memset(m_outSI, 0, m_nCountIndexArray);

	m_nSizeIndexBuffer = sizeof(unsigned int) * m_nCountIndexArray;

	GenerateGLEObject();
}