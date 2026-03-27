/*

EngineCoreCommon


Author: Zhen Yi

Created Date: Nov. 23, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_ENGINECORE_COMMON_
#define _FW_ENGINECORE_COMMON_

#include <vector>


namespace FW
{
	//for message
	typedef enum eMessageType {
		MSG_TIME = 0, MSG_MMOVE, MSG_MLBDOWN, MSG_MLBUP, MSG_MRBDOWN, MSG_MRBUP, MSG_KBDOWN, MSG_KBUP,
		MSG_UIBTDOWN, MSG_UIBTUP, MSG_UNKNOWN
	}EMSGTYPE;


	class CLight;
	typedef std::vector<CLight*> VTLIT;
	typedef VTLIT::iterator VTLIT_ITER;


	class AMatrix4x4;
	typedef struct SSkinDfm
	{
		AMatrix4x4* mat;
		float weight;
		unsigned int indexVt;
	}SSKDFM;

	typedef std::vector<SSKDFM*> VTSSKF;
	typedef VTSSKF::iterator VTSSKF_ITER;
}



#endif // !_FW_ENGINECORE_COMMON_
