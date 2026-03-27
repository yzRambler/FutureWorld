#include"CMesh.h"
#include"CComesh.h"
#include"CEssety.h"
#include"CVertexAttribute.h"
#include"CSkin.h"
#include"CMaterial.h"
#include"CTime.h"
#include"CAABB.h"
#include"CAssistFrame.h"
#include"CSceneNode.h"
#include"CPass.h"
#include"CProgram.h"
#include"CRender.h"
#include"CBound.h"
#include"CBox.h"
#include"CIDManager.h"
#include"IDataResource.h"

#include"MathLibrary.h"



#ifndef _WND_OPENGL_PLATFORM_

#include <emscripten.h>

#define _WEB_DEBUG_

#endif



using namespace FW;

CMesh::CMesh(CConstruct* pHost) : CPrimatter(pHost), m_pCurrentSkin(nullptr), 
m_bMajorCompleted(false), m_idCurrentSkin(0), m_pMatGeometry(nullptr), m_pBox(nullptr), 
m_pBound(nullptr), m_pRndUt(nullptr)
{
	m_jMatTmp.Zero();
	m_jMatModelSpace.Identity();
	m_vtSVertex.clear();
	m_vtSNormal.clear();
	m_vtSTangent.clear();
	m_vtUV.clear();
	m_vtVertexAdjSurface.clear();
	m_vtSVertexRlt.clear();
	m_vtSurface.clear();

}

CMesh::CMesh(const char* pszName, CConstruct* pHost) : CPrimatter(pszName, pHost), 
m_pCurrentSkin(nullptr), m_idCurrentSkin(0), m_bMajorCompleted(false), m_pMatGeometry(nullptr), 
m_pBox(nullptr), m_pBound(nullptr), m_pRndUt(nullptr)
{
	m_jMatTmp.Zero();
	m_jMatModelSpace.Identity();
	m_vtSVertex.clear();
	m_vtSNormal.clear();
	m_vtSTangent.clear();
	m_vtUV.clear();
	m_vtVertexAdjSurface.clear();
	m_vtSVertexRlt.clear();
	m_vtSurface.clear();
}


CMesh::~CMesh()
{
	ClearAll();
}


const int SIZE_BUF = 128;
bool CMesh::Initialize(FDWORD id,  const char* pszName, const char* pszNamePathAndFile)
{
	if (!CPrimatter::Initialize(pszName, pszNamePathAndFile))
	{
		return false;
	}

	m_pRndUt = new CRenderUnit(name(), this);
	setID(id);

	char nameBuffer[SIZE_BUF];
	memset(nameBuffer, 0, sizeof(nameBuffer));
	sprintf_s(nameBuffer, "%sBoxRender", name());


	CEssety* pEstMaster = (CEssety*)((CRender*)host()->host())->host();
	CRender* pMBRender = new CRender(nameBuffer, pEstMaster);

	memset(nameBuffer, 0, sizeof(nameBuffer));
	sprintf_s(nameBuffer, "%sBox", name());
	m_pBox = new CBox(nameBuffer, pMBRender);
	if (!m_pBox->Create())
	{
		return false;
	}

	m_pBox->setGen(EGEN::GE_ORG_DT);


	FDWORD idRd = CIDManager::Instance().ApplyID();
	if (0 == idRd)
	{
		return false;
	}

	pMBRender->setID(idRd);
	pMBRender->setComesh(m_pBox);
	pEstMaster->AddSubRender(pMBRender);


	return true;
}


bool CMesh::CreateVertexBufferByOBJFile(const char* pszOBJName, OBJECT* pOBJ)
{
	if (pOBJ == 0)
	{
		return false;
	}

	return true;
}



bool CMesh::CreateVertexBufferByFBXFile(const char* pszOBJName, OBJECT* pOBJ)
{
	if (pOBJ == 0)
	{
		return false;
	}



	return true;
}



