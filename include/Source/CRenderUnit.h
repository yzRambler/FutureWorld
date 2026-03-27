/*
CRenderUnit


Author: Zhen Yi

Created Date: June 8 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_RENDERUNIT_
#define _FW_RENDERUNIT_

#include<vector>
#include "GL/glew.h"
#include"CommonPrimatter.h"
#include"Common.h"
#include"CConstruct.h"

namespace FW
{
	class CMaterial;
	class CVertexAttribute;
	class CRenderUnit : public CConstruct
	{
	protected:
		typedef std::vector<CVertexAttribute*> VTVA;
		typedef VTVA::iterator VTVA_ITER;

	public:
		CRenderUnit(CConstruct* pHost);
		CRenderUnit(const char* pszName, CConstruct* pHost);
		virtual ~CRenderUnit();

		virtual void Initialize(int countVertexBuffer, int countIndexBuffer);
		virtual void Rendering(CMaterial* pMatl, int indexPass);

		virtual void BindModel();
		virtual void UnbindMode();


		virtual void AddVertexAttribute(CVertexAttribute* vat) { m_vtVertexAttrib.push_back(vat); }

		void InitializeVertexData(int index, float val) 
		{ m_outVT[index] = m_outVTOriginal[index] = m_tmpVT[index] = val; }

		void InitializeIndexData(int index, unsigned int val) { m_outSI[index] = val; }


	//attribute
	public:
		ERNDTYPE typeRender() { return m_eRenderType; }
		void setRenderType(ERNDTYPE typeRender) { m_eRenderType = typeRender; }

		int orderGroup() { return m_nGroupOrder; }
		void setGroupOrder(int nd) { m_nGroupOrder = nd; }

		int countVertexAttribute() { return m_vtVertexAttrib.size(); }
		CVertexAttribute* getVertexAttribute(int index)
		{
			if ((index < 0) || (index >= m_vtVertexAttrib.size())) { return 0; }

			return m_vtVertexAttrib[index];
		}

		int countVertexComponent() { return m_nCountVertexComponent; }


		virtual float* arrayVertices() { return m_outVT; }
		virtual unsigned int* arrayIndex() { return m_outSI; }

		int sizeVertexBuffer() { return m_nSizeVertexBuffer; }
		int sizeIndexBuffer() { return m_nSizeIndexBuffer; }

		float valueOrignalVT(int index) { return m_outVTOriginal[index]; }
		
		virtual void setVertexData(int index, float val) { m_outVT[index] = val; }

		float valueTempVT(int index) { return m_tmpVT[index]; }
		void setTempData(int index, float val) { m_tmpVT[index] = val; }

		virtual void setIndexData(int index, unsigned int val) { m_outSI[index] = val; }


		//for rendering instruction
		int countIndexArray() { return  m_nCountIndexArray; }
		int countVertexArray() { return m_nCountVertexArray; }

		int sizeVertex() { return m_nSizeVertex; }

		CMaterial* material() { return m_pMaterial; }

		virtual void setMaterial(CMaterial* pMaterial);

		virtual bool InitializeMaterial(CMaterial* pMatl);

		Matrix4x4& matWorld() { return m_matWorld; }



	protected:
		void GenerateGLEObject();
		void DestroyGLEObject();
		virtual int countSurfaceComponent() { return 3; }
		bool existed(CVertexAttribute* pVA);

		void Destroy();


	protected:

#ifdef _WND_OPENGL_PLATFORM_
		GLuint m_unVAO;
#endif
		GLuint m_uVBuffer[2];

		//Note. 
		//1. These four vertex attributes are optional. 
		//2. It have to keep the order:  pos < normal < tangent < uv
		VTVA m_vtVertexAttrib;

		//the vertex buffer
		float* m_outVT;
		
		//the index buffer
		unsigned int* m_outSI;

		Matrix4x4 m_matWorld;

		int m_nSizeVertexBuffer;
		int m_nSizeIndexBuffer;
		int m_nSizeVertex;
		int m_nCountVertexComponent;

		int m_nCountVertexArray;
		int m_nCountIndexArray;


		CMaterial* m_pMaterial;
		FDWORD m_idMaterial;   //for check
		EGEN m_eGenMatl;

	private:
		int m_nGroupOrder;
		ERNDTYPE m_eRenderType;

		float* m_outVTOriginal;
		float* m_tmpVT;
	};
}


#endif // !_FW_RENDERUNIT_
