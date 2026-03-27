/*

IDataResource


Author:  Zhen Yi


Created Data: Apr. 8, 2025

Version: 0.2.0 Alpha


*/



#ifndef _FW_IDATARESOURCE_
#define _FW_IDATARESOURCE_

#include"CIDManager.h"
#include"CMsgCenter.h"
#include"FWEngineShareExport.h"
#include"IPrimatterManager.h"


namespace FW
{
	class CAspect;
	class DLLSHAPI IDataResource
	{
	public:
		virtual bool Initialize(int widthWnd, int heightWnd, CIDManager& rIDMag, 
			CMsgCenter& rMsgCet)= 0;

		virtual void Run() = 0;

		virtual CAspect* ApplyAspect(const char* pszName, const char* pszNameFile,
			EAPTTYPE typeApt) = 0;

		virtual EAPTSTATE InquireAspectState(CAspect* pPmtApt) = 0;

		virtual bool ReleaseAspect(const char* pszName, const char* pszNameFile, 
			EAPTTYPE typeApt) = 0;

		virtual EAPPPRRES ApplyPrimatter(IPrimatterAspect* pIPmtApt, IPrimatter** ppPamt) = 0;

		virtual EPMTSTATE InquirePrimatterState(IPrimatterAspect* pPmtApt) = 0;

		virtual CMaterial* TakeMatrial(const char* pszNameFile, const char* pszNameMat) = 0;

		//Matching with ApplyPrimatterMajor
		virtual int ReleasePrimatter(IPrimatter* pPmt) = 0;


		//If the primatter is released in the primatter center, the outside primatter pointer is hungling
		//this check can be used to prevent to refer a invalid primatter pointer.
		virtual bool CheckValidRes(FDWORD id) = 0;

		//For: Search and refer the specific primatter again if the current id check is faild which mean the 
		//primatter has released.
		virtual IPrimatter* RequirePrimatter(const char* pszName, const char* pszNameFile, EPMTTYPE typePmt)
			= 0;

		virtual IPrimatterManager* IPrimatterMag() = 0;
	};


#ifdef _WND_OPENGL_PLATFORM_

	extern "C" DLLSHAPI IDataResource* CreateDataResource();
	extern "C" DLLSHAPI void ReleaseDataResource();


#else

	extern "C" IDataResource* __cdecl CreateDataResource();
	extern "C" void __cdecl ReleaseDataResource();

#endif


}



#endif // !_FW_IDATARESOURCE_