bool CMesh::CreateVertexBufferByFWDFile(const char* pszOBJName, OBJECT* pOBJ)
{
	if (pOBJ == 0)
	{
		return false;
	}

	if (!CreateVertexBufferFromEXOBJ(pszOBJName, pOBJ))
	{
		return false;
	}


	if (0 != pOBJ->pMatGeometry)
	{
		m_pMatGeometry = new Matrix4x4;
		*m_pMatGeometry = *(pOBJ->pMatGeometry);
	}

	m_bMajorCompleted = true;

	return true;
}




void CMesh::setMaterial(CMaterial* pMatl)
{
	if (nullptr == m_pRndUt)
	{
		return;
	}

	m_pRndUt->setMaterial(pMatl);
	m_pRndUt->setGroupOrder(pMatl->orderRNDGroup());
	m_pRndUt->setRenderType(pMatl->typeRender());

}


bool CMesh::initializeMaterial(CMaterial* pMaterial)
{
	if (0 == m_pRndUt)
	{
		return false;
	}

	m_pRndUt->setGroupOrder(pMaterial->orderRNDGroup());
	m_pRndUt->setRenderType(pMaterial->typeRender());

	return m_pRndUt->InitializeMaterial(pMaterial);
}




const Vector3& CMesh::BindingBoxCenter()
{
	return m_pBox->center();
}




#define ERROR_CA  0.0000001f
bool EqualUV(float u1, float v1, float u2, float v2)
{
	float du = u1 - u2;
	float dv = v1 - v2;
	return ((-ERROR_CA < du) && (du < ERROR_CA)) && ((-ERROR_CA < dv) && (dv < ERROR_CA));
}


bool CMesh::CreateVertexBufferFromOBJFile(const char* pszMeshName, OBJECT* pOBJ)
{
	return true;
}





void CMesh::ProcessVertexNormal(OBJECT* pOBJ)
{
	if ((0 == pOBJ) || (pOBJ->vertices.empty()))
	{
		return;
	}

	m_vtSNormal.resize(m_vtVertexAdjSurface.size());

	const int LEN = 3;
	SSurface* pSuf = 0;
	int indexSurface = 0;
	for (int i = 0; i < m_vtVertexAdjSurface.size(); i++)
	{
		//caculate all adjacency surface normal average
		int count = m_vtVertexAdjSurface[i].size();
		Vector3* pNormal = new Vector3;

		for (int j = 0; j < count; j++)
		{

			indexSurface = m_vtVertexAdjSurface[i][j];
			pSuf = m_vtSurface[indexSurface];
			for (int n = 0; n < LEN; n++)
			{
				if (pSuf->arIndex[n] == i)
				{
					//accumulate the normal vector
					int indexNormal = pOBJ->surfaces[indexSurface * LEN + n]->_c;

					//Here, the index of normal equal the index of vertex.
					pNormal->x += pOBJ->normals[indexNormal]->x;
					pNormal->y += pOBJ->normals[indexNormal]->y;
					pNormal->z += pOBJ->normals[indexNormal]->z;
				}
			}

		}

		float inverse = 1.0 / count;

		(*pNormal) *= inverse;
		m_vtSNormal[i] = pNormal;
	}
}




void CMesh::ProcessVertexTangent(OBJECT* pOBJ)
{
	if ((0 == pOBJ) || (pOBJ->tangents.empty()))
	{
		return;
	}

	m_vtSTangent.resize(m_vtVertexAdjSurface.size());

	const int LEN = 3;
	int indexSurface = 0;
	SSurface* pSuf = 0;
	for (int i = 0; i < m_vtVertexAdjSurface.size(); i++)
	{
		//caculate all adjacency surface normal average
		int count = m_vtVertexAdjSurface[i].size();
		Vector3* pTangent = new Vector3;

		for (int j = 0; j < count; j++)
		{
			indexSurface = m_vtVertexAdjSurface[i][j];
			pSuf = m_vtSurface[indexSurface];
			for (int n = 0; n < LEN; n++)
			{
				if (pSuf->arIndex[n] == i)
				{
					//accumulate the tangent vector
					//The index of tangent vector3 equal the index of normal vector3.
					int indexTangent = pOBJ->surfaces[indexSurface * LEN + n]->_c;
					pTangent->x += pOBJ->tangents[indexTangent]->x;
					pTangent->y += pOBJ->tangents[indexTangent]->y;
					pTangent->z += pOBJ->tangents[indexTangent]->z;
				}
			}

		}

		float inverse = 1.0 / count;

		(*pTangent) *= inverse;
		m_vtSTangent[i] = pTangent;
	}

}





