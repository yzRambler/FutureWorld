/*

CUIMsgListener


Author:  Zhen Yi   (взеђ)

Created Date: Feb, 24, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_UI_MSGLISTENER_
#define _FW_UI_MSGLISTENER_

#include"CListener.h"
#include"FWUIExport.h"


namespace FW
{

	class DLLCOAPI CUIMsgListener : public CListener
	{
	public:
		CUIMsgListener(CConstruct* pHost) :CListener(pHost) {}
		CUIMsgListener(const char* pszName, CConstruct* pHost):CListener(pszName, pHost) {}

		virtual ~CUIMsgListener() {}


	//Inherit from IMsgListener
	public:
		virtual FDWORD GetID() { return m_pHost->id(); }
		virtual const char* GetName() { return m_pHost->name(); }
		virtual void OnCallback(void* p);

	private:
		//CUI* m_pHost;
	};

}




#endif // !_FW_UI_MSGLISTENER_
