#include"CSceneNodeAspect.h"
#include"CPrimatterCenter.h"
#include"CPrimatterAspectCenter.h"
#include"CEssetyAspect.h"
#include"CRender.h"
#include"CSceneNode.h"
#include"CSpaceAspect.h"
#include"CEssety.h"
#include"CCoordSys.h"

#include"RenderSystemCommon.h"




using namespace FW;


CSceneNodeAspect::CSceneNodeAspect() :CAspect(), /*m_pSpaceAspect(0),*/ m_pSpaceWorldAspect(0), m_pSpaceLocalAspect(0),
m_nSpaceOrder(-1), m_nTimeOrder(-1), m_bInitSpaceWorld(false), m_bInitSpaceLocal(false), m_pConstructAspect(0), 
m_idSpaceTime(0)
{
}

CSceneNodeAspect::CSceneNodeAspect(const char* pszName) : CAspect(pszName), /*m_pSpaceAspect(0),*/ m_pSpaceWorldAspect(0),
m_pSpaceLocalAspect(0), m_nSpaceOrder(-1), m_nTimeOrder(-1), m_bInitSpaceWorld(false), m_bInitSpaceLocal(false),
m_pConstructAspect(0), m_idSpaceTime(0)
{
}

CSceneNodeAspect::~CSceneNodeAspect()
{
	Destroy();
}


bool CSceneNodeAspect::Clone(CSceneNodeAspect* pSceneNodeApt)
{

	Destroy();

	if (!CAspect::Clone(pSceneNodeApt))
	{
		return false;
	}

	m_bInitSpaceWorld = pSceneNodeApt->m_bInitSpaceWorld;
	m_bInitSpaceLocal = pSceneNodeApt->m_bInitSpaceLocal;
	m_idSpaceTime = pSceneNodeApt->m_idSpaceTime;
	m_nSpaceOrder = pSceneNodeApt->m_nSpaceOrder;
	m_nTimeOrder = pSceneNodeApt->m_nTimeOrder;

	
	//clone construct aspect
	if (nullptr != pSceneNodeApt->m_pConstructAspect)
	{
		m_pConstructAspect = pSceneNodeApt->m_pConstructAspect->Duplicate(1);
		if (nullptr == m_pConstructAspect)
		{
			Destroy();
			return false;
		}
	}



	//clone space aspect
	m_pSpaceWorldAspect = new CSpaceAspect();
	m_pSpaceWorldAspect->Create();
	if (!m_pSpaceWorldAspect->Clone(pSceneNodeApt->m_pSpaceWorldAspect))
	{
		Destroy();
		return false;
	}


	m_pSpaceLocalAspect = new CSpaceAspect();
	m_pSpaceLocalAspect->Create();
	if (!m_pSpaceLocalAspect->Clone(pSceneNodeApt->m_pSpaceLocalAspect))
	{
		Destroy();
		return false;
	}



	//clone all sub node
	CSceneNodeAspect* pSNAptSrc = 0;
	CSceneNodeAspect* pSNAptTag = 0;
	int countSubSrc = pSceneNodeApt->countSubNodes();
	for (int i = 0; i < countSubSrc; i++)
	{
		pSNAptSrc = (CSceneNodeAspect*)pSceneNodeApt->subNode(i);
		pSNAptTag = new CSceneNodeAspect;
		if (!pSNAptTag->Clone(pSNAptSrc))
		{
			return false;
		}

		AttachChild(pSNAptTag);
	}
	


	return true;
}



