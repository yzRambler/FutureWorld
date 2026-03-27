/*

CShaderFile



Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_SHADER_FILE_
#define _FW_SHADER_FILE_

#include<vector>
#include"CTextFile.h"
#include"CommonPrimatter.h"

namespace FW
{
	class CShaderFile :public CTextFile
	{
	public:
		CShaderFile(const char* pszName);
		CShaderFile(const char* pszName, const char* pszNameFile);
		virtual ~CShaderFile();

		//derive from CFile
		virtual bool Parse();

	protected:
		virtual bool isSkippedLine(std::string& str) { return false; }

	//attribute
	public:
		//reserve
		char* buffer() { return &m_vtBuffer[0]; }
		int size() { return m_vtBuffer.size(); }
		ESHDTYPE typeShader() { return m_eType; }

	private:
		std::vector<char> m_vtBuffer;
		ESHDTYPE m_eType;
	};

}


#endif // !_FW_SHADER_FILE_
