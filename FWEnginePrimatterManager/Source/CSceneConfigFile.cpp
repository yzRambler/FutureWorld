#include"CSceneConfigFile.h"
#include"CSceneAspect.h"
#include"CSceneNodeAspect.h"
#include"CEssetyAspect.h"
#include"CRenderAspect.h"
#include"CCameraAspect.h"
#include"CComeshAspect.h"
#include"CLightAspect.h"
#include"CMeshAspect.h"
#include"CMaterialAspect.h"
#include"CSkinAspect.h"
#include"CAnimationGroupAspect.h"
#include"CSkeletonAnimationAspect.h"
#include"CSkeletonAspect.h"
#include"CSpaceAspect.h"
#include"MathLibrary.h"

using namespace FW;

inline const char* CloneString(const char* pszName)
{
	int len = strlen(pszName);
	char* pszNameCln = new char[len + 1];
	memcpy(pszNameCln, pszName, len);
	pszNameCln[len] = 0;

	return pszNameCln;
}

CSceneConfigFile::CSceneConfigFile(const char* pszName) :CTextFile(pszName), m_pSceneApt(0), m_pJSSoruce(0)
{
}

CSceneConfigFile::CSceneConfigFile(const char* pszName, const char* pszNameFile) :
	CTextFile(pszName, pszNameFile), m_pSceneApt(0), m_pJSSoruce(0)
{
}

CSceneConfigFile::~CSceneConfigFile()
{
	Destroy();
}

bool CSceneConfigFile::Parse()
{
	if (0 == m_pBuffer)
	{
		return false;
	}

	if (0 != m_pSceneApt)
	{
		Destroy();
	}

	m_pJSSoruce = cJSON_Parse(m_pBuffer);
	if (0 == m_pJSSoruce)
	{
		return false;
	}

	if (!CreateSceneAspect(m_pJSSoruce->child))
	{
		return false;
	}

	setState(EFSTATE::PARSE_SUC);

	cJSON_Delete(m_pJSSoruce);
	m_pJSSoruce = 0;

	return true;
}



bool CSceneConfigFile::CreateSceneAspect(cJSON* pJS)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Scene") != 0))
	{
		return false;
	}

	if (0 == m_pSceneApt)
	{
		m_pSceneApt = new CSceneAspect;
	}

	cJSON* pJSSceneCom = pJS->child;

	//while (pJSSceneCom)
	for (cJSON* pJSSceneCom = pJS->child; pJSSceneCom != 0; pJSSceneCom = pJSSceneCom->next)
	{
		if (strcmp(pJSSceneCom->string, "Name") == 0)
		{
			m_pSceneApt->setName(pJSSceneCom->valuestring);
			m_pSceneApt->setNameData(pJSSceneCom->valuestring);

			continue;
		}
		else if (strcmp(pJSSceneCom->string, "TimeOrder") == 0)
		{
			m_pSceneApt->setTimeOrder(pJSSceneCom->valueint);
			continue;
		}
		else if (strcmp(pJSSceneCom->string, "SceneNode") == 0)
		{
			CSceneNodeAspect* pSceneNodeApt = CreateSceneNodeAspect(m_pSceneApt->orderTime(), pJSSceneCom);
			if (0 == pSceneNodeApt)
			{
				delete m_pSceneApt;
				m_pSceneApt = 0;
			}

			CompleteSceneNodeSpace(pSceneNodeApt);

			m_pSceneApt->setRootSceneAptTree(pSceneNodeApt);

			return true;
		}
		else
		{
			break;
		}

	}


	return false;
}



