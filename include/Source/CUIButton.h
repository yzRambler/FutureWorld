/*

CUIButton


Author: Zhen Yi  --- взеђ

Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha


*/


#ifndef _FW_UI_BUTTON_
#define _FW_UI_BUTTON_

#include"CUI.h"



namespace FW
{
	class Vector4;
	class CMaterial;
	class DLLUIAPI CUIButton : public CUI
	{
	private:
		typedef enum eStageBt {
			STGB_NORMAL = 0, STGB_HOVE, STGB_PRESSED, STGB_DISABLE
		}ESTAGEBT;


		//Inherit from CUI
	public:
		virtual bool ProcessMsg(CMsgBase& msg);
		virtual bool Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl);


	public:
		CUIButton(const char* pszName, CConstruct* pHost);
		virtual ~CUIButton();




	//Attribute
	public:
		FDWORD  idTarget() { return m_idTarget; }
		void setTargetId(FDWORD idTarget) { m_idTarget = idTarget; }


	private:
		void ChangeTexture(int index);


	private:
		FDWORD m_idTarget;
		ESTAGEBT m_eStageBt;
	};

}


#endif // !_FW_UI_BUTTON_
