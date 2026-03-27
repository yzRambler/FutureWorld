#if _WND_OPENGL_PLATFORM_
#include<stdlib.h>
#else
#include<stdio.h>
#endif // _WND_OPENGL_PLATFORM

#include"CUICount.h"
#include"CEssety.h"
#include"CSceneNode.h"
#include"CBound.h"
#include"CRender.h"
#include"CRectImage.h"
#include"CTextField.h"



using namespace FW;



CUICount::CUICount(const char* pszName, CConstruct* pHost) : CUITextBox(pszName, pHost)
{
	setTypeUI(EUITYPE::UI_COUNT);
	m_rUV.fx = m_rUV.fy = m_rUV.fh = m_rUV.fw = 0.0f;
}


CUICount::~CUICount()
{
}



bool CUICount::Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl)
{
	if (!CUI::Create(block, fDist2Cam, pszNameFileMatl, pszNameMatl))
	{
		return false;
	}


	return CreateTextField("000", block, fDist2Cam, 1.0f);
}



static const int ARRY_LEN = 64;
bool CUICount::ProcessMsg(CMsgBase& msg)
{
	if (msg.type != EMSGTYPE::MSG_TIME)
	{
		return false;
	}

	CMsgTime& msgTm = (CMsgTime&)msg;

	char str[ARRY_LEN];
	memset(str, 0, ARRY_LEN);

	int fps = 1000 / msgTm.dltTime();

#if _WND_OPENGL_PLATFORM_
	_itoa_s(fps, str, 10);
#else
	sprintf(str, "%d", fps);
#endif // _WND_OPENGL_PLATFORM

	CChar* pChar = nullptr;
	CRectImage* pRImg = nullptr;

	//The unit count of m_pTxtField is equal the size of m_vtRend.
	for (int i = 0; i < m_vtRnd.size(); i++)
	{
		//pChar = m_pTxtField->unit(i);
		pChar = m_pTxtField->getChar(i);
		m_rUV.fx = pChar->u();
		m_rUV.fy = pChar->v();
		m_rUV.fw = pChar->du();
		m_rUV.fh = pChar->dv();

		pRImg = (CRectImage*)m_vtRnd[i]->comesh();
		pRImg->UpdateUV(&m_rUV);
	}

	//for (int i = 0; str[i] != '\0'; i++)
	//{
	//	m_vtChar[m_vtChar.size() - i - 1]->Update(str[i]);
	//}


	return true;
}




void CUICount::Destroy()
{
}

