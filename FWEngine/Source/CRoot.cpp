

#include<string>
#include"CRoot.h"
#include"CScene.h"
#include"CTime.h"
#include"CMsgCenter.h"
#include"CIDManager.h"
#include"CEssety.h"
#include"CSceneNode.h"
#include"CMaterialAspect.h"
#include"CMaterial.h"
#include"CUIPanel.h"
#include"CUIButton.h"

#ifndef  _WND_OPENGL_PLATFORM_
#include<emscripten/emscripten.h>
#include "CBrowserDevice.h"
#else

#include "CWindowsDevice.h"

#endif



#define _PRE_LOADMATERIAL_


using namespace FW;



CRoot::CRoot() : CListener(nullptr), m_pIDataRes(0),  m_pISceneDispatcher(0), m_pIRenderMag(0),
m_pIInputDevice(0), m_pUIMag(0), m_eStage(ESTAGE::RT_UNKNOWN)
{
}

CRoot::~CRoot()
{
	DestroyAll();
}


void* CRoot::WindowHandle()
{
#ifdef _WND_OPENGL_PLATFORM_
	return ((CWindowsDevice*)m_pDevice)->getWndHandle();
#else
	return 0;
#endif // _WND_OPENGL_PLATFORM_

}



bool CRoot::Initalize(int widthWnd, int heightWnd)
{

	setID(CIDManager::Instance().ApplyID());


	m_pIInputDevice = CreateInputDevice(CMsgCenter::Instance());
	if (0 == m_pIInputDevice)
	{
		return false;
	}


#ifndef  _WND_OPENGL_PLATFORM_
	m_pDevice = new CBrowserDevice();
#else
	m_pDevice = new CWindowsDevice();
#endif // ! _WND_OPENGL_PLATEFORM_

	if (!m_pDevice->Create(widthWnd, heightWnd, m_pIInputDevice))
	{
		m_pDevice->Destroy();
		delete m_pDevice;

		return false;
	}


	m_pIDataRes = CreateDataResource();
	if (!m_pIDataRes->Initialize(widthWnd, heightWnd, CIDManager::Instance(), *CMsgCenter::Instance()))
	{
		return false;
	}



	m_pISceneDispatcher = CreateSceneManager();
	if (!m_pISceneDispatcher->Initalize(&CIDManager::Instance()))
	{
		return false;
	}


	m_pIRenderMag = CreateRenderManager();
	if (!m_pIRenderMag->Initialize(widthWnd, heightWnd))
	{
		return false;
	}


	m_pUIMag = CreateUIManager();

	m_eStage = ESTAGE::RT_START;

	setIDIntTarget(EICTAGTYPE::ICT_MSGCENTER);

	return true;
}





