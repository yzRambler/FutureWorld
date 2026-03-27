#include "CPrimatterAspect.h"
#include "CPrimatter.h"
#include "CScene.h"



using namespace FW;


bool CPrimatterAspect::InitializeCorrelateConstructIF(IPrimatter** ppIPmt, 
	IPrimatterManager* pIPmtCent, CConstruct* pHostCst)
{
	if (nullptr == pIPmtCent)
	{
		return false;
	}

	CConstruct* pConstruct = 0;
	if (!InitializeCorrelateConstruct(&pConstruct, pIPmtCent, pHostCst))
	{
		return false;
	}

	switch (pConstruct->typeCST())
	{
	case ECONSTRTYPE::CST_PRIMATTER:
	{
		*ppIPmt = (IPrimatter*)pConstruct;
		return true;
	}
	break;

	default:
	{
		delete pConstruct;
	}
		break;
	}

	return false;
}


EPMTSTATE CPrimatterAspect::CheckCorrelateConstructIF(IPrimatter** ppIPmt, 
	IPrimatterManager* pIPmtCent)
{
	if ((0 == ppIPmt) || (0 == *ppIPmt) || (0 == pIPmtCent))
	{
		return EPMTSTATE::UNKNOWN;
	}



	switch (type())
	{
	case EPMTTYPE::SCENE:
	{
		return CheckCorrelateConstruct((CConstruct**)ppIPmt, pIPmtCent);
	}
	break;

	default:
		break;
	}


	
	return EPMTSTATE::FAILED;
}



void CPrimatterAspect::CloneName(const char* pszName)
{
	if (nullptr == pszName)
	{
		return;
	}

	setName(pszName);
	setNameData(pszName);
}


void CPrimatterAspect::CloneFileName(const char* pszNameFile)
{
	if (nullptr == pszNameFile)
	{
		return;
	}

	setNameFileData(pszNameFile);

}


