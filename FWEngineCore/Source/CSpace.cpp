#include"CCurve.h"
#include"CBone.h"
#include"CSpace.h"


using namespace FW;




CSpace::CSpace():CConstruct(0, ECONSTRTYPE::CST_SPACE), m_pFrame(0)
{
}

CSpace::~CSpace()
{
	if (0 != m_pFrame)
	{
		delete m_pFrame;
		m_pFrame = 0;
	}
}


void CSpace::Create(Vector3& pos, Vector3& forward, Vector3& up)
{
	m_v4Position = Vector4(pos, 1.0);

	if (0 == m_pFrame)
	{
		m_pFrame = new CFrame;
	}

	m_pFrame->Create(forward, up);
}

bool CSpace::Clone(CSpace& spaceSrc)
{
	if (((0 == m_pFrame) && (0 != spaceSrc.m_pFrame))
		|| ((0 != m_pFrame) && (0 == spaceSrc.m_pFrame)))
	{
		return false;
	}

	if (0 != m_pFrame)
	{
		m_pFrame->Create(spaceSrc.m_pFrame->forward(), spaceSrc.m_pFrame->up());
	}

	m_v4Position = spaceSrc.m_v4Position;

	return true;
}


