/*

FWIOSystemExport


Author:  Zhen Yi


Created Date: Aug. 22, 2025


Version: 0.2.0 Alpha


*/



#ifndef _FW_IOSYSTEM_EXPORT_
#define _FW_IOSYSTEM_EXPORT_


#ifdef _WND_OPENGL_PLATFORM_
#ifdef _IO_SYSTEM_
#define DLLIOAPI __declspec(dllexport)
#else
#define DLLIOAPI __declspec(dllimport)
#endif
#else
#define DLLIOAPI
#endif



#endif // !_FW_IOSYSTEM_EXPORT
