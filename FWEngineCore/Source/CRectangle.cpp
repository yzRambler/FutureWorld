#include"CRectangle.h"
#include"IDataResource.h"
#include"CMaterial.h"
#include"CLineMesh.h"


using namespace FW;


CRectangle::CRectangle(CConstruct* pHost):CComesh(pHost), m_pRect(nullptr), m_pMatlShare(nullptr)
{
}


CRectangle::CRectangle(const char* pszName, CConstruct* pHost):CComesh(pszName, pHost), m_pRect(nullptr), 
m_pMatlShare(nullptr)
{
}

CRectangle::~CRectangle()
{
}



bool CRectangle::Create(Vector4& ltv, Vector3& offHor, Vector3& offVer, Matrix4x4& matWorld)
{
	if (nullptr == m_pRect)
	{
		m_pRect = new CRect;
	}

	m_pRect->Create(ltv, offHor, offVer);

	UpdateBorderArrayByRect();


	IDataResource* pIDR = CreateDataResource();
	m_pMatlShare = pIDR->TakeMatrial("./resources/DefaultFrame.mat", "DefaultFrame");
	if (nullptr == m_pMatlShare)
	{
		return false;
	}

	m_idMatl = m_pMatlShare->id();
	m_pMatlShare->setRNDGroupOrder(10);



	//Create borders
	CleanAllMesh();
	CLineMesh* pBorder = 0;

	char buffer[16];
	for (int i = 0; i < EBD::BDCOUNT; i++)
	{
		memset(buffer, 0, sizeof(buffer));
		sprintf_s(buffer, "Border%d", i);

		pBorder = new CLineMesh(buffer, this);
		pBorder->Initialize(m_border[i].start, m_border[i].end);
		pBorder->setMaterial(m_pMatlShare);
		pBorder->renderUnit()->matWorld() = matWorld;

		AddMesh(pBorder);

	}


	return true;
}


void CRectangle::Transform(Matrix4x4& mat)
{
	if (nullptr == m_pRect)
	{
		return;
	}

	m_pRect->Transform(mat);
	UpdateBorderArrayByRect();
	SetupBorders();
}


void CRectangle::OnAreaUpdate(Vector4& ltv, Vector3& offHor, Vector3& offVer)
{
	if (nullptr == m_pRect)
	{
		return;
	}

	m_pRect->Update(ltv.v3, offHor, offVer);
	UpdateBorderArrayByRect();
	SetupBorders();
}


void CRectangle::UpdateBorderArrayByRect()
{
	m_border[EBD::_01].start = *m_pRect->vertex(0);
	m_border[EBD::_01].end = *m_pRect->vertex(1);

	m_border[EBD::_12].start = *m_pRect->vertex(1);
	m_border[EBD::_12].end = *m_pRect->vertex(2);

	m_border[EBD::_23].start = *m_pRect->vertex(2);
	m_border[EBD::_23].end = *m_pRect->vertex(3);

	m_border[EBD::_30].start = *m_pRect->vertex(3);
	m_border[EBD::_30].end = *m_pRect->vertex(0);
	
}


void CRectangle::SetupBorders()
{
	CLineMesh* pBorder = nullptr;
	for (int i = 0; i < EBD::BDCOUNT; i++)
	{
		pBorder = (CLineMesh*)mesh(i);
		pBorder->Update(m_border[i].start, m_border[i].end);
	}
}