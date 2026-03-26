/*

CDataResource


Author:  Zhen  Yi

Created Date: Apr. 8, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_DATARESOURCE_
#define _FW_DATARESOURCE_

#include"IPrimatterManager.h"
#include"IAspectManager.h"
#include"IDataResource.h"


namespace FW
{


	class CDataResource : public IDataResource
	{
	//Inherit from IDataResource
	public:


		virtual bool Initialize(int widthWnd, int heightWnd, CIDManager& rIDMag, CMsgCenter& rMsgCet);
		virtual void Run();

		virtual CAspect* ApplyAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt);
		virtual EAPTSTATE InquireAspectState(CAspect* pPmtApt);
		virtual bool ReleaseAspect(const char* pszName, const char* pszNameFile, EAPTTYPE typeApt);

		virtual EAPPPRRES ApplyPrimatter(IPrimatterAspect* pIPmtApt, IPrimatter** ppPamt);
		virtual EPMTSTATE InquirePrimatterState(IPrimatterAspect* pPmtApt);
		virtual CMaterial* TakeMatrial(const char* pszNameFile, const char* pszNameMat);
		
		//Matching with ApplyPrimatterMajor
		virtual int ReleasePrimatter(IPrimatter* pPmt);


		//If the primatter is released in the primatter center, the outside primatter pointer is hungling
		//this check can be used to prevent to refer a invalid primatter pointer.
		virtual bool CheckValidRes(FDWORD id);

		//For: Search and refer the specific primatter again if the current id check is faild which mean the 
		//primatter has released.
		virtual IPrimatter* RequirePrimatter(const char* pszName, const char* pszNameFile, EPMTTYPE typePmt);
		virtual IPrimatterManager* IPrimatterMag() { return m_pIPmtMag; }



	public:
		CDataResource();
		virtual ~CDataResource();
		

	//attribute
	public:
		static CDataResource* Instance()
		{
			if (nullptr == m_pInstance)
			{
				m_pInstance = new CDataResource;
				m_pInstance->Create();
			}

			return m_pInstance;
		}

		static void Release()
		{
			if (nullptr != m_pInstance)
			{
				m_pInstance->Destroy();

				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}

		


	private:
		static void Create();
		static void Destroy();

	private:
		static CDataResource* m_pInstance;

		static IAspectManager* m_pIAptMag;
		static IPrimatterManager* m_pIPmtMag;

	};

}




#endif // !_FW_DATASOURCE_
