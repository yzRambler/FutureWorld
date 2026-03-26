#include"CAspectCenter.h"
#include"CAspect.h"
#include"CSceneAspect.h"
#include"CMaterialAspect.h"
#include"CUITreeAspect.h"

#include"CSceneConfigFile.h"
#include"CMaterialFile.h"
#include"CUIFile.h"

#include"CFileManager.h"
#include"CFileDescribe.h"


#include"CIDManagerAgent.h"
#include"FWEngineCoreExport.h"


using namespace FW;



//static IAspectManager* g_pAspectMag = nullptr;
static CAspectCenter* g_pAspectMag = nullptr;

/*
#ifdef _WND_OPENGL_PLATFORM_
extern "C" __declspec(dllexport) IAspectManager* CreateAspectManager()
#else
extern "C" IAspectManager* __cdecl CreateAspectManager()
#endif
{
	if (nullptr == g_pAspectMag)
	{
		g_pAspectMag = new CAspectCenter();
		if (!g_pAspectMag->Create())
		{
			delete g_pAspectMag;
			g_pAspectMag = 0;
		}
	}

	return g_pAspectMag;
}
*/


#ifdef _WND_OPENGL_PLATFORM_

extern "C" DLLPRAPI IAspectManager* CreateAspectManager()
{
	if (nullptr == g_pAspectMag)
	{
		g_pAspectMag = new CAspectCenter();
		if (!g_pAspectMag->Create())
		{
			delete g_pAspectMag;
			g_pAspectMag = nullptr;
		}
	}

	return g_pAspectMag;
}

extern "C" DLLPRAPI void ReleaseAspectManager()
{
	if (nullptr != g_pAspectMag)
	{
		delete g_pAspectMag;
		g_pAspectMag = nullptr;
	}
}


#else

extern "C" IAspectManager* __cdecl CreateAspectManager()
{
	if (nullptr == g_pAspectMag)
	{
		g_pAspectMag = new CAspectCenter();
		if (!g_pAspectMag->Create())
		{
			delete g_pAspectMag;
			g_pAspectMag = 0;
		}
	}

	return g_pAspectMag;
}

extern "C" void __cdecl ReleaseAspectManager()
{
	if (nullptr != g_pAspectMag)
	{
		delete g_pAspectMag;
		g_pAspectMag = nullptr;
	}
}

#endif







CAspectSet::CAspectSet()
{
	m_mapIDASS.clear();
}


CAspectSet::~CAspectSet()
{
	//DestroyAll();
}


void CAspectSet::AddData(FDWORD id, CData* pPmt)
{
	//Check id

	//if (!ID_VALID(id) || (pPmt == 0))
	//{
	//	return;
	//}

	if ((pPmt == nullptr) || (!CIDManagerAgent::Instance().idMag().Inquire(id)))
	{
		return;
	}



	//MAPIDAS_ITER iter = m_mapIDASS.find(id);
	if (m_mapIDASS.find(id) != m_mapIDASS.end())
	{
		return;
	}

	SDataSign* pSS = new SDataSign();
	pSS->pPmt = pPmt;
	pSS->count = 1;

	m_mapIDASS[id] = pSS;
}

//CData* CAspectSet::GetUnpossess(FDWORD id)
void* CAspectSet::GetUnpossess(FDWORD id)
{
	//Check id.

	//if (!ID_VALID(id))
	//{
	//	//return 0;
	//	return nullptr;
	//}

	if (!CIDManagerAgent::Instance().idMag().Inquire(id))
	{
		return nullptr;
	}


	return m_mapIDASS[id]->pPmt->pointerSubclass();
}


//CData* CAspectSet::AcquireReference(FDWORD id)
void* CAspectSet::AcquireReference(FDWORD id)
{
	//Check id whether is valid.
	//if (!ID_VALID(id))
	//{
	//	return 0;
	//}
	if (!CIDManagerAgent::Instance().idMag().Inquire(id))
	{
		return nullptr;
	}


	MAPIDAS_ITER iter = m_mapIDASS.find(id);
	if (iter != m_mapIDASS.end())
	{
		iter->second->count++;
		//return iter->second->pPmt;
		return iter->second->pPmt->pointerSubclass();
	}

	return nullptr;
}

