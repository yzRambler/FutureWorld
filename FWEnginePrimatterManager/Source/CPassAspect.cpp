
#include"CPassAspect.h"


using namespace FW;

CPassAspect::CPassAspect():m_pParaHost(0)
{
	m_pProgramApt = new CProgramAspect(this);
	m_vtCmdAspet.clear();
}


CPassAspect::~CPassAspect()
{
	Destroy();
}



bool CPassAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
{
	return true;
}

EPMTSTATE CPassAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}


bool CPassAspect::Copy(CAspect* pAptSrc)
{
	if (nullptr == m_pProgramApt)
	{
		return false;
	}

	if (!CPrimatterAspect::Copy(pAptSrc))
	{
		return false;
	}

	CPassAspect* pPassApt = (CPassAspect*)pAptSrc;
	if (!m_pProgramApt->Copy(pPassApt->programApt()))
	{
		return false;
	}



	return true;
}



bool CPassAspect::Clone(CAspect* pAptSrc)
{
	if (pAptSrc == nullptr)
	{
		return false;
	}

	Destroy();

	if (!CPrimatterAspect::Clone(pAptSrc))
	{
		return false;
	}

	CPassAspect* pPassAptSrc = (CPassAspect*)pAptSrc;
	CCommandAspect* pCmdAptSrc = nullptr;
	for (int i = 0; i < pPassAptSrc->countCmdApt(); i++)
	{
		pCmdAptSrc = pPassAptSrc->cmdApt(i);
		AppendComdApt(pCmdAptSrc->Clone());
	}


	m_pProgramApt = new CProgramAspect(this);
	if (!m_pProgramApt->Clone(pPassAptSrc->programApt()))
	{
		Destroy();
		return false;
	}

	return true;
}



void CPassAspect::InitializeAppState(EAPPPRRES appState)
{
	if(nullptr != m_pProgramApt)
	{
		m_pProgramApt->InitializeAppState(appState);
	}
}


void CPassAspect::setProgramApt(CProgramAspect* pProgramApt)
{
	if (nullptr == pProgramApt)
	{
		return;
	}

	Destroy();

	m_pProgramApt = pProgramApt;
}


void CPassAspect::Destroy()
{
	if(nullptr != m_pProgramApt)
	{
		delete m_pProgramApt;
		m_pProgramApt = nullptr;
	}
}