/*
IInputDeivce


Author:  Zhen Yi

Created Date:  July 15, 2023

Version: 0.2.0 Alpha

*/



#ifndef _INTERFACE_INPUTDEVICE_
#define _INTERFACE_INPUTDEVICE_

#include"Common.h"
#include"CMsgCenter.h"
#include"FWIOSystemExport.h"


namespace FW
{

	class CIOListener
	{
	public:
		CIOListener():m_id(0){}
		virtual ~CIOListener(){}

		/*
		  vk equal the character ASCII value. 
		  A~Z :  65~90.
		  a~z :  97~122
		*/
		virtual void OnKeyDown(int vk) {}
		virtual void OnKeyUp(int vk) {}
		virtual void OnKeyPress(int vk) {}

		virtual void OnMouseDrag(float dx, float dy) {}
		virtual void OnMouseLButtonDown() {}
		virtual void OnMouseMButtonDown() {}
		virtual void OnMouseRButtonDown() {}
		virtual void OnMouseLButtonUp() {}
		virtual void OnMouseMButtonUp() {}
		virtual void OnMouseRButtonUp() {}

	//attribute
	public:
		void setID(FDWORD id) { m_id = id; }
		FDWORD id() { return m_id; }

	private:
		FDWORD m_id;
	};


	class IInputDevice
	{
	public:
		//orderMB: 0 - mouse button left; 1 - mouse button middle;  2 - mouse button right. 
		virtual void OnMouseButtonDown(int orderBtn) = 0;
		virtual void OnMouseButtonUp(int orderBtn) = 0;
		virtual void OnMouseMove(int x, int y) = 0;

		//wx, wy: the coordinate of the window position
		//ww, wh: the width and height of the window
		//sw, sh: the width and height of the screen
		virtual void Process(int wx, int wy, int ww, int wh, int sw, int sh) = 0;
	};


#ifdef _WND_OPENGL_PLATFORM_


	extern "C" DLLIOAPI IInputDevice* CreateInputDevice(CMsgCenter* pMsgCent);
	extern "C" DLLIOAPI void ReleaseInputDevice();

#else
	extern "C" IInputDevice* __cdecl CreateInputDevice(CMsgCenter* pMsgCent);
	extern "C" void __cdecl ReleaseInputDevice();

#endif // _WND_OPENGL_PLATFORM_



}



#endif // !_INTERFACE_INPUTDEVICE_
