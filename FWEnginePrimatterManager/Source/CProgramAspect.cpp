#include"CProgramAspect.h"
#include"CShaderAspect.h"
#include"CShader.h"
#include"CommonPrimatter.h"
#include"CShaderVariableAspect.h"
#include"CParameterUniform.h"

using namespace FW;



CProgramAspect::~CProgramAspect()
{
	Destory();
}



void CProgramAspect::ClearVertexAttributeSet()
{
	for (VTSHVA_ITER iter = m_vtVertexAttribute.begin(); iter != m_vtVertexAttribute.end(); ++iter)
	{
		if ((*iter) != 0)
		{
			delete (*iter);
		}
	}

	m_vtVertexAttribute.clear();
}



bool CProgramAspect::InitializeCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
{
	return true;
}



EPMTSTATE CProgramAspect::CheckCorrelateConstruct(CConstruct** ppConstruct,
	IPrimatterManager* pPmtCent)
{
	return EPMTSTATE::READY;
}




bool CProgramAspect::Copy(CAspect* pAptSrc)
{
	//In this step, the result of Copy or Clone is same.
	if (!Clone(pAptSrc))
	{
		return false;
	}
	
	return CPrimatterAspect::Copy(pAptSrc);
}



bool CProgramAspect::Clone(CAspect* pAptSrc)
{
	//clear all members
	Destory();


	if (!CPrimatterAspect::Clone(pAptSrc))
	{
		return false;
	}


	CProgramAspect* pProgramApt = (CProgramAspect*)pAptSrc;


	CVertexAttributeAspect* pVAA = 0;
	for (int i = 0; i < pProgramApt->m_vtVertexAttribute.size(); i++)
	{
		pVAA = new CVertexAttributeAspect;
		pVAA->Clone((CVertexAttributeAspect*)pProgramApt->m_vtVertexAttribute[i]);
		m_vtVertexAttribute.push_back(pVAA);
	}


	CParameterUniformAspect* pPUA = 0;
	for (int i = 0; i < pProgramApt->m_vtParaUniform.size(); i++)
	{
		pPUA = (CParameterUniformAspect*)pProgramApt->m_vtParaUniform[i];
		switch (pPUA->typeShaderUniform())
		{
		case ESUTYPE::SU_CAMERA:
		{
			CParaUniformCameraAspect* pPUCAS = (CParaUniformCameraAspect*)pPUA;
			CParaUniformCameraAspect* pPUCAT = new CParaUniformCameraAspect;
			if (!pPUCAT->Clone(pPUCAS))
			{
				delete pPUCAT;
				ClearVertexAttributeSet();

				return false;
			}

			m_vtParaUniform.push_back(pPUCAT);

		}
		break;

		case ESUTYPE::SU_LIGHT:
		{
			CParaUniformLightAspect* pPULAS = (CParaUniformLightAspect*)pPUA;
			CParaUniformLightAspect* pPULAT = new CParaUniformLightAspect;
			if (!pPULAT->Clone(pPULAS))
			{
				delete pPULAT;
				ClearVertexAttributeSet();

				return false;
			}

			m_vtParaUniform.push_back(pPULAT);

		}
		break;

		case ESUTYPE::SU_TEXTURE:
		{
			CParaUniformTextureAspect* pPUTAS = (CParaUniformTextureAspect*)pPUA;
			CParaUniformTextureAspect* pPUTAT = new CParaUniformTextureAspect;
			if (!pPUTAT->Clone(pPUTAS))
			{
				delete pPUTAT;
				ClearVertexAttributeSet();

				return false;
			}

			m_vtParaUniform.push_back(pPUTAT);

		}
		break;


		case ESUTYPE::SU_WORLDTF:
		{
			CParaUniformWorldTransformAspect* pPUWAS = (CParaUniformWorldTransformAspect*)pPUA;
			CParaUniformWorldTransformAspect* pPUWAT = new CParaUniformWorldTransformAspect(pPUWAS->name());

			if (!pPUWAT->Create(pPUWAS->shaderDataType(), pPUWAS->nameVar()))
			{
				delete pPUWAT;
				ClearVertexAttributeSet();

				return false;
			}

			m_vtParaUniform.push_back(pPUWAT);

		}
		break;

		case ESUTYPE::SU_VECTOR:
		{
			CParaUniformVectorAspect* pPUVAS = (CParaUniformVectorAspect*)pPUA;
			CParaUniformVectorAspect* pPUVAT = new CParaUniformVectorAspect;
			if (!pPUVAT->Clone(pPUVAS))
			{
				delete pPUVAT;
				ClearVertexAttributeSet();

				return false;
			}

			m_vtParaUniform.push_back(pPUVAT);
		}
		break;

		case ESUTYPE::SU_NUMBER:
		{
			CParaUniformNumberAspect* pPUNAS = (CParaUniformNumberAspect*)pPUA;
			CParaUniformNumberAspect* pPUNAT = new CParaUniformNumberAspect;
			if (!pPUNAT->Clone(pPUNAS))
			{
				delete pPUNAT;
				ClearVertexAttributeSet();

				return false;
			}

			m_vtParaUniform.push_back(pPUNAT);
		}
		break;

		default:
		{
			return false;
		}
		break;
		}

	}



	if (!m_jVertexShaderApt.Clone(&pProgramApt->m_jVertexShaderApt))
	{
		return false;
	}

	if (!m_jFragmentShaderApt.Clone(&pProgramApt->m_jFragmentShaderApt))
	{
		return false;
	}

	setState(pProgramApt->state());

	return true;
}


