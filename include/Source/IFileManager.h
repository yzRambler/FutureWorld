/*

IFileManaager


Author:  Zhen Yi (взеђ)

Create Date:  Mar. 2026

Version 0.2.1 Alpha

*/


#ifndef _FW_FILEMANAGER_INTERFACE_
#define _FW_FILEMANAGER_INTERFACE_

#include"FWFileManagerExport.h"


namespace FW
{
	class CFile;
	class CPrimatterDescribe;
	class CFileDescribe;
	class CListener;
	class CICTarget;

	class DLLFMAPI IFileManager
	{
	public:
		virtual bool RegisterLst(CListener* pLsn) = 0;
		virtual void UnregisterLst(CListener* pLsn) = 0;
		virtual void Update() = 0;

		virtual void HandlePrimatterApply(CPrimatterDescribe* pPmtDesc) = 0;
		virtual void HandleFileApply(CFileDescribe* pFileDesc) = 0;

		virtual CFile* SearchFinishedFileQueue(const char* pszNamePathFile) = 0; 
		virtual CFile* SearchRequestFilesQueue(const char* pszNamePathFile) = 0;

		virtual bool TransformFileFromFBX2FWD(const char* pszNameFilePathSrc) = 0;

		virtual bool Package(const char* pszNameFolder, const char* pszNamePackage) = 0;
		virtual bool Unpackage(const char* pszNamePath, const char* pszNamePackage) = 0;

		//Atrribute
	public:
		virtual CICTarget* targetIC() = 0;

	};


#ifdef _WND_OPENGL_PLATFORM_
	extern "C" DLLFMAPI IFileManager* CreateFileManager();
	extern "C" DLLFMAPI void ReleaseFileManager();

#else
	extern "C" IFileManager* __cdecl CreateFileManager();
	extern "C" void __cdecl ReleaseFileManager();
#endif

}







#endif // !_FW_FILEMANAGER_INTERFACE_
