/*
CDeformer

       CDeformer is not independent primatter, so it do not possess the id itself.


Author: Zhen Yi
Created Date: Dec. 05, 2022

Version: 0.2.0 Alpha

*/


#ifndef _FW_DEFORMER_
#define _FW_DEFORMER_

#include "CPrimatter.h"
#include"CommonPrimatter.h"


namespace FW
{
	class CMesh;

	/*
	  Important:
		 CDeformer is not independent primatter, so it do not possess the id itself.
	*/
	class CDeformer : public CPrimatter
	{
	//Inherit from CPrimatter
	public:
		virtual bool ReleaseAllSubPrimatter(IPrimatterManager* pPmtCent) { return true; }


	public:
		CDeformer(CConstruct* pHost, EDEFORMTYPE type = EDEFORMTYPE::DE_UNKNOWN) :
			CPrimatter(pHost, EPMTTYPE::DEFORMER), m_eDefType(type) {}

		CDeformer(const char* pszName, CConstruct* pHost, EDEFORMTYPE type = EDEFORMTYPE::DE_UNKNOWN) :
			CPrimatter(pszName, pHost, EPMTTYPE::DEFORMER), m_eDefType(type) {}

		virtual ~CDeformer(){}

		virtual void Update(CMesh* pMesh) {}



	//attribute
	public:
		EDEFORMTYPE type() { return m_eDefType; }
		void setType(EDEFORMTYPE type) { m_eDefType = type; }

		CMesh* host() { return (CMesh*)m_pHost; }

	private:
		EDEFORMTYPE m_eDefType;
	};

}


#endif // !_FW_DEFORMER_
