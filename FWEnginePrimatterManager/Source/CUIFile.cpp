#include"CUIFile.h"
#include"CUITreeAspect.h"
#include"CSceneNodeAspect.h"
#include"CSpaceAspect.h"
#include"CEssetyAspect.h"
#include"CCameraAspect.h"
#include"CUIAspect.h"
#include"CCommandAspect.h"
#include"MathLibrary.h"


using namespace FW;


CUIFile::CUIFile(const char* pszName) : CTextFile(pszName), m_pUITreeApt(nullptr)
{
}


CUIFile::CUIFile(const char* pszName, const char* pszNameFile) : CTextFile(pszName, pszNameFile), m_pUITreeApt(nullptr)
{
}


CUIFile::~CUIFile()
{
}


bool CUIFile::Parse()
{
	if (nullptr == m_pBuffer)
	{
		return false;
	}

	if (nullptr != m_pUITreeApt)
	{
		Destroy();
	}

	m_pJSSource = cJSON_Parse(m_pBuffer);
	if (nullptr == m_pJSSource)
	{
		return false;
	}

	bool result = CreateUITreeAspect(m_pJSSource->child);

	cJSON_Delete(m_pJSSource);
	m_pJSSource = nullptr;

	return result;
}



bool CUIFile::CreateUITreeAspect(cJSON* pJS)
{
	if ((nullptr == pJS) || (strcmp(pJS->string, "UITree") != 0))
	{
		return false;
	}

	if (nullptr == m_pUITreeApt)
	{
		m_pUITreeApt = new CUITreeAspect;
	}

	cJSON* pJSSceneCom = pJS->child;

	for (cJSON* pJSSceneCom = pJS->child; pJSSceneCom != 0; pJSSceneCom = pJSSceneCom->next)
	{
		if (strcmp(pJSSceneCom->string, "Name") == 0)
		{
			m_pUITreeApt->setName(pJSSceneCom->valuestring);
			m_pUITreeApt->setNameData(pJSSceneCom->valuestring);

			continue;
		}
		else if (strcmp(pJSSceneCom->string, "TimeOrder") == 0)
		{
			m_pUITreeApt->setTimeOrder(pJSSceneCom->valueint);
			continue;
		}
		else if (strcmp(pJSSceneCom->string, "SceneNode") == 0)
		{
			CSceneNodeAspect* pSceneNodeApt = CreateSceneNodeAspect(m_pUITreeApt->orderTime(), pJSSceneCom);
			if (nullptr == pSceneNodeApt)
			{
				delete m_pUITreeApt;
				m_pUITreeApt = nullptr;
			}

			CompleteSceneNodeSpace(pSceneNodeApt);

			m_pUITreeApt->setRootUIAptTree(pSceneNodeApt);

		}
		else
		{
			return false;
		}

	}

	setState(EFSTATE::PARSE_SUC);

	return true;
}


CSceneNodeAspect* CUIFile::CreateSceneNodeAspect(int orderTime, cJSON* pJS)
{
	if (nullptr == pJS)
	{
		return nullptr;
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
			if (nullptr == pConstructApt)
			{
				return nullptr;
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
					return nullptr;
				}

				CSceneNodeAspect* pSubSceneNodeApt = CreateSceneNodeAspect(orderTime, pJSSceneNodeArrayItemSub);
				if (pSubSceneNodeApt == nullptr)
				{
					return nullptr;
				}

				pSubSceneNodeApt->SetParent(pSceneNodeApt);
				pSceneNodeApt->AttachChild(pSubSceneNodeApt);

				pJSSceneNodeArrayItem = pJSSceneNodeArrayItem->next;
			}

			continue;
		}
		else
		{
			return nullptr;
		}

	}

	return pSceneNodeApt;
}



