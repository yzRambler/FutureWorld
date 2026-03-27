/*
CFWDFile

  The .fwd file structure:


chunk:
 head: sign + chunk size + head length + name
 data:


chunk type:
  vertex
	position
	normal
	tangent
	uv

  polygen   vertex index: a/b/c

  skeleton  bone: name + parent + children

  skin     cluster + bone

  animation  bone + curve

  ///////////////////////////////////////////////////////////////////////////


File Structure:

file head:
  FTWD  4
  version  8
  size  4             //the total file size


file body:

------------------------------------------------------------------------------------

skeleton chunk
  head:  SChunkMdHead
	FDWORD sign:    //SKLT
	int sizeChunk:   //the size of all bones + skeleton chunk head length
	int lenHead:     // sizeof(SchunkMdHead) + strlen(name) + 1;
	int count:       // the number of bones
	char name[];     // skeleton name


  data (bone tree in array):  //sub-chunk bones array.The bone tree is saved in array.
	sub-chunk bone[...]

	sub-chunk bone: SChunkBone
	  int index;    //the bone index of the bone array in skeleton
	  char name[32];
	  int countSub;    // the number of subbone
	  int* aryIndexSub;   // the array for saving sub bone index

	  
--------------------------------------------------------------------------------------

 mesh(OBJECT) chunk
  head: SChunkHead
    FDWORD sign:  MESH
	int sizeChunk: all subchunk size + vertex chunk head length
	int lenHead:  sizeof(SChunkHead) + name.len
	                The name.len include the terminal sign '\0'. 
		            i.e. name.len = strlen(name) + 1 
				    sizeof(SChunkHead) = 4 * 4
	FMATRIX matGeometry;

	FDWORD elementVt;  //PNTU  'P': position| 'N': normal| 'T': tangent| 'U': uv    [ 'O': none ]
					   //The omitted compnonet which equal 'O' will be skipped over.
					   // The letter ('P'/'N'/'T'/'U') order of the sign is not fixed, but it have to
					   // be as same as the order subchunk written.

	char name []:  //(variable)   mesh name


  data:
	sub-chunk position
	  head: SChunkRdHead
		FDWORD sign: POSI
		int sizeChunk: the size of all vertices position + subchunk head length
		int lenHead:  4*4
		FDWORD count:  the number of vertices

	  data: (x,y,z),...


    sub-chunk normal
	  head: SChunkRdHead
	    FDWORD sign: NORM
		int sizeChunk: the size of all vertices normal + subchunk head length
		int lenHead:  4*4
		FDWORD count:  the number of normals

	  data: (x,y,z),...


    sub-chunk tangent
	  head: SChunkRdHead
	    FDWORD sign: TANG
		int sizeChunk: the size of all vertices tangent + subchunk head length
		int lenHead:  4*4
		FDWORD count:  the number of tangents

	  data: (x,y,z),...


    sub-chunk UV
	  head: SChunkRdHead
	    FDWORD sign: UV
		int sizeChunk: the size of all vertices uv + subchunk head length
		int lenHead:  4*4
		FDWORD count:  the number of uvs

	  data: (u,v),...


    sub-chunk polygen
      head:  SChunkRdHead
	    FDWORD sign: POLY
		int sizeChunk: the size of all polygen + subchunk head length
		int lenHead:  4*4
		FDWORD count:  the number of polygens

      data: (a,b,c), ...


    sub-chunk skin
      head:  SChunkRdHead
	    FDWORD sign: SKIN
		int sizeChunk: the size of all cluster + subchunk head length
		int lenHead:  4*4
		FDWORD count:  the number of cluster
	    
      data:    //cluster array
        sub-chunk cluster
	      head:  SChunkClusterHead
		    FDWORD sign: CLST
		    int sizeChunk: the size of all vertex-weight + subchunk head length
		    int lenHead:   sizeof(SChunkClusterHead) + lenBoneName
		    FDWORD count:  the number of vertex-weight pair
			FMATRIX transform matrix:
			FMATRIX transform link matrix:
			FWORD indexBone:  //The index of bone in the bones array.
			                  //The skeleton tree is saved in array.
			FWORD lenBoneName:  strlen(nameBone) + 1
			char nameBone[]:
			
	      data:
	        (index, weight),...     //vertex index (FDWORD) + vertex weight (FDWORD): 



-----------------------------------------------------------------------------------------


skeleton animation chunk
  head: SChunkSkeletonAniHead
	FDWORD sign; //: SKAI
	int sizeChunk;
	int lenHead;
	int countTrack;    // the number of track equal( correspond to ) the active bone
	char nameAnimation[NAME_LEN];
	char* pNameSkeleton;
	
  date:
	SChunkTrack[...]     // SChunkTrack array


	sub-chunk track
	  head:  SChunkTrackHead
		FDWORD sign;  //TRCK
		int sizeChunk;
		int lenHead;
		int indexBone;  // the index of Bone in the bone array of skeleton.
		char nameBone[NAME_LEN];
		FMATRIX mat;   // base local matrix in corresponding to bone
		int countValidCurves;   // the number of valid curves

      data:   //curve array    T(X/Y/Z)/R(X/Y/X)/S(X/Y/Z)
	    curve[...]     // reserve the index of curve array
		               // //arranging order: T(translation) >>> R(rotation) >>> S(Scalar)

	sub-chunk curve
	  head: SChunkCurveHead
	    FDWORD sign;    // CURV
		int sizeChunk;
		int lenHead;
		FBYTE type;    // T / R / S
		FBYTE part;    // X / Y / Z
		int countKeyFrame;

		data:  //key array
		  SChunkKey[...]


		  sub-chunk :  SChunkKey
		    int index;     //the index of the key in key array of the curves
		    float time;
		    float value;
		    FWORD typeInterpolate;	//C: CONSTANT / L: LINEAR / C: CUBIC





Author: Zhen Yi

Created Date: April 30, 2023

Version: 0.2.0 Alpha

*/



