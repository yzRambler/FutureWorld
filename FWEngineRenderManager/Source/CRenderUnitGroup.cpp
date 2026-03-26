
#include"CRenderUnitGroup.h"
#include"CRenderUnit.h"
#include"CRenderUnitList.h"
#include"CMesh.h"
#include"CMaterial.h"
#include"CCamera.h"
#include"CLight.h"


using namespace FW;

CRenderUnitGroup::CRenderUnitGroup():m_nOrder(-1), m_nOrderCount(-1), m_eRenderType(ERNDTYPE::RT_UNKNOW)
{
	m_vtRenderUnit.clear();
	m_lstSubRenderUtGroup.clear();
}


CRenderUnitGroup::~CRenderUnitGroup()
{
}


void CRenderUnitGroup::Sort(CCamera* pCam)
{
	MergeSort(pCam, 0, m_vtRenderUnit.size() - 1);
}

void CRenderUnitGroup::MergeSort(CCamera* pCam, int indStart, int indEnd)
{
	if (indEnd > indStart)
	{
		float fmd = (indEnd + indStart) * 0.5f;

		MergeSort(pCam, indStart, fmd);
		MergeSort(pCam, fmd + 1.0f, indEnd);

		int indWorkLeft = indStart;
		int md = fmd;
		int indWorkRight = fmd + 1.0f;

		CMesh* pMeshLeft = 0;
		CMesh* pMeshRight = 0;
		Vector3 v3DstLeft;
		Vector3 v3DstRight;
		VTRNDUT vtRUTmp;
		vtRUTmp.clear();
	

		while ((indWorkLeft <= md) && (indWorkRight <= indEnd))
		{
			pMeshLeft = (CMesh*)m_vtRenderUnit[indWorkLeft]->host();
			pMeshRight = (CMesh*)m_vtRenderUnit[indWorkRight]->host();

			v3DstLeft = (Vector3&)pMeshLeft->centerBound() - pCam->pos();
			v3DstRight = (Vector3&)pMeshRight->centerBound() - pCam->pos();

			//The further one will be rendered first.
			float fLeftLen = abs(v3DstLeft.Dot(pCam->forward()));
			float fRightLen = abs(v3DstRight.Dot(pCam->forward()));
			if (fRightLen > fLeftLen)
			{
				vtRUTmp.push_back(m_vtRenderUnit[indWorkRight]);
				indWorkRight++;
			}
			else
			{
				vtRUTmp.push_back(m_vtRenderUnit[indWorkLeft]);
				indWorkLeft++;
			}

		}

		for (int i = indWorkLeft; i <= md; i++)
		{
			vtRUTmp.push_back(m_vtRenderUnit[i]);
		}

		for (int i = indWorkRight; i <= indEnd; i++)
		{
			vtRUTmp.push_back(m_vtRenderUnit[i]);
		}

		//now vtRUTmp.size() == indEnd - indStart + 1 !!
		for (int i = 0; i < vtRUTmp.size(); i++)
		{
			m_vtRenderUnit[indStart + i] = vtRUTmp[i];
		}
	}
}



void CRenderUnitGroup::Sort(const Vector3& v3CameraPos)
{
	MergeSort(v3CameraPos, 0, m_vtRenderUnit.size() - 1);
}

void CRenderUnitGroup::MergeSort(const Vector3& v3CameraPos, int indStart, int indEnd)
{
	if (indEnd > indStart)
	{
		float fmd = (indEnd + indStart)*0.5f;

		MergeSort(v3CameraPos, indStart, fmd);
		MergeSort(v3CameraPos, fmd+1.0f, indEnd);

		int indWorkLeft = indStart;
		int md = fmd;
		int indWorkRight = fmd+1.0f;

		CMesh* pMeshLeft = 0;
		CMesh* pMeshRight = 0;
		Vector3 v3DstLeft;
		Vector3 v3DstRight;
		VTRNDUT vtRUTmp;
		vtRUTmp.clear();

		while ((indWorkLeft <= md)&&(indWorkRight <= indEnd))
		{
			pMeshLeft = (CMesh*)m_vtRenderUnit[indWorkLeft]->host();
			pMeshRight = (CMesh*)m_vtRenderUnit[indWorkRight]->host();

			v3DstLeft = (Vector3&)pMeshLeft->centerBound() - v3CameraPos;
			v3DstRight = (Vector3&)pMeshRight->centerBound() - v3CameraPos;

			//The further one will be rendered first.
			if (v3DstRight.SquareLen() > v3DstLeft.SquareLen())
			{
				vtRUTmp.push_back(m_vtRenderUnit[indWorkRight]);
				indWorkRight++;
			}
			else
			{
				vtRUTmp.push_back(m_vtRenderUnit[indWorkLeft]);
				indWorkLeft++;
			}

		}

		for (int i = indWorkLeft; i <= md; i++)
		{
			vtRUTmp.push_back(m_vtRenderUnit[i]);
		}

		for (int i = indWorkRight; i <= indEnd; i++)
		{
			vtRUTmp.push_back(m_vtRenderUnit[i]);
		}

		//now vtRUTmp.size() == indEnd - indStart + 1 !!
		for (int i = 0; i < vtRUTmp.size(); i++)
		{
			m_vtRenderUnit[indStart + i] = vtRUTmp[i];
		}
	}
}



