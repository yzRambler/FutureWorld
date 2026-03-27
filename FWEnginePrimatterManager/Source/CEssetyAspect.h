/*
CEssetyAspect


Author: Zhen Yi
Created Date: Feb. 06, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_ESSETYASPECT_
#define _FW_ESSETYASPECT_


#include<vector>
#include"CAspect.h"
#include"TemplateLibrary.h"

namespace FW
{
	class CEssety;
	class CPrimatterAspectCenter;
	class CComponentAspect;
	class CSceneNodeAspect;
	class CSkeletonAspect;
	class CRender;
	class CEssetyAspect : public CAspect
	{
	private:
		typedef std::vector<CComponentAspect*> VTCPT;
		typedef VTCPT::iterator VTCPT_ITER;


		//Inherited from CAspect
	public:
		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);
		virtual CAspect* Duplicate(int n);

		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent);
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);


		//Inherited from CAspect
	protected:
		virtual CAspect* CreateInstance();



	public:
		CEssetyAspect(CAspect* pHost);
		CEssetyAspect(const char* pszName, CAspect* pHost);

		virtual ~CEssetyAspect();
		

		bool AddComponentAspect(CComponentAspect* pComAspect);
		void RemoveComponentAspect(const char* pszNameCommonent);
		CComponentAspect* GetComponetApt(ECOMTYPE type, const char* psName = nullptr);
		CComponentAspect* GetComponetAptByIndex(int index) 
		{ 
			if ((index < 0) || (index >= m_vtComponentApt.size())) { return nullptr; } 
			return m_vtComponentApt[index];
		}

		int CountComponent() { return m_vtComponentApt.size(); }


		CSkeletonAspect* SearchSkeletonAspect(const char* pszNameSkeletonApt);



	private:
		void Destroy();
		

	private:
		VTCPT m_vtComponentApt;

		bool m_bAllLocalDataReady;

	};

};



#endif // !_FW_ESSETYASPECT_
