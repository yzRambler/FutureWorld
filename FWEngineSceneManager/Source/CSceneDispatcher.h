/*
CSceneNode


Author: Zhen Yi
Created Date: Feb. 05, 2023

Version: 0.2.0 Alpha


*/

#ifndef _FW_SCENE_DISPATCHER_
#define _FW_SCENE_DISPATCHER_

#include<vector>
#include"IDataResource.h"
#include"ISceneManager.h"
#include"CString.h"

namespace FW
{
	class CSceneNode;
	class CSceneNodeAspect;
	class CUITreeAspect;
	class CSceneAspect;
	class CCamera;
	class CSceneDispatcher : public ISceneManager
	{
	private:
		typedef struct SScene
		{
			CString* pSceName;
			CString* pSceFullName;
			CScene* pScene;
			FDWORD  idScene;
			CSceneAspect* pSceneApt;
		}SScene;

		typedef std::vector<SScene*> VTSEN;
		typedef VTSEN::iterator VTSEN_ITER;


		//drivate from ISceneManager
	public:
	
		virtual bool Initalize(CIDManager* pIDMag);
		virtual bool LoadScene(const char* pszNamePathFile);
		virtual bool UnloadScene(const char* pszNamePathFile);
		
		virtual void Update(float ratioWH, IRenderManager* pRenderMag);
		
		virtual void CheckState();



		virtual bool SaveCurrentScene();
		virtual bool SetCurrentScene(const char* pszNamePathFile);

		virtual CScene* GetCurrentScene() { return (m_pCurScene == 0) ? 0 : m_pCurScene->pScene; }

		virtual bool AllReady();

		virtual bool CreateUITree();

		virtual bool InitializeUITree();

		
	public:
		CSceneDispatcher();
		virtual ~CSceneDispatcher();

		


	private:
		SScene* FindScene(const char* pszNamePathFile);
		SScene* FindSceneExcludeUninit(const char* pszNamePathFile);
		SScene* FindSceneAll(const char* pszNamePathFile);
		void DestroyCurrentScene();
		void ReleasePossession();

		CSceneNode* CreateUITreeRoot(CSceneNodeAspect* pSNodeApt, CSceneNode* pParentNode);
		CSceneNode* InitializeUINodes(CSceneNodeAspect* pSNodeApt, CSceneNode* pParentNode);


	private:
		VTSEN m_vtScene;
		SScene* m_pCurScene;
		CUITreeAspect* m_pUITreeApt;
		CSceneNode* m_pUITreeRoot;

		IDataResource* m_pIDataRes;


	};
}


#endif // !_FW_SCENE_DISPATCHER_

