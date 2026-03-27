#include"CUIButton.h"
#include"CEssety.h"
#include"CBound.h"
#include"CBox.h"
#include"CRender.h"
#include"CRectImage.h"
#include"CSceneNode.h"
#include"CMessage.h"
#include"CMsgManagerAgent.h"
#include"IDataResource.h"

using namespace FW;



CUIButton::CUIButton(const char* pszName, CConstruct* pHost):
	CUI(pszName, pHost, 
	EUITYPE::UI_BUTTON), m_eStageBt(ESTAGEBT::STGB_NORMAL)
{
}

CUIButton::~CUIButton()
{
}

bool CUIButton::ProcessMsg(CMsgBase& msg)
{
	switch (msg.type)
	{
	case EMSGTYPE::MSG_MMOVE:
	{
		CMsgMSMove& msgMv = (CMsgMSMove&)msg;
		CEssety* pEst = (CEssety*)host();
		if (pEst->bound().InsideRectWS(msgMv.x(), msgMv.y(), msgMv.z()))
		{		

			m_stageUI = ESTAGEUI::STG_FOCUS;

			if (m_eStageBt == ESTAGEBT::STGB_NORMAL)
			{
				m_eStageBt = ESTAGEBT::STGB_HOVE;
				ChangeTexture(1);
			}

			return true;
		}
		else
		{
			m_stageUI = ESTAGEUI::STG_UNFOCUS;

			if (m_eStageBt == ESTAGEBT::STGB_HOVE)
			{
				m_eStageBt = ESTAGEBT::STGB_NORMAL;
				ChangeTexture(0);
			}
		}

	}
	break;

	case EMSGTYPE::MSG_MLBDOWN:
	{
		CMsgLBDown& msgDown = (CMsgLBDown&)msg;
		if (m_stageUI == ESTAGEUI::STG_FOCUS)
		{
			if ((m_eStageBt == ESTAGEBT::STGB_HOVE)||(m_eStageBt == ESTAGEBT::STGB_NORMAL))
			{
				CMsgUI* pmsg = new CMsgUI(EMSGTYPE::MSG_UIBTDOWN, EUITYPE::UI_BUTTON);
		        pmsg->Create(id(), m_idTarget, EUICOMD::UIC_PLAYANI);
		        CMsgManagerAgent::Instance().msgCenter().AddMessage(pmsg);

				m_eStageBt = ESTAGEBT::STGB_PRESSED;
				ChangeTexture(2);
			}
			else if (m_eStageBt == ESTAGEBT::STGB_PRESSED)
			{
				CMsgUI* pmsg = new CMsgUI(EMSGTYPE::MSG_UIBTDOWN, EUITYPE::UI_BUTTON);
				pmsg->Create(id(), m_idTarget, EUICOMD::UIC_STOPANI);
				CMsgManagerAgent::Instance().msgCenter().AddMessage(pmsg);

				m_eStageBt = ESTAGEBT::STGB_HOVE;
				ChangeTexture(1);
			}
		}


	}
	break;


	case EMSGTYPE::MSG_MLBUP:
	{
		//return m_stageUI == ESTAGEUI::STG_HOVER;
	}
	break;


	default:
		break;
	}


	return false;
}




void CUIButton::ChangeTexture(int index)
{
	((CRectImage*)m_pRender->comesh())->ActiveTexture(0, index);
}




bool CUIButton::Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, 
	const char* pszNameMatl)
{
	if (!CUI::Create(block,  fDist2Cam, pszNameFileMatl, pszNameMatl))
	{
		return false;
	}


	//...

	return true;
}

