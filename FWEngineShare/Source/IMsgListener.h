/*

CListener


Author: Zhen Yi.  ( взеђ )

Created Date: Feb, 23, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_LISTENER_
#define _FW_LISTENER_

#include"BaseData.h"
#include"CMessage.h"
#include"FWEngineShareExport.h"

namespace FW
{
	class DLLSHAPI IMsgListener
	{
	public:
		virtual FDWORD GetID() = 0;
		virtual const char* GetName() = 0;
		virtual void OnMsg(CMsgBase* pMsg) = 0;
	};
}




#endif // !_FW_LISTENER_