//int CDataSet::ReleaseData(FWORD id)
int CAspectSet::ReleaseReference(FDWORD id)
{
	//Check id whether is valid.
	/*
	if (!ID_VALID(id))
	{
		return -1;
	}*/


	if (!CIDManagerAgent::Instance().idMag().Inquire(id))
	{
		return -1;
	}


	MAPIDAS_ITER iter = m_mapIDASS.find(id);
	if (iter != m_mapIDASS.end())
	{
		int count = iter->second->count;

		iter->second->count = (count <= 0) ? 0 : count - 1;
		if (iter->second->count == 0)
		{
			delete iter->second->pPmt;
			iter->second->pPmt = nullptr;

			delete iter->second;
			m_mapIDASS.erase(iter);

			CIDManagerAgent::Instance().idMag().RemoveID(id);

			return 0;
		}

	}

	return iter->second->count;
}


FDWORD CAspectSet::Check(const char* pszFileName, const char* pszName)
{
	CData* pAt = 0;
	for (MAPIDAS_ITER iter = m_mapIDASS.begin(); iter != m_mapIDASS.end(); ++iter)
	{
		pAt = iter->second->pPmt;
		if ((strcmp(pAt->nameData(), pszName) == 0) && (strcmp(pAt->namePathFile(), pszFileName) == 0))
		{
			return ((CAspect*)pAt->pointerSubclass())->id();
		}

	}

	//have none.
	return 0;
}




FDWORD CAspectSet::RequireData(char* pszFileName, char* pszName)
{
	//SDataSign* pAS = 0;
	CData* pAt = 0;
	for (MAPIDAS_ITER iter = m_mapIDASS.begin(); iter != m_mapIDASS.end(); ++iter)
	{
		pAt = iter->second->pPmt;
		if ((strcmp(pAt->nameData(), pszName) == 0) && (strcmp(pAt->namePathFile(), pszFileName) == 0))
		{
			iter->second->count++;

			return ((CAspect*)pAt->pointerSubclass())->id();
		}

	}

	//have none
	return 0;
}




void CAspectSet::DestroyAll()
{
	for (MAPIDAS_ITER iter = m_mapIDASS.begin(); iter != m_mapIDASS.end(); ++iter)
	{
		if ((*iter).second == nullptr)
		{
			continue;
		}

		CAspect* pApt = (CAspect*)(*iter).second->pPmt->pointerSubclass();
		if (pApt != nullptr)
		{
			if (CIDManager::Instance().Inquire(pApt->id()))
			{
				CIDManager::Instance().RemoveID(pApt->id());
				delete pApt;
			}
		}

		delete (*iter).second;

	}

	m_mapIDASS.clear();
}




////////////////////////////////////////////////////////////////////////////





CAspect* CAspectCenter::ApplyAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt)
{
	CAspect* pPmtApt = nullptr;
	FDWORD id = GetAspectID(pszName, pszNameFile, typeApt);

	if (id == 0)
	{
		CFile* pFile = CFileManager::Instance().SearchFinishedFileQueue(pszNameFile);
		if (0 != pFile)
		{
			return CreateAspectByLoadedFile(pszName, pszNameFile, typeApt, pFile);
		}

		return PreApplyAspect(pszName, pszNameFile, typeApt);
	}

	return GetReference(id, typeApt);
}



//////////////////////////////////////////////////////////////////////




CAspectCenter::CAspectCenter() :m_pSetSceneApt(nullptr), m_pSetMaterialApt(nullptr), m_pSetUITreeApt(nullptr)
{
}


CAspectCenter::~CAspectCenter()
{
	DestroyAll();
}



bool CAspectCenter::Create()
{
	m_pSetSceneApt = new CAspectSet();
	m_pSetMaterialApt = new CAspectSet();
	m_pSetUITreeApt = new CAspectSet();

	return true;
}


