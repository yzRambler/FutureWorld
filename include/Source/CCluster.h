/*
CCluster

Author: Zhen Yi
Created Date: Dec. 06, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_CLUSTER_
#define _FW_CLUSTER_

#include<vector>
#include<map>
#include"CBase.h"
#include"TemplateLibrary.h"
#include"EngineCoreCommon.h"
#include"MathLibrary.h"
#include"CCluster.h"

namespace FW
{
	class CBone;
	class Vector3;
	class CMesh;
	class DLLCOAPI CCluster : public CBase
	{
	private:
		typedef std::map<unsigned int, float> MAPVERTEX;
		typedef MAPVERTEX::iterator MAPVERTEX_ITER;

	public:
		typedef struct SDfm
		{
			AMatrix4x4* mat;
			float weight;
			unsigned int indexVt;
			unsigned int indexCVAry;  // the index in the control vertex array
		}SDFM;

		typedef std::vector<SDFM*> VTSDFM;
		typedef VTSDFM::iterator VTSDFM_ITER;

	public:
		CCluster();
		CCluster(const char* pszName);
		virtual ~CCluster();

		void AddControlVertex(unsigned int indexVertex, float weight);
		void UpdateLinearMatrix(std::map<unsigned int, TVTAmount<AMatrix4x4>*>& map, CMesh* pMesh);
		void UpdateLinearMatrix(VTSSKF& vt, CMesh* pMesh);
		void UpdateDQuaternion(std::map<unsigned int, TVTAmount<DualQuaternion>*>& map);

		bool Clone(CCluster& cluster);
		void GetAllControlVertices(std::vector<std::pair<unsigned int, float>>& vtPair);

	//attribute
	public:
		void setNameAssociateBone(const char* pszName) { m_strNameAssociateBone.Set(pszName); }
		
		void setAssociateBone(CBone* pBone) {  if(m_pBone == 0) m_pBone = pBone; }
		CBone* boneAssociate() { return m_pBone; }
		const char* nameAssociateBone() { return m_strNameAssociateBone.Get(); }

		int countControlVertices() { return m_mapControlVertices.size(); }
		int countControlVertex() { return m_vtControlVertices.size(); }
		SDFM* contrlVertex(int ind) 
		{ if ((ind < 0) || (ind >= m_vtControlVertices.size())) { return 0; } return m_vtControlVertices[ind]; }


		void setTransformMatrix(Matrix4x4& mat) { memcpy(&m_matTransform, &mat, sizeof(Matrix4x4)); }
		Matrix4x4& matTransform() { return m_matTransform; }

		void setTransformLinkMatrix(Matrix4x4& mat) { memcpy(&m_matTransformLink, &mat, sizeof(Matrix4x4)); }
		Matrix4x4& matTransformLink() { return m_matTransformLink; }

	private:
		void Destroy();
		bool SearchControlVertexInVT(unsigned int index);

	private:
		MAPVERTEX m_mapControlVertices;
		VTSDFM m_vtControlVertices;


		CString m_strNameAssociateBone;
		CBone* m_pBone;  //just refer the outside pointer. Don't delete it.


		Matrix4x4 m_matTransform;
		Matrix4x4 m_matTransformLink;
	};
}


#endif // !_FW_CLUSTER_
