#include"CLineMesh.h"
#include"CVertexAttribute.h"
#include"CMaterial.h"
#include"CPass.h"
#include"CProgram.h"
#include"CVertexShader.h"
#include"CFragmentShader.h"
#include"CParameterUniform.h"
#include"CRenderUnitLine.h"



using namespace FW;

CLineMesh::CLineMesh(CConstruct* pHost) : CMesh(pHost)
{
	m_v4Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

CLineMesh::CLineMesh(const char* pszName, CConstruct* pHost) : CMesh(pszName, pHost)
{
	m_v4Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}


CLineMesh::~CLineMesh()
{
}


bool CLineMesh::Initialize(Vector3& start, Vector3& end, Vector4* pColor /*= 0*/)
{
	if (m_pRndUt != 0)
	{
		return false;
	}

	if (0 != pColor)
	{
		m_v4Color = *pColor;
	}

	m_pRndUt = new CRenderUnitLine(name(), this);
	

	CVertexAttribute* pAttrib = new CVertexAttribute("VertexPos");
	pAttrib->Initialize(EVATYPE::VA_POS, "", 3, sizeof(float), 0);
	m_pRndUt->AddVertexAttribute(pAttrib);

	Vector3* pPos = new Vector3(start);
	m_vtSVertex.push_back(pPos);

	pPos = new Vector3(end);
	m_vtSVertex.push_back(pPos);


	SSurface* pSuf = new SSurface;
	pSuf->_v0 = 0;
	pSuf->_v1 = 1;
	pSuf->_v2 = 1;

	m_vtSurface.push_back(pSuf);

	m_pRndUt->Initialize(m_vtSVertex.size(), m_vtSurface.size());
	((CRenderUnitLine*)m_pRndUt)->setColor(m_v4Color);

	//generate output data
	SetOutputVertexData();

	int index = -1;
	for (int i = 0; i < m_vtSurface.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_pRndUt->setIndexData(++index, m_vtSurface[i]->arIndex[j]);
		}
	}

	return true;
}



void CLineMesh::Update(Vector3& start, Vector3& end, Matrix4x4& matWorld)
{
	if (nullptr == m_pRndUt)
	{
		return;
	}

	*m_vtSVertex[0] = start;
	*m_vtSVertex[1] = end;

	//((CRenderUnitLine*)m_pRndUt)->setColor(m_v4Color);

	SetOutputVertexData();

	m_pRndUt->matWorld() = matWorld;
}



void CLineMesh::Update(Vector3& start, Vector3& end)
{
	if (nullptr == m_pRndUt)
	{
		return;
	}

	*m_vtSVertex[0] = start;
	*m_vtSVertex[1] = end;

	SetOutputVertexData();
}




void CLineMesh::SetOutputVertexData()
{
	int index = -1;
	for (int i = 0; i < m_vtSVertex.size(); i++)
	{
		m_pRndUt->setVertexData(++index, m_vtSVertex[i]->x);
		m_pRndUt->setVertexData(++index, m_vtSVertex[i]->y);
		m_pRndUt->setVertexData(++index, m_vtSVertex[i]->z);
	}
}