/*
CSkeleton

Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_SKELETON_
#define _FW_SKELETON_

#include<map>
#include<string>

#include "CPrimatter.h"
#include "FWEngineCoreExport.h"

namespace FW
{
	class CBone;
	class CSkeletonAnimation;
	class DLLCOAPI CSkeleton : public CPrimatter
	{
	public:
		enum EBONE {
			UNKNOWN = 0, ROOT, PELVIS, SPINE0, SPINE1, SPINE2, SPINE3, NECK0, NECK1, NECK2, NECK3, NECK4,
			HEAD, EAR0_LEFT, EAR0_RIGHT, EAR1_LEFT, EAR1_RIGHT, EAR2_LEFT, EAR2_RIGHT,
			THIGH_LEFT, THIGH_RIGHT, CALF_LEFT, CALF_RIGHT, FOOT_LEFT, FOOT_RIGHT, TOE0_LEFT, TOE0_RIGHT,
			TOE1_LEFT, TOE1_RIGHT, TOE2_LEFT, TOE2_RIGHT,
			CLAVICLE_LEFT, CLAVICLE_RIGHT, UPPERARM_LEFT, UPPERARM_RIGHT, FOREARM_LEFT, FOREARM_RIGHT,
			HAND_LEFT, HAND_RIGHT, FINGER0_LEFT, FINGER0_RIGHT, FINGER1_LEFT, FINGER1_RIGHT, FINGER2_LEFT, 
			FINGER2_RIGHT, TAIL0, TAIL1, TAIL2, COUNT,
		};

	private:
		typedef std::map<const char*, EBONE> MAPBONETYPE;
		typedef MAPBONETYPE::iterator ITER_MAPBONETYPE;

		typedef std::map<EBONE, CBone*> MAPBONES;
		typedef MAPBONES::iterator ITER_MAPBONES;

	public:
		CSkeleton(CConstruct* pHost);
		CSkeleton(const char* pszName, CConstruct* pHost);

		virtual ~CSkeleton();

		bool Create(FDWORD id);
		bool Clone(CSkeleton* pSk);
		bool CloneBoneTree(CBone* pRoot);
		void Update(long lDltTime);
		

	//attribute
	public:
		const CBone* const rootBoneTree() { return m_pRoot; }
		const CBone* bone(EBONE eBone) 
		{ ITER_MAPBONES iter = m_mapBones.find(eBone); return (iter == m_mapBones.end() ? 0 : iter->second); }

		CBone* GetBone(const char* pszNameBone);


	private:
		bool Create(FDWORD id, Vector3* pPos, Vector3* pForward, Vector3* pUp);
		void Destroy();

		bool CloneNode(CBone* pInputBone, CBone** ppOutputBone);
		bool Traverse(CBone* pRoot);
		bool AddBone(CBone* pBone);

		EBONE ValidName(const char* pszName)
		{
			ITER_MAPBONETYPE iter = m_mapBT.begin();
			for (; iter != m_mapBT.end(); ++iter)
			{
				if (strcmp(pszName, iter->first) == 0)
				{
					return iter->second;
				}
			}

			return EBONE::UNKNOWN;
		}

		void DestroyBoneTree();
		void ComputeAnimGlobalMatrix(long lDltTime, CBone* pBone);


	private:

		MAPBONETYPE m_mapBT;
		MAPBONES m_mapBones;

		CBone* m_pRoot;

	};

};





#endif // !_FW_SKELETON_

