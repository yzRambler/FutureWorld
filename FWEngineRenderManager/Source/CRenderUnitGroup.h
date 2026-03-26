/*
CRenderUnitGroup
    


Author:  Zhen Yi

Created Date:  June  8, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_RENDERUNIT_GROUP_
#define _FW_RENDERUNIT_GROUP_

#include<map>
#include<list>
#include<vector>

#include"CommonPrimatter.h"
#include"Common.h"
#include"EngineCoreCommon.h"

namespace FW
{
	
	class CRenderUnit;
	class CRenderUnitList;
	class Vector3;
	class CCamera;
	class CRenderUnitGroup
	{
	private:
		typedef std::vector<CRenderUnit*> VTRNDUT;
		typedef VTRNDUT::iterator VTRNDUT_ITER;

		typedef std::map<FDWORD, CRenderUnitList*> MAPRULT;
		typedef MAPRULT::iterator MAPRULT_ITER;

		typedef std::list<CRenderUnitGroup*> LTRNDGP;
		typedef LTRNDGP::iterator LTRNDGP_ITER;

	public:
		CRenderUnitGroup();
		virtual ~CRenderUnitGroup();

		void AddRenderUnit(CRenderUnit* pRenderUnit) { m_vtRenderUnit.push_back(pRenderUnit); }
		void MergeWithMaterial(const Vector3& v3PosCamera);
		void MergeWithMaterial(CCamera* pCam);
		void UpdateCameraLightParameter(CCamera* pCam, VTLIT& vtLights);

		void Rendering();
		void CleanAll();

		//Just clear RenderUnit list but keeping the grouped result (i.e. m_vtRenderUnit). 
		void ClearRenderUnitList();

	//attribute
	public:
		int order() { return m_nOrder; }
		void setOrder(int nd) { m_nOrder = nd; }
		ERNDTYPE typeRender() { return m_eRenderType; }
		void setRenderType(ERNDTYPE type) { m_eRenderType = type; }
		bool emptyRenderUnit() { return m_mapRndUtList.empty() && m_vtRenderUnit.empty(); }


	private:
		void Sort(const Vector3& v3CameraPos);
		void Sort(CCamera* pCam);
		void MergeSort(const Vector3& v3CameraPos, int indStart, int indEnd);
		void MergeSort(CCamera* pCam, int indStart, int indEnd);


		CRenderUnitList* SearchRenderUnitList(FDWORD idMatl);
		void InsertRenderUnitList(CRenderUnitList* pRndUtLst);
		void AppendRenderUnitList(CRenderUnitList* pRndUtLst);
		CRenderUnitList* GetLastRUList() { return m_nOrderCount < 0 ? 0 : m_mapRndUtList[m_nOrderCount]; }

	private:
		int m_nOrder;

		//Just offer to transparent group for generating order.
		//Note.  The key of m_mapRndUtList in transparent group is not material id.
		int m_nOrderCount;
		ERNDTYPE m_eRenderType;
		
		VTRNDUT m_vtRenderUnit;
		MAPRULT m_mapRndUtList;

		//
		LTRNDGP m_lstSubRenderUtGroup;

	};
}



#endif // !_FW_RENDERUNIT_GROUP_
