/*
CWindows

Author: Zhen Yi
Create Date: May 08, 2021

Version 0.2.1 Alpha

*/

#ifndef _FW_WINDOWS_
#define _FW_WINDOWS_

#include<stdio.h>
#include"CPlatform.h"
#include"CFileNode.h"

namespace FW
{
	class CWindows : public CPlatform
	{
		//derived from CFilePlatform
	public:
		virtual void OpenAndCopy(CFile* pFile);
		virtual CFileNode* CreateFileTree(const char* pszNamePath);


	public:
		CWindows();
		virtual ~CWindows();



	private:
		FILE* m_pHandleFile;
		CFileNode* m_pFileTreeRoot;

	};

}



#endif // ! _FW_WINDOWS_
