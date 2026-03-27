#include"CRenderUnit.h"
#include"CVertexAttribute.h"
#include"CMaterial.h"
#include"CPass.h"
#include"CProgram.h"
#include"CSpace.h"
#include"CFrame.h"
#include"IDataResource.h"


using namespace FW;


CRenderUnit::CRenderUnit(CConstruct* pHost) : CConstruct(pHost, ECONSTRTYPE::CST_RENDERUNIT), 
m_eRenderType(ERNDTYPE::RT_UNKNOW), m_nGroupOrder(-1), m_outVT(nullptr), m_outVTOriginal(nullptr),
m_tmpVT(nullptr), m_outSI(nullptr), m_nSizeVertexBuffer(0), m_nSizeIndexBuffer(0), 
m_nSizeVertex(0),  m_nCountIndexArray(0), m_nCountVertexArray(0), 
m_idMaterial(0), m_pMaterial(nullptr), m_eGenMatl(EGEN::GE_UNKNOW)
{
}


CRenderUnit::CRenderUnit(const char* pszName, CConstruct* pHost) : CConstruct(pszName, pHost, 
ECONSTRTYPE::CST_RENDERUNIT), m_eRenderType(ERNDTYPE::RT_UNKNOW), m_nGroupOrder(-1), m_outVT(nullptr), 
m_outVTOriginal(nullptr), m_tmpVT(nullptr), m_outSI(nullptr), m_nSizeVertexBuffer(0), m_nSizeIndexBuffer(0),
m_nSizeVertex(0), m_nCountIndexArray(0), m_nCountVertexArray(0), 
m_idMaterial(0), m_pMaterial(nullptr), m_eGenMatl(EGEN::GE_UNKNOW)
{
}



CRenderUnit::~CRenderUnit()
{
	Destroy();
}


inline void CRenderUnit::setMaterial(CMaterial* pMaterial)
{
	m_pMaterial = pMaterial; 
	m_idMaterial = pMaterial->id();
	m_eGenMatl = pMaterial->gen();
}



void CRenderUnit::Initialize(int countVertexBuffer, int countIndexBuffer)
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

	m_outVTOriginal = new float[m_nCountVertexArray];
	memset(m_outVTOriginal, 0, m_nCountVertexArray);

	m_tmpVT = new float[m_nCountVertexArray];
	memset(m_tmpVT, 0, m_nCountVertexArray);

	m_nSizeVertexBuffer = sizeof(float) * m_nCountVertexArray;


	m_nCountIndexArray = countIndexBuffer * countSurfaceComponent();
	m_outSI = new unsigned int[m_nCountIndexArray];
	memset(m_outSI, 0, m_nCountIndexArray);

	m_nSizeIndexBuffer = sizeof(unsigned int) * m_nCountIndexArray;



	GenerateGLEObject();
}


void CRenderUnit::GenerateGLEObject()
{
	glGenBuffers(2, m_uVBuffer);

#ifdef _WND_OPENGL_PLATFORM_

	//generate VAO and bind the VAO & set vertex attribute
	glGenVertexArrays(1, &m_unVAO);

#endif

}


void CRenderUnit::DestroyGLEObject()
{
	glDeleteBuffers(2, m_uVBuffer);

#ifdef _WND_OPENGL_PLATFORM_

	glDeleteVertexArrays(1, &m_unVAO);

#endif // _WND_OPENGL_PLATFORM_

}



void CRenderUnit::BindModel()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeVertexBuffer(), arrayVertices(), GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBuffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexBuffer(), arrayIndex(), GL_STATIC_DRAW);

#ifdef _WND_OPENGL_PLATFORM_

	glBindVertexArray(m_unVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBuffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBuffer[1]);

#endif

}





bool inited = false;
void CRenderUnit::Rendering(CMaterial* pMatl, int indexPass)
{
	BindModel();
	pMatl->pass(indexPass)->program()->SetVertexAttributs(this);

	pMatl->pass(indexPass)->program()->UpdateWorldMatrix(m_matWorld);
	pMatl->pass(indexPass)->program()->SetUniformParameters();


	//glEnable(GL_CULL_FACE);

#ifdef _WND_OPENGL_PLATFORM_
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

	glDrawElements(GL_TRIANGLES, m_nCountIndexArray, GL_UNSIGNED_INT, 0);

	UnbindMode();
}



void CRenderUnit::UnbindMode()
{
#ifdef _WND_OPENGL_PLATFORM_

	glBindVertexArray(0);

#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



bool CRenderUnit::InitializeMaterial(CMaterial* pMatl)
{
	if (0 == pMatl)
	{
		return false;
	}

	CProgram* pProgm = 0;
	CVertexAttribute* pVA = 0;
	for (int i = 0; i < pMatl->countPass(); i++)
	{
		pProgm = pMatl->pass(i)->program();
		for (int n = 0; n < pProgm->countVertexAttribute(); n++)
		{
			pVA = pProgm->vertexAttr(n);
			if (!existed(pVA))
			{
				return false;
			}
		}
	}

	return true;
}


bool CRenderUnit::existed(CVertexAttribute* pVA)
{
	if (0 == pVA)
	{
		return false;
	}

	for (VTVA_ITER iter = m_vtVertexAttrib.begin(); iter != m_vtVertexAttrib.end(); ++iter)
	{
		if ((*iter)->typeVertexAttr() == pVA->typeVertexAttr())
		{
			return true;
		}
	}

	return false;
}



void CRenderUnit::Destroy()
{
	if (nullptr != m_outVT)
	{
		delete[] m_outVT;
		m_outVT = nullptr;
	}

	if (nullptr != m_outVTOriginal)
	{
		delete[] m_outVTOriginal;
		m_outVTOriginal = nullptr;
	}

	if (nullptr != m_tmpVT)
	{
		delete[] m_tmpVT;
		m_tmpVT = nullptr;
	}

	if (nullptr != m_outSI)
	{
		delete[] m_outSI;
		m_outSI = nullptr;
	}


	for (VTVA_ITER iter = m_vtVertexAttrib.begin(); iter != m_vtVertexAttrib.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
		}
	}

	if (nullptr != m_pMaterial)
	{
		if (CIDManager::Instance().Inquire(m_idMaterial))
		{
			IDataResource* pIDR = CreateDataResource();
			pIDR->ReleasePrimatter(m_pMaterial);
		}
		else
		{
			if (m_eGenMatl != EGEN::GE_ORG_PM)
			{
				delete m_pMaterial;
			}
		}

		m_idMaterial = 0;
		m_pMaterial = nullptr;
	}

	DestroyGLEObject();

}


