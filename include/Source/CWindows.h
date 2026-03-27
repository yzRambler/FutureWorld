/*
CWindows

Author: Zhen Yi
Created Date: May 08, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_WINDOWS_
#define _FW_WINDOWS_

#include<stdio.h>
#include"CPlatform.h"

namespace FW
{
	class CWindows : public CPlatform
	{
	public:
		CWindows(){}
		virtual ~CWindows(){}

	    //derived from CFilePlatform
		virtual void OpenAndCopy(CFile* pFile);

	private:
		FILE* m_pHandleFile;

	};

}



#endif // ! _FW_WINDOWS_
