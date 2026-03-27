/*

CTextureBuffer


Author:  Zhen Yi

Created Date:  Nov. 6, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_TEXTUREBUFFER_
#define _FW_TEXTUREBUFFER_

#include"GL/glew.h"
#include"COutputBuffer.h"



namespace FW
{
	class CTextureBuffer : public COutputBuffer
	{
	public:
		typedef enum eTBufferType {
			TB_2D = 0, TB_CUBE, TB_3D, TB_UNKNOW
		}ETBTYPE;

	public:
		CTextureBuffer();
		CTextureBuffer(const char* pszName);
		virtual ~CTextureBuffer();
		
		virtual void Initialize();


	//Inherite from COutputBuffer
	public:
		virtual bool Create(int width, int height, ETBTYPE type = ETBTYPE::TB_2D);
		virtual void Bind();


	//attribute
	public:
		ETBTYPE typeTB() { return m_typeTB; }
		void setTypeTB(ETBTYPE type) { m_typeTB = type; }


	private:
		ETBTYPE m_typeTB;
	};
}



#endif // !_FW_TEXTUREBUFFER_
