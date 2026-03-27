/*
CBone

Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_BONE
#define _FW_BONE


#include<map>

#include"CConstruct.h"
#include"CNode.h"
//#include"CSpace.h"
//#include"CCluster.h"
#include"CTrack.h"
#include"MathLibrary.h"




namespace FW
{
	class CCurve;
	class CSpace;
	class DLLCOAPI CBone : public CNode, public CConstruct
	{
	public:
		CBone();
		CBone(const char* pszName);
		virtual ~CBone();


		bool Clone(CBone* pBoneSrc);
		void Update(long lDltTime);


	//attribute
	public:
		CTrack* track() { return m_pTrack; }
		CTrack& trackUnNull() { if (0 == m_pTrack) m_pTrack = new CTrack; return *m_pTrack; }

		Matrix4x4& matAniBaseLocalMatrix() { return m_matAniBaseLocal; }
		void setAniBaseLocalMatrix(Matrix4x4& mat) { m_matAniBaseLocal = mat; }


		void setSign(int sign) { m_nSign = sign; }
		int  getSign() { return m_nSign; }


		AMatrix4x4& matOutput() { return m_matOutput; }



	private:
		CSpace* m_pSpace;
		CTrack* m_pTrack;

		//m_matAniBase is used for the basic transform of the animation, specailly in
        //the case: m_pTrack == null.
		Matrix4x4 m_matAniBaseLocal;

		AMatrix4x4 m_matOutput;

		int m_nSign;   //The id match CSkeleton::EBONE

		bool m_bActive;
	};


};


#endif // ! _FW_BONE

