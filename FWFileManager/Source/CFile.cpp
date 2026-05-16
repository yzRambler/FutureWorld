#include"CFile.h"
#include"CListener.h"


using namespace FW;


CFile::CFile(const char* pszName /*, CListener* pLsn  = nullptr */) :CBase(pszName),
m_eFileState(EFSTATE::NONE),  m_eFileType(EFILETYPE::FI_UNKNOWN), m_pBuffer(0), m_nSize(0)/*,
m_pLsn(pLsn)*/
{
}

CFile::CFile(const char* pszName, const char* pszNamePathFile /*, CListener* pLsn  = nullptr */) :
	CBase(pszName), m_eFileState(EFSTATE::NONE), m_eFileType(EFILETYPE::FI_UNKNOWN), m_pBuffer(0), 
	m_nSize(0) /*, m_pLsn(pLsn)*/
{
	m_strNamePathFile.Set(pszNamePathFile);
}

CFile::~CFile()
{
	if (m_pBuffer != 0) 
	{ 
		delete[] m_pBuffer;
		m_pBuffer = 0;
	}  
	
	m_nSize = 0;
}


//void CFile::LoadFinish()
//{
//	if (nullptr == m_pLsn)
//	{
//		return;
//	}
//
//	m_pLsn->OnCallback(this);
//}

