/*

IUIManager

Author: Zhen Yi --- взеђ

Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_IUI_MANAGER_
#define _FW_IUI_MANAGER_

#include"ISceneManager.h"
//#include"IPrimatterManager.h"
#include"IDataResource.h"
#include"CMsgCenter.h"
#include"CIDManager.h"
#include"CUI.h"
#include"FWUIExport.h"



namespace FW
{
	
	class DLLUIAPI IUIManager
	{
	public:
		virtual bool Initialize(ISceneManager* pISceneMag, CMsgCenter* pMsgCenter,
			CIDManager* pIDMag) = 0;


		virtual CUI* CreateUI(EUITYPE type, const char* pszName, const char* pszNameFileMatl,
			const char* pszNameMatl, float ltx, float lty, float w, float h, 
			CConstruct* pHost = nullptr) = 0;

		virtual void Update(long lDltTime) = 0;

	};


#ifdef _WND_OPENGL_PLATFORM_
	extern "C" DLLUIAPI IUIManager* CreateUIManager();
	extern "C" DLLUIAPI void ReleaseUIManager();
#else
	extern "C" IUIManager* __cdecl CreateUIManager();
	extern "C" void ReleaseUIManager();
#endif


}


#endif // !_FW_IUI_MANAGER_
