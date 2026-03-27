/*
CTextureUnit


Author:  Zhen Yi

Created Date: Feb. 26, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_TEXTURE_UNIT_
#define _FW_TEXTURE_UNIT_

#include "GL/glew.h"

#include"CConstruct.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class CMaterial;
	class CProgram;
	class CTexture;
	class DLLCOAPI CTextureUnit : public CConstruct
	{
	public:
		CTextureUnit(CConstruct* pHostCst);
		CTextureUnit(const char* pszName, CConstruct* pHostCst);
		virtual ~CTextureUnit();

		bool Initialize(const char* pszNamePathFile, const char* pszNameSampler, 
			int indexOfMaterialArray, GLenum eTextUnitId, CTexture* pTexture);

		void UseTexture(CProgram* pProgram);

	//attribute
	public:

		void setTextureUnitId(GLenum idTU) { m_eTextureUnitId = idTU; }
		GLenum idTextureUnit() { return m_eTextureUnitId; }
		
		void setTexArrayIndexOfMatl(int index) { m_indexMaterialArray = index; }
		int indexTexArrayIndexOfMatl() { return m_indexMaterialArray; }

		void setTexture(CTexture* pTexture) { m_pTexture = pTexture; }
		CTexture* texture() { return m_pTexture; }

		const char* nameFile() { return m_strNamePathFile.Get(); } 
		const char* nameSampler() { return m_strNameSampler.Get(); }
		

	private:
		void Destroy();


	private:
		CTexture* m_pTexture;
		FDWORD m_idTexture;    //for check

		CString m_strNamePathFile;

		CString m_strNameSampler;

		GLenum m_eTextureUnitId;    // Correspond with the element of texture array in CMaterial object.
		                            // The element index equal m_indexMaterialArray.

		int m_indexMaterialArray;   // the position of the texture array of corresponding CMaterial object 

	};
}




#endif // !_FW_TEXTURE_UNIT_
