#include"CTextureUnitAspect.h"
#include"CTextureAspect.h"
#include"CTextureUnit.h"
#include"CMaterialAspect.h"

using namespace FW;

CTextureUnitAspect::CTextureUnitAspect(CMaterialAspect* pHost):m_pHost(pHost), m_pTextureApt(0),
m_indexMaterialArray(0)
{
}

CTextureUnitAspect::CTextureUnitAspect(const char* pszName, CMaterialAspect* pHost) : 
	CAspect(pszName), m_pHost(pHost), m_pTextureApt(0), 
	m_indexMaterialArray(0)
{
}

CTextureUnitAspect::~CTextureUnitAspect()
{
	Destroy();
}

bool CTextureUnitAspect::Initialize(const char* pszNameSampler, CTextureAspect* pTextApt)
{
	if ((0 == pTextApt)||(pszNameSampler == 0))
	{
		return false;
	}


	m_strNamePathFile.Set(pTextApt->namePathFile());
	m_strSamplerName.Set(pszNameSampler);

	m_pTextureApt = pTextApt;

	return true;
}



bool CTextureUnitAspect::Copy(CAspect* pAptSrc)
{
	if (!CAspect::Copy(pAptSrc))
	{
		return false;
	}

	CTextureUnitAspect* pTextureUnitApt = (CTextureUnitAspect*)pAptSrc;

	m_strNamePathFile.Set(pTextureUnitApt->m_strNamePathFile.Get());
	m_strSamplerName.Set(pTextureUnitApt->m_strSamplerName.Get());


	m_eTextureUnitId = pTextureUnitApt->m_eTextureUnitId;
	m_indexMaterialArray = pTextureUnitApt->m_indexMaterialArray;

	if(nullptr == m_pTextureApt)
	{ 
		m_pTextureApt = new CTextureAspect(this);
	}

	if (!m_pTextureApt->Copy(pTextureUnitApt->m_pTextureApt))
	{
		return false;
	}


	return true;
}



bool CTextureUnitAspect::Clone(CAspect* pAptSrc)
{
	Destroy();

	if (!CAspect::Clone(pAptSrc))
	{
		return false;
	}

	CTextureUnitAspect* pTextureUnitApt = (CTextureUnitAspect*)pAptSrc;

	m_strNamePathFile.Set(pTextureUnitApt->m_strNamePathFile.Get());
	m_strSamplerName.Set(pTextureUnitApt->m_strSamplerName.Get());

	m_eTextureUnitId = pTextureUnitApt->m_eTextureUnitId;
	m_indexMaterialArray = pTextureUnitApt->m_indexMaterialArray;

	m_pTextureApt = new CTextureAspect(this);
	if (!m_pTextureApt->Clone(pTextureUnitApt->m_pTextureApt))
	{
		Destroy();

		return false;
	}

	return true;
}







void CTextureUnitAspect::CloneNameSampler(const char* pszNameSampler)
{
	m_strSamplerName.Set(pszNameSampler);
}


void CTextureUnitAspect::CloneNameFile(const char* pszNameFile)
{
	m_strNamePathFile.Set(pszNameFile);

}

void CTextureUnitAspect::InitializeAppState(EAPPPRRES appState)
{
	setAppState(appState);
	if (0 != m_pTextureApt)
	{
		m_pTextureApt->setAppState(appState);
	}
}




bool CTextureUnitAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /*= nullptr*/)
{
	return true;
}

EPMTSTATE CTextureUnitAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}



bool CTextureUnitAspect::isMatching(CTextureUnit* pTextUnit)
{
	if (0 == pTextUnit)
	{
		return false;
	}


	if ((strcmp(m_strNamePathFile.Get(), pTextUnit->nameFile()) != 0)
		|| (strcmp(m_strSamplerName.Get(), pTextUnit->nameSampler()) != 0)
		|| (m_eTextureUnitId != pTextUnit->idTextureUnit())
		|| (m_indexMaterialArray != pTextUnit->indexTexArrayIndexOfMatl()))
	{
		return false;
	}


	return true;
}



void CTextureUnitAspect::Destroy()
{
	if (0 != m_pTextureApt)
	{
		delete m_pTextureApt;
		m_pTextureApt = 0;
	}
}