void CMesh::ProcessVertexUV(OBJECT* pOBJ)
{
	if ((0 == pOBJ) || (pOBJ->uvs.empty()))
	{
		return;
	}

	const int LEN = 3;

	m_vtUV.resize(m_vtVertexAdjSurface.size());


	SSurface* pSuf = 0;
	int indexSurface = 0;
	for (int i = 0; i < m_vtVertexAdjSurface.size(); i++)
	{
		//caculate all adjacency surface normal average
		int count = m_vtVertexAdjSurface[i].size();
		for (int j = 0; j < count; j++)
		{
			indexSurface = m_vtVertexAdjSurface[i][j];
			pSuf = m_vtSurface[indexSurface];
			for (int n = 0; n < LEN; n++)
			{
				if (pSuf->arIndex[n] == i)
				{
					//UV
					unsigned int uvIndex = pOBJ->surfaces[indexSurface * 3 + n]->_b;
					if (!m_vtSVertexRlt[i]->inited)
					{
						m_vtSVertexRlt[i]->index = i;
						m_vtSVertexRlt[i]->uvIndex = uvIndex;
						m_vtSVertexRlt[i]->inited = true;

						Vector2* pUV = new Vector2;
						pUV->x = pOBJ->uvs[uvIndex]->u;
						pUV->y = pOBJ->uvs[uvIndex]->v;
						m_vtUV[i] = pUV;
					}
					else
					{

						//search all relation vertices with current vertex
						bool found = false;
						unsigned int vertexLocation = 0;
						SRelation* work = m_vtSVertexRlt[i];
						SRelation* prevWork = work;
						for (; work != 0; work = work->next)
						{
							prevWork = work;

							//found same uv exist by another surface
							if (work->uvIndex == uvIndex)
							{
								found = true;
								vertexLocation = work->index;
							}
						}

						//The uv of the current vertex in current surface is new. 
						//So, this vertex is "seam vertex".
						if (!found)
						{
							//create new a vertex in m_vtSVertex/m_vtSNormal/m_vtSTangent/m_vtUV
							//with the attribute in m_vtVertexAttrib.
							AppendCloneVertex(i, *pOBJ->uvs[uvIndex]);

							//create new SRelation which point new vertex
							SRelation* newRlt = new SRelation;
							newRlt->inited = true;
							newRlt->index = m_vtSVertex.size() - 1;
							newRlt->uvIndex = uvIndex;
							newRlt->next = 0;

							prevWork->next = newRlt;

							//fix the index of current surface element into new vertex location
							m_vtSurface[indexSurface]->arIndex[n] = newRlt->index;
						}
						else
						{
							m_vtSurface[indexSurface]->arIndex[n] = vertexLocation;
						}
					}
				}
			}

		}

	}
}



