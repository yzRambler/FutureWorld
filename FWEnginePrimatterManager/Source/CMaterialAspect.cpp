#include"CMaterialAspect.h"
#include"CMaterial.h"
#include"CProgramAspect.h"
#include"CTextureUnitAspect.h"
#include"CTextureUnit.h"
#include"CTextureAspect.h"
#include"CTexture.h"
#include"CPrimatterCenter.h"

using namespace FW;


CMaterialAspect::CMaterialAspect() :CPrimatterAspect(EPMTTYPE::MATERIAL), m_nTextureCount(0), 
m_nRNDGOrder(-1), m_typeRender(ERNDTYPE::RT_UNKNOW)
{
	InitializeTextUnitArray();
	m_vtPass.clear();
}

CMaterialAspect::CMaterialAspect(const char* pszName) : CPrimatterAspect(pszName, EPMTTYPE::MATERIAL),
m_nTextureCount(0)
{
	InitializeTextUnitArray();
	m_vtPass.clear();
}

CMaterialAspect::~CMaterialAspect()
{
	Destroy();
}



bool CMaterialAspect::Copy(CAspect* pAptSrc)
{
	if (!CPrimatterAspect::Copy(pAptSrc))
	{
		return false;
	}



	CMaterialAspect* pMatlApt = (CMaterialAspect*)pAptSrc;
	m_nRNDGOrder = pMatlApt->m_nRNDGOrder;
	m_typeRender = pMatlApt->m_typeRender;


	if (m_vtPass.size() < pMatlApt->m_vtPass.size())
	{
		m_vtPass.resize(pMatlApt->m_vtPass.size());
	}


	for (int i = 0; i < pMatlApt->m_vtPass.size(); i++)
	{
		if (nullptr != pMatlApt->m_vtPass[i])
		{
			if (nullptr == m_vtPass[i])
			{
				m_vtPass[i] = new CPassAspect();
			}

			if (!m_vtPass[i]->Copy(pMatlApt->m_vtPass[i]))
			{
				return false;
			}
		}
		else
		{
			if (nullptr != m_vtPass[i])
			{

				delete m_vtPass[i];

				m_vtPass[i] = nullptr;
			}
		}
	
	}


	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		if (nullptr != pMatlApt->m_ayTextUnitApt[i])
		{
			if (nullptr == m_ayTextUnitApt[i])
			{
				m_ayTextUnitApt[i] = new CTextureUnitAspect(this);
			}

			if (!m_ayTextUnitApt[i]->Copy(pMatlApt->m_ayTextUnitApt[i]))
			{
				return false;
			}
		}
		else
		{
			if (nullptr != m_ayTextUnitApt[i])
			{
				delete m_ayTextUnitApt[i];

				m_ayTextUnitApt[i] = nullptr;
			}
		}
		
	}



	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		if (0 != pMatlApt->m_ayTextureAptIDSET[i])
		{
			m_ayTextureAptIDSET[i] = pMatlApt->m_ayTextureAptIDSET[i];
		}
	}

	m_nTextureCount = pMatlApt->m_nTextureCount;


	return true;
}



bool CMaterialAspect::Clone(CAspect* pAptSrc)
{

	Destroy();

	
	if (!CPrimatterAspect::Clone(pAptSrc))
	{
		return false;
	}
	

	CMaterialAspect* pMatlApt = (CMaterialAspect*)pAptSrc;

	m_nRNDGOrder = pMatlApt->m_nRNDGOrder;
	m_typeRender = pMatlApt->m_typeRender;


	CPassAspect* pPassApt = 0;
	for (int i = 0; i < pMatlApt->m_vtPass.size(); i++)
	{
		pPassApt = new CPassAspect();
		if (!pPassApt->Clone(pMatlApt->m_vtPass[i]))
		{
			Destroy();
			return false;
		}

		AddPassAspect(pPassApt);
	}



	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		if (0 != pMatlApt->m_ayTextUnitApt[i])
		{
			if (m_ayTextUnitApt[i] == 0)
			{
				m_ayTextUnitApt[i] = new CTextureUnitAspect(this);
			}

			if (!m_ayTextUnitApt[i]->Clone(pMatlApt->m_ayTextUnitApt[i]))
			{
				Destroy();
				return false;
			}
		}
	}

	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		if (0 != pMatlApt->m_ayTextureAptIDSET[i])
		{
			m_ayTextureAptIDSET[i] = pMatlApt->m_ayTextureAptIDSET[i];
		}
	}

	m_nTextureCount = pMatlApt->m_nTextureCount;


	return true;
}



