/*
CSceneConfigFile


Author: Zhen Yi

Created Date: April 21. 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SCENECONFIG_FILE_
#define _FW_SCENECONFIG_FILE_

#include"CTextFile.h"

#ifdef _WND_OPENGL_PLATFORM_

#include"cJSON/cJSON.h"

#else

#include"cJSON.h"

#endif // !_WND_OPENGL_PLATFORM_


namespace FW
{
	class CAspect;
	class CSceneAspect;
	class CSceneNodeAspect;
	class CEssetyAspect;
	class CSpaceAspect;
	class CRenderAspect;
	class CComeshAspect;
	class CCameraAspect;
	class CLightAspect;
	class CMeshAspect;
	class CMaterialAspect;
	class CSkinAspect;
	class CAnimationGroupAspect;
	class CAnimationAspect;
	class CSkeletonAspect;
	class CComponentAspect;
	struct Vector3;
	class CSceneConfigFile : public CTextFile
	{
	public:
		CSceneConfigFile(const char* pszName);
		CSceneConfigFile(const char* pszName, const char* pszNameFile);
		virtual ~CSceneConfigFile();

	//derive from CTextFile
	public:
		virtual bool isSkippedLine(std::string& str) { return true; }
		virtual bool Parse();

	//attribute
	public:
		CSceneAspect* sceneAspect() { return m_pSceneApt; }

	private:
		bool CreateSceneAspect(cJSON* pJS);
		CSceneNodeAspect* CreateSceneNodeAspect(int orderTime, cJSON* pJS);
		CAspect* CreateConstructAspect(CAspect* pHostApt, cJSON* pJS);
		
		bool InitializeSpaceAspect(cJSON* pJS, CSpaceAspect& rSpaceApt);
		bool InitializeCameraAspect(cJSON* pJS, CCameraAspect* pCameraApt);
		bool InitializeLightAspect(cJSON* pJS, CLightAspect* pLightApt);
		bool InitializeEssetyAspect(cJSON* pJS, CEssetyAspect* pEssetyApt);

		bool CompleteSceneNodeSpace(CSceneNodeAspect* pSceneNodeApt);

		Vector3 CreateVector3(cJSON* pJS);

		CComponentAspect* CreateEssetyComponentAspect(cJSON* pJS, CEssetyAspect* pComHost);

		CCameraAspect* CreateCameraAspectInCom(cJSON* pJS, CEssetyAspect* pComHost);
		CLightAspect* CreateLightAspectInCom(cJSON* pJS, CEssetyAspect* pComHost);

		CRenderAspect* CreateRenderAspect(cJSON* pJS, CEssetyAspect* pComHost);
		CRenderAspect* CreateRenderAspectInCom(cJSON* pJS, CEssetyAspect* pComHost);
		CMeshAspect* CreateMeshAspect(cJSON* pJS, CComeshAspect* pHost);

		CMaterialAspect* CreateMaterialAspect(cJSON* pJS);
		CSkinAspect* CreateSkinAspect(cJSON* pJS, CMeshAspect* pHost);

		CAnimationGroupAspect* CreateAnimationGroupAspect(cJSON* pJS, CEssetyAspect* pComHost);
		CAnimationGroupAspect* CreateAnimationGroupAspectInCom(cJSON* pJS, CEssetyAspect* pComHost);
		CAnimationAspect* CreateAnimationAspect(cJSON* pJS);
		CSkeletonAspect* CreateSkeletonAspect(cJSON* pJS);

		void Destroy();

	private:
		cJSON* m_pJSSoruce;
		CSceneAspect* m_pSceneApt;
	};
}


#endif // !_FW_SCENECONFIG_FILE_
