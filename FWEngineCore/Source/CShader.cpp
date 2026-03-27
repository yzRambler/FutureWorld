#include "CShader.h"
#include "CIDManager.h"


#ifndef _WND_OPENGL_PLATFORM_

#include<emscripten.h>
#define _WEB_DEBUG_

#endif

using namespace FW;


CShader::CShader(CConstruct* pHost, ESHDTYPE type) :CPrimatter(pHost, EPMTTYPE::SHADER), m_parScript(0), m_nLen(0), 
m_idShader(0), m_eTypeShader(type)
{
}

CShader::CShader(const char* pszName, CConstruct* pHost, ESHDTYPE type) : CPrimatter(pszName, pHost, EPMTTYPE::SHADER), 
m_parScript(0), m_nLen(0), m_idShader(0), m_eTypeShader(type)
{
}


CShader::~CShader()
{
	Destroy();
}

bool CShader::Create(const char* pString, GLuint idShader)
{
	if ((0 == pString) || (0 == idShader) || (0 != m_parScript) )
	{
		return false;
	}

	m_idShader = idShader;


#ifndef _WND_OPENGL_PLATFORM_
	//eliminate redundancy symbol in the end.

	GLint len = 1;
	char* pWork = (char*)pString;
	while (*pWork != '}')
	{
		pWork++;
		len++;
	}

	char* pNString = new char[len + 1];
	memset(pNString, 0, len + 1);
	memcpy(pNString, pString, len);
	pNString[len] = '\0';

	glShaderSource(m_idShader, 1, &pNString, &len);

#else
	glShaderSource(m_idShader, 1, &pString, NULL);
#endif // !_WND_OPENGL_PLATFORM_

	

	//glShaderSource(m_idShader, 1, &m_parScript, NULL);
	glCompileShader(m_idShader);

	GLint result = 0;
	glGetShaderiv(m_idShader, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result)
	{
		GLint lenInfo = 0;
		glGetShaderiv(m_idShader, GL_INFO_LOG_LENGTH, &lenInfo);
		char* pInfo = new char[lenInfo];
		glGetShaderInfoLog(m_idShader, lenInfo, NULL, pInfo);

#ifdef _WEB_DEBUG_
		EM_ASM({ console.log("CShader::Create failed! Reason: " + UTF8ToString($0)); }, (char*)pInfo);
#endif

		delete[] pInfo;


		glDeleteShader(m_idShader);
		m_idShader = 0;

		return false;
	}

	return true;
}



void CShader::Destroy()
{
	CIDManager::Instance().RemoveID(id());

	if (nullptr != m_parScript)
	{
		delete[]m_parScript;
		m_parScript = nullptr;

		m_nLen = 0;
	}


	glDeleteShader(m_idShader);

	//if (0 != m_idShader)
	//{
	//	glDeleteShader(m_idShader);
	//	m_idShader = 0;
	//}
}


