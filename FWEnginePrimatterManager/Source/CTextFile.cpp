#include "CTextFile.h"
#include"CPrimatterCenter.h"

//#include"CFileInstance.h"
//#include<string>
//
//
//
//#ifndef _WND_OPENGL_PLATFORM_
//#define _DEBUG_OBJFILE_READ_FROMWEB_
//#include<emscripten.h>
//#include "CWebFile.h"
//
//#else
//#define _DEBUG_OBJFILE_READ_
//#endif

using namespace FW;
using namespace std;


CTextFile::CTextFile(const char* pszName) :CFile(pszName), m_pWork(0)
{
	m_vtContent.clear();
}

CTextFile::CTextFile(const char* pszName, const char* pszNameFile) : CFile(pszName, pszNameFile), m_pWork(0)
{
}

CTextFile::~CTextFile()
{
	Destory();
}


bool CTextFile::GetNextWholeLine()
{
	if ((m_pWork - m_pBuffer) >= m_nSize)
	{
		return false;
	}

	m_strCurrentLine.clear();
	//m_strTmp.clear();
	//circle condition:1. have not encountered carriage return-line feed translation. ("\n")
	//                 2. have not encountered the end of file. (Ctrl+Z == "^Z") 

	while (m_pWork - m_pBuffer < m_nSize)
	{
		//char c;
		m_strCurrentLine.push_back(*m_pWork);


		if (m_strCurrentLine.size() >= 2)
		{
			if ((m_strCurrentLine[m_strCurrentLine.size() - 2] == '\r') 
				&& (m_strCurrentLine[m_strCurrentLine.size() - 1] == '\n'))
			{
				m_pWork++;
				break;
			}
			else if (m_strCurrentLine.substr(m_strCurrentLine.size() - 2, 2).compare("^Z") == 0)
			{
				break;
			}
		}

		m_pWork++;

	}

	return true;
}

bool CTextFile::Parse()
{
	if ((m_pBuffer == 0) || (m_nSize <= 0))
	{
		return false;
	}

	m_pWork = m_pBuffer;

	string strTmp;
	while (GetNextWholeLine())
	{
		strTmp = m_strCurrentLine;

		if ((!isBlankLine(strTmp)) && (!isSkippedLine(strTmp)))
		{
			char* pString = new char[strTmp.length() + 1];
			memcpy(pString, strTmp.c_str(), strTmp.length());
			pString[strTmp.length()] = '\0';
			m_vtContent.push_back(pString);


			//#ifdef _DEBUG_OBJFILE_READ_FROMWEB_ 
			//
			//			EM_ASM({
			//				console.log("current row len :" + UTF8ToString($0));
			//			},pString); 
			//			
			//#endif

		}
	}

	return true;
}


void CTextFile::Destory()
{
	for (VSITER iter = m_vtContent.begin(); iter != m_vtContent.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete[] *iter;
		}
	}

	m_vtContent.clear();
}




