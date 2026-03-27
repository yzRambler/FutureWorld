
/*

CMaterial


Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_MATERIAL_
#define _FW_MATERIAL_

#include <vector>
#include "GL/glew.h"
#include "Common.h"
#include"CPrimatter.h"
#include"CommonPrimatter.h"
#include"FWEngineCoreExport.h"
#include "MathLibrary.h"

namespace FW
{
	class CMesh;
	class CPass;
	class CTextureUnit;
	class CTextureUnitAspect;
	class CRenderUnit;
	class DLLCOAPI CMaterial : public CPrimatter
	{
	private:
		typedef std::vector<CPass*> VTPASS;
		typedef VTPASS::iterator VTPAS_ITER;


	public:
		CMaterial(CConstruct* pHost);
		CMaterial(const char* pszName, CConstruct* pHost);
		virtual ~CMaterial();

		bool AddTextureUnit(CTextureUnit* pTextUnit);
		bool InsertTextureUnit(int ind, CTextureUnit* pTextUnit);

		bool AddPass(CPass* pPass);
		bool BindPass(int ind);


	//attribute
	public:
		CMesh* host() { return (CMesh*)m_pHost; }

		bool textUnitEmpty(int ind) 
		{ if ((ind < 0) || (ind >= ETXTU::TEXTURE_COUNT)) return true; return m_ayTextureUnit[ind]; }

		bool matchingTextUnit(int ind, CTextureUnitAspect* pTextUnitApt);
		CTextureUnit* textUnit(int ind, CTextureUnitAspect* pTextUnitApt);
		CTextureUnit* textureUnit(int ind)
		{  if ((ind < 0) || (ind >= ETXTU::TEXTURE_COUNT)) return 0;  return m_ayTextureUnit[ind]; }


		int countValidTextUnit() { return m_nTextureCount; }

		CPass* pass(int ind)
		{  if ((ind < 0) || (ind >= m_vtPass.size())) return 0; return m_vtPass[ind];  }

		int countPass() { return m_vtPass.size(); }


		void setRNDGroupOrder(int order) { m_nRNDGOrder = order; }
		int orderRNDGroup() { return m_nRNDGOrder; }

		void setRenderType(ERNDTYPE type) { m_typeRender = type; }
		ERNDTYPE typeRender() { return m_typeRender; }

	private:
		void InitializeTextureArray();
		void Destroy();

	private:

		VTPASS m_vtPass;
		CTextureUnit* m_ayTextureUnit[ETXTU::TEXTURE_COUNT];

		int m_nTextureCount;

		int m_nRNDGOrder;

		ERNDTYPE m_typeRender;

	};

}

#endif // !_FW_MATERIAL_
