/*

CLineMesh


Author: Zhen Yi   взеђ

Created Date: Jan. 28, 2024

Version: 0.2.0 Alpha

*/

#ifndef _FW_LINEMESH_
#define _FW_LINEMESH_

#include"CMesh.h"


namespace FW
{
	class CLineMesh : public CMesh
	{
	public:
		CLineMesh(CConstruct* pHost);
		CLineMesh(const char* pszName, CConstruct* pHost);
		virtual ~CLineMesh();

		bool Initialize(Vector3& start, Vector3& end, Vector4* pColor = 0);
		void Update(Vector3& start, Vector3& end, Matrix4x4& matWorld);
		void Update(Vector3& start, Vector3& end);

	private:
		void SetOutputVertexData();

	private:
		Vector4 m_v4Color;
	};
}





#endif