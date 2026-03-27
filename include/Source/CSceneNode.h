/*
CSceneNode:
    Each CSceneNode obj own one and only one CEssety obj, if it's existed.


Author: Zhen Yi
Created Date: Feb. 05, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SCENENODE_
#define _FW_SCENENODE_

#include<vector>

#include"IPrimatterManager.h"
#include"IRenderManager.h"

#include"CConstruct.h"
#include"CNode.h"
#include"CSpace.h"
#include"BaseData.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class CEssety;
	class DLLCOAPI CSceneNode : public CConstruct, public CNode
	{

	//Inherit from CConstruct
	public:
		virtual bool ReleasePrimatterAll(IPrimatterManager* pPmtCent);



	public:
		CSceneNode();
		CSceneNode(const char* pszName);
		virtual ~CSceneNode();

		void Create(int orderSpace, int orderTime, FDWORD idSpaceTime, Vector3& posWorld, Vector3& forwardWorld, 
			Vector3& upWorld, Vector3& posLocal, Vector3& forwardLocal, Vector3& upLocal);

		void Update(float ratio, long lDltTime, IPrimatterManager* pPmtCent, IRenderManager* pRenderMag);
		void Update(float ratio, long lDltTime, CScene* pScene, IPrimatterManager* pPmtCent, IRenderManager* pRenderMag);

		bool AttachConstruct(CConstruct* pConstruct) 
		{ if ((m_pMainConstruct != 0) || (pConstruct == 0)) return false; m_pMainConstruct = pConstruct; return true; }


		CConstruct* SearchConstruct(const char* pszName);

		void DestroyMainConstruct() { if (0 != m_pMainConstruct) { delete m_pMainConstruct; m_pMainConstruct = 0; } }


	private:
		void Destroy();


	//attribute
	public:
		CConstruct* construct() { return m_pMainConstruct; }

		CSpace* spaceWorld() { return m_pSpaceWorld; }
		CSpace* spaceLocal() { return m_pSpaceLocal; }

		int orderSpace() { return m_nSpaceOrder; }
		int orderTime() { return m_nTimeOrder; }
		FDWORD spaceTimeID() { return m_idSpaceTime; }

	private:

		CSpace* m_pSpaceWorld;
		CSpace* m_pSpaceLocal;

		CConstruct* m_pMainConstruct;

		int m_nSpaceOrder;
		int m_nTimeOrder;
		FDWORD m_idSpaceTime;
	};
};


#endif // !_FW_SCENENODE_
