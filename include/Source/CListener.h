/*

CListener


Author:  Zhen  Yi

Created Date: Jul. 16, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_LISTENSER
#define _FW_LISTENSER

#include"CConstruct.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class DLLCOAPI CListener : public CConstruct
	{
	public:
		CListener(CConstruct* pHost):
			CConstruct(pHost, ECONSTRTYPE::CST_LISTERNER){}

		CListener(const char* pszName, CConstruct* pHost):
			CConstruct(pszName, pHost, ECONSTRTYPE::CST_LISTERNER){}

		virtual ~CListener() {}

		virtual FDWORD GetID() = 0;
		virtual const char* GetName() = 0;
		virtual void OnCallback(void* p) = 0;

	};

}





#endif // !_FW_LISTENSE
