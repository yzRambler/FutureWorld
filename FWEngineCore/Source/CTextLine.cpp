#include"CTextLine.h"
#include"CLiteralUnit.h"



using namespace FW;

CTextLine::CTextLine():m_widthLine(-1.0f), m_intervalWord(4.0f)
{
	m_vtLitUnit.clear();
}


CTextLine::~CTextLine()
{
	Destroy();
}



bool CTextLine::Create(float fx, float fy, float fdist, float fStep)
{
	//if (nullptr == pHostCom)
	//{
	//	return false;
	//}


	CLiteralUnit* pLitUnit = 0;
	float offX = 0.0f;
	
	for (VTLTU_ITER iter = m_vtLitUnit.begin(); iter != m_vtLitUnit.end(); ++iter)
	{
		if (!(*iter)->Create(fx + offX, fy, fdist, fStep))
		{
			return false;
		}

		offX += (*iter)->width() + m_intervalWord;
	}


	return true;
}




void CTextLine::Destroy()
{
	for (VTLTU_ITER iter = m_vtLitUnit.begin(); iter != m_vtLitUnit.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtLitUnit.clear();
}