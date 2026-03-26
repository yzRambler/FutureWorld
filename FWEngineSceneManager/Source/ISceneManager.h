/*

ISceneManager


Author:  Zhen Yi

Created Date: July 4, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_ISCENE_MANAGER_
#define _FW_ISCENE_MANAGER_


#include"CIDManager.h"
#include"FWEngineSceneManagerExport.h"

namespace FW
{
	class CScene;
	class IRenderManager;
	class ISceneManager
	{
	public:

		virtual bool Initalize(CIDManager* pIDMag) = 0;
		virtual bool LoadScene(const char* pszNamePathFile) = 0;
		virtual bool UnloadScene(const char* pszNamePathFile) = 0;

		virtual void Update(float ratioWH, IRenderManager* pRenderMag) = 0;
		virtual void CheckState() = 0;


		virtual bool SaveCurrentScene() = 0;
		virtual bool SetCurrentScene(const char* pszNamePathFile) = 0;
		virtual CScene* GetCurrentScene() = 0;

		virtual bool AllReady() = 0;
		virtual bool CreateUITree() = 0;
		virtual bool InitializeUITree() = 0;
	};



#ifdef _WND_OPENGL_PLATFORM_
	
	extern "C" DLLSEAPI  ISceneManager* CreateSceneManager();
	extern "C" DLLSEAPI void ReleaseSceneManager();

#else

	extern "C" ISceneManager* __cdecl CreateSceneManager();
	extern "C" void __cdecl ReleaseSceneManager();

#endif // _WND_OPENGL_PLATFORM_


}


#endif // !_FW_ISCENE_MANAGER_
