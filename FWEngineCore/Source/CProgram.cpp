#include "CMesh.h"
#include "CLight.h"
#include "CMaterial.h"
#include "CProgram.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CDirectLight.h"
#include "CVertexAttribute.h"
#include "CParameterUniform.h"
#include "CTextureUnit.h"
#include "IDataResource.h"

#ifndef _WND_OPENGL_PLATFORM_

#include<emscripten.h>

#define _WEB_DEBUG_

#endif


#define BUFFER_OFFSET(offset) ((void *)(offset))

using namespace FW;

CProgram::CProgram(CConstruct* pHost) : CPrimatter(pHost), m_pVertexShader(nullptr), 
m_pFragmentShader(nullptr), m_eGenVS(EGEN::GE_UNKNOW), m_eGenFS(EGEN::GE_UNKNOW)
{
}

CProgram::CProgram(const char* pszName, CConstruct* pHost) :CPrimatter(pszName, pHost), 
m_pVertexShader(nullptr), m_pFragmentShader(nullptr), m_eGenVS(EGEN::GE_UNKNOW), m_eGenFS(EGEN::GE_UNKNOW)
{
}

CProgram::~CProgram()
{
	Destroy();
}


bool CProgram::Create()
{
	if ((nullptr == m_pVertexShader) || (nullptr == m_pFragmentShader))
	{
		return false;
	}

	if ((m_pVertexShader->state() != EPMTSTATE::READY) 
		|| (m_pFragmentShader->state() != EPMTSTATE::READY))
	{
		return false;
	}


	m_idProgram = glCreateProgram();
	if (0 == m_idProgram)
	{
		return false;
	}

	m_idVS = m_pVertexShader->getShaderID();
	m_idFS = m_pFragmentShader->getShaderID();

	m_eGenVS = m_pVertexShader->gen();
	m_eGenFS = m_pFragmentShader->gen();


	glAttachShader(m_idProgram, m_idVS);
	glAttachShader(m_idProgram, m_idFS);

	glLinkProgram(m_idProgram);


	GLint result = 0;
	glGetProgramiv(m_idProgram, GL_LINK_STATUS, &result);
	if (GL_FALSE == result)
	{
		GLint lenInfo = 0;
		glGetProgramiv(m_idProgram, GL_INFO_LOG_LENGTH, &lenInfo);
		char* pInfo = new char[lenInfo];
		glGetProgramInfoLog(m_idProgram, lenInfo, NULL, pInfo);

#ifdef _WEB_DEBUGP_
		EM_ASM({ console.log("program link failed. Reason: " + UTF8ToString($0)); }, (char*)pInfo);
#endif

		delete[] pInfo;

		Destroy();
		return false;
	}

	for (VTPU_ITER iter = m_vtParaUniform.begin(); iter != m_vtParaUniform.end(); iter++)
	{
		(*iter)->setProgramID(m_idProgram);
	}



	return true;
}



void CProgram::Destroy()
{
	IDataResource* pIDR = CreateDataResource();
	if(nullptr != m_pVertexShader)
	{
		if (CIDManager::Instance().Inquire(m_idVS))
		{
			pIDR->ReleasePrimatter(m_pVertexShader);
		}
		else
		{
			if (m_eGenVS != EGEN::GE_ORG_PM)
			{
				//Now it confirm that CVertexShader object is created by colon/copy/file paring.
				delete m_pVertexShader;
			}
		}

		m_pVertexShader = nullptr;
		m_idVS = 0;
	}


	if(nullptr != m_pFragmentShader)
	{
		if (CIDManager::Instance().Inquire(m_idFS))
		{
			pIDR->ReleasePrimatter(m_pFragmentShader);
		}
		else
		{
			if (m_eGenFS != EGEN::GE_ORG_PM)
			{
				//Now, it confirm the CFragmentShader object is created by colon/copy/file paring.
				delete m_pFragmentShader;
			}
		}


		m_pFragmentShader = nullptr;
		m_idFS = 0;
	}


	for (VTVA_ITER iter = m_vtVertexAttr.begin(); iter != m_vtVertexAttr.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;
		}
	}

	m_vtVertexAttr.clear();


	for (VTPU_ITER iter = m_vtParaUniform.begin(); iter != m_vtParaUniform.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;
		}
	}

	m_vtParaUniform.clear();



	glDeleteProgram(m_idProgram);
}


bool CProgram::SetVertexAttributs(CRenderUnit* pRenderUnit)
{

	if ((0 == m_idProgram) || (0 == pRenderUnit))
	{
		return false;
	}

	GLint  n = 0;
	glGetProgramiv(m_idProgram, GL_ACTIVE_ATTRIBUTES, &n);


	CVertexAttribute* pVertexAttrib = 0;
	for(int i=0; i<m_vtVertexAttr.size(); i++)
	{
		pVertexAttrib = m_vtVertexAttr[i];
		if (0 != pVertexAttrib)
		{
			GLint localVA = glGetAttribLocation(m_idProgram, pVertexAttrib->varName());
			if (localVA < 0)
			{
				return false;
			}

			glEnableVertexAttribArray(localVA);
			glVertexAttribPointer(localVA, pVertexAttrib->count(), GL_FLOAT, GL_FALSE, 
				pRenderUnit->sizeVertex(), BUFFER_OFFSET(pVertexAttrib->local()));
		}
	}



	return true;

}



