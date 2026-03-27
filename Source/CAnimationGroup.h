/*
CAnimationGroup

Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_ANIMATIONGROUP_
#define _FW_ANIMATIONGROUP_

#include<map>
#include"CComponent.h"
#include"TemplateLibrary.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class CAnimation;
	class DLLCOAPI CAnimationGroup : public CComponent
	{
	public:
		typedef std::map<const char*, CAnimation*> MAPANI;
		typedef MAPANI::iterator MAPANI_ITER;

		typedef TIter<MAPANI> ANIM_ITER;

	//Inherit from CComponent
	public:
		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent);


	public:
		CAnimationGroup(CConstruct* pHost);
		CAnimationGroup(const char* pszName, CConstruct* pHost);

		virtual ~CAnimationGroup();

		bool Create();

		void InitializeAnimIterWork();
		bool AddAnimation(CAnimation* pAnim);


	//attribute
	public:
		bool hasCreated() { return m_bCreated; }

		const CAnimation* getCurrentAnim() { return m_pCurrentAnim; }
		void setCurrentAni(CAnimation* pAni) { if (m_pCurrentAnim == 0) m_pCurrentAnim = pAni; }

		ANIM_ITER& iterWorkAni() { return *m_pIterWorkAnim; }



	private:
		void Destroy();


	private:
		MAPANI m_mapAni;
		CAnimation* m_pCurrentAnim;
		FDWORD m_idCurrentAnim;     //for check

		ANIM_ITER* m_pIterWorkAnim;

		bool m_bCreated;
	};


};


#endif // !_FW_ANIMATIONSTACK_
