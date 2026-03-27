/*
CAnimation

Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/


#ifndef _FW_ANIMATION_
#define _FW_ANIMATION_

#include<map>
#include"CPrimatter.h"
#include"CSkeleton.h"
#include"CommonPrimatter.h"


namespace FW
{
	class CAnimationGroup;
	class CAnimation : public CPrimatter
	{
	public:
		enum EMODE { ONCE = 0, LOOP, READY };
		enum ESTATE { PLAY = 0, STOP };


	//Inherit from CPrimatter
	public:
		virtual bool Clone(CPrimatter* pPmt) { return true; }



	public:
		CAnimation(CConstruct* pHost, EANITYPE typeAni = EANITYPE::AN_UNKNOWN):CPrimatter(pHost, EPMTTYPE::ANIMATION), 
			m_typeAni(typeAni), m_eStatePlay(ESTATE::STOP), m_ePlayMode(EMODE::READY), m_lTotalTime(0), m_nSpeed(0){}

		CAnimation(const char* pszName, CConstruct* pHost, EANITYPE typeAni = EANITYPE::AN_UNKNOWN): 
			CPrimatter(pszName, pHost, EPMTTYPE::ANIMATION), m_typeAni(typeAni) ,m_eStatePlay(ESTATE::STOP), 
			m_ePlayMode(EMODE::READY), m_lTotalTime(0), m_nSpeed(0) {};

		virtual ~CAnimation() {}

		
		void PlayOnce() { m_eStatePlay = ESTATE::PLAY; m_ePlayMode = EMODE::ONCE; }
		void PlayLoop() { m_eStatePlay = ESTATE::PLAY; m_ePlayMode = EMODE::LOOP; }
		void Stop() { m_eStatePlay = ESTATE::STOP; }


		virtual bool Clone(CAnimation* pAniSrc, CSkeleton* pSkeleton) { return true; }
		virtual void Update(long lDltTime) {}



	//attribute
	public:
		CAnimationGroup* host() { return (CAnimationGroup*)m_pHost; }

		EANITYPE typeAni() { return m_typeAni; }
		EMODE mode() { return m_ePlayMode; }
		ESTATE statePlay() { return m_eStatePlay; }
		long totalTime() { return m_lTotalTime; }
		int speed() { return m_nSpeed; }

	protected:
		EANITYPE m_typeAni;
		EMODE m_ePlayMode;
		ESTATE m_eStatePlay;

		long m_lTotalTime;
		int m_nSpeed;
	};


}


#endif // !_FW_ANIMATION_
