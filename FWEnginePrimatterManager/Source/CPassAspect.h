/*
CPassAspect


Author:  Zhen Yi

Created Date: Oct. 21, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_PASSASPECT_
#define _FW_PASSASPECT_

#include "CPrimatterAspect.h"
#include "CProgramAspect.h"
#include "CCommandAspect.h"
#include "CMaterial.h"

namespace FW
{
	class CPassAspect : public CPrimatterAspect
	{
	private:
		typedef std::vector<CCommandAspect*> VTCMDAPT;
		typedef VTCMDAPT::iterator VTCMDAPT_ITER;


		//Inherited from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);


	public:
		CPassAspect();
		virtual ~CPassAspect();

		void InitializeAppState(EAPPPRRES appState);
		void AppendComdApt(CCommandAspect* pCmdApt) { if (nullptr != pCmdApt) { m_vtCmdAspet.push_back(pCmdApt); } }


	//attribute
	public:
		CProgramAspect* programApt() { return m_pProgramApt; }  //<<< cancel
		void setProgramApt(CProgramAspect* pProgramApt);

		void setParaHost(CMaterial* pHost) { m_pParaHost = pHost; }
		CMaterial* host() { return m_pParaHost; }

		int countCmdApt() { return m_vtCmdAspet.size(); }
		CCommandAspect* cmdApt(int ind) 
		{ if ((ind < 0) || (ind >= m_vtCmdAspet.size())) { return nullptr; } return m_vtCmdAspet[ind]; }


	private:
		void Destroy();

	private:
		CMaterial* m_pParaHost;
		CProgramAspect* m_pProgramApt;

		VTCMDAPT m_vtCmdAspet;
	};
}


#endif // !_FW_PASSASPECT_
