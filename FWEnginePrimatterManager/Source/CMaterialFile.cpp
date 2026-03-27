#include<string>
#include"CMaterialFile.h"
#include"CMaterialAspect.h"
#include"CTextureUnitAspect.h"
#include"CTextureAspect.h"
#include"CPassAspect.h"
#include"CProgramAspect.h"
#include"CShaderAspect.h"
#include"CShaderVariableAspect.h"
#include"CCommandAspect.h"
#include"Tools.h"

using namespace FW;

CMaterialFile::CMaterialFile(const char* pszName) :CTextFile(pszName), m_pMatlApt(0), m_pJSSource(0)
{
}

CMaterialFile::CMaterialFile(const char* pszName, const char* pszNameFile) : CTextFile(pszName, pszNameFile),
m_pMatlApt(0), m_pJSSource(0)
{
}

CMaterialFile::~CMaterialFile()
{
	Destroy();
}

bool CMaterialFile::Parse()
{
	if (0 == m_pBuffer)
	{
		return false;
	}

	if (0 != m_pMatlApt)
	{
		Destroy();
	}

	m_pJSSource = cJSON_Parse(m_pBuffer);
	if (0 == m_pJSSource)
	{
		return false;
	}


	bool result = CreateMaterialAspect(m_pJSSource->child);

	cJSON_Delete(m_pJSSource);
	m_pJSSource = 0;

	return result;
}



bool CMaterialFile::CreateMaterialAspect(cJSON* pJS)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Material") != 0))
	{
		return false;
	}

	CMaterialAspect* pMatlApt = new CMaterialAspect;
	cJSON* pJSMatlCom = pJS->child;
	while (pJSMatlCom)
	{
		if (strcmp(pJSMatlCom->string, "Name") == 0)
		{
			pMatlApt->CloneName(pJSMatlCom->valuestring);
		}
		else if (strcmp(pJSMatlCom->string, "NameFile") == 0)
		{
			pMatlApt->CloneFileName(pJSMatlCom->valuestring);
		}
		else if (strcmp(pJSMatlCom->string, "Order") == 0)
		{
			//convert string into number
			pMatlApt->setRNDGroupOrder(pJSMatlCom->valueint);
		}
		else if (strcmp(pJSMatlCom->string, "RenderType") == 0)
		{
			if (strcmp(pJSMatlCom->valuestring, "Opacity") == 0)
			{
				pMatlApt->setRenderType(ERNDTYPE::RT_OPACITY);
			}
			else if (strcmp(pJSMatlCom->valuestring, "Transparent") == 0)
			{
				pMatlApt->setRenderType(ERNDTYPE::RT_TRANSPARENT);
			}
			else
			{
				delete pMatlApt;
				return false;
			}

		}
		else if (strcmp(pJSMatlCom->string, "TextureUnits") == 0)
		{
			cJSON* pJSTextureUnit = pJSMatlCom->child;
			while (pJSTextureUnit)
			{
				CTextureUnitAspect* pTextureApt = CreateTextureUnitAspect(pJSTextureUnit, pMatlApt);
				if (0 != pTextureApt)
				{
					pMatlApt->AddTextureUnitAspect(pTextureApt);
				}

				pJSTextureUnit = pJSTextureUnit->next;
			}
		}
		else if (strcmp(pJSMatlCom->string, "Passes") == 0)
		{
			cJSON* pJSPassUnit = pJSMatlCom->child;
			while (pJSPassUnit)
			{
				CPassAspect* pPassApt = CreatePassAspect(pJSPassUnit, pMatlApt);
				if (0 == pPassApt)
				{
					delete pMatlApt;
					return false;
				}

				pMatlApt->AddPassAspect(pPassApt);

				pJSPassUnit = pJSPassUnit->next;
			}
		}

		/*
		else if (strcmp(pJSMatlCom->string, "Program") == 0)
		{
			CProgramAspect* pProgApt = CreateProgramAspect(pJSMatlCom, pMatlApt);
			if (0 == pProgApt)
			{
				delete pMatlApt;
				return false;
			}

			pMatlApt->setProgramApt(pProgApt);
		}
		*/

		pJSMatlCom = pJSMatlCom->next;
	}

	m_pMatlApt = pMatlApt;

	setState(EFSTATE::PARSE_SUC);

	return true;
}



