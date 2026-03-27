/*

CLiteralUnit


Author:  Zhen Yi  (взеђ)


Created Date:  Mar. 29, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_LITERUNIT_
#define _FW_LITERUNIT_

#include"CConstruct.h"


namespace FW
{
	class CMaterial;
	class Matrix4x4;
	class CEssety;
	class CLiteralUnit : public CConstruct
	{
	public:
		CLiteralUnit():CConstruct(0){}
		virtual ~CLiteralUnit() {}

		virtual bool Create(float fx, float fy, float fdist, float fStep) { return true; }


	//attribute
	public:
		virtual float width(){ return 0.0f; }
		virtual float height(){ return 0.0f; }
	};
}




#endif // !_FW_LITERUNIT_