bool CAspectCenter::Initialize(int widthWnd, int heightWnd)
{
	//Create();
	if ((nullptr == m_pSetSceneApt) || (nullptr == m_pSetMaterialApt))
	{
		return false;
	}

	m_widthWnd = widthWnd;
	m_heightWnd = heightWnd;

	return true;
}


void CAspectCenter::DestroyAll()
{
	if (nullptr == m_pSetSceneApt || nullptr == m_pSetMaterialApt)
	{
		return;
	}

	m_pSetSceneApt->DestroyAll();
	delete m_pSetSceneApt;
	m_pSetSceneApt = nullptr;

	m_pSetMaterialApt->DestroyAll();
	delete m_pSetMaterialApt;
	m_pSetMaterialApt = nullptr;

	m_pSetUITreeApt->DestroyAll();
	delete m_pSetUITreeApt;
	m_pSetUITreeApt = nullptr;
}



EAPTSTATE CAspectCenter::InquireAspectState(CAspect* pPmtApt)
{
	if (nullptr == pPmtApt)
	{
		return EAPTSTATE::APT_FAILED;
	}


	switch (pPmtApt->state())
	{
	case EAPTSTATE::APT_UNKNOWN:
	{
		if (pPmtApt->typeApt() == EAPTTYPE::CST_SCENE)
		{
			CSceneAspect* pSceneApt = (CSceneAspect*)pPmtApt;
			pSceneApt->CheckState(this);
		}
	}
	break;

	case EAPTSTATE::APT_INITING:
	{
		CFile* pFile = nullptr;
		if (pPmtApt->typeApt() == EAPTTYPE::CST_SCENE)
		{
			pFile = CFileManager::Instance().SearchFinishedFileQueue(((CSceneAspect*)pPmtApt)->namePathFile());
		}
		else if ((pPmtApt->typeApt() == EAPTTYPE::CST_UI_TREE))
		{
			pFile = CFileManager::Instance().SearchFinishedFileQueue(((CUITreeAspect*)pPmtApt)->namePathFile());
		}
		else if ((pPmtApt->typeApt() == EAPTTYPE::CST_PRIMATTER) &&
			(((CPrimatterAspect*)pPmtApt)->type() == EPMTTYPE::MATERIAL))
		{
			pFile = CFileManager::Instance().SearchFinishedFileQueue(((CMaterialAspect*)pPmtApt)->namePathFile());
		}
		

		if (nullptr != pFile)
		{
			if (pPmtApt->typeApt() == EAPTTYPE::CST_SCENE)
			{
				//initialize
				CSceneConfigFile* pSceneFile = (CSceneConfigFile*)pFile;
				CSceneAspect* pSceneApt = (CSceneAspect*)pPmtApt;
				if (nullptr == pSceneApt->rootSceneAptTree())
				{
					if (pSceneFile->sceneAspect()->rootSceneAptTree() == nullptr)
					{
						pSceneApt->setState(EAPTSTATE::APT_FAILED);
						return EAPTSTATE::APT_FAILED;
					}

					FDWORD id = pSceneApt->id();
					int w = pSceneApt->screenWidth();
					int h = pSceneApt->screenHeight();

					//if(!pSceneApt->Copy(pSceneFile->sceneAspect()))
					if (!pSceneApt->Clone(pSceneFile->sceneAspect()))
					{
						pSceneApt->setState(EAPTSTATE::APT_FAILED);
						return EAPTSTATE::APT_FAILED;
					}

					pSceneApt->setState(EAPTSTATE::APT_INITING);
					pSceneApt->setID(id);
					pSceneApt->setScreenWidth(w);
					pSceneApt->setScreenHeight(h);
				}
				else
				{
					pSceneApt->CheckState(this);
				}

			}
			else if (pPmtApt->typeApt() == EAPTTYPE::CST_UI_TREE)
			{
				CUIFile* pUIFile = (CUIFile*)pFile;
				CUITreeAspect* pUITApt = (CUITreeAspect*)pPmtApt;

				if (nullptr == pUITApt->rootUITree())
				{
					if (pUIFile->sceneAspect()->rootUITree() == nullptr)
					{
						pUITApt->setState(EAPTSTATE::APT_FAILED);
						return EAPTSTATE::APT_FAILED;
					}

					FDWORD id = pUITApt->id();
					if (!pUITApt->Clone(pUIFile->sceneAspect()))
					{
						pUITApt->setState(EAPTSTATE::APT_FAILED);
						return EAPTSTATE::APT_FAILED;
					}

					pUITApt->setState(EAPTSTATE::APT_INITING);
					pUITApt->setID(id);
				}
				else
				{
					pUITApt->CheckState(this);
				}

			}
			else if ((pPmtApt->typeApt() == EAPTTYPE::CST_PRIMATTER) &&
				(((CPrimatterAspect*)pPmtApt)->type() == EPMTTYPE::MATERIAL))
			{
				CMaterialFile* pMatlFile = (CMaterialFile*)pFile;
				CMaterialAspect* pMatlApt = (CMaterialAspect*)pPmtApt;

				if (pMatlFile->materialAspect() == 0)
				{
					pMatlApt->setState(EAPTSTATE::APT_FAILED);
					return EAPTSTATE::APT_FAILED;
				}

				//if (!pMatlApt->Copy(pMatlFile->materialAspect()))
				FDWORD id = pMatlApt->id();
				if (!pMatlApt->Clone(pMatlFile->materialAspect()))
				{
					pMatlApt->setState(EAPTSTATE::APT_FAILED);
					return EAPTSTATE::APT_FAILED;
				}

				pMatlApt->setID(id);

				pMatlApt->setState(EAPTSTATE::APT_READY);
			}


		}
		else
		{
			CFile* pFile = nullptr;
			if (pPmtApt->typeApt() == EAPTTYPE::CST_SCENE)
			{
				pFile = CFileManager::Instance().SearchRequestFilesQueue(
					((CSceneAspect*)pPmtApt)->namePathFile());
			}
			else if (pPmtApt->typeApt() == EAPTTYPE::CST_UI_TREE)
			{
				pFile = CFileManager::Instance().SearchRequestFilesQueue(((CUITreeAspect*)pPmtApt)->namePathFile());
			}
			else if ((pPmtApt->typeApt() == EAPTTYPE::CST_PRIMATTER) &&
				(((CPrimatterAspect*)pPmtApt)->type() == EPMTTYPE::MATERIAL))
			{
				pFile = CFileManager::Instance().SearchRequestFilesQueue(
					((CMaterialAspect*)pPmtApt)->namePathFile());
			}


			//if (0 == pFile)
			if (nullptr == pFile)
			{
				pPmtApt->setState(APT_FAILED);
				return EAPTSTATE::APT_FAILED;
			}

			pPmtApt->setState(APT_INITING);
			return EAPTSTATE::APT_INITING;
		}
	}
	break;


	default:
		break;
	}

	return pPmtApt->state();
}


