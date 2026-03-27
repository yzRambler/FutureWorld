/*

CUIManager


Author:  Zhen Yi    взеђ

Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha

*/

#ifndef _FW_UIMANAGER_
#define _FW_UIMANAGER_

#include"IUIManager.h"
#include"MathLibrary.h"


namespace FW
{
	class CUIManager : public IUIManager
	{
		typedef struct {
			CUI* pUI;
			FDWORD id;
		}SUI;

		typedef std::vector<SUI*> VTUI;
		typedef VTUI::iterator VTUI_ITER;


	//Inherit from IUIManager
	public:
		virtual bool Initialize(ISceneManager* pISceneMag, CMsgCenter* pMsgCenter, 
			CIDManager* pIDMag);


		virtual CUI* CreateUI(EUITYPE type, const char* pszName, const char* pszNameFileMatl,
			const char* pszNameMatl, float ltx, float lty, float w, float h,
			CConstruct* pHost = nullptr);

		virtual void Update(long lDltTime);


	public:
		CUIManager();
		virtual ~CUIManager();


	//attribute
	public:
		static CUIManager& Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CUIManager;
				if (!m_pInst->Create())
				{
					delete m_pInst;
					m_pInst = nullptr;    //???
				}
			}

			return *m_pInst;
		}


		static void Release()
		{
			if (nullptr != m_pInst)
			{
				m_pInst->Destroy();

				delete m_pInst;
				m_pInst = nullptr;
			}
		}


	private:
		bool Create();
		void Destroy();

	private:
		static CUIManager* m_pInst;

		CScene* m_pCurScene;

		VTUI m_vtUI;


		float m_fUIStep;
		
	};

}








#endif // !_FW_UIMANAGER_