CPassAspect* CMaterialFile::CreatePassAspect(cJSON* pJS, CMaterialAspect* pHost)
{
	if (0 == pJS)
	{
		return 0;
	}

	CPassAspect* pPassApt = new CPassAspect;
	cJSON* pJSMatlCom = pJS->child;
	while (pJSMatlCom)
	{
		if (strcmp(pJSMatlCom->string, "Program") == 0)
		{
			CProgramAspect* pProgApt = CreateProgramAspect(pJSMatlCom, pPassApt);
			if (0 == pProgApt)
			{
				delete pPassApt;
				return nullptr;
			}

			pPassApt->setProgramApt(pProgApt);
		}
		else if (strcmp(pJSMatlCom->string, "Command") == 0)
		{
			cJSON* pJSCmdCom = pJSMatlCom->child;
			for (; pJSCmdCom != 0; pJSCmdCom = pJSCmdCom->next)
			{
				CCommandAspect* pCmdApt = CreateCommandAspect(pJSCmdCom);
				if (nullptr == pCmdApt)
				{
					delete pCmdApt;
					return nullptr;
				}

				pPassApt->AppendComdApt(pCmdApt);
			}
		}

		pJSMatlCom = pJSMatlCom->next;
	}

	return pPassApt;
}



CCommandAspect* CMaterialFile::CreateCommandAspect(cJSON* pJS)
{
	if (nullptr == pJS)
	{
		return nullptr;
	}

	CString* pName = nullptr;
	//CString* pValue = nullptr;
	cJSON* pJSCmd = pJS->child;
	for (; pJSCmd != nullptr; pJSCmd = pJSCmd->next)
	{
		if (strcmp(pJSCmd->string, "Name") == 0)
		{
			pName = new CString(pJSCmd->valuestring);
		}
		else if (strcmp(pJSCmd->string, "Value") == 0)
		{

			if (pName == nullptr)
			{
				return nullptr;
			}

			if (strcmp(pName->Get(), "BlendFunc") == 0)
			{
				CCommandAspectBlend* pCmdApt = new CCommandAspectBlend();
				//pCmdApt->Create(pName->Get(), )
				CString* pSrc = nullptr;
				CString* pTag = nullptr;
				for (cJSON* pJSCmdCh = pJSCmd->child; pJSCmdCh != nullptr; pJSCmdCh = pJSCmdCh->next)
				{
					if (strcmp(pJSCmdCh->string, "Src") == 0)
					{
						pSrc = new CString(pJSCmdCh->valuestring);
					}
					else if (strcmp(pJSCmdCh->string, "Tag") == 0)
					{
						pTag = new CString(pJSCmdCh->valuestring);
					}
				}

				if ((nullptr != pSrc) && (nullptr != pTag))
				{
					pCmdApt->Create(pName->Get(), pSrc->Get(), pTag->Get());

					if (nullptr != pSrc)
					{
						delete pSrc;
					}

					if (nullptr != pTag)
					{
						delete pTag;
					}


					delete pName;


					return pCmdApt;
				}

			}
			else
			{
				CCommandAspect* pCmdApt = new CCommandAspect();
				pCmdApt->Create(pName->Get(), pJSCmd->valuestring);

				delete pName;

				return pCmdApt;
			}

		}
	}
	
	if (nullptr != pName)
	{
		delete pName;
	}



	return nullptr;
}



