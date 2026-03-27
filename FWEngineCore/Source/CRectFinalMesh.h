/*

CRectFinalMesh


Author:  Zhen Yi

Created Date: Feb. 12, 2026

Version: 0.2.0 Alpha

*/


#ifndef _FW_RECT_FINALMESH_
#define _FW_RECT_FINALMESH_

#include "CRectMesh.h"




namespace FW
{
	class CMaterial;
	class CTexture;
	class CVertexShader;
	class CFragmentShader;
	class DLLCOAPI CRectFinalMesh : public CRectMesh
	{
	public:
		CRectFinalMesh(CConstruct* pHost);
		CRectFinalMesh(const char* pszName, CConstruct* pHost);
		virtual ~CRectFinalMesh();

		bool Create();


	private:

	};


};





#endif // !_FW_RECT_FINALMESH_
