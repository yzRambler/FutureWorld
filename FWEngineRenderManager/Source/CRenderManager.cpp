#include"CRenderManager.h"
#include"CRender.h"
#include"CCamera.h"
#include"CDirectLight.h"
#include"CScene.h"
#include"CRenderUnitGroup.h"
#include"CRenderUnit.h"
#include"CMesh.h"
#include"CMaterial.h"
#include"CSpaceTime.h"
#include"COffScreen.h"
#include"CFinalSpaceTime.h"

#ifdef _WND_OPENGL_PLATFORM_

////#include<vld.h>

#endif // _WND_OPENGL_PLATFORM_




#define DEFAULT_OPACITY_ORDER   100
#define DEFAULT_TRANSPARENT_ORDER   500



using namespace FW;


static IRenderManager* g_RenderMag = nullptr;


/*
#ifdef _WND_OPENGL_PLATFORM_
extern "C" __declspec(dllexport) IRenderManager* CreateRenderManager()
#else
extern "C" IRenderManager* __cdecl CreateRenderManager()
#endif // _WND_OPENGL_PLATFORM_
{
	if (0 == g_RenderMag)
	{
		g_RenderMag = new CRenderManager();
	}

	return g_RenderMag;
}
*/

#ifdef _WND_OPENGL_PLATFORM_

extern "C" DLLRNAPI IRenderManager* CreateRenderManager()
{
	if (nullptr == g_RenderMag)
	{
		g_RenderMag = new CRenderManager();
	}

	return g_RenderMag;
}


extern "C" DLLRNAPI void ReleaseRenderManager()
{
	if (nullptr != g_RenderMag)
	{
		delete g_RenderMag;
		g_RenderMag = nullptr;
	}
}


#else

extern "C" IRenderManager* __cdecl CreateRenderManager()
{
	if (nullptr == g_RenderMag)
	{
		g_RenderMag = new CRenderManager();
	}

	return g_RenderMag;
}


extern "C" void ReleaseRenderManager()
{
	if (nullptr != g_RenderMag)
	{
		delete g_RenderMag;
		g_RenderMag = nullptr;
	}
}

#endif




CRenderManager::CRenderManager() : 
	m_bShowAssistFrame(false), m_pFinalScreen(0), m_pFinalSpaceTime(0)
{
	//m_vtRenders.clear();
	m_lstRenderUtGroup.clear();

	m_mapSpaceTime.clear();
	m_vtOffScreen.clear();
}




CRenderManager::~CRenderManager()
{
	Destroy();
}




bool CRenderManager::Initialize(int widthWnd, int heightWnd)
{
	COffScreen* pOffScr = 0;
	for (int i = 0; i < EBOUND::OFFSCR_COUNT; i++)
	{
		pOffScr = new COffScreen;
		if (!pOffScr->Create(i, widthWnd, heightWnd))
		{
			delete pOffScr;
			DestroyAllOffScreen();

			return false;
		}

		pOffScr->Bind();

		m_vtOffScreen.push_back(pOffScr);
	}


	m_pFinalScreen = new COffScreen();
	if (!m_pFinalScreen->Create(EBOUND::OFFSCR_COUNT + 1, widthWnd, heightWnd))
	{
		return false;
	}


	//Require to create render tree.
	m_pFinalSpaceTime = new CFinalSpaceTime;
	if (!m_pFinalSpaceTime->Create(widthWnd, heightWnd, m_vtOffScreen[0]->textureBuffer(), m_vtOffScreen[1]->textureBuffer()))
	{
		delete m_pFinalScreen;
		m_pFinalScreen = nullptr;

		delete m_pFinalSpaceTime;
		m_pFinalSpaceTime = nullptr;

		return false;
	}


	return true;
}


void CRenderManager::DestroyAllOffScreen()
{
	for (VTOSCR_ITER iter = m_vtOffScreen.begin(); iter != m_vtOffScreen.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete* iter;
		}
	}

	m_vtOffScreen.clear();
}




