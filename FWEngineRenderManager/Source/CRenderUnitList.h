/*
CRenderUnitList
      
	  For combining same material CRenderUnit objectes.
	  In principle, all CRenderUnit objectes share one material each CRenderUnitList.


Author:  Zhen Yi

Created Date:  June  6, 2023

Version: 0.2.0 Alpha

*/



#ifndef _FW_RENDERUNIT_LIST_
#define _FW_RENDERUNIT_LIST_

#include"EngineCoreCommon.h"
#include<list>


namespace FW
{
	class CMaterial;
	class CRenderUnit;
	class CCamera;
	class CRenderUnitList
	{
	private:
		typedef std::list<CRenderUnit*> LTRNDUT;
		typedef LTRNDUT::iterator LTRNDUT_ITER;

	public:
		CRenderUnitList();
		virtual ~CRenderUnitList();

		void AddRenderUnit(CRenderUnit* pRndUt) { m_lstRenderUt.push_back(pRndUt); }
		void UpdateCameraLightParameter(CCamera* pCam, VTLIT& vtLights);
		void Rendering();
		void Clean() { m_lstRenderUt.clear(); m_pMatlShare = 0; }

	//attribute
	public:
		CMaterial* material() { return m_pMatlShare; }
		void setMaterial(CMaterial* pMatl) { m_pMatlShare = pMatl; }

	private:

		//Share material for all CRenderUnit objectes in m_lstRenderUnit.
		CMaterial* m_pMatlShare;

		LTRNDUT m_lstRenderUt;
	};
}

#endif // !_FW_RENDERUNIT_LIST_
