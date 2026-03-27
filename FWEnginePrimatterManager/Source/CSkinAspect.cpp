//#include"CommonShare.h"
#include"CSkinAspect.h"
#include"CSkin.h"
#include"CPrimatterCenter.h"
#include"CEssetyAspect.h"
#include"CSkeletonAspect.h"

using namespace FW;

CSkinAspect::CSkinAspect(CMeshAspect* pHost):CDeformerAspect(pHost, EDEFORMTYPE::DE_SKIN),m_pSkeletonApt(0) 
{
}


CSkinAspect::CSkinAspect(const char* pszName, CMeshAspect* pHost) :CDeformerAspect(pszName, pHost, EDEFORMTYPE::DE_SKIN), 
m_pSkeletonApt(0)
{
}


CAspect* CSkinAspect::CreateInstance()
{
	return new CSkinAspect(0);
}



bool CSkinAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
{
	return true;
}


EPMTSTATE CSkinAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}




bool CSkinAspect::Clone(CAspect* pAptSrc)
{
	if (!CDeformerAspect::Clone(pAptSrc))
	{
		return false;
	}

	Destroy();

	CSkinAspect* pSkApt = (CSkinAspect*)pAptSrc;

	m_strNameSkeleton.Set(pSkApt->m_strNameSkeleton.Get());
	
	return true;

}



EAPTSTATE CSkinAspect::CheckState(CEssetyAspect* pEsetyApt)
{
	if (state() == EAPTSTATE::APT_READY)
	{
		return EAPTSTATE::APT_READY;
	}

	if (0 == m_pSkeletonApt)
	{
		if(0 == m_strNameSkeleton.Get())
		{
			return EAPTSTATE::APT_FAILED;
		}

		m_pSkeletonApt = pEsetyApt->SearchSkeletonAspect(m_strNameSkeleton.Get());
		if (0 == m_pSkeletonApt)
		{
			return EAPTSTATE::APT_FAILED;
		}
	}

	setState(EAPTSTATE::APT_READY);

	return APT_READY;
}



void CSkinAspect::Destroy()
{
	if (0 != m_pSkeletonApt)
	{
		delete m_pSkeletonApt;
		m_pSkeletonApt = 0;
	}
}

