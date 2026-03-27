#include "CTexture.h"
#include "CMaterial.h"
#include "CIDManager.h"


using namespace FW;


CTexture::CTexture(CConstruct* pHost):CPrimatter(pHost, EPMTTYPE::TEXTURE),
m_ePixelType(EPIXELTYPE::EP_UNKNOWN), m_uTextureId(0), m_nHeight(0), m_nWidth(0)
{
}

CTexture::CTexture(const char* pszName, CConstruct* pHost):
	CPrimatter(pszName, pHost, EPMTTYPE::TEXTURE),
m_ePixelType(EPIXELTYPE::EP_UNKNOWN),m_uTextureId(0), m_nHeight(0), m_nWidth(0)
{
}

CTexture::~CTexture()
{
	CIDManager::Instance().RemoveID(id());

	glDeleteTextures(1, &m_uTextureId);
}



bool CTexture::Create(unsigned char* pColorBuffer, int stride, int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;

	m_ePixelType = (EPIXELTYPE)stride;

	//glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_uTextureId);
	glBindTexture(GL_TEXTURE_2D, m_uTextureId);

	switch (m_ePixelType)
	{
	case EPIXELTYPE::EP_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nWidth, m_nHeight, 0, GL_RGB, 
			GL_UNSIGNED_BYTE, pColorBuffer);
		break;

	case EPIXELTYPE::EP_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, pColorBuffer);
		break;

	default:
		return false;
		break;
	}


#ifdef _WND_OPENGL_PLATFORM_
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#else
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif

	glGenerateMipmap(GL_TEXTURE_2D);


	return true;
}



bool CTexture::Clone(CPrimatter* pPmt)
{
	return true;
}


bool CTexture::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatter::Initialize(pszName, pszNamePathAndFile);
}