bool CSceneConfigFile::CompleteSceneNodeSpace(CSceneNodeAspect* pSceneNodeApt)
{
	if ((0 == pSceneNodeApt) || ((!pSceneNodeApt->initedSapceLocal()) && (!pSceneNodeApt->initedSpaceWorld())))
	{
		return false;
	}

	CSpaceAspect* pPtWSApt = 0;
	CSpaceAspect* pLocalSpaceApt = (CSpaceAspect*)pSceneNodeApt->spaceLocalAspect();
	CSpaceAspect* pWorldSpaceApt = (CSpaceAspect*)pSceneNodeApt->spaceWorldAspect();

	if (pSceneNodeApt->initedSpaceWorld())  // Only the world space has been initialized.
	{
		if (pSceneNodeApt->parent() == 0)
		{
			pLocalSpaceApt->Create(pWorldSpaceApt->pos(), pWorldSpaceApt->forward(), pWorldSpaceApt->up());
		}
		else
		{
			pPtWSApt = (CSpaceAspect*)((CSceneNodeAspect*)pSceneNodeApt->parent())->spaceWorldAspect();
			Matrix4x4 matLocal = pPtWSApt->matTrans().Inverse() * pWorldSpaceApt->matTrans();
			Vector3 up = matLocal.GetCol(1).v3;
			Vector3 forward = matLocal.GetCol(2).v3;

			//compute pos vector
			Vector3 left = up.Cross(forward);
			Matrix4x4 matRt;
			matRt.Identity();
			matRt.SetColV3AT(0, left);
			matRt.SetColV3AT(1, up);
			matRt.SetRowV3AL(2, forward);
			//matLocal = matLocal * matRt.Inverse();
			matLocal = matLocal * matRt.Transpose();

			Vector3 vp = matLocal.GetRow(3).v3;  //add this row just for compile in linux.
			pLocalSpaceApt->Create(-vp, forward, up);
		}
	}
	else  // Only the local space has been initialized.
	{
		if (!pSceneNodeApt->initedSapceLocal())
		{
			return false;
		}

		if (pSceneNodeApt->parent() == 0)
		{
			pWorldSpaceApt->Create(pLocalSpaceApt->pos(), pLocalSpaceApt->forward(), pLocalSpaceApt->up());
		}
		else
		{
			pPtWSApt = (CSpaceAspect*)((CSceneNodeAspect*)pSceneNodeApt->parent())->spaceWorldAspect();
			pPtWSApt->matTrans().Inverse();

			Vector4 pos;
			pos.SetPos(pLocalSpaceApt->pos());
			pos = Mul4(pos, pPtWSApt->matTrans());

			Vector4 forward;
			forward.SetVector(pLocalSpaceApt->forward());
			forward = Mul4(forward, pPtWSApt->matTrans());

			Vector4 up;
			up.SetVector(pLocalSpaceApt->up());
			up = Mul4(up, pPtWSApt->matTrans());

			pWorldSpaceApt->Create(pos.v3, forward.v3, up.v3);
		}
	}


	CSceneNodeAspect* pSubSceneNodeApt = 0;
	for (int i = 0; i < pSceneNodeApt->countSubNodes(); i++)
	{
		pSubSceneNodeApt = (CSceneNodeAspect*)pSceneNodeApt->subNode(i);
		if (!CompleteSceneNodeSpace(pSubSceneNodeApt))
		{
			return false;
		}
	}

	return true;
}




CSceneNodeAspect* CSceneConfigFile::CreateSceneNodeAspect(int orderTime, cJSON* pJS)
{
	if (0 == pJS)
	{
		return 0;
	}

	CSceneNodeAspect* pSceneNodeApt = new CSceneNodeAspect();
	pSceneNodeApt->Create();

	for (cJSON* pJSSceneNodeCom = pJS->child; pJSSceneNodeCom != 0; pJSSceneNodeCom = pJSSceneNodeCom->next)
	{
		if (strcmp(pJSSceneNodeCom->string, "Name") == 0)
		{
			pSceneNodeApt->setName(pJSSceneNodeCom->valuestring);
			
			continue;
		}
		else if (strcmp(pJSSceneNodeCom->string, "SpaceOrder") == 0)
		{
			pSceneNodeApt->GeneralSpaceTimeID(pJSSceneNodeCom->valueint, orderTime);
			continue;
		}
		else if (strcmp(pJSSceneNodeCom->string, "SpaceWorld") == 0)
		{
			InitializeSpaceAspect(pJSSceneNodeCom, (CSpaceAspect&)*pSceneNodeApt->spaceWorldAspect());
			pSceneNodeApt->setSignSpaceWorld(true);

			continue;
		}
		else if (strcmp(pJSSceneNodeCom->string, "SpaceLocal") == 0)
		{
			InitializeSpaceAspect(pJSSceneNodeCom, (CSpaceAspect&)*pSceneNodeApt->spaceLocalAspect());
			pSceneNodeApt->setSignSpaceLocal(true);

			continue;
		}
		//No CConstruct object attached to CSceneNode obj, No "Construct" field in correlated "SceneNode" field
		//in scene file. 
		else if (strcmp(pJSSceneNodeCom->string, "Construct") == 0)
		{
			CAspect* pConstructApt = CreateConstructAspect(pSceneNodeApt, pJSSceneNodeCom);
			if (0 == pConstructApt)
			{
				return 0;
			}

			pSceneNodeApt->AttachConstructAspect(pConstructApt);
			continue;

		}
		else if (strcmp(pJSSceneNodeCom->string, "Children") == 0)
		{
			cJSON* pJSSceneNodeArrayItem = pJSSceneNodeCom->child;
			while (pJSSceneNodeArrayItem)
			{
				cJSON* pJSSceneNodeArrayItemSub = pJSSceneNodeArrayItem->child;
				if (strcmp(pJSSceneNodeArrayItemSub->string, "SceneNode") != 0)
				{
					return 0;
				}

				CSceneNodeAspect* pSubSceneNodeApt = CreateSceneNodeAspect(orderTime, pJSSceneNodeArrayItemSub);
				if (pSubSceneNodeApt == 0)
				{
					return 0;
				}

				pSubSceneNodeApt->SetParent(pSceneNodeApt);
				pSceneNodeApt->AttachChild(pSubSceneNodeApt);

				pJSSceneNodeArrayItem = pJSSceneNodeArrayItem->next;
			}

			continue;
		}
		else
		{
			return 0;
		}

	}

	return pSceneNodeApt;
}




