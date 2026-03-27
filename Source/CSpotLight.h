/*

CSpotLight

Author: Zhen Yi

Created Date: Nov. 3,  2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SPOT_LIGHT_
#define _FW_SPOT_LIGHT_

#include"CLight.h"


namespace FW
{
	class CSpotLight : public CLight
	{
	public:
		CSpotLight(CConstruct* pHost):
			CLight(pHost, 
				ELITTYPE::LT_SPOT){}

		CSpotLight(const char* pszName, CConstruct* pHost):
			CLight(pszName, pHost, 
				ELITTYPE::LT_SPOT) {}

		virtual ~CSpotLight() {}
	};
}



#endif // !_FW_SPOT_LIGHT_