void CRenderManager::Update(CScene* pCurrentScene)
{
	if ((nullptr == m_pFinalScreen) || (nullptr == m_pFinalSpaceTime))
	{
		return;
	}


	if (nullptr == pCurrentScene)
	{
		//Clean the screen...

		CScreen* pSC = m_vtOffScreen[0];
		if (pSC->Bind())
		{
			//glClearColor(0, 1, 0, 1);
			glClearDepth(0);
		}

		//pSC = m_vtOffScreen[1];
		//if (pSC->Bind())
		//{
		//	//glClearColor(0, 1, 0, 1);
		//	glClearDepth(0);
		//}

		if (m_pFinalScreen->Bind())
		{
			m_pFinalScreen->OutputIntoScreen();
			m_pFinalSpaceTime->Update();
		}

		return;
	}
	else
	{
		glClearDepth(1);
	}


	for (MAPST_ITER iter = m_mapSpaceTime.begin(); iter != m_mapSpaceTime.end(); ++iter)
	{
		iter->second->Grouping();
	}


	CCamera* pCamera = 0;
	for (int i = 0; i < pCurrentScene->countCamera(); i++)
	{
		pCamera = pCurrentScene->camera(i);
		if (0 == pCamera)
		{
			continue;
		}

		//bind screen
		if ((pCamera->screenID() < 0) || (pCamera->screenID() >= m_vtOffScreen.size()))
		{
			continue;
		}

		//just test
		int idScrn = pCamera->screenID();
		int idSpt = pCamera->targetSpaceTimeID();

		CScreen* pSC = m_vtOffScreen[pCamera->screenID()];
		if (pSC->Bind())
		{
			pCamera->PerformCommand();

			//if (i == 0)
			//{
			//	glClearDepth(1);
			//}

			//update & rendering
			MAPST_ITER iter = m_mapSpaceTime.find(pCamera->targetSpaceTimeID());
			if (iter != m_mapSpaceTime.end())
			{
				iter->second->Update(pCamera, (VTLIT*)pCurrentScene->lightArray(
					iter->second->idSpaceTime()));
			}
		}
		else
		{

		}
	}


	if (m_pFinalScreen->Bind())
	{

		m_pFinalScreen->OutputIntoScreen();
		m_pFinalSpaceTime->Update();
	}


	//clear all render unit
	for (MAPST_ITER iter = m_mapSpaceTime.begin(); iter != m_mapSpaceTime.end(); ++iter)
	{
		iter->second->Clear();
	}

}




void CRenderManager::ShowAssistFrame(bool sw)
{
	for (MAPST_ITER iter = m_mapSpaceTime.begin(); iter != m_mapSpaceTime.end(); ++iter)
	{
		if (iter->second != 0)
		{
			iter->second->ShowAssistFrame(sw);
		}
	}
}




void CRenderManager::AddRender(FDWORD idSpaceTime, CRender* pRender)
{
	CSpaceTime* pSpaceTime = SearchSpaceTime(idSpaceTime);
	if (0 == pSpaceTime)
	{
		pSpaceTime = new CSpaceTime();
		pSpaceTime->Create(idSpaceTime);
		m_mapSpaceTime[idSpaceTime] = pSpaceTime;
	}

	pSpaceTime->AddRender(pRender);
}



CRenderUnitGroup* CRenderManager::FindRenderUnitGroup(int order)
{
	if (order < 0)
	{
		return 0;
	}

	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if ((*iter)->order() == order)
		{
			return (*iter);
		}
	}

	return 0;
}


void CRenderManager::InsertRenderUnitGroup(CRenderUnitGroup* pRndUtGp)
{
	if (m_lstRenderUtGroup.empty())
	{
		m_lstRenderUtGroup.push_back(pRndUtGp);
		return;
	}

	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if (pRndUtGp->order() < (*iter)->order())
		{
			m_lstRenderUtGroup.push_front(pRndUtGp);
		}
	}
}




void CRenderManager::Destroy()
{
	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
		}
	}
	m_lstRenderUtGroup.clear();


	for (MAPST_ITER iter = m_mapSpaceTime.begin(); iter != m_mapSpaceTime.end(); ++iter)
	{
		if ((*iter).second != nullptr)
		{
			delete (*iter).second;
		}
	}
	m_mapSpaceTime.clear();


	for (VTOSCR_ITER iter = m_vtOffScreen.begin(); iter != m_vtOffScreen.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
		}
	}
	m_vtOffScreen.clear();


	if (nullptr != m_pFinalScreen)
	{
		delete m_pFinalScreen;
		m_pFinalScreen = nullptr;
	}

	if (nullptr != m_pFinalSpaceTime)
	{
		delete m_pFinalSpaceTime;
		m_pFinalSpaceTime = nullptr;
	}

}


void CRenderManager::Clear()
{
	CRenderUnitGroup* pRenderUnitGp = 0;
	for (LTRNDGP_ITER iter = m_lstRenderUtGroup.begin(); iter != m_lstRenderUtGroup.end(); ++iter)
	{
		if (!(*iter)->emptyRenderUnit())
		{
			(*iter)->CleanAll();
		}
	}
}