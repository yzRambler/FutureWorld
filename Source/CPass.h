/*
CPass


Author:   Zhen Yi

Created Date:  Oct. 21, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_PASS_
#define _FW_PASS_

#include <vector>
#include "CPrimatter.h"
#include "CCommand.h"
#include "FWEngineCoreExport.h"


namespace FW
{
	class CMaterial;
	class CProgram;
	class DLLCOAPI CPass : public CPrimatter
	{
	private:
		typedef std::vector<CCommand*> VTCMD;
		typedef VTCMD::iterator VTCMD_ITER;


	public:
		//CPass(CMaterial* pHost);
		CPass(CConstruct* pHost);
		virtual ~CPass();

		void AddCommand(CCommand* pCmd) { m_vtCommand.push_back(pCmd); }
		void Execute();

		//attribute
	public:
		CMaterial* host() { return (CMaterial*)m_pHost; }

		void setProgram(CProgram* pProgram) { m_pProgram = pProgram; }
		CProgram* program() { return m_pProgram; } 

		int countCommand() { return m_vtCommand.size(); }
		CCommand* command(int ind) 
		{
			if ((ind < 0) || (ind >= m_vtCommand.size())) { return 0; }
			return m_vtCommand[ind];
		}

	private:
		void Destroy();


	private:
		VTCMD m_vtCommand;

		CProgram* m_pProgram;
	};

}




#endif // !_FW_PASS_
