#include"CUIPanel.h"
#include"CEssety.h"
#include"CSceneNode.h"
#include"CBound.h"
#include"CRender.h"
#include"CBox.h"
#include"CMaterial.h"
#include"CUIButton.h"





using namespace FW;


CUIPanel::CUIPanel(const char* pszName, CConstruct* pHost,
	EUITYPE type /*= EUITYPE::UI_PANEL*/) : 
	CUI(pszName, pHost,	type)
{
}

CUIPanel::~CUIPanel()
{
}




bool CUIPanel::ProcessMsg(CMsgBase& msg)
{
	return CUI::ProcessMsg(msg);
}






bool CUIPanel::Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl)
{
	if (!CUI::Create(block, fDist2Cam, pszNameFileMatl, pszNameMatl))
	{
		return false;
	}

	//...


	return true;
}

