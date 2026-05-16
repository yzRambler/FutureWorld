/*
CBase

Author: Zhen Yi (взеђ)
Create Date: May 7 2021

Version 0.2.1 Alpha

*/




#ifndef  _FW_BASE_
#define _FW_BASE_

#include"CString.h"
#include"FWEngineBaseExport.h"


namespace FW
{
	class DLLBSAPI CBase
	{
	public:
		CBase() {}
		CBase(const char* pszName) 
		{
			m_strName.Set(pszName);
		}

		virtual ~CBase()
		{
		}


		void ResetName(const char* pszName)
		{
			m_strName.Set(pszName);
		}

	
	//attribute
	public:
		const char* name() { return m_strName.Get(); }
		void setName(const char* pszName) { m_strName.Set(pszName); }

	private:
		CString m_strName;
	};
}


#endif // ! _FW_BASE_
