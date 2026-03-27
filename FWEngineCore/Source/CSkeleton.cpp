#include "CSkeleton.h"
#include "CBone.h"
#include "MathLibrary.h"
#include "CIDManager.h"

//#define _SK_DEBUG_

using namespace FW;


CSkeleton::CSkeleton(CConstruct* pHost) :CPrimatter(pHost, EPMTTYPE::SKELETON), m_pRoot(0)
{
	m_mapBT.clear();
	m_mapBones.clear();
}

CSkeleton::CSkeleton(const char* pszName, CConstruct* pHost) :CPrimatter(pszName, pHost, EPMTTYPE::SKELETON), m_pRoot(0)
{
	m_mapBT.clear();
	m_mapBones.clear();
}


CSkeleton::~CSkeleton()
{
	Destroy();
}


bool CSkeleton::Create(FDWORD id)
{
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	return Create(id, &pos, &forward, &up);
}


bool CSkeleton::Create(FDWORD id, Vector3* pPos, Vector3* pForward, Vector3* pUp)
{
	if ((pPos == 0) || (pForward == 0) || (pUp == 0))
	{
		return false;
	}

	setID(id);

	//m_jTransform.Initalize(*pPos, *pForward, *pUp);

	m_mapBT["Bip001"] = EBONE::ROOT;
	m_mapBT["Bip001 Pelvis"] = EBONE::PELVIS;
	m_mapBT["Bip001 Spine"] = EBONE::SPINE0;
	m_mapBT["Bip001 Spine1"] = EBONE::SPINE1;
	m_mapBT["Bip001 Spine2"] = EBONE::SPINE2;
	m_mapBT["Bip001 Spine3"] = EBONE::SPINE3;
	m_mapBT["Bip001 Neck"] = EBONE::NECK0;
	m_mapBT["Bip001 Neck1"] = EBONE::NECK1;
	m_mapBT["Bip001 Neck2"] = EBONE::NECK2;
	m_mapBT["Bip001 Neck3"] = EBONE::NECK3;
	m_mapBT["Bip001 Neck4"] = EBONE::NECK4;
	m_mapBT["Bip001 Head"] = EBONE::HEAD;
	m_mapBT["Bip001 Ponytail1"] = EBONE::EAR0_LEFT;
	m_mapBT["Bip001 Ponytail11"] = EBONE::EAR1_LEFT;
	m_mapBT["Bip001 Ponytail12"] = EBONE::EAR2_LEFT;
	m_mapBT["Bip001 Ponytail2"] = EBONE::EAR0_RIGHT;
	m_mapBT["Bip001 Ponytail21"] = EBONE::EAR1_RIGHT;
	m_mapBT["Bip001 Ponytail22"] = EBONE::EAR2_RIGHT;
	m_mapBT["Bip001 L Thigh"] = EBONE::THIGH_LEFT;
	m_mapBT["Bip001 L Calf"] = EBONE::CALF_LEFT;
	m_mapBT["Bip001 L Foot"] = EBONE::FOOT_LEFT;
	m_mapBT["Bip001 L Toe0"] = EBONE::TOE0_LEFT;
	m_mapBT["Bip001 L Toe01"] = EBONE::TOE1_LEFT;
	m_mapBT["Bip001 L Toe02"] = EBONE::TOE2_LEFT;
	m_mapBT["Bip001 R Thigh"] = EBONE::THIGH_RIGHT;
	m_mapBT["Bip001 R Calf"] = EBONE::CALF_RIGHT;
	m_mapBT["Bip001 R Foot"] = EBONE::FOOT_RIGHT;
	m_mapBT["Bip001 R Toe0"] = EBONE::TOE0_RIGHT;
	m_mapBT["Bip001 R Toe01"] = EBONE::TOE1_RIGHT;
	m_mapBT["Bip001 R Toe02"] = EBONE::TOE2_RIGHT;
	m_mapBT["Bip001 L Clavicle"] = EBONE::CLAVICLE_LEFT;
	m_mapBT["Bip001 L UpperArm"] = EBONE::UPPERARM_LEFT;
	m_mapBT["Bip001 L Forearm"] = EBONE::FOREARM_LEFT;
	m_mapBT["Bip001 L Hand"] = EBONE::HAND_LEFT;
	m_mapBT["Bip001 L Finger0"] = EBONE::FINGER0_LEFT;
	m_mapBT["Bip001 L Finger01"] = EBONE::FINGER1_LEFT;
	m_mapBT["Bip001 L Finger02"] = EBONE::FINGER2_LEFT;
	m_mapBT["Bip001 R Clavicle"] = EBONE::CLAVICLE_RIGHT;
	m_mapBT["Bip001 R UpperArm"] = EBONE::UPPERARM_RIGHT;
	m_mapBT["Bip001 R Forearm"] = EBONE::FOREARM_RIGHT;
	m_mapBT["Bip001 R Hand"] = EBONE::HAND_RIGHT;
	m_mapBT["Bip001 R Finger0"] = EBONE::FINGER0_RIGHT;
	m_mapBT["Bip001 R Finger01"] = EBONE::FINGER1_RIGHT;
	m_mapBT["Bip001 R Finger02"] = EBONE::FINGER2_RIGHT;
	m_mapBT["Bip001 Tail"] = EBONE::TAIL0;
	m_mapBT["Bip001 Tail1"] = EBONE::TAIL1;
	m_mapBT["Bip001 Tail2"] = EBONE::TAIL2;


	return true;
}


