#include "CCamera.h"
//#include"CInputDevice.h"
#include"CTime.h"
#include"FragmentOperation.h"
#include <GL/glew.h>
#include"CEssety.h"


using namespace FW;

//static IInputDevice* g_pInputDev = CreateInputDevice();


CCamera::CCamera(CConstruct* pHost, //CEssety* pComHost, 
	ECAMERATYPE typeCam /*= ECAMERATYPE::CAM_PERSPECT*/) : 
	CComponent(pHost, //pComHost, 
		ECOMTYPE::CO_CAMERA), 
	m_typeCamera(typeCam), m_aspect(0.0), m_fov(0.0),
	m_fN(0.0), m_fF(0.0), m_fT(0.0), m_fB(0.0), m_fL(0.0), m_fR(0.0), m_fSpeed(300.0f), 
	m_fDltTime(0.0f),
	m_nTargetTimeOrder(-1), m_nTargetSpaceOrder(-1), m_nTargeScreenId(-1), m_idTargetSpaceTime(0)
{
	m_vtCommand.clear();
	m_v4ViewPort.Clean();
}



CCamera::CCamera(const char* pszName, CConstruct* pHost, //CEssety* pComHost, 
	ECAMERATYPE typeCam /*= ECAMERATYPE::CAM_PERSPECT*/) : CComponent(pszName, pHost, //pComHost,
		ECOMTYPE::CO_CAMERA), 
	/*m_pFrameBuf(0),*/ m_typeCamera(typeCam), m_aspect(0.0), m_fov(0.0), m_fN(0.0), 
	m_fF(0.0), m_fT(0.0), m_fB(0.0), m_fL(0.0), m_fR(0.0), m_fSpeed(300.0f), m_fDltTime(0.0f), 
	m_nTargetTimeOrder(-1), m_nTargetSpaceOrder(-1),
	m_nTargeScreenId(-1), m_idTargetSpaceTime(0)
{
	m_vtCommand.clear();
	m_v4ViewPort.Clean();
}



CCamera::~CCamera()
{
	for (VTCMD_ITER iter = m_vtCommand.begin(); iter != m_vtCommand.end(); ++iter)
	{
		if (*iter != 0)
		{
			delete *iter;
		}
	}

	m_vtCommand.clear();
}


void CCamera::PerformCommand()
{
	for (VTCMD_ITER iter = m_vtCommand.begin(); iter != m_vtCommand.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Execute();
		}
	}
}


void CCamera::Update(float ratio, long lDltTime, IPrimatterManager* pPmtCent, IRenderManager* pRenderMag)
{
	m_fDltTime = lDltTime;
	UpdateMatView();
}



void CCamera::Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent)
{
	m_fDltTime = lDltTime;
	UpdateMatView();
}




void CCamera::OnKeyUp(int vk)
{
	if (vk == 'A')   //to left
	{
		//m_v3Pos += -m_jFrame.getRight() * fdlt * m_fSpeed;
		//m_jTransform.MoveToRight(-fdlt * m_fSpeed);
		//m_jTransform.MoveToRight(-m_fDltTime * m_fSpeed);
	}
	else if (vk == 'D')    //to right
	{
		//m_v3Pos += m_jFrame.getRight() * fdlt * m_fSpeed;
		//m_jTransform.MoveToRight(fdlt * m_fSpeed);
		//m_jTransform.MoveToRight(m_fDltTime * m_fSpeed);
	}
	else if (vk == 'W')    //forward
	{
		//m_v3Pos += -m_jFrame.getForward() * fdlt * m_fSpeed;
		//m_jTransform.MoveToForward(fdlt * m_fSpeed);
		//m_jTransform.MoveToForward(m_fDltTime * m_fSpeed);
	}
	else if (vk == 'S')   //backward
	{
		//m_v3Pos += m_jFrame.getForward() * fdlt * m_fSpeed;
		//m_jTransform.MoveToForward(-fdlt * m_fSpeed);
		//m_jTransform.MoveToForward(-m_fDltTime * m_fSpeed);
	}
}




void CCamera::OnMouseDrag(float dx, float dy)
{
	//m_jTransform.getFrame().Yaw(dx * 0.5f);
	//m_jTransform.getFrame().Pitch(dy * 0.5f);
}

void CCamera::CreateMatrixS2W(float widthScr, float hightScr)
{
	m_matS2W.Zero();
	m_matS2W.SetElt(0, 0, 1);
	m_matS2W.SetElt(1, 1, -1);
	m_matS2W.SetElt(3, 3, 1);
	m_matS2W.SetElt(3, 1, hightScr);


	//Get the transform matrix from OpenGL screen coordinates into clip space (CVV). 
	//Reference of the paper "Transform".
	Matrix4x4 matS2V;

	//The matrix is some differe from paper "Transform", because the transform from Screnn space 
	// into CVV space is inverse in X axis.
	const Vector4 r3(1.0f, 1.0f, 0.0f, 1.0f);
	matS2V.SetElt(0, 0, -2.0f / (float)widthScr);
	matS2V.SetElt(1, 1, -2.0f / (float)hightScr);
	matS2V.SetRow(3, r3);

	m_matS2W *= matS2V;


	Matrix4x4 matWork = m_matProject;
	matWork.Inverse();
	m_matS2W *= matWork;

	matWork = m_matView;
	matWork.Inverse();
	m_matS2W *= matWork;
}


