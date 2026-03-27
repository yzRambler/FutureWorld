/*

FWEnginePrimatterManagerExport.h


Author:  Zhen Yi

Created Date:  Apr. 20, 2025

Version: 0.2.0 Alpha


*/


#ifndef _FW_PRIMATTERMANAGER_EXPORT_
#define _FW_PRIMATTERMANAGER_EXPORT_


#ifdef _WND_OPENGL_PLATFORM_
#ifdef _PRIMATTER_MANAGER_
#define DLLPRAPI __declspec(dllexport)
#else
#define DLLPRAPI __declspec(dllimport)
#endif
#else

#define DLLPRAPI

#endif









#endif // !_FW_COMMON_PRIMATTERMANAGER_
