#include"CParameterUniform.h"


using namespace FW;


CParameterUniform::CParameterUniform(ESUTYPE type /*= ESUTYPE::SU_UNKNOW*/):m_eTypeSUniform(type), m_bActive(true)
{
}


CParameterUniform::CParameterUniform(const char* pszName, ESUTYPE type /*= ESUTYPE::SU_UNKNOW*/) : 
	CShaderVariable(pszName), m_eTypeSUniform(type), m_bActive(true)
{
}



CParameterUniform::~CParameterUniform()
{
}


bool CParameterUniform::Create(ESHDATATYPE dataType, const char* pszVarName)
{
	if ((dataType == ESHDATATYPE::SD_UNKNOW) || (0 == pszVarName))
	{
		return false;
	}

	m_typeShaderData = dataType;
	m_strVarName = pszVarName;

	return true;
}



CParaUniformCamera::CParaUniformCamera(): CParameterUniform(ESUTYPE::SU_CAMERA), m_valueType(ESHCAMVALTYPE::SCV_UNKNOW),
m_pWorkFun(0)
{
}

CParaUniformCamera::CParaUniformCamera(const char* pszName):CParameterUniform(pszName, ESUTYPE::SU_CAMERA),
m_valueType(ESHCAMVALTYPE::SCV_UNKNOW), m_pWorkFun(0)
{
}

CParaUniformCamera::~CParaUniformCamera()
{
}

bool CParaUniformCamera::Create(ESHDATATYPE dataType, const char* pszVarName, ESHCAMVALTYPE valType)
{
	m_valueType = valType;

	return CParameterUniform::Create(dataType, pszVarName);
}






CParaUniformLight::CParaUniformLight() :CParameterUniform(ESUTYPE::SU_LIGHT), m_valType(ESHLITVALTYPE::SLV_UNKNOW),
 m_fValue(0.0f), m_pWorkFun(0)
{
}

CParaUniformLight::CParaUniformLight(const char* pszName) : CParameterUniform(pszName, ESUTYPE::SU_LIGHT),
m_valType(ESHLITVALTYPE::SLV_UNKNOW), m_fValue(0.0f), m_pWorkFun(0)
{
}

CParaUniformLight::~CParaUniformLight()
{
}

bool CParaUniformLight::Create(ESHDATATYPE dataType, const char* pszVarName, int index, ESHLITVALTYPE valType)
{
	if (index < 0)
	{
		return false;
	}

	m_indexOfLightArray = index;
	m_valType = valType;

	return CParameterUniform::Create(dataType, pszVarName);
}




CParaUniformTexture::CParaUniformTexture() :CParameterUniform(ESUTYPE::SU_TEXTURE), m_indexOfTextureArray(-1)
{
}


CParaUniformTexture::CParaUniformTexture(const char* pszName) : CParameterUniform(pszName, ESUTYPE::SU_TEXTURE),
m_indexOfTextureArray(-1)
{
}


CParaUniformTexture::~CParaUniformTexture()
{
}


bool CParaUniformTexture::Create(ESHDATATYPE dataType, const char* pszVarName, int index)
{
	if (index < 0)
	{
		return false;
	}

	m_indexOfTextureArray = index;

	return CParameterUniform::Create(dataType, pszVarName);
}



