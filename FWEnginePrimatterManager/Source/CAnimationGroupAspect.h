/*
CAnimationGroupAspect

    One CAnimationGroupAspect match one animation file (.fbx file). 
	One animation file have some animations.

Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/


#ifndef _FW_ANIMATIONSTACK_ASPECT_
#define _FW_ANIMATIONSTACK_ASPECT_

//#include<list>
#include<vector>
#include "CComponentAspect.h"
#include "CString.h"

namespace FW
{
	class CAnimationAspect;
	class CAnimationGroupAspect : public CComponentAspect
	{
	private:
		typedef std::vector<CAnimationAspect*> VTANI;
		typedef VTANI::iterator VTANI_ITER;


		//Inherit from CAspect
	public:
		virtual EAPTSTATE CheckState(CAspectCenter* pPmtAtpCent, CEssetyAspect* pEsetyApt);
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);



		//Inherit from CComponentAspect
	public:
		virtual CComponentAspect* CreateCoInstance(CEssetyAspect* pComHost);
		



	public:
		CAnimationGroupAspect(CAspect* pHost);
		CAnimationGroupAspect(const char* pszName, CAspect* pHost);
		virtual ~CAnimationGroupAspect();

		bool Initialize(const char* pszName, const char* pszNamePathAndFile, 
			CAnimationAspect* pCurrentAniApt);

		void AddAnimationAspect(CAnimationAspect* pAniApt);

		void CloneFileName(const char* pszNameFile);
		





	//attribute
	public:
		//derive from the CAspect
		virtual bool isReady();

		CAnimationAspect* aniAspect(int index)
		{
			return index < 0 ? 0 : (index >= m_vtAnimationApt.size() ? 0 : m_vtAnimationApt[index]);
		}

		int size() { return m_vtAnimationApt.size(); }

		void setNameFile(const char* pszNameFile) { m_strNamePathAndFile.Set(pszNameFile);}
		const char* namePathFile() { return m_strNamePathAndFile.Get(); }


		CAnimationAspect* currentAniAspect() { return m_pCurrentAniApt; }

		bool setCurrentAniAspect(const char* pszNameAni)
		{
			CAnimationAspect* pAniApt = Search(pszNameAni, m_strNamePathAndFile.Get());
			if (0 == pAniApt)
			{
				return false;
			}

			m_pCurrentAniApt = pAniApt;

			return true;
		}

	private:
		CAnimationAspect* Search(const char* pszNameAni, const char* pszNamePathFile);
		void Destroy();

	private:
		VTANI  m_vtAnimationApt;
		CAnimationAspect* m_pCurrentAniApt;

		const char* m_pszNamePathAndFile;
		CString m_strNamePathAndFile;
	};
	
};


#endif // !_FW_ANIMATIONSTACK_
