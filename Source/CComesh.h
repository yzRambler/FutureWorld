/*

CComesh

    CComesh means co-mesh, combinating meshes. CComesh can be multi-part and multi-material. 


Author:  Zhen Yi

Created Date: Feb. 16, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_COMMESH_
#define _FW_COMMESH_

#include<vector>
#include"CPrimatter.h"
#include"CommonPrimatter.h"
#include"MathLibrary.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class CBox;
	class CEssety;
	class CMesh;
	class CSpace;
	class CRender;
	class DLLCOAPI CComesh : public CPrimatter
	{
	protected:
		typedef struct
		{
			CMesh* pMesh;
			FDWORD id;    //for avoiding operation hunging pointer.
		}SMeshData;

		typedef std::vector<SMeshData*> VTMESH;
		typedef VTMESH::iterator VTMESH_ITER;


		typedef std::vector<CRender*> VTRND;
		typedef VTRND::iterator VTRND_ITER;

		//Inherit from CPrimatter
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);


	public:
		CComesh(CConstruct* pHost);
		CComesh(const char* pszName, CConstruct* pHost);
		virtual ~CComesh();

		void AddMesh(CMesh* pMesh);
		void DeleteMesh(CMesh* pMesh);

		virtual void Update(CEssety* pEssety);


		CMesh* SearchMesh(const char* pszName);



	//attribute
	public:
		int countMesh() { return m_vtMesh.size(); }
		CMesh* mesh(int ind) 
		{ if ((ind < 0) || (ind >= m_vtMesh.size())) return 0; return m_vtMesh[ind]->pMesh; }

		CSpace* space() { return m_pSpaceModel; }


		//Note:
		// The max()/min() is the point location in Model space.
		Vector3& max() { return m_v3MaxMS; }
		Vector3& min() { return m_v3MinMS; }


	protected:
		virtual void CleanAllMesh();


	private:
		void Destroy();


	protected:
		VTMESH  m_vtMesh;
		VTRND m_vtSubRender;

		//Note: m_v3MaxMS/m_v3MinMS is max/min point in model space.
		Vector3 m_v3MinMS;
		Vector3 m_v3MaxMS;


	private:
		CSpace* m_pSpaceModel;

		
	};
}





#endif // !_FW_COMESH_



