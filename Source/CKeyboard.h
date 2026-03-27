/*

CKeyboard


Author:  Zhen Yi

Version: 0.2.0 Alpha


*/





#ifndef _FW_KEYBOARD_
#define _FW_KEYBOARD_

namespace FW
{
	class CInputDevice;
	class CKeyboard
	{
		/*
	public:
		enum EKEY{E_A=0, E_B, E_C, E_D, E_E, E_F, E_G, E_H, E_I, E_J, E_K, E_L, E_M, 
			      E_N, E_O, E_P, E_Q, E_R, E_S, E_T, E_U, E_V, E_W, E_X, E_Y, E_Z, E_NONE};
		*/

	public:
		CKeyboard();
		virtual ~CKeyboard();

		bool Initialize(CInputDevice* pInputDC) { m_pInputDC = pInputDC; return true; }

		/*
		  Just check single key state only, but not combine keys.
		*/
		void Check();

		void OnKeyPress(char vk);
		void OnKeyDown(char vk);
		void OnKeyUp(char vk);


	private:
		CInputDevice* m_pInputDC;

		//temporary code
		char m_key;

	};
}



#endif // !_FW_KEYBOARD_
