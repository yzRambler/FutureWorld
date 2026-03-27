/*
CMeshAspect

Author: Zhen Yi
Created Date:  May 08, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_MESHASPECT_
#define _FW_MESHASPECT_

#include "CPrimatterAspect.h"

namespace FW
{
	class CComesh;
	class CComeshAspect;
	class CDeformerAspect;
	class CEssetyAspect;
	class CMaterialAspect;
	class CPrimatterAspectCenter;
	class CMeshAspect : public CPrimatterAspect
	{
		//Inherit from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* = nullptr */);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);
		EAPTSTATE CheckState(CEssetyAspect* pEsetyApt, CAspectCenter* pPmtAptCent);


		//Inherit from CPrimatterAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);




	public:
		CMeshAspect(CComeshAspect* pHost);
		CMeshAspect(const char* pszName, CComeshAspect* pHost);
		virtual ~CMeshAspect();


	private:
		void Destroy();

	//attribute
	public:
		CComeshAspect* host() { return m_pHost; }

		CDeformerAspect* deformerAspect() { return m_pDeformerApt; }
		void setDeformerAspect(CDeformerAspect* pDeformerApt) { m_pDeformerApt = pDeformerApt; }

		CMaterialAspect* materialAspect() { return m_pMaterialApt; }
		void setMaterialAspect(CMaterialAspect* pMaterialApt) { m_pMaterialApt = pMaterialApt; }


		bool hasDeform() { return m_pDeformerApt != nullptr; }

	private:
		CComeshAspect* m_pHost;
		FDWORD  m_idMaterial;
		CMaterialAspect* m_pMaterialApt;
		CDeformerAspect* m_pDeformerApt;

	};

}


#endif // ! _FW_MESHASPECT_
