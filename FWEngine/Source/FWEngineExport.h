/*

FWEngineExport.h


Author:  Zhen Yi


Created Date: Aug. 22, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_ENGINE_EXPORT_
#define _FW_ENGINE_EXPORT_

#ifdef _WND_OPENGL_PLATFORM_
#ifdef _FW_ENGINE_
#define DLLEGAPI __declspec(dllexport)
#else
#define DLLEGAPI __declspec(dllimport)
#endif
#else
#define DLLEGAPI
#endif




#endif // !_FW_ENGINE_EXPORT_
