/*

CMsgCenter

Author:  Zhen Yi.   взеђ

Created Date: Feb. 23, 2024

Version: 0.2.0 Alpha

*/


#ifndef  _FW_MESSAGE_CENTER_
#define _FW_MESSAGE_CENTER_

#include<list>
#include<map>
#include"CMessage.h"
#include"IMsgListener.h"
#include"CICTarget.h"


namespace FW
{
	class DLLSHAPI CMsgCenter : public CICTarget
	{
	private:
		typedef std::list<CMsgBase*> LTMSG;
		typedef LTMSG::iterator LTMSG_ITER;


	//Inheriate from CICTarget
	public:
		virtual bool RegisterLst(CListener* pLsn);
		virtual void UnregisterLst(CListener* pLsn);
		virtual void Update();


	public:
		CMsgCenter();
		virtual ~CMsgCenter();

		static CMsgCenter* Instance()
		{
			if (0 == m_pInst)
			{
				m_pInst = new CMsgCenter;
			}

			return m_pInst;
		}


		bool Create();


		void AddMessage(CMsgBase* pMsg) { m_lsMsg.push_back(pMsg); }



	private:
		void Clean();

	private:
		static CMsgCenter* m_pInst;

		FDWORD m_idInt;  //for CInterchangeCenter

		LTMSG m_lsMsg;

	};

}





#endif // ! _FW_MESSAGE_CENTER_
