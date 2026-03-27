#include"CRectMesh.h"
#include"CRect.h"
#include"CPass.h"
#include"CProgram.h"
#include"CVertexAttribute.h"
#include"CMaterial.h"
#include"CTextureUnit.h"
#include"CRenderUnitRect.h"
#include"IDataResource.h"

using namespace FW;


CRectMesh::CRectMesh(CConstruct* pHost) :CMesh(pHost)
{
}


CRectMesh::CRectMesh(const char* pszName, CConstruct* pHost) :CMesh(pszName, pHost)
{
}


CRectMesh::~CRectMesh()
{

}




bool CRectMesh::CreateTest(CRect* pRect, const char* pszNameFileMatl, const char* pszNameMatl, URect* pRectUV /*= nullptr*/)
{
	if ((nullptr != m_pRndUt) || (nullptr == pRect)
		|| (nullptr == pszNameFileMatl) || (nullptr == pszNameMatl))
	{
		return false;
	}


	//set material
	IDataResource* pIDR = CreateDataResource();
	CMaterial* pMatl = pIDR->TakeMatrial(pszNameFileMatl, pszNameMatl);
	if (nullptr == pMatl)
	{
		Destroy();
		return false;
	}

	setMaterial(pMatl);


	//set vertex attribute of the RenderUnit
	int Offset = 0;
	int sizeFloat = sizeof(float);
	int countComThrice = 3;
	int countComDouble = 2;

	CPass* pPass = nullptr;
	CVertexAttribute* pAttrib = nullptr;
	CVertexAttribute* pAttribSrc = nullptr;
	int offset = 0;
	for (int i = 0; i < pMatl->countPass(); i++)
	{
		pPass = pMatl->pass(i);
		for (int n = 0; n < pPass->program()->countVertexAttribute(); n++)
		{

			pAttribSrc = pPass->program()->vertexAttr(n);
			pAttribSrc->setLocal(offset);

			pAttrib = new CVertexAttribute;
			if (!pAttrib->Copy(pAttribSrc))
			{
				Destroy();
				return false;
			}

			//m_pRndUt->AddVertexAttribute(pAttrib);

			offset += pAttribSrc->size();
		}
	}


	//Active texture only one!
	CParameterUniform* pPam = nullptr;
	int countText = 0;
	for (int i = 0; i < pMatl->countPass(); i++)
	{
		pPass = pMatl->pass(i);
		for (int n = 0; n < pPass->program()->countParaUniform(); n++)
		{
			pPam = pPass->program()->paraUniform(n);
			if (pPam->typeShaderUniform() == ESUTYPE::SU_TEXTURE)
			{
				pPam->setActive((countText == 0) ? true : false);
				countText++;
			}
		}

	}


	//create mesh and set RenderUnit
	m_v3MaxMS = *pRect->vertex(0);
	m_v3MinMS = *pRect->vertex(0);

	for (int i = 0; i < pRect->count(); i++)
	{
		Vector3* pPos = new Vector3(pRect->vertex(i)->x, pRect->vertex(i)->y, pRect->vertex(i)->z);
		m_vtSVertex.push_back(pPos);

		for (int m = 0; m < 3; m++)
		{
			if (pPos->c[m] < m_v3MinMS.c[m])
			{
				m_v3MinMS.c[m] = pPos->c[m];

				//temp
				//m_v3MinWS.c[m] = pPos->c[m];
			}

			if (pPos->c[m] > m_v3MaxMS.c[m])
			{
				m_v3MaxMS.c[m] = pPos->c[m];

				//temp
				//m_v3MaxWS.c[m] = pPos->c[m];
			}
		}
	}

	//m_v3Center = (m_v3MaxMS + m_v3MinMS) * 0.5f;


	return true;
}




