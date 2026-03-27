/*

FWEngineCoreExport.h


Author:  Zhen Yi

Created Date: Apr. 21,  2025

Version: 0.2.0 Alpha


*/

#ifndef _FW_ENGINECORE_EXPORT_
#define _FW_ENGINECORE_EXPORT_

#ifdef _WND_OPENGL_PLATFORM_
#ifdef _ENGINE_CORE_
#define DLLCOAPI __declspec(dllexport)
#else
#define DLLCOAPI __declspec(dllimport)
#endif
#else
#define DLLCOAPI
#endif




#endif // !_FW_ENGINECORE_EXPORT_
