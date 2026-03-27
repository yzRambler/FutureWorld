/*

CRenderUnitRect

Author:  Zhen Yi

Created Date: Oct. 21, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_RENDERUNIT_RECT_
#define _FW_RENDERUNIT_RECT_

#include "CRenderUnit.h"



namespace FW
{
	class CRenderUnitRect : public CRenderUnit
	{
	public:
		CRenderUnitRect(CConstruct* pHost);
		CRenderUnitRect(const char* pszName, CConstruct* pHost);
		virtual ~CRenderUnitRect();

		virtual void Initialize(int countVertexBuffer, int countIndexBuffer);


	};
}





#endif // !_FW_RENDERUNIT_RECT_
