#include<string>
#include"CShaderFile.h"
//#include"CAssetCenter.h"
#include"CPrimatterCenter.h"

#ifndef _WND_OPENGL_PLATFORM_

#include<emscripten.h>

#define _WEB_DEBUG_

#endif

using namespace FW;

CShaderFile::CShaderFile(const char* pszName) :CTextFile(pszName), m_eType(ESHDTYPE::SH_UNKOWN)
{
}

CShaderFile::CShaderFile(const char* pszName, const char* pszNameFile) : 
	CTextFile(pszName, pszNameFile)
{
	std::string strFileName = pszNameFile;
	if (strFileName.find("Vertex") != std::string::npos)
	{
		m_eType = ESHDTYPE::VERTEX_SH;
	}
	else if (strFileName.find("Fragment") != std::string::npos)
	{
		m_eType = ESHDTYPE::FRAGMENT_SH;
	}
}


CShaderFile::~CShaderFile()
{
}


bool CShaderFile::Parse()
{
	if ((m_pBuffer == 0) || (m_nSize <= 0))
	{
		return false;
	}

	//The m_pBuffer of the CFile member variable have some garbage characters, can not be used.
	//The parse procedure following, will wipe off them.
	if (!CTextFile::Parse())
	{
		return false;
	}

	for (int i = 0; i < m_vtContent.size(); i++)
	{
		int len = strlen(m_vtContent[i]);
		for (int n = 0; n < len; n++)
		{
			m_vtBuffer.push_back(*(m_vtContent[i] + n));
		}
	}

	m_vtBuffer.push_back('\0');

	m_eFileState = CFile::EFSTATE::PARSE_SUC;

#ifdef _WEB_DEBUG_
	EM_ASM({ console.log("shader file parse successful! The name is " + UTF8ToString($0)); }, (char*)this->nameFile());
#endif


	return true;
}



