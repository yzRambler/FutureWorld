/*

CData


Author: Zhen Yi (взеђ)

Create Date: April 23, 2023

Version 0.2.1 Alpha

*/


#ifndef _FW_DATA_
#define _FW_DATA_

#include"Common.h"
#include"CString.h"
#include"FWEngineBaseExport.h"


namespace FW
{
	class DLLBSAPI CData
	{
	public:
		CData();
		CData(const char* pszName); 
		virtual ~CData();

	//attribute
	public:
		const char* nameData() { return m_strNameData.Get(); }

		void setNameData(const char* pszName) 
		{ if (0 == pszName) { return; }  m_strNameData.Set(pszName); }

		const char* namePathFile() { return m_strNamePathAndFileData.Get(); }
		
		void setNameFileData(const char* pszNameFile) 
		{ if (0 == pszNameFile) { return; }  m_strNamePathAndFileData.Set(pszNameFile); }

		void* pointerSubclass() { return m_pSubclass; }
		void setPointerSubclass(void* p) { m_pSubclass = p; }

	private:
		CString m_strNameData;

		CString m_strNamePathAndFileData;

		//This member is used to save the subclass object address, specific multiply inheriting 
		// subclass such as  CSceneAspect / CScene / CPrimatterAspect / CPrimatter etc. 
		void* m_pSubclass;
	};
};




#endif // !_FW_DATA_
