/*
CMesh

	  CMesh is not independent primatter, so it do not possess the id itself.

Author: YZ
Created Date: Mar. 3, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_MESH_
#define _FW_MESH_


#include<vector>
#include<map>
#include "GL/glew.h"
#include"CPrimatter.h"
#include"CRenderUnit.h"
#include"CBound.h"
#include"CSkin.h"
#include"TemplateLibrary.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class CBox;
	class CEssety;
	class CRender;
	class CComesh;
	class CSkin;class CMaterial;
	class Matrix3x3;
	class Matrix4x4;
	class CAABB;
	class CAssistFrame;
	class Vector3;

	/*
	  Important:
	    CMesh is not independent primatter, so it do not possess the id itself.
	*/
	class DLLCOAPI CMesh : public CPrimatter
	{
	private:
		typedef std::vector<Vector3*> VTVC3;
		typedef VTVC3::iterator VTVC3_ITER;

		typedef std::vector<Vector2*> VTVC2;
		typedef VTVC2::iterator VTVC2_ITER;

		typedef std::vector<SSurface*> VTSSF;
		typedef VTSSF::iterator VTSSF_ITER;

		typedef std::vector<unsigned int> VTIND;
		typedef std::vector<VTIND> VTSUF;
		typedef VTSUF::iterator VTSUF_ITER;

		typedef std::vector<SRelation*> VTSRT;
		typedef VTSRT::iterator VTSRT_ITER;

		typedef std::vector<CRender*> VTRND;
		typedef VTRND::iterator VTRND_ITER;


	//Inherite from CPrimatter
	public:
		virtual bool Initialize(FDWORD id, const char* pszName, const char* pszNamePathAndFile);
		virtual bool ReleasePrimatterAll(IPrimatterManager* pPmtCent) { return true; }



	public:
		CMesh(CConstruct* pHost);
		CMesh(const char* pszName, CConstruct* pHost);
		virtual ~CMesh();


		bool CreateVertexBufferByOBJFile(const char* pszOBJName, OBJECT* pOBJ);
		bool CreateVertexBufferByFBXFile(const char* pszOBJName, OBJECT* pOBJ);
		bool CreateVertexBufferByFWDFile(const char* pszOBJName, OBJECT* pOBJ);


		Vector3* GetVertexAt(int index)
		{
			if ((index < 0) || (index >= m_vtSVertex.size())) return 0;
			return m_vtSVertex[index];
		}

		bool RegisterBox(CBox* pBox);

		//FinishAdd must be called after the finish of appendding vertex.
		void Destroy();
		void Update(CEssety* pEssety);


		//call back by CSkin object 
		void OnUpdateOutputVertices(VTSSKF& vtControlVertex);


	//attribute
	public:

		CComesh* host() { return (CComesh*)m_pHost; }

		virtual void setMaterial(CMaterial* pMaterial);
		virtual bool initializeMaterial(CMaterial* pMaterial);


		CSkin* skin() { return m_pCurrentSkin; }
		void setSkin(CSkin* pSkin) 
		{ m_pCurrentSkin = pSkin; m_idCurrentSkin = pSkin->id(); }

		bool majorCompleted() { return m_bMajorCompleted; }

		Matrix4x4* const matGeometry() { return m_pMatGeometry; }
		void setMatGeometry(Matrix4x4* pMat) { m_pMatGeometry = pMat; }


		const Vector3& BindingBoxCenter();
		virtual const Vector3& centerBound() { return m_pBound->center(); }

		Matrix4x4& matModelSpace() { return m_jMatModelSpace; }
		void setMatrixModelSpace(Matrix4x4& mat) { m_jMatModelSpace = mat; }

		Vector3& max() { return m_v3MaxMS; }
		Vector3& min() { return m_v3MinMS; }

		CRenderUnit* renderUnit() { return m_pRndUt; }



	private:
		bool CreateVertexBufferFromOBJFile(const char* pszMeshName, OBJECT* pOBJ);
		bool CreateVertexBufferFromEXOBJ(const char* pszMeshName, OBJECT* pOBJ);
		bool CreateOutputBuffer();
		void ClearAll();
		void ProcessVertexNormal(OBJECT* pOBJ);
		void ProcessVertexTangent(OBJECT* pOBJ);
		void ProcessVertexUV(OBJECT* pOBJ);
		void AppendCloneVertex(int indexSrc, UV& uv);


	protected:
		/*
		  The set m_vtSvertex/m_vtSNormal/m_vtStangent save all position/normal/tangent vector
		  in the MODEL SPACE.
		*/
		VTVC3 m_vtSVertex;
		VTVC3 m_vtSNormal;     // the average normal
		VTVC3 m_vtSTangent;    // the average tangent
		VTVC2 m_vtUV;

		VTSUF m_vtVertexAdjSurface;     // for solving the average normal
		VTSRT m_vtSVertexRlt;     // for solving uv seam problem
		VTSSF m_vtSurface;


		
		CSkin* m_pCurrentSkin;
		FDWORD m_idCurrentSkin;

		bool m_bMajorCompleted;


		int m_nSizeVertexBuffer;
		int m_nSizeIndexBuffer;

		int m_nIndexCount;

		Matrix4x4 m_jMatModelSpace;
		Matrix4x4* m_pMatGeometry;
		Matrix4x4 m_jMatTmp;


		//Note: m_v3MaxMS/m_v3MinMS is max/min point in model space. 
		Vector3 m_v3MaxMS;
		Vector3 m_v3MinMS;


		CBound* m_pBound;

		//Just a reference. Must not delete it.
		CBox* m_pBox;
		

		CRenderUnit* m_pRndUt;
	};

}

#endif