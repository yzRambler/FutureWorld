/*


CTime

Author: Zhen Yi - взеђ

Version: 0.2.0 Alpha


*/



#ifndef _FW_TIME_
#define _FW_TIME_


#ifdef _WND_OPENGL_PLATFORM_

//#include"CommonWnd.h"
#include<time.h>

#endif // _WINDOWS_OPERATION_SYS_

#include"FWEngineCoreExport.h"


namespace FW
{
	class DLLCOAPI CTime
	{
	public:
		CTime();
		virtual ~CTime();

		static CTime& Instance()
		{
			if (0 == m_pInstance)
			{
				m_pInstance = new CTime();
				//	m_pInstance->Create();
			}

			return *m_pInstance;
		}

		void Update();

		//long getDltTime() { return m_lDltTime; }
		long getDltTime(bool log = false);
		long getCurrentTime() { return m_lCurrent; }

		void BlockTestBegin();
		long BlockTestInterrupt(bool log = false);
		long BlockTestInterrupt(const char* pszInform, bool log = false);

	private:
//		void Create();

	private:
		static CTime* m_pInstance;

		long m_lStart;
		long m_lDltTime;
		long m_lCurrent;

		long m_lBlockTestCount;

	};

}



#endif // !_FW_TIME_
