/*

CSkinMesh

Author:  Zhen  Yi.

Created Data: Oct. 19, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_SKINMESH_
#define _FW_SKINMESH_

#include"CMesh.h"



namespace FW
{

	class CSkinMesh : public CMesh
	{
	public:
		CSkinMesh(CConstruct* pHost);
		CSkinMesh(const char* pszName, CConstruct* pHost);
		virtual ~CSkinMesh();
	};

}





#endif // !_FW_SKINMESH_
