#include"CICTarget.h"
#include"CListener.h"


using namespace FW;


bool CICTarget::RegisterLst(CListener* pLsn)
{
	if (nullptr != FindListener(pLsn->GetID()))
	{
		return false;
	}

	m_mapListener[pLsn->GetID()] = pLsn;

	return true;
}


void CICTarget::UnregisterLst(CListener* pLsn)
{
	if (nullptr == pLsn)
	{
		return;
	}

	for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
	{
		if (pLsn->GetID() == iter->first)
		{
			//Note: Just Remove, don't Delete.
			m_mapListener.erase(iter);

			break;
		}
	}
}


CListener* CICTarget::FindListener(FDWORD id)
{
	for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
	{
		if (id == iter->first)
		{
			return iter->second;
		}
	}

	return nullptr;
}