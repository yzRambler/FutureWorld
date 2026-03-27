#include"CSceneAspect.h"
#include"CScene.h"
#include"CSceneNode.h"
#include"CPrimatterCenter.h"
#include"CEssety.h"
#include"CPrimatterAspectCenter.h"
#include"CSceneNodeAspect.h"
#include"CEssetyAspect.h"
#include"CRenderAspect.h"
#include"CComeshAspect.h"
#include"CMeshAspect.h"
#include"CSkinAspect.h"
#include"CMaterialAspect.h"
#include"CTextureUnitAspect.h"
#include"CTextureAspect.h"
#include"CAnimationGroupAspect.h"
#include"CSkeletonAnimationAspect.h"
#include"CSkeletonAspect.h"
#include"CFileManager.h"
#include"CFileDescribe.h"
#include"CSceneConfigFile.h"

using namespace FW;



CSceneAspect::CSceneAspect() :/*CPrimatterAspect(EPMTTYPE::SCENE) ,*/ m_pRootSceneAptTree(nullptr),
m_eLoadPt(ELOADPATTERN::MANUAL), m_nTimeOrder(-1), m_nScreenWidth(-1), m_nScreenHeight(-1)
{
	setTypeApt(EAPTTYPE::CST_SCENE);
}


CSceneAspect::CSceneAspect(const char* pszName) : CAspect(pszName), CData(pszName),
/*CPrimatterAspect(pszName, EPMTTYPE::SCENE), */ m_pRootSceneAptTree(nullptr), 
m_eLoadPt(ELOADPATTERN::MANUAL), m_nTimeOrder(-1), m_nScreenWidth(-1), m_nScreenHeight(-1)
{
	setTypeApt(EAPTTYPE::CST_SCENE);
}


CSceneAspect::~CSceneAspect()
{
	Destroy();
}



bool CSceneAspect::Clone(CSceneAspect* pSceneApt)
{

	Destroy();

	if (!CAspect::Clone(pSceneApt))
	{
		return false;
	}

	//setPointerSubclass(this);

	m_eLoadPt = pSceneApt->m_eLoadPt;
	m_nTimeOrder = pSceneApt->m_nTimeOrder;
	m_nScreenHeight = pSceneApt->m_nScreenHeight;
	m_nScreenWidth = pSceneApt->m_nScreenWidth;


	m_pRootSceneAptTree = new CSceneNodeAspect();
	return  m_pRootSceneAptTree->Clone(pSceneApt->m_pRootSceneAptTree);
}




bool CSceneAspect::Copy(CAspect* pAptSrc)
{
	if (!CAspect::Copy(pAptSrc))
	{
		return false;
	}

	CSceneAspect* pSceneApt = (CSceneAspect*)pAptSrc;

	setPointerSubclass(this);

	m_eLoadPt = pSceneApt->m_eLoadPt;
	m_nTimeOrder = pSceneApt->m_nTimeOrder;
	m_nScreenHeight = pSceneApt->m_nScreenHeight;
	m_nScreenWidth = pSceneApt->m_nScreenWidth;


	if (nullptr == m_pRootSceneAptTree)
	{
		m_pRootSceneAptTree = new CSceneNodeAspect();
	}

	return m_pRootSceneAptTree->Copy(pSceneApt->m_pRootSceneAptTree);
}





bool CSceneAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/)
{
	if ((0 == pPmtCent))
	{
		return false;
	}

	switch (m_eLoadPt)
	{
	case ELOADPATTERN::AUTO:
	{
	}
	break;

	case ELOADPATTERN::MANUAL:
	{
		if (0 == m_pRootSceneAptTree)
		{
			return false;
		}

		CScene* pScene = new CScene;
		CSceneNode* pSNodeRoot = 0;
		if (!m_pRootSceneAptTree->InitializeCorrelateConstruct((CConstruct**)&pSNodeRoot, 
			pPmtCent, nullptr))
		{
			setAppState(EAPPPRRES::APP_FAILED);

			*ppConstruct = 0;
			delete pScene;

			return false;
		}


		if (!pScene->Create(pSNodeRoot, m_nScreenWidth, m_nScreenHeight))
		{
			setAppState(EAPPPRRES::APP_FAILED);

			*ppConstruct = 0;
			delete pScene;

			return false;
		}



		pScene->setNameFileData(namePathFile());
		pScene->setTimeOrder(m_nTimeOrder);


		setAppState(EAPPPRRES::APP_SUCCESS);
		*ppConstruct = pScene;


		return true;

	}
	break;

	case ELOADPATTERN::MIX:
	{
	}
	break;

	default:
		break;
	}

	*ppConstruct = 0;

	return false;
}




EPMTSTATE CSceneAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent)
{
	if ((0 == ppConstruct) || (0 == *ppConstruct) || (0 == pPmtCent) || (0 == m_pRootSceneAptTree))
	{
		return EPMTSTATE::UNKNOWN;
	}

	if (appState() != EAPPPRRES::APP_SUCCESS)
	{
		return EPMTSTATE::FAILED;
	}


	CConstruct* pC = *ppConstruct;
	CScene* pScene = (CScene*)pC;

	CSceneNode* pSceneNode = pScene->rootNode();
	EPMTSTATE st = m_pRootSceneAptTree->CheckCorrelateConstruct((CConstruct**)&pSceneNode, pPmtCent);
	pScene->setState(st);

	return st;
}



bool CSceneAspect::CreateByManual()
{
	CSceneNodeAspect* pSceneTree = CreateSceneNodeAspectTree("UserRoot");
	if (0 == pSceneTree)
	{
		return false;
	}

	m_pRootSceneAptTree = pSceneTree;

	setName("test");

	m_eLoadPt = ELOADPATTERN::MANUAL;

	return true;
}


bool CSceneAspect::CreateByConfigFile(const char* pszName, CSceneNodeAspect* pRootSceneAptTree)
{
	if ((0 == pszName) || (0 == pRootSceneAptTree))
	{
		return false;
	}

	setName(pszName);

	m_pRootSceneAptTree = pRootSceneAptTree;

	return true;
}



void CSceneAspect::Destroy()
{
	if (0 != m_pRootSceneAptTree)
	{
		delete m_pRootSceneAptTree;
		m_pRootSceneAptTree = 0;
	}
}




EAPTSTATE CSceneAspect::CheckState(CAspectCenter* pAtpCent)
{
	EAPTSTATE st = TraverseSceneAptTreeState(m_pRootSceneAptTree, pAtpCent);
	setState(st);

	return st;
}



EAPTSTATE CSceneAspect::TraverseSceneAptTreeState(CSceneNodeAspect* pSceneNodeApt, CAspectCenter* pAtpCent)
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



bool CSceneAspect::SearchSceneNodeInBuffer(char* pBuffer, const char* pszSceneNodeAspName)
{
	return true;
}


CSceneNodeAspect* CSceneAspect::CreateSceneNodeAspectTree(const char* pszSceneNodeAspName)
{

	return 0;
}
