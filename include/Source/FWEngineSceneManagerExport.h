
/*

FWEngineSceneManagerExport.h


Author:  Zhen Yi

Created Date: Aug. 22, 2025

Version: 0.2.0 Alpha


*/




#ifndef _FW_SCENEMANAGER_EXPORT_
#define _FW_SCENEMANAGER_EXPORT_

#ifdef _WND_OPENGL_PLATFORM_
#ifdef _SCENE_MANAGER_
#define DLLSEAPI __declspec(dllexport)
#else
#define DLLSEAPI __declspec(dllimport)
#endif
#else

#define DLLSEAPI

#endif




#endif // !_FW_SCENEMANAGER_EXPORT



