#include "CPass.h"
#include "CProgram.h"
#include "CMaterial.h"


using namespace FW;




CPass::CPass(CConstruct* pHost) : CPrimatter(pHost), m_pProgram(0)
{
}

CPass::~CPass()
{
	Destroy();
}



void CPass::Execute()
{
	for (VTCMD_ITER iter = m_vtCommand.begin(); iter != m_vtCommand.end(); ++iter)
	{
		if ((*iter) != 0)
		{
			(*iter)->Execute();
		}
	}
}



void CPass::Destroy()
{

	if (nullptr != m_pProgram)
	{
		delete m_pProgram;
		m_pProgram = nullptr;
	}


	for (VTCMD_ITER iter = m_vtCommand.begin(); iter != m_vtCommand.end(); ++iter)
	{
		if ((*iter) != 0)
		{
			delete *iter;
		}
	}

	m_vtCommand.clear();
}
