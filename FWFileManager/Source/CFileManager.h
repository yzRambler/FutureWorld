/*
CFileManager

Author: Zhen Yi (взеђ)
Create Date: May 08, 2021


Version 0.2.1 Alpha

*/

#ifndef _FW_FILEMANAGER_
#define _FW_FILEMANAGER_

#include<memory>
#include<vector>
#include<list>
#include"IFileManager.h"
#include"CPlatform.h"
#include"CICTarget.h"
#include"CFileOpListener.h"


namespace FW
{
	class CFile;
	class CFileDescribe;
	class CPrimatterDescribe;
	class CFileOpListener;

	class CFileManager : public IFileManager
	{
	private:
		typedef std::vector<CFile*> VTFILE;
		typedef VTFILE::iterator VTFILE_ITER;

		typedef std::list<CFile*> LSFILE;
		typedef LSFILE::iterator LSFILE_ITER;

	//Inheriate from IFileManager
	public:
		virtual bool RegisterLst(CListener* pLsn);
		virtual void UnregisterLst(CListener* pLsn);
		virtual void Update();

		virtual void HandlePrimatterApply(CPrimatterDescribe* pPmtDesc);
		virtual void HandleFileApply(CFileDescribe* pFileDesc);

		virtual CFile* SearchFinishedFileQueue(const char* pszNamePathFile);
		virtual CFile* SearchRequestFilesQueue(const char* pszNamePathFile);

		virtual bool TransformFileFromFBX2FWD(const char* pszNameFilePathSrc);

		virtual bool Package(const char* pszNameFolder, const char* pszNamePackage);
		virtual bool Unpackage(const char* pszNamePath, const char* pszNamePackage);



		virtual CICTarget* targetIC() { return m_pICTag; }


	public:
		CFileManager();
		virtual ~CFileManager();

		bool Create();
		void Destroy();


		//void ApplyFileWithListener(const char* pszNameFilePath, CFileOpListener* pFileOpLsn);


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
		CICTarget* m_pICTag;

		CFileOpListener* m_pFileLsn;

	};


}


#endif // !_FW_FILEMANAGER_