void CMesh::AppendCloneVertex(int indexSrc, UV& uv)
{
	if (0 == m_pRndUt)
	{
		return;
	}


	CVertexAttribute* pVA = 0;
	//for (int m = 0; m < m_vtVertexAttrib.size(); m++)
	for(int m=0; m<m_pRndUt->countVertexAttribute(); m++)
	{
		//pVA = m_vtVertexAttrib[m];
		pVA = m_pRndUt->getVertexAttribute(m);

		switch (pVA->typeVertexAttr())
		{
		case EVATYPE::VA_POS:
		{
			Vector3* pvt = new Vector3;
			pvt->x = m_vtSVertex[indexSrc]->x;
			pvt->y = m_vtSVertex[indexSrc]->y;
			pvt->z = m_vtSVertex[indexSrc]->z;
			m_vtSVertex.push_back(pvt);
		}
		break;

		case EVATYPE::VA_NORMAL:
		{
			Vector3* pvt = new Vector3;
			pvt->x = m_vtSNormal[indexSrc]->x;
			pvt->y = m_vtSNormal[indexSrc]->y;
			pvt->z = m_vtSNormal[indexSrc]->z;
			m_vtSNormal.push_back(pvt);
		}
		break;

		case EVATYPE::VA_TANGENT:
		{
			Vector3* pvt = new Vector3;
			pvt->x = m_vtSTangent[indexSrc]->x;
			pvt->y = m_vtSTangent[indexSrc]->y;
			pvt->z = m_vtSTangent[indexSrc]->z;
			m_vtSTangent.push_back(pvt);
		}
		break;

		case EVATYPE::VA_UV:
		{
			Vector2* pUV = new Vector2;
			pUV->x = uv.u;  
			pUV->y = uv.v;  
			m_vtUV.push_back(pUV);
		}
		break;

		default:
			break;
		}
	}
}






bool CMesh::CreateVertexBufferFromEXOBJ(const char* pszMeshName, OBJECT* pOBJ)
{
	if ((0 == pOBJ) || (pOBJ->vertices.size() <= 0))
	{
		return false;
	}

	setName(pszMeshName);

	//Fill invariable vertex attribute set.
	int Offset = 0;
	int sizeFloat = sizeof(float);
	int countComThrice = 3;
	int countComDouble = 2;


	CVertexAttribute* pAttrib = new CVertexAttribute("VertexPos");
	pAttrib->Initialize(EVATYPE::VA_POS, "", countComThrice, sizeFloat, Offset);
	m_pRndUt->AddVertexAttribute(pAttrib);

	Offset += pAttrib->size();


	//Create mesh from pOBJ vertices set & initialize vtVertices.
	for (int i = 0; i < pOBJ->vertices.size(); i++)
	{
		Vertex* pVt = pOBJ->vertices[i];

		Vector3* pSVt = new Vector3;
		pSVt->x = pVt->x;
		pSVt->y = pVt->y;
		pSVt->z = pVt->z;

		m_vtSVertex.push_back(pSVt);

		VTIND vtAdjSurfaces;
		m_vtVertexAdjSurface.push_back(vtAdjSurfaces);

		SRelation* pRlt = new SRelation;
		pRlt->inited = false;
		pRlt->index = 0;
		pRlt->uvIndex = 0;
		pRlt->next = 0;
		m_vtSVertexRlt.push_back(pRlt);
	}


	for (int i = 0; i < pOBJ->surfaces.size(); i += 3)
	{
		SSurface* pSS = new SSurface();

		pSS->_v0 = pOBJ->surfaces[i]->_a;
		pSS->_v1 = pOBJ->surfaces[i + 1]->_a;
		pSS->_v2 = pOBJ->surfaces[i + 2]->_a;

		m_vtSurface.push_back(pSS);
	}


	//collect each vertex adjacency surfaces
	const int LEN = 3;
	SSurface* psuf = 0;

	for (int i = 0; i < m_vtSurface.size(); i++)
	{
		psuf = m_vtSurface[i];
		for (int n = 0; n < LEN; n++)
		{
			//get the adjacency surface of the vertex.
			m_vtVertexAdjSurface[psuf->arIndex[n]].push_back(i);
		}
	}


	//has normal data
	if (pOBJ->normals.size() > 0)
	{
		pAttrib = new CVertexAttribute("VertexNormal");
		pAttrib->Initialize(EVATYPE::VA_NORMAL, "", countComThrice, sizeFloat, Offset);
		m_pRndUt->AddVertexAttribute(pAttrib);
		Offset += pAttrib->size();

		ProcessVertexNormal(pOBJ);
	}


	//has tangent data
	if (pOBJ->tangents.size() > 0)
	{
		pAttrib = new CVertexAttribute("VertexTangent");
		pAttrib->Initialize(EVATYPE::VA_TANGENT, "", countComThrice, sizeFloat, Offset);
		m_pRndUt->AddVertexAttribute(pAttrib);
		Offset += pAttrib->size();

		ProcessVertexTangent(pOBJ);
	}



	//has UV data
	if (pOBJ->uvs.size() > 0)
	{
		pAttrib = new CVertexAttribute("VertexUV");
		pAttrib->Initialize(EVATYPE::VA_UV, "", countComDouble, sizeof(unsigned int), Offset);
		m_pRndUt->AddVertexAttribute(pAttrib);
		ProcessVertexUV(pOBJ);
	}

	m_vtVertexAdjSurface.clear();


	return CreateOutputBuffer();
}





