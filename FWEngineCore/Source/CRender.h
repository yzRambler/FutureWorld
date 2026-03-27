/*
CRender

       One CRender object can include multi CMesh and CMaterial object.

Author: Zhen Yi

Created Date: May 10, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_RENDER_
#define _FW_RENDER_

#include<map>
#include<vector>
#include"CComponent.h"
#include"CComesh.h"
#include"MathLibrary.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class DLLCOAPI CRender : public CComponent
	{
	//Inherit from CComponent
	public:
		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent);


	public:
		CRender(CConstruct* pHost);
		CRender(const char* pszName, CConstruct* pHost);
		virtual ~CRender();


	//attribute
	public:
		CComesh* comesh() { return m_pComesh; }

		bool setComesh(CComesh* pComesh)
		{ 
			if (m_pComesh != 0) 
				return false; 

			m_pComesh = pComesh; 
			m_idComesh = m_pComesh->id();

			return true; 
		}



	private:
		void Destroy();



	private:
		//m_pComesh is just the reference of the primatter preserving in CPrimatterCenter.
		//Must not delete it, just only call the Cancel function of it.
		CComesh* m_pComesh;

		//Save comesh id for checking it.
		FDWORD m_idComesh;
	};


}



#endif // ! _FW_RENDER_
