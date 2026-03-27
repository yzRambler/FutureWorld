/*

CUITextBox

Author: Zhen Yi  (взеђ)

Created Date: Mar. 23, 2024

Version: 0.2.0 Alpha

*/

#ifndef _FW_TEXTBOX_
#define _FW_TEXTBOX_

#include<vector>
#include"CUI.h"


namespace FW
{
	class CTextField;
	class Matrix4x4;
	class CRender;
	class DLLUIAPI CUITextBox : public CUI
	{
	private:
		typedef std::vector<CRender*> VTRND;
		typedef VTRND::iterator VTRND_ITER;

		//Inherite from CUI
	public:
		virtual bool Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl);
		virtual bool ProcessMsg(CMsgBase& msg);


	public:
		CUITextBox(const char* pszName, CConstruct* pHost); 
		virtual ~CUITextBox();


	protected:
		bool CreateTextField(const char* pszContent, SRECT& block, float fDist2Cam, float step);

	
	private:
		void Destroy();



	protected:
		VTRND m_vtRnd;

		CTextField* m_pTxtField;
	};



}





#endif // !_FW_TEXTBOX_
