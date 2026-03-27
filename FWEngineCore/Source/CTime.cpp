
#ifdef _WND_OPENGL_PLATFORM_
#include<time.h>
#include<iostream>
#else
#include<emscripten/emscripten.h>
#endif

#include"CTime.h"




using namespace FW;

CTime* CTime::m_pInstance = 0;

CTime::CTime() :m_lStart(0), m_lDltTime(0), m_lCurrent(0), m_lBlockTestCount(0){}

CTime::~CTime(){}

void CTime::Update()
{
#ifdef _WND_OPENGL_PLATFORM_
			m_lCurrent = clock();
#else
			//m_lDltTime = 30;
			emscripten_get_main_loop_timing(0, &m_lCurrent);
			//m_lStart = 0.0f;
#endif // _WINDOWS_OPERATION_SYS_

			m_lDltTime = m_lCurrent - m_lStart;
			m_lStart = m_lCurrent;
		
}

long CTime::getDltTime(bool log /*= false*/)
{
	if (log)
	{
#ifdef _WND_OPENGL_PLATFORM_

		std::clog << "dltTime  =  " << m_lDltTime << std::endl;

#endif // _WND_OPENGL_PLATFORM_

	}

	return m_lDltTime;
}


void CTime::BlockTestBegin()
{
#ifdef _WND_OPENGL_PLATFORM_

	m_lBlockTestCount = clock();
	//std::clog << "BlockTest Begin" << std::endl;

#endif // _WND_OPENGL_PLATFORM_
}


long CTime::BlockTestInterrupt(bool log /*= false*/)
{
	
	long dt = 0;

#ifdef _WND_OPENGL_PLATFORM_

    dt = clock() - m_lBlockTestCount;
    
#endif

	if (log)
	{
#ifdef _WND_OPENGL_PLATFORM_

		std::clog << "BlockTestInterrupt dltTime = " << dt << std::endl;

#endif // _WND_OPENGL_PLATFORM_
	}

	//m_lBlockTestCount = ct;

	return dt;
}


long CTime::BlockTestInterrupt(const char* pszInform, bool log /*= false*/)
{
	if (0 == pszInform)
	{
		return 0;
	}

	long dt = 0;

#ifdef _WND_OPENGL_PLATFORM_

	dt = clock() - m_lBlockTestCount;

#endif

	if (log)
	{
#ifdef _WND_OPENGL_PLATFORM_

		std::clog << pszInform << "BlockTestInterrupt dltTime = " << dt << std::endl;

#endif // _WND_OPENGL_PLATFORM_
	}

	//m_lBlockTestCount = ct;

	return dt;
}