/*

FWEngineBaseExport.h


Author:  Zhen Yi (взеђ)

Create Date: May 6, 2026

Version 0.2.1 Alpha

*/


#ifndef _FW_ENGINEBASE_EXPORT_
#define _FW_ENGINEBASE_EXPORT_

#ifdef _WND_OPENGL_PLATFORM_
#ifdef _ENGINE_BASE_
#define DLLBSAPI __declspec(dllexport)
#else
#define DLLBSAPI __declspec(dllimport)
#endif
#else
#define DLLCOAPI
#endif




#endif // !_FW_ENGINEBASE_EXPORT_
