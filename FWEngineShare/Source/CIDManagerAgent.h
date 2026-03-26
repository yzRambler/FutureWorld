/*

CIDManagerAgent


Author:  Zhen Yi.  £¨Ò×Õò£©

Created Date: Mar. 17 2024

Version: 0.2.0 Alpha

*/

#ifndef _FW_IDMANAGER_AGENT_
#define _FW_IDMANAGER_AGENT_

#include"CIDManager.h"


namespace FW
{
	class DLLSHAPI CIDManagerAgent
	{
	public:
		CIDManagerAgent() {}
		virtual ~CIDManagerAgent() {}

		static CIDManagerAgent& Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CIDManagerAgent;
			}

			return *m_pInst;
		}


		static void Release()
		{
			if (nullptr != m_pInst)
			{
				delete m_pInst;
				m_pInst = nullptr;
			}
		}



	public:
		CIDManager& idMag() { return *m_pIDMag; }
		void setIDMag(CIDManager* pIdMag)
		{ if((pIdMag != nullptr)&&(m_pIDMag == nullptr))  m_pIDMag = pIdMag; }

	private:
		static CIDManagerAgent* m_pInst;
		CIDManager* m_pIDMag;
	};


}


#endif // !_FW_IDMANAGER_AGENT_