#ifndef _FW_FWDFILE_
#define _FW_FWDFILE_

#ifdef FW_EDITOR

#include<stdio.h>

#endif // FW_EDITOR


#include<vector>
#include<string>

#include"CFile.h"
#include"Common.h"
#include"CBAT.h"

#define NAME_LEN  32
#define NAME_LEN_LONG  64


namespace FW
{
#pragma pack(1)
	struct SChunkHead
	{
		FDWORD sign;
		int sizeChunk;
		int lenHead;   // The length of name include the terminal sign '\0'. 
		               // i.e. strlen(name) + 1 + sizeof(SChunkHead)
		FMATRIX matGeometry;
		FDWORD elementVt;  //PNTU  'P': position| 'N': normal| 'T': tangent| 'U': uv | 'O': none
						   /// The order for saving is position->normal->tangent->uv.
						   // The omitted compnonet which equal 'O' will be skipped over.  
		                   // The letter ('P'/'N'/'T'/'U') order of the sign is not fixed, but it have to 
		                   // be as same as the order subchunk written.  
		FBYTE containSkin;  // 1: yes; 0: none.

		//char name[];
		char* pName;
	};
#pragma pack()


	struct SChunkRdHead
	{
		FDWORD sign;
		int sizeChunk;
		int lenHead;
		FDWORD count;
	};


	struct SChunkClusterHead
	{
		FDWORD sign;    // CLST
		int sizeChunk;   // the size of all vertex - weight + subchunk head length
		int lenHead;     //: sizeof(SChunkClusterHead) + lenBoneName
		FDWORD count;    //: the number of vertex - weight pair
		FMATRIX matrixTF; //correspond to the transform matrix of FBX cluster
		FMATRIX matrixTFLink;    //correspond to the transform link matrix of FBX cluster
		FWORD indexBone;    //The index of bone in the bones array.
						    //Note. The skeleton tree is saved in array.

		FWORD lenBoneName; // strlen(nameBone) + 1
		char* pNameBone;
		//char nameBone[];
	};


	struct SChunkMdHead
	{
		FDWORD sign;
		int sizeChunk;
		int lenHead;
		int count;   //the total number of all bones.
		char* pName;     //skeleton name
	};

	struct SChunkBone
	{
		int index;      //the bone index of the bone array in skeleton
		char name[NAME_LEN];
		int countSub;
		int* aryIndexSub;   //the array for saving the sub bone index. 
	};


	struct SChunkSkeletonAniHead
	{
		FDWORD sign;  // SKAI
		int sizeChunk;	
		int lenHead;
		int countTrack;    // the number of track equal( correspond to ) the active bone 
		char nameAnimation[NAME_LEN];
		char nameAnimationFile[NAME_LEN_LONG];
		char* pNameSkeleton;
	};


