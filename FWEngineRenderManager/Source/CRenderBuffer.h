/*

CRenderBuffer


Author:  Zhen Yi

Created Date: Nov. 6, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_RENDERBUFFER_
#define _FW_RENDERBUFFER_

#include"GL/glew.h"
#include"COutputBuffer.h"



namespace FW
{

	class CRenderBuffer : public COutputBuffer
	{
	public:
		typedef enum eRBufferType {
			RB_COLOR = 0, RB_DEPTH, RB_STENCIL, RB_UNKNOW
		}ERBTYPE;

	public:
		CRenderBuffer();
		CRenderBuffer(const char* pszName);
		virtual ~CRenderBuffer();
	
		virtual void Initialize();


	//Inherite from COutputBuffer
	public:
		virtual bool Create(int w, int h, ERBTYPE type = ERBTYPE::RB_DEPTH);
		virtual void Bind();


	//attribute
	public:
		ERBTYPE typeRB() { return m_eTypeRB; }
		void setTypeRB(ERBTYPE type) { m_eTypeRB = type; }

	private:
		ERBTYPE m_eTypeRB;
	
	};


}




#endif // !_FW_RENDERBUFFER_
