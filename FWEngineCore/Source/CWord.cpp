#include"CWord.h"
#include"CFontLibrary.h"



using namespace FW;


CWord::CWord():m_fInterval(0.1f), m_fWidthWord(0.0f), m_fHightWord(0.0f)
{
	m_vtChar.clear();
}


CWord::~CWord()
{
	Destroy();
}



bool CWord::Start(char* pString, int len)
{
	if (0 == pString)
	{
		return false;
	}


	char* pWork = pString;
	CChar* pChar = 0;
	for (int i = 0; i < len; i++)
	{
		pChar = new CChar(*(pWork+i));
		//pChar->Initialize();
		pChar->Start();

		m_fWidthWord += pChar->width(); 
		m_fHightWord = m_fHightWord < pChar->height() ? pChar->height() : m_fHightWord;

		m_vtChar.push_back(pChar);
	}

	m_fWidthWord += m_fInterval * (len - 1);

	return true;
}


bool CWord::Create(float fx, float fy, float fdist, float fStep)
{
	float offX = 0;
	for (VTCHR_ITER iter = m_vtChar.begin(); iter != m_vtChar.end(); ++iter)
	{
		if (!(*iter)->Create(fx + offX, fy, fdist, fStep))
		{
			return false;
		}

		offX += (*iter)->width() + m_fInterval;
	}

	return true;
}




void CWord::Destroy()
{
	for (VTCHR_ITER iter = m_vtChar.begin(); iter != m_vtChar.end(); ++iter)
	{
		if (0 != *iter)
		{
			delete *iter;
		}
	}

	m_vtChar.clear();
}