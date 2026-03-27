/*
CSkeletonAnimation

Author: YiZhen
Created Date: Dec. 06, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_SKELETONANIMATION_

#include"CAnimation.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class DLLCOAPI CSkeletonAnimation : public CAnimation
	{
	public:
		CSkeletonAnimation(CConstruct* pHost);
		CSkeletonAnimation(const char* pszName, CConstruct* pHost);
		virtual ~CSkeletonAnimation();

	//Inheriate from CPrimatter
	public:
		virtual bool Clone(CPrimatter* pPmt);


    //derive from CAnimation
	public:
		virtual bool CopyWithSkeleton(CAnimation* pAniSrc, CSkeleton* pSkeleton);
		virtual void Update(long lDltTime);

	//property
	public:
		const char* nameSkeleton() { return m_strSkeletonName.Get(); }

		void setSkeletonName(const char* pszSKName) { m_strSkeletonName.Set(pszSKName); }

		CSkeleton* skeleton() { return m_pSkeleton; }
		void setSkeleton(CSkeleton* pSkeleton)
		{
			if ((pSkeleton != 0) && (m_pSkeleton == 0))
			{ m_pSkeleton = pSkeleton; m_idSkeleton = pSkeleton->id(); }
		}

		bool majorCompleted() { return m_bMajorCompleted; }

	private:
		//Just reference. Must not delete it.
		CSkeleton* m_pSkeleton;

		//for check
		FDWORD m_idSkeleton;

		CString m_strSkeletonName;
		bool m_bMajorCompleted;
	};
	
}

#endif // !_FW_SKELETONANIMATION_
