/*
CPrimatter:

    Primatter is the abbreviation and composition. It means primal matter.
	Primatter represent the parsed result from outside file.

	Mostly, CPrimatter object is created with some config parameters and the data from outside file. 
	After the data preserved in outside file is loaded and parsed successfully, the result will be saved in 
	CPrimatterCenter as a CPrimatter object.

	CPrimatter object is the basic element which will be composed a CEssety object.

	A CPrimatter object responsed to a CAspect objet.


Author:  Zhen Yi

Created Date:  Feb. 09, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_PRIMATTER_
#define _FW_PRIMATTER_

#include"CConstruct.h"
#include"CData.h"
#include"IPrimatterManager.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class DLLCOAPI CPrimatter : public CConstruct, public CData, public IPrimatter
	{
	public:
		CPrimatter(CConstruct* pHost, EPMTTYPE type = EPMTTYPE::PR_UNKNOWN) : 
			CConstruct(pHost, ECONSTRTYPE::CST_PRIMATTER), m_type(type), m_bLock(false) {}


		CPrimatter(const char* pszName, CConstruct* pHost, EPMTTYPE type = EPMTTYPE::PR_UNKNOWN) :
			CConstruct(pszName, pHost, ECONSTRTYPE::CST_PRIMATTER), CData(pszName), m_type(type), m_bLock(false) { }

		virtual ~CPrimatter(){}

		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile)
		{
			if (0 != name()|| 0 != nameData() || 0 != namePathFile())
			{
				return false;
			}

			setName(pszName);
			setNameData(pszName);
			setNameFileData(pszNamePathAndFile);

			return true;
		}


		virtual bool Clone(CPrimatter* pPmt) { return true; }



	//Inherited from IPrimatter
	public:
		virtual EPMTTYPE GetType() { return type(); }


	//attribute
	public:
		EPMTTYPE type() { return m_type; }
		void setType(EPMTTYPE type) { m_type = type; }

		void lock() { m_bLock = true; }
		void unlock() { m_bLock = false; }
		bool beLocked() { return m_bLock; }

	protected:
		EPMTTYPE m_type;


	private:
		bool m_bLock;
	};
};



#endif // !_FW_PRIMATTER_
