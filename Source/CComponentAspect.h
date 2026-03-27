/*
CComponentAspect

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_COMPONENT_ASPECT_
#define _FW_COMPONENT_ASPECT_


#include "CAspect.h"
#include "CommonPrimatter.h"

namespace FW
{
	class CPrimatterAspectCenter;
	class CEssetyAspect;
	class CComponentAspect : public CAspect
	{
	public:
		CComponentAspect(CAspect* pHost,
			ECOMTYPE type = ECOMTYPE::CO_UNKNOW) :
			CAspect(pHost),
			m_eComponentType(type) {}

		CComponentAspect(const char* pszName, CAspect* pHost,  
			ECOMTYPE type = ECOMTYPE::CO_UNKNOW) : CAspect(pszName, pHost), 
			m_eComponentType(type) {}

		virtual ~CComponentAspect() {}


		virtual CComponentAspect* CreateCoInstance(CEssetyAspect* pComHost) { return 0; }


		

	//Inherited from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst =nullptr)
		{ return true; }

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent) 
		{ return EPMTSTATE::UNKNOWN; }

		virtual bool Clone(CAspect* pAptSrc);

		virtual bool Copy(CAspect* pAptSrc);

		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent, CEssetyAspect* pEsetyApt)
		{
			return EAPTSTATE::APT_UNKNOWN;
		}




	//attribue
	public:
		bool isRenderComponentAspect() { return m_eComponentType == ECOMTYPE::CO_RENDER; }
		bool isAnimationSetAspect() { return m_eComponentType == ECOMTYPE::CO_ANIMATIONGROUP; }

		ECOMTYPE type() { return m_eComponentType; }


	protected:
		ECOMTYPE m_eComponentType;
	};
}



#endif // !_FW_COMPONENT_APECT_
