#include"CUITreeAspect.h"
#include"CSceneNodeAspect.h"
#include"CSceneNode.h"
#include"CEssetyAspect.h"
#include"CMaterialAspect.h"
#include"CUIAspect.h"

using namespace FW;



CUITreeAspect::CUITreeAspect(CAspect* pHost /*= nullptr*/) : CAspect(pHost), m_pRootUITreeApt(nullptr), 
m_bMatlInitialized(false), m_bReady(false)
{
	setTypeApt(EAPTTYPE::CST_UI_TREE);
	m_vtUIApt.clear();
}

CUITreeAspect::CUITreeAspect(const char* pszName, CAspect* pHost /*= nullptr*/) : CAspect(pszName, pHost),
m_pRootUITreeApt(nullptr), m_bMatlInitialized(false), m_bReady(false)
{
	setTypeApt(EAPTTYPE::CST_UI_TREE);
	m_vtUIApt.clear();
}

CUITreeAspect::~CUITreeAspect()
{
	if (nullptr != m_pRootUITreeApt)
	{
		delete m_pRootUITreeApt;
		m_pRootUITreeApt = nullptr;
	}

	m_vtUIApt.clear();
}



EAPTSTATE CUITreeAspect::CheckState(CAspectCenter* pAtpCent)
{
	EAPTSTATE st = TraverseSceneAptTreeState(m_pRootUITreeApt, pAtpCent);
	setState(st);


	if (m_vtUIApt.empty())
	{
		CollectUIAspect(m_pRootUITreeApt);
	}


	return st;
}



void CUITreeAspect::CollectUIAspect(CSceneNodeAspect* pSceneNodeApt)
{
	if (nullptr == pSceneNodeApt)
	{
		return;
	}

	CEssetyAspect* pEstApt = (CEssetyAspect*)pSceneNodeApt->aspect();
	if (nullptr != pEstApt)
	{
		CUIAspect* pUIApt = (CUIAspect*)pEstApt->GetComponetApt(ECOMTYPE::CO_UI);
		if (nullptr != pUIApt)
		{
			m_vtUIApt.push_back(pUIApt);
		}
	}


	int coutSub = pSceneNodeApt->countSubNodes();
	for (int i = 0; i < coutSub; i++)
	{
		CollectUIAspect((CSceneNodeAspect*)pSceneNodeApt->subNode(i));
	}
}



EAPTSTATE CUITreeAspect::TraverseSceneAptTreeState(CSceneNodeAspect* pSceneNodeApt, CAspectCenter* pAtpCent)
{
	if (0 == pSceneNodeApt)
	{
		return EAPTSTATE::APT_FAILED;
	}


	EAPTSTATE rsState = EAPTSTATE::APT_READY;
	EAPTSTATE state = pSceneNodeApt->CheckState(pAtpCent);

	rsState = state > rsState ? state : rsState;

	CSceneNodeAspect* pSubSceneNodeApt = 0;
	for (int i = 0; i < pSceneNodeApt->countSubNodes(); i++)
	{
		pSubSceneNodeApt = (CSceneNodeAspect*)pSceneNodeApt->subNode(i);
		state = TraverseSceneAptTreeState(pSubSceneNodeApt, pAtpCent);

		rsState = state > rsState ? state : rsState;
	}

	return rsState;
}



bool CUITreeAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst)
{

	for (int i = 0; i < m_vtUIApt.size(); i++)
	{
		if (!m_vtUIApt[i]->InitializeCorrelateConstruct(0, 0, 0))
		{
			return false;
		}
	}

	m_bMatlInitialized = true;

	return m_bMatlInitialized;

}


bool CUITreeAspect::Clone(CUITreeAspect* pUITApt)
{

	Destroy();

	if (!CAspect::Clone(pUITApt))
	{
		return false;
	}

	setNameData(pUITApt->nameData());


	m_nTimeOrder = pUITApt->m_nTimeOrder;


	m_pRootUITreeApt = new CSceneNodeAspect();
	return  m_pRootUITreeApt->Clone(pUITApt->m_pRootUITreeApt);
}


void CUITreeAspect::Destroy()
{

}



EPMTSTATE CUITreeAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent)
{

	EPMTSTATE RS = EPMTSTATE::READY;
	EPMTSTATE st = EPMTSTATE::UNKNOWN;

	for (int i = 0; i < m_vtUIApt.size(); i++)
	{
		st = m_vtUIApt[i]->CheckCorrelateConstruct(0, 0);
		RS = (RS < st) ? st : RS;
	}

	m_bReady = (RS == EPMTSTATE::READY);


	return RS;

}