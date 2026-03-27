
/*
CTextFile



Author: Zhen Yi
Created Date: Mar.30, 2021

Version: 0.2.0 Alpha

*/



#ifndef	_FW_TEXT_FILE_
#define _FW_TEXT_FILE_

#include"CFile.h"
#include<vector>
#include<string>

namespace FW
{

	class CTextFile :public CFile
	{
	protected:
		typedef std::vector<char*> VTSTR;
		typedef VTSTR::iterator VSITER;

	public:
		CTextFile(const char* pszName);
		CTextFile(const char* pszName, const char* pszNameFile);
		virtual ~CTextFile();

		//derive from CFile
		virtual bool Parse();

	protected:
		virtual bool isSkippedLine(std::string& str) = 0;
		bool isBlankLine(std::string& str)
		{
			return (str.empty()) || (str.find_first_not_of(' ') == str.npos) || ((str[0] == '\r') && (str[1] == '\n'));
		}

		bool GetNextWholeLine();


	private:
		void Destory();


	protected:
		VTSTR m_vtContent;

		std::string m_strCurrentLine;

		char* m_pWork;
	};


}


#endif