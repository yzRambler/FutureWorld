#include"CSpaceAspect.h"


using namespace FW;

CSpaceAspect::CSpaceAspect():m_pFrame(0)
{
	m_v4Position.Clean();
}


CSpaceAspect::~CSpaceAspect()
{
	if (nullptr != m_pFrame)
	{
		delete m_pFrame;
		m_pFrame = nullptr;
	}
}


void CSpaceAspect::Create(Vector3& pos, Vector3& forward, Vector3& up)
{
	m_v4Position = Vector4(pos, 1.0);

	if (0 == m_pFrame)
	{
		m_pFrame = new CFrame;
	}

	m_pFrame->Create(forward, up);

	m_matTrans.Identity();
	m_matTrans.SetRow(3, -m_v4Position);
	m_matTrans = m_matTrans * m_pFrame->matRotation();
}


void CSpaceAspect::Create()
{
	if (0 == m_pFrame)
	{
		m_pFrame = new CFrame;
	}
}



bool CSpaceAspect::Copy(CAspect* pAptSrc)
{
	CSpaceAspect* pSpAptSrc = (CSpaceAspect*)pAptSrc;
	if ((nullptr == pAptSrc) || ((nullptr == m_pFrame) && (nullptr != pSpAptSrc->m_pFrame))
		|| ((nullptr != m_pFrame) && (nullptr == pSpAptSrc->m_pFrame)))
	{
		return false;
	}

	if (!CAspect::Copy(pSpAptSrc))
	{
		return false;
	}

	if (nullptr != m_pFrame)
	{
		m_pFrame->Create(pSpAptSrc->m_pFrame->forward(), pSpAptSrc->m_pFrame->up());
	}


	m_v4Position = pSpAptSrc->m_v4Position;

	return true;
}




bool CSpaceAspect::Clone(CAspect* pAptSrc)
{

	CSpaceAspect* pSpAptSrc = (CSpaceAspect*)pAptSrc;
	if ((nullptr == pAptSrc) ||((nullptr == m_pFrame) && (nullptr != pSpAptSrc->m_pFrame))
		|| ((nullptr != m_pFrame) && (nullptr == pSpAptSrc->m_pFrame)))
	{
		return false;
	}

	if (!CAspect::Clone(pSpAptSrc))
	{
		return false;
	}
	

	if (nullptr != m_pFrame)
	{
		m_pFrame->Create(pSpAptSrc->m_pFrame->forward(), pSpAptSrc->m_pFrame->up());
	}


	m_v4Position = pSpAptSrc->m_v4Position;

	return true;
}