#include"CKeyboard.h"
#include"CInputDevice.h"

#ifdef _WND_OPENGL_PLATFORM_

#include<windows.h>

//#define KEY_PRESS(x) ( 0 != ((x) & 0xff00))
#define KEY_DOWN(x) ( 0 != ((x) & 0xff00))

#else

#include<emscripten/emscripten.h>
//#define _WEB_DEBUG_

#endif // _WND_OPENGL_PLATFORM_



using namespace FW;

CKeyboard::CKeyboard():m_key(0), m_pInputDC(0)
{
}

CKeyboard::~CKeyboard()
{
}



void CKeyboard::Check()
{
#ifdef _WND_OPENGL_PLATFORM_

	if (0 == m_pInputDC)
	{
		return;
	}

	char key = 'A';

	for (int i = 0; i < 26; i++)
	{
		key += i;
		SHORT rs = GetKeyState(key);
		if (KEY_DOWN(rs))
		{
			if (key != m_key)
			{
				//m_pInputDC->OnKeyDownByKeyboard(key);
				//m_key = key;
			}
			else
			{
				//m_pInputDC->OnKeyPressByKeyboard(key);
			}
		}
		else
		{
			if (key == m_key)
			{
				//m_pInputDC->OnKeyUpByKeyboard(key);
				//m_key = 0;
			}
		}
	}
	

#endif
}



void CKeyboard::OnKeyPress(char vk)
{
	if (0 != m_pInputDC)
	{
		//m_pInputDC->OnKeyPressByKeyboard(vk);
	}
}


void CKeyboard::OnKeyDown(char vk)
{
	if (0 != m_pInputDC)
	{
		//m_pInputDC->OnKeyDownByKeyboard(vk);
	}
}


void CKeyboard::OnKeyUp(char vk)
{
	if (0 != m_pInputDC)
	{
		//m_pInputDC->OnKeyUpByKeyboard(vk);
	}
}


/*
bool CKeyboard::KeyPressed(char key)
{
#ifdef _WND_OPENGL_PLATFORM_

	SHORT rs = GetKeyState(key);
	return KEY_DOWN(rs);
#else
	if(m_key == key)
	{

#ifdef _WEB_DEBUG_
		EM_ASM({
			console.log("The key pressed is:" + UTF8ToString($0))
		},(char*)&key);
#endif
	}

	return m_key == key;
#endif // _WND_OPENGL_PLATFORM_

}
*/
