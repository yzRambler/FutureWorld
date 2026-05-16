/*

CPlatform


Author:  Zhen Yi (взеђ)

Create Date: Mar. 5,  2023

Version 0.2.1 Alpha

*/

#ifndef _FW_PLATFORM_
#define _FW_PLATFORM_

#include"CFile.h"


namespace FW
{
	class CFileNode;
	class CPlatform
	{
	public:
		CPlatform() :m_pFile(0) {}
		virtual ~CPlatform() { m_pFile = 0; }

		virtual void OpenAndCopy(CFile* pFile) = 0;

		virtual CFileNode* CreateFileTree(const char* pszNamePath) { return nullptr; }

	protected:
		CFile* m_pFile;

	};

}



#endif // !_FW_PLATFORM_
