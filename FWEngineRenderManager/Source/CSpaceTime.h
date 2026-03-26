/*

CSpaceTime


Author: Zhen Yi


Created Date:  Nov. 9, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SPACETIME_
#define _FW_SPACETIME_

#include<vector>
#include<list>
#include"RenderSystemCommon.h"
#include"EngineCoreCommon.h"
#include"CBase.h"

namespace FW
{
	class CRender;
	class CRenderUnitGroup;
	class CCamera;
	class CLight;
	class CSpaceTime : public CBase
	{
	private:
		typedef std::vector<CRender*> VTRENDER;
		typedef VTRENDER::iterator VTRENDER_ITER;

		typedef std::list<CRenderUnitGroup*> LTRNDGP;
		typedef LTRNDGP::iterator LTRNDGP_ITER;

	public:
		CSpaceTime();
		virtual ~CSpaceTime();

		bool Create(int orderSpace, int orderTime);
		bool Create(FDWORD idSpaceTime);
		void AddRender(CRender* pRender) { m_vtRenders.push_back(pRender); }
		void Grouping();
		void Update(CCamera* pCamera, VTLIT* pLightArray);

		void ShowAssistFrame(bool sw) { m_bShowAssistFrame = sw; }
		void Clear();

	//attribute
	public:
		FDWORD idSpaceTime() { return m_dwSpaceTimeID; }


	private:
		void Create();
		CRenderUnitGroup* FindRenderUnitGroup(int order);
		void InsertRenderUnitGroup(CRenderUnitGroup* pRndUtGp);
		void ClearRenderUnitListEachGroup();


	//private:
	protected:
		VTRENDER m_vtRenders;

		//sort by order increasing
		LTRNDGP m_lstRenderUtGroup;
		CRenderUnitGroup* m_pDefaultOpacityGroup;

		//DWORD for space-time id ???
		FDWORD m_dwSpaceTimeID;

		int m_nSpaceOrder;
		int m_nTimeOrder;

		bool m_bShowAssistFrame;
	};
}




#endif // !_FW_SPACETIME_
