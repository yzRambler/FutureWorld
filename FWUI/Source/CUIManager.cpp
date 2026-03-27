#include"CIDManager.h"
#include"CScene.h"
#include"CEssety.h"
#include"CComponent.h"
#include"CUIButton.h"
#include"CUIPanel.h"
#include"CUITextBox.h"
#include"CUICount.h"

//#include"CMsgCenter.h"
#include"CMsgManagerAgent.h"
#include"CIDManagerAgent.h"
#include"CUIMsgListener.h"
#include"CUIManager.h"
#include"CSceneNode.h"
#include"CMaterial.h"

#include"CInterchangeCenter.h"


using namespace FW;

/*
#ifdef _WND_OPENGL_PLATFORM_
extern "C" __declspec(dllexport) IUIManager* CreateUIManager()
#else
extern "C" IUIManager* __cdecl CreateUIManager()
#endif // _WND_OPENGL_PLATFORM_
{
    return &CUIManager::Instance();
}
*/

#ifdef _WND_OPENGL_PLATFORM_
extern "C" DLLUIAPI IUIManager* CreateUIManager()
{
    return &CUIManager::Instance();
}


extern "C" DLLUIAPI void ReleaseUIManager()
{
    CUIManager::Release();
}

#else
extern "C" IUIManager* __cdecl CreateUIManager()
{
    return &CUIManager::Instance();
}

extern "C" void ReleaseUIManager()
{
    CUIManager::Release();
}

#endif





CUIManager* CUIManager::m_pInst = 0;

CUIManager::CUIManager(): m_pCurScene(nullptr), m_fUIStep(0.0f)
{
    m_vtUI.clear();
}

CUIManager::~CUIManager()
{
}


bool CUIManager::Create()
{
    return true;
}


void CUIManager::Destroy()
{
    SUI* pSUI = nullptr;
    for (VTUI_ITER iter = m_vtUI.begin(); iter != m_vtUI.end(); ++iter)
    {
        pSUI = *iter;
        if (pSUI == nullptr)
        {
            continue;
        }

        if (CIDManagerAgent::Instance().idMag().Inquire(pSUI->id))
        {
            delete pSUI->pUI;
            delete pSUI;
        }
        
    }

    m_vtUI.clear();
}




void CUIManager::Update(long lDltTime)
{
    //for (VTUI_ITER iter = m_vtUI.begin(); iter != m_vtUI.end(); ++iter)
    //{
    //	if (!CIDManager::Instance().Inquire((*iter)->id))
    //	{
    //		//m_vtUI.erase(iter);
    //	}
    //	else
    //	{
    //		(*iter)->pUI->Update(lDltTime, 0, 0);
    //	}
    //}

    VTUI vt;
    vt.clear();

    vt.assign(m_vtUI.begin(), m_vtUI.end());
    m_vtUI.clear();

    for (VTUI_ITER iter = vt.begin(); iter != vt.end(); ++iter)
    {
        if (CIDManager::Instance().Inquire((*iter)->id))
        {
            m_vtUI.push_back(*iter);
        }
    }

    for (VTUI_ITER iter = m_vtUI.begin(); iter != m_vtUI.end(); ++iter)
    {
        (*iter)->pUI->Update(lDltTime, 0, 0);
    }

}






bool CUIManager::Initialize(ISceneManager* pISceneMag, CMsgCenter* pMsgCenter, 
    CIDManager* pIDMag)
{
    if ((0 == pISceneMag) || (pISceneMag->GetCurrentScene()->rootNodeUI() != 0)
        ||(0 == pMsgCenter)||(0 == pIDMag))
    {
        return false;
    }

    CMsgManagerAgent::Instance().setMsgCenter(pMsgCenter);
    CIDManagerAgent::Instance().setIDMag(pIDMag);

    
    //UI Coordinate-System with right-hand rule.
    Vector3 posOrg(0.0f, -500.0f, 0.0f);
    Vector3 forwardOrg(0.0f, 1.0f, 0.0f);
    Vector3 upOrg(0.0f, 0.0f, -1.0f);
    Vector3 posCam(0.0f, -10.0f, 0.0f);

    m_pCurScene = pISceneMag->GetCurrentScene();
    
    

    m_fUIStep = 10.0f;

    return true;
}


