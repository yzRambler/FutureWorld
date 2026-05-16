/*

CFileOpListener

Author:  Zhen Yi

Create Date:  Jul. 26, 2025

Version 0.2.1 Alpha

*/


#ifndef _FW_FILEOP_LISTENER_
#define _FW_FILEOP_LISTENER_

#include"CListener.h"
#include"FWFileManagerExport.h"


namespace FW
{
	class CFBXFile;
	class DLLFMAPI CFileOpListener : public CListener
	{
	//Inheriate from CListener
	public:
		virtual FDWORD GetID();
		virtual const char* GetName();
		virtual void OnCallback(void* p);

	public:
		CFileOpListener(CConstruct* pHost);
		CFileOpListener(const char* pszName, CConstruct* pHost);
		virtual ~CFileOpListener();

		bool Create(const char* pszNameFilePath);


	private:
		bool CreateFWDFile(const char* pszTargetNameFile, CFBXFile* pSrcFile);


	};


}





#endif // !_FW_FILEOP_LISTENER_
