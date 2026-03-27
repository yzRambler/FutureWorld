#include"CFileManager.h"
#include"CFile.h"
#include"COBJFile.h"
#include"CPngFile.h"
#include"CShaderFile.h"

#ifdef _WND_OPENGL_PLATFORM_
#include"CFBXFile.h"
#endif


#include"CFWDFile.h"
#include"CSceneConfigFile.h"
#include"CMaterialFile.h"
#include"CUIFile.h"
#include"CFileDescribe.h"
#include"CFileOpListener.h"



#ifndef  _WND_OPENGL_PLATFORM_
#include<emscripten/emscripten.h>
//#define _FW_WEBGL_DEBUG_
  #include"CWeb.h"
#else
 #include"CWindows.h"
#endif

using namespace FW;
using namespace std;



CFileManager* CFileManager::m_pInstance = 0;

CFileManager::CFileManager():CICTarget(EICTAGTYPE::ICT_FILEMAG), m_pCurrentFile(0), 
m_pPlatform(0)
{
	m_lsRequest.clear();
	m_lsFinished.clear();
}

CFileManager::~CFileManager()
{
}

bool CFileManager::Create()
{

#ifdef _WND_OPENGL_PLATFORM_
	m_pPlatform = new CWindows();
#else
	m_pPlatform = &CWeb::Instance(); //new CWeb();
#endif


	return true;
}


void CFileManager::Destroy()
{
	for (LSFILE_ITER iter = m_lsRequest.begin(); iter != m_lsRequest.end(); ++iter)
	{
		delete* iter;
	}
	m_lsRequest.clear();

	for (LSFILE_ITER iter = m_lsFinished.begin(); iter != m_lsFinished.end(); ++iter)
	{
		delete* iter;
	}
	m_lsFinished.clear();

	if (nullptr != m_pPlatform)
	{
		delete m_pPlatform;
		m_pPlatform = nullptr;
	}
}





bool CFileManager::RegisterLst(CListener* pLsn)
{
	return  CICTarget::RegisterLst(pLsn);
}


void CFileManager::UnregisterLst(CListener* pLsn)
{
	CICTarget::UnregisterLst(pLsn);
}


void CFileManager::Update()
{
	Monitor();
}




void CFileManager::Monitor()
{
	if (m_pPlatform == nullptr)
	{
		return;
	}

	if ((nullptr == m_pCurrentFile)&&(m_lsRequest.empty()))
	{
		return;
	}

#ifdef _FW_WEBGL_DEBUG_
	int n = (int)m_pCurrentFile->state();
	EM_ASM({
		//console.log("CFileManager::Check() current file name: " + UTF8ToString($0));
		console.log("CFileManager::Check()  current file state: " + ($1));
		}, m_pCurrentFile->nameFile(), n);
#endif

	
	if (m_pCurrentFile == nullptr)
	{
		m_pCurrentFile = *m_lsRequest.begin();

#ifdef _FW_WEBGL_DEBUG_
		EM_ASM({
			   console.log("CFileManager: Set current file to " + UTF8ToString($0));
			}, m_pCurrentFile->nameFile());
#endif

	}


	switch (m_pCurrentFile->state())
	{
	case CFile::EFSTATE::NONE:
	case CFile::EFSTATE::WAITING_PROC:
	{
		m_pPlatform->OpenAndCopy(m_pCurrentFile);
	}
	break;


	case CFile::EFSTATE::COPY_SUC:
	{
#ifdef _FW_WEBGL_DEBUG_
		EM_ASM({
			   console.log("CFileManager: current file data copy successful file name: " + 
				   UTF8ToString($0));
			}, m_pCurrentFile->nameFile());
#endif
		//parse the current file
		m_pCurrentFile->Parse();
	}
	break;


	case CFile::EFSTATE::PARSE_SUC:
	{

#ifdef _FW_WEBGL_DEBUG_
		EM_ASM({
			   console.log("CFileManager: current file data parse successful file name: " + 
				   UTF8ToString($0));
			}, m_pCurrentFile->nameFile());
#endif

		//DriveListener(m_pCurrentFile);

		m_lsFinished.push_back(m_pCurrentFile);
		m_lsRequest.pop_front();

		m_pCurrentFile = nullptr;

	}
	break;


	//if invalid, try again later.
	case CFile::EFSTATE::INVALID:
	{
		//EraseFromRequestQueue(m_pCurrentFile);
		m_lsRequest.pop_front();
		m_lsRequest.push_back(m_pCurrentFile);

		m_pCurrentFile = nullptr;
	}
	break;

	default:
		break;
	}
}


