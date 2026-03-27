/*

CDeformerAspect


Author:  Zhen Yi

Created Date:  Feb. 16, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_DEFORMERASPECT_
#define _FW_DEFORMERASPECT_

#include"CPrimatterAspect.h"
#include"CommonPrimatter.h"


namespace FW
{
	class CMeshAspect;
	class CMesh;
	class CDeformerAspect : public CPrimatterAspect
	{
		//Inherited from CAspect 
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */)
		{
			return true;
		}

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent)
		{
			return EPMTSTATE::READY;
		}

		virtual bool Clone(CAspect* pAptSrc)
		{
			if (0 == pAptSrc) { return false; }

			CDeformerAspect* pDefApt = (CDeformerAspect*)pAptSrc;

			m_eDefType = pDefApt->m_eDefType;

			return true;
		}


		virtual bool Copy(CAspect* pAptSrc)
		{
			if (0 == pAptSrc) { return false; }

			CDeformerAspect* pDefApt = (CDeformerAspect*)pAptSrc;

			m_eDefType = pDefApt->m_eDefType;

			return true;
		}




	public:
		CDeformerAspect(CMeshAspect* pHost, EDEFORMTYPE type = EDEFORMTYPE::DE_UNKNOWN) :
			CPrimatterAspect(EPMTTYPE::DEFORMER), m_eDefType(type), m_pHost(pHost)
		{
		}

		CDeformerAspect(const char* pszName, CMeshAspect* pHost, EDEFORMTYPE type = EDEFORMTYPE::DE_UNKNOWN) :
			CPrimatterAspect(pszName, EPMTTYPE::DEFORMER), m_eDefType(type), m_pHost(pHost)
		{
		}

		virtual ~CDeformerAspect() {}

		




		//attribute
	public:
		EDEFORMTYPE typeDef() { return m_eDefType; }
		void setTypeDef(EDEFORMTYPE type) { m_eDefType = type; }

		CMeshAspect* host() { return m_pHost; }


		//Inherite from CAspect
	protected:
		virtual CAspect* CreateInstance() { return nullptr; }


	private:
		CMeshAspect* m_pHost;
		EDEFORMTYPE m_eDefType;

	};
}



#endif // !_FW_DEFORMASPECT_
