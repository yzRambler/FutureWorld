#include"CTextureAspect.h"
#include"CTextureUnitAspect.h"
#include"CTexture.h"
#include"CPrimatterCenter.h"

using namespace FW;

CTextureAspect::CTextureAspect(CTextureUnitAspect* pHost):CPrimatterAspect(EPMTTYPE::TEXTURE),m_pHost(pHost)
{
}

CTextureAspect::CTextureAspect(const char* pszName, CTextureUnitAspect* pHost) :
	CPrimatterAspect(pszName, EPMTTYPE::TEXTURE), m_pHost(pHost)//, m_pszNameSampler(0)
{
}

CTextureAspect::~CTextureAspect()
{
}


bool CTextureAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
{
	return true;
}


EPMTSTATE CTextureAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}



bool CTextureAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	if (0 == m_pHost)
	{
		return false;
	}

	//call host generate texture unit id and setup m_idTextureUnit;
	//...

	//m_pszNameSampler = pszNameSampler;

	return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
}



bool CTextureAspect::Copy(CAspect* pAptSrc)
{
	return CPrimatterAspect::Copy(pAptSrc);
}



bool CTextureAspect::Clone(CAspect* pAptSrc)
{
	return CPrimatterAspect::Clone(pAptSrc);
}
