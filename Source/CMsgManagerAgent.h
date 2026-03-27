/*

CMsgManagerAgent


Author:  Zhen Yi (взеђ)


Created Date:  Feb. 25, 2024

Version: 0.2.0 Alpha


*/

#ifndef _FW_MSGMANAGER_AGNET_
#define _FW_MSGMANAGER_AGNET_

#include"CMsgCenter.h"


namespace FW
{

	class DLLSHAPI CMsgManagerAgent
	{
	public:
		CMsgManagerAgent(): m_pMsgCenter(0) {}
		virtual ~CMsgManagerAgent() {}

		static CMsgManagerAgent& Instance()
		{
			if (0 == m_pInstan)
			{
				m_pInstan = new CMsgManagerAgent;
			}

			return *m_pInstan;
		}

	//attribute
	public:
		CMsgCenter& msgCenter() { return *m_pMsgCenter; }
		void setMsgCenter(CMsgCenter* pMsgCent) 
		{ if ((pMsgCent != 0) && (0 == m_pMsgCenter)) { m_pMsgCenter = pMsgCent; } }


	private:
		static CMsgManagerAgent* m_pInstan;
		CMsgCenter* m_pMsgCenter;

	};



}



#endif // !_FW_MSGMANAGER_AGNET_