CAspect* CSceneConfigFile::CreateConstructAspect(CAspect* pHostApt, cJSON* pJS)
{
	if ((0 == pJS) || (0 == pHostApt))
	{
		return 0;
	}

	cJSON* pJSConstructCom = 0;

	//create specified object.
	CAspect* pAspect = 0;
	for (pJSConstructCom = pJS->child; pJSConstructCom != 0; pJSConstructCom = pJSConstructCom->next)
	{
		if (strcmp(pJSConstructCom->string, "Class") == 0)
		{
			if (strcmp(pJSConstructCom->valuestring, "Essety") == 0)
			{
				pAspect = new CEssetyAspect(pHostApt);
				pAspect->setTypeApt(EAPTTYPE::CST_ESSETY);
			}
		}

	}


	if (nullptr == pAspect)
	{
		return nullptr;
	}


	//get uniform data
	for (pJSConstructCom = pJS->child; pJSConstructCom != 0; pJSConstructCom = pJSConstructCom->next)
	{
		if (strcmp(pJSConstructCom->string, "Name") == 0)
		{
			pAspect->setName(pJSConstructCom->valuestring);
			continue;
		}
	}


	//get peculiar information
	pJSConstructCom = pJS->child;
	switch (pAspect->typeApt())
	{
	/*
	case EAPTTYPE::CST_CAMERA:
	{
		if (!InitializeCameraAspect(pJSConstructCom, (CCameraAspect*)pAspect))
		{
			delete pAspect;
			return 0;
		}
	}
	break;

	case EAPTTYPE::CST_LIGHT:
	{
		if (!InitializeLightAspect(pJSConstructCom, (CLightAspect*)pAspect))
		{
			delete pAspect;
			return 0;
		}
	}
	break;
	*/

	case EAPTTYPE::CST_ESSETY:
	{
		if (!InitializeEssetyAspect(pJSConstructCom, (CEssetyAspect*)pAspect))
		{
			delete pAspect;
			return 0;
		}
	}
	break;

	default:
	{
		return 0;
	}
	break;
	}


	return pAspect;
}






CComponentAspect* CSceneConfigFile::CreateEssetyComponentAspect(cJSON* pJS, CEssetyAspect* pComHost)
{
	for (cJSON* pItemComJS = pJS->child; pItemComJS != 0; pItemComJS = pItemComJS->next)
	{
		if (strcmp(pItemComJS->string, "Class") == 0)
		{
			if (strcmp(pItemComJS->valuestring, "Render") == 0)
			{
				CRenderAspect* pRenderApt = CreateRenderAspectInCom(pJS, pComHost);
				if (0 == pRenderApt)
				{
					return 0;
				}

				return pRenderApt;
			}
			else if (strcmp(pItemComJS->valuestring, "AnimationGroup") == 0)
			{
				CAnimationGroupAspect* pAniGroupApt = CreateAnimationGroupAspectInCom(pJS, pComHost);
				if (0 == pAniGroupApt)
				{
					return 0;
				}

				return pAniGroupApt;
			}
			else if (strcmp(pItemComJS->valuestring, "Camera") == 0)
			{
				CCameraAspect* pCamApt = CreateCameraAspectInCom(pJS, pComHost);
				if (0 == pCamApt)
				{
					return 0;
				}

				return pCamApt;
			}
			else if (strcmp(pItemComJS->valuestring, "Light") == 0)
			{
				CLightAspect* pLightApt = CreateLightAspectInCom(pJS, pComHost);
				if (0 == pLightApt)
				{
					return 0;
				}

				return pLightApt;
			}
		}
	}


	return 0;
}



CCameraAspect* CSceneConfigFile::CreateCameraAspectInCom(cJSON* pJS, CEssetyAspect* pComHost)
{
	if (0 == pJS)
	{
		return 0;
	}

	CCameraAspect* pCamApt = new CCameraAspect(0, pComHost);
	pCamApt->Create();

	cJSON* pJSCameraCom = pJS->child;
	if (!InitializeCameraAspect(pJSCameraCom, pCamApt))
	{
		delete pCamApt;
		return 0;
	}

	return pCamApt;
}



