/*

CComponent

Author: Zhen Yi
Created Date: May 07, 2021
Version: 0.2.0 Alpha

*/


#ifndef _FW_COMPONENT_
#define _FW_COMPONENT_

#include"IPrimatterManager.h"

#include"CConstruct.h"
#include"CommonPrimatter.h"

namespace FW
{
	class CEssety;
	class CPrimatterCenter;
	class CComponent : public CConstruct
	{
	//Inherit form CConstruct
	public:
	//	virtual bool ReleasePrimatterAll(IPrimatterManager* pPmtCent) { return true; }


	public:
		CComponent(CConstruct* pHost, 
			ECOMTYPE type = ECOMTYPE::CO_UNKNOW) :
			CConstruct(pHost, ECONSTRTYPE::CST_COMPONENT), 
			m_eType(type) {}

		CComponent(const char* pszName, CConstruct* pHost, 
			ECOMTYPE type = ECOMTYPE::CO_UNKNOW) :
			CConstruct(pszName, pHost, ECONSTRTYPE::CST_COMPONENT), 
			m_eType(type) {}

		virtual ~CComponent() {}

		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent) = 0;



		//attribute
	public:
		ECOMTYPE type() { return m_eType; }


	protected:
		ECOMTYPE m_eType;
	};


}



#endif // !_FW_COMPONENT_
