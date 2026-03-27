
/*

CFileInstance

Author:  Zhen Yi

Version: 0.2.0 Alpha



*/

#ifndef _FW_FILE_INSTANCE_
#define	_FW_FILE_INSTANCE_

#include<string>


namespace FW
{
	class CFileInstance
	{
	public:
		enum ESOURCE{NONE, INVALID, WAITING, READY};

	public:
		CFileInstance();
		virtual ~CFileInstance();

		ESOURCE getState() { return m_eSourceState; }

		
		virtual ESOURCE Check() = 0;
		bool isReadyForRead(){ return m_eSourceState == ESOURCE::READY; }

		virtual bool Open(const char* pszFileName) = 0;
		virtual void Close() = 0;

		virtual bool isEmpty() = 0;
		virtual bool isEnd() = 0;
		virtual const char* getCurrentLine() = 0;
		virtual bool moveToNextLine() = 0;
		virtual bool moveToHead() = 0;
		virtual bool moveToEnd() = 0;

	protected:
		ESOURCE m_eSourceState;
		std::string m_strFileName;
	};

}


#endif