#include"CUIAspect.h"
#include"CSceneNodeAspect.h"
#include"CEssetyAspect.h"
#include"CUI.h"
#include"CMaterialAspect.h"
#include"CMaterial.h"
#include"IDataResource.h"
#include"CAspectCenter.h"


using namespace FW;

CUIAspect::CUIAspect(CAspect* pHost /*= nullptr*/) : CComponentAspect(pHost, ECOMTYPE::CO_UI), m_pMatl(nullptr)
{
	m_pMatlApt = new CMaterialAspect();
}


CUIAspect::CUIAspect(const char* pszName, CAspect* pHost /*= nullptr*/) : CComponentAspect(pszName, pHost, ECOMTYPE::CO_UI), m_pMatl(nullptr)
{
	m_pMatlApt = new CMaterialAspect();
}


CUIAspect::~CUIAspect()
{
	if (nullptr != m_pMatlApt)
	{
		delete m_pMatlApt;
		m_pMatlApt = nullptr;
	}
}


EAPTSTATE CUIAspect::CheckState(CAspectCenter* pAtpCent)
{
	return EAPTSTATE::APT_UNKNOWN;
}


bool CUIAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst)
{
	return m_pMatlApt->InitializeCorrelateConstruct((CConstruct**)&m_pMatl, CreateDataResource()->IPrimatterMag(), nullptr);
}


EPMTSTATE CUIAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{

	return m_pMatlApt->CheckCorrelateConstruct((CConstruct**)&m_pMatl, CreateDataResource()->IPrimatterMag());
}


CComponentAspect* CUIAspect::CreateCoInstance(CEssetyAspect* pComHost)
{
	return new CUIAspect(nullptr, pComHost);
}


bool CUIAspect::Clone(CAspect* pAptSrc)
{
	if ((nullptr == pAptSrc) || (!CComponentAspect::Clone(pAptSrc)))
	{
		return false;
	}

	CUIAspect* pUAS = (CUIAspect*)pAptSrc;


	m_strType.Set(pUAS->m_strType.Get());
	m_strNameMatl.Set(pUAS->m_strNameMatl.Get());
	m_strNameMatlFile.Set(pUAS->m_strNameMatlFile.Get());


	m_pMatlApt->Clone(pUAS->materialApt());

	m_nOrderTargetSpace = pUAS->m_nOrderTargetSpace;

	m_x = pUAS->m_x;
	m_y = pUAS->m_y;
	m_w = pUAS->m_w;
	m_h = pUAS->m_h;

	setState(EAPTSTATE::APT_INITING);

	return true;
}


EAPTSTATE CUIAspect::CheckState(CAspectCenter* pAptCent, CEssetyAspect* pEsetyApt)
{
	if ((pAptCent == nullptr) || (pEsetyApt == nullptr))
	{
		return EAPTSTATE::APT_FAILED;
	}

	
	return pAptCent->InquireAspectState(m_pMatlApt);

}



bool CUIAspect::Create(const char* pszType, const char* pszNameMaterial, const char* pszNameMaterialFile, int ordTargetSpace,
	float x, float y, float w, float h)
{
	if ((nullptr == pszType) || (nullptr == pszNameMaterial) || (nullptr == pszNameMaterialFile))
	{
		return false;
	}

	m_strType.Set(pszType);
	
	m_strNameMatl.Set(pszNameMaterial);
	m_strNameMatlFile.Set(pszNameMaterialFile);


	m_nOrderTargetSpace = ordTargetSpace;

	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;


	m_pMatlApt = (CMaterialAspect*)CreateDataResource()->ApplyAspect(m_strNameMatl.Get(),
		m_strNameMatlFile.Get(), EAPTTYPE::CST_PRM_MAT);



	return m_pMatlApt != nullptr;
}