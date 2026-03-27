
/*

FWEngineRenderManagerExport.h


Author:  Zhen Yi

Version: 0.2.0 Alpha


*/


#ifndef _FW_RNEDERMANAGER_EXPORT_
#define _FW_RENDERMANAGER_EXPORT_


#ifdef _WND_OPENGL_PLATFORM_
#ifdef _RENDER_MANAGER_
#define DLLRNAPI __declspec(dllexport)
#else
#define DLLRNAPI __declspec(dllimport)
#endif
#else

#define DLLRNAPI

#endif





#endif // !_FW_RNEDERMANAGER_EXPORT_
