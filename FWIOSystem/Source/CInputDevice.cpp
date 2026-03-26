#include"CInputDevice.h"
//#include"CIDManager.h"
#include"CKeyboard.h"
#include"CMouse.h"
#include"CMsgManagerAgent.h"


#ifndef _WND_OPENGL_PLATFORM_

#include<emscripten/emscripten.h>
#include<emscripten/html5.h>

#define _WEB_DEBUG_

#endif


using namespace FW;

CInputDevice* CInputDevice::m_pInstance = nullptr;

#ifdef _WND_OPENGL_PLATFORM_

/*
extern "C" __declspec(dllexport) IInputDevice* CreateInputDevice(CMsgCenter* pMsgCent)
{
	CInputDevice::Instance()->Create(pMsgCent);
	return CInputDevice::Instance();
}
*/

extern "C" DLLIOAPI IInputDevice* CreateInputDevice(CMsgCenter* pMsgCent)
{
	CInputDevice::Instance()->Create(pMsgCent);
	return CInputDevice::Instance();
}


extern "C" DLLIOAPI void ReleaseInputDevice()
{
	CInputDevice::Release();
}


#else

extern "C" IInputDevice* __cdecl CreateInputDevice(CMsgCenter* pMsgCent)
{
	CInputDevice::Instance()->Create(pMsgCent);
	return CInputDevice::Instance();
}


extern "C" void __cdecl ReleaseInputDevice()
{
	CInputDevice::Release();
}

#endif // _WND_OPENGL_PLATFORM_






CInputDevice::CInputDevice():m_pKeyboard(nullptr), m_pMouse(nullptr)//, m_pIDMag(0)
{
	m_mapListener.clear();
}

CInputDevice::~CInputDevice()
{

}


void CInputDevice::Create(CMsgCenter* pMsgCent)
{
	CMsgManagerAgent::Instance().setMsgCenter(pMsgCent);

	if (nullptr == m_pKeyboard)
	{
		m_pKeyboard = new CKeyboard();
		m_pKeyboard->Initialize(this);
	}

	if (nullptr == m_pMouse)
	{
		m_pMouse = new CMouse();

/*
#ifdef _WND_OPENGL_PLATFORM_
		m_pMouse->Initilize(this, (GLFWwindow*)pWndGL);
#else
		m_pMouse->Initilize(this);
#endif // _WND_OPENGL_PLATFORM_
*/
		m_pMouse->Initilize(this);
	}

	

}



void CInputDevice::Destroy()
{
	if (nullptr != m_pKeyboard)
	{
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (nullptr != m_pMouse)
	{
		delete m_pMouse;
		m_pMouse = nullptr;
	}

}



void CInputDevice::Process(int wx, int wy, int ww, int wh, int sw, int sh)
{
	//drive to check key 
	if (0 != m_pKeyboard)
	{
		m_pKeyboard->Check();
	}

	//drive to check mouse 
	if (0 != m_pMouse)
	{
		m_pMouse->Check(wx, wy, ww, wh, sw, sh);
	}
}

