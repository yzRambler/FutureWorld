/*
CDirectLight

Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_DIRECTLIGHT_
#define _FW_DIRECTLIGHT_

#include"CLight.h"

namespace FW
{
	class DLLCOAPI CDirectLight : public CLight
	{
	public:
		CDirectLight(CConstruct* pHost);
		CDirectLight(const char* pszName, CConstruct* pHost);
		virtual ~CDirectLight();

		const Vector4& getDirect() { return m_v4Direct; }


	//Inheriate from CLight
	public:
		virtual bool Create(FDWORD idSpaceTime);


	private:
		Vector4 m_v4Direct;
	};
}



#endif // !_FW_DIRECTLIGHT_
