/*

CRenderManager


Author: Zhen Yi
Created Date: Feb. 05, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_RENDER_MANAGER_
#define _FW_RENDER_MANAGER_


#include<vector>
#include<map>
#include<list>
#include"IRenderManager.h"
#include"BaseData.h"


namespace FW
{
	class CRender;
	class CRenderUnitGroup;
	class CSpaceTime;
	class COffScreen;
	class CFinalSpaceTime;
	class CRenderManager : public IRenderManager
	{
	private:
		typedef std::vector<CRender*> VTRENDER;
		typedef VTRENDER::iterator VTRENDER_ITER;

		typedef std::list<CRenderUnitGroup*> LTRNDGP;
		typedef LTRNDGP::iterator LTRNDGP_ITER;

		typedef std::map<FDWORD, CSpaceTime*> MAPST;
		typedef MAPST::iterator MAPST_ITER;

		typedef std::vector<COffScreen*> VTOSCR;
		typedef VTOSCR::iterator VTOSCR_ITER;

		typedef enum { OFFSCR_COUNT = 8 } EBOUND;
	public:
		CRenderManager();
		virtual ~CRenderManager();


	//derivate from IRenderManager
	public:
		virtual bool Initialize(int widthWnd, int heightWnd);
		virtual void AddRender(FDWORD idSpaceTime, CRender* pRender);
		virtual void Update(CScene* pCurrentScene);
		virtual void ShowAssistFrame(bool sw);

	private:
		CSpaceTime* SearchSpaceTime(FDWORD id)
		{
			MAPST_ITER iter = m_mapSpaceTime.find(id); if (iter != m_mapSpaceTime.end()) { return iter->second; }
			return 0;
		}

		void DestroyAllOffScreen();

		void Destroy();
		void Clear();
		CRenderUnitGroup* FindRenderUnitGroup(int order);
		void InsertRenderUnitGroup(CRenderUnitGroup* pRndUtGp);


	private:
		//sort by order increasing
		LTRNDGP m_lstRenderUtGroup;

		MAPST m_mapSpaceTime;
		VTOSCR m_vtOffScreen;

		CFinalSpaceTime* m_pFinalSpaceTime;
		COffScreen* m_pFinalScreen;

		bool m_bShowAssistFrame;
	};
}



#endif // !_FW_RENDER_MANAGER_


