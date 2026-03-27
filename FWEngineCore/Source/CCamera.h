/*

CCamera
          
	OpenGL coordinate system.  ( right hand )


Author:  Zhen Yi

Created Date: May 7, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_CAMERA_
#define _FW_CAMERA_


#include<vector>
#include"IInputDevice.h"
#include"CSceneNode.h"
#include"CComponent.h"
#include"BaseData.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class CCommand;
	class DLLCOAPI CCamera : public CIOListener, public CComponent
	{
	private:
		typedef std::vector<CCommand*> VTCMD;
		typedef VTCMD::iterator VTCMD_ITER;

	public:
		CCamera(CConstruct* pHost, //CEssety* pComHost, 
			ECAMERATYPE typeCam = ECAMERATYPE::CAM_PERSPECT);

		CCamera(const char* pszName, CConstruct* pHost, //CEssety* pComHost, 
			ECAMERATYPE typeCam = ECAMERATYPE::CAM_PERSPECT);

		virtual ~CCamera();

		/*
		    Perspective camera: paramA == aspect,  paramB == fov  <= The fov is angle but not radian.
			Orthographic camera: paramA == width,  paramB == height

			The near and far are all distance. So all are larger or equal than zero.
		*/
		bool Create(float paramA, float paramB, float near, float far, Vector4& v4ViewPort,  int orderSpace, 
			int orderTime, FDWORD idSpaceTime, int targetScreenID, ECAMERATYPE type = ECAMERATYPE::CAM_PERSPECT);

		void CreateMatrixS2W(float widthScr, float hightScr);


		void GenerateViewPort(int width, int height);

		void AddCommand(CCommand* pCmd) { m_vtCommand.push_back(pCmd); }
		void PerformCommand();

		

	//Inherite from CIOListener
	public:
		virtual void OnKeyUp(int vk);
		virtual void OnMouseDrag(float dx, float dy);


	//Inherite from CConstruct
	public:
		virtual void Update(float ratio, long lDltTime, IPrimatterManager* pPmtCent, IRenderManager* pRenderMag);


	//Inherite from CComponent
	public:
		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent);


	//attribute
	public:
		ECAMERATYPE typeCamera() { return m_typeCamera; }

		const Matrix4x4& matView() { return m_matView; }
		const Matrix4x4& matProjection() { return m_matProject; }

		const Vector3& pos();
		const Vector3& forward();
		const Vector3& up();


		float aspectRation() { return m_aspect; }
		void setAspectRation(float ration) { m_aspect = ration; }

		float FOV() { return m_fov; }
		void setFOV(float fov) { m_fov = fov; }

		float near() { return m_fN; }
		void setNear(float near) { m_fN = near; }

		float far() { return m_fF; }
		void setFar(float far) { m_fF = far; }

		void setXVP(int x) { m_nVPx = x; }
		int xViewPort() { return m_nVPx; }

		void setYVP(int y) { m_nVPy = y; }
		int yViewPort() { return m_nVPy; }

		void setWVP(int w) { m_nVPw = w; }
		int wViewPort() { return m_nVPw; }

		void setHVP(int h) { m_nVPh = h; }
		int hViewPort() { return m_nVPh; }

		int targetTimeOrder() { return m_nTargetTimeOrder; }

		int targetSpaceOrder() { return m_nTargetSpaceOrder; }

		int screenID() { return m_nTargeScreenId; }

		FDWORD targetSpaceTimeID() { return m_idTargetSpaceTime; }

		Vector4& viewPort() { return m_v4ViewPort; }

		Matrix4x4& matS2W() { return m_matS2W; }



	protected:
		void UpdateMatView();
		void CreatePerspectiveProjectionMatrix();
		void CreateOrthographicProjectionMatrix();

	private:
		//OpenGL row matrix
		Matrix4x4 m_matView;

		//OpenGL row matrix
		Matrix4x4 m_matProject;

		//--start Just for perspective projection
		float m_aspect;
		float m_fov;  //in radian. (changed into)
		//--end

		float m_fN;
		float m_fF;
		float m_fT;
		float m_fB;
		float m_fL;
		float m_fR;

		Vector4 m_v4ViewPort;
		int m_nVPx;
		int m_nVPy;
		int m_nVPw;
		int m_nVPh;


		VTCMD m_vtCommand;
		Vector4 m_v4Temp;

		ECAMERATYPE m_typeCamera;

		int m_nTargetTimeOrder;
		int m_nTargetSpaceOrder;
		int m_nTargeScreenId;
		FDWORD m_idTargetSpaceTime;

		float m_fSpeed;
		float m_fDltTime;

		//The matrix from screen space into world space by this camera.
		Matrix4x4 m_matS2W;
	};
}

#endif // !_FW_CAMERA_
