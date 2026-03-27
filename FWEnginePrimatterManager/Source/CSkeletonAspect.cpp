#include "CSkeletonAspect.h"
#include "CPrimatterCenter.h"
#include"CSkeleton.h"

using namespace FW;

CSkeletonAspect::CSkeletonAspect():CPrimatterAspect(EPMTTYPE::SKELETON)
{
}

CSkeletonAspect::CSkeletonAspect(const char* pszName) : CPrimatterAspect(pszName, EPMTTYPE::SKELETON)
{
}

CSkeletonAspect::~CSkeletonAspect()
{
}

bool CSkeletonAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
}


bool CSkeletonAspect::Clone(CAspect* pAptSrc)
{
	return CPrimatterAspect::Clone(pAptSrc);
}



bool CSkeletonAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
{
	return true;
}

EPMTSTATE CSkeletonAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}

