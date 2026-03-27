#include"CFileOpListener.h"
#include"CIDManager.h"
#include"CFile.h"
#include"CFBXFile.h"
#include"CFWDFile.h"

#include<vector>
#include<string>
#include"CBone.h"
#include"CAnimation.h"

using namespace FW;

extern void ListBones(CBone* pRootBone, std::vector<CBone*>& vt);




CFileOpListener::CFileOpListener(CConstruct* pHost) :
	CListener(pHost)
{
}


CFileOpListener::CFileOpListener(const char* pszName, CConstruct* pHost) : 
	CListener(pszName, pHost)
{
}

CFileOpListener::~CFileOpListener()
{
}

FDWORD CFileOpListener::GetID()
{
	return id();
}


const char* CFileOpListener::GetName()
{
	return name();
}


void CFileOpListener::OnCallback(void* p)
{
	if (nullptr == p)
	{
		return;
	}


	//temp code
	CFile* pFile = (CFile*)p;
	if (pFile->type() == EFILETYPE::FI_FBX)
	{
		std::string strNameFile = pFile->name();
		int loc = strNameFile.find_last_of("fbx");
		//strNameFile.replace(loc, "fbx", "fwd");
		std::string strNName = strNameFile.substr(0, loc - 3);
		strNName += ".fwd";

		CreateFWDFile(strNName.c_str(), (CFBXFile*)pFile);
	}

}


bool CFileOpListener::Create(const char* pszNameFilePath)
{
	if (nullptr == pszNameFilePath)
	{
		return false;
	}

	setID(CIDManager::Instance().ApplyID());
	setIDIntTarget(EICTAGTYPE::ICT_FILEMAG);
	setName(pszNameFilePath);

	return true;
}


bool CFileOpListener::CreateFWDFile(const char* pszTargetNameFile, CFBXFile* pSrcFile)
{
	if (!CFWDFile::Instance().CreateEmptyFile(pszTargetNameFile))
	{
		return false;
	}


	CFWDFile::Instance().WriteFileHead(pSrcFile->sizeFWDFile(), pSrcFile->hasSkeleton(),
		pSrcFile->hasAnimation());


	if (pSrcFile->hasSkeleton())
	{
		CFWDFile::Instance().WriteSkeleton(pSrcFile->nameSkeleton(), pSrcFile->rootBoneTree());
	}



	OBJECT* pOBJ = 0;
	unsigned int total = 0;
	unsigned int count = 0;
	for(int i=0; i<pSrcFile->countOBJECT(); i++)
	{
		//pOBJ = m_vtOBJ[i];
		pOBJ = pSrcFile->getOBJECT(i);
		count = CFWDFile::Instance().WriteMeshData(pOBJ);
		if (0 == count)
		{
			return false;
		}

		total += count;
	}


	std::vector<CBone*> vtFromFBXBones;
	vtFromFBXBones.clear();

	ListBones(pSrcFile->rootBoneTree(), vtFromFBXBones);


	//Change file name from X1.fbx into X2.fwd.
	if (pSrcFile->hasAnimation())
	{
		CAnimation* pAni = (CAnimation*)pSrcFile->animationGroup()->getCurrentAnim();
		const char* pszNameFileOriginal = pAni->namePathFile();

		pAni->setNameFileData(pszTargetNameFile);
		CFWDFile::Instance().WriteAnimationData(pSrcFile->boneAniUnit(), pSrcFile->animationGroup());

		pAni->setNameFileData(pszNameFileOriginal);
	}


	//size verify
	if (total != pSrcFile->sizeAllMeshBlock())
	{
		return false;
	}


	CFWDFile::Instance().Finish();



	//test
	CFWDFile::Instance().ReadWholeFile();
	CFWDFile::Instance().Parse();

	CFWDFile* pFWDFile = &CFWDFile::Instance();

	std::vector<CBone*> vtFromFWD;
	vtFromFWD.clear();

	ListBones(CFWDFile::Instance().rootBoneTree(), vtFromFWD);

	return true;
}
