#include"CMeshAspect.h"
#include<string>
#include "CComeshAspect.h"
#include "CPrimatterCenter.h"
#include "CAspectCenter.h"
#include "CSkin.h"
#include "CMaterial.h"
#include "CMaterialAspect.h"
#include"CSkinAspect.h"
#include"CMaterialAspect.h"
#include"IDataResource.h"


using namespace FW;
using namespace std;



CMeshAspect::CMeshAspect(CComeshAspect* pHost) : CPrimatterAspect(EPMTTYPE::MESH), m_pMaterialApt(nullptr), 
m_pDeformerApt(nullptr), m_pHost(pHost)
{
}

CMeshAspect::CMeshAspect(const char* pszName, CComeshAspect* pHost) :CPrimatterAspect(pszName, 
	EPMTTYPE::MESH), m_pMaterialApt(nullptr), m_pDeformerApt(nullptr), m_pHost(pHost)
{
}

CMeshAspect::~CMeshAspect()
{
	Destroy();
}



bool CMeshAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* = nullptr */)
{
	return true;
}

EPMTSTATE CMeshAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}




bool CMeshAspect::Copy(CAspect* pAptSrc)
{
	if (!CPrimatterAspect::Copy(pAptSrc))
	{
		return false;
	}

	CMeshAspect* pMeshApt = (CMeshAspect*)pAptSrc;

	if (((nullptr == m_pMaterialApt) && (nullptr != pMeshApt->m_pMaterialApt))
		|| ((nullptr != m_pMaterialApt) && (nullptr == pMeshApt->m_pMaterialApt))
		|| ((nullptr == m_pDeformerApt) && (nullptr != pMeshApt->m_pDeformerApt))
		|| ((nullptr != m_pMaterialApt) && (nullptr == pMeshApt->m_pMaterialApt)))
	{
		return false;
	}


	//CComeshAspect* m_pHost ?

	if (pMeshApt->m_pMaterialApt != nullptr)
	{
		if (nullptr == m_pMaterialApt)
		{
			m_pMaterialApt = new CMaterialAspect();
		}

		if (!m_pMaterialApt->Copy(pMeshApt->m_pMaterialApt))
		{
			return false;
		}

		m_idMaterial = pMeshApt->m_idMaterial;

	}
	else
	{
		if (nullptr != m_pMaterialApt)
		{
			if(m_pMaterialApt->gen() != EGEN::GE_ORG_PM)
			{
				delete m_pMaterialApt;
			}


			m_pMaterialApt = nullptr;
			m_idMaterial = 0;
		}
	}




	if (pMeshApt->m_pDeformerApt != nullptr)
	{
		if (nullptr == m_pDeformerApt)
		{
			m_pDeformerApt = new CDeformerAspect(0);
		}

		if (!m_pDeformerApt->Copy(pMeshApt->m_pDeformerApt))
		{
			return false;
		}
	}
	else
	{
		if (nullptr != m_pDeformerApt)
		{
			if(m_pDeformerApt->gen() != EGEN::GE_ORG_PM)
			{
				delete m_pDeformerApt;
			}

			m_pDeformerApt = nullptr;
		}
	}



	return true;
}



bool CMeshAspect::Clone(CAspect* pAptSrc)
{
	Destroy();

	if (!CPrimatterAspect::Clone(pAptSrc))
	{
		return false;
	}


	CMeshAspect* pMeshApt = (CMeshAspect*)pAptSrc;
	
	//CComeshAspect* m_pHost ?


	m_pMaterialApt = new CMaterialAspect();
	if (!m_pMaterialApt->Clone(pMeshApt->m_pMaterialApt))
	{
		Destroy();
		return false;
	}
	m_idMaterial = pMeshApt->m_idMaterial;


	if (pMeshApt->hasDeform())
	{
		m_pDeformerApt = (CDeformerAspect*)pMeshApt->m_pDeformerApt->Duplicate(1);
		if (0 == m_pDeformerApt)
		{
			Destroy();
			return false;
		}
	}
	

	return true;
}




bool CMeshAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
}


EAPTSTATE CMeshAspect::CheckState(CEssetyAspect* pEsetyApt, CAspectCenter* pAptCent)
{
	if (state() == EAPTSTATE::APT_READY)
	{
		return EAPTSTATE::APT_READY;
	}

	EAPTSTATE rs = EAPTSTATE::APT_READY;
	EAPTSTATE st = EAPTSTATE::APT_UNKNOWN;
	CMaterialAspect* pMatlApt = 0;
	if (nullptr == m_pMaterialApt)
	{

		CMaterialAspect* pMatlApt = (CMaterialAspect*)pAptCent->ApplyAspect("Default",
			"./resources/Blank.mat", EAPTTYPE::CST_PRM_MAT);

		m_pMaterialApt = pMatlApt;
		m_idMaterial = pMatlApt->id();

		st = pMatlApt->state();
	}
	else
	{
		switch (m_pMaterialApt->state())
		{
		case APT_UNKNOWN:
		{

			pMatlApt = (CMaterialAspect*)pAptCent->ApplyAspect(m_pMaterialApt->nameData(),
				m_pMaterialApt->namePathFile(), EAPTTYPE::CST_PRM_MAT);

			if (nullptr == pMatlApt)
			{
				return EAPTSTATE::APT_FAILED;
			}


			//Check the valid of m_pMaterialApt object.
			if (CIDManagerAgent::Instance().idMag().Inquire(m_idMaterial))
			{
				if(m_pMaterialApt->gen() != EGEN::GE_ORG_PM)
				{
					delete m_pMaterialApt;
				}
				else
				{
					pAptCent->ReleaseAspect(m_pMaterialApt->name(), m_pMaterialApt->namePathFile(),
						EAPTTYPE::CST_PRM_MAT);
				}
			}

			m_pMaterialApt = pMatlApt;
			m_idMaterial = pMatlApt->id();

			st = m_pMaterialApt->state();
		}
		break;

		case APT_READY:
		{
			st = APT_READY;
		}
		break;

		case APT_INITING:
		{
			st = pAptCent->InquireAspectState(m_pMaterialApt);
		}
		break;

		default:
		{
			setState(APT_FAILED);

			return APT_FAILED;
		}
		break;
		}
	}

#ifdef _FW_DEBUG_

	if (st == EAPTSTATE::APT_FAILED)
	{
		int n = 0;
	}

#endif // _FW_DEBUG_




	rs = rs < st ? st : rs;


	if (nullptr != m_pDeformerApt)
	{
		if (m_pDeformerApt->typeDef() == EDEFORMTYPE::DE_SKIN)
		{
			CSkinAspect* pSkinApt = (CSkinAspect*)m_pDeformerApt;
			st = pSkinApt->CheckState(pEsetyApt);

			rs = rs < st ? st : rs;
		}
	}

#ifdef _FW_DEBUG_

	if (st == EAPTSTATE::APT_FAILED)
	{
		int n = 0;
	}

#endif // _FW_DEBUG_


	setState(rs);

	return rs;
}


void CMeshAspect::Destroy()
{
	if (nullptr != m_pMaterialApt)
	{
		if (CIDManagerAgent::Instance().idMag().Inquire(m_idMaterial))
		{
			IDataResource* pIDR = CreateDataResource();
			pIDR->ReleaseAspect(m_pMaterialApt->name(), m_pMaterialApt->namePathFile(), 
				EAPTTYPE::CST_PRM_MAT);
		}

		m_pMaterialApt = nullptr;
		m_idMaterial = 0;
	}

	if(nullptr != m_pDeformerApt)
	{
		delete m_pDeformerApt;
		m_pDeformerApt = nullptr;
	}
}


