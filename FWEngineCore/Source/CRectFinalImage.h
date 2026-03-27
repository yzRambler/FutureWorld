/*

CRectFinalImanager


Author:  Zhen Yi

 Created Date:  Feb. 12, 2026

 Version: 0.2.0 Alpha

*/


#ifndef _FW_RECT_FINAL_IMAGE_
#define _FW_RECT_FINAL_IMAGE_

#include "CRectImage.h"



namespace FW
{
	class CMaterial;
	class CPass;
	class CProgram;
	class CTexture;
	class CVertexShader;
	class CFragmentShader;
	class DLLCOAPI CRectFinalImage : public CRectImage
	{
	public:
		CRectFinalImage(CConstruct* pHost);
		CRectFinalImage(const char* pszName, CConstruct* pHost);
		virtual ~CRectFinalImage();

		bool Create(CTexture** aryTexturePt, int sizeArray);

		virtual void Update(int indPass);


		//Atrribute
	public:
		CMaterial* material() { return m_pMatl; }

	private:
		void InitParameters();

		CMaterial* CreateInnerMaterial(CTexture** aryTexturePt, int sizeArray);
		CPass* CreatePassWithTexture(CMaterial* pMatl, const char* pszSamplerName, int indexTextureArray);
		CVertexShader* CreateVertexShaderWithTexture(CProgram* pHost, const char* pszParam);
		CFragmentShader* CreateFragmentShaderWithTexture(CProgram* pHost, const char* pszParam, int indexTextureArray);

	private:
		unsigned int m_ayTextureAptIDSET[ETXTU::TEXTURE_COUNT];

		CMaterial* m_pMatl;

	};


}





#endif // !_FW_RECT_FINAL_IMAGE_
