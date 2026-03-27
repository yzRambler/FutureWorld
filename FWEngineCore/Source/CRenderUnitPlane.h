/*

CRenderUnitPlane


Author: Zhen Yi -- взеђ


Created Date: Feb. 20, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_RENDERUNIT_PLANE_
#define _FW_RENDERUNIT_PLANE_

#include"CRenderUnit.h"

namespace FW
{
	class CRenderUnitPlane : public CRenderUnit
	{
	private:
		enum ECONST{ SF_CONT = 2, SF_COM = 3, VT_CONT = 4, VT_COM = 5};
	public:
		CRenderUnitPlane(CConstruct* pHost);
		CRenderUnitPlane(const char* pszName, CConstruct* pHost);
		virtual ~CRenderUnitPlane();

	//Inherit from CRenderUnit
	public:
		virtual void Initialize(int countVertexBuffer, int countIndexBuffer);
		virtual void Rendering(CMaterial* pMatl, int indexPass);


	private:
		void Clean();

	};
}


#endif // !_FW_RENDERUNIT_PLANE_