CLightAspect* CSceneConfigFile::CreateLightAspectInCom(cJSON* pJS, CEssetyAspect* pComHost)
{
	CLightAspect* pLightApt = new CLightAspect(0, pComHost);
	pLightApt->Create(m_pSceneApt->orderTime());
	
	cJSON* pJSLightCom = pJS->child;
	if (!InitializeLightAspect(pJSLightCom, pLightApt))
	{
		delete pLightApt;
		return 0;
	}

	return pLightApt;
}



CRenderAspect* CSceneConfigFile::CreateRenderAspectInCom(cJSON* pJS, CEssetyAspect* pComHost)
{
	if (0 == pJS)
	{
		return 0;
	}

	CRenderAspect* pRenderApt = new CRenderAspect(0, pComHost);
	cJSON* pJSRenderCom = pJS->child;
	cJSON* pJSComesh = 0;
	while (pJSRenderCom)
	{
		if (strcmp(pJSRenderCom->string, "Name") == 0)
		{
			pRenderApt->setName(pJSRenderCom->valuestring);
		}
		else if (strcmp(pJSRenderCom->string, "Comesh") == 0)
		{
			pJSComesh = pJSRenderCom;
			break;
		}

		pJSRenderCom = pJSRenderCom->next;
	}


	if ((0 == pJSComesh) || (strcmp(pJSComesh->string, "Comesh") != 0))
	{
		delete pRenderApt;
		return 0;
	}


	CMeshAspect* pMeshApt = 0;
	for(cJSON* pJSComeshCom = pJSComesh->child; pJSComeshCom != 0; pJSComeshCom = pJSComeshCom->next)
	{
		if (strcmp(pJSComeshCom->string, "Name") == 0)
		{
			pRenderApt->comeshApt().CloneName(pJSComeshCom->valuestring);
			continue;
		}
		else if (strcmp(pJSComeshCom->string, "NameFile") == 0)
		{
			pRenderApt->comeshApt().CloneFileName(pJSComeshCom->valuestring);
			continue;
		}
		else if (strcmp(pJSComeshCom->string, "SpaceModel") == 0)
		{
			if (!InitializeSpaceAspect(pJSComeshCom, *pRenderApt->comeshApt().spaceApt()))
			{
				return 0;
			}
			continue;
		}
		else if (strcmp(pJSComeshCom->string, "Meshes") == 0)
		{
			cJSON* pJSMesh = pJSComeshCom->child;
			while (pJSMesh)
			{
				pMeshApt = CreateMeshAspect(pJSMesh, &pRenderApt->comeshApt());
				if (0 == pMeshApt)
				{
					delete pRenderApt;
					return 0;
				}
				pRenderApt->comeshApt().AddMeshAspect(pMeshApt);

				pJSMesh = pJSMesh->next;
			}
		}


		//pJSComeshCom = pJSComeshCom->next;
	}

	return pRenderApt;
}



CRenderAspect* CSceneConfigFile::CreateRenderAspect(cJSON* pJS, CEssetyAspect* pComHost)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Render") != 0))
	{
		return 0;
	}

	CRenderAspect* pRenderApt = new CRenderAspect(0, pComHost);
	cJSON* pJSRenderCom = pJS->child;
	cJSON* pJSComesh = 0;
	while (pJSRenderCom)
	{
		if (strcmp(pJSRenderCom->string, "Name") == 0)
		{
			pRenderApt->setName(pJSRenderCom->valuestring);
		}
		else if (strcmp(pJSRenderCom->string, "Comesh") == 0)
		{
			pJSComesh = pJSRenderCom;
			break;
		}

		pJSRenderCom = pJSRenderCom->next;
	}


	if ((0 == pJSComesh) || (strcmp(pJSComesh->string, "Comesh") != 0))
	{
		delete pRenderApt;
		return 0;
	}


	CMeshAspect* pMeshApt = 0;
	cJSON* pJSComeshCom = pJSComesh->child;
	while (pJSComeshCom)
	{
		if (strcmp(pJSComeshCom->string, "Name") == 0)
		{
			pRenderApt->comeshApt().CloneName(pJSComeshCom->valuestring);
		}
		else if (strcmp(pJSComeshCom->string, "NameFile") == 0)
		{
			pRenderApt->comeshApt().CloneFileName(pJSComeshCom->valuestring);
		}
		else if (strcmp(pJSComeshCom->string, "Meshes") == 0)
		{
			cJSON* pJSMesh = pJSComeshCom->child;
			while (pJSMesh)
			{
				pMeshApt = CreateMeshAspect(pJSMesh, &pRenderApt->comeshApt());
				if (0 == pMeshApt)
				{
					delete pRenderApt;
					return 0;
				}
				pRenderApt->comeshApt().AddMeshAspect(pMeshApt);

				pJSMesh = pJSMesh->next;
			}
		}


		pJSComeshCom = pJSComeshCom->next;
	}

	return pRenderApt;
}


