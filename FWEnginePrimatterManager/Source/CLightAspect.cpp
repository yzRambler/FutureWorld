#include"CDirectLight.h"
#include"CPointLight.h"
#include"CSpotLight.h"
#include"CLightAspect.h"
//#include"CSpaceInformAspect.h"
#include"RenderSystemCommon.h"
#include"CEssety.h"


using namespace FW;


CLightAspect::CLightAspect(CAspect* pHost) : 
	CComponentAspect(pHost,	ECOMTYPE::CO_LIGHT), 
	m_fIntensity(0.0f), m_eLitType(ELITTYPE::LT_UNKNOW), 
	m_nTargetSpaceOrder(-1), m_idTargetSpaceTime(0), m_nSceneTimeOrder(-1)
{
	m_v4Color.Clean();
}

CLightAspect::CLightAspect(const char* pszName, CAspect* pHost) :
CComponentAspect(pszName, pHost, ECOMTYPE::CO_LIGHT), m_fIntensity(0.0f), 
m_eLitType(ELITTYPE::LT_UNKNOW),m_nTargetSpaceOrder(-1), m_idTargetSpaceTime(0), 
m_nSceneTimeOrder(-1)
{
	m_v4Color.Clean();
}

CLightAspect::~CLightAspect()
{
}


bool CLightAspect::Create(int sceneTimeOrder)
{
	m_nSceneTimeOrder = sceneTimeOrder;

	return true;
}


CComponentAspect* CLightAspect::CreateCoInstance(CEssetyAspect* pComHost)
{
	return new CLightAspect((CAspect*)pComHost);
}



bool CLightAspect::Clone(CAspect* pAptSrc)
{
	if (!CComponentAspect::Clone(pAptSrc))
	{
		return false;
	}

	CLightAspect* pLitApt = (CLightAspect*)pAptSrc;

	m_nSceneTimeOrder = pLitApt->m_nSceneTimeOrder;
	m_nTargetSpaceOrder = pLitApt->m_nTargetSpaceOrder;
	m_idTargetSpaceTime = pLitApt->m_idTargetSpaceTime;

	m_fIntensity = pLitApt->m_fIntensity;

	m_v4Color = pLitApt->m_v4Color;
	m_eLitType = pLitApt->m_eLitType;

	return true;
}



void CLightAspect::GenerateSpaceTimeID()
{
	m_idTargetSpaceTime = CreateSpaceTimeID(m_nTargetSpaceOrder, m_nSceneTimeOrder);
}


bool CLightAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/)
{
	if ((pPmtCent == 0) || (0 == ppConstruct) || (*ppConstruct == 0))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		//*ppConstruct = 0;

		return false;
	}

	EPMTSTATE RS = EPMTSTATE::READY;

	CEssety* pEst = (CEssety*)((CLight*)(*ppConstruct))->host();
	CLight* pLight = nullptr;

	//The host and component host will be set up in outside.
	switch (m_eLitType)
	{
	case ELITTYPE::LT_POINT:
	{
		pLight = new CPointLight(name(), pEst);
		delete *ppConstruct;
	}
	break;

	case ELITTYPE::LT_DIRECT:
	{
		pLight = new CDirectLight(name(), pEst);
		if (!pLight->Create(m_idTargetSpaceTime))
		{
			setAppState(EAPPPRRES::APP_FAILED);
			//*ppConstruct = 0;

			return false;
		}

		delete *ppConstruct;
		
	}
	break;

	case ELITTYPE::LT_SPOT:
	{
		pLight = new CSpotLight(name(), pEst);
		delete *ppConstruct;
	}
	break;

	default:
	{
		setAppState(EAPPPRRES::APP_FAILED);
		//*ppConstruct = 0;

		return false;
	}
	break;
	}

	pLight->setTargetSpaceOrder(m_nTargetSpaceOrder);

	pLight->setIntensity(m_fIntensity);
	pLight->setColor(m_v4Color.x, m_v4Color.y, m_v4Color.z, m_v4Color.w);


	pLight->setState(RS);
	setAppState(EAPPPRRES::APP_SUCCESS);

	*ppConstruct = pLight;

	return true;
}



EPMTSTATE CLightAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent)
{
	if ((0 == ppConstruct) || (0 == *ppConstruct) || (0 == pPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return EPMTSTATE::FAILED;
	}

	CLight* pLight = (CLight*)*ppConstruct;

	return pLight->state();
}