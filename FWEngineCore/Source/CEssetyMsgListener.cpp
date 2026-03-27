#include"CEssetyMsgListener.h"
#include"CEssety.h"

using namespace FW;

CEssetyMsgListener::CEssetyMsgListener(CEssety* pHost):CListener(pHost)
{
}

CEssetyMsgListener::~CEssetyMsgListener()
{
}


FDWORD CEssetyMsgListener::GetID()
{
	return m_pHost->id();
}


const char* CEssetyMsgListener::GetName()
{
	return m_pHost->name();
}



void CEssetyMsgListener::OnCallback(void* p)
{
	if (nullptr != m_pHost)
	{
		((CEssety*)m_pHost)->ProcessMsg(*(CMsgBase*)p);
	}

}