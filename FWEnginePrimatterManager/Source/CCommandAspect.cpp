#include"CCommandAspect.h"

using namespace FW;

CCommandAspect::CCommandAspect(CAspect* pHost /*= nullptr*/):CAspect(pHost)
{
	setTypeApt(EAPTTYPE::CST_COMMAND);
}


CCommandAspect::CCommandAspect(const char* pszName, CAspect* pHost /*= nullptr*/) :CAspect(pszName, pHost)
{
	setTypeApt(EAPTTYPE::CST_COMMAND);
}


CCommandAspect::~CCommandAspect()
{
}


bool CCommandAspect::Create(const char* pszCommandName, const char* pszValue)
{
	if ((nullptr == pszCommandName) || (nullptr == pszValue))
	{
		return false;
	}

	setName(pszCommandName);
	m_strValue.Set(pszValue);

	return true;
}





bool CCommandAspectBlend::Create(const char* pszCommandName, const char* pszSrc, const char* pszTag)
{
	if ((nullptr == pszCommandName) || (nullptr == pszSrc) || (nullptr == pszTag))
	{
		return false;
	}


	setName(pszCommandName);
	m_strSrc.Set(pszSrc);
	m_strTag.Set(pszTag);

	return true;

}