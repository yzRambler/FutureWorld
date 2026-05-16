/*

FWFileManagerExport.h


Author:  Zhen Yi (взеђ)

Create Date:  Mar. 2026

Version: 0.2.1 Alpha

*/


#ifndef _FW_FILEMANAGER_EXPORT_
#define _FW_FILEMANAGER_EXPORT_


#ifdef _WND_OPENGL_PLATFORM_
#ifdef _FILE_MANAGER_
#define DLLFMAPI __declspec(dllexport)
#else
#define DLLFMAPI __declspec(dllimport)
#endif
#else
#define DLLFMAPI
#endif



#endif // !_FW_FILEMANAGER_EXPORT_

