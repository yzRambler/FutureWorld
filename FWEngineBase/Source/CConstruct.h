/*

CConstruct 



Author: Zhen Yi (взеђ)

Create Date: Feb. 19, 2023

Version 0.2.1 Alpha

*/


#ifndef _FW_CONSTRUCT_
#define _FW_CONSTRUCT_

#include"CBase.h"
#include"CommonPrimatter.h"
#include"BaseData.h"
#include"FWEngineBaseExport.h"


namespace FW
{
	class IPrimatterManager;
	class IRenderManager;
	class DLLBSAPI CConstruct : public CBase
	{
	public:
		CConstruct(CConstruct* pHost, ECONSTRTYPE typeCST = ECONSTRTYPE::CST_UNKNOWN);

		CConstruct(const char* pszName, CConstruct* pHost, ECONSTRTYPE typeCST =
			ECONSTRTYPE::CST_UNKNOWN);

		virtual ~CConstruct();

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
