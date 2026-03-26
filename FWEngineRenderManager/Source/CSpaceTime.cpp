#include"FWEnginePrimatterManagerExport.h"
#include"CSpaceTime.h"
#include"CRender.h"
#include"CCamera.h"
#include"CDirectLight.h"
#include"CSceneNode.h"
#include"CRenderUnitGroup.h"
#include"CRenderUnit.h"
#include"CMesh.h"
#include"CMaterial.h"


using namespace FW;

const int DEFAULT_OPACITY_ORDER = 100;
const int DEFAULT_TRANSPARENT_ORDER = 500;


CSpaceTime::CSpaceTime(): m_nSpaceOrder(-1), m_nTimeOrder(-1), m_dwSpaceTimeID(0)
{
}

CSpaceTime::~CSpaceTime()
{
}


bool CSpaceTime::Create(int orderSpace, int orderTime)
{
	if ((orderSpace < 0) || (orderTime < 0))
	{
		return false;
	}

	m_nSpaceOrder = orderSpace;
	m_nTimeOrder = orderTime;
	m_dwSpaceTimeID = CreateSpaceTimeID(m_nSpaceOrder, m_nTimeOrder);

	Create();

	return true;
}



bool CSpaceTime::Create(FDWORD idSpaceTime)
{
	m_nSpaceOrder = GetSpaceOrderFromSTID(idSpaceTime);
	m_nTimeOrder = GetTimeOrderFromSTID(idSpaceTime);
	m_dwSpaceTimeID = idSpaceTime;

	Create();

	return true;
}


void CSpaceTime::Create()
{
	//first opacity render unit group
	CRenderUnitGroup* pRenderUtGp = new CRenderUnitGroup();
	pRenderUtGp->setOrder(DEFAULT_OPACITY_ORDER);
	pRenderUtGp->setRenderType(ERNDTYPE::RT_OPACITY);
	m_lstRenderUtGroup.push_back(pRenderUtGp);
	m_pDefaultOpacityGroup = pRenderUtGp;

	//first transparent render unit group
	pRenderUtGp = new CRenderUnitGroup();
	pRenderUtGp->setOrder(DEFAULT_TRANSPARENT_ORDER);
	pRenderUtGp->setRenderType(ERNDTYPE::RT_TRANSPARENT);
	m_lstRenderUtGroup.push_back(pRenderUtGp);
}



void CSpaceTime::Grouping()
{
	//Assign render unit into a group by the group order or render type
	CRender* pRender = 0;
	CRenderUnit* pRndUt = 0;
	int countMesh = 0;
	CRenderUnitGroup* pRndGp = 0;
	CMesh* pMesh = 0;
	CPrimatter* pPmt = 0;

	for (VTRENDER_ITER iter = m_vtRenders.begin(); iter != m_vtRenders.end(); ++iter)
	{
		pRender = *iter;
		//if (strcmp(pRender->name(), "HorseRender") == 0)
		//{
		//	continue;
		//}


		countMesh = pRender->comesh()->countMesh();
		for (int i = 0; i < countMesh; i++)
		{
			pRndUt = pRender->comesh()->mesh(i)->renderUnit();
			if (0 != pRndUt)
			{
				pRndGp = FindRenderUnitGroup(pRndUt->material()->orderRNDGroup());
				if (pRndGp == 0)
				{
					pRndGp = new CRenderUnitGroup();
					pRndGp->setOrder(pRndUt->material()->orderRNDGroup());

					pRndGp->setRenderType(pRndUt->material()->typeRender());
					InsertRenderUnitGroup(pRndGp);
				}

				pRndGp->AddRenderUnit(pRndUt);
			}
		}
	}
}





void CSpaceTime::Update(CCamera* pCamera, VTLIT* pLightArray)
{
	CSceneNode* pCamSND = (CSceneNode*)pCamera->host();
	CRenderUnitGroup* pRenderGp = 0;

	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		pRenderGp = *iter;
		if ((0 != pRenderGp) && (!pRenderGp->emptyRenderUnit()))
		{
			pRenderGp->MergeWithMaterial(pCamera);
			pRenderGp->UpdateCameraLightParameter(pCamera, *pLightArray);
		}
	}

	//rendering into bounded screen
	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		pRenderGp = *iter;
		if ((0 != pRenderGp) && (!pRenderGp->emptyRenderUnit()))
		{
			pRenderGp->Rendering();
		}
	}

	ClearRenderUnitListEachGroup();
}






CRenderUnitGroup* CSpaceTime::FindRenderUnitGroup(int order)
{
	if (order < 0)
	{
		return 0;
	}

	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if ((*iter)->order() == order)
		{
			return (*iter);
		}
	}

	return 0;
}



void CSpaceTime::Clear()
{
	m_vtRenders.clear();

	CRenderUnitGroup* pRgp = 0;
	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		pRgp = *iter;
		if (!pRgp->emptyRenderUnit())
		{
			pRgp->CleanAll();
			//delete pRgp;
		}
	}

	//m_lstRenderUtGroup.clear();
}




void CSpaceTime::ClearRenderUnitListEachGroup()
{
	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if (!(*iter)->emptyRenderUnit())
		{
			(*iter)->ClearRenderUnitList();
		}
	}
}






void CSpaceTime::InsertRenderUnitGroup(CRenderUnitGroup* pRndUtGp)
{
	if (m_lstRenderUtGroup.empty())
	{
		m_lstRenderUtGroup.push_back(pRndUtGp);
		return;
	}

	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if (pRndUtGp->order() < (*iter)->order())
		{
			m_lstRenderUtGroup.push_front(pRndUtGp);
			break;
		}
	}
}