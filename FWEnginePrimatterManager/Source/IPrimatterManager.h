/*
IPrimatterManager



Author:  Zhen Yi

Created Date: July 4, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_IPRIMATTER_MANAGER_
#define _FW_IPRIMATTER_MANAGER_

#include"CommonPrimatter.h"
#include"IRenderManager.h"
#include"CMsgCenter.h"
#include"CIDManager.h"
#include"FWEnginePrimatterManagerExport.h"

namespace FW
{
	class IPrimatterManager;

	class IPrimatter
	{
	public:
		virtual EPMTTYPE GetType() = 0;
	};


	class CConstruct;
	class IPrimatterAspect
	{
	public:
		virtual bool InitializeCorrelateConstructIF(IPrimatter** ppIPmt, 
			IPrimatterManager* pIPmtCent, CConstruct* pHostCst) = 0;

		virtual EPMTSTATE CheckCorrelateConstructIF(IPrimatter** ppIPmt, 
			IPrimatterManager* pIPmtCent) = 0;

		virtual EPMTTYPE TypeIF() = 0;
		virtual EAPTSTATE StateIF() = 0;
		virtual const char* Name() = 0;
		virtual const char* FullName() = 0;
	};


	class CMaterial;
	class DLLPRAPI IPrimatterManager
	{
	public:
		virtual bool Initialize(CMsgCenter* pMsgCenter, CIDManager* pIDMag) = 0;
		virtual void Run() = 0;
		virtual EAPPPRRES ApplyPrimatter(IPrimatterAspect* pPmtApt, IPrimatter** ppPamt, 
			CConstruct* pHostCst) = 0;

		virtual int ReleasePrimatter(IPrimatter* pPmt) = 0;
		

		virtual EPMTSTATE InquirePrimatterState(IPrimatterAspect* pPmtApt) = 0;
		virtual CMaterial* TakeMatrial(const char* pszNameFile, const char* pszNameMat) = 0;
	};


	class DLLPRAPI IPrimatterAspectManager
	{
	public:
		virtual IPrimatterAspect* ApplyPrimatterAspectIF(const char* pszName, 
			const char* pszNameFile, EPMTTYPE typeApt) = 0;

		virtual EAPTSTATE InquirePrimatterAspectStateIF(IPrimatterAspect* pPmtApt) = 0;
		
		virtual bool ReleasePrimatterAspectIF(IPrimatterAspect* pPmtApt) = 0;
		virtual bool ReleasePrimatterAspect(const char* pszName, const char* pszNameFile,
			EPMTTYPE typeApt) = 0;

		virtual bool CreateIF() = 0;
		virtual bool Initialize(int widthWnd, int heightWnd) = 0;
		
	};



#ifdef _WND_OPENGL_PLATFORM_
	extern "C" DLLPRAPI IPrimatterManager* CreatePrimatterManager();
	extern "C" DLLPRAPI void ReleasePrimatterManager();

#else
	extern "C" IPrimatterManager* __cdecl CreatePrimatterManager();
	extern "C" void __cdecl ReleasePrimatterManager();

#endif


}


#endif // !_FW_IPRIMATTER_MANAGER_
