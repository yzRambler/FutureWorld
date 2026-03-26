#include"CAspect.h"
#include<string>
#include"CIDManager.h"


using namespace FW;


CAspect::~CAspect()
{
	CIDManager::Instance().RemoveID(id());
}


CAspect* CAspect::Duplicate(int n)
{
	CAspect* pApt = CreateInstance();
	if (nullptr == pApt)
	{
		return 0;
	}

	if (n == 0)
	{
		return pApt;
	}


	if (!pApt->Clone(this))
	{
		delete pApt;
		return 0;
	}


	return pApt;
}




bool CAspect::Copy(CAspect* pAptSrc)
{
	if (nullptr == pAptSrc)
	{
		return false;
	}


	m_eGenFrom = EGEN::GE_COPY;

	m_id = pAptSrc->m_id;

	setName(pAptSrc->name());

	m_eState = pAptSrc->m_eState;
	m_eAppState = pAptSrc->m_eAppState;
	m_eTypeApt = pAptSrc->m_eTypeApt;



	return true;
}




bool CAspect::Clone(CAspect* pAptSrc)
{
	if (nullptr == pAptSrc)
	{
		return false;
	}


	m_eGenFrom = EGEN::GE_CLONE;

	m_id = pAptSrc->m_id;

	setName(pAptSrc->name());

	m_eState = pAptSrc->m_eState;
	m_eAppState = pAptSrc->m_eAppState;
	m_eTypeApt = pAptSrc->m_eTypeApt;


	return true;
}
