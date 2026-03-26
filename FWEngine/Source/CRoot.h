/*
CRoot

Author: Zhen Yi
Created Date: May 13, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_ROOT_
#define _FW_ROOT_

#include<vector>

#include "IEngine.h"
#include "IAspectManager.h"
#include "IDataResource.h"
#include "IRenderManager.h"
#include "IInputDevice.h"
#include "IUIManager.h"
#include "CListener.h"

namespace FW
{
	class CDevice;
	class CMaterialAspect;
	class CMaterial;
	class DLLEGAPI CRoot: public CListener
	{
	private:
		//RT_PRELOAD_PRE: reload precede stage; RT_PRELOAD_SUC: reload succeed stage.
		typedef enum  eStage {
			RT_START = 0, RT_DEFAULT_ASPECT, RT_DEFAULT_CONSTRUCT, RT_SCENEINI, RT_SCENECHECK,
			RT_PERFORMAN, RT_UNKNOWN
		}ESTAGE;

		typedef std::vector<CMaterialAspect*> VTMAPT;
		typedef VTMAPT::iterator VTMAPT_ITER;

		typedef std::vector<CMaterial*> VTMATL;
		typedef VTMATL::iterator VTMATL_ITER;


	public:
		CRoot();
		virtual ~CRoot();

		bool Initalize(int widthWnd, int heightWnd);
		bool Circle();
		bool LoadScene(const char* pszNamePathFile);
		bool UnloadScene(const char* pszNamePathFile);
		bool SetCurrentScene(const char* pszNamePathFile);
		bool RemoveScene(const char* pszNamePathFile);

	//Inherit from CListener
	public:
		virtual FDWORD GetID() { return 0; }
		virtual const char* GetName() { return "Root"; }
		virtual void OnCallback(void* p);


	//attribute
	public:

		bool InitCompleted() { return (m_eStage >= ESTAGE::RT_SCENEINI)&&(m_eStage != ESTAGE::RT_UNKNOWN); }
		void* WindowHandle();

	private:
		void DestroyAll();


	private:
		ESTAGE m_eStage;


		CDevice* m_pDevice;

		IInputDevice* m_pIInputDevice;

		IDataResource* m_pIDataRes;

		ISceneManager* m_pISceneDispatcher;

		IRenderManager* m_pIRenderMag;

		IUIManager* m_pUIMag;


		VTMAPT m_vtMatApt;
		VTMATL m_vtMatl;
	};

}


#endif // !_FW_ROOT_
