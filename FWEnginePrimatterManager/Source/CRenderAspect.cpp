#include<string>
#include"Tools.h"
#include"CRenderAspect.h"
#include"CComeshAspect.h"
#include"CPrimatterCenter.h"
#include"CPrimatterAspectCenter.h"
#include"CRender.h"
#include"CEssety.h"
#include"CEssetyAspect.h"
#include"CBox.h"
#include"CMesh.h"
#include"CIDManager.h"
#include"IDataResource.h"


using namespace FW;



CRenderAspect::CRenderAspect(CAspect* pHost):
	CComponentAspect(pHost, 
		ECOMTYPE::CO_RENDER), m_pComshApt(nullptr)
{
	m_pComshApt = new CComeshAspect();
}


CRenderAspect::CRenderAspect(const char* pszName, CAspect* pHost):
	CComponentAspect(pszName, pHost, 
		ECOMTYPE::CO_RENDER), m_pComshApt(nullptr)
{
	m_pComshApt = new CComeshAspect();
}


CRenderAspect::~CRenderAspect()
{
	if (nullptr != m_pComshApt)
	{
		delete m_pComshApt;
		m_pComshApt = nullptr;
	}
}



CComponentAspect* CRenderAspect::CreateCoInstance(CEssetyAspect* pComHost)
{
	return new CRenderAspect(0, pComHost);
}



bool CRenderAspect::Clone(CAspect* pAptSrc)
{
	if ((nullptr == m_pComshApt)||(!CComponentAspect::Clone(pAptSrc)))
	{
		return false;
	}

	return m_pComshApt->Clone(((CRenderAspect*)pAptSrc)->m_pComshApt);
}



bool CRenderAspect::Copy(CAspect* pAptSrc)
{
	if ((nullptr == m_pComshApt)||(!CComponentAspect::Copy(pAptSrc)))
	{
		return false;
	}

	return m_pComshApt->Copy(((CRenderAspect*)pAptSrc)->m_pComshApt);

	//return true;
}



bool CRenderAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	if ((nullptr == m_pComshApt)||(nullptr == pszName) || (nullptr == pszNamePathAndFile))
	{
		return false;
	}

	setName(pszName);

	return m_pComshApt->Initialize(pszName, pszNamePathAndFile);
}

EAPTSTATE CRenderAspect::CheckState(CAspectCenter* pAptCent, CEssetyAspect* pEsetyApt)
{
	if ((nullptr == m_pComshApt)||(state() == EAPTSTATE::APT_READY))
	{
		return EAPTSTATE::APT_READY;
	}

	EAPTSTATE st = m_pComshApt->CheckState(pEsetyApt, pAptCent);
	setState(st);

	return st;
}


bool CRenderAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/)
{
	if ((nullptr == m_pComshApt)||(nullptr == ppConstruct)|| (nullptr == *ppConstruct) 
		|| (nullptr == pPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);

		return false;
	}

	CRender* pRender = (CRender*)*ppConstruct;
	CComesh* pComesh = 0;
	if (!m_pComshApt->InitializeCorrelateConstruct((CConstruct**)&pComesh, pPmtCent, pRender))
	{
		setAppState(EAPPPRRES::APP_FAILED);
		
		return false;
	}

	pComesh->setHost(pRender);



	FDWORD id = CIDManager::Instance().ApplyID();
	if (id == 0)
	{
		setAppState(EAPPPRRES::APP_FAILED);
		return false;
	}

	pRender->setID(id);
	pRender->setComesh(pComesh);
	pRender->setState(pComesh->state());

	setAppState(EAPPPRRES::APP_SUCCESS);

	return true;

}

EPMTSTATE CRenderAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent)
{
	if ((nullptr == m_pComshApt)||(nullptr == ppConstruct)||( nullptr == *ppConstruct)
		||(nullptr == pPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return EPMTSTATE::FAILED;
	}

	CRender* pRender = (CRender*)*ppConstruct;
	if (pRender->state() == EPMTSTATE::READY)
	{
		return EPMTSTATE::READY;
	}


	CComesh* pComesh = pRender->comesh();
	EPMTSTATE st = m_pComshApt->CheckCorrelateConstruct((CConstruct**)&pComesh, pPmtCent);
	
	
	pRender->setState(st);

	return st;
}


bool CRenderAspect::CreateBoxes(CComesh* pCmsh)
{
	if (nullptr == pCmsh)
	{
		return false;
	}

	CRender* pCmshRnd = (CRender*)pCmsh->host();

	CMesh* pMesh = 0;
	CRender* pMBRender = 0;
	CBox* pMeshBox = 0;

	char nameBuffer[64];


	for (int i = 0; i < pCmsh->countMesh(); i++)
	{
		pMesh = pCmsh->mesh(i);

		//Create mesh bound and register it.

		memset(nameBuffer, 0, sizeof(nameBuffer));
		sprintf(nameBuffer, "%sBoundRender", pMesh->name());
		pMBRender = new CRender(nameBuffer, pCmshRnd->host());

		memset(nameBuffer, 0, sizeof(nameBuffer));
		sprintf(nameBuffer, "%sBound", pMesh->name());
		pMeshBox = new CBox(nameBuffer, pMBRender);

		pMeshBox->Create();
		pMeshBox->setGen(EGEN::GE_ORG_DT);


		pMBRender->setComesh(pMeshBox);

		if(!pMesh->RegisterBox(pMeshBox))
		{
			delete pMeshBox;
			delete pMBRender;
			return false;
		}

		((CEssety*)pCmshRnd->host())->AddSubRender(pMBRender);
	}


	return true;
}

