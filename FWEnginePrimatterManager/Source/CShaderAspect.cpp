#include"CShaderAspect.h"
#include"CVertexShader.h"
#include"CFragmentShader.h"

using namespace FW;


CShaderAspect::CShaderAspect(ESHDTYPE type):CPrimatterAspect(EPMTTYPE::SHADER), m_eTypeShader(type)
{
	ClearSet();
}

CShaderAspect::CShaderAspect(const char* pszName, ESHDTYPE type) : CPrimatterAspect(pszName, EPMTTYPE::SHADER),
m_eTypeShader(type)
{
	ClearSet();
}

CShaderAspect::~CShaderAspect()
{
	Destroy();
}

bool CShaderAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
}



bool CShaderAspect::Clone(CAspect* pAptSrc)
{
	Destroy();

	if (!CPrimatterAspect::Clone(pAptSrc))
	{
		return false;
	}


	CShaderAspect* pShaderApt = (CShaderAspect*)pAptSrc;
	m_eTypeShader = pShaderApt->m_eTypeShader;

	SKeyValue* pKV = 0;
	for (VTKV_ITER iter = pShaderApt->m_vtKeyValue.begin(); 
		iter != pShaderApt->m_vtKeyValue.end(); ++iter)
	{
		pKV = new SKeyValue;

		pKV->key = new CString((*iter)->key->Get());
		pKV->value = new CString((*iter)->value->Get());

		m_vtKeyValue.push_back(pKV);
	}

	return true;
}


void CShaderAspect::AddKeyValue(const char* key, const char* value)
{
	if ((key == 0) || (value == 0))
	{
		return;
	}


	SKeyValue* pkv = new SKeyValue;


	pkv->key = new CString(key);
	pkv->value = new CString(value);


	m_vtKeyValue.push_back(pkv);
}



void CShaderAspect::ClearSet()
{
	for (VTKV_ITER iter = m_vtKeyValue.begin(); iter != m_vtKeyValue.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtKeyValue.clear();
}


void CShaderAspect::Destroy()
{
	for (VTKV_ITER iter = m_vtKeyValue.begin(); iter != m_vtKeyValue.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete(*iter)->key;
			delete(*iter)->value;

			delete *iter;
		}
	}

	m_vtKeyValue.clear();
}





//////////////////////////////////////////////////////////////////




CVertexShaderAspect::CVertexShaderAspect():CShaderAspect(ESHDTYPE::VERTEX_SH)
{
}

CVertexShaderAspect::CVertexShaderAspect(const char* pszName) :
	CShaderAspect(pszName, ESHDTYPE::VERTEX_SH)
{
}

CVertexShaderAspect::~CVertexShaderAspect()
{
}

bool CVertexShaderAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CShaderAspect::Initialize(pszName, pszNamePathAndFile);
}




CFragmentShaderAspect::CFragmentShaderAspect():CShaderAspect(ESHDTYPE::FRAGMENT_SH)
{
	//setAppState(EAPPPRRES::APP_SUCCESS);
}

CFragmentShaderAspect::CFragmentShaderAspect(const char* pszName) : 
	CShaderAspect(pszName, ESHDTYPE::FRAGMENT_SH)
{
	//setAppState(EAPPPRRES::APP_SUCCESS); 
}

CFragmentShaderAspect::~CFragmentShaderAspect()
{
}


bool CFragmentShaderAspect::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CShaderAspect::Initialize(pszName, pszNamePathAndFile);
}

