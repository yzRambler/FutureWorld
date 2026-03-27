/*

CPrimatterAspect



Author: Zhen Yi

Date: April 23, 2023

*/

#ifndef _FW_PRIMATTERASPECT_CENTER_
#define _FW_PRIMATTERASPECT_CENTER_

//#include"CDataCenter.h"
#include"CPrimatterAspectSet.h"
#include"CommonPrimatter.h"
#include"IPrimatterManager.h"


namespace FW
{
	class CFile;
	class CPrimatterAspect;

	//class CPrimatterAspectCenter : public CDataCenter, public IPrimatterAspectManager
	class CPrimatterAspectCenter : public IPrimatterAspectManager
	{
	public:
		CPrimatterAspectCenter():m_widthWnd(0), m_heightWnd(0) {}
		virtual ~CPrimatterAspectCenter() {}

		CPrimatterAspect* ApplyPrimatterAspect(const char* pszName, const char* pszNameFile, EPMTTYPE typeApt);
		EAPTSTATE InquirePrimatterAspectState(CPrimatterAspect* pPmtApt);



	//Inherited from IPrimatterAspectManager
	public:
		virtual IPrimatterAspect* ApplyPrimatterAspectIF(const char* pszName, const char* pszNameFile,
			EPMTTYPE typeApt);

		virtual EAPTSTATE InquirePrimatterAspectStateIF(IPrimatterAspect* pIPmtApt);
		//virtual bool ReleasePrimatterAspectIF(const char* pszName, const char* pszNameFile, EPMTTYPE typeApt);

		virtual bool ReleasePrimatterAspectIF(IPrimatterAspect* pPmtApt);
		bool ReleasePrimatterAspect(const char* pszName, const char* pszNameFile, EPMTTYPE typeApt);


		//virtual bool CreateIF() { return CDataCenter::Create(); }
		virtual bool CreateIF() { return true; }
		virtual bool Initialize(int widthWnd, int heightWnd);


	private:
		FDWORD GetPrimatterAspectID(const char* pszName, const char* pszNameFile, EPMTTYPE typeApt);
		CPrimatterAspect* GetUnpossessPrimatterAspect(FDWORD id, EPMTTYPE typeApt);

		CPrimatterAspect* PreApplyPrimatterAspect(const char* pszName, const char* pszNameFile, EPMTTYPE typeApt);
		CPrimatterAspect* PreCreatePrimatterAspect(const char* pszName, const char* pszNameFile, EPMTTYPE typeApt);

		CPrimatterAspect* CreatePrimatterAspectByLoadedFile(const char* pszName, EPMTTYPE typeApt, CFile* pFile);

	private:
		CPrimatterAspectSet m_setSceneApt;
		CPrimatterAspectSet m_setMaterialApt;

		int m_widthWnd;
		int m_heightWnd;
	};
}


#endif // !_FW_PRIMATTERASPECT_CENTER_
