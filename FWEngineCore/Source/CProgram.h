/*
CProgram
     CProgram is not independent primatter, so it do not possess the id itself.

Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_PROGRAM_
#define _FW_PROGRAM_

#include <vector>

#include "GL/glew.h"
#include "Common.h"

#include "CPrimatter.h"
#include "CVertexShader.h"
#include "CFragmentShader.h"
#include "CPass.h"
#include "EngineCoreCommon.h"
#include "CParameterUniform.h"
#include "FWEngineCoreExport.h"
#include "MathLibrary.h"


namespace FW
{
	class CMaterial;
	class CMesh;
	class CCamera;
	class CRenderUnit;
	class CVertexAttribute;

	/*
	  Important:
		 CProgram is not independent primatter, so it do not possess the id itself.
	*/

	class DLLCOAPI CProgram : public CPrimatter
	{
	private:
		typedef std::vector<CVertexAttribute*> VTVA;
		typedef VTVA::iterator VTVA_ITER;

		typedef std::vector<CParameterUniform*> VTPU;
		typedef VTPU::iterator VTPU_ITER;




	public:
		CProgram(CConstruct* pHost);
		CProgram(const char* pszName, CConstruct* pHost);
		virtual ~CProgram();

		bool Create();


		bool SetVertexAttributs(CRenderUnit* pRenderUnit);
		bool SetUniformParameters();

		void UseProgram() { glUseProgram(m_idProgram); }

		void UpdateCameraLight(CCamera* pCame, VTLIT& vtLights);

		//The UpdateCameraLight has been called before this.
		void UpdateWorldMatrix(Matrix4x4& matWorld);

		void AppendVertexAttribute(CVertexAttribute* pVertexAttr) 
		{ if (0 != pVertexAttr) { m_vtVertexAttr.push_back(pVertexAttr); } }

		void AppendParameterUniform(CParameterUniform* pParaUniform)
		{
			if (0 != pParaUniform) { pParaUniform->setProgramID(m_idProgram); m_vtParaUniform.push_back(pParaUniform); }
		}




	//attribute
	public:
		CPass* host() { return (CPass*)m_pHost; }

		void setVertexShader(CVertexShader* pVShader) 
		{
			m_pVertexShader = pVShader; m_idVS = pVShader->id();
		}

		CVertexShader* vertexShader() { return m_pVertexShader; }


		void setFragmentShader(CFragmentShader* pFShader) 
		{
			m_pFragmentShader = pFShader; m_idFS = pFShader->id();
		}

		CFragmentShader* fragmentShader() { return m_pFragmentShader; }


		GLuint idProgram() { return m_idProgram; }
		void setProgramID(GLuint id) { m_idProgram = id; }

		int countVertexAttribute() { return m_vtVertexAttr.size(); }
		CVertexAttribute* vertexAttr(int ind)
		{
			if ((ind < 0) || (ind >= m_vtVertexAttr.size())) { return 0; }
			return m_vtVertexAttr[ind];
		}

		int countParaUniform() { return m_vtParaUniform.size(); }
		CParameterUniform* paraUniform(int ind) 
		{
			if ((ind < 0) || (ind >= m_vtParaUniform.size())) { return 0; }
			return m_vtParaUniform[ind];
		}

		CParameterUniform* findParaUniform(const char* pszVarName)
		{
			for (int i = 0; i < m_vtParaUniform.size(); i++)
			{
				if (strcmp(m_vtParaUniform[i]->nameVar(), pszVarName) == 0){ return m_vtParaUniform[i];	}
			}

			return 0;
		}



	private:
		void Destroy();


	private:
		GLuint m_idProgram;

		CVertexShader* m_pVertexShader;
		CFragmentShader* m_pFragmentShader;
		FDWORD m_idVS;
		EGEN m_eGenVS;

		FDWORD m_idFS;
		EGEN m_eGenFS;

		VTVA m_vtVertexAttr;
		VTPU m_vtParaUniform;

	};

}
	
#endif // !_FW_PROGRAM_