void CRenderUnitGroup::MergeWithMaterial(CCamera* pCam)
{
	if (m_eRenderType == ERNDTYPE::RT_TRANSPARENT)
	{
		Sort(pCam);

		//Merge meshes with same material in order.
		CRenderUnitList* pRULst = 0;
		for (VTRNDUT_ITER iter = m_vtRenderUnit.begin(); iter != m_vtRenderUnit.end(); ++iter)
		{
			pRULst = GetLastRUList();
			if (0 != pRULst)
			{
				if (pRULst->material()->id() == (*iter)->material()->id())
				{
					pRULst->AddRenderUnit(*iter);
					continue;
				}
			}

			pRULst = new CRenderUnitList();
			pRULst->setMaterial((*iter)->material());
			pRULst->AddRenderUnit(*iter);
			AppendRenderUnitList(pRULst);
		}

	}
	else
	{
		//merge meshes with same material and assign render unit into CRenderUnitList object
		CRenderUnitList* pRndLst = 0;
		CMesh* pMesh = 0;
		for (VTRNDUT_ITER iter = m_vtRenderUnit.begin(); iter != m_vtRenderUnit.end(); ++iter)
		{
			pRndLst = SearchRenderUnitList((*iter)->material()->id());
			if (0 == pRndLst)
			{
				pRndLst = new CRenderUnitList();
				pRndLst->setMaterial((*iter)->material());
				InsertRenderUnitList(pRndLst);
			}

			pRndLst->AddRenderUnit(*iter);
		}
	}
}



void CRenderUnitGroup::MergeWithMaterial(const Vector3& v3PosCamera)
{
   //Sort (from near to far) if in transparent CRenderUnitGroup object.
	if (m_eRenderType == ERNDTYPE::RT_TRANSPARENT)
	{
		Sort(v3PosCamera);

		//Merge meshes with same material in order.
		CRenderUnitList* pRULst = 0;
		for (VTRNDUT_ITER iter = m_vtRenderUnit.begin(); iter != m_vtRenderUnit.end(); ++iter)
		{
			//pMesh = (CMesh*)(*iter);
			pRULst = GetLastRUList();
			if (0 != pRULst)
			{
				if (pRULst->material()->id() == (*iter)->material()->id())
				{
					pRULst->AddRenderUnit(*iter);
					continue;
				}
			}

			pRULst = new CRenderUnitList();
			pRULst->setMaterial((*iter)->material());
			pRULst->AddRenderUnit(*iter);
			AppendRenderUnitList(pRULst);
		}

	}
	else
	{
		//merge meshes with same material and assign render unit into CRenderUnitList object
		CRenderUnitList* pRndLst = 0;
		CMesh* pMesh = 0;
		for (VTRNDUT_ITER iter = m_vtRenderUnit.begin(); iter != m_vtRenderUnit.end(); ++iter)
		{
			pRndLst = SearchRenderUnitList((*iter)->material()->id());
			if (0 == pRndLst)
			{
				pRndLst = new CRenderUnitList();
				pRndLst->setMaterial((*iter)->material());
				InsertRenderUnitList(pRndLst);
			}

			pRndLst->AddRenderUnit(*iter);
		}
	}


}



void CRenderUnitGroup::UpdateCameraLightParameter(CCamera* pCam, VTLIT& vtLights)
{
	for (MAPRULT_ITER iter = m_mapRndUtList.begin(); iter != m_mapRndUtList.end(); ++iter)
	{
		iter->second->UpdateCameraLightParameter(pCam, vtLights);
	}
}




CRenderUnitList* CRenderUnitGroup::SearchRenderUnitList(FDWORD idMatl)
{
	MAPRULT_ITER iter = m_mapRndUtList.find(idMatl);
	if (iter != m_mapRndUtList.end())
	{
		return iter->second;
	}

	return 0;
}



void CRenderUnitGroup::AppendRenderUnitList(CRenderUnitList* pRndUtLst)
{
	m_nOrderCount++;
	m_mapRndUtList[m_nOrderCount] = pRndUtLst;
}



void CRenderUnitGroup::InsertRenderUnitList(CRenderUnitList* pRndUtLst)
{
	if (0 == pRndUtLst)
	{
		return;
	}

	MAPRULT_ITER iter = m_mapRndUtList.find(pRndUtLst->material()->id());
	if (iter == m_mapRndUtList.end())
	{
		m_mapRndUtList[pRndUtLst->material()->id()] = pRndUtLst;
	}
}



void CRenderUnitGroup::Rendering()
{
	for (MAPRULT_ITER iter = m_mapRndUtList.begin(); iter != m_mapRndUtList.end(); ++iter)
	{
		(*iter).second->Rendering();
	}
}


void CRenderUnitGroup::CleanAll()
{
	m_vtRenderUnit.clear();
	ClearRenderUnitList();
}



void CRenderUnitGroup::ClearRenderUnitList()
{
	CRenderUnitList* pRlst = 0;
	for (MAPRULT_ITER iter = m_mapRndUtList.begin(); iter != m_mapRndUtList.end(); ++iter)
	{
		pRlst = iter->second;
		if (0 != pRlst)
		{
			pRlst->Clean();
			delete pRlst;
		}
	}

	m_mapRndUtList.clear();

	m_nOrderCount = -1;
}