/*

CRenderAspect
   
    Note:  One CRender object can include multi CMesh and CMaterial object.

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_RENDER_ASPECT_
#define _FW_RENDER_ASPECT_

#include"CComponentAspect.h"
#include"CMaterialAspect.h"

namespace FW
{
	class CEssetyAspect;
	class CComeshAspect;
	class CComesh;
	class CRenderAspect : public CComponentAspect
	{
	public:
		CRenderAspect(CAspect* pHost);

		//Parameter: pszName is mesh name in the model file.
		CRenderAspect(const char* pszName, CAspect* pHost);


		virtual ~CRenderAspect();

		bool Initialize(const char* pszName, const char* pszNamePathAndFile);


	//Inherite from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);

		virtual EAPTSTATE CheckState(CAspectCenter* pPmtAtpCent, CEssetyAspect* pEsetyApt);



	//Inherit from CComponentAspect
	public:
		virtual CComponentAspect* CreateCoInstance(CEssetyAspect* pComHost);
		


	//attribute
	public:
		//get current material.  Reserve for: switch various material object.
		CComeshAspect& comeshApt() { return *m_pComshApt; }



	private:
		bool CreateBoxes(CComesh* pCmsh);

	private:
		CComeshAspect* m_pComshApt;
	};


}


#endif // !_FW_RENDER_ASPECT_
