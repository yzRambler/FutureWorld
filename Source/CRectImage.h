/*

CRectImage

Author:  Zhen Yi

Created Data: Oct. 14, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_RECT_IMG_
#define _FW_RECT_IMG_


#include"CComesh.h"


namespace FW
{

	class CMatrial;
	class CRect;
	class DLLCOAPI CRectImage : public CComesh
	{
		//Inheriate from CComesh
	public:
		virtual void Update(CEssety* pEssety);

	public:
		CRectImage(CConstruct* pHost) : CComesh(pHost),
			m_pRect(nullptr) {}

		CRectImage(const char* pszName, CConstruct* pHost) : CComesh(pszName, pHost),
			m_pRect(nullptr) {}

		virtual ~CRectImage();

		bool Create(Vector3& lt, Vector3& hor, Vector3& ver, const char* pszFileNameMatl, 
			const char* pszNameMatl, URect* pRectUV = nullptr);


		void UpdateUV(URect* pRectUV);

		void ActiveTexture(int indMesh, int indTex);


	public:
		Vector3& maxWS() { return m_v3MaxWS; }
		Vector3& minWS() { return m_v3MinWS; }


	private:
		void Destroy();

	private:
		CRect* m_pRect;

		Vector3 m_v3MaxWS;
		Vector3 m_v3MinWS;
	};
}




#endif