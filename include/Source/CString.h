/*

CString

Author:  Zhen Yi.    взеђ

Created Date: Mar. 5, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_STRING_
#define _FW_STRING_
#include<memory>
#include"FWEngineCoreExport.h"




namespace FW
{
	class DLLCOAPI CString
	{
	public:
		CString():m_pszStr(nullptr) {}
		CString(const char* pszStr):m_pszStr(nullptr){ Set(pszStr); }
		virtual ~CString() { Release(); }

		CString& operator=(CString& strSrc) { Set(strSrc.Get()); return *this; }

		void Set(const char* pszStr)
		{
			if ((0 == pszStr)||(pszStr == m_pszStr))
			{
				return;
			}

			int len = strlen(pszStr);
			if (0 == len)
			{
				return;
			}

			Release();
			m_pszStr = new char[len + 1];
			memcpy(m_pszStr, pszStr, len);
			m_pszStr[len] = '\0';
		}

		const char* Get() { return m_pszStr; }

	private:
		void Release() { if (nullptr != m_pszStr) { delete[] m_pszStr; } }

	private:
		char* m_pszStr;
	};

}





#endif // !_FW_STRING_