CMeshAspect* CSceneConfigFile::CreateMeshAspect(cJSON* pJS, CComeshAspect* pHost)
{
	if (0 == pJS)
	{
		return 0;
	}

	CMeshAspect* pMeshApt = new CMeshAspect(pHost);
	for (cJSON* pJSMeshCom = pJS->child; pJSMeshCom != 0; pJSMeshCom = pJSMeshCom->next)
	{
		if (strcmp(pJSMeshCom->string, "Name") == 0)
		{
			pMeshApt->CloneName(pJSMeshCom->valuestring);
			continue;
		}
		else if (strcmp(pJSMeshCom->string, "NameFile") == 0)
		{
			pMeshApt->CloneFileName(pJSMeshCom->valuestring);
			continue;
		}
		else if (strcmp(pJSMeshCom->string, "Material") == 0)
		{
			CMaterialAspect* pMatlApt = CreateMaterialAspect(pJSMeshCom);
			if (0 == pMatlApt)
			{
				delete pMeshApt;
				return 0;
			}

			pMeshApt->setMaterialAspect(pMatlApt);
			continue;
		}
		else if (strcmp(pJSMeshCom->string, "Skin") == 0)
		{
			CSkinAspect* pSkinApt = CreateSkinAspect(pJSMeshCom, pMeshApt);
			if (0 == pSkinApt)
			{
				delete pMeshApt;
				return 0;
			}

			pMeshApt->setDeformerAspect(pSkinApt);
			continue;
		}

	}

	return pMeshApt;
}


CMaterialAspect* CSceneConfigFile::CreateMaterialAspect(cJSON* pJS)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Material") != 0))
	{
		return 0;
	}

	CMaterialAspect* pMatlApt = new CMaterialAspect;
	cJSON* pJSMatlCom = pJS->child;
	while (pJSMatlCom)
	{
		if (strcmp(pJSMatlCom->string, "Name") == 0)
		{
			pMatlApt->CloneName(pJSMatlCom->valuestring);
		}
		else if (strcmp(pJSMatlCom->string, "NameFile") == 0)
		{
			pMatlApt->CloneFileName(pJSMatlCom->valuestring);
		}

		pJSMatlCom = pJSMatlCom->next;
	}

	return pMatlApt;
}


CSkinAspect* CSceneConfigFile::CreateSkinAspect(cJSON* pJS, CMeshAspect* pHost)
{
	if ((0 == pJS) || (0 == pHost) || (strcmp(pJS->string, "Skin") != 0))
	{
		return 0;
	}

	CSkinAspect* pSkinApt = new CSkinAspect(pHost);
	for (cJSON* pJSSkinCom = pJS->child; pJSSkinCom != 0; pJSSkinCom = pJSSkinCom->next)
	{
		if (strcmp(pJSSkinCom->string, "Name") == 0)
		{
			pSkinApt->CloneName(pJSSkinCom->valuestring);
		}
		else if (strcmp(pJSSkinCom->string, "NameFile") == 0)
		{
			pSkinApt->CloneFileName(pJSSkinCom->valuestring);
		}
		else if (strcmp(pJSSkinCom->string, "NameSkeleton") == 0)
		{
			pSkinApt->setSkeletonName(pJSSkinCom->valuestring);
		}

	}

	return pSkinApt;

}



CAnimationGroupAspect* CSceneConfigFile::CreateAnimationGroupAspectInCom(cJSON* pJS, CEssetyAspect* pComHost)
{
	if (0 == pJS)
	{
		return 0;
	}

	CAnimationGroupAspect* pAniGroupApt = new CAnimationGroupAspect(0, pComHost);
	cJSON* pJSAniGroupCom = pJS->child;
	while (pJSAniGroupCom)
	{
		if (strcmp(pJSAniGroupCom->string, "Name") == 0)
		{
			pAniGroupApt->setName(pJSAniGroupCom->valuestring);
		}
		else if (strcmp(pJSAniGroupCom->string, "NameFile") == 0)
		{
			pAniGroupApt->CloneFileName(pJSAniGroupCom->valuestring);
		}
		else if (strcmp(pJSAniGroupCom->string, "Animation") == 0)
		{
			CAnimationAspect* pAniApt = CreateAnimationAspect(pJSAniGroupCom);
			if (0 == pAniApt)
			{
				delete pAniGroupApt;
				return 0;
			}

			pAniGroupApt->AddAnimationAspect(pAniApt);
			pAniGroupApt->setCurrentAniAspect(pAniApt->name());
		}

		pJSAniGroupCom = pJSAniGroupCom->next;
	}

	return pAniGroupApt;
}