bool CSceneNodeAspect::Copy(CAspect* pAptSrc)
{
	if (nullptr == pAptSrc)
	{
		return false;
	}

	CSceneNodeAspect* pSceneNodeApt = (CSceneNodeAspect*)pAptSrc;


	if (!CAspect::Copy(pSceneNodeApt))
	{
		return false;
	}

	m_bInitSpaceWorld = pSceneNodeApt->m_bInitSpaceWorld;
	m_bInitSpaceLocal = pSceneNodeApt->m_bInitSpaceLocal;
	m_idSpaceTime = pSceneNodeApt->m_idSpaceTime;
	m_nSpaceOrder = pSceneNodeApt->m_nSpaceOrder;
	m_nTimeOrder = pSceneNodeApt->m_nTimeOrder;



	if (nullptr != pSceneNodeApt->m_pConstructAspect)
	{
		if (nullptr == m_pConstructAspect)
		{
			m_pConstructAspect = pSceneNodeApt->m_pConstructAspect->Duplicate(0);
		}

		if ((nullptr == m_pConstructAspect) 
			|| (!m_pConstructAspect->Copy(pSceneNodeApt->m_pConstructAspect)))
		{
			Destroy();
			return false;
		}
	}
	else
	{
		if (nullptr != m_pConstructAspect)
		{
			delete m_pConstructAspect;
		}

		m_pConstructAspect = nullptr;
	}



	//copy space aspect
	if (nullptr == m_pSpaceWorldAspect)
	{
		m_pSpaceWorldAspect = new CSpaceAspect();
		m_pSpaceWorldAspect->Create();
	}

	if(!m_pSpaceWorldAspect->Copy(pSceneNodeApt->m_pSpaceWorldAspect))
	{
		Destroy();
		return false;
	}

	if (nullptr == m_pSpaceLocalAspect)
	{
	    m_pSpaceLocalAspect = new CSpaceAspect();
	    m_pSpaceLocalAspect->Create();

	}

	if (!m_pSpaceLocalAspect->Copy(pSceneNodeApt->m_pSpaceLocalAspect))
	{
		Destroy();
		return false;
	}



	//copy all sub node
	CSceneNodeAspect* pSNAptSrc = 0;
	CSceneNodeAspect* pSNAptTag = 0;
	int countSubSrc = pSceneNodeApt->countSubNodes();
	for (int i = 0; i < countSubSrc; i++)
	{
		pSNAptSrc = (CSceneNodeAspect*)pSceneNodeApt->subNode(i);
		pSNAptTag = (CSceneNodeAspect*)subNode(i);
		if((nullptr == pSNAptTag) || (!pSNAptTag->Copy(pSNAptSrc)))
		{
			return false;
		}

	}



	return true;

}





void CSceneNodeAspect::Create(Vector3& pos, Vector3& forward, Vector3& up)
{

	if (0 == m_pSpaceWorldAspect)
	{
		m_pSpaceWorldAspect = new CSpaceAspect;
	}

	m_pSpaceWorldAspect->Create(pos, forward, up);
}


void CSceneNodeAspect::Create()
{
	if (0 == m_pSpaceLocalAspect)
	{
		m_pSpaceLocalAspect = new CSpaceAspect;
	}

	m_pSpaceLocalAspect->Create();


	if (0 == m_pSpaceWorldAspect)
	{
		m_pSpaceWorldAspect = new CSpaceAspect;
	}

	m_pSpaceWorldAspect->Create();

}



void CSceneNodeAspect::GeneralSpaceTimeID(int orderSpace, int orderTime)
{
	m_nSpaceOrder = orderSpace;
	m_nTimeOrder = orderTime;

	m_idSpaceTime = CreateSpaceTimeID(m_nSpaceOrder, m_nTimeOrder);
}



void CSceneNodeAspect::Destroy()
{

	if (0 != m_pConstructAspect)
	{
		delete m_pConstructAspect;
		m_pConstructAspect = 0;
	}


	if (0 != m_pSpaceLocalAspect)
	{
		delete m_pSpaceLocalAspect;

		m_pSpaceLocalAspect = 0;
	}

	if (0 != m_pSpaceWorldAspect)
	{
		delete m_pSpaceWorldAspect;

		m_pSpaceWorldAspect = 0;
	}

}



void CSceneNodeAspect::AttachConstructAspect(CAspect* pApt)
{
	if (pApt == 0)
	{
		return;
	}

	m_pConstructAspect = pApt;
	m_pConstructAspect->setHost(this);
}





EAPTSTATE CSceneNodeAspect::CheckState(CAspectCenter* pAtpCent)
{
	if (CAspect::state() == EAPTSTATE::APT_READY)
	{
		return state();
	}


	if (0 == m_pConstructAspect)
	{
		setState(EAPTSTATE::APT_READY);
		return EAPTSTATE::APT_READY;
	}

	EAPTSTATE st = m_pConstructAspect->CheckState(pAtpCent);
	setState(st);

#ifdef _FW_DEBUG_

	if (st == EAPTSTATE::APT_FAILED)
	{
		int n = 0;
	}

#endif // _FW_DEBUG_



	return st;
}




