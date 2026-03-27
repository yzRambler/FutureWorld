/*
CMaterialAspect

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_MATERIAL_ASPECT_
#define _FW_MATERIAL_ASPECT_

#include<vector>
#include"GL/glew.h"
#include "CPrimatterAspect.h"
#include"CPassAspect.h"
#include"CommonPrimatter.h"
#include"TemplateLibrary.h"
#include"FWEnginePrimatterManagerExport.h"

namespace FW
{

	class CMaterial;
	class CTextureUnitAspect;
	class DLLPRAPI CMaterialAspect : public CPrimatterAspect
	{
	private:
		typedef std::vector<CPassAspect*> VTPASS;
		typedef VTPASS::iterator VTPASS_ITER;


		//Inherit from CAspect
	public:
		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);

		/*
		The function InitializeCorrelateConstruct() just ready for independent loading the 
		CMaterial object.
		*/

		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pIPmtCent, CConstruct* pHostCst  = nullptr );

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pIPmtCent);


		//Inherit from CPrimatterAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);



	public:
		CMaterialAspect();
		CMaterialAspect(const char* pszName);
		virtual ~CMaterialAspect();

		
		bool AddTextureUnitAspect(CTextureUnitAspect* pTXApt);
		void InitializeAppState(EAPPPRRES appState);

		void AddPassAspect(CPassAspect* pPassApt) { m_vtPass.push_back(pPassApt); }



	//attribute
	public:
		CPassAspect* passApt(int ind)


		{ if ((ind < 0) || (ind >= m_vtPass.size())) return 0; return m_vtPass[ind]; }

		int sizePassArray() { return m_vtPass.size(); }

		CTextureUnitAspect* textureUnitApt(int ind) 
		{ if ((ind < 0) || (ind >= ETXTU::TEXTURE_COUNT)) return 0; return m_ayTextUnitApt[ind]; }

		int countValidTextUnit() { return m_nTextureCount; }
		int sizeTextUnitArray() { return ETXTU::TEXTURE_COUNT; }

		void setRNDGroupOrder(int order) { m_nRNDGOrder = order; }
		int orderRNDGroup() { return m_nRNDGOrder; }

		void setRenderType(ERNDTYPE type) { m_typeRender = type; }
		ERNDTYPE typeRender() { return m_typeRender; }
		
	private:
		void InitializeTextUnitArray();
		void Destroy();

	private:
		VTPASS m_vtPass;

		CTextureUnitAspect* m_ayTextUnitApt[ETXTU::TEXTURE_COUNT];
		GLenum m_ayTextureAptIDSET[ETXTU::TEXTURE_COUNT];

		int m_nTextureCount;

		int m_nRNDGOrder;
		ERNDTYPE m_typeRender;

	};


}


#endif // !_FW_MATERIAL_ASPECT_