bool CAspectCenter::ReleaseAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt)
{
	if ((nullptr == m_pSetSceneApt) || (nullptr == m_pSetMaterialApt)
		|| (nullptr == pszName) || (nullptr == pszNameFile))
	{
		return false;
	}

	//Check out whether the primatteraspect exist.
	//FDWORD id = GetPrimatterAspectID(pszName, pszNameFile, typeApt);
	FDWORD id = GetAspectID(pszName, pszNameFile, typeApt);

	if (0 == id)
	{
		return false;
	}


	switch (typeApt)
	{
		//case EPMTTYPE::SCENE:
	case EAPTTYPE::CST_SCENE:
	{
		m_pSetSceneApt->ReleaseReference(id);
		return true;
	}
	break;

	//case EPMTTYPE::MATERIAL:
	case EAPTTYPE::CST_PRM_MAT:
	{
		m_pSetMaterialApt->ReleaseReference(id);
		return true;
	}
	break;

	case EAPTTYPE::CST_UI_TREE:
	{
		m_pSetUITreeApt->ReleaseReference(id);
		return true;
	}
	break;


	default:
		break;
	}


	return false;


	return true;
}









FDWORD CAspectCenter::GetAspectID(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt)
{
	if ((0 == pszName) || (0 == pszNameFile))
	{
		return 0;
	}

	FDWORD id = 0;

	switch (typeApt)
	{
	case EAPTTYPE::CST_SCENE:
		id = m_pSetSceneApt->Check(pszNameFile, pszName);
		break;

	case EAPTTYPE::CST_PRM_MAT:
		id = m_pSetMaterialApt->Check(pszNameFile, pszName);
		break;

	case EAPTTYPE::CST_UI_TREE:
		id = m_pSetUITreeApt->Check(pszNameFile, pszName);
		break;

	default:
		break;
	}

	return id;

}


