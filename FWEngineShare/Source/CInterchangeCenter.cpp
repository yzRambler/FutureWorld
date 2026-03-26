#include"CInterchangeCenter.h"
#include"CConstruct.h"
#include"CMsgCenter.h"
//#include"CComponent.h"
#include"CUI.h"
#include"CUIMsgListener.h"


using namespace FW;


CInterchangeCenter* CInterchangeCenter::m_pInst = nullptr;

CInterchangeCenter::CInterchangeCenter()
{
	//Just Remove, Don't Delete.
	m_mapTarget.clear();
	m_mapConstruct.clear();
}


CInterchangeCenter::~CInterchangeCenter()
{
}


void CInterchangeCenter::AddTarget(CICTarget* pTag)
{
	if(nullptr == pTag)
	{
		return;
	}

	if(m_mapTarget.find(pTag->typeTag()) != m_mapTarget.end())
	{
		return;
	}

	m_mapTarget[pTag->typeTag()] = pTag;
}



void CInterchangeCenter::RemoveTarget(EICTAGTYPE type)
{
	//Note: Just remove, don't Delete it.
	MAPTAG_ITER iter = m_mapTarget.find(type);
	if (iter != m_mapTarget.end())
	{
		m_mapTarget.erase(iter);
	}
}


void CInterchangeCenter::AddApplication(CConstruct* pCst)
{
	if ((nullptr == pCst) || (pCst->id() == 0))
	{
		return;
	}

	if (m_mapConstruct.find(pCst->id()) != m_mapConstruct.end())
	{
		return;
	}

	m_mapConstruct[pCst->id()] = pCst;

	//For extending
	if (m_mapTarget.find((EICTAGTYPE)pCst->idIntTarget()) != m_mapTarget.end())
	{
		//CMsgCenter* pMC = (CMsgCenter*)m_mapTarget[pCst->idIntTarget()];
		//if (pCst->typeCST() == ECONSTRTYPE::CST_COMPONENT)
		//{
		//	CComponent* pCmp = (CComponent*)pCst;
		//	if (pCmp->type() == ECOMTYPE::CO_UI)
		//	{
		//		CUI* pUI = (CUI*)pCst;

		//		pMC->RegisterLst((IMsgListener*)pUI->listener());

		//	}
		//}

		CICTarget* pTag = m_mapTarget[(EICTAGTYPE)pCst->idIntTarget()];

		switch (pCst->typeCST())
		{
		case ECONSTRTYPE::CST_COMPONENT:
		{
			CComponent* pCmp = (CComponent*)pCst;
			if (pCmp->type() == ECOMTYPE::CO_UI)
			{
				CUI* pUI = (CUI*)pCst;
				pTag->RegisterLst((CListener*)pUI->listener());
			}
		}
		break;

		case ECONSTRTYPE::CST_LISTERNER:
		{
			pTag->RegisterLst((CListener*)pCst);
		}
		break;

		default:
			break;
		}

		
	}
}


void CInterchangeCenter::RemoveApplication(CConstruct* pCst)
{
	if (nullptr == pCst)
	{
		return;
	}

	MAPTAG_ITER iter = m_mapTarget.find((EICTAGTYPE)pCst->idIntTarget());
	if (iter != m_mapTarget.end())
	{
		////temporary code
		//CMsgCenter* pMC = (CMsgCenter*)m_mapTarget[pCst->idIntTarget()];
		//if (pCst->typeCST() == ECONSTRTYPE::CST_COMPONENT)
		//{
		//	CComponent* pCmp = (CComponent*)pCst;
		//	if (pCmp->type() == ECOMTYPE::CO_UI)
		//	{
		//		CUI* pUI = (CUI*)pCst;
		//		pMC->UnregisterLst((IMsgListener*)pUI->listener());
		//	}
		//}

		CICTarget* pTag = m_mapTarget[(EICTAGTYPE)pCst->idIntTarget()];
		if (pCst->typeCST() == ECONSTRTYPE::CST_COMPONENT)
		{
			CComponent* pCmp = (CComponent*)pCst;
			if (pCmp->type() == ECOMTYPE::CO_UI)
			{
				CUI* pUI = (CUI*)pCst;
				pTag->UnregisterLst((CListener*)pUI->listener());
			}
		}
	}


	//Note: Just remove, don't Delete it.
	MAPCST_ITER iterCst = m_mapConstruct.find(pCst->id());
	if (iterCst != m_mapConstruct.end())
	{
		m_mapConstruct.erase(iterCst);
	}
}



void CInterchangeCenter::Update()
{
	for (MAPTAG_ITER iter = m_mapTarget.begin(); iter != m_mapTarget.end(); ++iter)
	{
		iter->second->Update();
	}
}