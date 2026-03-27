/*

CSkeletonAspect



Author:  Zhen Yi

Created Date:  Feb. 12, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SKELETON_ASPECT_
#define _FW_SKELETON_ASPECT_

#include "CPrimatterAspect.h"

namespace FW
{
	class CSkeletonAspect : public CPrimatterAspect
	{
		//Inherited from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);


	public:
		CSkeletonAspect();
		CSkeletonAspect(const char* pszName);
		virtual ~CSkeletonAspect();

		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);



	};

};




#endif // !_FW_SKELETON_ASPECT_
