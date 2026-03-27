/*

IRenderManager


Author:  Zhen Yi -- взеђ

Created Date: July 4, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_IRENDER_MANAGER_
#define _FW_IRENDER_MANAGER_

#include"BaseData.h"
#include"FWEngineRenderManagerExport.h"


namespace FW
{
	class CScene;
	class CRender;
	class CTexture;
	class IRenderManager
	{
	public:
		virtual bool Initialize(int widthWnd, int heightWnd) = 0;
		virtual void AddRender(FDWORD idSpaceTime, CRender* pRender) = 0;
		virtual void Update(CScene* pCurrentScene) = 0;
		virtual void ShowAssistFrame(bool sw) = 0;
	};


#ifdef _WND_OPENGL_PLATFORM_

	extern "C" DLLRNAPI IRenderManager* CreateRenderManager();
	extern "C" DLLRNAPI void ReleaseRenderManager();


#else

	extern "C" IRenderManager* __cdecl CreateRenderManager();
	extern "C" void ReleaseRenderManager();

#endif
	
}




#endif // !_FW_IRENDER_MANAGER_
