/*

CSkinAspect


Author:  Zhen Yi

Created Date: Feb. 12, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_SKINASPECT_
#define _FW_SKINASPECT_

#include "CDeformerAspect.h"


namespace FW
{
	class CEssetyAspect;
	class CSkeletonAspect;
	class CSkinAspect : public CDeformerAspect
	{
		//Inheriate from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual EAPTSTATE CheckState(CEssetyAspect* pEsetyApt);
		virtual bool Clone(CAspect* pAptSrc);


		//Inherite from CPrimatterAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile)
		{
			return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
		}


	public:
		CSkinAspect(CMeshAspect* pHost);
		CSkinAspect(const char* pszName, CMeshAspect* pHost);
		virtual ~CSkinAspect() {}

		


	//attribute
	public:
		void setSkeletonApt(CSkeletonAspect* pSKApt) { m_pSkeletonApt = pSKApt; }
		CSkeletonAspect* skeletonAspect() { return m_pSkeletonApt; }


		void setSkeletonName(const char* pszName) { m_strNameSkeleton.Set(pszName); }
		const char* nameSkeleton() { return m_strNameSkeleton.Get(); }


		//Inherite from CAspect
	protected:
		virtual CAspect* CreateInstance();


	private:
		void Destroy();


	private:
		//Just reference, cann't delete it. 
		CSkeletonAspect* m_pSkeletonApt;

		//for create CSkinAspect object from file automatically.
		//const char* m_pszNameSkeleton;
		CString m_strNameSkeleton;
	};
}


#endif // !_FW_SKINASPECT_
