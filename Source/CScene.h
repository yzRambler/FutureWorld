/*
CScene

Author: Zhen Yi
Created Date: May 13, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_SCENE_
#define _FW_SCENE_

#include<vector>
#include<map>
#include<string>

#include"IPrimatterManager.h"
#include"IRenderManager.h"

//#include"CPrimatter.h"
//#include"CSceneNode.h"
#include "CData.h"
#include"CConstruct.h"
#include"EngineCoreCommon.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class CCamera;
	class CFrame;
	class CSceneNode;
	class CUI;

	//class CScene : public CPrimatter, public IScene
	//class CScene : public CPrimatter
	class DLLCOAPI CScene : public CConstruct, public CData
	{
	public:
		typedef std::vector<CCamera*> VTCAM;
		typedef VTCAM::iterator VTCAM_ITER;

		//the key is CLight::m_idTargetSpaceTime
		typedef std::map<FDWORD, VTLIT> MAPLIT;
		typedef MAPLIT::iterator MAPLIT_ITER;



	//Inherit from CConstruct
	public:
		//virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);
		virtual bool ReleasePrimatterAll(IPrimatterManager* pPmtCent);


	public:
		CScene();
		CScene(const char* pszName);
		virtual ~CScene();

		//bool Create(int width, int height, CSceneNode* pSceneNodeRoot);
		bool Create(CSceneNode* pSceneNodeRoot, int sw, int sh);

		bool InitializeUITree(CSceneNode* pUITreeRoot);

		bool CreateUITreeDynamic(Vector3& posOrg, Vector3& forwardOrg, Vector3& upOrg, 
			Vector3& posCam, int vpX, int vpy, int vpw, int vph);

		void AppendCameraIntoArray(CCamera* pCamera);
		void RemoveCameraFromArray(CCamera* );

		CSceneNode* FindNode(const char* pszNodeName)
		{
			return SearchNode(pszNodeName, m_pSceneTreeRoot);
		}


		CSceneNode* FindUINode(const char* pszNodeName)
		{
			return SearchNode(pszNodeName, m_pUITreeRoot);
		}

		CUI* FindUI(UID id);


		//This update procedure contain that check the visibility of the scene node   
		void Update(float ratio, IPrimatterManager* pPmtCenter, 
			IRenderManager* pRenderMag);


	//attribute
	public:
		CSceneNode* rootNode() { return m_pSceneTreeRoot; }
		void setRootNode(CSceneNode* pSRNode) { m_pSceneTreeRoot = pSRNode; }

		CSceneNode* rootNodeUI() { return m_pUITreeRoot; }
		void setUIRootNode(CSceneNode* pSRNode) { m_pUITreeRoot = pSRNode; }


		int countCamera() { return m_vtCamera.size(); }
		CCamera* camera(int ind) 
		{  if ((ind < 0) || (ind >= m_vtCamera.size())) { return 0; } 
		return m_vtCamera[ind]; }

		
		const VTLIT* lightArray(FDWORD idSpaceTime)
		{
			MAPLIT_ITER iter = m_mapLight.find(idSpaceTime);
			if (iter == m_mapLight.end()) { return 0; }

			return &iter->second;
		}

		int orderTime() { return m_nTimeOrder; }
		void setTimeOrder(int order) { m_nTimeOrder = order; }

		int widthWnd() { return m_widthWnd; }
		int heightWnd() { return m_heightWnd; }


		//The transform matrix from screen space into world space.
		Matrix4x4& matSToWByUICam() { return m_jMatS2WUICam; }
		void setMatrixSToWByUICam(Matrix4x4& mat) { m_jMatS2WUICam = mat; }


	private:
		void UpdateSceneNode(float ratio, long dltTime, CSceneNode* pSNode,
			IPrimatterManager* pPmtCenter, IRenderManager* pRenderMag);
		void Destroy();
		void CreateCameraLightArray(CSceneNode* pSceNode);
		CSceneNode* SearchNode(const char* pszNodeName, CSceneNode* pNode);
		CUI* SearchUITree(UID id, CSceneNode* pNode);
		CCamera* SearchUICamera(CSceneNode* pNode);

	private:
		VTCAM m_vtCamera;
		MAPLIT m_mapLight;

		CSceneNode* m_pSceneTreeRoot;
		CSceneNode* m_pUITreeRoot;

		//world coordinate system :  right-hand ruler  
		//up(Y axis) - left(X axis) - forward(Z axis)
		CFrame* m_pWorldCoordSystem;

		//the matrix of Screen Space to World Sapce with UICamera
		Matrix4x4 m_jMatS2WUICam;

		int m_widthWnd;
		int m_heightWnd;

		int m_nTimeOrder;
	};



}



#endif // !_FW_SCENE_
