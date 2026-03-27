/*
CAspect

Author: Zhen Yi
Created Date: May 08, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_ASPECT_
#define _FW_ASPECT_



#include"CBase.h"
#include"CommonPrimatter.h"
#include "IPrimatterManager.h"

namespace FW
{
	class CConstruct;
	class CAspectCenter;
	class CAspect : public CBase
	{
	public:
		CAspect(CAspect* pHost = 0) :m_eState(EAPTSTATE::APT_UNKNOWN), 
			m_eAppState(EAPPPRRES::APP_UNKNOWN), m_pHost(pHost), m_eTypeApt(EAPTTYPE::CST_UNKNOWN), 
			m_id(0), m_eGenFrom(EGEN::GE_UNKNOW){}

		CAspect(const char* pszName, CAspect* pHost = 0) : CBase(pszName), 
			m_eState(EAPTSTATE::APT_UNKNOWN), m_eAppState(EAPPPRRES::APP_UNKNOWN), m_pHost(pHost),
			m_eTypeApt(EAPTTYPE::CST_UNKNOWN), m_id(0), m_eGenFrom(EGEN::GE_UNKNOW){}

		virtual ~CAspect();// {}


		/*
		* The host need be reset by setHost after calling Clone.
		*/
		virtual bool Clone(CAspect * pAptSrc);



		virtual bool Copy(CAspect* pAptSrc);



		/*
		* The host need be reset by setHost after calling Clone.
		* Parameter n = 0: only create a instance object; = 1: clone (create new) current object. 
		*/
		virtual CAspect* Duplicate(int n);


		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent) { return EAPTSTATE::APT_UNKNOWN; }

		//Just check the CConstruct object state
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst) { return true; }

		//Just check the CConstruct object state
		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent) 
		{ return EPMTSTATE::UNKNOWN; }




	//attribute
	public:
		FDWORD id() { return m_id; }
		void setID(FDWORD id) { m_id = id; }

		FDWORD idCorrelateCst() { return m_idCorrelateCst; }
		void setIDCorrelateCst(FDWORD id) { m_idCorrelateCst = id; }

		EGEN gen() { return m_eGenFrom; }

		EAPTSTATE state() { return m_eState; }
		void setState(EAPTSTATE state) { m_eState = state; }

		EAPPPRRES appState() { return m_eAppState; }
		void setAppState(EAPPPRRES state) { m_eAppState = state; }

		void setHost(CAspect* pHost) { m_pHost = pHost; }
		CAspect* host() { return m_pHost; }

		void setTypeApt(EAPTTYPE type) { m_eTypeApt = type; }
		EAPTTYPE typeApt() { return m_eTypeApt; }


	protected:
		//Complete just in  subclass.
		virtual CAspect* CreateInstance() { return 0; }



	private:
		EGEN m_eGenFrom;

		FDWORD m_id;
		FDWORD m_idCorrelateCst;

		EAPTSTATE m_eState;
		EAPPPRRES m_eAppState;

		EAPTTYPE m_eTypeApt;

		CAspect* m_pHost;
	};

}


#endif // !_FW_ASPECT_