CAnimationGroupAspect* CSceneConfigFile::CreateAnimationGroupAspect(cJSON* pJS, CEssetyAspect* pComHost)
{
	if ((0 == pJS) || (strcmp(pJS->string, "AnimationGroup") != 0))
	{
		return 0;
	}

	CAnimationGroupAspect* pAniGroupApt = new CAnimationGroupAspect(0, pComHost);
	cJSON* pJSAniGroupCom = pJS->child;
	while (pJSAniGroupCom)
	{
		if (strcmp(pJSAniGroupCom->string, "Name") == 0)
		{
			pAniGroupApt->setName(pJSAniGroupCom->valuestring);
		}
		else if (strcmp(pJSAniGroupCom->string, "NameFile") == 0)
		{
			pAniGroupApt->CloneFileName(pJSAniGroupCom->valuestring);
		}
		else if (strcmp(pJSAniGroupCom->string, "Animation") == 0)
		{
			CAnimationAspect* pAniApt = CreateAnimationAspect(pJSAniGroupCom);
			if (0 == pAniApt)
			{
				delete pAniGroupApt;
				return 0;
			}

			pAniGroupApt->AddAnimationAspect(pAniApt);
			pAniGroupApt->setCurrentAniAspect(pAniApt->name());
		}

		pJSAniGroupCom = pJSAniGroupCom->next;
	}

	return pAniGroupApt;
}


CAnimationAspect* CSceneConfigFile::CreateAnimationAspect(cJSON* pJS)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Animation") != 0))
	{
		return 0;
	}

	CSkeletonAnimationAspect* pSkAniApt = new CSkeletonAnimationAspect;
	cJSON* pJSAniCom = pJS->child;
	while (pJSAniCom)
	{
		if (strcmp(pJSAniCom->string, "Name") == 0)
		{
			pSkAniApt->CloneName(pJSAniCom->valuestring);
		}
		else if (strcmp(pJSAniCom->string, "NameFile") == 0)
		{
			pSkAniApt->CloneFileName(pJSAniCom->valuestring);
		}
		else if (strcmp(pJSAniCom->string, "Skeleton") == 0)
		{
			CSkeletonAspect* pSkApt = CreateSkeletonAspect(pJSAniCom);
			if (0 == pSkApt)
			{
				delete pSkAniApt;
				return 0;
			}

			pSkAniApt->setSkeletonAspect(pSkApt);
		}

		pJSAniCom = pJSAniCom->next;
	}

	return pSkAniApt;

}

CSkeletonAspect* CSceneConfigFile::CreateSkeletonAspect(cJSON* pJS)
{
	if ((0 == pJS) || (strcmp(pJS->string, "Skeleton") != 0))
	{
		return 0;
	}

	CSkeletonAspect* pSkApt = new CSkeletonAspect;
	cJSON* pJSSkAptCom = pJS->child;
	while (pJSSkAptCom)
	{
		if (strcmp(pJSSkAptCom->string, "Name") == 0)
		{
			pSkApt->CloneName(pJSSkAptCom->valuestring);
		}
		else if (strcmp(pJSSkAptCom->string, "NameFile") == 0)
		{
			pSkApt->CloneFileName(pJSSkAptCom->valuestring);
		}

		pJSSkAptCom = pJSSkAptCom->next;
	}

	return pSkApt;
}



bool CSceneConfigFile::InitializeEssetyAspect(cJSON* pJS, CEssetyAspect* pEssetyApt)
{
	if ((0 == pJS) || (0 == pEssetyApt))
	{
		return false;
	}


	for (cJSON* pItemJS = pJS; pItemJS != 0; pItemJS = pItemJS->next)
	{
		if (strcmp(pItemJS->string, "Component") != 0)
		{
			continue;
		}

		for (cJSON* pComJS = pItemJS->child; pComJS != 0; pComJS = pComJS->next)
		{
			CComponentAspect* pComApt = CreateEssetyComponentAspect(pComJS, pEssetyApt);
			if (0 == pComApt)
			{
				return false;
			}

			pEssetyApt->AddComponentAspect(pComApt);

		}

	}


	return true;


}




