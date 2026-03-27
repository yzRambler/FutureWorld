/*
	CFBXFile

Author: Zhen Yi
Created Date: Mar. 3, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_FBXFILE_
#define _FW_FBXFILE_

#include<map>
#include"CFile.h"
#include"fbxsdk.h"
#include"CTrack.h"
#include"CBAT.h"
#include"TemplateLibrary.h"
#include"Common.h"
#include"CAnimationGroup.h"


namespace FW
{
	class CFBXStream;
	class CBone;
	class CSkeletonAnimation;
	class CCurve;
	class CSkin;
	class Matrix4x4;
	class CFBXFile : public CFile
	{
	private:
		//IFF_SOLID: no skin and no deform; IFF_VDEF: just deform and no skin; IFF_SKIN: just skin.
		typedef enum eINF {
			IFF_SOLID, IFF_VDEF, IFF_SKIN, IFF_UNKNOWN
		}EIFF;  


	public:
		enum EBONE {
			UNKNOWN = 0, ROOT, PELVIS, SPINE0, SPINE1, SPINE2, SPINE3, NECK0, NECK1, NECK2, NECK3, 
			NECK4, HEAD, EAR0_LEFT, EAR0_RIGHT, EAR1_LEFT, EAR1_RIGHT, EAR2_LEFT, EAR2_RIGHT,
			THIGH_LEFT, THIGH_RIGHT, CALF_LEFT, CALF_RIGHT, FOOT_LEFT, FOOT_RIGHT, TOE0_LEFT,
			TOE0_RIGHT, TOE1_LEFT, TOE1_RIGHT, TOE2_LEFT, TOE2_RIGHT,  CLAVICLE_LEFT, CLAVICLE_RIGHT,
			UPPERARM_LEFT, UPPERARM_RIGHT, FOREARM_LEFT, FOREARM_RIGHT, HAND_LEFT, HAND_RIGHT, 
			FINGER0_LEFT, FINGER0_RIGHT, FINGER1_LEFT, FINGER1_RIGHT, FINGER2_LEFT, FINGER2_RIGHT,
			TAIL0, TAIL1, TAIL2
		};


	public:

		

		typedef std::vector<OBJECT*> VTOBJ;
		typedef VTOBJ::iterator VTOBJ_ITER;

		typedef std::map<const char*, EBONE> MAPBONETYPE;
		typedef MAPBONETYPE::iterator ITER_MAPBONETYPE;

		typedef std::vector<CSkin*> VTSKIN;
		typedef VTSKIN::iterator VTSKIN_ITER;


		typedef TIter<VTOBJ> OBJ_ITER;
		typedef TIter<VTSKIN> SKIN_ITER;


	public:
		CFBXFile(const char* pszFileName);
		CFBXFile(const char* pszName, const char* pszFileName);
		virtual ~CFBXFile();


		//derive from the CFile
		virtual bool Parse();

		void InitializeOBJIterWork();

		OBJECT* GetOBJECT(const char* pszOBJName)
		{
			for (VTOBJ_ITER iter = m_vtOBJ.begin(); iter != m_vtOBJ.end(); ++iter)
			{
				OBJECT* pOBJ = (OBJECT*)(*iter);
				if (strcmp(pszOBJName, pOBJ->name.c_str()) == 0)
				{
					return pOBJ;
				}
			}

			return 0;
		}


		//attribute
	public:
		OBJ_ITER& iterWorkOBJ() { return *m_pIterWork; }
		CAnimationGroup* animationGroup() { return m_pAnimGroup; }

		CBone* rootBoneTree() { return m_pRootBones; }

		int countUnitBoneAni() { return m_vtBoneAniUnit.size(); }
		CBAT* unitBoneAni(int ind) 
		{
			if ((ind < 0) || (ind >= m_vtBoneAniUnit.size())) return 0; return m_vtBoneAniUnit[ind];
		}


		const char* nameSkeleton() { return m_pszSkeletonName; }
		Matrix4x4* const matGeometry() { return m_pMatGeometry; }

		FDWORD sizeFWDFile() { return m_uSizeFWDFile; }
		FDWORD sizeAllMeshBlock() { return m_uSizeAllMeshFWDBlock; }

		bool hasSkeleton() { return m_pRootBones != nullptr; }
		bool hasAnimation() { return m_pAnimGroup != nullptr 
			                         && m_pAnimGroup->getCurrentAnim() != nullptr; }

		int countOBJECT() { return m_vtOBJ.size(); }
		OBJECT* getOBJECT(int ind) 
		{ return (ind < 0 || ind >= m_vtOBJ.size()) ? nullptr : m_vtOBJ[ind]; }


		VTBNTK& boneAniUnit() { return m_vtBoneAniUnit; }

	private:

		OBJECT* CreateObjectByFbxMesh(FbxMesh* pMesh, const char* pszMeshName);
		bool CreateSkinesByFbxMesh(FbxMesh* pMesh, const char* pszMeshName, OBJECT* pObj);

		bool CreateBoneTree(FbxNode* pNode, CBone** ppBone);
		bool ExtractSkeletonAnimations(FbxScene* pScene);
		
		bool CreateSkeletonAnimation(FbxAnimLayer* pAniLayer, FbxNode* pFNode, CBone* pBoneT, 
			CSkeletonAnimation** ppAni);

		bool CreateSkeletonAnimation(FbxAnimLayer* pAniLayer, FbxNode* pFNode);
		CCurve* CreateCurve(FbxAnimCurve* pFACurve);

		void InitBonesTable();

		EBONE GetBoneSign(const char* pszBoneName);
		CBone* SearchBone(const char* pszTargetBoneName, CBone* pRootBone);


		void AssignFromFbxMatrix(FbxAMatrix& matIn, Matrix4x4& matOut);


#ifdef FW_EDITOR

		bool CreateFWDFile();
		void PreComputeSizeOBJECT();
		void PreComputeSizeFWDFile();
		FDWORD PreComputeAllBoneChunkSizeAlongBoneTree(CBone* pBone);
#endif // FW_EDITOR




	private:
		EIFF m_eFileInf;

		CFBXStream* m_pStream;

		VTOBJ m_vtOBJ;
		OBJ_ITER* m_pIterWork;

		MAPBONETYPE m_mapBT;

		VTBNTK  m_vtBoneAniUnit;

		CAnimationGroup* m_pAnimGroup;

		CBone* m_pRootBones;
		FbxNode* m_pRootBonesSrc;
		FbxAnimLayer* m_pFBXAniLayer;


		FDWORD m_uSizeAllMeshFWDBlock;
		FDWORD m_uSizeFWDFile;

		const char* m_pszSkeletonName;

		//The geometry (FbxMesh) offset matrix to a node (FbxNode).
		Matrix4x4* m_pMatGeometry;

		//temporary code for debug
		std::vector<Matrix4x4> m_vtMatrices;


	};




	class CFBXStream : public fbxsdk::FbxStream
	{
	public:
		CFBXStream(FbxManager* pSDKMag, long size);
		virtual ~CFBXStream();


		//derive from FbxStream
		//Query the current state of the stream.
		virtual EState GetState() { return m_eState; }


		//Open the stream.
		//return True if successful.
		//remark Each time the stream is open or closed, the stream position must be reset to zero.
		virtual bool Open(void* pStreamData);


		//Close the stream.
		//return True if successful.
		//remark Each time the stream is open or closed, the stream position must be reset to zero.
		virtual bool Close();


		//Empties the internal data of the stream.
		//return True if successful. 
		virtual bool Flush() { return true; }


		//Writes a memory block.
		//param pData Pointer to the memory block to write.
		//param pSize Size (in bytes) of the memory block to write.
		//return The number of bytes written in the stream.
		virtual int Write(const void* pData, int nSize);


		//Read bytes from the stream and store them in the memory block.
		//param pData Pointer to the memory block where the read bytes are stored.
		//param pSize Number of bytes read from the stream.
		//return The actual number of bytes successfully read from the stream. 
		virtual int Read(void* pData, int nSize) const;


		virtual int GetReaderID() const { return m_nReadID; }
		virtual int GetWriterID() const { return m_nWriteID; }


		//Adjust the current stream position.
		//param pSeekPos Pre-defined position where offset is added (FbxFile::eBegin, FbxFile::eCurrent:, FbxFile::eEnd)
		//param pOffset Number of bytes to offset from pSeekPos.
		virtual void Seek(const fbxsdk::FbxInt64& rOffset, const fbxsdk::FbxFile::ESeekPos& rSeekPos);


		//Get the current stream position.
		//return Current number of bytes from the beginning of the stream.
		virtual long GetPosition() const { return (char*)m_pCurrent - (char*)m_pData; }

		//Set the current stream position.
		//param pPosition Number of bytes from the beginning of the stream to seek to.
		virtual void SetPosition(long pPosition) { m_pCurrent = pPosition < 0 ? 0 : (char*)m_pData + pPosition; }

		//Return 0 if no errors occurred. Otherwise, return 1 to indicate
		//an error. This method will be invoked whenever FBX needs to verify
		//that the last operation succeeded.
		virtual int GetError() const { return m_nErrorSign; }

		// Clear current error condition by setting the current error value to 0. 
		virtual void ClearError() { m_nErrorSign = 0; }



	private:
		void ResetPosition() { m_pCurrent = m_pData; }


	private:
		EState m_eState;
		void* m_pData;
		mutable void* m_pCurrent;
		long m_lSize;

		int m_nReadID;
		int m_nWriteID;

		int m_nErrorSign;     //Return 0 if no errors occurred.Otherwise, return 1 to indicate an error.
	};



}



#endif // !_FW_FBXFILE_