bool CMesh::CreateOutputBuffer()
{
	if(m_vtSVertex.empty() || m_vtSurface.empty() || m_pRndUt == 0)
	{
		return false;
	}

	m_pRndUt->Initialize(m_vtSVertex.size(), m_vtSurface.size());

	//process vertices
	int index = 0;
	//Vector3 v3Max, v3Min;
	CVertexAttribute* pVA = 0;
	int countVertex = m_vtSVertex.size();
	bool bInit = false;
	for (int i = 0; i < countVertex; i++)
	{
		for(int j = 0; j < m_pRndUt->countVertexAttribute(); j++)
		{
			pVA = m_pRndUt->getVertexAttribute(j);
			switch (pVA->typeVertexAttr())
			{
			case EVATYPE::VA_POS:
			{
				Vector3* pSV = m_vtSVertex[i];

				if (!bInit)
				{
					for (int m = 0; m < pVA->count(); m++)
					{
						m_v3MaxMS.c[m] = m_v3MinMS.c[m] = pSV->c[m];
					}

					bInit = true;
				}

				for (int m = 0; m < pVA->count(); m++)
				{
					m_pRndUt->InitializeVertexData(index, pSV->c[m]);
					index++;

					float val = pSV->c[m];
					m_v3MinMS.c[m] = val < m_v3MinMS.c[m] ? val : m_v3MinMS.c[m];
					m_v3MaxMS.c[m] = val > m_v3MaxMS.c[m] ? val : m_v3MaxMS.c[m];

				}
			}
			break;

			case EVATYPE::VA_NORMAL:
			{
				Vector3* pSN = m_vtSNormal[i];
				for (int m = 0; m < pVA->count(); m++)
				{
					m_pRndUt->InitializeVertexData(index, pSN->c[m]);
					index++;
				}
			}
			break;

			case EVATYPE::VA_TANGENT:
			{
				Vector3* pST = m_vtSTangent[i];
				for (int m = 0; m < pVA->count(); m++)
				{
					m_pRndUt->InitializeVertexData(index, pST->c[m]);
					index++;
				}
			}
			break;

			case EVATYPE::VA_UV:
			{
				Vector2* pUV = m_vtUV[i];
				for (int m = 0; m < pVA->count(); m++)
				{
					m_pRndUt->InitializeVertexData(index, pUV->c[m]);
					index++;
				}
			}
			break;

			default:
			{
				ClearAll();
				return false;
			}
			break;
			}
		}
	}


	//process the index of the vertex
	index = -1;
	SSurface* pSF = 0;
	for (VTSSF::iterator iter = m_vtSurface.begin(); iter != m_vtSurface.end(); ++iter)
	{
		pSF = (*iter);
		m_pRndUt->setIndexData(++index, pSF->_v0);
		m_pRndUt->setIndexData(++index, pSF->_v1);
		m_pRndUt->setIndexData(++index, pSF->_v2);
	}


	//create bound
	if (nullptr == m_pBound)
	{
		m_pBound = new CBound(this);
		//m_pBound->Create(v3Max, v3Min);
		Vector3 pos = (m_v3MaxMS + m_v3MinMS) * 0.5f;
		m_pBound->Create(m_v3MaxMS, m_v3MinMS, pos);
	}



#ifdef _WEB_DEBUG_
	EM_ASM({ console.log("create mesh successful! name is:" + UTF8ToString($0)); }, (char*)name());
#endif

	return true;
}