bool CSceneConfigFile::InitializeLightAspect(cJSON* pJS, CLightAspect* pLightApt)
{
	if ((0 == pJS) || (0 == pLightApt))
	{
		return false;
	}

	for (cJSON* pJSLightCom = pJS; pJSLightCom != 0; pJSLightCom = pJSLightCom->next)
	{
		if (strcmp(pJSLightCom->string, "Name") == 0)
		{
			pLightApt->setName(pJSLightCom->valuestring);
			continue;
		}
		else if (strcmp(pJSLightCom->string, "TargetSpaceOrder") == 0)
		{
			pLightApt->setTargetSpaceOrder(pJSLightCom->valueint);
			continue;
		}
		else if (strcmp(pJSLightCom->string, "LitType") == 0)
		{
			if (strcmp(pJSLightCom->valuestring, "Point") == 0)
			{
				pLightApt->setLightType(ELITTYPE::LT_POINT);
			}
			else if (strcmp(pJSLightCom->valuestring, "Direct") == 0)
			{
				pLightApt->setLightType(ELITTYPE::LT_DIRECT);
			}
			else if (strcmp(pJSLightCom->valuestring, "Spot") == 0)
			{
				pLightApt->setLightType(ELITTYPE::LT_SPOT);
			}

			continue;
		}
		else if (strcmp(pJSLightCom->string, "Intensity") == 0)
		{
			pLightApt->setIntensity(pJSLightCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSLightCom->string, "Color") == 0)
		{
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;
			float a = 0.0f;
			for (cJSON* pJSLightComPart = pJSLightCom->child; pJSLightComPart != 0;
				pJSLightComPart = pJSLightComPart->next)
			{
				if (strcmp(pJSLightComPart->string, "r") == 0)
				{
					r = pJSLightComPart->valuedouble;
					continue;
				}
				else if (strcmp(pJSLightComPart->string, "g") == 0)
				{
					g = pJSLightComPart->valuedouble;
					continue;
				}
				else if (strcmp(pJSLightComPart->string, "b") == 0)
				{
					b = pJSLightComPart->valuedouble;
					continue;
				}
				else if (strcmp(pJSLightComPart->string, "a") == 0)
				{
					a = pJSLightComPart->valuedouble;
					continue;
				}

			}

			pLightApt->setColor(r, g, b, a);

			continue;
		}

	}


	pLightApt->GenerateSpaceTimeID();

	return true;
}



