/*

CAspectCenter


Author:  Zhen Yi

Created Date:  Mar. 2025

Version: 0.2.0 Alpha


*/

#ifndef _FW_ASPECTCENTER_
#define _FW_ASPECTCENTER_

#include <map>
#include "IAspectManager.h"
#include "CData.h"
#include "CommonPrimatter.h"
#include "FWEnginePrimatterManagerExport.h"


namespace FW
{

	class CAspectSet
	{
		typedef struct SDataSign
		{
			CData* pPmt;    //Data pointer
			int count;       //the count of Data reference
		}SDataSign;

		typedef std::map<FDWORD, SDataSign*> MAPIDAS;
		typedef MAPIDAS::iterator MAPIDAS_ITER;

	public:
		CAspectSet();
		virtual ~CAspectSet();


		void AddData(FDWORD id, CData* pPmt);
		void* GetUnpossess(FDWORD id);

		FDWORD Check(const char* pszFileName, const char* pszName);


		//Just for calling of a creating function outside.
		void* AcquireReference(FDWORD id);

		/*
		  Just for outside calling. It match with AcquireReference.
		  When the Data counter decrease into zero, don't delete matching Data
		immediately.

		  If the return value equal 0 means the count of the reference of the Data
		is zero.
		  If the return value is -1, means the parameter id is invalid.
		*/
		int ReleaseReference(FDWORD id);

		//for calling in create function
		FDWORD  RequireData(char* pszFileName, char* pszName);


	//private:
		void DestroyAll();


	private:
		MAPIDAS m_mapIDASS;
	};




	class CFile;
	class CAspectCenter : public IAspectManager
	{
		//Inherit from IAspectManager
	public:
		virtual CAspect* ApplyAspect(const char* pszName, const char* pszNameFile, 
			EAPTTYPE typeApt);

		virtual EAPTSTATE InquireAspectState(CAspect* pPmtApt);

		virtual bool ReleaseAspect(const char* pszName, const char* pszNameFile, 
			EAPTTYPE typeApt);

		virtual bool Create();
		virtual bool Initialize(int widthWnd, int heightWnd);


	public:
		CAspectCenter();
		virtual ~CAspectCenter();



	private:
		FDWORD GetAspectID(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt);
		CAspect* GetReference(FDWORD id, EAPTTYPE typeApt);
		CAspect* GetUnpossessAspect(FDWORD id, EAPTTYPE typeApt);

		CAspect* PreApplyAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt);
		CAspect* PreCreateAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt);

		CAspect* CreateAspectByLoadedFile(const char* pszName, const char* pszNameFile, 
			EAPTTYPE typeApt, CFile* pFile);

		void DestroyAll();



	private:
		CAspectSet* m_pSetSceneApt;
		CAspectSet* m_pSetMaterialApt;
		CAspectSet* m_pSetUITreeApt;

		int m_widthWnd;
		int m_heightWnd;




	private:

	};


}





#endif // !_FW_ASPECTCENTER_



