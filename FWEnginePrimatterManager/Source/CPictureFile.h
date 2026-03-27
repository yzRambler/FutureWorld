/*
CPictureFile

Author: Zhen Yi
Created Date: May 08, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_PICTUREFILE_
#define _FW_PICTUREFILE_

#include"CFile.h"

namespace FW
{
	class CPictureFile : public CFile
	{
	public:
		CPictureFile(const char* pszFileName) :CFile(pszFileName, pszFileName) {}
		virtual ~CPictureFile() {}

		//derive from CFile
		virtual bool Parse()
		{
			if ((m_pBuffer == 0) || (m_nSize <= 0)) { return false; }  return true;
		}
	};


}


#endif // !_FW_PICTURE_
