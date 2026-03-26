/*

CDeviceAgent


Author: Zhen Yi

Created Date: Feb. 28, 2024

Version: 0.2.0 Alpha

*/


#ifndef _DEVICE_AGENT_
#define _DEVICE_AGENT_

#include"IInputDevice.h"


namespace FW
{

	class CInputDecAgent
	{
	public:
		CInputDecAgent();
		virtual ~CInputDecAgent();


		static CInputDecAgent& Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CInputDecAgent;
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


		IInputDevice* IIDec() { return m_pIIDec; }
		void setIIDec(IInputDevice* pIIDec) { m_pIIDec = pIIDec; }


	private:
		static CInputDecAgent* m_pInst;
		IInputDevice* m_pIIDec;
	};


}




#endif // !_DEVICE_AGENT_