void CFileManager::HandleFileApply(CFileDescribe* pFileDesc)
{
	if (nullptr == pFileDesc)
	{
		return;
	}


	const char* pszFileName = pFileDesc->namePathFile();

	CFile* pFile = SearchFinishedFileQueue(pszFileName);
	if (pFile != nullptr)
	{
		//pFileDesc->listener()->OnCallback(pFile);
		DriveListener(pFile);

		delete pFileDesc;

		return;
	}

	pFile = SearchRequestFilesQueue(pszFileName);
	if (pFile != nullptr)
	{
		delete pFileDesc;

		return;
	}


	switch (pFileDesc->typeFile())
	{
	case EFILETYPE::FI_SCENECFG:
	{
		pFile = new CSceneConfigFile(pFileDesc->name(), pFileDesc->namePathFile());
	}
	break;

	case EFILETYPE::FI_MATERIAL:
	{
#ifdef _FW_DEBUG_

		if (strcmp(pFileDesc->name(), "HorseMaterial") == 0)
		{
			int n = 0;
		}

#endif // !_FW_DEBUG_

		pFile = new CMaterialFile(pFileDesc->name(), pFileDesc->namePathFile());
	}
	break;


	case EFILETYPE::FI_UI:
	{
		pFile = new CUIFile(pFileDesc->name(), pFileDesc->namePathFile());
	}
	break;


	case EFILETYPE::FI_FBX:
	{
		pFile = new CFBXFile(pFileDesc->name(), pFileDesc->namePathFile());

	}
	break;


	default:
		return;
		break;
	}


	m_lsRequest.push_back(pFile);
}


void CFileManager::HandlePrimatterApply(CPrimatterDescribe* pPmtDesc)
{
	if (nullptr == pPmtDesc)
	{
		return;
	}


	const char* pszFileName = pPmtDesc->namePathFile();

	CFile* pFile = SearchFinishedFileQueue(pszFileName);
	if (pFile != nullptr)
	{
		return;
	}

	pFile = SearchRequestFilesQueue(pszFileName);
	if (pFile != nullptr)
	{
		return;
	}

	switch (pPmtDesc->typeFile())
	{
	case EFILETYPE::FI_OBJ:
		pFile = new COBJFile(pPmtDesc->name(), pszFileName);
		break;

	case EFILETYPE::FI_PNG:
		pFile = new CPngFile(pszFileName);
		break;

	case EFILETYPE::FI_SHADER:
		pFile = new CShaderFile(pPmtDesc->name(), pszFileName);
		break;


#ifdef _WND_OPENGL_PLATFORM_

	case EFILETYPE::FI_FBX:
		pFile = new CFBXFile(pPmtDesc->name(), pszFileName);
		break;

#endif // _WND_OPENGL_PLATFORM_



	case EFILETYPE::FI_FWD:
		pFile = new CFWDFile(pPmtDesc->name(), pszFileName);
		break;

	case EFILETYPE::FI_MATERIAL:
	{
#ifdef _FW_DEBUG_

		if (strcmp(pPmtDesc->name(), "HorseMaterial") == 0)
		{
			int n = 0;
		}

#endif // !_FW_DEBUG_

		pFile = new CMaterialFile(pPmtDesc->name(), pszFileName);
	}

		break;

	default:
		return;
		break;
	}


	m_lsRequest.push_back(pFile);
}



void CFileManager::DriveListener(CFile* pFile)
{
	if (nullptr == pFile)
	{
		return;
	}

	for (MAPLST_ITER iter = m_mapListener.begin(); iter != m_mapListener.end(); ++iter)
	{
		if (strcmp(pFile->nameFile(), iter->second->name()) == 0)
		{
			iter->second->OnCallback(pFile);
		}
	}
}





CFile* CFileManager::SearchFinishedFileQueue(const char* pszNamePathFile)
{
	if (nullptr == pszNamePathFile)
	{
		return nullptr;
	}


	for (LSFILE_ITER iter = m_lsFinished.begin(); iter != m_lsFinished.end(); ++iter)
	{
		if (strcmp((*iter)->nameFile(), pszNamePathFile) == 0)
		{
			return *iter;
		}
	}

	return nullptr;
}



CFile* CFileManager::SearchRequestFilesQueue(const char* pszNamePathFile)
{
	if (nullptr == pszNamePathFile)
	{
		return nullptr;
	}


	CFile* pFile = 0;
	for (LSFILE_ITER iter = m_lsRequest.begin(); iter != m_lsRequest.end(); ++iter)
	{
		pFile = *iter;
		if (strcmp(pFile->nameFile(), pszNamePathFile) == 0)
		{
			return *iter;
		}
	}

	return nullptr;
}



void CFileManager::EraseFromRequestQueue(CFile* pFile)
{
	for (LSFILE_ITER iter = m_lsRequest.begin(); iter != m_lsRequest.end(); )
	{
		if (*iter == pFile)
		{
			iter = m_lsRequest.erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}
}

