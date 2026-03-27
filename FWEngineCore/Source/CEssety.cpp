#include"CEssetyMsgListener.h"
#include"CEssety.h"
#include"CAnimation.h"
#include"CAnimationGroup.h"
#include"CSceneNode.h"
#include"CTime.h"
#include"CRender.h"
#include"CUI.h"
#include"CBound.h"
#include"CIDManager.h"
#include"CInterchangeCenter.h"


using namespace FW;




CEssety::CEssety(CConstruct* pHost) :CConstruct(pHost, ECONSTRTYPE::CST_ESSETY), 
m_pListener(0), m_bInit(false), m_pBound(nullptr)
{
	m_vtComponent.clear();
	m_vtSubRender.clear();
}

CEssety::CEssety(const char* pszName, CConstruct* pHost) : CConstruct(pszName, pHost,
	ECONSTRTYPE::CST_ESSETY), m_pListener(0), m_bInit(false), m_pBound(nullptr)
{
	m_vtComponent.clear();
	m_vtSubRender.clear();
}

CEssety::~CEssety()
{
	Destory();

}




bool CEssety::Create()
{
	if ((nullptr != m_pListener)||(nullptr != m_pBound))
	{
		return false;
	}

	FDWORD id = CIDManager::Instance().ApplyID();
	if (id == 0)
	{
		return false;
	}

	setID(id);

	m_pListener = new CEssetyMsgListener(this);


	const int SIZE = 64;
	char nameBound[SIZE];
	memset(nameBound, 0, SIZE);

	sprintf_s(nameBound, SIZE, "%sBound", name());
	m_pBound = new CBound(nameBound, this);

	Vector3 v3Max = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 v3Min = Vector3(-1.0f, -1.0f, -1.0f);

	m_pBound->Create(v3Max, v3Min, ((CSceneNode*)host())->spaceWorld()->pos());

	return true;
}


void CEssety::SetBound()
{
	if (nullptr == m_pBound)
	{
		return;
	}

	
	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
	{
		if ((*iter)->type() == ECOMTYPE::CO_RENDER)
		{
			CRender* pRnd = (CRender*)(*iter);
			CSceneNode* pSNd = (CSceneNode*)host();
			m_pBound->Update(pRnd->comesh()->max(), pRnd->comesh()->min(), pSNd->spaceWorld()->up(),
				pSNd->spaceWorld()->forward(), &pSNd->spaceWorld()->pos());

			break;
		}
		else if ((*iter)->type() == ECOMTYPE::CO_UI)
		{
			CUI* pUI = (CUI*)(*iter);
			CSceneNode* pSNd = (CSceneNode*)host();

			for (VTREN_ITER iterRd = m_vtSubRender.begin(); iterRd != m_vtSubRender.end(); ++iterRd)
			{
				if ((*iterRd)->id() == pUI->idRndHost())
				{
					CRender* pRnd = (*iterRd);
					m_pBound->Update(pRnd->comesh()->max(), pRnd->comesh()->min(), pSNd->spaceWorld()->up(),
						pSNd->spaceWorld()->forward(), &pSNd->spaceWorld()->pos());

					break;
				}
			}

			break;
		}
	}

}



void CEssety::AddSubRender(CRender* pRnd)
{
	if (nullptr != pRnd)
	{
		m_vtSubRender.push_back(pRnd);
	}
}


void CEssety::AddComponent(CComponent* pCom)
{
	if (nullptr != pCom)
	{
		m_vtComponent.push_back(pCom);
	}
}

CComponent* CEssety::SearchComponent(ECOMTYPE type, const char* pszName)
{
	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
	{
		if (((*iter)->type() == type) && (strcmp(pszName, (*iter)->name()) == 0))
		{
			return (*iter);
		}
	}

	return 0;
}



void CEssety::PlayCurrentAni()
{
	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
	{
		if ((*iter)->type() == ECOMTYPE::CO_ANIMATIONGROUP)
		{
			CAnimationGroup* pAniGp = (CAnimationGroup*)(*iter);
			CAnimation* pCurAni = (CAnimation*)pAniGp->getCurrentAnim();
			pCurAni->PlayLoop();

			break;
		}
	}
}


bool CEssety::ProcessMsg(CMsgBase& msg)
{

	switch (msg.type)
	{
	case EMSGTYPE::MSG_UIBTDOWN:
	{
		CMsgUI& msgUI = (CMsgUI&)msg;
		if (nullptr != m_pHost)
		{
			if (msgUI.command == EUICOMD::UIC_PLAYANI)
			{
				PlayCurrentAni();
			}
			else if (msgUI.command == EUICOMD::UIC_STOPANI)
			{
				StopCurrentAni();
			}
		}
	}
	break;

	case EMSGTYPE::MSG_UIBTUP:
	{
	}
	break;


	default:
		break;
	}

	return true;
}


void CEssety::StopCurrentAni()
{
	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
	{
		if ((*iter)->type() == ECOMTYPE::CO_ANIMATIONGROUP)
		{
			CAnimationGroup* pAniGp = (CAnimationGroup*)(*iter);
			CAnimation* pCurAni = (CAnimation*)pAniGp->getCurrentAnim();
			pCurAni->Stop();

			break;
		}
	}
}



//bool init = false;
void CEssety::Update(float ratio, long lDltTime, IPrimatterManager* pPmtCent, 
	IRenderManager* pRenderMag)
{
	if (0 == pRenderMag)
	{
		return;
	}


	if ((strcmp(name(), "Horse") == 0) || (strcmp(name(), "DavidHead") == 0))
	{
		if(!m_bInit)
		{
			((CSceneNode*)host())->spaceWorld()->frame().Yaw(90);
			((CSceneNode*)host())->spaceWorld()->frame().Roll(90);

			m_bInit = true;
		}
	}

	Matrix4x4 matR = ((CSceneNode*)host())->spaceWorld()->frame().matRotation();

	Matrix4x4 matT;
	matT.Identity();

	((CSceneNode*)host())->spaceWorld()->matOutput() = matR * matT;

	CComponent* pCom = 0;
	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
	{
		pCom = *iter;
		if (nullptr != pCom)
		{

			pCom->Update(lDltTime, this, pPmtCent);
			if ((pCom->type() == ECOMTYPE::CO_RENDER) && (pCom->active()))
			{
				if (nullptr != pRenderMag)
				{
					pRenderMag->AddRender(((CSceneNode*)pCom->host()->host())->spaceTimeID(),
							(CRender*)pCom);
				}
				
			}

		}

	}


	if (nullptr != pRenderMag)
	{
		CRender* pRnd = nullptr;
		for (VTREN_ITER iter = m_vtSubRender.begin(); iter != m_vtSubRender.end(); ++iter)
		{
			pRnd = *iter;
			if ((nullptr != pRnd)&&(pRnd->active()))
			{
				pRenderMag->AddRender(((CSceneNode*)pCom->host()->host())->spaceTimeID(), pRnd);
			}
		}
	}

	

}


inline CEssetyMsgListener* CEssety::listener()
{
	return m_pListener;
}



void CEssety::Destory()
{
	if (m_pListener != nullptr)
	{
		CMsgCenter::Instance()->UnregisterLst(m_pListener);

		delete m_pListener;
		m_pListener = nullptr;
	}


	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;
		}
	}


	if (nullptr != m_pBound)
	{
		delete m_pBound;
		m_pBound = nullptr;
	}


	m_vtComponent.clear();

	//Just clear, DONOT delete it!
	m_vtSubRender.clear();
}