CAspect* CAspectCenter::GetReference(FDWORD id, EAPTTYPE typeApt)
{
	if ((nullptr == m_pSetSceneApt) || (nullptr == m_pSetMaterialApt))
	{
		return nullptr;
	}

	CAspect* pPmtApt = nullptr;
	switch (typeApt)
	{
	case EAPTTYPE::CST_SCENE:
		pPmtApt = (CAspect*)m_pSetSceneApt->AcquireReference(id);
		break;

	case EAPTTYPE::CST_PRM_MAT:
		pPmtApt = (CAspect*)m_pSetMaterialApt->AcquireReference(id);
		break;


	case EAPTTYPE::CST_UI_TREE:
		pPmtApt = (CAspect*)m_pSetUITreeApt->AcquireReference(id);
		break;


	default:
		break;
	}

	return pPmtApt;
}




CAspect* CAspectCenter::GetUnpossessAspect(FDWORD id, EAPTTYPE typeApt)
{
	if ((nullptr == m_pSetSceneApt) || (nullptr == m_pSetMaterialApt))
	{
		return nullptr;
	}

	CAspect* pPmtApt = nullptr;
	switch (typeApt)
	{
	case EAPTTYPE::CST_SCENE:
		pPmtApt = (CAspect*)m_pSetSceneApt->GetUnpossess(id);
		break;

	case EAPTTYPE::CST_PRM_MAT:
		pPmtApt = (CAspect*)m_pSetMaterialApt->GetUnpossess(id);
		break;


	case EAPTTYPE::CST_UI_TREE:
		pPmtApt = (CAspect*)m_pSetUITreeApt->GetUnpossess(id);
		break;


	default:
		break;
	}

	return pPmtApt;
}



CAspect* CAspectCenter::PreApplyAspect(const char* pszName, const char* pszNameFile,
	EAPTTYPE typeApt)
{
	if ((nullptr == pszName) || (nullptr == pszNameFile))
	{
		return nullptr;
	}

	CFile* pFile = CFileManager::Instance().SearchRequestFilesQueue(pszNameFile);
	//if (0 == pFile)
	if (nullptr == pFile)
	{
		CAspectDescribe aptDesc;
		aptDesc.Initialize(pszName, pszNameFile);
		CFileManager::Instance().HandleFileApply(&aptDesc);


	}

	return PreCreateAspect(pszName, pszNameFile, typeApt);
}


