/*

CUI



  The UI tree in scene is created by CSceneNode. The concern between a CUI object

and it's children is established by the host CConstruct object (not component host). i.e,

all message are transferred through the host pointer.
  


Author: Zhen Yi.  взеђ

Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_UI_
#define _FW_UI_

#include"CComponent.h"
#include"CommonUI.h"
#include"CMessage.h"
#include"FWUIExport.h"
#include"CUIMsgListener.h"
#include"CBound.h"
#include"CRender.h"
#include"CRectImage.h"


namespace FW
{
	class CRender;
	class DLLCOAPI CUI : public CComponent
	{
	public:
		typedef enum eStageUi {
			//STG_NORMAL = 0, STG_HOVER
			STG_UNFOCUS, STG_FOCUS
		}ESTAGEUI;

	private:
		typedef std::vector<CMsgBase*> VTMSG;
		typedef VTMSG::iterator VTMSG_ITER;

		//Inherit from CComponent
	public:
		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent);


	public:
		CUI(const char* pszName, CConstruct* pHost,	EUITYPE typeUI = EUITYPE::UI_UNKNOW);
		virtual ~CUI();

		virtual bool Create(SRECT& block, float fDist2Cam,	const char* pszNameFileMatl, const char* pszNameMatl);


		virtual bool ProcessMsg(CMsgBase& msg);




	//atrribute
	public:
		FDWORD idRndHost()
		{
			return m_pRender->id();
		}
		ESTAGEUI stage() { return m_stageUI; }
		EUITYPE typeUI() { return m_typeUI; }
		void setTypeUI(EUITYPE type) { m_typeUI = type; }

		CUIMsgListener* listener() { return m_pUIMsgLst; }

		Vector3* maxWS() { if (nullptr == m_pRender) { return nullptr; } return &((CRectImage*)m_pRender->comesh())->maxWS(); }
		Vector3* minWS() { if (nullptr == m_pRender) { return nullptr; } return &((CRectImage*)m_pRender->comesh())->minWS(); }

		


	private:
		void Destroy();


	protected:
		ESTAGEUI m_stageUI;

		CRender* m_pRender;


	private:
		EUITYPE m_typeUI;

		//The matrix from screen space into world space.
		static Matrix4x4 m_sMatS2W;

		const float STEP;
		int m_nLevel;
		float m_fDepth;


		//message list
		CUIMsgListener* m_pUIMsgLst;


	};

}




#endif // !_FW_UI_