CProgramAspect* CMaterialFile::CreateProgramAspect(cJSON* pJS, CPassAspect* pHost)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Program") != 0))
	{
		return 0;
	}

	CProgramAspect* pProgramApt = new CProgramAspect(pHost);
	cJSON* pJSProgramCom = pJS->child;
	//while (pJSProgramCom)
	for (; pJSProgramCom != 0; pJSProgramCom = pJSProgramCom->next)
	{
		if (strcmp(pJSProgramCom->string, "VertexAttribute") == 0)
		{
			if (!InitializeVertexAttrSet(pJSProgramCom, pProgramApt))
			{
				delete pProgramApt;
				return 0;
			}

			continue;
		}
		else if (strcmp(pJSProgramCom->string, "ParameterUniform") == 0)
		{
			if (!InitializeParaUniformSet(pJSProgramCom, pProgramApt))
			{
				delete pProgramApt;
				return 0;
			}

			continue;
		}
		else if (strcmp(pJSProgramCom->string, "VertexShader") == 0)
		{
			if (!InitializeVertexShaderAspect(pJSProgramCom, pProgramApt->vertexShader()))
			{
				delete pProgramApt;
				return 0;
			}

			continue;
		}
		else if (strcmp(pJSProgramCom->string, "FragmentShader") == 0)
		{
			if (!InitializeFragmentShaderAspect(pJSProgramCom, pProgramApt->fragmentShader()))
			{
				delete pProgramApt;
				return 0;
			}

			continue;
		}

	}

	return pProgramApt;
}



bool CMaterialFile::InitializeVertexAttrSet(cJSON* pJS, CProgramAspect* pProgApt)
{
	if ((0 == pJS) || (strcmp(pJS->string, "VertexAttribute") != 0) || (pProgApt == 0))
	{
		return false;
	}

	CVertexAttributeAspect* pVAA = 0;
	cJSON* pJSVA = pJS->child;
	for (; pJSVA != 0; pJSVA = pJSVA->next)
	{
		pVAA = CreateVertexAttributeAspect(pJSVA);
		if (0 == pVAA)
		{
			return false;
		}

		pProgApt->AddVertexAttribute(pVAA);
	}

	pProgApt->VertexAttrSort();

	return true;
}



CVertexAttributeAspect* CMaterialFile::CreateVertexAttributeAspect(cJSON* pJS)
{
	if (0 == pJS)
	{
		return 0;
	}

	ESHDATATYPE dataType = ESHDATATYPE::SD_UNKNOW;
	EVATYPE type = EVATYPE::VA_UNKNOW;
	const char* pszName = 0;
	CVertexAttributeAspect* pVAA = new CVertexAttributeAspect;
	cJSON* pJSCom = pJS->child;
	for (; pJSCom != 0; pJSCom = pJSCom->next)
	{
		if (strcmp(pJSCom->string, "DataType") == 0)
		{
			dataType = GetDataType(pJSCom->valuestring);
			if (dataType == ESHDATATYPE::SD_UNKNOW)
			{
				return 0;
			}
		}
		else if (strcmp(pJSCom->string, "AttrType") == 0)
		{
			if (strcmp(pJSCom->valuestring, "VertexPos") == 0)
			{
				type = EVATYPE::VA_POS;
			}
			else if (strcmp(pJSCom->valuestring, "VertexNormal") == 0)
			{
				type = EVATYPE::VA_NORMAL;
			}
			else if (strcmp(pJSCom->valuestring, "VertexTangent") == 0)
			{
				type = EVATYPE::VA_TANGENT;
			}
			else if (strcmp(pJSCom->valuestring, "VertexUV") == 0)
			{
				type = EVATYPE::VA_UV;
			}
			else
			{
				return 0;
			}

			continue;
		}
		else if (strcmp(pJSCom->string, "VarName") == 0)
		{
			pszName = pJSCom->valuestring;
		}
	}

	//if (!pVAA->Create(type, pszName))
	if (!pVAA->Create(dataType, type, pszName))
	{
		return 0;
	}

	return pVAA;
}




bool CMaterialFile::InitializeParaUniformSet(cJSON* pJS, CProgramAspect* pProgApt)
{
	if ((0 == pJS) || (strcmp(pJS->string, "ParameterUniform") != 0) || (pProgApt == 0))
	{
		return false;
	}

	CParameterUniformAspect* pPUA = 0;
	cJSON* pJSPU = pJS->child;
	for (; pJSPU != 0; pJSPU = pJSPU->next)
	{
		pPUA = CreateParameterUniformAspect(pJSPU);
		if (0 == pPUA)
		{
			return false;
		}

		pProgApt->AddParaUniform(pPUA);
	}


	return true;
}



