/*

CSceneAspect


Author:  Zhen Yi
Created Date: Feb. 06, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SCENEASPECT_



#include"CAspect.h"
#include"CData.h"
#include"FWEnginePrimatterManagerExport.h"


namespace FW
{
	class CSceneNode;
	class CSceneNodeAspect;
	class CScene;
	class CPrimatterAspectCenter;
	class DLLPRAPI CSceneAspect : public CAspect, public CData
	{
	private:
		/*
		Three scene loading pattern:
		   MANUAL: manual loading
		   AUTO: automatically loading
		   MIX:  combine loading
		*/
		enum ELOADPATTERN{ MANUAL=0, AUTO, MIX, UNKNOW };

	public:
		CSceneAspect();
		CSceneAspect(const char* pszName);
		virtual ~CSceneAspect();

		

		bool CreateByManual();
		bool CreateByConfigFile(const char* pszName, CSceneNodeAspect* pRootSceneAptTree);

	//Inherited from CAspect
	public:
		virtual bool Clone(CSceneAspect* pSceneApt);
		virtual bool Copy(CAspect* pAptSrc);
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst  =nullptr );

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual EAPTSTATE CheckState(CAspectCenter* pPmtAtpCent);


	//attribute
	public:
		bool isLoadAuto() { return m_eLoadPt == ELOADPATTERN::AUTO; }
		ELOADPATTERN patternLoad() { return m_eLoadPt; }

		CSceneNodeAspect* rootSceneAptTree() { return m_pRootSceneAptTree; }
		void setRootSceneAptTree(CSceneNodeAspect* pRootSceneNodeApt) 
		{ m_pRootSceneAptTree = pRootSceneNodeApt; }

		int orderTime() { return m_nTimeOrder; }
		void setTimeOrder(int order) { m_nTimeOrder = order; }

		int screenWidth() { return m_nScreenWidth; }
		void setScreenWidth(int w) { m_nScreenWidth = w; }

		int screenHeight() { return m_nScreenHeight; }
		void setScreenHeight(int h) { m_nScreenHeight = h; }



	private:
		bool SearchSceneNodeInBuffer(char* pBuffer, const char* pszSceneNodeAspName);
		CSceneNodeAspect* CreateSceneNodeAspectTree(const char* pszSceneNodeAspName);

		EAPTSTATE TraverseSceneAptTreeState(CSceneNodeAspect* pSceneNodeApt, CAspectCenter* pAtpCent);

		void Destroy();



	private:
		CSceneNodeAspect* m_pRootSceneAptTree;
		ELOADPATTERN m_eLoadPt;


		int m_nTimeOrder;

		int m_nScreenWidth;
		int m_nScreenHeight;

	};

};


#endif // !_FW_SCENEASPECT_
