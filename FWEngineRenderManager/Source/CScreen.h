/*

CScreen


Author:  Zhen Yi

Created Date: Nov. 9, 2023

Version: 0.2.0 Alpha


*/


#ifndef _FW_SCREEN_
#define _FW_SCREEN_

#include"CFrameBuffer.h"

namespace FW
{
	class CScreen : public CBase
	{
	public:
		CScreen();
		CScreen(const char* pszName);
		virtual ~CScreen();

		virtual bool Create(int id, int w, int h);
		bool Bind()
		{
			if (0 == m_pFrameBuf) { return false; } 
			m_pFrameBuf->Bind(); return m_pFrameBuf->CheckCompletness();
		}

		void OutputIntoScreen() { if (0 != m_pFrameBuf) { m_pFrameBuf->RenderToScreen(); } }

		void CheckUnbindReason();


	//attribute
	public:
		int id() { return m_nID; }


	protected:
		CFrameBuffer* m_pFrameBuf;
		int m_nID;
	};


}




#endif // !_FW_SCREEN_
