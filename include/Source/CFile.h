/*
CFile

Author: Zhen Yi (взеђ)
Date: May 08, 2021

Version 0.2.1 Alpha

*/


#ifndef _FW_FILE_
#define _FW_FILE_

#include<string>
#include"CBase.h"
#include"CommonPrimatter.h"
#include"FWFileManagerExport.h"

namespace FW
{
	//class CListener;
	class DLLFMAPI CFile : public CBase
	{
	public:
		typedef enum { NONE = 0, INVALID, WAITING_PROC, WAITING_DATA, COPY_SUC, PARSE_SUC } EFSTATE;

	public:
		CFile(const char* pszName /*, CListener* pLsn = nullptr */ );
		CFile(const char* pszName, const char* pszNamePathFile /*, CListener* pLsn = nullptr */ );
		virtual ~CFile();


		void SetBuffer(char* pBuffer, int size)
		{
			if ((size <= 0) || (pBuffer == 0))
			{
				return;
			}

			m_nSize = size;
			m_pBuffer = new char[m_nSize];
			memset(m_pBuffer, 0, m_nSize);
			memcpy(m_pBuffer, pBuffer, m_nSize);
		}

		char* GetBuffer() { return m_pBuffer; }


		virtual bool Parse() { return true; }

		//virtual bool Parse() = 0;
		//void LoadFinish();


	//attribute
	public:
		const char* nameFile() { return m_strNamePathFile.Get(); }
		void setNameFile(const char* pszNameFile) { m_strNamePathFile.Set(pszNameFile); }
		
		EFSTATE state() { return m_eFileState; }
		void setState(EFSTATE state) { m_eFileState = state; }

		EFILETYPE type() { return m_eFileType; }
		void setType(EFILETYPE type) { m_eFileType = type; }

		//void setListener(CListener* pLsn) { m_pLsn = pLsn; }


		bool processing() { return (m_eFileState == EFSTATE::WAITING_DATA) 
			|| (m_eFileState == EFSTATE::WAITING_PROC); }

		bool isReady() { return m_eFileState == EFSTATE::PARSE_SUC; }
		int size() { return m_nSize; }

	protected:
		//const char* m_pszNamePathFile;
		CString m_strNamePathFile;
		EFSTATE m_eFileState;
		EFILETYPE m_eFileType;

		//CListener* m_pLsn;

		char* m_pBuffer;
		int m_nSize;
	};
};


#endif