CMaterialAspect* pPRMatlApt = 0;
CMaterial* pPRMatl = 0;
CUI* pUICountTest = 0;
bool CRoot::Circle()
{
	if ((nullptr == m_pDevice) || (nullptr == m_pIDataRes) || (nullptr == m_pISceneDispatcher)
		|| (nullptr == m_pIRenderMag) || (nullptr == m_pIInputDevice))
	{
		return false;
	}


	if (!m_pDevice->Update())
	{
		return false;
	}



	m_pIDataRes->Run();


	switch (m_eStage)
	{
	case ESTAGE::RT_START:
	{

#ifdef _PRE_LOADMATERIAL_


		CMaterialAspect* pMatApt = (CMaterialAspect*)m_pIDataRes->ApplyAspect("DefaultFrame",
			"./resources/DefaultFrame.mat", EAPTTYPE::CST_PRM_MAT);
		if (pMatApt == nullptr)
		{
			return false;
		}
		pMatApt->lock();
		m_vtMatApt.push_back(pMatApt);


		pMatApt = (CMaterialAspect*)m_pIDataRes->ApplyAspect("DefaultColor",
			"./resources/DefaultColor.mat", EAPTTYPE::CST_PRM_MAT);
		if (pMatApt == nullptr)
		{
			return false;
		}
		pMatApt->lock();
		m_vtMatApt.push_back(pMatApt);



		pMatApt = (CMaterialAspect*)m_pIDataRes->ApplyAspect("FontLibMatl",
			"./resources/FontLibrary.mat", EAPTTYPE::CST_PRM_MAT);
		if (pMatApt == nullptr)
		{
			return false;
		}
		pMatApt->lock();
		m_vtMatApt.push_back(pMatApt);




		for (int i = 0; i < m_vtMatApt.size(); i++)
		{
			m_vtMatl.push_back(nullptr);
		}


#endif // _PRE_LOADMATERIAL_

		m_eStage = ESTAGE::RT_DEFAULT_ASPECT;
	}
	break;

	case ESTAGE::RT_DEFAULT_ASPECT:
	{

		if (nullptr == m_pIDataRes)
		{
			return false;
		}

#ifdef _PRE_LOADMATERIAL_

		bool bReady = true;

		for (int i = 0; i < m_vtMatApt.size(); i++)
		{
			if (m_pIDataRes->InquireAspectState(m_vtMatApt[i]) == EAPTSTATE::APT_READY)
			{
				if (!m_vtMatApt[i]->InitializeCorrelateConstruct((CConstruct**)&m_vtMatl[i],
					m_pIDataRes->IPrimatterMag(), nullptr))
				{
					return false;
				}
			}
			else
			{
				bReady = false;
			}
		}


		m_eStage = bReady ? RT_DEFAULT_CONSTRUCT : m_eStage;
#else

		m_eStage = RT_DEFAULT_CONSTRUCT;


#endif // _PRE_LOADMATERIAL_


	}
	break;


	case ESTAGE::RT_DEFAULT_CONSTRUCT:
	{
		if (0 == m_pISceneDispatcher)
		{
			return false;
		}


		bool bAllReady = true;

#ifdef _PRE_LOADMATERIAL_

		for (int i = 0; i < m_vtMatApt.size(); i++)
		{
			if (m_vtMatApt[i]->CheckCorrelateConstruct((CConstruct**)&m_vtMatl[i], 
				m_pIDataRes->IPrimatterMag()) != EPMTSTATE::READY)
			{
				bAllReady = false;
			}
		}

#endif // _PRE_LOADMATERIAL_


		m_eStage = bAllReady ? ESTAGE::RT_SCENEINI : m_eStage;

	}
	break;


	case ESTAGE::RT_SCENEINI:
	{

		if (!m_pISceneDispatcher->Initalize(&CIDManager::Instance()))
		{
			//release m_pISceneDispatcher;    //add new interface

			return false;
		}

		m_eStage = ESTAGE::RT_SCENECHECK;
	}
	break;



	case ESTAGE::RT_SCENECHECK:
	{
		if ((nullptr == m_pISceneDispatcher) || (nullptr == m_pIRenderMag))
		{
			return false;
		}

		int width = m_pDevice->GetWndWidth();
		int height = m_pDevice->GetWndHeight();
		float ratioWH = (float)width / (float)height;

		m_pISceneDispatcher->CheckState();
		if(m_pISceneDispatcher->AllReady())
		{

#ifdef _PRE_LOADMATERIAL_

			
			if (!m_pUIMag->Initialize(m_pISceneDispatcher, CMsgCenter::Instance(), 
				&CIDManager::Instance()))
			{
				return false;
			}

			
			CSceneNode* pTargetNode = m_pISceneDispatcher->GetCurrentScene()->FindNode("Horse");
			if (0 != pTargetNode)
			{		


				
				float fBaseY = 470.0f;
				float fBaseX = 90.0f;
				float fInterval = 70.0f;
				float fy = fBaseY + 60.0f;
				float fw = 64.0f;
				float fh = 32.0f;

				

				if (!m_pISceneDispatcher->CreateUITree())
				{
					return false;
				}


				if (!m_pISceneDispatcher->InitializeUITree())
				{
					return false;
				}

				
			}
			

#endif // _PRE_LOADMATERIAL_

			m_eStage = ESTAGE::RT_PERFORMAN;
		}
	}
	break;



	case ESTAGE::RT_PERFORMAN:
	{
		if ((0 == m_pIInputDevice) || (0 == m_pISceneDispatcher) || (0 == m_pIRenderMag))
		{
			return false;
		}


		//Input Device update
		int wx = 0;
		int wy = 0;
		m_pDevice->GetWndPos(&wx, &wy);

		m_pIInputDevice->Process(wx, wy, m_pDevice->GetWndWidth(), m_pDevice->GetWndHeight(),
			m_pDevice->GetScreenWidth(), m_pDevice->GetScreenHeight());


		//CTime::Instance().BlockTestInterrupt(true);
		//CTime::Instance().BlockTestBegin();

		int width = m_pDevice->GetWndWidth();
		int height = m_pDevice->GetWndHeight();
		float ratioWH = (float)width / (float)height;

		m_pUIMag->Update(CTime::Instance().getDltTime());


		m_pISceneDispatcher->Update(ratioWH, m_pIRenderMag);

		//CTime::Instance().BlockTestInterrupt("CRt::PM:SceneMag Update:", true);
		//CTime::Instance().BlockTestBegin();


		m_pIRenderMag->Update(m_pISceneDispatcher->GetCurrentScene());

		//CTime::Instance().BlockTestInterrupt("CRt::PM:RenderSys Update:", true);

	}
	break;

	default:
	{
		return false;
	}
	break;
	}


	m_pDevice->Post();


	return true;
}



bool CRoot::LoadScene(const char* pszNamePathFile)
{
	if ((nullptr == pszNamePathFile) || (nullptr == m_pISceneDispatcher) || (nullptr == m_pIDataRes))
	{
		return false;
	}


	m_eStage = ESTAGE::RT_SCENEINI;
	
	return m_pISceneDispatcher->LoadScene(pszNamePathFile);
}





bool CRoot::UnloadScene(const char* pszNamePathFile)
{
	if ((nullptr == m_pIDataRes)||(nullptr == pszNamePathFile))
	{
		return false;
	}


	return m_pISceneDispatcher->UnloadScene(pszNamePathFile);
}



bool CRoot::RemoveScene(const char* pszNamePathFile)
{
	if (0 == pszNamePathFile)
	{
		return false;
	}


	return true;
}



bool CRoot::SetCurrentScene(const char* pszNamePathFile)
{
	if (0 == pszNamePathFile)
	{
		return false;
	}


    return	m_pISceneDispatcher->SetCurrentScene(pszNamePathFile);
}





void CRoot::OnCallback(void* p)
{
	CMsgBase* pMsg = (CMsgBase*)p;
	if (pMsg->type == EMSGTYPE::MSG_TIME)
	{
		Circle();
	}
}



void CRoot::DestroyAll()
{
	if (nullptr != m_pDevice)
	{
		delete m_pDevice;
		m_pDevice = nullptr;
	}

	if (nullptr != m_pIInputDevice)
	{
		ReleaseInputDevice();
		m_pIInputDevice = nullptr;
	}

	if (nullptr != m_pISceneDispatcher)
	{
		ReleaseSceneManager();
		m_pISceneDispatcher = nullptr;
	}

	if (nullptr != m_pIRenderMag)
	{
		ReleaseRenderManager();
		m_pIRenderMag = nullptr;
	}


	//Note: must be at the last.
	if (nullptr != m_pIDataRes)
	{
		ReleaseDataResource();
		m_pIDataRes = nullptr;
	}
}



