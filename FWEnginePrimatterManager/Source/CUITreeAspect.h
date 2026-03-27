/*

CUITreeAspect

Author: Zhen Yi

Created Date: Feb. 16, 2026

Version: 0.2.0 Alpha

*/

#ifndef _FW_UI_TREE_ASPECT_
#define _FW_UI_TREE_ASPECT_

#include<vector>
#include"CAspect.h"
#include"CData.h"
#include"CommonUI.h"
#include"FWEnginePrimatterManagerExport.h"

namespace FW
{
	class CSceneNodeAspect;
	class CAspectCenter;
	class CUIAspect;
	class DLLPRAPI CUITreeAspect : public CAspect, public CData
	{
	private:
		typedef std::vector<CUIAspect*> VTUIAPT;
		typedef VTUIAPT::iterator VTUIAPT_ITER;


		//Inheriate from CAspect
	public:
		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent);

		//Just check the CConstruct object state
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst);

		//Just check the CConstruct object state
	    virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent);



	public:
		CUITreeAspect(CAspect* pHost = nullptr);
		CUITreeAspect(const char* pszName, CAspect* pHost = nullptr);
		virtual ~CUITreeAspect();

		bool Clone(CUITreeAspect* pUITApt);


		//Attribute 
	public:
		void setTimeOrder(int order) { m_nTimeOrder = order; }
		int orderTime() { return m_nTimeOrder; }
		void setRootUIAptTree(CSceneNodeAspect* pSNodeApt) { m_pRootUITreeApt = pSNodeApt; }
		CSceneNodeAspect* rootUITree() { return m_pRootUITreeApt; }

		bool initMatl() { return m_bMatlInitialized; }

		bool AllReady() { return m_bReady; }


	private:
		void Destroy();
		EAPTSTATE TraverseSceneAptTreeState(CSceneNodeAspect* pSceneNodeApt, CAspectCenter* pAtpCent);
		void CollectUIAspect(CSceneNodeAspect* pSceneNodeApt);


	private:
		CSceneNodeAspect* m_pRootUITreeApt;

		VTUIAPT m_vtUIApt;
		bool m_bMatlInitialized;
		bool m_bReady;

		int m_nTimeOrder;
		
	};

}




#endif // !_FW_UI_TREE_ASPECT_
