/*

CWindowsDevice


Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_WINDOWS_DEVICE_
#define _FW_WINDOWS_DEVICE_

#include "CDevice.h"

#include "GL/glew.h"
#include "glfw3.h"


#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"

namespace FW
{
	class CWindowsDevice : public CDevice
	{
	public:
		CWindowsDevice();
		virtual ~CWindowsDevice();

		void OnMouse(GLFWwindow* window, int button, int action, int mods) {}

	//Inherit from CDevice
	public:
		virtual bool Create(int width, int height, IInputDevice* pIIDevice);
		virtual void Destroy();

		virtual bool Update();
		virtual void Post();

		virtual void GetWndPos(int* px, int* py) 
		{ if (0 != m_pWindow) { glfwGetWindowPos(m_pWindow, px, py); } }

	//attribute
	public:
		void* pointGLWnd() { return m_pWindow; }
		void* getWndHandle() { return  glfwGetWin32Window(m_pWindow); }

	private:
		GLFWwindow* m_pWindow;
		bool m_bValid;
	};
}


#endif // !_FW_DEVICE_