CParameterUniformAspect* CMaterialFile::CreateParameterUniformAspect(cJSON* pJS)
{
	if (pJS == 0)
	{
		return 0;
	}


	ESHDATATYPE dataType = ESHDATATYPE::SD_UNKNOW;
	std::string strVarName;
	std::string strValue;
	int index = -1;
	CParameterUniformAspect* pPUA = 0;
	cJSON* pJSCom = pJS->child;
	for (; pJSCom != 0; pJSCom = pJSCom->next)
	{
		if (strcmp(pJSCom->string, "DataType") == 0)
		{
			dataType = GetDataType(pJSCom->valuestring);
			if (dataType == ESHDATATYPE::SD_UNKNOW)
			{
				return 0;
			}

			continue;
		}
		else if (strcmp(pJSCom->string, "VarName") == 0)
		{
			strVarName = pJSCom->valuestring;
			continue;
		}
		else if (strcmp(pJSCom->string, "Class") == 0)
		{
			if (strcmp(pJSCom->valuestring, "Camera") == 0)
			{
				pPUA = new CParaUniformCameraAspect;
			}
			else if (strcmp(pJSCom->valuestring, "Light") == 0)
			{
				pPUA = new CParaUniformLightAspect;
			}
			else if (strcmp(pJSCom->valuestring, "Texture") == 0)
			{
				pPUA = new CParaUniformTextureAspect;
			}
			else if (strcmp(pJSCom->valuestring, "WorldTransform") == 0)
			{
				pPUA = new CParaUniformWorldTransformAspect;
			}
			else if (strcmp(pJSCom->valuestring, "Vector") == 0)
			{
				pPUA = new CParaUniformVectorAspect;
			}
			else if (strcmp(pJSCom->valuestring, "Color") == 0)
			{
				pPUA = new CParaUniformVectorAspect;
			}
			else if (strcmp(pJSCom->valuestring, "Number") == 0)
			{
				pPUA = new CParaUniformNumberAspect;
			}

			continue;
		}

	}


	if (0 == pPUA)
	{
		return 0;
	}

	//SU_CAMERA = 0, SU_LIGHT, SU_TEXTURE, SU_WORLDTF, SU_VECTOR,  SU_NUMBER
	switch (pPUA->typeShaderUniform())
	{
	case ESUTYPE::SU_CAMERA:
	{
		pJSCom = pJS->child;
		for (; pJSCom != 0; pJSCom = pJSCom->next)
		{
			if (strcmp(pJSCom->string, "Value") == 0)
			{
				strValue = pJSCom->valuestring;
				break;
			}
		}

		CParaUniformCameraAspect* pPCam = (CParaUniformCameraAspect*)pPUA;
		if (!pPCam->Create(dataType, strVarName.c_str(), strValue.c_str()))
		{
			delete pPCam;
			return 0;
		}
	}
	break;

	case ESUTYPE::SU_LIGHT:
	{
		pJSCom = pJS->child;
		for (; pJSCom != 0; pJSCom = pJSCom->next)
		{
			if (strcmp(pJSCom->string, "Value") == 0)
			{
				strValue = pJSCom->valuestring;
				continue;
			}
			else if (strcmp(pJSCom->string, "Ind") == 0)
			{
				index = pJSCom->valueint;
				continue;
			}
		}

		CParaUniformLightAspect* pPLit = (CParaUniformLightAspect*)pPUA;
		if (!pPLit->Create(dataType, strVarName.c_str(), index, strValue.c_str()))
		{
			delete pPLit;
			return 0;
		}
	}
	break;

	case ESUTYPE::SU_TEXTURE:
	{
		pJSCom = pJS->child;
		for (; pJSCom != 0; pJSCom = pJSCom->next)
		{
			if (strcmp(pJSCom->string, "Ind") == 0)
			{
				index = pJSCom->valueint;
				break;
			}
		}

		CParaUniformTextureAspect* pTextu = (CParaUniformTextureAspect*)pPUA;
		if (!pTextu->Create(dataType, strVarName.c_str(), index))
		{
			delete pTextu;
			return 0;
		}

	}
	break;

	case ESUTYPE::SU_WORLDTF:
	{
		CParaUniformWorldTransformAspect* pTA = (CParaUniformWorldTransformAspect*)pPUA;
		if (!pTA->Create(dataType, strVarName.c_str()))
		{
			delete pTA;
			return 0;
		}
	}
	break;


	case ESUTYPE::SU_VECTOR:
	{
		pJSCom = pJS->child;
		float x, y, z, w;
		for (; pJSCom != 0; pJSCom = pJSCom->next)
		{
			if (strcmp(pJSCom->string, "Value") == 0)
			{
				cJSON* pJSAry = pJSCom->child;// ->child;
				for (; pJSAry != 0; pJSAry = pJSAry->next)
				{
					cJSON* pJSVal = pJSAry->child;
					if (strcmp(pJSVal->string, "x") == 0)
					{
						x = pJSVal->valuedouble;
						continue;
					}
					else if (strcmp(pJSVal->string, "y") == 0)
					{
						y = pJSVal->valuedouble;
						continue;
					}
					else if (strcmp(pJSVal->string, "z") == 0)
					{
						z = pJSVal->valuedouble;
						continue;
					}
					else if (strcmp(pJSVal->string, "w") == 0)
					{
						w = pJSVal->valuedouble;
						continue;
					}
				}

	

				break;
			}
		}

		CParaUniformVectorAspect* pVT = (CParaUniformVectorAspect*)pPUA;
		if (!pVT->Create(dataType, strVarName.c_str(), x, y, z, w))
		{
			delete pVT;
			return 0;
		}
	}
	break;


	case ESUTYPE::SU_NUMBER:
	{
		float fval = 0.0f;
		pJSCom = pJS->child;
		for (; pJSCom != 0; pJSCom = pJSCom->next)
		{
			if (strcmp(pJSCom->string, "Value") == 0)
			{
				fval = pJSCom->valuedouble;
				break;
			}
		}

		CParaUniformNumberAspect* pNB = (CParaUniformNumberAspect*)pPUA;
		if (!pNB->Create(dataType, strVarName.c_str(), fval))
		{
			delete pNB;
			return 0;
		}
	}
	break;

	default:
	{
		delete pPUA;
		return 0;
	}
	break;
	}


	return pPUA;
}