void CProgramAspect::InitializeAppState(EAPPPRRES appState)
{
	setAppState(appState);
	m_jVertexShaderApt.setAppState(appState);
	m_jFragmentShaderApt.setAppState(appState);
}


void CProgramAspect::AddVertexAttribute(CVertexAttributeAspect* pVAA)
{
	if (0 == pVAA)
	{
		return;
	}

	for (VTSHVA_ITER iter = m_vtVertexAttribute.begin(); iter != m_vtVertexAttribute.end(); ++iter)
	{
		if (pVAA == *iter)
		{
			return;
		}
	}

	m_vtVertexAttribute.push_back(pVAA);

}


// VertexPos < VertexNormal < VertexTangent < VertexUV
void CProgramAspect::VertexAttrSort()
{
	CVertexAttributeAspect* pVAAIn = 0;
	CVertexAttributeAspect* pVAAOut = 0;
	CVertexAttributeAspect* pTmp = 0;
	for (int i = 0; i < m_vtVertexAttribute.size(); i++)
	{
		for (int j = i + 1; j < m_vtVertexAttribute.size(); j++)
		{
			pVAAOut = (CVertexAttributeAspect*)m_vtVertexAttribute[i];
			pVAAIn = (CVertexAttributeAspect*)m_vtVertexAttribute[j];
			if (pVAAOut->typeVertexAttribute() > pVAAIn->typeVertexAttribute())
			{
				pTmp = pVAAOut;
				m_vtVertexAttribute[i] = m_vtVertexAttribute[j];
				m_vtVertexAttribute[j] = pTmp;
			}
		}
	}
}



void CProgramAspect::AddParaUniform(CParameterUniformAspect* pPUA)
{
	if (0 == pPUA)
	{
		return;
	}

	for (VTSHVA_ITER iter = m_vtParaUniform.begin(); iter != m_vtParaUniform.end(); ++iter)
	{
		if (pPUA == *iter)
		{
			return;
		}
	}

	m_vtParaUniform.push_back(pPUA);
}





void CProgramAspect::Destory()
{
	for (VTSHVA_ITER iter = m_vtVertexAttribute.begin(); iter != m_vtVertexAttribute.end(); ++iter)
	{
		if ((*iter) != 0)
		{
			delete (*iter);
		}
	}

	m_vtVertexAttribute.clear();


	for (VTSHVA_ITER iter = m_vtParaUniform.begin(); iter != m_vtParaUniform.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;
		}
	}

	m_vtParaUniform.clear();
}