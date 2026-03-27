#include"CUITextBox.h"
#include"CTextField.h"
#include"CTextLine.h"
#include"CEssety.h"
#include"CSceneNode.h"
#include"CRender.h"
#include"CBound.h"
#include"CIDManager.h"
#include"CRectImage.h"




using namespace FW;

CUITextBox::CUITextBox(const char* pszName, CConstruct* pHost) :
	CUI(pszName, pHost, EUITYPE::UI_TEXTBOX), m_pTxtField(nullptr)
{
	m_vtRnd.clear();
}


CUITextBox::~CUITextBox()
{
	Destroy();
}


bool CUITextBox::Create(SRECT& block, float fDist2Cam, const char* pszNameFileMatl, const char* pszNameMatl)
{
	if (!CUI::Create(block, fDist2Cam, pszNameFileMatl, pszNameMatl))
	{
		return false;
	}

	return CreateTextField("Hollow World! Great job!", block, fDist2Cam, 1.0f);
}



bool CUITextBox::CreateTextField(const char* pszContent, SRECT& block, float fDist2Cam, float step)
{
	m_pTxtField = new CTextField;
	if (!m_pTxtField->Create(block.x, block.y, fDist2Cam, 200.0f, 180.0f, pszContent, step))
	{
		return false;
	}


	//fill m_vtRectImg...
	const int SIZE = 64;
	char nameRnd[SIZE];


	CRectImage* pRImg = nullptr;
	CChar* pChar = nullptr;
	URect rUV;


	char c;
	for (int i = 0; i < m_pTxtField->countChar(); i++)
	{
		pChar = m_pTxtField->getChar(i);

		memset(nameRnd, 0, SIZE);
		c = pChar->value();
		sprintf_s(nameRnd, SIZE, "%sRender", &c);

		CRender* pRndRIG = new CRender(nameRnd, this);
		pRImg = new CRectImage(pRndRIG);

		rUV.fx = pChar->u();
		rUV.fy = pChar->v();
		rUV.fw = pChar->du();
		rUV.fh = pChar->dv();

		if (!pRImg->Create(pChar->local(), pChar->horizon(), pChar->vertical(), "./resources/FontLibrary.mat", "FontLibMatl", &rUV))
		{
			Destroy();
			return false;
		}

		FDWORD idRnd = CIDManager::Instance().ApplyID();
		if (0 == idRnd)
		{
			Destroy();
			return false;
		}

		pRndRIG->setID(idRnd);
		pRndRIG->setComesh(pRImg);
		((CEssety*)host())->AddSubRender(pRndRIG);

		m_vtRnd.push_back(pRndRIG);
	}






	


	return true;
}




//Igonre all messages.
bool CUITextBox::ProcessMsg(CMsgBase& msg)
{
	return false;
}




void CUITextBox::Destroy()
{
	if (nullptr != m_pTxtField)
	{
		delete m_pTxtField;
		m_pTxtField = nullptr;
	}

	for (VTRND_ITER iter = m_vtRnd.begin(); iter != m_vtRnd.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;
		}
	}

	m_vtRnd.clear();
}