CAspect* CAspectCenter::PreCreateAspect(const char* pszName, const char* pszNameFile,
	EAPTTYPE typeApt)
{
	if ((nullptr == pszName) || (nullptr == pszNameFile))
	{
		return nullptr;
	}

	FDWORD id = CIDManagerAgent::Instance().idMag().ApplyID();
	if (id == 0)
	{
		return nullptr;
	}

	switch (typeApt)
	{
	case EAPTTYPE::CST_SCENE:
	{
		CSceneAspect* pSceneApt = new CSceneAspect(pszName);
		pSceneApt->setID(id);
		pSceneApt->setScreenWidth(m_widthWnd);
		pSceneApt->setScreenHeight(m_heightWnd);
		pSceneApt->setNameFileData(pszNameFile);
		pSceneApt->setState(EAPTSTATE::APT_INITING);
		pSceneApt->setPointerSubclass(pSceneApt);

		m_pSetSceneApt->AddData(id, pSceneApt);

		return pSceneApt;
	}
	break;

	case EAPTTYPE::CST_PRM_MAT:
	{
		CMaterialAspect* pMatlApt = new CMaterialAspect(pszName);
		pMatlApt->setID(id);
		pMatlApt->setNameFileData(pszNameFile);
		pMatlApt->setState(EAPTSTATE::APT_INITING);
		pMatlApt->setPointerSubclass(pMatlApt);

		m_pSetMaterialApt->AddData(id, static_cast<CData*>(pMatlApt));

		return pMatlApt;
	}
	break;


	case EAPTTYPE::CST_UI_TREE:
	{
		CUITreeAspect* pUIApt = new CUITreeAspect(pszName);
		pUIApt->setID(id);
		pUIApt->setNameFileData(pszNameFile);
		pUIApt->setState(EAPTSTATE::APT_INITING);
		pUIApt->setPointerSubclass(pUIApt);

		m_pSetUITreeApt->AddData(id, static_cast<CData*>(pUIApt));

		return pUIApt;
	}
	break;


	default:
		break;
	}

	return nullptr;
}



CAspect* CAspectCenter::CreateAspectByLoadedFile(const char* pszName, const char* pszNameFile,
	EAPTTYPE typeApt, CFile* pFile)
{
	if ((nullptr == pszName) || (nullptr == pszNameFile) || (nullptr == pFile))
	{
		return nullptr;
	}


	FDWORD id = CIDManagerAgent::Instance().idMag().ApplyID();
	if (id == 0)
	{
		return 0;
	}

	switch (typeApt)
	{
	case EAPTTYPE::CST_SCENE:
	{
		CSceneConfigFile* pSceneFile = (CSceneConfigFile*)pFile;
		if (pSceneFile->sceneAspect()->rootSceneAptTree() != 0)
		{
			CSceneAspect* pSceneApt = new CSceneAspect(pszName);

			//if (pSceneApt->Clone(pSceneFile->sceneAspect()))
			{
				pSceneApt->setID(id);
				pSceneApt->setScreenHeight(m_heightWnd);
				pSceneApt->setScreenWidth(m_widthWnd);
				pSceneApt->setNameFileData(pszNameFile);

				pSceneApt->setPointerSubclass(pSceneApt);
				pSceneApt->setState(EAPTSTATE::APT_INITING);

				m_pSetSceneApt->AddData(id, pSceneApt);

				//return pSceneApt;
				return (CPrimatterAspect*)pSceneApt;    //temporary code
			}

		}
	}
	break;

	case EAPTTYPE::CST_PRM_MAT:
	{
		CMaterialFile* pMatlFile = (CMaterialFile*)pFile;
		CMaterialAspect* pMatlApt = new CMaterialAspect(pszName);
		if (pMatlFile->materialAspect() != 0)
		{
			//if (pMatlApt->Clone(pMatlFile->materialAspect()))
			{
				pMatlApt->setID(id);
				pMatlApt->setState(EAPTSTATE::APT_INITING);
				pMatlApt->setNameFileData(pszNameFile);
				pMatlApt->setPointerSubclass(pMatlApt);

				//m_setMaterialApt.AddData(id, pMatlApt);
				m_pSetMaterialApt->AddData(id, pMatlApt);

				return pMatlApt;
			}
		}
	}
	break;


	case EAPTTYPE::CST_UI_TREE:
	{
		CUIFile* pUIFile = (CUIFile*)pFile;
		CUITreeAspect* pUIApt = new CUITreeAspect(pszName);

		pUIApt->setID(id);
		pUIApt->setState(EAPTSTATE::APT_INITING);
		pUIApt->setNameFileData(pszNameFile);
		pUIApt->setPointerSubclass(pUIApt);

		m_pSetUITreeApt->AddData(id, pUIApt);

		return pUIApt;

	}
	break;


	default:
		break;
	}


	return nullptr;
}