bool CProgram::SetUniformParameters()
{
	CMaterial* pMatl = (CMaterial*)m_pHost->host();
	CParaUniformTexture* pPUT = 0;
	CTextureUnit* pTextUt = 0;
	for (int i = 0; i < m_vtParaUniform.size(); i++)
	{
		if (!m_vtParaUniform[i]->active())
		{
			continue;
		}

		//check whether or not use texture
		if (m_vtParaUniform[i]->typeShaderUniform() == ESUTYPE::SU_TEXTURE)
		{
			pPUT = (CParaUniformTexture*)m_vtParaUniform[i];
			pTextUt = pMatl->textureUnit(pPUT->indexOfTextureArray());

			pPUT->setTextureUnitId(pTextUt->idTextureUnit());
			pPUT->setTextureId(pTextUt->texture()->idTexture());
		}

		m_vtParaUniform[i]->Process();
	}

	return true;
}



void CProgram::UpdateCameraLight(CCamera* pCame, VTLIT& vtLights)
{
	CParaUniformCamera* pPUCam = 0;
	CParaUniformLight* pPULit = 0;
	CLight* pLit = 0;
	for (int i = 0; i < m_vtParaUniform.size(); i++)
	{
		if (m_vtParaUniform[i]->typeShaderUniform() == ESUTYPE::SU_CAMERA)
		{
			pPUCam = (CParaUniformCamera*)m_vtParaUniform[i];
			
			switch (pPUCam->valueType())
			{
			case ESHCAMVALTYPE::SCV_V:
			{
				pPUCam->BindMatrixValue((Matrix4x4&)pCame->matView());
			}
			break;

			case ESHCAMVALTYPE::SCV_MV:
			{
				pPUCam->BindMatrixValue((Matrix4x4&)pCame->matView());
			}
			break;

			case ESHCAMVALTYPE::SCV_MVP:
			{
				Matrix4x4 mat = pCame->matView();
				mat *= pCame->matProjection();
				pPUCam->BindMatrixValue(mat);
			}
			break;

			case ESHCAMVALTYPE::SCV_PROJ:
			{
				pPUCam->BindMatrixValue((Matrix4x4&)pCame->matProjection());
			}
			break;

			case ESHCAMVALTYPE::SCV_POS:
			{
				pPUCam->BindVectorValue((Vector3&)pCame->pos());
			}
			break;

			default:
				break;
			}

			continue;
		}
		else if (m_vtParaUniform[i]->typeShaderUniform() == ESUTYPE::SU_LIGHT)
		{
			if (!vtLights.empty())
			{
				pPULit = (CParaUniformLight*)m_vtParaUniform[i];
				pLit = vtLights[pPULit->indexOfLightArray()];
				if (0 == pLit)
				{
					continue;
				}

				switch (pPULit->valueType())
				{
				case ESHLITVALTYPE::SLV_INTENSITY:
				{
					pPULit->BindFloatValue(pLit->intensity());
				}
				break;

				case ESHLITVALTYPE::SLV_POS:
				{
					pPULit->BindVector3Value(pLit->pos());
				}
				break;

				case ESHLITVALTYPE::SLV_COLOR:
				{
					pPULit->BindVector4Value(pLit->color());
				}
				break;

				case ESHLITVALTYPE::SLV_DIRECT:
				{
					if (pLit->typeLight() == CLight::ELITTYPE::LT_DIRECT)
					{
						pPULit->BindVector4Value((Vector4&)((CDirectLight*)pLit)->getDirect());
					}
				}
				break;

				default:
					break;
				}
			}

		}
	}
}



void CProgram::UpdateWorldMatrix(Matrix4x4& matWorld)
{
	CParaUniformCamera* pPUCam = 0;
	CParaUniformWorldTransform* pPUWT = 0;
	for (int i = 0; i < m_vtParaUniform.size(); i++)
	{
		if (m_vtParaUniform[i]->typeShaderUniform() == ESUTYPE::SU_WORLDTF)
		{
			pPUWT = (CParaUniformWorldTransform*)m_vtParaUniform[i];
			pPUWT->setWorldMatrix(matWorld);

			continue;
		}
		else if (m_vtParaUniform[i]->typeShaderUniform() == ESUTYPE::SU_CAMERA)
		{
			pPUCam = (CParaUniformCamera*)m_vtParaUniform[i];
			switch (pPUCam->valueType())
			{
			case ESHCAMVALTYPE::SCV_MV:
			case ESHCAMVALTYPE::SCV_MVP:
			{
				pPUCam->ComputeOutputMatrix(matWorld);
			}
			break;

			default:
				break;
			}
		}
 	}
}
