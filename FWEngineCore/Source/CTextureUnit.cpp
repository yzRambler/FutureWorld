#include"CTextureUnit.h"
#include"CTexture.h"
#include"CProgram.h"
#include"CMaterial.h"
#include"IDataResource.h"

using namespace FW;

CTextureUnit::CTextureUnit(CConstruct* pHost):CConstruct(pHost, ECONSTRTYPE::CST_TEXTUREUNIT), 
m_eTextureUnitId(0), m_indexMaterialArray(0)
{

}

CTextureUnit::CTextureUnit(const char* pszName, CConstruct* pHostCst) : CConstruct(pszName, 
	pHostCst, ECONSTRTYPE::CST_TEXTUREUNIT), 
	m_pTexture(0), m_idTexture(0), 
	m_eTextureUnitId(0), m_indexMaterialArray(0)
{
}

CTextureUnit::~CTextureUnit()
{
	Destroy();
}

bool CTextureUnit::Initialize(const char* pszNamePathFile, const char* pszNameSampler, 
	int indexOfMaterialArray, GLenum eTextUnitId, CTexture* pTexture)
{
	if ((nullptr == pszNamePathFile)||(nullptr == pszNameSampler) || (indexOfMaterialArray < 0))
	{
		return false;
	}

	m_strNamePathFile.Set(pszNamePathFile);
	m_strNameSampler.Set(pszNameSampler);

	m_indexMaterialArray = indexOfMaterialArray;
	m_eTextureUnitId = eTextUnitId;

	if (nullptr != pTexture)
	{
		m_pTexture = pTexture;
		m_pTexture->setHost(this);
		m_idTexture = pTexture->id();
	}


	return true;
}

void CTextureUnit::UseTexture(CProgram* pProgram)
{
	if((nullptr == m_pTexture)||(nullptr == pProgram))
	{
		return;
	}

	GLint sampler = glGetUniformLocation(pProgram->idProgram(), m_strNameSampler.Get());
	if (sampler < 0)
	{
		return;
	}

	//Active the texture unit (example. GL_TEXTURE0)
	glActiveTexture(m_eTextureUnitId);

	//Bind current 2D texture unit generated before to the texture unit actived.
	glBindTexture(GL_TEXTURE_2D, m_pTexture->idTexture());

	//Set the sampler texture unit to m_indexMaterialArray which is matching m_eTextureUnitId.
	//(example: 0 corresponding GL_TEXTURE0, 1 corresponding GL_TEXTURE0, ... )
	glUniform1i(sampler, m_indexMaterialArray);

}



void CTextureUnit::Destroy()
{
	m_pHost = nullptr;
	if ((nullptr != m_pTexture)&&(CIDManager::Instance().Inquire(m_idTexture)))
	{
		IDataResource* pIDR = CreateDataResource();
		pIDR->ReleasePrimatter(m_pTexture);
	}

	m_pTexture = nullptr;
	m_idTexture = 0;
}