/*

CPlatform


Author:  Zhen Yi

Created Date: Mar. 5,  2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_PLATFORM_
#define _FW_PLATFORM_

#include"CFile.h"


namespace FW
{
	class CPlatform
	{
	public:
		CPlatform() :m_pFile(0) {}
		virtual ~CPlatform() { m_pFile = 0; }

		virtual void OpenAndCopy(CFile* pFile) = 0;

	protected:
		CFile* m_pFile;

	};

}



#endif // !_FW_PLATFORM_
