/*

CConstruct 



Author: Zhen Yi

Created Date: Feb. 19, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_CONSTRUCT_
#define _FW_CONSTRUCT_

#include"CBase.h"
#include"CommonPrimatter.h"
#include"FWEngineCoreExport.h"
#include"IPrimatterManager.h"


namespace FW
{
	//class CConstruct : public CBase
	class DLLCOAPI CConstruct : public CBase
	{
	public:
		CConstruct(CConstruct* pHost, ECONSTRTYPE typeCST = ECONSTRTYPE::CST_UNKNOWN): m_id(0), 
			m_pHost(pHost), m_eConType(typeCST), m_eState(EPMTSTATE::UNKNOWN), m_bActive(true),
			m_eGenFrom(EGEN::GE_UNKNOW){}

		CConstruct(const char* pszName, CConstruct* pHost, ECONSTRTYPE typeCST =
			ECONSTRTYPE::CST_UNKNOWN):CBase(pszName), m_id(0), m_pHost(pHost), 
			m_eConType(typeCST), 
			m_eState(EPMTSTATE::UNKNOWN), m_bActive(true), m_eGenFrom(EGEN::GE_UNKNOW){}

		virtual ~CConstruct(){}

		virtual void Update(float ratio, long lDltTime, IPrimatterManager* pPmtCent, 
			IRenderManager* pRenderMag) {}




	//attribute
	public:
		FDWORD id() { return m_id; }
		void setID(FDWORD id) { m_id = id; }

		FDWORD idIntTarget() { return m_idIntTarget; }
		void setIDIntTarget(FDWORD id) { m_idIntTarget = id; }

		bool isReady() { return m_eState == EPMTSTATE::READY; }

		ECONSTRTYPE typeCST() { return m_eConType; }
		void setTypeCST(ECONSTRTYPE type) { m_eConType = type; }

		EPMTSTATE state() { return m_eState; }
		void setState(EPMTSTATE state) { m_eState = state; }

		void setHost(CConstruct* pHost) { m_pHost = pHost; }
		CConstruct* host() { return m_pHost; }

		bool active() { return m_bActive; }
		void setActive(bool active) { m_bActive = active; }

		EGEN gen() { return m_eGenFrom; }
		void setGen(EGEN gen) { m_eGenFrom = gen; }


	protected:
		CConstruct* m_pHost;
	
	private:
		FDWORD m_id;
		FDWORD m_idIntTarget;  //reserve for CInterchangeCenter

		EGEN m_eGenFrom;

		EPMTSTATE m_eState;
		ECONSTRTYPE m_eConType;
		bool m_bActive;

	};
}



#endif // !_FW_CONSTRUCT_
