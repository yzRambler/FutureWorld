/*
CTextureUnitAspect

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_TEXTUREUNIT_ASPECT_
#define _FW_TEXTUREUNIT_ASPECT_

#include "GL/glew.h"
//#include "CAssetAspect.h"
#include "CPrimatterAspect.h"

namespace FW
{
	class CMaterialAspect;
	class CTextureAspect;
	class CTextureUnit;
	class CTextureUnitAspect :public CAspect
	{

	//Inherited from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*= nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);

	public:
		CTextureUnitAspect(CMaterialAspect* pHost);
		CTextureUnitAspect(const char* pszName, CMaterialAspect* pHost);
		virtual ~CTextureUnitAspect();

		bool Initialize(const char* pszNameSampler, CTextureAspect* pTextApt);


		void CloneNameSampler(const char* pszNameSampler);
		void CloneNameFile(const char* pszNameFile);
		//Inherited from CAspect

		void InitializeAppState(EAPPPRRES appState);




	//attribute
	public:
		CMaterialAspect* host() { return m_pHost; }
		CTextureAspect* textureApt() { return m_pTextureApt; }
		void setTextureApt(CTextureAspect* pTextureApt) { m_pTextureApt = pTextureApt; }
		 
		const char* nameSampler() { return m_strSamplerName.Get(); }
		void setNameSampler(const char* pszNameSampler) { m_strSamplerName.Set(pszNameSampler); }

		const char* nameFile() { return m_strNamePathFile.Get(); }
		void setNameFile(const char* pszNameFile) { m_strNamePathFile.Set(pszNameFile); }

		void setTextArrayIndexOfMatl(int index) { m_indexMaterialArray = index; }
		int indexTextArrayIndexOfMatl() { return m_indexMaterialArray; }

		void setTextureUnitId(GLenum idTU) { m_eTextureUnitId = idTU; }
		unsigned int idTextureUnit() { return m_eTextureUnitId; }

		bool isMatching(CTextureUnit* pTextUnit);


	private:
		void Destroy();

	private:
		CMaterialAspect* m_pHost;
		CTextureAspect* m_pTextureApt;


		CString m_strNamePathFile;
		CString m_strSamplerName;

		GLenum m_eTextureUnitId;  // get from corresponding CMaterial object.
		int m_indexMaterialArray;
	};

}

#endif // !_FW_TEXTUREUNIT_ASPECT_
