#include"CRenderUnitList.h"
#include"CRenderUnit.h"
#include"CMaterial.h"
#include"CPass.h"
#include"CProgram.h"
//#include"CBorder.h"
#include"CMesh.h"

using namespace FW;



CRenderUnitList::CRenderUnitList():m_pMatlShare(0)
{
	m_lstRenderUt.clear();
}

CRenderUnitList::~CRenderUnitList()
{
	m_pMatlShare = 0;
	m_lstRenderUt.clear();
}

void CRenderUnitList::Rendering()
{
	if (0 == m_pMatlShare)
	{
		return;
	}


	for (int i = 0; i < m_pMatlShare->countPass(); i++)
	{
		if (m_pMatlShare->BindPass(i))
		{
			for (LTRNDUT_ITER iter = m_lstRenderUt.begin(); iter != m_lstRenderUt.end(); ++iter)
			{
				(*iter)->Rendering(m_pMatlShare, i);
			}
		}
	}

	
}


void CRenderUnitList::UpdateCameraLightParameter(CCamera* pCam, VTLIT& vtLights)
{
	for (int i = 0; i < m_pMatlShare->countPass(); i++)
	{
		m_pMatlShare->pass(i)->program()->UpdateCameraLight(pCam, vtLights);
	}
}