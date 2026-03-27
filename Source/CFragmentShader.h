/*
CFragmentShader


Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_FRAGMENTSHADER_
#define _FW_FRAGMENTSHADER_

#include "CShader.h"


namespace FW
{
	class DLLCOAPI CFragmentShader : public CShader
	{
	public:
		CFragmentShader(CConstruct* pHost);
		CFragmentShader(const char* pszName, CConstruct* pHost);
		virtual ~CFragmentShader();

		//Inherit from CShader
		virtual bool Create(char* pShaderFileBuffer);

	};
}



#endif // !_FW_FRAGMENTSHADER_
