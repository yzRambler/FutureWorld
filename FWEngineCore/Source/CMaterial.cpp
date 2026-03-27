#include"CMaterial.h"
#include"CTextureUnit.h"
#include"CTextureUnitAspect.h"
#include"CTexture.h"
#include"CMaterialAspect.h"
#include"CRenderUnit.h"
#include"CMesh.h"
#include"CCamera.h"
#include "CProgram.h"
#include "CPass.h"
#include "IDataResource.h"
#include "CIDManager.h"


#ifndef _WND_OPENGL_PLATFORM_
#define _WEB_DEBUG_
#include<emscripten.h>

#endif


using namespace FW;

CMaterial::CMaterial(CConstruct* pHost) :CPrimatter(pHost, EPMTTYPE::MATERIAL), m_nTextureCount(0), 
m_nRNDGOrder( -1 ), m_typeRender(ERNDTYPE::RT_UNKNOW)
{
	InitializeTextureArray();
	m_vtPass.clear();
}


CMaterial::CMaterial(const char* pszName, CConstruct* pHost) : CPrimatter(pszName, pHost, EPMTTYPE::MATERIAL), 
m_nTextureCount(0)
{
	InitializeTextureArray();
	m_vtPass.clear();
}


CMaterial::~CMaterial()
{
	Destroy();
}



bool CMaterial::AddPass(CPass* pPass)
{
	if (0 == pPass)
	{
		return false;
	}

	m_vtPass.push_back(pPass);

	return true;
}



bool CMaterial::matchingTextUnit(int ind, CTextureUnitAspect* pTextUnitApt)
{
	if ((ind < 0) || (ind >= ETXTU::TEXTURE_COUNT) || (0 == pTextUnitApt))
	{
		return false;
	}

	CTextureUnit* pTextUt = m_ayTextureUnit[ind];
	if (0 == pTextUt)
	{
		return false;
	}

	if ((pTextUt->indexTexArrayIndexOfMatl() != pTextUnitApt->indexTextArrayIndexOfMatl())
		|| (strcmp(pTextUt->nameSampler(), pTextUnitApt->nameSampler()) != 0))
	{
		return false;
	}

	if (strcmp(pTextUt->nameFile(), pTextUnitApt->nameFile()) != 0)
	{
		return false;
	}


	return true;
}


CTextureUnit* CMaterial::textUnit(int ind, CTextureUnitAspect* pTextUnitApt)
{
	if ((ind < 0) || (ind >= ETXTU::TEXTURE_COUNT) || (0 == pTextUnitApt))
	{
		return 0;
	}

	CTextureUnit* pTextUt = m_ayTextureUnit[ind];
	if (0 == pTextUt)
	{
		return 0;
	}

	if ((pTextUt->indexTexArrayIndexOfMatl() != pTextUnitApt->indexTextArrayIndexOfMatl())
		|| (strcmp(pTextUt->nameSampler(), pTextUnitApt->nameSampler()) != 0))
	{
		return 0;
	}

	if (strcmp(pTextUt->nameFile(), pTextUnitApt->nameFile()) != 0)
	{
		return 0;
	}


	return pTextUt;
}



bool CMaterial::AddTextureUnit(CTextureUnit* pTextUnit)
{
	if (0 == pTextUnit)
	{
		return false;
	}

	if (m_nTextureCount >= ETXTU::TEXTURE_COUNT)
	{
		return false;
	}

	if (0 != m_ayTextureUnit[pTextUnit->indexTexArrayIndexOfMatl()])
	{
		return false;
	}

	m_ayTextureUnit[pTextUnit->indexTexArrayIndexOfMatl()] = pTextUnit;

	m_nTextureCount++;

	return true;
}


bool CMaterial::InsertTextureUnit(int ind, CTextureUnit* pTextUnit)
{
	if ((ind < 0) || (ind >= ETXTU::TEXTURE_COUNT) || (0 == pTextUnit))
	{
		return false;
	}

	if (0 != m_ayTextureUnit[ind])
	{
		return false;
	}

	m_ayTextureUnit[ind] = pTextUnit;

	return true;
}



void CMaterial::Destroy()
{
	CIDManager::Instance().RemoveID(id());

	//release all textureUnit
	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		if (m_ayTextureUnit[i] != nullptr)
		{
			delete m_ayTextureUnit[i];
			m_ayTextureUnit[i] = nullptr;
		}
	}
	
	
	//release all pass
	for (VTPAS_ITER iter = m_vtPass.begin(); iter != m_vtPass.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;
		}
	}

	m_vtPass.clear();


}




void CMaterial::InitializeTextureArray()
{
	for (int i = 0; i < ETXTU::TEXTURE_COUNT; i++)
	{
		m_ayTextureUnit[i] = 0;
	}
}


bool CMaterial::BindPass(int ind)
{
	if ((ind < 0) || (ind >= m_vtPass.size()))
	{
		return false;
	}

	CPass* pPass = m_vtPass[ind];

	if ((0 == pPass)||(0 == pPass->program()))
	{
		return false;
	}

	for (int i = 0; i < pPass->countCommand(); i++)
	{
		pPass->command(i)->Execute();
	}

	
	pPass->program()->UseProgram();

	return true;
}




