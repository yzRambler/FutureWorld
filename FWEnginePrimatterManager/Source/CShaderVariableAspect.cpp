#include"CShaderVariableAspect.h"


using namespace FW;


bool CVertexAttributeAspect::Create(ESHDATATYPE dataType, EVATYPE typeVertexAtt, const char* pszVarName)
{
	//m_eDataType = dataType;
	m_eTypeVertexAttr = typeVertexAtt;
	m_strVarName = pszVarName;

	switch (dataType)
	{
	case ESHDATATYPE::SD_VEC3:
	{
		m_nCountComponent = 3;
		m_nSizeComponent = sizeof(float);
	}
	break;

	case ESHDATATYPE::SD_VEC2:
	{
		m_nCountComponent = 2;
		m_nSizeComponent = sizeof(unsigned int);
	}
	break;


	default:
	{
		return false;
	}
	break;
	}

	return true;
}



bool CVertexAttributeAspect::Clone(CVertexAttributeAspect* pSrcVA)
{
	if (0 == pSrcVA)
	{
		return false;
	}

	m_eTypeVertexAttr = pSrcVA->m_eTypeVertexAttr;
	m_strVarName = pSrcVA->m_strVarName;

	m_nCountComponent = pSrcVA->m_nCountComponent;
	m_nSizeComponent = pSrcVA->m_nSizeComponent;

	m_eTypeShaderVar = pSrcVA->m_eTypeShaderVar;

	ResetName(pSrcVA->name());


	return true;
}




bool CParaUniformCameraAspect::Create(ESHDATATYPE dataType, const char* pszVarName, const char* pszValue)
{
	if (strcmp(pszValue, "Position") == 0)
	{
		m_valueType = ESHCAMVALTYPE::SCV_POS;
	}
	else if (strcmp(pszValue, "ModelViewProjection") == 0)
	{
		m_valueType = ESHCAMVALTYPE::SCV_MVP;
	}
	else if (strcmp(pszValue, "ModelView") == 0)
	{
		m_valueType = ESHCAMVALTYPE::SCV_MV;
	}
	else if (strcmp(pszValue, "View") == 0)
	{
		m_valueType = ESHCAMVALTYPE::SCV_V;
	}
	else if (strcmp(pszValue, "Projection") == 0)
	{
		m_valueType = ESHCAMVALTYPE::SCV_PROJ;
	}
	else
	{
		return false;
	}


	return CParameterUniformAspect::Create(dataType, pszVarName);
}



bool CParaUniformCameraAspect::Clone(CParaUniformCameraAspect* pPUCA)
{
	m_valueType = pPUCA->m_valueType;

	return CParameterUniformAspect::Create(pPUCA->shaderDataType(), pPUCA->nameVar());
}




bool CParaUniformLightAspect::Create(ESHDATATYPE dataType, const char* pszVarName, int index, const char* pszValue)
{
	if ((index < 0) || (pszValue == 0))
	{
		return false;
	}

	if (strcmp(pszValue, "Direct") == 0)
	{
		m_valType = ESHLITVALTYPE::SLV_DIRECT;
	}
	else if (strcmp(pszValue, "Position") == 0)
	{
		m_valType = ESHLITVALTYPE::SLV_POS;
	}
	else if (strcmp(pszValue, "Intensity") == 0)
	{
		m_valType = ESHLITVALTYPE::SLV_INTENSITY;
	}
	else if (strcmp(pszValue, "Color") == 0)
	{
		m_valType = ESHLITVALTYPE::SLV_COLOR;
	}
	else
	{
		return false;
	}

	m_indexOfLightArray = index;

	return CParameterUniformAspect::Create(dataType, pszVarName);
}



bool CParaUniformLightAspect::Clone(CParaUniformLightAspect* pPULA)
{
	m_indexOfLightArray = pPULA->m_indexOfLightArray;
	m_valType = pPULA->valueType();

	return CParameterUniformAspect::Create(pPULA->shaderDataType(), pPULA->nameVar());
}



bool CParaUniformTextureAspect::Create(ESHDATATYPE dataType, const char* pszVarName, int index)
{
	if (index < 0)
	{
		return false;
	}

	m_indexOfTextureArray = index;

	return CParameterUniformAspect::Create(dataType, pszVarName);
}


bool CParaUniformTextureAspect::Clone(CParaUniformTextureAspect* pPUTA)
{
	m_indexOfTextureArray = pPUTA->m_indexOfTextureArray;

	return CParameterUniformAspect::Create(pPUTA->shaderDataType(), pPUTA->nameVar());
}



bool CParaUniformVectorAspect::Clone(CParaUniformVectorAspect* pPUVA)
{
	m_x = pPUVA->m_x;
	m_y = pPUVA->m_y;
	m_z = pPUVA->m_z;
	m_w = pPUVA->m_w;

	return CParameterUniformAspect::Create(pPUVA->shaderDataType(), pPUVA->nameVar());
}



bool CParaUniformNumberAspect::Clone(CParaUniformNumberAspect* pPUNA)
{
	m_Number = pPUNA->m_Number;

	return CParameterUniformAspect::Create(pPUNA->shaderDataType(), pPUNA->nameVar());
}