CAspect* CUIFile::CreateConstructAspect(CAspect* pHostApt, cJSON* pJS)
{
	if ((nullptr == pJS) || (nullptr == pHostApt))
	{
		return nullptr;
	}

	cJSON* pJSConstructCom = nullptr;

	//create specified object.
	CAspect* pAspect = nullptr;
	for (pJSConstructCom = pJS->child; pJSConstructCom != nullptr; pJSConstructCom = pJSConstructCom->next)
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
	case EAPTTYPE::CST_ESSETY:
	{
		if (!InitializeEssetyAspect(pJSConstructCom, (CEssetyAspect*)pAspect))
		{
			delete pAspect;
			return nullptr;
		}
	}
	break;

	default:
	{
		return nullptr;
	}
	break;
	}


	return pAspect;
}


bool CUIFile::InitializeUIAspect(cJSON* pJS, CUIAspect* pUIApt)
{
	if ((nullptr == pJS) || (nullptr == pUIApt))
	{
		return false;
	}

	CString strType;
	CString strName;
	CString strNameMatl;
	CString strNameMatlFile;
	int targetSOrder = -1;
	float x, y, w, h = 0;

	for (cJSON* pJSConstructCom = pJS; pJSConstructCom != nullptr; pJSConstructCom = pJSConstructCom->next)
	{
		if (strcmp(pJSConstructCom->string, "UIType") == 0)
		{
			strType.Set(pJSConstructCom->valuestring);
		}
		else if(strcmp(pJSConstructCom->string, "Name") == 0)
		{
			strName.Set(pJSConstructCom->valuestring);
		}
		else if (strcmp(pJSConstructCom->string, "TargetSpaceOrder") == 0)
		{
			targetSOrder = pJSConstructCom->valueint;
		}
		else if (strcmp(pJSConstructCom->string, "NameMaterialFile") == 0)
		{
			strNameMatlFile.Set(pJSConstructCom->valuestring);
		}
		else if (strcmp(pJSConstructCom->string, "NameMaterial") == 0)
		{
			strNameMatl.Set(pJSConstructCom->valuestring);
		}
		else if (strcmp(pJSConstructCom->string, "Rect") == 0)
		{
			for (cJSON* pJSRect = pJSConstructCom->child; pJSRect != nullptr; pJSRect = pJSRect->next)
			{
				if (strcmp(pJSRect->string, "x") == 0)
				{
					x = pJSRect->valuedouble;
				}
				else if (strcmp(pJSRect->string, "y") == 0)
				{
					y = pJSRect->valuedouble;
				}
				else if (strcmp(pJSRect->string, "w") == 0)
				{
					w = pJSRect->valuedouble;
				}
				else if (strcmp(pJSRect->string, "h") == 0)
				{
					h = pJSRect->valuedouble;
				}
			}
		}
		else if (strcmp(pJSConstructCom->string, "Target") == 0)
		{
			targetSOrder = pJSConstructCom->valueint;
		}

	}

	pUIApt->setName(strName.Get());
	pUIApt->Create(strType.Get(), strNameMatl.Get(), strNameMatlFile.Get(), targetSOrder, x, y, w, h);


	return true;
}


Vector3 CUIFile::CreateVector3(cJSON* pJS)
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



