#include"CPrimatterAspectSet.h"
#include"CPrimatterAspect.h"


using namespace FW;





CPrimatterAspectSet::CPrimatterAspectSet()
{
	m_mapIDASS.clear();
}


CPrimatterAspectSet::~CPrimatterAspectSet()
{

}

void CPrimatterAspectSet::Create()
{
}


void CPrimatterAspectSet::AddData(FDWORD id, CData* pPmt)
{
	if (!ID_VALID(id) || (pPmt == 0))
	{
		return;
	}

	//MAPIDAS_ITER iter = m_mapIDASS.find(id);
	if (m_mapIDASS.find(id) != m_mapIDASS.end())
	{
		return;
	}

	SDataSign* pSS = new SDataSign();
	pSS->pPmt = pPmt;
	pSS->count = 1;

	m_mapIDASS[id] = pSS;
}

//CData* CDataSet::GetData(FDWORD id)
CData* CPrimatterAspectSet::GetUnpossess(FDWORD id)
{
	if (!ID_VALID(id))
	{
		return 0;
	}


	return m_mapIDASS[id]->pPmt;

}


CData* CPrimatterAspectSet::AcquireReference(FDWORD id)
{
	if (!ID_VALID(id))
	{
		return 0;
	}

	MAPIDAS_ITER iter = m_mapIDASS.find(id);
	if (iter != m_mapIDASS.end())
	{
		iter->second->count++;
		return iter->second->pPmt;
	}

	return 0;
}

//int CDataSet::ReleaseData(FWORD id)
int CPrimatterAspectSet::ReleaseReference(FWORD id)
{
	if (!ID_VALID(id))
	{
		return -1;
	}

	MAPIDAS_ITER iter = m_mapIDASS.find(id);
	if (iter != m_mapIDASS.end())
	{
		int count = iter->second->count;

		iter->second->count = (count <= 0) ? 0 : count - 1;
		if (iter->second->count == 0)
		{
			delete iter->second->pPmt;
			iter->second->pPmt = 0;

			m_mapIDASS.erase(iter);

			return 0;
		}

	}

	return iter->second->count;
}


FDWORD CPrimatterAspectSet::Check(const char* pszFileName, const char* pszName)
{
	CData* pAt = 0;
	for (MAPIDAS_ITER iter = m_mapIDASS.begin(); iter != m_mapIDASS.end(); ++iter)
	{
		pAt = iter->second->pPmt;
		if ((strcmp(pAt->nameData(), pszName) == 0) && (strcmp(pAt->namePathFile(), pszFileName) == 0))
		{
			//return pAt->id();
			return ((CPrimatterAspect*)pAt)->id();
		}

	}

	//have none.
	return 0;
}




FDWORD CPrimatterAspectSet::RequireData(char* pszFileName, char* pszName)
{
	//SDataSign* pAS = 0;
	CData* pAt = 0;
	for (MAPIDAS_ITER iter = m_mapIDASS.begin(); iter != m_mapIDASS.end(); ++iter)
	{
		pAt = iter->second->pPmt;
		if ((strcmp(pAt->nameData(), pszName) == 0) && (strcmp(pAt->namePathFile(), pszFileName) == 0))
		{
			iter->second->count++;

			//return pAt->id();
			return ((CPrimatterAspect*)pAt)->id();
		}

	}

	//have none
	return 0;
}


