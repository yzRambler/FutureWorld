/*

COutputBuffer


Author:  Zhen Yi

Created Date: Nov. 6, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_OUTPUTBUFFER_
#define _FW_OUTPUTBUFFER_

#include"CBase.h"
#include"CommonPrimatter.h"


namespace FW
{
	class COutputBuffer: public CBase
	{
	public:
		COutputBuffer(EOUTBFTYPE type = EOUTBFTYPE::OUB_UNKNOW): m_eOutputBufferType(type), m_bCreatedSign(false),
		m_id(0){}

		COutputBuffer(const char* pszName, EOUTBFTYPE type = EOUTBFTYPE::OUB_UNKNOW) : CBase(pszName), 
			m_eOutputBufferType(type), m_bCreatedSign(false), m_id(0){}

		virtual ~COutputBuffer() {}

		virtual bool Create(int w, int h) 
		{
			if (m_bCreatedSign) { return false; }
			if ((w <= 0) || (h <= 0)) { return false; }	m_bCreatedSign = true; m_nWidth = w; m_nHeight = h;
			return true;
		}

		virtual void Bind() {}


	//attribute
	public:
		EOUTBFTYPE type() { return m_eOutputBufferType; }
		void setType(EOUTBFTYPE type) { m_eOutputBufferType = type; }

		GLuint id() { return m_id; }

		int Width() { return m_nWidth; }
		void setWidth(int w) { m_nWidth = w; }

		int Height() { return m_nHeight; }
		void setHeight(int h) { m_nHeight = h; }

		bool isCreated() { return m_bCreatedSign; }



	protected:
		GLuint m_id;
		bool m_bCreatedSign;
		int m_nWidth;
		int m_nHeight;


	private:
		EOUTBFTYPE m_eOutputBufferType;
	};
}




#endif // !_FW_OUTPUTBUFFER_