void CSkeleton::Update(long lDltTime)
{
	ComputeAnimGlobalMatrix(lDltTime, m_pRoot);
}



void CSkeleton::ComputeAnimGlobalMatrix(long lDltTime, CBone* pBone)
{
	if (pBone == 0)
	{
		return;
	}

	pBone->Update(lDltTime);

	CBone* pSubBone = 0;
	int count = pBone->countSubNodes();
	for (int i = 0; i < count; i++)
	{
		pSubBone = (CBone*)pBone->subNode(i);

#ifdef _SK_DEBUG_
		if ((strcmp(pSubBone->name(), "Bip001 L Thigh") == 0) || (strcmp(pSubBone->name(), "Bip001 R Thigh") == 0))
		{
			int n = 0;
		}

#endif // _DEBUG

		ComputeAnimGlobalMatrix(lDltTime, pSubBone);
	}
}





CBone* CSkeleton::GetBone(const char* pszNameBone)
{
	if (pszNameBone == 0)
	{
		return 0;
	}

	EBONE eSign = ValidName(pszNameBone);
	if (eSign == EBONE::UNKNOWN)
	{
		return 0;
	}

	ITER_MAPBONES iter = m_mapBones.find(eSign);
	if (iter == m_mapBones.end())
	{
		return 0;
	}

	return iter->second;
}



bool CSkeleton::Clone(CSkeleton* pSk)
{
	if (nullptr == pSk)
	{
		return false;
	}

	m_mapBT.clear();
	for (ITER_MAPBONETYPE iter = pSk->m_mapBT.begin(); iter != pSk->m_mapBT.end(); ++iter)
	{
		m_mapBT[iter->first] = iter->second;
	}

	return CloneBoneTree(pSk->m_pRoot);
}



bool CSkeleton::CloneBoneTree(CBone* pRoot)
{
	if (nullptr == pRoot)
	{
		return false;
	}

	DestroyBoneTree();

	if (!CloneNode(pRoot, &m_pRoot))
	{
		return false;
	}

	return Traverse(m_pRoot);
}




bool CSkeleton::CloneNode(CBone* pInputBone, CBone** ppOutputBone)
{
	if (pInputBone == 0)
	{
		*ppOutputBone = 0;

		return false;
	}

	CBone* pCloneBone = new CBone;
	pCloneBone->Clone(pInputBone);

	CBone* pSubBone = 0;
	int countSubNodes = pInputBone->countSubNodes();
	for (int i = 0; i < countSubNodes; i++)
	{
		if (!CloneNode((CBone*)pInputBone->subNode(i), &pSubBone))
		{
			delete pCloneBone;
			*ppOutputBone = 0;

			return false;
		}

		pSubBone->SetParent(pCloneBone);
		pCloneBone->AttachChild(pSubBone);
	}


	*ppOutputBone = pCloneBone;

	return true;

}



bool CSkeleton::Traverse(CBone* pBone)
{
	EBONE eSign = ValidName(pBone->name());
	if (eSign == EBONE::UNKNOWN)
	{
		return false;
	}

	AddBone(pBone);

	int countSubNode = pBone->countSubNodes();
	for (int i = 0; i < countSubNode; i++)
	{
		if (!Traverse((CBone*)pBone->subNode(i)))
		{
			return false;
		}
	}

	return true;
}




bool CSkeleton::AddBone(CBone* pBone)
{
	if (pBone == 0)
	{
		return false;
	}

	EBONE eSign = ValidName(pBone->name());
	if (eSign == EBONE::UNKNOWN)
	{
		return false;
	}

	if (m_mapBones.find(eSign) != m_mapBones.end())
	{
		return false;
	}

	pBone->setSign((int)eSign);
	m_mapBones[eSign] = pBone;

	return true;
}



void CSkeleton::Destroy()
{
	CIDManager::Instance().RemoveID(id());

	m_mapBT.clear();
	DestroyBoneTree();
}

void CSkeleton::DestroyBoneTree()
{

	if (m_pRoot != nullptr)
	{
		delete m_pRoot;
		m_pRoot = nullptr;
	}

	m_mapBones.clear();
}

