#include"CTextField.h"
#include"CTextLine.h"
#include"CChar.h"
#include"CWord.h"



using namespace FW;

CTextField::CTextField(): m_fIntervalLine(3.0f), m_fWidth(0.0f), m_fHeight(0.0f), m_fX(0.0f), m_fY(0.0f),
m_fOffX(45.0f), m_fOffY(60.0f)
{
	m_vtTextLine.clear();
	m_vtLtUnit.clear();
	m_vtChar.clear();
}

CTextField::~CTextField()
{
	Destroy();
}



bool CTextField::Create(float x, float y, float fdist, float w, float h, 
	const char* pszString, float fStep)
{
	if ((w <= 0.0f) || (h <= 0.0f) || (nullptr == pszString))
	{
		return false;
	}

	m_fX = x + m_fOffX;
	m_fY = y + m_fOffY;
	m_fWidth = w;
	m_fHeight = h;

	if (!Parse(pszString))
	{
		Destroy();

		return false;
	}

	//split into several rows
	CTextLine* pTxL = new CTextLine;
	for (VTLTU_ITER iter = m_vtLtUnit.begin(); iter != m_vtLtUnit.end(); ++iter)
	{
		if (pTxL->width() + (*iter)->width() > m_fWidth)
		{
			m_vtTextLine.push_back(pTxL);

			pTxL = new CTextLine;
			pTxL->AddLiterUnit(*iter);
		}
		else
		{
			pTxL->AddLiterUnit(*iter);
		}
	}
	m_vtTextLine.push_back(pTxL);


	//Generate literal plane in the scene
	float offY = 0.0f;
	for (VTTXL_ITER iter = m_vtTextLine.begin(); iter != m_vtTextLine.end(); ++iter)
	{
		if (!(*iter)->Create(m_fX, m_fY + offY, fdist, fStep))
		{
			Destroy();

			return false;
		}

		offY += (*iter)->height() + m_fIntervalLine;
	}



	for (int i = 0; i < m_vtTextLine.size(); i++)
	{
		for (int j = 0; j < m_vtTextLine[i]->countWord(); j++)
		{
			for (int k = 0; k < m_vtTextLine[i]->word(j)->countChar(); k++)
			{
				m_vtChar.push_back(m_vtTextLine[i]->word(j)->getChar(k));
			}
		}
	}



	return true;
}




bool CTextField::Parse(const char* pszText)
{
	int lenText = strlen(pszText);
	char* pWork = (char*)pszText;
	char* pBeg = pWork;
	char* pEnd = pBeg;
	char cSpa = ' ';
	CLiteralUnit* pLtUnit = 0;

	for (int i = 0; i < lenText; i++)
	{
		if (*(pWork + i) == cSpa)
		{
			if (*pBeg != cSpa)
			{
				//create a word and push back.
				CWord* pWord = new CWord;
				pWord->Start(pBeg, pEnd - pBeg + 1);
				pLtUnit = pWord;

				m_vtLtUnit.push_back(pLtUnit);
			}

			pBeg = pEnd = pWork + i;
		}
		else
		{
			pEnd = pWork + i;
			if (*pBeg == cSpa)
			{
				pBeg = pEnd;
			}
		}
	}

	pLtUnit = nullptr;
	
	if ((nullptr != pBeg) && (nullptr != pEnd))
	{
		//create a word
		CWord* pWord = new CWord;
		pWord->Start(pBeg, pEnd - pBeg + 1);
		pLtUnit = pWord;

		m_vtLtUnit.push_back(pLtUnit);
	}


	return true;
}





void CTextField::Destroy()
{
	for (VTTXL_ITER iter = m_vtTextLine.begin(); iter != m_vtTextLine.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete (*iter);
		}
	}

	m_vtTextLine.clear();


	//All literal units have been saved in the CTextline objects in the m_vtTextLine.
	m_vtLtUnit.clear();

	m_vtChar.clear();
}