bool CUIFile::InitializeSpaceAspect(cJSON* pJS, CSpaceAspect& rSpaceApt)
{
	if (0 == pJS)
	{
		return false;
	}

	Vector3 pos;
	Vector3 forward;
	Vector3 up;

	Vector3 v3;
	for (cJSON* pSubJS = pJS->child; pSubJS != 0; pSubJS = pSubJS->next)
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





bool CUIFile::InitializeCameraAspect(cJSON* pJS, CCameraAspect* pCameraApt)
{
	if ((nullptr == pJS) || (nullptr == pCameraApt))
	{
		return false;
	}

	for (cJSON* pJSConstructCom = pJS; pJSConstructCom != nullptr; pJSConstructCom = pJSConstructCom->next)
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
		else if (strcmp(pJSConstructCom->string, "Near") == 0)
		{
			pCameraApt->setNear(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Far") == 0)
		{
			pCameraApt->setFar(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Width") == 0)
		{
			pCameraApt->setWidth(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Height") == 0)
		{
			pCameraApt->setHight(pJSConstructCom->valuedouble);
			continue;
		}
		else if (strcmp(pJSConstructCom->string, "Command") == 0)
		{
			cJSON* pJSCmdCom = pJSConstructCom->child;
			for (; pJSCmdCom != 0; pJSCmdCom = pJSCmdCom->next)
			{
				CCommandAspect* pCmdApt = CreateCommandAspect(pJSCmdCom);
				if (nullptr == pCmdApt)
				{
					delete pCmdApt;
					return nullptr;
				}

				pCameraApt->AddCommandAspect(pCmdApt);
			}
		}
	}

	pCameraApt->GenerateSpaceTimeID();

	return true;
}


CCameraAspect* CUIFile::CreateCameraAspectInCom(cJSON* pJS, CEssetyAspect* pComHost)
{
	if (nullptr == pJS)
	{
		return nullptr;
	}

	CCameraAspect* pCamApt = new CCameraAspect(0, pComHost);
	pCamApt->Create();

	cJSON* pJSCameraCom = pJS->child;
	if (!InitializeCameraAspect(pJSCameraCom, pCamApt))
	{
		delete pCamApt;
		return nullptr;
	}

	return pCamApt;
}


CCommandAspect* CUIFile::CreateCommandAspect(cJSON* pJS)
{

	if (nullptr == pJS)
	{
		return nullptr;
	}

	CCommandAspect* pCmdApt = nullptr;

	CString* pName = nullptr;
	cJSON* pJSCmd = pJS->child;
	for (; pJSCmd != nullptr; pJSCmd = pJSCmd->next)
	{
		if (strcmp(pJSCmd->string, "Name") == 0)
		{
			pName = new CString(pJSCmd->valuestring);
		}
		else if (strcmp(pJSCmd->string, "Value") == 0)
		{

			if (pName == nullptr)
			{
				return nullptr;
			}

			if (strcmp(pName->Get(), "BlendFunc") == 0)
			{
				CCommandAspectBlend* pCmdBlendApt = new CCommandAspectBlend();
				//pCmdApt->Create(pName->Get(), )
				CString* pSrc = nullptr;
				CString* pTag = nullptr;
				for (cJSON* pJSCmdCh = pJSCmd->child; pJSCmdCh != nullptr; pJSCmdCh = pJSCmdCh->next)
				{
					if (strcmp(pJSCmdCh->string, "Src") == 0)
					{
						pSrc = new CString(pJSCmdCh->valuestring);
					}
					else if (strcmp(pJSCmdCh->string, "Tag") == 0)
					{
						pTag = new CString(pJSCmdCh->valuestring);
					}
				}

				if ((nullptr != pSrc) && (nullptr != pTag))
				{
					pCmdBlendApt->Create(pName->Get(), pSrc->Get(), pTag->Get());

					delete pSrc;
					delete pTag;
					delete pName;

					pSrc = nullptr;
					pTag = nullptr;
					pName = nullptr;
					//return pCmdBlendApt;

					pCmdApt = pCmdBlendApt;
				}

			}
			else if (strcmp(pName->Get(), "ClearColor") == 0)
			{
				CCommandAspectClearColor* pCmdCCApt = new CCommandAspectClearColor();

				float r, g, b, a;
				for (cJSON* pJSCmdCh = pJSCmd->child; pJSCmdCh != nullptr; pJSCmdCh = pJSCmdCh->next)
				{
					if (strcmp(pJSCmdCh->string, "r") == 0)
					{
						r = pJSCmdCh->valuedouble;
					}
					else if (strcmp(pJSCmdCh->string, "g") == 0)
					{
						g = pJSCmdCh->valuedouble;
					}
					else if (strcmp(pJSCmdCh->string, "b") == 0)
					{
						b = pJSCmdCh->valuedouble;
					}
					else if (strcmp(pJSCmdCh->string, "a") == 0)
					{
						a = pJSCmdCh->valuedouble;
					}
					else
					{
						//need optmize

						delete pCmdCCApt;
						return nullptr;
					}
				}

				pCmdCCApt->Create(r, g, b, a);
				pCmdCCApt->ResetName(pName->Get());

				pCmdApt = pCmdCCApt;

			}
			else if (strcmp(pName->Get(), "ViewPort") == 0)
			{
				float x, y, w, h;
				CCommandAspectViewPort* pCmdVpApt = new CCommandAspectViewPort();
				for (cJSON* pJSCmdCh = pJSCmd->child; pJSCmdCh != nullptr; pJSCmdCh = pJSCmdCh->next)
				{
					if (strcmp(pJSCmdCh->string, "x") == 0)
					{
						x = pJSCmdCh->valuedouble;
					}
					else if (strcmp(pJSCmdCh->string, "y") == 0)
					{
						y = pJSCmdCh->valuedouble;
					}
					else if (strcmp(pJSCmdCh->string, "w") == 0)
					{
						w = pJSCmdCh->valuedouble;
					}
					else if (strcmp(pJSCmdCh->string, "h") == 0)
					{
						h = pJSCmdCh->valuedouble;
					}
					else
					{
						//need optmize

						delete pCmdVpApt;
					}
				}

				pCmdVpApt->Create(x, y, w, h);
				pCmdVpApt->ResetName(pName->Get());

				pCmdApt = pCmdVpApt;
			}
			else
			{
				CCommandAspect* pComcmdApt = new CCommandAspect();
				pComcmdApt->Create(pName->Get(), pJSCmd->valuestring);

				delete pName;
				pName = nullptr;

				pCmdApt = pComcmdApt;
			}

		}
	}

	if (nullptr != pName)
	{
		delete pName;
	}



	return pCmdApt;
}


CUIAspect* CUIFile::CreateUIAspectInCom(cJSON* pJS, CEssetyAspect* pComHost)
{
	if (nullptr == pJS)
	{
		return nullptr;
	}


	CUIAspect* pUIApt = new CUIAspect(nullptr, pComHost);
	cJSON* pJSUICom = pJS->child;
	if (!InitializeUIAspect(pJSUICom, pUIApt))
	{
		delete pJSUICom;
		return nullptr;
	}


	return pUIApt;
}




CComponentAspect* CUIFile::CreateEssetyComponentAspect(cJSON* pJS, CEssetyAspect* pComHost)
{
	for (cJSON* pItemComJS = pJS->child; pItemComJS != 0; pItemComJS = pItemComJS->next)
	{
		if (strcmp(pItemComJS->string, "Class") == 0)
		{
			if (strcmp(pItemComJS->valuestring, "Camera") == 0)
			{
				CCameraAspect* pCamApt = CreateCameraAspectInCom(pJS, pComHost);
				if (nullptr == pCamApt)
				{
					return nullptr;
				}

				return pCamApt;
			}
			else if (strcmp(pItemComJS->valuestring, "UI") == 0)
			{
				CUIAspect* pUIApt = CreateUIAspectInCom(pJS, pComHost);
				if(pUIApt == nullptr)
				{
					return nullptr;
				}

				return pUIApt;
			}
		}
	}


	return nullptr;
}



bool CUIFile::InitializeEssetyAspect(cJSON* pJS, CEssetyAspect* pEssetyApt)
{
	if ((nullptr == pJS) || (nullptr == pEssetyApt))
	{
		return false;
	}


	for (cJSON* pItemJS = pJS; pItemJS != 0; pItemJS = pItemJS->next)
	{
		if (strcmp(pItemJS->string, "Component") != 0)
		{
			continue;
		}

		for (cJSON* pComJS = pItemJS->child; pComJS != nullptr; pComJS = pComJS->next)
		{
			CComponentAspect* pComApt = CreateEssetyComponentAspect(pComJS, pEssetyApt);
			if (nullptr == pComApt)
			{
				return false;
			}

			pEssetyApt->AddComponentAspect(pComApt);

		}

	}


	return true;
}





bool CUIFile::CompleteSceneNodeSpace(CSceneNodeAspect* pSceneNodeApt)
{
	if ((nullptr == pSceneNodeApt) || ((!pSceneNodeApt->initedSapceLocal()) && (!pSceneNodeApt->initedSpaceWorld())))
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




void CUIFile::Destroy()
{
	if (nullptr != m_pUITreeApt)
	{
		delete m_pUITreeApt;
		m_pUITreeApt = nullptr;
	}


	if (nullptr != m_pJSSource)
	{
		cJSON_Delete(m_pJSSource);
	}
}