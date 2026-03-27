#include"CFragmentShader.h"
//#include "glfw3.h"

using namespace FW;

CFragmentShader::CFragmentShader(CConstruct* pHost) : CShader(pHost, ESHDTYPE::FRAGMENT_SH)
{
}

CFragmentShader::CFragmentShader(const char* pszName, CConstruct* pHost) : CShader(pszName, pHost, ESHDTYPE::FRAGMENT_SH)
{
}

CFragmentShader::~CFragmentShader()
{
}


bool CFragmentShader::Create(char* pShaderFileBuffer)
{
	if (0 == pShaderFileBuffer)
	{
		return false;
	}

	GLuint idShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == idShader)
	{
		return false;
	}

	return CShader::Create(pShaderFileBuffer, idShader);
}

