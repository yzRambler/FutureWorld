/*

Tools

Author: Zhen Yi


Created Date: Nov. 19, 2023

Version: 0.2.0 Alpha


*/


#ifndef _FW_TOOLS_
#define _FW_TOOLS_

#include<memory.h>
#include<string.h>

namespace FW
{

	inline char* CloneStr(char** ppTargetBuf, char* pSrcBuf, int len)
	{
		if (0 == pSrcBuf)
		{
			return 0;
		}

		char* pstr = new char[len + 1];
		memcpy(pstr, pSrcBuf, len);
		pstr[len] = '\0';

		*ppTargetBuf = pstr;

		return *ppTargetBuf;
	}

	inline char* CloneStr(char** ppTargetBuf, const char* pScrBuf)
	{
		if (0 == pScrBuf)
		{
			return 0;
		}

		int len = strlen(pScrBuf);
		return CloneStr(ppTargetBuf, (char*)pScrBuf, len);
	}



	inline void ReleaseStr(char* pBuf)
	{
		if (0 != pBuf)
		{
			delete[] pBuf;
		}
	}

}




#endif // !_FW_TOOLS_

