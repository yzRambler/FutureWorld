/*
CFilePlatform

Author: Zhen Yi
Created Date: May 08, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_FILE_PLATFORM_
#define _FW_FILE_PLATFORM_

#include"CFile.h"
#include<memory>

namespace FW
{
	class CFilePlatform
	{
	public:
		CFilePlatform():m_pFile(0){}
		virtual ~CFilePlatform(){ m_pFile = 0; }

		virtual void Open(CFile* pFile) = 0;
	
	protected:
		CFile* m_pFile;
	};

}


#endif // !_FW_FILE_PLATFORM_