bool CRectMesh::Create(CRect* pRect, const char* pszNameFileMatl, const char* pszNameMatl, URect* pRectUV /* = nullptr*/)
{
	if ((nullptr != m_pRndUt) || (nullptr == pRect) || (nullptr == pszNameFileMatl) || (nullptr == pszNameMatl))
	{
		return false;
	}


	//create RenderUnit 
	m_pRndUt = new CRenderUnitRect(name(), this);

	
	//set material
	IDataResource* pIDR = CreateDataResource();
	CMaterial* pMatl = pIDR->TakeMatrial(pszNameFileMatl, pszNameMatl);
	if (nullptr == pMatl)
	{
		Destroy();
		return false;
	}
	

	setMaterial(pMatl);


	//set vertex attribute of the RenderUnit
	int Offset = 0;
	int sizeFloat = sizeof(float);
	int countComThrice = 3;
	int countComDouble = 2;

	CPass* pPass = nullptr;
	CVertexAttribute* pAttrib = nullptr;
	CVertexAttribute* pAttribSrc = nullptr;
	int offset = 0;
	for (int i = 0; i < pMatl->countPass(); i++)
	{
		pPass = pMatl->pass(i);
		for (int n = 0; n < pPass->program()->countVertexAttribute(); n++)
		{

			pAttribSrc = pPass->program()->vertexAttr(n);
			pAttribSrc->setLocal(offset);

			pAttrib = new CVertexAttribute;
			if (!pAttrib->Copy(pAttribSrc))
			{
				Destroy();
				return false;
			}

			//pAttrib->Initialize(pAttribSrc->typeVertexAttr(), pAttribSrc->varName(), pAttribSrc->count(), 
			//	pAttribSrc->sizeComponent(), offset);
			m_pRndUt->AddVertexAttribute(pAttrib);

			offset += pAttribSrc->size();
		}
	}


	//Active texture only one!
	CParameterUniform* pPam = nullptr;
	int countText = 0;
	for (int i = 0; i < pMatl->countPass(); i++)
	{
		pPass = pMatl->pass(i);
		for (int n = 0; n < pPass->program()->countParaUniform(); n++)
		{
			pPam = pPass->program()->paraUniform(n);
			if (pPam->typeShaderUniform() == ESUTYPE::SU_TEXTURE)
			{
				pPam->setActive((countText == 0) ? true : false);
				countText++;
			}
		}

	}




	//temp
	//create mesh and set RenderUnit
	m_v3MaxMS = *pRect->vertex(0);
	m_v3MinMS = *pRect->vertex(0);

	for (int i = 0; i < pRect->count(); i++)
	{
		Vector3* pPos = new Vector3(pRect->vertex(i)->x, pRect->vertex(i)->y, pRect->vertex(i)->z);
		m_vtSVertex.push_back(pPos);

		for (int m = 0; m < 3; m++)
		{
			if (pPos->c[m] < m_v3MinMS.c[m])
			{
				m_v3MinMS.c[m] = pPos->c[m];

				//temp
				m_v3MinWS.c[m] = pPos->c[m];
			}

			if (pPos->c[m] > m_v3MaxMS.c[m])
			{
				m_v3MaxMS.c[m] = pPos->c[m];

				//temp
				m_v3MaxWS.c[m] = pPos->c[m];
			}
		}
	}

	m_v3Center = (m_v3MaxMS + m_v3MinMS) * 0.5f;


	if (nullptr == pRectUV)
	{
		Vector2* pUV = new Vector2(1.0f, 1.0f);
		m_vtUV.push_back(pUV);

		pUV = new Vector2(0.0f, 1.0f);
		m_vtUV.push_back(pUV);

		pUV = new Vector2(0.0f, 0.0f);
		m_vtUV.push_back(pUV);

		pUV = new Vector2(1.0f, 0.0f);
		m_vtUV.push_back(pUV);
	}
	else
	{
		Vector2*  pUV = new Vector2(pRectUV->fx + pRectUV->fw, pRectUV->fy);
		m_vtUV.push_back(pUV);

		pUV = new Vector2(pRectUV->fx, pRectUV->fy);
		m_vtUV.push_back(pUV);

		pUV = new Vector2(pRectUV->fx, pRectUV->fy - pRectUV->fh);
		m_vtUV.push_back(pUV);

		pUV = new Vector2(pRectUV->fx + pRectUV->fw, pRectUV->fy - pRectUV->fh);
		m_vtUV.push_back(pUV);

		
	}




	SSurface* pSuf = new SSurface;
	pSuf->_v0 = 0;
	pSuf->_v1 = 2;
	pSuf->_v2 = 1;
	m_vtSurface.push_back(pSuf);

	pSuf = new SSurface;
	pSuf->_v0 = 0;
	pSuf->_v1 = 3;
	pSuf->_v2 = 2;
	m_vtSurface.push_back(pSuf);

	m_pRndUt->Initialize(m_vtSVertex.size(), m_vtSurface.size());


	
	int index = -1;
	for (int i = 0; i < m_vtSVertex.size(); i++)
	{
		m_pRndUt->setVertexData(++index, m_vtSVertex[i]->x);
		m_pRndUt->setVertexData(++index, m_vtSVertex[i]->y);
		m_pRndUt->setVertexData(++index, m_vtSVertex[i]->z);
		m_pRndUt->setVertexData(++index, m_vtUV[i]->x);
		m_pRndUt->setVertexData(++index, m_vtUV[i]->y);
	}



	index = -1;
	for (int i = 0; i < m_vtSurface.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_pRndUt->setIndexData(++index, m_vtSurface[i]->arIndex[j]);
		}
	}




	return true;
}




void CRectMesh::ActiveTexture(int indTex)
{
	if (indTex < 0)
	{
		return;
	}

	CMaterial* pMat = m_pRndUt->material();
	CProgram* pProgram = nullptr;
	for (int n = 0; n < pMat->countPass(); n++)
	{
		pProgram = pMat->pass(n)->program();
		for (int m = 0; m < pProgram->countParaUniform(); m++)
		{
			if (pProgram->paraUniform(m)->typeShaderUniform() == ESUTYPE::SU_TEXTURE)
			{
				CParaUniformTexture* pPUTexture = (CParaUniformTexture*)pProgram->paraUniform(m);
				pPUTexture->setActive(indTex == pPUTexture->indexOfTextureArray());
			}

		}
	}
}




void CRectMesh::UpdateUV(URect* pRectUV)
{
	if (nullptr == pRectUV)
	{
		return;
	}

	int index = 3;
	for (int i = 0; i < CRect::count(); i++)
	{
		m_vtUV[i]->x = pRectUV->fx + pRectUV->fw * ((i + 1) / 2);
		m_vtUV[i]->y = pRectUV->fy + pRectUV->fh * (i / 2);

		m_pRndUt->setVertexData(index, m_vtUV[i]->x);
		m_pRndUt->setVertexData(++index, m_vtUV[i]->y);
		index += 5;
	}
}

