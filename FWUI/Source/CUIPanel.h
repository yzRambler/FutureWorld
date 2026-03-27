/*

CUIPanel


Author: Zhen Yi -- взеђ


Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha


*/


#ifndef _FW_UI_PANEL_
#define _FW_UI_PANEL_

#include"CUI.h"



namespace FW
{
	class CMaterial;
	class DLLUIAPI CUIPanel : public CUI
	{
		//Inherite from CUI
	public:

		virtual bool Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl);
		virtual bool ProcessMsg(CMsgBase& msg);


	public:
		CUIPanel(const char* pszName, CConstruct* pHost,
			EUITYPE type = EUITYPE::UI_PANEL);

		virtual ~CUIPanel();



	};


}



#endif // !_FW_UI_PANEL_