ESHDATATYPE CMaterialFile::GetDataType(const char* pszString)
{
	if (0 == pszString)
	{
		return ESHDATATYPE::SD_UNKNOW;
	}

	ESHDATATYPE dataType = ESHDATATYPE::SD_UNKNOW;

	//SD_FLOAT = 0, SD_INT, SD_BOOL, SD_VEC2, SD_VEC3, SD_VEC4, SD_MAT2, SD_MAT3, SD_MAT4, SD_SAMP2, SD_UNKNOW
	if (strcmp(pszString, "float") == 0)
	{
		dataType = ESHDATATYPE::SD_FLOAT;
	}
	else if (strcmp(pszString, "int") == 0)
	{
		dataType = ESHDATATYPE::SD_INT;
	}
	else if (strcmp(pszString, "bool") == 0)
	{
		dataType = ESHDATATYPE::SD_BOOL;
	}
	else if (strcmp(pszString, "vec2") == 0)
	{
		dataType = ESHDATATYPE::SD_VEC2;
	}
	else if (strcmp(pszString, "vec3") == 0)
	{
		dataType = ESHDATATYPE::SD_VEC3;
	}
	else if (strcmp(pszString, "vec4") == 0)
	{
		dataType = ESHDATATYPE::SD_VEC4;
	}
	else if (strcmp(pszString, "mat2") == 0)
	{
		dataType = ESHDATATYPE::SD_MAT2;
	}
	else if (strcmp(pszString, "mat3") == 0)
	{
		dataType = ESHDATATYPE::SD_MAT3;
	}
	else if (strcmp(pszString, "mat4") == 0)
	{
		dataType = ESHDATATYPE::SD_MAT4;
	}
	else if (strcmp(pszString, "samp2") == 0)
	{
		dataType = ESHDATATYPE::SD_SAMP2;
	}

	return dataType;
}



