#include"CSkeletonAnimation.h"
#include"CSkeleton.h"
//#include"CEssety.h"
#include"IDataResource.h"

using namespace FW;

CSkeletonAnimation::CSkeletonAnimation( CConstruct* pHost ) :CAnimation(pHost, EANITYPE::AN_SKELETON),
m_pSkeleton(0), m_bMajorCompleted(false),m_idSkeleton(0)
{
	m_ePlayMode = EMODE::READY;
	m_eStatePlay = ESTATE::STOP;
}

CSkeletonAnimation::CSkeletonAnimation(const char* pszName, CConstruct* pHost) : 
CAnimation(pszName, pHost, EANITYPE::AN_SKELETON), m_pSkeleton(0),
m_bMajorCompleted(false),m_idSkeleton(0)
{
	m_ePlayMode = EMODE::READY;
	m_eStatePlay = ESTATE::STOP;
}


CSkeletonAnimation::~CSkeletonAnimation()
{
	CIDManager::Instance().RemoveID(id());

	//release m_pSkeleton
	if (!CIDManager::Instance().Inquire(m_idSkeleton))
	{
		return;
	}

	IDataResource* pIDR = CreateDataResource();
	pIDR->ReleasePrimatter(m_pSkeleton);
	

	m_pSkeleton = nullptr;

}


bool CSkeletonAnimation::Clone(CPrimatter* pPmt)
{
	if ((nullptr == pPmt)||(pPmt->type() != EPMTTYPE::ANIMATION))
	{
		return false;
	}

	CAnimation* pAni = (CAnimation*)pPmt;
	if (pAni->typeAni() != EANITYPE::AN_SKELETON)
	{
		return false;
	}

	CSkeletonAnimation* pSktAni = (CSkeletonAnimation*)pPmt;
	m_type = pSktAni->type();
	m_ePlayMode = pSktAni->mode();
	m_eStatePlay = pSktAni->statePlay();

	m_lTotalTime = pSktAni->totalTime();
	m_nSpeed = pSktAni->speed();

	m_strSkeletonName.Set(pSktAni->nameSkeleton());

	IDataResource* pIDR = CreateDataResource();
	CSkeleton* pSk = (CSkeleton*)pIDR->RequirePrimatter(pSktAni->skeleton()->name(), 
		pSktAni->skeleton()->namePathFile(), pSktAni->skeleton()->type());

	if ((pSk == nullptr)||(pSk->state() != EPMTSTATE::READY))
	{
		return false;
	}

	m_pSkeleton = pSk;
	m_idSkeleton = m_pSkeleton->id();


	m_bMajorCompleted = true;

	return true;
}




bool CSkeletonAnimation::CopyWithSkeleton(CAnimation* pAniSrc, CSkeleton* pSkeleton)
{
	if ((pAniSrc == nullptr) || (pSkeleton == nullptr))
	{

		return false;
	}

	m_type = pAniSrc->type();
	m_ePlayMode = pAniSrc->mode();
	m_eStatePlay = pAniSrc->statePlay();

	m_lTotalTime = pAniSrc->totalTime();
	m_nSpeed = pAniSrc->speed();

	m_strSkeletonName.Set(pSkeleton->name());

	m_pSkeleton = pSkeleton;
	m_idSkeleton = pSkeleton->id();

	m_bMajorCompleted = true;

	return true;
}



void CSkeletonAnimation::Update(long lDltTime)
{
	switch (m_ePlayMode)
	{
	case EMODE::LOOP:
	{
		switch (m_eStatePlay)
		{
		case ESTATE::PLAY:
		{
			if (m_pSkeleton != 0)
			{
				m_pSkeleton->Update(lDltTime);
			}
		}

		case ESTATE::STOP:
		{
		}

		default:
			break;
		}
	}
	break;

	case EMODE::ONCE:
		break;

	default:
	{
		if (m_pSkeleton != 0)
		{
			lDltTime = 0;
			m_pSkeleton->Update(lDltTime);
		}
	}
	break;
	}
}
