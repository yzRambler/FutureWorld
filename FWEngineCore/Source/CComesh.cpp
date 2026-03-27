#include"CComesh.h"
#include"CMesh.h"
#include"IDataResource.h"
#include"CMaterialAspect.h"
#include"CMaterial.h"
#include"CSpace.h"
#include"CBox.h"
#include"CIDManager.h"


using namespace FW;

CComesh::CComesh(CConstruct* pHost):CPrimatter(pHost, EPMTTYPE::COMESH)
{
	m_pSpaceModel = new CSpace;
	m_vtSubRender.clear();
	m_vtMesh.clear();
}

CComesh::CComesh(const char* pszName, CConstruct* pHost) :CPrimatter(pszName, 
	pHost, EPMTTYPE::COMESH)
{
	m_pSpaceModel = new CSpace;
	m_vtSubRender.clear();
	m_vtMesh.clear();
}

CComesh::~CComesh()
{
	Destroy();
}

bool CComesh::Initialize(const char* pszName, const char* pszNamePathAndFile)
{
	return CPrimatter::Initialize(pszName, pszNamePathAndFile);
}


void CComesh::AddMesh(CMesh* pMesh)
{
	if (0 == pMesh)
	{
		return;
	}

	CMesh* pMeshIn = 0;
	for (VTMESH_ITER iter = m_vtMesh.begin(); iter != m_vtMesh.end(); ++iter)
	{
		pMeshIn = (*iter)->pMesh;
		if (strcmp(pMeshIn->name(), pMesh->name()) == 0)
		{
			return;
		}
	}

	pMesh->setHost(this);

	SMeshData* pMD = new SMeshData;
	pMD->pMesh = pMesh;
	pMD->id = pMesh->id();

	m_vtMesh.push_back(pMD);
}

void CComesh::DeleteMesh(CMesh* pMesh)
{
	if (nullptr == pMesh)
	{
		return;
	}

	IDataResource* pIDRes = CreateDataResource();
	SMeshData* pMD = nullptr;
	for (VTMESH_ITER iter = m_vtMesh.begin(); iter != m_vtMesh.end(); )
	{
		pMD = *iter;

		if ((pMD->id == pMesh->id()&&(pIDRes->CheckValidRes(pMD->id))))
		{
			delete pMD->pMesh;
			delete pMD;
			m_vtMesh.erase(iter);

			return;
		}

		++iter;
	}
}



void CComesh::Destroy()
{
	CIDManager::Instance().RemoveID(id());

	CleanAllMesh();

	if (nullptr != m_pSpaceModel)
	{
		delete m_pSpaceModel;
		m_pSpaceModel = nullptr;
	}



	for (VTRND_ITER iter = m_vtSubRender.begin(); iter != m_vtSubRender.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete *iter;
		}
	}

	m_vtSubRender.clear();
}




void CComesh::CleanAllMesh()
{
	IDataResource* pIDRes = CreateDataResource();
	for (VTMESH_ITER iter = m_vtMesh.begin(); iter != m_vtMesh.end(); ++iter)
	{
		if ((*iter) == nullptr)
		{
			continue;
		}

		if ((*iter)->pMesh->gen() == EGEN::GE_ORG_PM)
		{
			if (pIDRes->CheckValidRes((*iter)->pMesh->id()))
			{
				delete (*iter)->pMesh;
			}
		}
		else
		{
			delete (*iter)->pMesh;
		}

		delete* iter;
		
	}

	m_vtMesh.clear();
}



CMesh* CComesh::SearchMesh(const char* pszName)
{
	SMeshData* pMD = 0;
	for (VTMESH_ITER iter = m_vtMesh.begin(); iter != m_vtMesh.end(); ++iter)
	{
		pMD = *iter;
		if (strcmp(pMD->pMesh->name(), pszName) == 0)
		{
			return pMD->pMesh;
		}
	}

	return nullptr;
}



void CComesh::Update(CEssety* pEssety)
{
	m_v3MaxMS.Clean();
	m_v3MinMS.Clean();

	CMesh* pMesh = 0;
	for (VTMESH_ITER iter = m_vtMesh.begin(); iter != m_vtMesh.end(); ++iter)
	{
		pMesh = (*iter)->pMesh;
		

		if (nullptr != pMesh)
		{
			pMesh->Update(pEssety);
			for (int i = 0; i < 3; i++)
			{
				m_v3MaxMS.c[i] = m_v3MaxMS.c[i] < pMesh->max().c[i] ? pMesh->max().c[i] : m_v3MaxMS.c[i];
				m_v3MinMS.c[i] = m_v3MinMS.c[i] > pMesh->min().c[i] ? pMesh->min().c[i] : m_v3MinMS.c[i];
			}
		}

		
	}


}