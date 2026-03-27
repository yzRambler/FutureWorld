/*

CUICount

Author:  Zhen Yi  (взеђ)


Created Date:  Apr. 5, 2024

Version: 0.2.0 Alpha


*/

#ifndef _FW_UICOUNT_
#define _FW_UICOUNT_

#include"CUITextBox.h"
#include"CChar.h"

namespace FW
{
	class DLLUIAPI CUICount : public CUITextBox
	{
		//Inherit from CUI
	public:
		virtual bool Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl);
		virtual bool ProcessMsg(CMsgBase& msg);


	public:
		CUICount(const char* pszName, CConstruct* pHost);
		virtual ~CUICount();


	private:
		void Destroy();

	private:
		URect m_rUV;
		float m_fInterval;  //between two characters 

	};


}






#endif // !_FW_UICOUNT_