bool CSceneNodeAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/)
{
	if (0 == pPmtCent)
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		*ppConstruct = 0;

		return false;
	}


	CSceneNode* pSceneNode = new CSceneNode(name());
	pSceneNode->Create(m_nSpaceOrder, m_nTimeOrder, m_idSpaceTime,
		m_pSpaceWorldAspect->pos(), m_pSpaceWorldAspect->forward(), m_pSpaceWorldAspect->up(),
		m_pSpaceLocalAspect->pos(), m_pSpaceLocalAspect->forward(), m_pSpaceLocalAspect->up());


	//Note. the Root SceneNode's construct is empty centainly.
	if (strcmp(pSceneNode->name(), "Root") == 0)
	{
		CEssety* pEssety = new CEssety("RootSysEssety", pSceneNode);
		CreateCoordSysRender(pSceneNode, pEssety);
		pEssety->setState(EPMTSTATE::READY);

		pSceneNode->AttachConstruct(pEssety);
	}
	else if (0 != m_pConstructAspect)   //check the construct aspect
	{
		CConstruct* pConstruct = 0;
		if (!m_pConstructAspect->InitializeCorrelateConstruct(&pConstruct, pPmtCent, pSceneNode))
		{
			setAppState(EAPPPRRES::APP_FAILED);
			delete pSceneNode;
			*ppConstruct = 0;

			return false;
		}

		if (!pSceneNode->AttachConstruct(pConstruct))
		{
			setAppState(EAPPPRRES::APP_FAILED);
			delete pSceneNode;
			//delete pEssety; ???

			*ppConstruct = 0;

			return false;
		}

		pConstruct->setHost(pSceneNode);

		if (pConstruct->typeCST() == ECONSTRTYPE::CST_ESSETY)
		{
			CreateCoordSysRender(pSceneNode, (CEssety*)pConstruct);
		}
	}



	//search all subnodes
	CSceneNodeAspect* pSubSNodeApt = 0;
	CSceneNode* pSubNode = 0;
	int countSub = countSubNodes();
	for (int i = 0; i < countSub; i++)
	{
		pSubSNodeApt = (CSceneNodeAspect*)subNode(i);
		pSubNode = 0;

		if (!pSubSNodeApt->InitializeCorrelateConstruct((CConstruct**)&pSubNode, pPmtCent, nullptr))
		{
			setAppState(EAPPPRRES::APP_FAILED);

			//Now, the essety have been hung up with scene node.
			//It will be deleted while the scene node is deleted as well.
			delete pSceneNode;
			*ppConstruct = 0;

			return false;
		}

		pSubNode->SetParent(pSceneNode);
		pSceneNode->AttachChild(pSubNode);
	}

	setAppState(EAPPPRRES::APP_SUCCESS);
	*ppConstruct = pSceneNode;

	return true;
}



EPMTSTATE CSceneNodeAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent)
{
	if ((0 == ppConstruct) || (0 == *ppConstruct) || (0 == pPmtCent))
	{
		return EPMTSTATE::FAILED;
	}

	CSceneNode* pSceneNode = (CSceneNode*)*ppConstruct;
	if (pSceneNode->state() == EPMTSTATE::READY)
	{
		return EPMTSTATE::READY;
	}


	EPMTSTATE RS = EPMTSTATE::READY;
	EPMTSTATE st = EPMTSTATE::UNKNOWN;


	CConstruct* pConstruct = pSceneNode->construct();
	if (0 != m_pConstructAspect)
	{
		st = m_pConstructAspect->CheckCorrelateConstruct(&pConstruct, pPmtCent);

		RS = (RS < st) ? st : RS;
	}




	CSceneNodeAspect* pSubNodeApt = 0;
	CSceneNode* pSubNode = 0;
	int count = countSubNodes();
	for (int i = 0; i < count; i++)
	{
		pSubNodeApt = (CSceneNodeAspect*)subNode(i);
		pSubNode = (CSceneNode*)pSceneNode->subNode(i);
		if (0 != pSubNodeApt)
		{
			st = pSubNodeApt->CheckCorrelateConstruct((CConstruct**)&pSubNode, pPmtCent);

			RS = (RS < st) ? st : RS;
		}

	}

	pSceneNode->setState(RS);

	return RS;
}


void CSceneNodeAspect::CreateCoordSysRender(CSceneNode* pSceneNode, CEssety* pEssety)
{
	if ((nullptr == pSceneNode) || (nullptr == pEssety))
	{
		return;
	}

	//CRender* pRender = new CRender("CoordRender", 0, pEssety);
	CRender* pRender = new CRender("CoordRender", pEssety);
	CCoordSys* pCoordSys = new CCoordSys("CoordSys", pRender);
	pCoordSys->Create(pSceneNode->spaceWorld()->pos(), pSceneNode->spaceWorld()->forward(), 
		pSceneNode->spaceWorld()->up());


	FDWORD idRd = CIDManager::Instance().ApplyID();
	if (0 == idRd)
	{
		return;
	}

	pRender->setID(idRd);
	pRender->setComesh(pCoordSys);
	pEssety->AddComponent(pRender);
}


