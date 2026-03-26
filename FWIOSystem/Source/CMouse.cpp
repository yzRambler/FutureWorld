#ifdef _WND_OPENGL_PLATFORM_

#define KEY_DOWN(x) ( 0 != ((x) & 0xff00))

#else

#endif

#include"CInputDevice.h"
#include"CMouse.h""
#include"CMsgCenter.h"
#include"CMsgManagerAgent.h"



using namespace FW;
#ifdef _WND_OPENGL_PLATFORM_
CMouse::CMouse() :m_bDrag(false), m_nPrevX(0), m_nPrevY(0), m_pInputDC(0), 
m_nStMLBtn(GLFW_RELEASE)
#else
CMouse::CMouse() :m_bDrag(false), m_nPrevX(0), m_nPrevY(0), m_pInputDC(0)
#endif
{
}

CMouse::~CMouse()
{

}

bool CMouse::OnDrag()
{
	return m_bDrag;
}

/*
#ifdef _WND_OPENGL_PLATFORM_
bool CMouse::Initilize(CInputDevice* pInputDC, GLFWwindow* pWndow)
#else
bool CMouse::Initilize(CInputDevice* pInputDC)
#endif // _WND_OPENGL_PLATFORM_
*/

bool CMouse::Initilize(CInputDevice* pInputDC)
{
	m_pInputDC = pInputDC; 
	
#ifdef _WND_OPENGL_PLATFORM_

	//m_hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	//m_pWindow = pWndow;
#endif

	return true;
}


void CMouse::OnMouseButtonDown(int orderMB)
{
	switch (orderMB)
	{
	case 0:  //mouse left button
	{
		CMsgLBDown* msgDw = new CMsgLBDown;
		msgDw->Create(0, 0);

		CMsgManagerAgent::Instance().msgCenter().AddMessage(msgDw);
	}
	break;

	case 1:  //mouse middle button
	{

	}
	break;

	case 2:  //mouse right button
	{

	}
	break;

	default:
		break;
	}
}


void CMouse::OnMouseButtonUp(int orderMB)
{
	switch (orderMB)
	{
	case 0:  //mouse left button
	{
		CMsgLBUp* msgUp = new CMsgLBUp;
		msgUp->Create(0, 0);

		CMsgManagerAgent::Instance().msgCenter().AddMessage(msgUp);
	}
	break;

	case 1:  //mouse middle button
	{

	}
	break;

	case 2:  //mouse right button
	{

	}
	break;

	default:
		break;
	}
}


void CMouse::OnMouseMove(int x, int y)
{
	m_v2DltPos.x = x - m_nPrevX;
	m_v2DltPos.y = y - m_nPrevY;

	m_nPrevX = x;
	m_nPrevY = y;

	CMsgMSMove* msgMv = new CMsgMSMove;
	msgMv->Create(m_nPrevX, m_nPrevY, m_v2DltPos.x, m_v2DltPos.y);

	CMsgManagerAgent::Instance().msgCenter().AddMessage(msgMv);
}



//void CMouse::Update()
void CMouse::Check(int wx, int wy, int ww, int wh, int sw, int sh)
{
#ifdef _WND_OPENGL_PLATFORM_

	if (0 == m_pInputDC)
	{
		return;
	}

	/*
	//check mouse click
	int stMLBtn = glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT);
	if (stMLBtn == GLFW_PRESS)
	{
		if (m_nStMLBtn == GLFW_RELEASE)
		{
			CMsgLBDown* msgDw = new CMsgLBDown;
			CMsgManagerAgent::Instance()->msgCenter().AddMessage(msgDw);

			m_nStMLBtn = GLFW_PRESS;
		}
	}
	else if (stMLBtn == GLFW_RELEASE)
	{
		if (m_nStMLBtn == GLFW_PRESS)
		{
			CMsgLBUp* msgUp = new CMsgLBUp;
			CMsgManagerAgent::Instance()->msgCenter().AddMessage(msgUp);

			m_nStMLBtn = GLFW_RELEASE;
		}
	}
	*/


	/*
	//get mouse position
	POINT pt;
	if (GetCursorPos(&pt))
	{
		//mapping into window space from screen space
		float fdx = (float)ww / (float)sw;
		float fdy = (float)wh / (float)sh;

		pt.x = pt.x < wx ? wx : (pt.x > wx + ww ? wx + ww : (pt.x - wx)*fdx);
		pt.y = pt.y < wy ? wy : (pt.y > wy + wh ? wy + wh : (pt.y - wh)*fdy);

		m_v2DltPos.x = pt.x - m_nPrevX;
		m_v2DltPos.y = pt.y - m_nPrevY;

		m_nPrevX = pt.x;
		m_nPrevY = pt.y;
	}


	if (KEY_DOWN(GetKeyState(VK_RBUTTON)))
	{
		m_pInputDC->OnMouseDrag(m_v2DltPos.x, m_v2DltPos.y);
		m_bDrag = true;
	}
	else
	{
		m_bDrag = false;
	}
	*/

	/*
	CMsgMSMove* msgMv = new CMsgMSMove;
	msgMv->Create(m_nPrevX, m_nPrevY, m_v2DltPos.x, m_v2DltPos.y);

	//CMsgCenter::Instance()->AddMessage(msg);
	CMsgManagerAgent::Instance()->msgCenter().AddMessage(msgMv);
	*/


#endif
}
