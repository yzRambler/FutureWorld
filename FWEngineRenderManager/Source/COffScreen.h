/*

COffScreen


Author: Zhen Yi

Created Date: Nov. 14, 2023

Version: 0.2.0 Alpha


*/


#ifndef _FW_OFFSCREEN_
#define _FW_OFFSCREEN_

#include"CScreen.h"
#include"CRenderToTexture.h"

namespace FW
{
	class COffScreen : public CScreen
	{
	public:
		COffScreen();
		COffScreen(const char* pszName);
		virtual ~COffScreen();


		//Inherit from CScreen
	public:
		virtual bool Create(int id, int width, int height);


		//attribute
	public:
		CTextureBuffer* textureBuffer()
		{
			if (0 == m_pFrameBuf) { return 0; } return ((CRenderToTexture*)m_pFrameBuf)->textureBuffer();
		}

	};

}



#endif // ! _FW_OFFSCREEN_
