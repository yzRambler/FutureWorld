/*
CRenderToTexture


Author: Zhen Yi

Created Date: Nov. 14, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_RENDER_TO_TEXTURE_
#define _FW_RENDER_TO_TEXTURE_

#include"CFrameBuffer.h"

namespace FW
{
	class CTextureBuffer;
	class CRenderToTexture : public CFrameBuffer
	{
	public:
		CRenderToTexture();
		virtual ~CRenderToTexture();

	//Inherit from CFrameBuffer 
	public:
		virtual bool Create(int width, int height);

	//Attribute:
	public:
		CTextureBuffer* textureBuffer() { return (CTextureBuffer*)m_lstOptBuf.front(); }
	};
}




#endif // !_FW_RENDER_TO_TEXTURE_
