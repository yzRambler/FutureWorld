#include "CVertexShader.h"



using namespace FW;
using namespace std;

CVertexShader::CVertexShader(CConstruct* pHost) : CShader(pHost, ESHDTYPE::VERTEX_SH)
{
}

CVertexShader::CVertexShader(const char* pszName, CConstruct* pHost) : CShader(pszName, pHost, ESHDTYPE::VERTEX_SH)
{
}

CVertexShader::~CVertexShader()
{
	Destroy();
}

void CVertexShader::AddKeyValue(const char* key, const char* value)
{
	if ((key == 0) || (value == 0))
	{
		return;
	}


	PAIR* pkv = new PAIR;
	pkv->first = key;
	pkv->second = value;

	m_vtKeyValue.push_back(pkv);
}

bool CVertexShader::Create(char* pShaderFileBuffer)
{
	if (0 == pShaderFileBuffer)
	{
		return false;
	}

	GLuint idShader = glCreateShader(GL_VERTEX_SHADER);
	if (0 == idShader)
	{
		return false;
	}

	return CShader::Create(pShaderFileBuffer, idShader);
}

void CVertexShader::Destroy()
{
	for (VTKV_ITER iter = m_vtKeyValue.begin(); iter != m_vtKeyValue.end(); iter++)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtKeyValue.clear();

}