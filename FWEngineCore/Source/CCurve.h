/*
CCurve

Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_CURVE_
#define	_FW_CURVE_

#include<vector>
#include"CBase.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class DLLCOAPI CCurve : public CBase
	{

	public:
		struct SKey
		{
			enum EINTERP_TYPE { CONSTANT = 0, LINEAR, CUBIC };
			long time;
			float value;
			EINTERP_TYPE typeInterpolation;
		};

		struct SEndPoint
		{
			float fDltX;
			float fDltY;
			float fB;
			float fC;
			float fD;
		};

		typedef std::vector<SKey*> VTKEY;
		typedef VTKEY::iterator ITER_VTKEY;

		typedef std::vector<std::vector<float>> VT2D;
		typedef std::vector<SEndPoint> VTEP;

	public:
		CCurve();
		CCurve(const char* pszName);
		virtual ~CCurve();

		/*
		The paramter typeInterporation : 0 <==> SKey::EINTERP_TYPE::CONSTANT ,  
		                                 1 <==> SKey::EINTERP_TYPE::LINEAR,  
										 2 <==> SKey::EINTERP_TYPE::CUBIC
		*/
		bool Initialize(int size);
		bool Create();
		bool Clone(CCurve* pCurveSrc);
		bool AddKeyValue(int key, float value, long time, int typeInterporation);
		float ComputeCurrentValue(long lDltTime);

	//attribute
	public:
		float length() { return m_fTotalTime; }
		long len() { return m_lTotalTime; }
		float countKeys() { return m_nCountKeys; }
		SKey* key(int ind) { if ((ind < 0) || (ind >= m_nCountKeys)) { return 0; } return m_vtKeyFrame[ind]; }


	private:
		void Reset();
		void Destroy();
		void GaussEliminationFindC();


	private:
		//key value array
		VTKEY m_vtKeyFrame;

		//Just for computing the cubic spline coefficients.
		//rows: n == the count of key frames 
		//columes: n+1
		VT2D m_matCoeff;

		//cubic spline endpoints: n == the count of key frames
		VTEP m_vtCubicSpline;

		//interpolation type
		//EINTERP_TYPE m_eInterpolationType;

		int m_nCountKeys;
		float m_fTotalTime;
		long m_lTotalTime;
		long m_lCountTime;
	};

};

#endif // ! _FW_CURVE_
