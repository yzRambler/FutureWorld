/*

CEngine


Author:  Zhen Yi

Created Date: Apr. 24, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_ENGINE_OBJ_
#define _FW_ENGINE_OBJ_


#include"IEngine.h"
#include"CRoot.h"
#include"CFileOpListener.h"


namespace FW
{
	
	class DLLEGAPI CEngine : public IEngine
	{
	public:
		CEngine();
		virtual ~CEngine();

		static CEngine* Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CEngine;
			}

			return m_pInst;
		}

		static void Release()
		{
			if (nullptr != m_pInst)
			{
				delete m_pInst;
				m_pInst = nullptr;
			}
		}



	//Property inherit from IEngine
	public:
		virtual bool isStartUp() { return m_pRoot->InitCompleted(); }
		virtual void* getWindowHandle() { if (0 == m_pRoot) { return 0; }  return m_pRoot->WindowHandle(); }

	//Fuction Inherit from IEngine
	public:
		virtual bool Initalize(int widthWnd, int heightWnd);
		virtual void Run();

		virtual bool LoadScene(const char* pszNamePathFile);
		virtual bool UnloadScene(const char* pszNamePathFile);
		virtual bool RemoveScene(const char* pszNamePathFile);

		virtual bool SaveCurrentScene();
		virtual bool SetCurrentScene(const char* pszNamePathFile);
		virtual CScene* GetCurrentScene();

		virtual bool TransformFileFromFBX2FWD(const char* pszNamePathFileSrc);

		virtual CRender* CreateModel(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, const char* pszNameComesh, const char* pszNameFile);

		virtual CRender* CreateModel(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, const char* pszNameModelFile);
		
		virtual CCamera* CreateCamera(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, ECAMERATYPE typeCam);

		virtual CCamera* CreateCamera(CEssety* pComHost, Vector3& forward, Vector3& up, 
			ECAMERATYPE typeCam);

		virtual CLight* CreateLight(CSceneNode* pParent, Vector3& pos, Vector3& forward, 
			Vector3& up, ELITTYPE typeLit);

		virtual CLight* CreateLight(CEssety* pComHost, Vector3& forward, Vector3& up, 
			ELITTYPE typeLit);

		virtual CUI* CreateUI(EUITYPE type, const char* pszName, float ltx, float lty, 
			float w, float h);


	private:
		void Destroy();


	private:
		static CEngine* m_pInst;

		CRoot* m_pRoot;
		CFileOpListener* m_pFileLsn;
	};
}





#endif // !_FW_ENGINE_