void CMesh::ClearAll()
{
	m_pHost = nullptr;
	if (nullptr != m_pBound)
	{
		delete m_pBound;
		m_pBound = nullptr;
	}

	if (nullptr != m_pCurrentSkin)
	{
		IDataResource* pIDR = CreateDataResource();
		if (m_pCurrentSkin->gen() == EGEN::GE_ORG_PM)
		{
			if (pIDR->CheckValidRes(m_idCurrentSkin))
			{
				delete m_pCurrentSkin;
				m_idCurrentSkin = 0;
			}
		}
		else
		{
			delete m_pCurrentSkin;
		}

		m_pCurrentSkin = nullptr;

	}

	//Just set null, because the host in the m_vtSubRender has been deleted. 
	m_pBox = nullptr;


	Destroy();
}



void CMesh::Update(CEssety* pEssety)
{
	if (nullptr == pEssety)
	{
		return;
	}

	CVertexAttribute* pVA = nullptr;

	//CTime::Instance().BlockTestBegin();
	if (nullptr != m_pCurrentSkin)
	{
		m_pCurrentSkin->Update(this);
	}
	else
	{
		if (nullptr != m_pBox)
		{
			int countVertex = m_vtSVertex.size();
			
			//bool bInit = false;
			for (int j = 0; j < m_pRndUt->countVertexAttribute(); j++)
			{
				pVA = m_pRndUt->getVertexAttribute(j);
				if (pVA->typeVertexAttr() == EVATYPE::VA_POS)
				{
					for (int i = 0; i < countVertex; i++)
					{
						Vector3* pSV = m_vtSVertex[i];
						for (int m = 0; m < pVA->count(); m++)
						{
							m_v3MaxMS.c[m] = m_v3MaxMS.c[m] < pSV->c[m] ? pSV->c[m] : m_v3MaxMS.c[m];
							m_v3MinMS.c[m] = m_v3MinMS.c[m] > pSV->c[m] ? pSV->c[m] : m_v3MinMS.c[m];
						}
					}

					break;
				}
			}

			m_pBox->OnAreaUpdate(m_v3MaxMS, m_v3MinMS, ((CSceneNode*)pEssety->host())->spaceWorld()->matOutput());

		}
	}

	
	//move into CComesh ??
	if (nullptr != m_pRndUt)
	{
		//debug code
		if (strcmp(name(), "Horse") == 0)
		{
			int i = 0;
		}


		m_jMatTmp = ((CSceneNode*)pEssety->host())->spaceWorld()->matOutput();

		m_pRndUt->matWorld() = m_jMatTmp;
	}
	
}



Vector3 v3TmpPos;
Vector3 v3TmpNormal;
Vector3 v3TmpTangent;

Vector4 v4TmpPos;
Vector4 v4TmpNormal;
Vector4 v4TmpTangent;


Vector4 v4SrcPos;
Vector4 v4TargetPos;


