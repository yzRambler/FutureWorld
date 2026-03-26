/*
CAnimationAspect


Author: Zhen Yi

Created Date: Feb. 02, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_ANIMATION_ASPECT_
#define _FW_ANIMATION_ASPECT_

#include"FWEnginePrimatterManagerExport.h"
#include "CPrimatterAspect.h"



namespace FW
{
	class CAnimationAspect : public CPrimatterAspect
	{
	public:
		CAnimationAspect(EANITYPE typeAni = EANITYPE::AN_UNKNOWN):CPrimatterAspect(EPMTTYPE::ANIMATION),m_typeAni(typeAni){}

		CAnimationAspect(const char* pszName, EANITYPE typeAni = EANITYPE::AN_UNKNOWN):
			CPrimatterAspect(pszName, EPMTTYPE::ANIMATION), m_typeAni(typeAni) {}

		virtual ~CAnimationAspect() {}

		//Inherited from CAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile)
		{
			return CPrimatterAspect::Initialize(pszName, pszNamePathAndFile);
		}


		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */) 
		{ return true; }

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent)
		{
			return EPMTSTATE::UNKNOWN;
		}

		virtual bool Clone(CAspect* pAptSrc)
		{
			if (!CPrimatterAspect::Clone(pAptSrc))
			{
				return false;
			}

			m_typeAni = ((CAnimationAspect*)pAptSrc)->m_typeAni;

			return true;
		}


		virtual bool Copy(CAspect* pAptSrc)
		{
			if (!CPrimatterAspect::Copy(pAptSrc))
			{
				return false;
			}


			CAnimationAspect* pAniApt = (CAnimationAspect*)pAptSrc;
			m_typeAni = pAniApt->m_typeAni;


			return true;
		}



	//attribute
	public:
		EANITYPE typeAni() { return m_typeAni; }

	private:
		EANITYPE m_typeAni;

	};
}



#endif // !_FW_ANIMATION_ASPECT_