	struct SChunkTrackHead
	{
		FDWORD sign;  //TRCK
		int sizeChunk;
		int lenHead;
		int indexBone;  // the index of Bone in the bone array of skeleton.
		char nameBone[NAME_LEN];
		FMATRIX mat;   // base local matrix in corresponding to bone
		int countValidCurves;   // the number of valid curves
	};

#pragma pack(1)
	struct SChunkCurveHead
	{
		FDWORD sign;    // CURV
		int sizeChunk;
		int lenHead;
		FBYTE type;  // T / R / S
		FBYTE part;  // X / Y / Z
		int countKeyFrame;
	};


	struct SChunkKey
	{
		int index;     //the index of the key in key array of the curves
		int time;
		float value;
		FBYTE typeInterpolate;	//C: CONSTANT / L: LINEAR / B: CUBIC

		SChunkKey* next;     //This field will not be written into .fwd file.
	};

#pragma pack()

	struct SChunkCurve
	{
		SChunkCurveHead head;
		SChunkKey* pKeyList;
	};


	struct SChunkTrack
	{
		SChunkTrackHead head;
		SChunkCurve* aryCurves[3][3];  //[0|1|2] T|R|S  [0|1|2] X|Y|Z
	};


	struct SChunkSkeletonAni
	{
		SChunkSkeletonAniHead head;
		SChunkTrack* aryTrack;
	};


	class Matrix4x4;

    inline extern FDWORD Str2DWord(char* pszBuf);
    inline extern char* DWord2Str(FDWORD dw);
    inline extern void AssignMatrix(FMATRIX& destMat, Matrix4x4& srcMat);
	inline extern void AssignMatrix(Matrix4x4& destMat, FMATRIX& srcMat);
    inline extern float Buffer2Float(char* pBuf);
    inline extern FDWORD Buffer2DWord(char* pBuf);
	inline extern Matrix4x4 Buffer2Matrix4x4(char* pBuf);
	inline extern bool AssignConstantLenChunkStr(char* pDestString, char* pSrcString);
	inline extern bool AssignConstantLenChunkStrLong(char* pDestString, char* pSrcString);

	class CBone;
	class CAnimationGroup;
	class CTrack;
	class CCurve;
	class CSkeletonAnimation;
	class CFWDFile : public CFile
	{
	private:
		typedef std::vector<OBJECT*> VTOBJ;
		typedef VTOBJ::iterator VTOBJ_ITER;
		
		typedef std::vector<SChunkBone*> VTBNCK;
		typedef VTBNCK::iterator VTBNCK_ITER;

		typedef std::vector<SChunkTrack*> VTTRCK;
		typedef VTTRCK::iterator VTTRCK_ITER;


	public:
		CFWDFile(const char* pszName);
		CFWDFile(const char* pszName, const char* pszNamePathFile);
		virtual ~CFWDFile();

		//temprary interface function for testing
		bool ReadWholeFile();


		//derive from CFile
		virtual bool Parse();

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

//#ifdef FW_EDITOR

	public:
		bool CreateEmptyFile(const char* pszNameFile);
		bool WriteFileHead(unsigned int sizeAllOBJBlock, bool hasSkeleton = false, bool hasAnim = false);
		FDWORD WriteSkeleton(const char* pszNameSkeleton, CBone* pRootBoneTree);
		FDWORD WriteMeshData(OBJECT* pOBJ);
		
		FDWORD WriteAnimationData(VTBNTK& vtBAT, CAnimationGroup* pAniGroup);

		void Finish() { fclose(m_pHandleFile); }

	public:
		static CFWDFile& Instance() { if (0 == m_pInstance) { m_pInstance = new CFWDFile(""); } return *m_pInstance; }



	//attribute
	public:
		CBone* rootBoneTree() { return m_pRootBones; }
		const char* nameSkeleton() { return m_strNameSkeleton.Get(); }

		CAnimationGroup* animationGroup() { return m_pAnimGroup; }

		int countUnitBoneAni() { return m_vtBoneAniUnit.size(); }
		CBAT* unitBoneAni(int ind)
		{
			if ((ind < 0) || (ind >= m_vtBoneAniUnit.size())) return 0; return m_vtBoneAniUnit[ind];
		}


