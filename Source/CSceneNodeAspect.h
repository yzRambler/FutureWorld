/*

CSceneNodeAspect


Author: Zhen Yi
Created Date: Feb. 05, 2023

Version: 0.2.0 Alpha

*/

#include<vector>
#include"CAspect.h"
#include"CNode.h"
#include"BaseData.h"

namespace FW
{
	class CEssety;
	class CEssetyAspect;
	class CSpaceAspect;
	class CSceneNode;
	class CPrimatterAspectCenter;
	class Vector3;
	class CSceneNodeAspect : public CAspect, public CNode
	{
	public:
		CSceneNodeAspect();
		CSceneNodeAspect(const char* pszName);
		virtual ~CSceneNodeAspect();


		
		void Create(Vector3& pos, Vector3& forward, Vector3& up);
		void Create();
		void GeneralSpaceTimeID(int orderSpace, int orderTime);


		void AttachConstructAspect(CAspect* pCstApt);
		
		//Just detach, no delete.
		void DetachConstructAspect(CAspect* pCstApt) { m_pConstructAspect = 0; }


	//Inherited from CAspect
	public:
		virtual bool Clone(CSceneNodeAspect* pSceneNodeApt);
		virtual bool Copy(CAspect* pAptSrc);
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent);

	//attribute
	public:
		const CAspect* aspect() { return m_pConstructAspect; }

		const CSpaceAspect* spaceWorldAspect() { return m_pSpaceWorldAspect; }
		const CSpaceAspect* spaceLocalAspect() { return m_pSpaceLocalAspect; }

		bool initedSpaceWorld() { return m_bInitSpaceWorld; }
		void setSignSpaceWorld(bool sign) { m_bInitSpaceWorld = sign; }

		bool initedSapceLocal() { return m_bInitSpaceLocal; }
		void setSignSpaceLocal(bool sign) { m_bInitSpaceLocal = sign; }

		int orderSpace() { return m_nSpaceOrder; }

		int orderTime() { return m_nTimeOrder; }

		FDWORD spaceTimeID() { return m_idSpaceTime; }


	private:
		void CreateCoordSysRender(CSceneNode* pSceneNode, CEssety* pEssety);
		void Destroy();

	private:
		CAspect* m_pConstructAspect;
		CSpaceAspect* m_pSpaceWorldAspect;
		CSpaceAspect* m_pSpaceLocalAspect;

		bool m_bInitSpaceWorld;
		bool m_bInitSpaceLocal;

		FDWORD m_idSpaceTime;
		int m_nSpaceOrder;
		int m_nTimeOrder;
	};
}