bool CMaterialFile::InitializeVertexShaderAspect(cJSON* pJS, CVertexShaderAspect& rVSApt)
{
	if ((0 == pJS) || (strcmp(pJS->string, "VertexShader") != 0))
	{
		return false;
	}

	cJSON* pJSVSCom = pJS->child;
	while (pJSVSCom)
	{
		if (strcmp(pJSVSCom->string, "Name") == 0)
		{
			rVSApt.CloneName(pJSVSCom->valuestring);
		}
		else if (strcmp(pJSVSCom->string, "NameFile") == 0)
		{
			rVSApt.CloneFileName(pJSVSCom->valuestring);
		}
		else if (strcmp(pJSVSCom->string, "KeyValue") == 0)
		{
			cJSON* pJSSubKV = pJSVSCom->child;
			while (pJSSubKV)
			{
				SKeyValue kv = CreateKeyValue(pJSSubKV);
				rVSApt.AddKeyValue(kv.key, kv.value);

				pJSSubKV = pJSSubKV->next;
			}
		}

		pJSVSCom = pJSVSCom->next;
	}

	return true;
}


bool CMaterialFile::InitializeFragmentShaderAspect(cJSON* pJS, CFragmentShaderAspect& rFGApt)
{
	if ((0 == pJS) || (strcmp(pJS->string, "FragmentShader") != 0))
	{
		return false;
	}

	cJSON* pJSFGCom = pJS->child;
	while (pJSFGCom)
	{
		if (strcmp(pJSFGCom->string, "Name") == 0)
		{
			rFGApt.CloneName(pJSFGCom->valuestring);
		}
		else if (strcmp(pJSFGCom->string, "NameFile") == 0)
		{
			rFGApt.CloneFileName(pJSFGCom->valuestring);
		}

		pJSFGCom = pJSFGCom->next;
	}

	return true;
}


CTextureUnitAspect* CMaterialFile::CreateTextureUnitAspect(cJSON* pJS, CMaterialAspect* pHost)
{
	if (0 == pJS)
	{
		return 0;
	}

	CTextureUnitAspect* pTextureUnitApt = new CTextureUnitAspect(pHost);
	cJSON* pJSTextureUnitCom = pJS->child;
	while (pJSTextureUnitCom)
	{
		if (strcmp(pJSTextureUnitCom->string, "NameSampler") == 0)
		{
			pTextureUnitApt->CloneNameSampler(pJSTextureUnitCom->valuestring);
		}
		else if (strcmp(pJSTextureUnitCom->string, "Texture") == 0)
		{
			CTextureAspect* pTextureApt = CreateTextureAspect(pJSTextureUnitCom, pTextureUnitApt);
			if (0 == pTextureApt)
			{
				delete pTextureUnitApt;
				return 0;
			}

			pTextureUnitApt->setNameFile(pTextureApt->namePathFile());
			pTextureUnitApt->setTextureApt(pTextureApt);
		}

		pJSTextureUnitCom = pJSTextureUnitCom->next;
	}

	return pTextureUnitApt;
}


CTextureAspect* CMaterialFile::CreateTextureAspect(cJSON* pJS, CTextureUnitAspect* pHost)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Texture") != 0))
	{
		return 0;
	}

	CTextureAspect* pTextureApt = new CTextureAspect(pHost);
	cJSON* pJSTextureCom = pJS->child;
	while (pJSTextureCom)
	{
		if (strcmp(pJSTextureCom->string, "Name") == 0)
		{
			pTextureApt->CloneName(pJSTextureCom->valuestring);
		}
		else if (strcmp(pJSTextureCom->string, "NameFile") == 0)
		{
			pTextureApt->CloneFileName(pJSTextureCom->valuestring);
		}

		pJSTextureCom = pJSTextureCom->next;
	}

	return pTextureApt;
}



void CMaterialFile::Destroy()
{
	if (0 != m_pMatlApt)
	{
		delete m_pMatlApt;
		m_pMatlApt = 0;
	}

	if (0 != m_pJSSource)
	{
		cJSON_Delete(m_pJSSource);
	}
}



