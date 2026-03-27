#include "CSkeletonAnimationAspect.h"
#include"CSkeletonAnimation.h"
#include "CSkeletonAspect.h"
#include"CSkeleton.h"
#include"CPrimatterCenter.h"

using namespace FW;

CSkeletonAnimationAspect::CSkeletonAnimationAspect() : CAnimationAspect(EANITYPE::AN_SKELETON), m_pSkeletonApt(0)
{
}

CSkeletonAnimationAspect::CSkeletonAnimationAspect(const char* pszName) : 
	CAnimationAspect(pszName, EANITYPE::AN_SKELETON), m_pSkeletonApt(0)
{
}

CSkeletonAnimationAspect::~CSkeletonAnimationAspect()
{
	Destroy();
}


bool CSkeletonAnimationAspect::Clone(CAspect* pAptSrc)
{
	Destroy();

	if (!CAnimationAspect::Clone(pAptSrc))
	{
		return false;
	}

	m_pSkeletonApt = new CSkeletonAspect();
	
	return m_pSkeletonApt->Clone(((CSkeletonAnimationAspect*)pAptSrc)->m_pSkeletonApt);
}



bool CSkeletonAnimationAspect::Initialize(const char* pszName, const char* pszNamePathAndFile, CSkeletonAspect* pSkeletonApt)
{
	if ((0 == pSkeletonApt)||(0 != m_pSkeletonApt))
	{
		return false;
	}

	m_pSkeletonApt = pSkeletonApt;

	return CAnimationAspect::Initialize(pszName, pszNamePathAndFile);
}


bool CSkeletonAnimationAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
{
	if (pPmtCent == 0)
	{
		return false;
	}

	CSkeletonAnimation* pSkeletonAni = 0;
	EAPPPRRES rc = pPmtCent->ApplyPrimatter(this, (IPrimatter**)&pSkeletonAni, pHostCst);

	if (rc == EAPPPRRES::APP_SUCCESS)
	{
		*ppConstruct = pSkeletonAni;
		return true;
	}

	*ppConstruct = 0;
	return false;
}

EPMTSTATE CSkeletonAnimationAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	if ((0 == ppConstruct)||(0 == *ppConstruct)||(0 == pPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return EPMTSTATE::FAILED;
	}

	return pPmtCent->InquirePrimatterState(this);
}


void CSkeletonAnimationAspect::Destroy()
{
	if (0 != m_pSkeletonApt)
	{
		delete m_pSkeletonApt;
		m_pSkeletonApt = 0;
	}
}