bool CSceneConfigFile::InitializeCameraAspect(cJSON* pJS, CCameraAspect* pCameraApt)
{
	if ((0 == pJS) || (0 == pCameraApt))
	{
		return false;
	}

	for (cJSON* pJSConstructCom = pJS; pJSConstructCom != 0; pJSConstructCom = pJSConstructCom->next)
	{
		if (strcmp(pJSConstructCom->string, "Name") == 0)
		{
			pCameraApt->setName(pJSConstructCom->valuestring);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Type") == 0)
		{
			if (strcmp(pJSConstructCom->valuestring, "Orthogra") == 0)
			{
				pCameraApt->setCamType(ECAMERATYPE::CAM_ORTHOGRA);
			}
			else if (strcmp(pJSConstructCom->valuestring, "Perspect") == 0)
			{
				pCameraApt->setCamType(ECAMERATYPE::CAM_PERSPECT);
			}
		}
		else if (strcmp(pJSConstructCom->string, "TargetSpaceOrder") == 0)
		{
			pCameraApt->setTargetSpaceOrder(pJSConstructCom->valueint);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "TargetTimeOrder") == 0)
		{
			pCameraApt->setTargetTimeOrder(pJSConstructCom->valueint);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "TargetScreenID") == 0)
		{
			pCameraApt->setTargetScreenID(pJSConstructCom->valueint);
			continue;
		}

		else if (strcmp(pJSConstructCom->string, "AspectRatio") == 0)
		{
			pCameraApt->setAspectRation(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "FOV") == 0)
		{
			pCameraApt->setFOV(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Near") == 0)
		{
			pCameraApt->setNear(pJSConstructCom->valuedouble);
			continue;
		}
		if (strcmp(pJSConstructCom->string, "Far") == 0)
		{
			pCameraApt->setFar(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "ViewPort") == 0)
		{
			float fx = 0.0;
			float fy = 0.0;
			float fw = 0.0;
			float fh = 0.0;
			for (cJSON* pJSViewPortCom = pJSConstructCom->child; pJSViewPortCom != 0;
				pJSViewPortCom = pJSViewPortCom->next)
			{
				if (strcmp(pJSViewPortCom->string, "X") == 0)
				{
					fx = pJSViewPortCom->valuedouble;
				}
				else if (strcmp(pJSViewPortCom->string, "Y") == 0)
				{
					fy = pJSViewPortCom->valuedouble;
				}
				else if (strcmp(pJSViewPortCom->string, "W") == 0)
				{
					fw = pJSViewPortCom->valuedouble;
					continue;
				}
				else if (strcmp(pJSViewPortCom->string, "H") == 0)
				{
					fh = pJSViewPortCom->valuedouble;
					continue;
				}

			}

			pCameraApt->setViewPort(fx, fy, fw, fh);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Enable") == 0)
		{
			cJSON* pJSEnableArrayItem = pJSConstructCom->child;
			while (pJSEnableArrayItem)
			{
				//check input value.
				if (strcmp(pJSEnableArrayItem->valuestring, "Depth") != 0)
				{
					if (strcmp(pJSEnableArrayItem->valuestring, "Stencil") != 0)
					{
						if (strcmp(pJSEnableArrayItem->valuestring, "Blend") != 0)
						{
							return false;
						}
					}
				}

				pCameraApt->AddEnableOption(pJSEnableArrayItem->valuestring);

				pJSEnableArrayItem = pJSEnableArrayItem->next;
			}

			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Disable") == 0)
		{
			cJSON* pJSDisableArrayItem = pJSConstructCom->child;
			while (pJSDisableArrayItem)
			{
				//check input value.
				if (strcmp(pJSDisableArrayItem->valuestring, "Depth") != 0)
				{
					if (strcmp(pJSDisableArrayItem->valuestring, "Stencil") != 0)
					{
						if (strcmp(pJSDisableArrayItem->valuestring, "Blend") != 0)
						{
							return false;
						}
					}
				}


				pCameraApt->AddDisableOption(pJSDisableArrayItem->valuestring);
				pJSDisableArrayItem = pJSDisableArrayItem->next;
			}

			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Clear") == 0)
		{
			cJSON* pJSClearArrayItem = pJSConstructCom->child;
			while (pJSClearArrayItem)
			{
				//check input value.
				if (strcmp(pJSClearArrayItem->valuestring, "Depth") != 0)
				{
					if (strcmp(pJSClearArrayItem->valuestring, "Stencil") != 0)
					{
						if (strcmp(pJSClearArrayItem->valuestring, "Color") != 0)
						{
							return false;
						}
					}
				}

				pCameraApt->AddClearOption(pJSClearArrayItem->valuestring);
				pJSClearArrayItem = pJSClearArrayItem->next;
			}

			continue;
		}
		else if (strcmp(pJSConstructCom->string, "ClearColor") == 0)
		{
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;
			float a = 0.0f;



			//while (pJSClearColorArrayItem)
			for (cJSON* pJSClearColorCom = pJSConstructCom->child; pJSClearColorCom != 0;
				pJSClearColorCom = pJSClearColorCom->next)
			{
				//check input value.
				if (strcmp(pJSClearColorCom->string, "r") == 0)
				{
					r = pJSClearColorCom->valuedouble;
					continue;
				}
				else if (strcmp(pJSClearColorCom->string, "g") == 0)
				{
					g = pJSClearColorCom->valuedouble;
					continue;
				}
				else if (strcmp(pJSClearColorCom->string, "b") == 0)
				{
					b = pJSClearColorCom->valuedouble;
					continue;
				}
				else if (strcmp(pJSClearColorCom->string, "a") == 0)
				{
					a = pJSClearColorCom->valuedouble;
					continue;
				}

			}

			pCameraApt->setClearColorValue(r, g, b, a);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "ClearStencil") == 0)
		{
			pCameraApt->setClearDepthValue(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "ClearDepth") == 0)
		{
			pCameraApt->setClearStencilValue(pJSConstructCom->valueint);
			continue;
		}


	}

	pCameraApt->GenerateSpaceTimeID();


	return true;
}



bool CSceneConfigFile::InitializeSpaceAspect(cJSON* pJS, CSpaceAspect& rSpaceApt)
{
	if (0 == pJS)
	{
		return false;
	}

	Vector3 pos;
	Vector3 forward;
	Vector3 up;

	Vector3 v3;
	for(cJSON* pSubJS = pJS->child; pSubJS != 0; pSubJS = pSubJS->next)
	{
		v3 = CreateVector3(pSubJS);

		if (strcmp(pSubJS->string, "Pos") == 0)
		{
			pos = v3;
			continue;
		}
		else if (strcmp(pSubJS->string, "Forward") == 0)
		{
			forward = v3;
			continue;
		}
		else if (strcmp(pSubJS->string, "Up") == 0)
		{
			up = v3;
		}

	}

	rSpaceApt.Create(pos, forward, up);

	return true;
}



Vector3 CSceneConfigFile::CreateVector3(cJSON* pJS)
{
	Vector3 v3;
	cJSON* pCom = pJS->child;
	while (pCom != 0)
	{
		if (strcmp(pCom->string, "x") == 0)
		{
			v3.x = pCom->valuedouble;
		}
		else if (strcmp(pCom->string, "y") == 0)
		{
			v3.y = pCom->valuedouble;
		}
		else if (strcmp(pCom->string, "z") == 0)
		{
			v3.z = pCom->valuedouble;
		}

		pCom = pCom->next;
	}

	return v3;
}


void CSceneConfigFile::Destroy()
{
	if (0 != m_pSceneApt)
	{
		delete m_pSceneApt;
		m_pSceneApt = 0;
	}

	if (0 != m_pJSSoruce)
	{
		cJSON_Delete(m_pJSSoruce);
	}
}