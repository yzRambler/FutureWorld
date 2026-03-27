/*
IEngine.h

Author: Zhen Yi
Created Date: May 13, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_INTERFACE_ENGINE_
#define _FW_INTERFACE_ENGINE_


#include"FWEngineExport.h"
#include"CommonPrimatter.h"
#include"CommonUI.h"
#include"ISceneManager.h"


namespace FW
{
	class CUI;
	class CCamera;
	class CEssety;
	class CRender;
	class CLight;
	class CSceneNode;
	class DLLEGAPI IEngine
	{
	// Property
	public:
		virtual bool isStartUp() = 0;
		virtual void* getWindowHandle() = 0;

	// Function
	public:
		virtual bool Initalize(int widthWnd, int heightWnd) = 0;
		virtual void Run() = 0;

		virtual bool LoadScene(const char* pszNamePathFile) = 0;

		/*
		* UnloadScene will destroy the CSceneAspect date from CPrimatterAspectCenter and all 
		  objects in the specific scene from CPrimatterCenter.
		*/
		virtual bool UnloadScene(const char* pszNamePathFile) = 0;

		/*
		* RemoveScene will destroy all objects in the specific scene from CPrimatterCenter.
		*/
		virtual bool RemoveScene(const char* pszNamePathFile) = 0;

		virtual bool SaveCurrentScene() = 0;

		virtual bool SetCurrentScene(const char* pszNamePathFile) = 0;

		virtual CScene* GetCurrentScene() = 0;

		virtual bool TransformFileFromFBX2FWD(const char* pszNamePathFileSrc) = 0;


		virtual CRender* CreateModel(CSceneNode* pParent, Vector3& pos, Vector3& forward,
			Vector3& up, const char* pszNameComesh, const char* pszNameFile) = 0;

		virtual CRender* CreateModel(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, const char* pszNameModelFile) = 0;

		virtual CCamera* CreateCamera(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, ECAMERATYPE typeCam) = 0;

		virtual CCamera* CreateCamera(CEssety* pComHost, Vector3& forward, Vector3& up, 
			ECAMERATYPE typeCam) = 0;

		virtual CLight* CreateLight(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, ELITTYPE typeLit) = 0;

		virtual CLight* CreateLight(CEssety* pComHost, Vector3& forward, Vector3& up, 
			ELITTYPE typeLit) = 0;

		virtual CUI* CreateUI(EUITYPE type, const char* pszName, float ltx, float lty, float w, 
			float h) = 0;
		
	};

#ifdef _WND_OPENGL_PLATFORM_

	extern "C" DLLEGAPI IEngine* CreateEngine();
	extern "C" DLLEGAPI void ReleaseEngine();

#else

	extern "C" IEngine* __cdecl CreateEngine();
	extern "C" void ReleaseEngine();

#endif


}


#endif // !_FW_INTERFACE_ENGINE_
