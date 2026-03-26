#include "CWindowsDevice.h"
#include <stdio.h>
#include <Windows.h>
#include "CInputDecAgent.h"

//#include<vld.h>


using namespace FW;

static void error_callback(int error, const char* pDiscript)
{
	//std::cout << pDiscript << "\n";+
	printf_s("%s", pDiscript);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
		
}


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			CInputDecAgent::Instance().IIDec()->OnMouseButtonDown(0);
		}
		else if (action == GLFW_RELEASE)
		{
			CInputDecAgent::Instance().IIDec()->OnMouseButtonUp(0);
		}

	}
}


static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	CInputDecAgent::Instance().IIDec()->OnMouseMove(xpos, ypos);
}


CWindowsDevice::CWindowsDevice():m_pWindow(nullptr)
{
}

CWindowsDevice::~CWindowsDevice()
{
	Destroy();
}

bool CWindowsDevice::Create(int width, int height, IInputDevice* pIIDevice)
{
	if (!CDevice::Create(width, height, pIIDevice))
	{
		return false;
	}

	m_nWidthScrn = GetSystemMetrics(SM_CXSCREEN);
	m_nHeightScrn = GetSystemMetrics(SM_CYSCREEN);

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	m_pWindow = glfwCreateWindow(m_nWidthWnd, m_nHeightWnd, "Device Window", NULL, NULL);

	if (m_pWindow == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwSetKeyCallback(m_pWindow, key_callback);

	glfwSetMouseButtonCallback(m_pWindow, mouse_button_callback);

	glfwSetCursorPosCallback(m_pWindow, cursor_pos_callback);

	glfwMakeContextCurrent(m_pWindow);

	// Set this to true so GLEW knows to use a modern approach to retrieving function 
	// pointers and extensions
	glewExperimental = GL_TRUE;


	//glfwSetInputMode(m_pWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	m_bValid = true;


	CInputDecAgent::Instance().setIIDec(m_pIIDevice);

	return true;
}


void CWindowsDevice::Destroy()
{
	if (m_pWindow != NULL)
	{
		glfwDestroyWindow(m_pWindow);
	}
	
	glfwTerminate();

	CInputDecAgent::Release();
}


bool CWindowsDevice::Update()
{
	if (m_pWindow != NULL)
	{
		m_bValid = !glfwWindowShouldClose(m_pWindow);
		glfwGetFramebufferSize(m_pWindow, &m_nWidthWnd, &m_nHeightWnd);
		
		CDevice::Update();
	}

	return m_bValid;
}


void CWindowsDevice::Post()
{
	if (m_pWindow != NULL)
	{
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
	
}



