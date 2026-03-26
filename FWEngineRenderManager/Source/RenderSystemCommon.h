/*

RenderSystemCommon

Author: Zhen Yi

Created Date: Nov. 9, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_RENDERSYSTEM_COMMON_
#define _FW_RENDERSYSTEM_COMMON_

#include"BaseData.h"


namespace FW
{
	inline FDWORD CreateSpaceTimeID(int orderSpace, int orderTime)
	{
		FDWORD id = (orderSpace & 0x0000ffff) << 16 + (orderTime & 0x0000ffff);
		return id;
	}

	inline int GetSpaceOrderFromSTID(FDWORD idSpaceTime)
	{
		return (idSpaceTime & 0xffff0000) >> 16;
	}

	inline int GetTimeOrderFromSTID(FDWORD idSpaceTime)
	{
		return (idSpaceTime & 0x0000ffff);
	}
}



#endif // !_FW_RENDERSYSTEM_COMMON_


