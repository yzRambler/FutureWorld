/*

CEssetyMsgListener


Author:  Zhen Yi

Created Date: Feb. 28, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_ESSETY_MSGLISTENER_
#define _FW_ESSETY_MSGLISTENER_

#include"CListener.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class CEssety;
	class DLLCOAPI CEssetyMsgListener : public CListener
	{
	public:
		CEssetyMsgListener(CEssety* pHost);
		virtual ~CEssetyMsgListener();

	//Inherit from CListener
	public:
		virtual FDWORD GetID(); 
		virtual const char* GetName(); 
		virtual void OnCallback(void* p);


	private:
		//CEssety* m_pHost;
	};

}




#endif // !_FW_ESSETY_MSGLISTENER_
