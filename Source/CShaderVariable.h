/*

CShaderVariable


Author:  Zhen Yi

Created Date: Nov. 18, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SHADER_VARIABLE_
#define _FW_SHADER_VARIABLE_

#include"CBase.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class DLLCOAPI CShaderVariable : public CBase
	{
	public:
		CShaderVariable() {}
		CShaderVariable(const char* pszName):CBase(pszName) {}
		virtual ~CShaderVariable() {}
	};
}

#endif // !_FW_SHADER_VARIABLE_
