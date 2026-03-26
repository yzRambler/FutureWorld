#include "CComponentAspect.h"
#include "CEssetyAspect.h"


using namespace FW;


bool CComponentAspect::Clone(CAspect* pAptSrc)
{
	if (!CAspect::Clone(pAptSrc))
	{
		return false;
	}

	m_eComponentType = ((CComponentAspect*)pAptSrc)->m_eComponentType;

	return true;
}



bool CComponentAspect::Copy(CAspect* pAptSrc)
{
	if (nullptr == pAptSrc)
	{
		return false;
	}

	m_eComponentType = ((CComponentAspect*)pAptSrc)->m_eComponentType;

	return true;
}