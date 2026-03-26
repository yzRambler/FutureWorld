#include"CComeshAspect.h"
#include"CMeshAspect.h"
#include"CPrimatterCenter.h"
#include"CComesh.h"
#include"CMesh.h"
#include"CSpaceAspect.h"

using namespace FW;

CComeshAspect::CComeshAspect():CPrimatterAspect(EPMTTYPE::COMESH)
{
	m_pSpaceModelApt = new CSpaceAspect;
}


CComeshAspect::CComeshAspect(const char* pszName) :CPrimatterAspect(pszName, EPMTTYPE::COMESH)
{
	m_pSpaceModelApt = new CSpaceAspect;
}


CComeshAspect::~CComeshAspect()
{
	Destroy();
}



bool CComeshAspect::Copy(CAspect* pAptSrc)
{

	if ((pAptSrc == nullptr)||(!CPrimatterAspect::Copy(pAptSrc)))
	{
		return false;
	}

	CMeshAspect* pMshApt = 0;
	CComeshAspect* pCmApt = (CComeshAspect*)pAptSrc;

	if (m_vtMeshApt.size() < pCmApt->m_vtMeshApt.size())
	{
		m_vtMeshApt.resize(pCmApt->m_vtMeshApt.size());
	}

	for (int i = 0; i < pCmApt->m_vtMeshApt.size(); i++)
	{
		if (nullptr != pCmApt->m_vtMeshApt[i])
		{
			if (nullptr == m_vtMeshApt[i])
			{
				m_vtMeshApt[i] = new CMeshAspect(this);
			}
			else
			{
				if (strcmp(m_vtMeshApt[i]->name(), pCmApt->m_vtMeshApt[i]->name()) != 0)
				{
					Destroy();
					return false;
				}
			}

			if (!m_vtMeshApt[i]->Copy(pCmApt->m_vtMeshApt[i]))
			{
				Destroy();
				return false;
			}

		}
		else
		{
			if (m_vtMeshApt[i] != nullptr)
			{
				delete m_vtMeshApt[i];

				m_vtMeshApt[i] = nullptr;
			}
		}
	}


	if (nullptr == m_pSpaceModelApt)
	{
		m_pSpaceModelApt = new CSpaceAspect();
		m_pSpaceModelApt->Create();
	}

	m_pSpaceModelApt->Copy(pCmApt->m_pSpaceModelApt);

	return true;
}


bool CComeshAspect::Clone(CAspect* pAptSrc)
{
	Destroy();

	if (!CPrimatterAspect::Clone(pAptSrc))
	{
		return false;
	}

	CMeshAspect* pMshApt = 0;
	CComeshAspect* pCmApt = (CComeshAspect*)pAptSrc;
	for (VTMESHAPT_ITER iter = pCmApt->m_vtMeshApt.begin(); iter != pCmApt->m_vtMeshApt.end(); ++iter)
	{
		pMshApt = new CMeshAspect(this);
		if (!pMshApt->Clone(*iter))
		{
			Destroy();
			return false;
		}

		m_vtMeshApt.push_back(pMshApt);
	}

	m_pSpaceModelApt = new CSpaceAspect();
	m_pSpaceModelApt->Create();
	m_pSpaceModelApt->Clone(pCmApt->m_pSpaceModelApt);


	return true;
}


bool CComeshAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
}


bool CComeshAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pPmtCent, CConstruct* pHostCst)
{
	if (0 == pPmtCent)
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return false;
	}

	CComesh* pComesh = 0;
	EAPPPRRES rc = pPmtCent->ApplyPrimatter(this, (IPrimatter**)&pComesh, pHostCst);
	if (rc == EAPPPRRES::APP_SUCCESS)
	{
		*ppConstruct = pComesh;
		return true;
	}

	*ppConstruct = 0;
	return false;

}


EAPTSTATE CComeshAspect::CheckState(CEssetyAspect* pEsetyApt, CAspectCenter* pAptCent)
{
	if (state() == EAPTSTATE::APT_READY)
	{
		return EAPTSTATE::APT_READY;
	}

	EAPTSTATE rs = EAPTSTATE::APT_READY;
	EAPTSTATE st = EAPTSTATE::APT_UNKNOWN;
	CMeshAspect* pMeshApt = 0;
	for (VTMESHAPT_ITER iter = m_vtMeshApt.begin(); iter != m_vtMeshApt.end(); ++iter)
	{
		pMeshApt = *iter;
		if (0 != pMeshApt)
		{
			st = pMeshApt->CheckState(pEsetyApt, pAptCent);

#ifdef _FW_DEBUG_

			if ((strcmp(pMeshApt->name(), "EyeBallLeft") == 0) && (st == EAPTSTATE::APT_READY))
			{
				char c = 0;
			}

#endif // _FW_DEBUG_



			rs = st > rs ? st : rs;
		}
	}

	setState(rs);

	return rs;
}



EPMTSTATE CComeshAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent)
{
	if ((0 == ppConstruct)||(0 == *ppConstruct)||(0 == pPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return EPMTSTATE::FAILED;
	}

	return pPmtCent->InquirePrimatterState(this);
}




CMeshAspect* CComeshAspect::Find(const char* pszNameMesh)
{
	return 0;
}

void CComeshAspect::Destroy()
{
	for (VTMESHAPT_ITER iter = m_vtMeshApt.begin(); iter != m_vtMeshApt.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtMeshApt.clear();


	if (0 != m_pSpaceModelApt)
	{
		delete m_pSpaceModelApt;
		m_pSpaceModelApt = 0;
	}
}