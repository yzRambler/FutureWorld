/*
CTrack


Author: Zhen Yi

Created Date: Mar. 3, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_TRACK_
#define _FW_TRACK_

#include"CConstruct.h"
#include"MathLibrary.h"
#include"FWEngineCoreExport.h"



namespace FW
{
	class CCurve;
	class DLLCOAPI CTrack : public CConstruct
	{
	public:
		enum ETRS { T = 0, R, S, COUNT };

		struct STrack
		{
			enum ECVCOM { X = 0, Y, Z, COUNT };
			CCurve* ary[ECVCOM::COUNT];
		};


	public:
		CTrack();
		CTrack(const char* pszName);
		virtual ~CTrack();

		bool AddCurve(CCurve* pCurve, int TRSCom, int XYZCom);
		bool Clone(CTrack* pTrack);

		void ComputeAnimMatrix(long lDltTime);


	//attribute
	public:

		Matrix4x4& matComputeResult() { return m_matResult; }
		STrack& track() { return *m_aryTRS; }
		STrack* strack(int c) { if ((c < 0) || (c >= ETRS::COUNT))return 0; return &m_aryTRS[c]; }


	private:
		void InitTRSArray();
		void ClearTRSArray();


	private:
		STrack m_aryTRS[ETRS::COUNT];

		Vector3  m_v3TempTranslate;
		Vector3  m_v3TempRotation;
		Vector3  m_v3TempScaling;

		Matrix4x4 m_matTempTranslate;
		Matrix4x4 m_matTempRotation;
		Matrix4x4 m_matTempScaling;
		Matrix4x4 m_matTempWorkA;
		Matrix4x4 m_matTempWorkB;

		Matrix4x4 m_matResult;

		long m_lCountTime;
		long m_lTotalTime;
	};
};


#endif // !_FW_TRACK_
