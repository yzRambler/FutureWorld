/*


CUIFile


Author: Zhen Yi

Created Date: Feb. 17, 2026

Version: 0.2.0 Alpha

*/


#ifndef _FW_UIFILE_
#define _FW_UIFILE_


#include"CTextFile.h"

#ifdef _WND_OPENGL_PLATFORM_

#include"cJSON/cJSON.h"

#else

#include"cJSON.h"

#endif // _WND_OPENGL_PLATFORM_




namespace FW
{
	class CAspect;
	class CSceneNodeAspect;
	class CEssetyAspect;
	class CSpaceAspect;
	class CCameraAspect;
	class CUIAspect;
	class CMaterialAspect;
	class CComponentAspect;
	class CUITreeAspect;
	class CCommandAspect;
	struct Vector3;
	class CUIFile : public CTextFile
	{
	public:
		CUIFile(const char* pszName);
		CUIFile(const char* pszName, const char* pszNameFile);
		virtual ~CUIFile();

		//Derive from CTextFile
	public:
		virtual bool Parse();
		virtual bool isSkippedLine(std::string& str) { return true; }

	public:
		CUITreeAspect* sceneAspect() { return m_pUITreeApt; }

	private:
		bool CreateUITreeAspect(cJSON* pJS);
		CSceneNodeAspect* CreateSceneNodeAspect(int orderTime, cJSON* pJS);
		CAspect* CreateConstructAspect(CAspect* pHostApt, cJSON* pJS);

		bool InitializeSpaceAspect(cJSON* pJS, CSpaceAspect& rSpaceApt);
		bool InitializeCameraAspect(cJSON* pJS, CCameraAspect* pCameraApt);
		bool InitializeUIAspect(cJSON* pJS, CUIAspect* pUIApt);
		bool InitializeEssetyAspect(cJSON* pJS, CEssetyAspect* pEssetyApt);

		bool CompleteSceneNodeSpace(CSceneNodeAspect* pSceneNodeApt);

		Vector3 CreateVector3(cJSON* pJS);

		CComponentAspect* CreateEssetyComponentAspect(cJSON* pJS, CEssetyAspect* pComHost);

		CCameraAspect* CreateCameraAspectInCom(cJSON* pJS, CEssetyAspect* pComHost);
		CCommandAspect* CreateCommandAspect(cJSON* pJS);
		CUIAspect* CreateUIAspectInCom(cJSON* pJS, CEssetyAspect* pComHost);



		void Destroy();

	private:
		cJSON* m_pJSSource;
		CUITreeAspect* m_pUITreeApt;

	};
}







#endif // !_FW_UIFILE_
