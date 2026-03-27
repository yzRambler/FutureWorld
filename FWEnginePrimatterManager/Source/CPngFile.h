
/*

CPngFile

Author:  Zhen Yi - взеђ

Version: 0.2.0 Alpha

*/



#ifndef _FW_PNGFILE_
#define _FW_PNGFILE_

#include"CPictureFile.h"

namespace FW
{
	class CPngFile :public CPictureFile
	{
	public:
		CPngFile(const char* pszFileName);
		virtual ~CPngFile();

		//derive from CPictureFile
		virtual bool Parse();

		//atrribute
	public:
		unsigned char* bufferColor() { return m_pBufferColor; }
		int width() { return m_nWidth; }
		int height() { return m_nHeight; }
		int stride() { return m_nStride; }

	private:
		

	private:
		unsigned char* m_pBufferColor;

		int m_nWidth;
		int m_nHeight;
		int m_nStride;
	};

}



#endif // !_FW_PNGFILE_
