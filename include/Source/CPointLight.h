/*

CPointLight


Author: Zhen Yi

Created Date: Nov. 3, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_POINT_LIGHT_
#define _FW_POINT_LIGHT_

#include"CLight.h"

namespace FW
{
	class CPointLight : public CLight
	{
	public:
		CPointLight(CConstruct* pHost): 
			CLight(pHost, 
				ELITTYPE::LT_POINT) {}

		CPointLight(const char* pszName, CConstruct* pHost):
			CLight(pszName, pHost, //pComHost, 
				ELITTYPE::LT_POINT) {}

		virtual ~CPointLight() {}
	};
}


#endif // !_FW_POINT_LIGHT_

