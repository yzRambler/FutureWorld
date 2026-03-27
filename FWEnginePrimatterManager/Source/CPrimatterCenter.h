/*

CPrimatterCenter

Optimize: Use Factory Function pattern ??

Author:  Zhen Yi

Created Date: Feb. 13, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_PRIMATTER_CENTER_
#define _FW_PRIMATTER_CENTER_

#include<vector>
#include<list>
#include<map>
#include<memory>
#include"Common.h"
#include"CIDManagerAgent.h"
#include"CPrimatter.h"
#include"IPrimatterManager.h"
#include"FWEnginePrimatterManagerExport.h"



namespace FW
{
	class CPrimatterSet
	{
		typedef struct SPrimatterSign
		{
			CPrimatter* pPmt;    //primatter pointer
			int count;       //the count of primatter reference
		}SPrimatterSign;

		typedef std::map<FDWORD, SPrimatterSign*> MAPIDAS;
		typedef MAPIDAS::iterator MAPIDAS_ITER;

	public:
		CPrimatterSet();
		virtual ~CPrimatterSet();

		void Create();

		void AddPrimatter(FDWORD id, CPrimatter* pPmt);
		CPrimatter* GetUnpossess(FDWORD id);
		
		FDWORD Check(const char* pszFileName, const char* pszName);

		//Just for calling of a creating function outside.
		CPrimatter* AcquireReference(FDWORD id);

		/*
		  Just for outside calling. It match with AcquireReference.
		  When the primatter counter decrease into zero, don't delete matching primatter 
		immediately.

		  If the return value equal 0 means the count of the reference of the primatter 
		is zero.
		  If the return value is -1, means the parameter id is invalid.
		*/
		int ReleaseReference(FDWORD id);

		//for calling in create function
		FDWORD  RequirePrimatter(char* pszFileName, char* pszName);

	//attribute
	public:
		bool empty() { return m_mapIDASS.empty(); }


	private:
		void DestroyAll();

	private:
		MAPIDAS m_mapIDASS;
	};



	//////////////////////////////////////////////////////////////////////////////////////


	//class CBound;
	class CComesh;
	class CMesh;
	class CMaterial;
	class CTextureUnit;
	class CTexture;
	class CProgram;
	class CSkeleton;
	class CDeformer;
	class CSkin;
	class CShader;
	class CAnimation;
	class CDeformerAspect;
	class CMeshAspect;
	class CSkinAspect;
	class CSkeletonAspect;
	class CTextureUnitAspect;
	class CProgramAspect;
	class CEssety;
	class CFile;
	class CPass;
	class CPassAspect;
	class CPrimatterAspect;
	class CPrimatterDescribe;
	class CCurves;
	class CBone;
	class DLLPRAPI CPrimatterCenter : public IPrimatterManager//, public CDataCenter
	{
	private:
		typedef std::vector<CEssety*> VTESSETY;
		typedef VTESSETY::iterator VTESSETY_ITER;

		typedef std::list<CPrimatterDescribe*> LSPRMATDC;
		typedef LSPRMATDC::iterator LSPRIMATDC_ITER;
		

		//Derivate from IPrimatterManager
	public:
		//virtual bool Create(CMsgCenter* pMsgCenter);
		virtual bool Initialize(CMsgCenter* pMsgCenter, CIDManager* pIDMag);

		virtual void Run();

		/*
		  1. Just for calling in create function outside. If application successful, the
			 counter of matching primatter will increase one by itself automatically.

		  2. In many more cases, the primatter have the hierarchical struct like a nodes
			 tree. The primatter major is the root of this tree.
			 This function just be called in manual pattern.
			   return result sign:
				 INVAL_PARA : parameters check error or invalid interior member
				 FAILED     : failed
				 SUCCESS    : successful
				 PROCESSING : application is processing

		  3. The primatter can be taked from parameter ppPamt if return SUCCESS.
			 The *ppPamt == 0  if return PROCESSING
			 The *ppPamt == 0  if return FAILED or INVAL-PARA

		*/

		virtual EAPPPRRES ApplyPrimatter(IPrimatterAspect* pIPmtApt, IPrimatter** ppIPamt,
			CConstruct* pHostCst);

		//Matching with ApplyPrimatterMajor
		virtual int ReleasePrimatter(IPrimatter* pIPmt);

		virtual EPMTSTATE InquirePrimatterState(IPrimatterAspect* pIPmtApt);

		virtual CMaterial* TakeMatrial(const char* pszNameFile, const char* pszNameMat);




	public:
		CPrimatterCenter();
		virtual ~CPrimatterCenter();


		bool InquireIDValidity(FDWORD id) 
		{ return CIDManagerAgent::Instance().idMag().Inquire(id); }

		CPrimatter* TakePrimatter(CPrimatterAspect* pPmtApt);

		EAPPPRRES ApplyPrimatter(CPrimatterAspect* pPmtApt, CPrimatter** ppPamt, 
			CConstruct* pHostCst);

		void ReleasePrimatterFromSet(CPrimatter* pPmt);
		EPMTSTATE InquirePrimatterState(CPrimatterAspect* pPmtApt);



	

	//new procedure flow
	private:
		EAPPPRRES PreApplyPrimatter(CPrimatterAspect* pPmtApt, CPrimatter** ppPamt, 
			CConstruct* pHostCst);

		CPrimatter* CreatePrimatterByLoadedFile(CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);

		CPrimatter* PreCreatePrimatter(CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CComesh* CreateComesh(FDWORD id, CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);

		CMesh* CreateMesh(CPrimatterAspect* pPmtApt, CFile* pFile, CConstruct* pHostCst);

		CMaterial* CreateMaterial(FDWORD id, CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);

		CPass* CreatePass(CPassAspect* pPmtApt, CConstruct* pHostCst);

		CProgram* CreateProgram(CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CTextureUnit* CreateTextureUnit(CTextureUnitAspect* pPmtApt, CConstruct* pHostCst);

		CTexture* CreateTexture(FDWORD id, CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);

		CShader* CreateShader(FDWORD id, CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);
		
		CDeformer* CreateDeformer(CPrimatterAspect* pPmtApt, OBJECT* pOBJ, CConstruct* pHostCst);

		CSkeleton* CreateSkeleton(FDWORD id, CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);

		CAnimation* CreateAnimation(FDWORD id, CPrimatterAspect* pPmtApt, CFile* pFile, 
			CConstruct* pHostCst);



		CComesh* PrecreateComesh(FDWORD id, CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CMesh* PrecreateMesh(CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CMaterial* PrecreateMaterial(FDWORD id, CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CPass* PrecreatePass(CPassAspect* pPmtApt, CConstruct* pHostCst);

		CTexture* PrecreateTexture(FDWORD id, CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CShader* PrecreateShader(FDWORD id, CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CDeformer* PrecreateDeformer(CDeformerAspect* pDefApt, CConstruct* pHostCst);

		CSkeleton* PrecreateSkeleton(FDWORD id, CPrimatterAspect* pPmtApt, CConstruct* pHostCst);

		CAnimation* PrecreateAnimation(FDWORD id, CPrimatterAspect* pPmtApt, CConstruct* pHostCst);



		EPMTSTATE InitializePrimatterAndAspectState(CPrimatterAspect* pPmtApt, 
			CPrimatter* pPmt, CFile* pFile);
		EPMTSTATE InitializeComesh(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, CFile* pFile);
		EPMTSTATE InitializeMesh(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, CFile* pFile);
		EPMTSTATE InitializeMaterial(CPrimatterAspect* pPmtApt, CPrimatter* pPmt);
		EPMTSTATE InitializePass(CPrimatterAspect* pPmtApt, CPrimatter* pPmt);


		EPMTSTATE InitializeTextureUnit(CTextureUnitAspect* pTextUnitApt, 
			CTextureUnit* pTextUnit);
		EPMTSTATE InitializeTexture(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, CFile* pFile);
		EPMTSTATE InitializeProgram(CPrimatterAspect* pPmtApt, CPrimatter* pPmt);
		EPMTSTATE InitializeShader(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, CFile* pFile);


		EPMTSTATE InitializeDeformer(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, OBJECT* pOBJ);
		EPMTSTATE InitializeSkeleton(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, CFile* pFile);
		EPMTSTATE InitializeAnimation(CPrimatterAspect* pPmtApt, CPrimatter* pPmt, CFile* pFile);

	
		
		void PushPrimatterIntoSet(CPrimatter* pPmt);
		
		CPrimatterDescribe* FindPrimatterDescb(CPrimatterAspect* pPmtApt);
		
		FDWORD GetPrimatterID(CPrimatterAspect* pPmtApt);

		CPrimatter* GetReference(CPrimatterAspect* pPmtApt, FDWORD id);
		CPrimatter* GetUnpossessPrimatter(CPrimatterAspect* pPmtApt, FDWORD id);

		CMesh* GetUnpossessMesh(CMeshAspect* pMeshApt);
		CSkin* GetUnpossessSkin(CSkinAspect* pSkinApt);
		//CProgram* GetUnpossessProgram(CProgramAspect* pProgramApt);
		CSkeleton* GetUnpossessSkeleton(CSkeletonAspect* pSkeletonApt);

#ifdef _WND_OPENGL_PLATFORM_

		bool InitializeSkeletonAniDataFromFBX(CFile* pfile, CSkeleton* pSkt);

#endif // _FW_EDITOR_

		bool InitializeSkeletonAniDataFromFWD(CFile* pfile, CSkeleton* pSkt);

		CMaterial* GetReferenceDefaultFrameMaterial();

		/*
		  Reset the CVertexAttribute::m_nOffset in 
		  CMaterial::CPass::CProgram::m_vtVertexAttribute 
		  with the CVertexAttribute::m_nOffset in CRenderUnit::m_vtVertexAttribute
		*/

		bool InitializeMeshVAWithMatlVA(CMesh* pMesh, CMaterial* pMatl);

		bool InitializeProgramVAPU(CProgram* pProgram, CProgramAspect* pProgApt);

	private:
		LSPRMATDC m_quPrimatterApply;

		CPrimatterSet m_setMaterial;
		CPrimatterSet m_setComesh;
		CPrimatterSet m_setTexture;
		CPrimatterSet m_setShader;
		CPrimatterSet m_setAnimation;
		CPrimatterSet m_setSkeleton;

	};


}



#endif // !_FW_PRIMATTER_CENTER_
