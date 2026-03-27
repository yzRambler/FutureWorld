/*
CSKin

Author: Zhen Yi

Created Date: May 1, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_SKIN_
#define _FW_SKIN_

#include<vector>
#include<map>
#include"EngineCoreCommon.h"
#include"CDeformer.h"
#include"TemplateLibrary.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class CMesh;
	class CCluster;
	class CSkeleton;
	class AMatrix4x4;
	class DualQuaternion;
	class DLLCOAPI CSkin : public CDeformer
	{
	public:

		typedef std::map<unsigned int, TVTAmount<AMatrix4x4>*> MAPLINEDF;
		typedef MAPLINEDF::iterator MAPLINEDF_ITER;

		typedef std::map<unsigned int, TVTAmount<DualQuaternion>*> MAPDQUATDF;
		typedef MAPDQUATDF::iterator MAPDQUATDF_ITER;

		typedef std::vector<float> VTBLDWT;
		typedef VTBLDWT::iterator VTBLDWT_ITER;

		typedef std::vector<CCluster*> VTCLUSTER;
		typedef VTCLUSTER::iterator VTCLUSTER_ITER;


	//Inheriate from CPrimatter
	public:
		virtual bool Clone(CPrimatter* pPmt);


	//Inherite from CDeformer
	public:
		virtual void Update(CMesh* pMesh);


	public: 
		CSkin(CConstruct* pHost);
		CSkin(const char* pszName, CConstruct* pHost);

		virtual ~CSkin();


		bool AddCluster(CCluster* pCluster);
		bool CopyWithSkeleton(CSkin* pSrcSkin, CSkeleton* pSkeleton);
		void AddBlendWeight(std::vector<float>& vt);




	//attribute
	public:
		CMesh* host() { return (CMesh*)m_pHost; }

		void setVerticesCount(int n) { m_nVerticesLen = n; }
		int getVerticesCount() { return m_nVerticesLen; }

		void setSkeleton(CSkeleton* pSkeleton) { m_pSkeleton = pSkeleton; }
		CSkeleton* skeleton() { return m_pSkeleton; }

		bool majorCompleted() { return m_bMajorCompleted; }

		int countCluster() { return m_vtCluster.size(); }
		CCluster* cluster(int ind) 
		{ if ((ind < 0) || (ind >= m_vtCluster.size())) { return 0; } return m_vtCluster[ind]; }

	private:
		void Destroy();
		void ClearClusterSet();
		void ComputeClusterDeformation();
		void ComputeLinearDeformation();
		void ComputeQuaternionDeformation();
		bool FindCluster(const char* nameAssociatedBone);
		void ExtendControlVertexSet(void* pSDFM);


	private:
		VTCLUSTER m_vtCluster;

		//Just reference. Must not delete it.
		CSkeleton* m_pSkeleton;

		//for check
		FDWORD  m_idSkeleton;  


		MAPLINEDF m_mapLinearDef;
		MAPDQUATDF m_mapDQuaterDef;
		VTBLDWT  m_vtQLBlendWeight;

		VTSSKF  m_vtControlVertex;

		int m_nVerticesLen;

		bool m_bMajorCompleted;
	};

}




#endif // ! _FW_SKIN_
