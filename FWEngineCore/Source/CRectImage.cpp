#include"CRectImage.h"
#include"CRect.h"
#include"IDataResource.h"
#include"CMaterial.h"
#include"CProgram.h"
#include"CParameterUniform.h"
#include"CRectMesh.h"
#include"CRenderUnit.h"
#include"CPass.h"

using namespace FW;


CRectImage::~CRectImage()
{
	Destroy();
}



bool CRectImage::Create(Vector3& lt, Vector3& hor, Vector3& ver, const char* pszFileNameMatl, 
	const char* pszNameMatl, URect* pRectUV /*= nullptr*/)
{
	if (nullptr != m_pRect)
	{
		delete m_pRect;
	}

	m_pRect = new CRect();
	Vector3 rt = lt + hor;
	Vector3 rb = lt + hor + ver;

	m_pRect->Create(lt, rt, rb);

	
	CRectMesh* pRectMsh = new CRectMesh(this);
	if (!pRectMsh->Create(m_pRect, pszFileNameMatl, pszNameMatl, pRectUV))
	{
		Destroy();
		return false;
	}


	AddMesh(pRectMsh);


	m_v3MaxMS = pRectMsh->max();
	m_v3MinMS = pRectMsh->min();

	return true;
}



void CRectImage::ActiveTexture(int indMesh, int indTex)
{
	if ((indMesh < 0) || (indMesh >= countMesh()))
	{
		return;
	}

	CRectMesh* pMsh = (CRectMesh*)mesh(indMesh);
	if (pMsh == nullptr)
	{
		return;
	}

	pMsh->ActiveTexture(indTex);

}




void CRectImage::UpdateUV(URect* pRectUV)
{
	CRectMesh* pMsh = (CRectMesh*)mesh(0);
	if (nullptr != pMsh)
	{
		pMsh->UpdateUV(pRectUV);
	}
}



void CRectImage::Update(CEssety* pEssety)
{
	if (m_vtMesh.empty())
	{
		return;
	}

	
	m_v3MaxWS = ((CRectMesh*)m_vtMesh[0]->pMesh)->maxWS();
	m_v3MinWS = ((CRectMesh*)m_vtMesh[0]->pMesh)->minWS();

	CRectMesh* pRtMesh = nullptr;
	for (VTMESH_ITER iter = m_vtMesh.begin(); iter != m_vtMesh.end(); ++iter)
	{
		pRtMesh = (CRectMesh*)(*iter)->pMesh;

		if (nullptr != pRtMesh)
		{
			for (int i = 0; i < 3; i++)
			{
				m_v3MaxWS.c[i] = m_v3MaxWS.c[i] < pRtMesh->maxWS().c[i] ? pRtMesh->maxWS().c[i] : m_v3MaxWS.c[i];
				m_v3MinWS.c[i] = m_v3MinWS.c[i] > pRtMesh->minWS().c[i] ? pRtMesh->minWS().c[i] : m_v3MinMS.c[i];
			}
		}

	}

	pRtMesh = (CRectMesh*)m_vtMesh[0];
	if (pRtMesh != nullptr)
	{
		Vector3 cnt = (m_v3MaxWS + m_v3MinWS) * 0.5f;
		pRtMesh->setCenterBound(cnt);
	}

}





void CRectImage::Destroy()
{
	if (nullptr != m_pRect)
	{
		delete m_pRect;
		m_pRect = nullptr;
	}

}