/*
CEssety

    CEssety describe the image of the esse.
	A CEssety object like a entity.

Author:  Zhen Yi
Created Date: Feb. 06, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_ESSETY_
#define _FW_ESSETY_

#include<vector>

#include"IPrimatterManager.h"
#include"IRenderManager.h"

#include"CConstruct.h"
#include"CComponent.h"
#include"FWEngineCoreExport.h"
#include"CMessage.h"


namespace FW
{
	class CBound;
	class CRender;
	class CSceneNode;
	class CEssetyMsgListener;
	class DLLCOAPI CEssety : public CConstruct
	{
	private:
		typedef std::vector<CComponent*> VTCOM;
		typedef VTCOM::iterator VTCOM_ITER;

		typedef std::vector<CRender*> VTREN;
		typedef VTREN::iterator VTREN_ITER;


	//Inherit from CConstruct
	public:
		void Update(float ratio, long lDltTime, IPrimatterManager* pPmtCent, 
			IRenderManager* pRenderMag);


	public:
		CEssety(CConstruct* pHost);
		CEssety(const char* pszName, CConstruct* pHost);
		virtual ~CEssety();

		bool Create();
		void SetBound();

		void AddComponent(CComponent* pCom);
		void AddSubRender(CRender* pRnd);

		CComponent* SearchComponent(ECOMTYPE type, const char* pszName);
		CComponent* GetComponent(ECOMTYPE type)
		{	for (VTCOM_ITER iter = m_vtComponent.begin(); iter != m_vtComponent.end(); ++iter)
			{  if ((*iter)->type() == type) { return *iter; } }
			return 0;
		}

		void PlayCurrentAni();
		void StopCurrentAni();


		virtual bool ProcessMsg(CMsgBase& msg);


	private:
		void Destory();



	//attribute
	public:
		int sizeComponentArray() { return m_vtComponent.size(); }
		CComponent* component(int index)
		{
			if ((index < 0) || (index >= m_vtComponent.size())) { return 0; }
			return m_vtComponent[index];
		}

		CEssetyMsgListener* listener();

		CBound& bound() { return *m_pBound; }


	private:
		VTCOM m_vtComponent;

		//If the major component object which be defined by the CComesh at CRender is a model, 
		//the sub render means bounding box or local coordinate system. If the major component
		//object is a UI, the sub render means some concern of CRectangle objects. 
		//Donot delete the members just clear its, because the data is just reference. 
		VTREN m_vtSubRender;
		CEssetyMsgListener* m_pListener;

		CBound* m_pBound;

		bool m_bInit;
	};

};



#endif // !_FW_ESSETY_


