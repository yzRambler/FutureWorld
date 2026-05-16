/*

CComponent

Author: Zhen Yi (взеђ)
Create Date: May 07, 2021

Version 0.2.1 Alpha

*/


#ifndef _FW_COMPONENT_
#define _FW_COMPONENT_

#include"IPrimatterManager.h"
#include"CConstruct.h"
#include"CommonPrimatter.h"

namespace FW
{
	class CEssety;
	class CListener;
	class DLLBSAPI CComponent : public CConstruct
	{
	public:
		CComponent(CConstruct* pHost, ECOMTYPE type = ECOMTYPE::CO_UNKNOW);

		CComponent(const char* pszName, CConstruct* pHost, ECOMTYPE type = ECOMTYPE::CO_UNKNOW);

		virtual ~CComponent();

		
		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent) = 0;



		//attribute
	public:
		ECOMTYPE type() { return m_eType; }

		virtual CListener* getListener() { return nullptr; }



	protected:
		ECOMTYPE m_eType;
	};


}



#endif // !_FW_COMPONENT_
