/*

IAspectManager


Author:   Zhen Yi

Created Date:  Mar. 2025

Version: 0.2.0 Alpha

*/

#include"CommonPrimatter.h"
#include"CAspect.h"
#include"FWEnginePrimatterManagerExport.h"


namespace FW
{

	class DLLPRAPI IAspectManager
	{
	public:
		virtual CAspect* ApplyAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt) = 0;

		virtual EAPTSTATE InquireAspectState(CAspect* pPmtApt) = 0;

		virtual bool ReleaseAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt) = 0;
		virtual bool Create() = 0;
		virtual bool Initialize(int widthWnd, int heightWnd) = 0;
	};


	/*
#ifdef _WND_OPENGL_PLATFORM_
#ifdef _PRIMATTER_MANAGER_
	extern "C" __declspec(dllexport) IAspectManager* CreateAspectManager();
#else
	extern "C" __declspec(dllimport) IAspectManager* CreateAspectManager();
#endif
#else
	extern "C" IAspectManager* __cdecl CreateAspectManager();
#endif
	*/

#ifdef _WND_OPENGL_PLATFORM_
	extern "C" DLLPRAPI IAspectManager* CreateAspectManager();
	extern "C" DLLPRAPI void ReleaseAspectManager();

#else
	extern "C" IAspectManager* __cdecl CreateAspectManager();
	extern "C" void __cdecl ReleaseAspectManager();
#endif

}