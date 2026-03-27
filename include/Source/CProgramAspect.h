/*
CProgramAspect

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_PROGRAM_ASPECT_
#define _FW_PROGRAM_ASPECT_

#include<vector>
#include"CPrimatterAspect.h"
#include"CShaderAspect.h"

namespace FW
{
	class CPassAspect;
	class CPass;
	class CShaderVariableAspect;
	class CVertexAttributeAspect;
	class CParameterUniformAspect;
	class CProgramAspect : public CPrimatterAspect
	{
	private:
		typedef std::vector<CShaderVariableAspect*> VTSHVA;
		typedef VTSHVA::iterator VTSHVA_ITER;


	//Inherited from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);


	public:
		CProgramAspect(CPassAspect* pHost) :
			CPrimatterAspect(EPMTTYPE::PROGRAM)
		{
		}

		CProgramAspect(const char* pszName, CPassAspect* pHost) :
			CPrimatterAspect(pszName, EPMTTYPE::PROGRAM)
		{
		}

		virtual ~CProgramAspect();

		void InitializeAppState(EAPPPRRES appState);
		void AddVertexAttribute(CVertexAttributeAspect* pVAA);
		void AddParaUniform(CParameterUniformAspect* pPUA);

		//Keep order: VertexPos < VertexNormal < VertexTangent < VertexUV
		void VertexAttrSort();


	


	//attribute
	public:
		CVertexShaderAspect& vertexShader() { return m_jVertexShaderApt; }
		CFragmentShaderAspect& fragmentShader() { return m_jFragmentShaderApt; }


		int countVertexAttrApt() { return m_vtVertexAttribute.size(); }
		CVertexAttributeAspect* vertexAttrApt(int ind)
		{
			if ((ind < 0) || (ind >= m_vtVertexAttribute.size())) { return 0; }
			return (CVertexAttributeAspect*)m_vtVertexAttribute[ind];
		}


		int countParaUniformApt() { return m_vtParaUniform.size(); }
		CParameterUniformAspect* paraUnifApt(int ind)
		{
			if ((ind < 0) || (ind >= m_vtParaUniform.size())) { return 0; }
			return (CParameterUniformAspect*)m_vtParaUniform[ind];
		}


	private:
		void ClearVertexAttributeSet();
		void Destory();



	private:
		CVertexShaderAspect m_jVertexShaderApt;
		CFragmentShaderAspect m_jFragmentShaderApt;


		VTSHVA m_vtVertexAttribute;
		VTSHVA m_vtParaUniform;
	};
}


#endif // !_FW_PROGRAM_ASPECT_
