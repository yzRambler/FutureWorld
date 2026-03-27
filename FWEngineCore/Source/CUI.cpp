#include"CUI.h"
#include"CBox.h"
#include"CBound.h"
#include"CRectImage.h"
#include"CUIMsgListener.h"
#include"CEssety.h"
#include"CSceneNode.h"
#include"ISceneManager.h"
#include"CScene.h"
#include"CIDManager.h"
#include"CInterchangeCenter.h"

using namespace FW;

CUI::CUI(const char* pszName, CConstruct* pHost, EUITYPE typeUI /*= EUITYPE::UI_UNKNOW*/):
	CComponent(pszName, pHost, ECOMTYPE::CO_UI), m_stageUI(ESTAGEUI::STG_UNFOCUS), m_typeUI(typeUI),
	m_pUIMsgLst(nullptr), STEP(0.1f), m_nLevel(0), m_fDepth(m_nLevel * STEP), m_pRender(nullptr)
{
}


CUI::~CUI()
{
	Destroy();
}


void CUI::Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent)
{
	if (nullptr != m_pRender)
	{
		((CRectImage*)m_pRender->comesh())->Update(pEty);

		((CEssety*)host())->bound().UpdateWS(*maxWS(), *minWS());
	}
}



bool CUI::Create(SRECT& block, float fDis2Cam,	const char* pszNameFileMatl, const char* pszNameMatl)
{
	//generate id
	FDWORD idUI = CIDManager::Instance().ApplyID();
	if (idUI == 0)
	{
		return false;
	}

	setID(idUI);

	m_pUIMsgLst = new CUIMsgListener(this);

	//Transform coordinate from screen space into world space.
	Vector4* aryVt[4];


	aryVt[0] = new Vector4(block.x, block.y, 0.0f, 1.0f);
	aryVt[1] = new Vector4(block.x, block.y + block.h, 0.0f, 1.0f);
	aryVt[2] = new Vector4(block.x + block.w, block.y + block.h, 0.0f, 1.0f);
	aryVt[3] = new Vector4(block.x + block.w, block.y, 0.0f, 1.0f);


	Matrix4x4& matS2W = CreateSceneManager()->GetCurrentScene()->matSToWByUICam();

	for (int i = 0; i < 4; i++)
	{
		*aryVt[i] = Mul4(*aryVt[i], matS2W);
		(*aryVt[i]).y = fDis2Cam;
	}


	//create CRectImage object
	const int SIZE = 64;
	char nameRnd[SIZE];
	memset(nameRnd, 0, SIZE);
	sprintf_s(nameRnd, SIZE, "%sRender", name());
	m_pRender = new CRender(nameRnd, this);

	Vector3& vHor = aryVt[1]->v3;
	vHor = vHor - aryVt[0]->v3;

	Vector3& vVer = aryVt[3]->v3;
	vVer = vVer - aryVt[0]->v3;

	CRectImage* pRectImg = new CRectImage(m_pRender);
	if (!pRectImg->Create(aryVt[0]->v3, vHor, vVer, pszNameFileMatl, pszNameMatl))
	{
		delete m_pRender;
		delete pRectImg;
		return false;
	}


	FDWORD idRnd = CIDManager::Instance().ApplyID();
	if (0 == idRnd)
	{
		delete m_pRender;
		delete pRectImg;
		return false;
	}

	m_pRender->setID(idRnd);
	m_pRender->setComesh(pRectImg);



	((CEssety*)host())->AddSubRender(m_pRender);

	for (int i = 0; i < 4; i++)
	{
		delete aryVt[i];
	}


	return true;
}




bool CUI::ProcessMsg(CMsgBase& msg)
{
	switch (msg.type)
	{
	//MSG_MMOVE is the local broadcast message just for all sub UI objects of hitting UI.
	case EMSGTYPE::MSG_MMOVE:
	{
		CMsgMSMove& msgMv = (CMsgMSMove&)msg;
		CEssety* pEst = (CEssety*)host();
		CEssety* pSubEst = nullptr;

		if (pEst->bound().InsideRectWS(msgMv.x(), msgMv.y(), msgMv.z()))
		{

			//Search all sub CUI object being.
			CSceneNode* pNode = (CSceneNode*)pEst->host();
			CSceneNode* pSubNode = nullptr;
			bool bProced = false;
			for (int i = 0; i < pNode->countSubNodes(); i++)
			{
				pSubNode = (CSceneNode*)pNode->subNode(i);
				if ((pSubNode->construct() != nullptr)
					&& (pSubNode->construct()->typeCST() == ECONSTRTYPE::CST_ESSETY))
				{
					//Check whether this CEssety attached a CUI object
					pSubEst = (CEssety*)pSubNode->construct();
					CUI* pSubUI = (CUI*)pSubEst->GetComponent(ECOMTYPE::CO_UI);
					if (nullptr != pSubUI)
					{
						bProced |= pSubUI->ProcessMsg(msg);
					}
				}

			}

			//m_stageUI = bProced ? ESTAGEUI::STG_NORMAL : ESTAGEUI::STG_HOVER;
			m_stageUI = bProced ? ESTAGEUI::STG_UNFOCUS : ESTAGEUI::STG_FOCUS;

			return true;
		}
		else
		{
			//m_stageUI = ESTAGEUI::STG_NORMAL;
			m_stageUI = ESTAGEUI::STG_UNFOCUS;
		}
	}
	break;



	//MSG_MTIME/MSG_MLBDOWN/MSG_MLBUP is the global broadcast message begining from CMsgCenter.
	case EMSGTYPE::MSG_TIME:
	{
	}
	break;

	case EMSGTYPE::MSG_MLBUP:
	case EMSGTYPE::MSG_MLBDOWN:
	{
		//Broadcast all sub ui objects.
		CSceneNode* pNode = (CSceneNode*)host()->host();
		CSceneNode* pSubNode = nullptr;
		CEssety* pSubEst = nullptr;
		CUI* pSubUI = nullptr;
		bool bProced = false;
		for (int i = 0; i < pNode->countSubNodes(); i++)
		{
			pSubNode = (CSceneNode*)pNode->subNode(i);
			if ((pSubNode->construct() != nullptr)
				&& (pSubNode->construct()->typeCST() == ECONSTRTYPE::CST_ESSETY))
			{
				pSubEst = (CEssety*)pSubNode->construct();
				pSubUI = (CUI*)pSubEst->GetComponent(ECOMTYPE::CO_UI);
				if (nullptr != pSubUI)
				{
					bProced |= pSubUI->ProcessMsg(msg);
				}
			}
		}

		//
		CEssety* pEst = (CEssety*)host();
		//if ((bProced)||(m_stageUI == ESTAGEUI::STG_HOVER))
		if ((bProced) || (m_stageUI == ESTAGEUI::STG_FOCUS))
		{
			return true;
		}

	}
	break;


	default:
		break;
	}

	return false;
}




void CUI::Destroy()
{
	CIDManager::Instance().RemoveID(id());
	
	if (m_pUIMsgLst != nullptr)
	{
		CInterchangeCenter::Instance()->RemoveApplication(this);
		delete m_pUIMsgLst;
		m_pUIMsgLst = nullptr;
	}


	if (nullptr != m_pRender)
	{
		delete m_pRender;
		m_pRender = nullptr;
	}
}