	private:
		FBYTE ReadByte() { return (FBYTE)*Read(sizeof(FBYTE)); }
		FWORD ReadWord() { return (FWORD)*Read(sizeof(FWORD)); }
		FDWORD ReadDWord() { return (FDWORD)*Read(sizeof(FDWORD)); }
		char* ReadString(int len) { return Read(len); }

		bool WriteByte(char* pBuf) { return Write(pBuf, sizeof(FBYTE)) == sizeof(FBYTE); }
		bool WriteWord(char* pBuf) { return Write(pBuf, sizeof(FWORD)) == sizeof(FWORD); }
		bool WriteDWord(char* pBuf) { return Write(pBuf, sizeof(FDWORD)) == sizeof(FDWORD); }
		bool WriteBuffer(char* pBuf, int len) { return Write(pBuf, len) == len; }

		char* Read(int size);
		int Write(char* buf, int size);

		//Create a new empty file with specific file name
		//confirm the file exist for next reading and writing. 
		bool CreateEmptyFile();
		bool ReOpenFile();

		OBJECT* CreateOBJ(char* pBuffer);
		void DestoryAllOBJ();

		FDWORD WritePositionBlock(OBJECT* pOBJ);
		FDWORD WriteNormalBlock(OBJECT* pOBJ);
		FDWORD WriteTangentBlock(OBJECT* pOBJ);
		FDWORD WriteUVBlock(OBJECT* pOBJ);



		bool CreateArraySkeleton(CBone* pRootBoneTree);
		FDWORD WriteSkeletonData(const char* pszSkeletonName);
		FDWORD ReadSkeletonData(char* pBuf);
		CBone* SearchBone(char* pszTargetBoneName, CBone* pRootBone);
		int SearchBoneIndexFromFBX(CBone* pBone);
		int SearchBoneIndexFromFBXEx(char* pNameBone);

		FDWORD ReadVertexData(SChunkHead& vtChunk, char* pBuf, OBJECT* pOBJ);
		FDWORD ReadPolygenData(char* pBuf, OBJECT* pOBJ);

		FDWORD WriteSkinData(OBJECT* pOBJ);
		FDWORD ReadSkinData(char* pBuf, OBJECT* pOBJ);

		int GetBoneIndex(const char* pszNameBone);
		int GetBoneIndexFromSktAryFromFBX(const char* pszNameBone);
		void ClearSkeletonArray();
		void ClearSkeletonArrayFromFBX();

		void CreateChunkBone(CBone* pBone);
		void CreateChunkBoneIntoSktAryFromFBX(CBone* pBone);
		bool ReconstructBoneTree();
		CBone* ReconstructBone(int index, CBone* pParent);
		void DestroyBoneTree();


		bool CreateTrackChunkArrayFBX(CBone* pBone);
		bool CreateTrackChunkArrayFBXEx(VTBNTK& vtBAT);
		SChunkTrack* CreateTrackChunk(CBone* pBone);
		SChunkCurve* CreateCurveChunk(CCurve* pCurve, int type, int component);

		FDWORD WriteTrackChunk(SChunkTrack* pTrackCk);

		void InitializeCurveInfoArray();

		FDWORD ReadAnimationData(char* pBuf);
		FDWORD ReadTrackData(char* pBuf, CSkeletonAnimation* pAniSk);
		FDWORD ReadTrackDataEx(char* pBuf);
		FDWORD ReadCurveData(char* pBuf, CCurve** ppCurve, int& type, int& part);
		FDWORD ReadKeyData(char* pBuf, CCurve* pCurve);

		void ClearBoneAniUnitArray();
		void ClearTrackFromFBX();

	private:
		static CFWDFile* m_pInstance;
		FILE* m_pHandleFile;

		VTOBJ m_vtOBJ;
		VTBNCK m_vtSkeleton;
		VTBNCK m_vtSkeletonFromFBXFile;

		VTTRCK m_vtTrackChunkFromFBXFile;

		VTBNTK  m_vtBoneAniUnit;

		CAnimationGroup* m_pAnimGroup;

		CBone* m_pRootBones;

		CString m_strNameSkeleton;

		char m_aryCurveType[3];
		char m_aryCurveComponent[3];
		char m_aryInterpolate[3];

//#endif // FW_EDITOR


	};
}





#endif // !_FW_FWDFILE_