Matrix4x4 mat4x4Tmp;
void CMesh::OnUpdateOutputVertices(VTSSKF& vtControlVertex)
{
	if (0 == m_pRndUt)
	{
		return;
	}


	unsigned int index = 0;
	unsigned int local = 0;

	m_v3MaxMS.Clean();
	m_v3MinMS.Clean();

	bool bInit = false;

	//update output array by m_vtLinearDef
	for (VTSSKF_ITER iter = vtControlVertex.begin(); iter != vtControlVertex.end(); ++iter)
	{
		index = (*iter)->indexVt ;
		local = index * m_pRndUt->countVertexComponent();
		v4SrcPos.x = m_pRndUt->valueOrignalVT(local);
		v4SrcPos.y = m_pRndUt->valueOrignalVT(local + 1);
		v4SrcPos.z = m_pRndUt->valueOrignalVT(local + 2);
		v4SrcPos.w = 1.0f;

		v4TargetPos = Mul4(v4SrcPos, *((*iter)->mat));
		v4TargetPos *= (*iter)->weight;

		m_pRndUt->setVertexData(local, v4TargetPos.x);
		m_pRndUt->setVertexData(local + 1, v4TargetPos.y);
		m_pRndUt->setVertexData(local + 2, v4TargetPos.z);

		if (!bInit)
		{
			m_v3MaxMS = v4TargetPos.v3;
			m_v3MinMS = v4TargetPos.v3;

			bInit = true;
		}

		//preprocess for AABB
		for (int i = 0; i < 3; i++)
		{
			if (v4TargetPos.c[i] < m_v3MinMS.c[i])
			{
				m_v3MinMS.c[i] = v4TargetPos.c[i];
			}
			else if (v4TargetPos.c[i] > m_v3MaxMS.c[i])
			{
				m_v3MaxMS.c[i] = v4TargetPos.c[i];
			}

		}


		SRelation* pRlt = m_vtSVertexRlt[index];

		//Determine whether or not the current vertex is seam vertex
		//and process its.
		if (pRlt->inited)
		{
			SRelation* pWork = pRlt;

			while (pWork != 0)
			{
				local = pWork->index * 11;

				v4SrcPos.x = m_pRndUt->valueOrignalVT(local);
				v4SrcPos.y = m_pRndUt->valueOrignalVT(local + 1);
				v4SrcPos.z = m_pRndUt->valueOrignalVT(local + 2);

				v4SrcPos.w = 1.0f;

				v4TargetPos = Mul4(v4SrcPos, *((*iter)->mat));
				v4TargetPos = v4TargetPos * (*iter)->weight;

				m_pRndUt->setVertexData(local, v4TargetPos.x);
				m_pRndUt->setVertexData(local + 1, v4TargetPos.y);
				m_pRndUt->setVertexData(local + 2, v4TargetPos.z);

				pWork = pWork->next;
			}
		}

	}


	mat4x4Tmp.Identity();

	if (0 != m_pBox)
	{
		m_pBox->OnAreaUpdate(m_v3MaxMS, m_v3MinMS, m_pRndUt->matWorld());
	}
}




void CMesh::Destroy()
{
	CIDManager::Instance().RemoveID(id());


	if (nullptr != m_pMatGeometry)
	{
		delete m_pMatGeometry;
		m_pMatGeometry = nullptr;
	}

	if (nullptr != m_pRndUt)
	{
		delete m_pRndUt;
		m_pRndUt = nullptr;
	}


	for (VTVC3_ITER iter = m_vtSVertex.begin(); iter != m_vtSVertex.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
		}
	}
	m_vtSVertex.clear();


	for (VTVC3_ITER iter = m_vtSNormal.begin(); iter != m_vtSNormal.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
		}
	}
	m_vtSNormal.clear();


	for (VTVC3_ITER iter = m_vtSTangent.begin(); iter != m_vtSTangent.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete *iter;
		}
	}
	m_vtSTangent.clear();


	for (VTVC2_ITER iter = m_vtUV.begin(); iter != m_vtUV.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete *iter;
		}
	}
	m_vtUV.clear();


	m_vtVertexAdjSurface.clear();


	for (VTSRT_ITER iter = m_vtSVertexRlt.begin(); iter != m_vtSVertexRlt.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete *iter;
		}
	}
	m_vtSVertexRlt.clear();


	for (VTSSF::iterator iter = m_vtSurface.begin(); iter != m_vtSurface.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
		}
	}
	m_vtSurface.clear();
}





bool CMesh::RegisterBox(CBox* pBox)
{
	if (nullptr != m_pBox)
	{
		return false;
	}

	m_pBox = pBox;

	return true;
}
