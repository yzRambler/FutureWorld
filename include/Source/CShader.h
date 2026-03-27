/*
CShader


Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_SHADER_
#define _FW_SHADER_

#include<string.h>
#include "GL/glew.h"
#include "CPrimatter.h"
#include "CommonPrimatter.h"
#include "FWEngineCoreExport.h"

namespace FW
{
	class CProgram;
	class DLLCOAPI CShader : public CPrimatter
	{
	public:
		CShader(CConstruct* pHost, ESHDTYPE type = ESHDTYPE::SH_UNKOWN);
		CShader(const char* pszName, CConstruct* pHost, ESHDTYPE type = ESHDTYPE::SH_UNKOWN);
		virtual ~CShader();

		virtual bool Create(char* pShaderFileBuffer) { return true; }


	//attribute
	public:
		CProgram* host() { return (CProgram*)m_pHost; }

		ESHDTYPE typeShader() { return m_eTypeShader; }
		GLuint getShaderID() { return m_idShader; }


	protected:
		bool Create(const char* pString, GLuint idShader);


	private:
		void Destroy();



	protected:
		char* m_parScript;
		int m_nLen;
		GLuint m_idShader;

		ESHDTYPE m_eTypeShader;

	};

}

#endif // !_FW_SHADER_