bool CCamera::Create(float paramA, float paramB, float near, float far, Vector4& v4ViewPort, int orderSpace,
	int orderTime, FDWORD idSpaceTime, int targetScreenID, ECAMERATYPE type/*= ECAMERATYPE::CAM_PERSPECT*/)
{
	m_nTargetSpaceOrder = orderSpace;
	m_nTargetTimeOrder = orderTime;
	m_nTargeScreenId = targetScreenID;
	m_idTargetSpaceTime = idSpaceTime;
		
	UpdateMatView();

	m_typeCamera = type;
	switch (m_typeCamera)
	{
	case ECAMERATYPE::CAM_PERSPECT:
	{
		m_aspect = paramA;
		m_fov = AngleToRadian(paramB);
		m_fN = -near;
		m_fF = -far;

		CreatePerspectiveProjectionMatrix();

	}
	break;

	case ECAMERATYPE::CAM_ORTHOGRA:
	{
		float fx = paramA * 0.5f;     // fx = width/2.0
		float fy = paramB * 0.5f;     // fy = height/2.0
		
		m_fL = fx;
		m_fR = -m_fL;
		m_fT = fy;
		m_fB = -m_fT;
		m_fN = -near;
		m_fF = -far;

		CreateOrthographicProjectionMatrix();


	}
	break;

	default:
	{
		return false;
	}
	break;
	}


	m_v4ViewPort = v4ViewPort;

	return true;
}





void CCamera::GenerateViewPort(int width, int height)
{
	m_nVPx = m_v4ViewPort.x;
	m_nVPy = m_v4ViewPort.y;
	m_nVPw = m_v4ViewPort.z * width;
	m_nVPh = m_v4ViewPort.w * height;

	AddCommand(new CViewPortSet(m_nVPx, m_nVPy, m_nVPw, m_nVPh));
}



inline const Vector3& CCamera::pos()
{
	return ((CSceneNode*)((CEssety*)host())->host())->spaceWorld()->pos();
}


inline const Vector3& CCamera::forward()
{
	return ((CSceneNode*)((CEssety*)host())->host())->spaceWorld()->forward();
}


inline const Vector3& CCamera::up()
{
	return ((CSceneNode*)((CEssety*)host())->host())->spaceWorld()->up();
}



void CCamera::UpdateMatView()
{
	CEssety* pEstHost = (CEssety*)host();
	if((nullptr == pEstHost)||(nullptr == pEstHost->host()))
	{
		return;
	}

	m_matView.Identity();

	CSceneNode* pSceneNode = (CSceneNode*)pEstHost->host();

	m_matView.SetColV3AT(0, pSceneNode->spaceWorld()->frame().left()); //.getLeft());
	m_matView.SetColV3AT(1, pSceneNode->spaceWorld()->frame().up());//.getUp());
	m_matView.SetColV3AT(2, -pSceneNode->spaceWorld()->frame().forward());//.getForward());

	m_v4Temp.x = -Dot(pSceneNode->spaceWorld()->pos(), pSceneNode->spaceWorld()->frame().left());//.getLeft());
	m_v4Temp.y = -Dot(pSceneNode->spaceWorld()->pos(), pSceneNode->spaceWorld()->frame().up());// .getUp());
	m_v4Temp.z = -Dot(pSceneNode->spaceWorld()->pos(),
		-pSceneNode->spaceWorld()->frame().forward());//.getForward());
	m_v4Temp.w = 1.0f;



	m_matView.SetRow(3, m_v4Temp);

}


void CCamera::CreatePerspectiveProjectionMatrix()
{
	m_fT = m_fN * tan(m_fov * 0.5f);
	m_fB = -m_fT;


	m_fL = m_fT * m_aspect;
	m_fR = -m_fL;

	m_matProject.Zero();
	m_matProject.SetRow(0, 2.0f * m_fN / (m_fL - m_fR), 0.0f, 0.0f, 0.0f);
	m_matProject.SetRow(1, 0.0f, 2.0f * m_fN / (m_fT - m_fB), 0.0f, 0.0f);
	m_matProject.SetRow(2, (m_fL + m_fR) / (m_fL - m_fR), (m_fT + m_fB) / (m_fT - m_fB),
		-(m_fF + m_fN) / (m_fF - m_fN), -1.0f);
	m_matProject.SetRow(3, 0.0f, 0.0f, -2.0f * m_fF*m_fN / (m_fF - m_fN), 0.0f);
	
}



void CCamera::CreateOrthographicProjectionMatrix()
{
	m_matProject.Zero();
	m_matProject.SetRow(0, 2.0f / (m_fL - m_fR), 0.0f, 0.0f, 0.0f);
	m_matProject.SetRow(1, 0.0f, 2.0f / (m_fT - m_fB), 0.0f, 0.0f);
	m_matProject.SetRow(2, 0.0f, 0.0f, -2.0f / (m_fF - m_fN), 0.0f);
	m_matProject.SetRow(3, -(m_fR + m_fL) / (m_fL - m_fR), -(m_fT + m_fB) / (m_fT - m_fB), 
		-(m_fF + m_fN) / (m_fF - m_fN), 1.0f);

}