CUI* CUIManager::CreateUI(EUITYPE type, const char* pszName, const char* pszNameFileMatl,
    const char* pszNameMatl, float ltx, float lty, float w, float h, CConstruct* pHost /*= nullptr*/)
{
    if ((m_pCurScene == nullptr)||(w < 0.0f) || (h < 0.0f))
    {
        return nullptr;
    }


    CSceneNode* pUIRoot = m_pCurScene->rootNodeUI();
    CSceneNode* pParentNode = nullptr;

    if (nullptr == pHost)
    {
        pParentNode = pUIRoot;
    }
    else
    {
        switch (pHost->typeCST())
        {
        case ECONSTRTYPE::CST_SCENENODE:
        {
            pParentNode = (CSceneNode*)pHost;
        }
        break;

        case ECONSTRTYPE::CST_COMPONENT:
        {
            CComponent* pCmp = (CComponent*)pHost;
            if (pCmp->type() != ECOMTYPE::CO_UI)
            {
                return nullptr;
            }
            pParentNode = (CSceneNode*)pCmp->host()->host();
        }
        break;

        default:
            return nullptr;
            break;
        }
    }


    //check host in UI tree by UI id ??

    Vector3 pos = pParentNode->spaceWorld()->pos();
    pos.y += m_fUIStep;

    Vector3 posLc;
    Vector3 forwardLc;
    Vector3 upLc;
    CSceneNode* pUINode = new CSceneNode(pszName);
    pUINode->Create(pUIRoot->orderSpace(), pUIRoot->orderTime(), pUIRoot->spaceTimeID(), pos,
        pUIRoot->spaceWorld()->forward(), pUIRoot->spaceWorld()->up(), posLc, forwardLc, upLc);


    pUINode->setState(EPMTSTATE::READY);


    SRECT scrRect;
    scrRect.x = ltx;
    scrRect.y = lty;
    scrRect.w = w;
    scrRect.h = h;


    CEssety* pUIEsty = nullptr;
    CUI* pUI = nullptr;
    switch (type)
    {
    case EUITYPE::UI_BUTTON:
    {
        pUIEsty = new CEssety("ButtonEty", pUINode);
        pUIEsty->Create();
        pUIEsty->setState(EPMTSTATE::READY);

        CUIButton* pUIBtn = new CUIButton(pszName, pUIEsty);
        if (!pUIBtn->Create(scrRect, pos.y, pszNameFileMatl, pszNameMatl))
        {
            delete pUIBtn;
            delete pUIEsty;
            delete pUINode;

            return nullptr;
        }

        pUI = pUIBtn;

        //update the essety object rect.
        Vector3 posCt = (*pUI->maxWS() + *pUI->minWS()) * 0.5f;

        pUIEsty->bound().CreateWS(*pUI->maxWS(), *pUI->minWS(), pUINode->spaceWorld()->up(),
            pUINode->spaceWorld()->forward(), &posCt);
    }
    break;

    case EUITYPE::UI_PANEL:
    {
        pUIEsty = new CEssety("PanelEty", pUINode);
        pUIEsty->Create();
        pUIEsty->setState(EPMTSTATE::READY);

        CUIPanel* pUIPal = new CUIPanel(pszName, pUIEsty);

        pUI = pUIPal;


        //update the essety object rect.
        Vector3 posCt = (*pUI->maxWS() + *pUI->minWS()) * 0.5f;

        pUIEsty->bound().CreateWS(*pUI->maxWS(), *pUI->minWS(), pUINode->spaceWorld()->up(),
            pUINode->spaceWorld()->forward(), &posCt);


        //for test
        //Vector3 v3Max;
        //Vector3 v3Min;
        //Vector3 v3Pos;

        //pUIEsty->bound().CreateWS(v3Max, v3Min, pUINode->spaceWorld()->up(), pUINode->spaceWorld()->forward(), &v3Pos);

    }
    break;


    case EUITYPE::UI_COUNT:
    {
        pUIEsty = new CEssety("UICountEty", pUINode);
        pUIEsty->Create();
        pUIEsty->setState(EPMTSTATE::READY);

        CUICount* pUICount = new CUICount(pszName, pUIEsty);

        if(!pUICount->Create(scrRect, pos.y, pszNameFileMatl, pszNameMatl))
        {
            delete pUICount;
            delete pUIEsty;
            delete pUINode;
            return nullptr;
        }


        pUI = pUICount;
    }
    break;

    case EUITYPE::UI_TEXTBOX:
    {
        pUIEsty = new CEssety("TextBoxEty", pUINode);
        pUIEsty->Create();
        pUIEsty->setState(EPMTSTATE::READY);

        CUITextBox* pUITxtBox = new CUITextBox(pszName, pUIEsty);
        if (!pUITxtBox->Create(scrRect, pos.y, pszNameFileMatl, pszNameMatl))
        {
            delete pUITxtBox;
            delete pUIEsty;
            delete pUINode;
            return nullptr;
        }


        pUI = pUITxtBox;
    }
    break;

    case EUITYPE::UI_WINDOW:
    {

    }
    break;

    default:
        break;

    }

    //Match this UI object with CMsgCenter. 
    pUI->setIDIntTarget(CMsgCenter::Instance()->typeTag());

    pUIEsty->AddComponent(pUI);
    pUIEsty->SetBound();

    pUINode->AttachConstruct(pUIEsty);
    pUINode->SetParent(pParentNode);

    pParentNode->AttachChild(pUINode);


    //Note: Just register root UI.
    if (nullptr == pHost)
    {
        CInterchangeCenter::Instance()->AddApplication(pUI);
    }


    SUI* pSUI = new SUI;

    pSUI->pUI = pUI;
    pSUI->id = pUI->id();

    m_vtUI.push_back(pSUI);


    return pUI;
}

