/*

CDesribe


Author:    Zhen Yi

Created Date:  Apr.  2025

Version: 0.2.0 Alpha


*/

#ifndef _FW_FILEDESCRIBE_
#define _FW_FILEDESCRIBE_


#include<string>
#include"CommonPrimatter.h"
#include"CAspect.h"
#include"FWEnginePrimatterManagerExport.h"


namespace FW
{
	//class CListener;
	class DLLPRAPI CFileDescribe : public CBase
	{
	public:
		CFileDescribe(EFILETYPE fileType = EFILETYPE::FI_UNKNOWN) :m_typeFile(fileType){}

		virtual ~CFileDescribe() { /*m_pLsn = nullptr; */ }


		bool Initialize(const char* pszNamePathFile /*, CListener* pLsn = nullptr */ );


		//attribute
	public:
		EFILETYPE typeFile() { return m_typeFile; }
		virtual const char* namePathFile() { return m_strNamePathFile.Get(); }


	protected:
		EFILETYPE m_typeFile;
		CString m_strNamePathFile;
	};



	//CAspectDescirbe is a description of secene file or material file.
	class CAspectDescribe : public CFileDescribe
	{
	public:
		CAspectDescribe() {}
		virtual ~CAspectDescribe() {}

	    bool Initialize(const char* pNamePrimatterApt, const char* pNamePathFile);

	};


	//CPrimatterDescribe is a description of model file or texture file or shader file.
	class CPrimatterDescribe : public CFileDescribe
	{
	public:
		CPrimatterDescribe() :m_typePmt(EPMTTYPE::PR_UNKNOWN) {}
		virtual ~CPrimatterDescribe() {}

		bool Initialize(const char* pNamePrimatter, const char* pNamePathFile, EPMTTYPE typePmt);


	//attribute
	public:
		EPMTTYPE typePrimatter() { return m_typePmt; }


	private:
		EPMTTYPE m_typePmt;

	};
}



#endif
