/*l

CComeshAspect



Author: Zhen Yi

Created Date: Feb. 16, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_COMMESHASPECT_
#define _FW_COMMESHASPECT_

#include<vector>
#include"CPrimatterAspect.h"


namespace FW
{
	class CComesh;
	class CEssetyAspect;
	class CMeshAspect;
	class CSpaceAspect;
	class CPrimatterAspectCenter;
	class  CComeshAspect : public CPrimatterAspect
	{
		typedef std::vector<CMeshAspect*> VTMESHAPT;
		typedef VTMESHAPT::iterator VTMESHAPT_ITER;

		//Inherit from CAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);

		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst =nullptr );

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);
		virtual EAPTSTATE CheckState(CEssetyAspect* pEsetyApt, CAspectCenter* pAptCent);


	public:
		CComeshAspect();
		CComeshAspect(const char* pszName);
		virtual~ CComeshAspect();

		void AddMeshAspect(CMeshAspect* pMeshApt) { m_vtMeshApt.push_back(pMeshApt); }




		CMeshAspect* Find(const char* pszNameMesh);

	public:
		void Destroy();

		//attribute
	public:
		int countMeshApt() { return m_vtMeshApt.size(); }
		CMeshAspect* meshApt(int ind) 
		{ if ((ind < 0) || (ind >= m_vtMeshApt.size())) return 0; return m_vtMeshApt[ind]; }

		CSpaceAspect* spaceApt() { return m_pSpaceModelApt; }


	private:
		VTMESHAPT m_vtMeshApt;
		CSpaceAspect* m_pSpaceModelApt;
	};


}


#endif // !_FW_COMMESHASPECT_
