/*

CPrimatterAspect


Author:  Zhen Yi

Created Date: Feb. 12, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_PRIMATTER_ASPECT_
#define _FW_PRIMATTER_ASPECT_

#include"CAspect.h"
#include"CData.h"
#include"CommonPrimatter.h"

namespace FW
{
	class CPrimatterAspect : public CAspect, public CData, public IPrimatterAspect
	{

	//Inherited from IPrimatterAspect
	public:
		virtual bool InitializeCorrelateConstructIF(IPrimatter** ppIPmt, 
			IPrimatterManager* pIPmtCent, CConstruct* pHostCst);

		virtual EPMTSTATE CheckCorrelateConstructIF(IPrimatter** ppIPmt, 
			IPrimatterManager* pIPmtCent);

		virtual EPMTTYPE TypeIF() { return type(); }

		virtual EAPTSTATE StateIF()
		{
			return state();
		}

		virtual const char* Name() { return name(); }
		virtual const char* FullName() { return namePathFile(); }



	//Inherited from CAspect 
	public:	
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst )
		{ 
			return true; 
		}

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent) 
		{ 
			return EPMTSTATE::UNKNOWN; 
		}


		virtual bool Clone(CAspect* pAptSrc)
		{
			if (!CAspect::Clone(pAptSrc))
			{
				return false;
			}

			CPrimatterAspect* pPrmApt = (CPrimatterAspect*)pAptSrc;

			setNameData(pPrmApt->name());
			setNameFileData(pPrmApt->namePathFile());
			setPointerSubclass(this);

			m_eType = pPrmApt->m_eType;

			return true;
		}


		virtual bool Copy(CAspect* pAptSrc)
		{
			if (!CAspect::Copy(pAptSrc))
			{
				return false;
			}


			CPrimatterAspect* pPrmApt = (CPrimatterAspect*)pAptSrc;

			setNameData(pPrmApt->name());
			setNameFileData(pPrmApt->namePathFile());
			setPointerSubclass(this);

			m_eType = pPrmApt->m_eType;

			return true;
		}




		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent) { return EAPTSTATE::APT_UNKNOWN; }



	public:
		CPrimatterAspect(EPMTTYPE typeDefault = EPMTTYPE::PR_UNKNOWN) :m_eType(typeDefault), m_bLocked(false)
		{ setTypeApt(EAPTTYPE::CST_PRIMATTER); }

		CPrimatterAspect(const char* pszName, EPMTTYPE typeDefault = EPMTTYPE::PR_UNKNOWN) :
			CAspect(pszName), CData(pszName), m_eType(typeDefault), m_bLocked(false) 
		{
			setTypeApt(EAPTTYPE::CST_PRIMATTER);
		}

		virtual ~CPrimatterAspect() {}



		virtual void CloneName(const char* pszName);
		void CloneFileName(const char* pszNameFile);


		void InitializeName(const char* pszName)
		{
			setName(pszName);
			setNameData(pszName);
		}

		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile)
		{
			if (0 != name() || 0 != nameData() || 0 != namePathFile())
			{
				return false;
			}

			setName(pszName);
			setNameData(pszName);
			setNameFileData(pszNamePathAndFile);


			return true;
		}



	//attributes
	public:
		EPMTTYPE type() { return m_eType; }
		bool beLocked() { return m_bLocked; }
		void lock() { m_bLocked = true; }
		void unlock() { m_bLocked = false; }


	protected:
		EPMTTYPE m_eType;
		bool m_bLocked;
	};

};




#endif // !_FW_PRIMATTER_ASPECT_
