#include"CPrimatterCenter.h"
#include"CPrimatterAspectCenter.h"
#include"CCameraAspect.h"
#include"CCamera.h"
#include"CLightAspect.h"
#include"CLight.h"
#include "CRenderAspect.h"
#include "CRender.h"
#include "CAnimationGroupAspect.h"
#include "CAnimationGroup.h"
#include "CSkeletonAnimationAspect.h"
#include "CSkeletonAspect.h"
#include "CEssety.h"
#include"CEssetyAspect.h"
#include "CMsgManagerAgent.h"
#include "CUIAspect.h"
#include "CIDManagerAgent.h"
//#include "CSpaceInform.h"
#include"CComponent.h"

using namespace FW;

CEssetyAspect::CEssetyAspect(CAspect* pHost):CAspect(pHost), m_bAllLocalDataReady(false)
{
}

CEssetyAspect::CEssetyAspect(const char* pszName, CAspect* pHost) :CAspect(pszName, pHost), m_bAllLocalDataReady(false)
{
}

CEssetyAspect::~CEssetyAspect()
{
	Destroy();
}


void CEssetyAspect::Destroy()
{
	//just setup to zero.
	//m_pDependentOnSNApt = 0;

	CIDManagerAgent::Instance().idMag().RemoveID(id());

	for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtComponentApt.clear();
}




bool CEssetyAspect::Copy(CAspect* pAptSrc)
{
	if(!CAspect::Copy(pAptSrc))
	{
		return false;
	}

	CComponentAspect* pCptApt = 0;
	CEssetyAspect* pEsetApt = (CEssetyAspect*)pAptSrc;
	if (m_vtComponentApt.size() < pEsetApt->m_vtComponentApt.size())
	{
		//m_vtComponentApt.reserve(pEsetApt->m_vtComponentApt.size());
		m_vtComponentApt.resize(pEsetApt->m_vtComponentApt.size());
	}

	for (int i = 0; i < pEsetApt->m_vtComponentApt.size(); i++)
	{
		if (pEsetApt->m_vtComponentApt[i] != nullptr)
		{
			if (m_vtComponentApt[i] == nullptr)
			{
				m_vtComponentApt[i] = pEsetApt->m_vtComponentApt[i]->CreateCoInstance(pEsetApt);
			}

			if (!m_vtComponentApt[i]->Copy(pEsetApt->m_vtComponentApt[i]))
			{
				Destroy();

				return false;
			}
		}
		else
		{
			if (m_vtComponentApt[i] != nullptr)
			{
				delete m_vtComponentApt[i];

				m_vtComponentApt[i] = nullptr;
			}
		}
	}



	m_bAllLocalDataReady = pEsetApt->m_bAllLocalDataReady;


	return true;
}




bool CEssetyAspect::Clone(CAspect* pAptSrc)
{
	Destroy();

	if (!CAspect::Clone(pAptSrc))
	{
		return false;
	}

	CComponentAspect* pCptApt = 0;
	CEssetyAspect* pEsetApt = (CEssetyAspect*)pAptSrc;
	for (VTCPT_ITER iter = pEsetApt->m_vtComponentApt.begin(); iter != pEsetApt->m_vtComponentApt.end(); ++iter)
	{
		pCptApt = (*iter)->CreateCoInstance(pEsetApt);

		//temporary code
		if (0 == pCptApt)
		{
			Destroy();
			return false;
		}

		if (!pCptApt->Clone(*iter))
		{
			Destroy();
			return false;
		}

		/*
		pCptApt = (CComponentAspect*)(*iter)->Duplicate();
		if (0 == pCptApt)
		{
			Destroy();
			return false;
		}
		*/

		m_vtComponentApt.push_back(pCptApt);
	}


	m_bAllLocalDataReady = pEsetApt->m_bAllLocalDataReady;


	return true;
}


CAspect* CEssetyAspect::Duplicate(int n)
{
	CEssetyAspect* pEsetApt = new CEssetyAspect(0);
	if (n == 0)
	{
		return pEsetApt;
	}



	if (!pEsetApt->Clone(this))
	{
		return 0;
	}

	return pEsetApt;
}


CAspect* CEssetyAspect::CreateInstance()
{
	return new CEssetyAspect(0);
}




bool CEssetyAspect::AddComponentAspect(CComponentAspect* pComAspect)
{
	if (0 != pComAspect->name())
	{
		for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
		{
			if (((*iter)->name() != 0)&&(strcmp((*iter)->name(), pComAspect->name()) == 0))
			{
				return false;
			}
		}
	}
	

	m_vtComponentApt.push_back(pComAspect);

	return true;
}


void CEssetyAspect::RemoveComponentAspect(const char* pszNameComponent)
{
	for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end();)
	{
		if (strcmp((*iter)->name(), pszNameComponent) == 0)
		{
			m_vtComponentApt.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}
}



CSkeletonAspect* CEssetyAspect::SearchSkeletonAspect(const char* pszNameSkeletonApt)
{
	if (0 == pszNameSkeletonApt)
	{
		return 0;
	}

	for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
	{
		if ((*iter)->type() == ECOMTYPE::CO_ANIMATIONGROUP)
		{
			CAnimationGroupAspect* pAGApt = (CAnimationGroupAspect*)(*iter);
			CAnimationAspect* pAniApt = pAGApt->currentAniAspect();
			if (pAniApt->typeAni() == EANITYPE::AN_SKELETON)
			{
				CSkeletonAnimationAspect* pSkAniApt = (CSkeletonAnimationAspect*)pAniApt;
				if (strcmp(pszNameSkeletonApt, pSkAniApt->skeletonAspect()->name()) == 0)
				{
					return pSkAniApt->skeletonAspect();
				}
			}
		}
	}

	return 0;
}



