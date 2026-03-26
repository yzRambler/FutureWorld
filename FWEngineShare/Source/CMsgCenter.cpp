#include"CMsgCenter.h"
#include"CIDManager.h"
#include"CListener.h"
#include"CEssety.h"
#include"CBound.h"


using namespace FW;

CMsgCenter* CMsgCenter::m_pInst = nullptr;


CMsgCenter::CMsgCenter(): CICTarget(EICTAGTYPE::ICT_MSGCENTER)
{
	m_lsMsg.clear();
}


CMsgCenter::~CMsgCenter()
{
	Clean();
}


bool CMsgCenter::RegisterLst(CListener* pLsn)
{

	return CICTarget::RegisterLst(pLsn);
	//return true;
}



void CMsgCenter::UnregisterLst(CListener* pLsn)
{
	CICTarget::UnregisterLst(pLsn);
}



bool CMsgCenter::Create()
{
	m_idInt = CIDManager::Instance().ApplyID();

	return true;
}


void CMsgCenter::Update()
{
	if (m_lsMsg.empty())
	{
		return;
	}


	CEssety* pEst = nullptr;

	//process the first message
	while (!m_lsMsg.empty())
	{
		CMsgBase* pMsg = m_lsMsg.front();


		switch (pMsg->type)
		{
		case EMSGTYPE::MSG_TIME:
		{
			//The listener is CRoot object.
			//if (m_mapLst[0]->GetID() == 0)
			//{
			//	m_mapLst[0]->OnMsg(pMsg);
			//}

			//if (m_mapListener[0]->GetID() == 0)
			//{
			//	m_mapListener[0]->OnCallback(pMsg);
			//}

			for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
			{
				if ((iter->first == 0) && (iter->second->GetID() == 0))
				{
					iter->second->OnCallback(pMsg);
				}
				else if (iter->second->host()->typeCST() == ECONSTRTYPE::CST_ESSETY)
				{
					((CEssety*)iter->second->host())->ProcessMsg(*pMsg);
				}
			}

		}
		break;

		case EMSGTYPE::MSG_MMOVE:
		{

			CMsgMSMove& msgMv = *(CMsgMSMove*)pMsg;

			//for test
			//msgMv.setX()


			for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
			{
				//It's a broadcast message.
				if ((nullptr != iter->second) && (pMsg->idTarget == 0))
				{
					iter->second->OnCallback(pMsg);
				}
			}
		}
		break;

		case EMSGTYPE::MSG_MLBDOWN:
		case EMSGTYPE::MSG_MLBUP:
		case EMSGTYPE::MSG_MRBDOWN:
		case EMSGTYPE::MSG_MRBUP:
		case EMSGTYPE::MSG_KBDOWN:
		case EMSGTYPE::MSG_KBUP:
		{

			for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
			{
				//It's broadcast message.
				if ((nullptr != iter->second) && (pMsg->idTarget == 0))
				{
					iter->second->OnCallback(pMsg);
				}
			}

		}
		break;

		case EMSGTYPE::MSG_UIBTDOWN:
		case EMSGTYPE::MSG_UIBTUP:
		{

			MAPLST_ITER iter = m_mapListener.find(pMsg->idTarget);
			if (iter != m_mapListener.end())
			{
				iter->second->OnCallback(pMsg);
			}

		}
		break;


		default:
			break;
		}

		if (nullptr != pMsg)
		{
			delete pMsg;
		}


		m_lsMsg.pop_front();
	}
	
}






void CMsgCenter::Clean()
{
	for (LTMSG_ITER iter = m_lsMsg.begin(); iter != m_lsMsg.end(); ++iter)
	{
		if (nullptr != *iter)
		{
			delete *iter;
		}
	}

	m_lsMsg.clear();



	for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			//...
		}
	}

	m_mapListener.clear();

}


