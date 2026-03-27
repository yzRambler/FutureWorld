/*
CFileManager

Author: Zhen Yi
Created Date: May 08, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_FILEMANAGER_
#define _FW_FILEMANAGER_

#include<memory>
#include<vector>
#include<list>
#include"CPlatform.h"
#include"CICTarget.h"
#include"FWEnginePrimatterManagerExport.h"

namespace FW
{
	class CFile;
	class CFileDescribe;
	class CPrimatterDescribe;
	class CFileOpListener;
	class DLLPRAPI CFileManager : public CICTarget
	{
	private:
		typedef std::vector<CFile*> VTFILE;
		typedef VTFILE::iterator VTFILE_ITER;

		typedef std::list<CFile*> LSFILE;
		typedef LSFILE::iterator LSFILE_ITER;

	//Inheriate from CICTarget
	public:
		virtual bool RegisterLst(CListener* pLsn);
		virtual void UnregisterLst(CListener* pLsn);
		virtual void Update();


	public:
		CFileManager();
		virtual ~CFileManager();

		bool Create();
		void Destroy();
		void HandlePrimatterApply(CPrimatterDescribe* pPmtDesc);
		void HandleFileApply(CFileDescribe* pFileDesc);

		CFile* SearchFinishedFileQueue(const char* pszNamePathFile);
		CFile* SearchRequestFilesQueue(const char* pszNamePathFile);



	public:
		static CFileManager& Instance() 
		{
			if (nullptr == m_pInstance) 
			{ m_pInstance = new CFileManager; m_pInstance->Create(); } return *m_pInstance;
		}


		static void Release()
		{
			if (nullptr != m_pInstance)
			{
				m_pInstance->Destroy();

				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}


	private:
		void Monitor();
		void EraseFromRequestQueue(CFile* pFile);
		void DriveListener(CFile* pFile);


	private:
		static CFileManager* m_pInstance;

		LSFILE m_lsRequest;
		LSFILE m_lsFinished;
		
		CFile* m_pCurrentFile;

		CPlatform* m_pPlatform;


	};


}


#endif // !_FW_FILEMANAGER_
