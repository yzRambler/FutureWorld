/*

CEssetyDataApply


Author:  Zhen Yi
Created Date: Feb. 07, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_ESSETYDATAAPPLY_
#define _FW_ESSETYDATAAPPLY_

#include<vector>

namespace FW
{
	class CPrimatterCenter;
	class CEssetyAspect;
	class CFileDataApply;
	class CEssetyDataApply
	{
	public:
		typedef std::vector<CFileDataApply*> VTFDA;
		typedef VTFDA::iterator VTFDA_ITER;

	public:
		CEssetyDataApply();
		virtual ~CEssetyDataApply();

		void Create(CEssetyAspect* pEApt);
		void Check(CPrimatterCenter* pPmtCenter);

		//all local file parse successfully.
		//have data file to apply in CEssetyAspect queue
		bool IsAllLocalDataReady();

		//need not data file in CEssetyAspect queue
		bool IsNoneLocalData() { return m_vtFileDAProcessing.empty() && m_vtFileDAFinished.empty(); }

		//attribute
	public:
		CEssetyAspect& essetyAspect() { return *m_pEssetyApt; }

	private:
		CEssetyAspect* m_pEssetyApt;
		VTFDA m_vtFileDAProcessing;
		VTFDA m_vtFileDAFinished;
	};

};


#endif // !_FW_ESSETYDATAAPPLY_