bool CEssetyAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/)
{
	if ((pPmtCent == 0)||(0 == ppConstruct))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		*ppConstruct = 0;

		return false;
	}

	EPMTSTATE RS = EPMTSTATE::READY;
	EPMTSTATE st = EPMTSTATE::UNKNOWN;
	
	//CEssety isn't primatter, cann't be acquired from CPrimatterCenter.
	//The host will be set up in outside.
	//FDWORD id = CIDManagerAgent::Instance().idMag().ApplyID();
	//CEssety* pEsety = new CEssety(name(), 0);
	CEssety* pEsety = new CEssety(name(), pHostCst);
	pEsety->Create();
	//pEsety->setID(id);



	//create and initialize all components. 
	CComponentAspect* pComApt = 0;
	CComponent* pCom = 0;
	for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
	{
		pCom = 0;
		pComApt = *iter;
		switch (pComApt->type())
		{
		case ECOMTYPE::CO_CAMERA:
		{
			//pCom = new CCamera(pComApt->name(), 0, pEsety);
			pCom = new CCamera(pComApt->name(), pEsety);
		}
		break;

		case ECOMTYPE::CO_LIGHT:
		{
			//pCom = new CLight(pComApt->name(), 0, pEsety);
			pCom = new CLight(pComApt->name(), pEsety);
		}
		break;

		case ECOMTYPE::CO_RENDER:
		{
			//CRender is not primatter, cann't be acquire from CPrimatterCenter.
			//For unified code style, the creation of CRender, un-primatter object, should be put into 
			//pComApt's initilaize function, but the construct function of CRender need host object. 
			//So, put it out is more convenient. 
			//pCom = new CRender(pComApt->name(), 0, pEsety);
			pCom = new CRender(pComApt->name(), pEsety);
		}
		break;

		case ECOMTYPE::CO_ANIMATIONGROUP:
		{
			//CAnimationGroup is not primatter, cann't be acquire from CPrimatterCenter.
			//pCom = new CAnimationGroup(pComApt->name(), 0, pEsety);
			pCom = new CAnimationGroup(pComApt->name(), pEsety);

			CMsgManagerAgent::Instance().msgCenter().RegisterLst((CListener*)pEsety->listener());
		}
		break;

			
		default:
		{
			delete pCom;
			*ppConstruct = 0;

			return false;
		}
		break;
		}


		if (!pComApt->InitializeCorrelateConstruct((CConstruct**)&pCom, pPmtCent))
		{
			setAppState(EAPPPRRES::APP_FAILED);

			delete pEsety;
			delete pCom;
			*ppConstruct = 0;

			return false;
		}

		pEsety->AddComponent(pCom);
		//pCom->setHostCom(pEsety);

		st = pCom->state();
		RS = RS < st ? st : RS;
	}

	pEsety->setState(RS);
	setAppState(EAPPPRRES::APP_SUCCESS);
	*ppConstruct = pEsety;


	return true;
}



EPMTSTATE CEssetyAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent)
{
	if ((0 == ppConstruct)||(0 == *ppConstruct)||(0 == pPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return EPMTSTATE::FAILED;
	}

	CEssety* pEsety = (CEssety*)*ppConstruct;
	if (pEsety->state() == EPMTSTATE::READY)
	{
		return EPMTSTATE::READY;
	}


	EPMTSTATE RS = EPMTSTATE::READY;
	EPMTSTATE st = EPMTSTATE::UNKNOWN;

	CComponent* pCom = 0;
	CComponentAspect* pComApt = 0;
	for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
	{
		pComApt = *iter;
		pCom = pEsety->SearchComponent(pComApt->type(), pComApt->name());

		st = pComApt->CheckCorrelateConstruct((CConstruct**)&pCom, pPmtCent);

		RS = (RS < st) ? st : RS;
	}

	pEsety->setState(RS);



	if (RS == EPMTSTATE::READY)
	{
		CComponentAspect* pRndApt = GetComponetApt(ECOMTYPE::CO_RENDER);
		if (nullptr != pRndApt)
		{
			pEsety->SetBound();
		}
	}


	return RS;
}



CComponentAspect* CEssetyAspect::GetComponetApt(ECOMTYPE type, const char* psName /*= nullptr*/)
{
	if (nullptr == psName)
	{
		if (type != ECOMTYPE::CO_UNKNOW)
		{
			for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
			{
				if ((*iter)->type() == type)
				{
					return (*iter);
				}
			}
		}

		return nullptr;
	}

	if (type == ECOMTYPE::CO_UNKNOW)
	{
		for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
		{
			if (strcmp( (*iter)->name(), psName) == 0)
			{
				return (*iter);
			}
		}
	}
	else
	{
		for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
		{
			if ((strcmp((*iter)->name(), psName) == 0)&&((*iter)->type() == type))
			{
				return (*iter);
			}
		}
	}

	return nullptr;
}




//EAPTSTATE CEssetyAspect::CheckState(CPrimatterAspectCenter* pPmtAtpCent)
EAPTSTATE CEssetyAspect::CheckState(CAspectCenter* pAtpCent)
{
	EAPTSTATE stateResult = EAPTSTATE::APT_READY;
	EAPTSTATE state = EAPTSTATE::APT_UNKNOWN;

	CComponentAspect* pComApt = 0;
	for (VTCPT_ITER iter = m_vtComponentApt.begin(); iter != m_vtComponentApt.end(); ++iter)
	{
		pComApt = *iter;
		state = pComApt->CheckState(pAtpCent, this);

#ifdef _FW_DEBUG_

		if (state == EAPTSTATE::APT_FAILED)
		{
			int i = 0;
		}

#endif // _FW_DEBUG_



		stateResult = state > stateResult ? state : stateResult;
	}

	setState(stateResult);

	return stateResult;
}







