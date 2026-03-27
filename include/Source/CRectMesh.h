/*

CRectMesh


Author:  Zhen  Yi

Created Date:  Oct. 19, 2025

Version: 0.2.0 Alpha

*/

#ifndef _FW_RECTMESH_
#define _FW_RECTMESH_

#include"BaseData.h"
#include"CMesh.h"




namespace FW
{

	class CRect;
	class CMaterial;
	class DLLCOAPI CRectMesh : public CMesh
	{
	public:
		CRectMesh(CConstruct* pHost);
		CRectMesh(const char* pszName, CConstruct* pHost);
		virtual ~CRectMesh();

		/*
		 SRect* pRectUV     left-top corner location(x, y) and horizontal span(z), vertical span.
		*/
		bool Create(CRect* pRect, const char* pszNameFileMatl, const char* pszNameMatl, URect* pRectUV = nullptr);
		bool CreateTest(CRect* pRect, const char* pszNameFileMatl, const char* pszNameMatl, URect* pRectUV = nullptr);
		void UpdateUV(URect* pRectUV);


		void ActiveTexture(int indTex);


		//Attribute.   Inherit from CMesh 
	public:
		virtual const Vector3& centerBound() { return m_v3Center; }

		//Attribute.  
	public:
		void setCenterBound(Vector3& v3Cent) {}
		Vector3& maxWS() { return m_v3MaxMS; }
		Vector3& minWS() { return m_v3MinMS; }




	private:
		

		Vector3 m_v3Center;
		Vector3 m_v3MaxWS;
		Vector3 m_v3MinWS;

	};


}



#endif // !_FW_RECTMESH_
