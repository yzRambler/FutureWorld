/*
CSkeletonAnimationAspect


Author:  Zhen Yi

Created Date: Feb. 02, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_SKELETONANIMATION_ASPECT_
#define _FW_SKELETONANIMATION_ASPECT_

#include "CAnimationAspect.h"

namespace FW
{
	class CSkeletonAspect;
	class CSkeletonAnimationAspect : public CAnimationAspect
	{
	public:
		CSkeletonAnimationAspect();
		CSkeletonAnimationAspect(const char* pszName);
		virtual ~CSkeletonAnimationAspect();

		bool Initialize(const char* pszName, const char* pszNamePathAndFile, 
			CSkeletonAspect* pSkeletonApt);


	//Inherited from CAnimationAspcet
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst =nullptr );

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);

	//attribute
	public:
		void setSkeletonAspect(CSkeletonAspect* pSkApt) { m_pSkeletonApt = pSkApt; }
		CSkeletonAspect* skeletonAspect() { return m_pSkeletonApt; }

	//Inherite from CAspect
	protected:
		virtual CAspect* CreateInstance() { return new CSkeletonAnimationAspect(); }



	private:
		void Destroy();

	private:
		CSkeletonAspect* m_pSkeletonApt;

	};
};




#endif // !_FW_SKELETONANIMATION_ASPECT_
