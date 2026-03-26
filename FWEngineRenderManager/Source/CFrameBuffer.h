/*
CFrameBuffer


Author:  Zhen  Yi

Created Date: Nov. 6, 2023

Version: 0.2.0 Alpha


*/

#ifndef _FW_FRAMEBUFFER_
#define _FW_FRAMEBUFFER_

#include<list>

#include"GL/glew.h"
#include"CBase.h"
#include"CTextureBuffer.h"


namespace FW
{
	class COutputBuffer;
	class CFrameBuffer : public CBase
	{
	private:
		typedef std::list<COutputBuffer*> LSTOUTBUF;
		typedef LSTOUTBUF::iterator LSTOUTBUF_ITER;


	public:
		CFrameBuffer();
		virtual ~CFrameBuffer();

		virtual bool Create( int width, int height );
		void Bind();

		void AttachOutputBuffer(COutputBuffer* pBuffer);
		void DetachOutputBuffer(COutputBuffer* pBuffer);

		bool CheckCompletness()
		{ return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE; }

		void RenderToScreen() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }


	//attribute
	public:
		GLuint id() { return m_uFBufferId; }
		bool isInit() { return m_bCreatedSign; }


	protected:
		LSTOUTBUF m_lstOptBuf;
		int m_nWidth;
		int m_nHeight;


	private:
		GLuint m_uFBufferId;
		bool m_bCreatedSign;


	};


}




#endif // !_FW_FRAME_BUFFER_
