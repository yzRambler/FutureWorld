/*

CommonShare.h


Author:  Zhen Yi

Created Date: Apr. 10, 2025

Version: 0.2.0 Alpha


*/


#ifndef _FW_ENGINESHARE_EXPORT_
#define _FW_ENGINESHARE_EXPORT_

#ifdef _WND_OPENGL_PLATFORM_
#ifdef _FW_ENGINE_SHARE_
#define DLLSHAPI __declspec(dllexport)
#else
#define DLLSHAPI __declspec(dllimport)
#endif
#else

#define DLLSHAPI
//extern "C" IDataResource* __cdecl CreateDataResource();
#endif



#endif // !_FW_ENGINE_SHARE_
