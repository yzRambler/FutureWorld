#include"CChar.h"
#include"CRender.h"
#include"CFontLibrary.h"
#include"CEssety.h"
#include"CSceneNode.h"
#include"ISceneManager.h"
#include"CScene.h"
#include"MathLibrary.h"



using namespace FW;



CChar::CChar(char c):m_char(c), m_fU(0.0f), m_fV(0.0f), m_fWidth(0.0f), m_fHight(0.0f), m_fOffV(0.0f), 
m_fDu(1.0f), m_fDv(1.0f)
{
	for (int i = 0; i < CAC; i++)
	{
		m_aryVt[i] = new Vector4;
	}
}

CChar::~CChar()
{
	Destroy();
}


bool CChar::Start()
{
	CFontLibrary::SCHR* pSC =  CFontLibrary::Instance().InquireChar(m_char);

	m_fU = pSC->u;
	m_fV = pSC->v;
	m_fWidth = pSC->w;
	m_fHight = pSC->h;
	m_fOffV = pSC->offV;


	return true;
}


bool CChar::Create(float fx, float fy, float fdist, float fStep, bool show /*= true*/)
{
	fy += m_fOffV;

	m_aryVt[0]->x = fx;
	m_aryVt[0]->y = fy;
	m_aryVt[0]->z = 0.0f;
	m_aryVt[0]->w = 1.0f;

	m_aryVt[1]->x = fx;
	m_aryVt[1]->y = fy + m_fHight;
	m_aryVt[1]->z = 0.0f;
	m_aryVt[1]->w = 1.0f;

	m_aryVt[2]->x = fx + m_fWidth;
	m_aryVt[2]->y = fy + m_fHight;
	m_aryVt[2]->z = 0.0f;
	m_aryVt[2]->w = 1.0f;

	m_aryVt[3]->x = fx + m_fWidth;
	m_aryVt[3]->y = fy;
	m_aryVt[3]->z = 0.0f;
	m_aryVt[3]->w = 1.0f;



	Matrix4x4& matS2W = CreateSceneManager()->GetCurrentScene()->matSToWByUICam();

	//Obtain the rectangle position
	for (int i = 0; i < 4; i++)
	{
		*m_aryVt[i] = Mul4(*m_aryVt[i], matS2W);
		(*m_aryVt[i]).y = fdist + fStep;
	}

	m_fDu = m_fWidth / CFontLibrary::Instance().width();
	m_fDv = m_fHight / CFontLibrary::Instance().height();

	m_v3Horizon = m_aryVt[1]->v3;
	m_v3Horizon = m_v3Horizon - m_aryVt[0]->v3;

	m_v3Vertical = m_aryVt[3]->v3;
	m_v3Vertical = m_v3Vertical - m_aryVt[0]->v3;


	return true;
}

static int cout = 0;
void CChar::Update(char c)
{

	if (cout < 30)
	{
		cout++;
		return;
	}
	else
	{
		cout = 0;
	}


	m_char = c;

	CFontLibrary::SCHR* pSC = CFontLibrary::Instance().InquireChar(m_char);

	m_fU = pSC->u;
	m_fV = pSC->v;
	m_fWidth = pSC->w;
	m_fHight = pSC->h;
	m_fOffV = pSC->offV;

	m_fDu = m_fWidth / CFontLibrary::Instance().width();
	m_fDv = m_fHight / CFontLibrary::Instance().height();

}


void CChar::Destroy()
{
	for (int i = 0; i < CAC; i++)
	{
		if (nullptr != m_aryVt[i])
		{
			delete m_aryVt[i];
			m_aryVt[i] = nullptr;
		}
	}
}