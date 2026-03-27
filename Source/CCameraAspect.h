/*

CCameraAspect


Author: Zhen Yi

Created Date: Oct. 28, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_CAMERA_ASPECT_
#define _FW_CAMERA_ASPECT_

#include<vector>
#include"CComponentAspect.h"
#include"CCommandAspect.h"
#include"FWEnginePrimatterManagerExport.h"
#include"BaseData.h"
#include"MathLibrary.h"

namespace FW
{
	//class CSpaceInformAspect;
	class DLLPRAPI CCameraAspect : public CComponentAspect
	{
	public:
		//typedef enum { CAM_ORT, CAM_PER, CAM_UNKNOW } ECAMTYPE;
		


	private:
		typedef std::vector<CString*> VTOPT;
		typedef VTOPT::iterator VTOPT_ITER;

		typedef std::vector<CCommandAspect*> VTCMDAPT;
		typedef VTCMDAPT::iterator VTCMDAPT_ITER;

	public:
		CCameraAspect(CAspect* pHost);
		CCameraAspect(const char* pszName, CAspect* pHost);
		~CCameraAspect();

		bool Create();
		void GenerateSpaceTimeID();
		void AddClearOption(const char* pszOpt);
		void AddEnableOption(const char* pszOpt);
		void AddDisableOption(const char* pszOpt);

		void AddCommandAspect(CCommandAspect* pCmdApt) { m_vtCmdAspect.push_back(pCmdApt); }

	//Inherited from CComponentAspect
	public:
		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent, CEssetyAspect* pEsetyApt)
		{
			return EAPTSTATE::APT_READY;
		}


		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual CComponentAspect* CreateCoInstance(CEssetyAspect* pComHost);


	//attribute
	public:
		ECAMERATYPE camType() { return m_enCamType; }
		void setCamType(ECAMERATYPE type) { m_enCamType = type; }

		int countEnableOpt() { return m_vtEnable.size(); }
		const char* enableOption(int ind)
		{
			if ((ind < 0) || (ind >= m_vtEnable.size())) return 0; return m_vtEnable[ind]->Get();
		}

		int countDisableOpt() { return m_vtDisable.size(); }
		const char* disableOption(int ind)
		{  if ((ind < 0) || (ind >= m_vtDisable.size())) return 0; return m_vtDisable[ind]->Get(); }


		int countClearOpt() { return m_vtClear.size(); }
		const char* clearOption(int ind)
		{  if ((0 < ind) || (ind >= m_vtClear.size())) return 0; return m_vtClear[ind]->Get();  }



		float aspectRation() { return m_fAspectRatio; }
		void setAspectRation(float ration) { m_fAspectRatio = ration; }

		float FOV() { return m_fFOV; }
		void setFOV(float fov) { m_fFOV = fov; }

		float near() { return m_fNear; }
		void setNear(float near) { m_fNear = near; }

		float far() { return m_fFar; }
		void setFar(float far) { m_fFar = far; }

		float clearDepth() { return m_fClearDepth; }
		void setClearDepthValue(float val) 
		{ 
			m_fClearDepth = val;
			//m_vtCommOpt.push_back("setClearDepthVal");
			CString* pStr = new CString("setClearDepthVal");
			m_vtCommOpt.push_back(pStr);
		}


		float clearStencil() { return m_nClearStencil; }
		void setClearStencilValue(int val) 
		{ 
			m_nClearStencil = val; 
			//m_vtCommOpt.push_back("setClearStencilVal");
			CString* pStr = new CString("setClearStencilVal");
			m_vtCommOpt.push_back(pStr);
		}


		Vector4& viewPort() { return m_v4ViewPort; }
		void setViewPort(float fx, float fy, float fw, float fh) 
		{ m_v4ViewPort.x = fx; m_v4ViewPort.y = fy; m_v4ViewPort.z = fw; m_v4ViewPort.w = fh; }

		Vector4& clearColor() { return m_v4ClearColor; }
		void setClearColorValue(float r, float g, float b, float a) 
		{ 
			m_v4ClearColor.x = r; m_v4ClearColor.y = g; m_v4ClearColor.z = b, m_v4ClearColor.w = a; 
			//m_vtCommOpt.push_back("setClearColorVal");
			CString* pStr = new CString("setClearColorVal");
			m_vtCommOpt.push_back(pStr);
		}

		int targetSpaceOrder() { return m_nTargetSpaceOrder; }
		void setTargetSpaceOrder(int order) { m_nTargetSpaceOrder = order; }

		int targetTimeOrder() { return m_nTargetTimeOrder; }
		void setTargetTimeOrder(int order) { m_nTargetTimeOrder = order; }

		int screenID() { return m_nTargetScreenId; }
		void setTargetScreenID(int id) { m_nTargetScreenId = id; }

		FDWORD targetSpaceTimeID() { return m_idTargetSpaceTime; }



		int countCmdApt() { return m_vtCmdAspect.size(); }
		CCommandAspect* commandAspect(int index) 
		{ 
			if ((index < 0) || (index >= m_vtCmdAspect.size())) { return nullptr; } 
			return m_vtCmdAspect[index];
		}


		float width() { return m_fWidth; }
		void setWidth(float w) { m_fWidth = w; }

		float hight() { return m_fHight; }
		void setHight(float h) { m_fHight = h; }

	private:
		void AllOptionDestroy();


	private:

		//ECAMTYPE m_enCamType;
		ECAMERATYPE m_enCamType;

		float m_fAspectRatio;
		float m_fFOV;
		float m_fNear;
		float m_fFar;

		float m_fWidth;
		float m_fHight;

		//for Fragment Operation
		float m_fClearDepth;
		int m_nClearStencil;
		Vector4 m_v4ViewPort;   //x: x, y: y, z: width, w: height
		Vector4 m_v4ClearColor;   //x: r, y: g, z: b, w: a
		
		VTOPT m_vtEnable;
		VTOPT m_vtDisable;
		VTOPT m_vtClear;
		VTOPT m_vtCommOpt;

		FDWORD m_idTargetSpaceTime;
		int m_nTargetTimeOrder;
		int m_nTargetSpaceOrder;
		int m_nTargetScreenId;


		VTCMDAPT m_vtCmdAspect;


	};

}

#endif // !_FW_CAMERA_ASPECT_