bool CMaterialAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
}


void CMaterialAspect::InitializeAppState(EAPPPRRES appState)
{
	setAppState(appState);

	for (int i = 0; i < m_vtPass.size(); i++)
	{
		m_vtPass[i]->InitializeAppState(appState);
	}

	//textures Apt
	CTextureUnitAspect* pTxtUApt = 0;
	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		pTxtUApt = m_ayTextUnitApt[i];
		if (0 != pTxtUApt)
		{
			pTxtUApt->InitializeAppState(appState);
		}
	}
}




bool CMaterialAspect::AddTextureUnitAspect(CTextureUnitAspect* pTXApt)
{
	if (m_nTextureCount >= ETXTU::TEXTURE_COUNT)
	{
		return false;
	}

	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		if (0 == m_ayTextUnitApt[i])
		{
			m_ayTextUnitApt[i] = pTXApt;
			pTXApt->setTextArrayIndexOfMatl(i);
			pTXApt->setTextureUnitId(m_ayTextureAptIDSET[i]);

			m_nTextureCount++;

			return true;
		}
	}

	return false;
}



void CMaterialAspect::InitializeTextUnitArray()
{
	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		m_ayTextUnitApt[i] = 0;
	}

	m_ayTextureAptIDSET[0] = 0x84C0;   //GL_TEXTURE0
	m_ayTextureAptIDSET[1] = 0x84C1;   //GL_TEXTURE1
	m_ayTextureAptIDSET[2] = 0x84C2;   //GL_TEXTURE2
	m_ayTextureAptIDSET[3] = 0x84C3;   //GL_TEXTURE3
	m_ayTextureAptIDSET[4] = 0x84C4;   //GL_TEXTURE4
	m_ayTextureAptIDSET[5] = 0x84C5;   //GL_TEXTURE5
	m_ayTextureAptIDSET[6] = 0x84C6;   //GL_TEXTURE6
	m_ayTextureAptIDSET[7] = 0x84C7;   //GL_TEXTURE7
}



bool CMaterialAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pIPmtCent, CConstruct* pHostCst)
{
	if ((ppConstruct == 0) || (pIPmtCent == 0))
	{
		return false;
	}

	CMaterial* pMatl = 0;

	EAPPPRRES rc = ((CPrimatterCenter*)pIPmtCent)->ApplyPrimatter(this, (CPrimatter**)&pMatl,
		pHostCst);

	if (rc != EAPPPRRES::APP_SUCCESS)
	{
		setAppState(EAPPPRRES::APP_FAILED);
		*ppConstruct = 0;

		return false;
	}

	if (m_bLocked)
	{
		pMatl->lock();
	}

	*ppConstruct = pMatl;

	return true;
}



EPMTSTATE CMaterialAspect::CheckCorrelateConstruct(CConstruct** ppConstruct, 
	IPrimatterManager* pIPmtCent)
{
	if ((0 == ppConstruct) || (0 == pIPmtCent))
	{
		setAppState(EAPPPRRES::INVAL_PARA);
		return EPMTSTATE::FAILED;
	}

	return ((CPrimatterCenter*)pIPmtCent)->InquirePrimatterState(this);
}




void CMaterialAspect::Destroy()
{
	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		CTextureUnitAspect* pTextUnitApt = m_ayTextUnitApt[i];
		if (pTextUnitApt != 0)
		{
			delete pTextUnitApt;
			m_ayTextUnitApt[i] = 0;
		}
	}

	for (VTPASS_ITER iter = m_vtPass.begin(); iter != m_vtPass.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtPass.clear();
}

