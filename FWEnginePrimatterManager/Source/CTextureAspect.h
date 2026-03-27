/*
CTextureAspect


Author:  Zhen Yi

Created Date:  Feb. 26, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_TEXTURE_ASPECT_
#define _FW_TEXTURE_ASPECT_

#include "GL/glew.h"

#include"CPrimatterAspect.h"



namespace FW
{
	class CTextureUnitAspect;
	class CTextureAspect : public CPrimatterAspect
	{
	//Inherit from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /* =nullptr */);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);


		//Inherit from CPrimatterAspect
	public:
		bool Initialize(const char* pszName, const char* pszNamePathAndFile);


	public:
		CTextureAspect(CTextureUnitAspect* pHost);
		CTextureAspect(const char* pszName, CTextureUnitAspect* pHost);
		virtual ~CTextureAspect();



	//Attribute
	public:
		CTextureUnitAspect* host() { return m_pHost; }
		

	private:
		CTextureUnitAspect* m_pHost;
	};


};



#endif // !_FW_TEXTURE_ASPECT_
