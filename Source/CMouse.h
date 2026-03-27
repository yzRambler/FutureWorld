
/*

CMouse

Author:  Zhen Yi

Version: 0.2.0 Alpha


*/





#ifndef _FW_MOUSE_
#define _FW_MOUSE_

#ifdef _WND_OPENGL_PLATFORM_

#include<windows.h>
#include "glfw3.h"

#endif


#include"MathLibrary.h"

namespace FW
{
	class CInputDevice;
	class CMouse
	{
	public:
		CMouse();
		virtual ~CMouse();

/*
#ifdef _WND_OPENGL_PLATFORM_
		bool Initilize(CInputDevice* pInputDC, GLFWwindow* pWndow);
#else
		bool Initilize(CInputDevice* pInputDC);
#endif
*/

		bool Initilize(CInputDevice* pInputDC);

		//orderMB: 0 - left; 1 - middle;  2 - right. 
		void OnMouseButtonDown(int orderMB);
		void OnMouseButtonUp(int orderMB);
		void OnMouseMove(int x, int y);


		//void Update();
		void Check(int wx, int wy, int ww, int wh, int sw, int sh);

		bool OnDrag();

	//attribute
	public:
		const Vector2& deltaPos() { return m_v2DltPos; }

	private:
#ifdef _WND_OPENGL_PLATFORM_

		HANDLE m_hStdInput;
		DWORD m_res;
		INPUT_RECORD m_inputRec;

		int m_nStMLBtn;
		int m_nStMRBtn;
#endif

		CInputDevice* m_pInputDC;

		bool m_bDrag;
		Vector2 m_v2DltPos;

		int m_nPrevX;
		int m_nPrevY;
	};
}


#endif // !_FW_MOUSE_
