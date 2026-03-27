/*

CFrame:  
    Adopt right-hand rule in FutureWorld. In this case, the x/y/z-axis separately correspond to  left/up/forward 
  direction traditionally. So, it's necessary to make change for creating the right/up/forward frame. 
    It establish right-hand coordinate system.

	Gave up right axis?  Replace right axis with left axis ??

Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/



#ifndef _FW_FRAME_
#define _FW_FRAME_

#include"MathLibrary.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	

	//Right-hand Coordinate System
	class DLLCOAPI CFrame
	{
	public:
		CFrame();
		virtual~CFrame();

		void Create(const Vector3& forward, const Vector3& up);

		//around the x-axis
		void Pitch(float angle, bool global = true);

		//around the y-axis
		void Yaw(float angle, bool global = true);

		//around the z-axis
		void Roll(float angle, bool global = true);


		virtual void Transform(Matrix4x4 mat);


	//attribute
	public:
		Vector3& forward() { return m_v4Forward.v3; }
		Vector3& up() { return m_v4Up.v3; }
		Vector3& left() { return m_v4Left.v3; }
		//Matrix4x4& getMat() { return m_matRt; }

		const Matrix4x4& matRotation() { return m_matRt; }
		void resetMatRotation() { m_matRt.Identity(); }

		const Matrix4x4& matLocalRotation() { return m_matLocalRt; }
		void resetMatLocalRotation() { m_matLocalRt.Identity(); }

	private:
		void SetLocalRtMatrix();
		void RotateAroundDt(Vector3& v3Direct, float angle, Matrix4x4& outMat);

	protected:
		Vector3 m_v3Forward;
		Vector3 m_v3Up;
		Vector3 m_v3Right;
		Vector3 m_v3Left;

		Matrix4x4 m_matTmp;
		Matrix4x4 m_matTmp2;

		//The rotation matrix of concatenation transform.
		//example: Yaw * Pitch * Roll.
		Matrix4x4 m_matRt;  
		                    
		//The matrix transforming into local coordination system. 
		Matrix4x4 m_matLocalRt;

		Vector4 m_v4Forward;
		Vector4 m_v4Up;
		Vector4 m_v4Right;
		Vector4 m_v4Left;

		Vector4 m_v4ForwardOrg;
		Vector4 m_v4UpOrg;
		Vector4 m_v4LeftOrg;
	};



	//------------------------


	//Note: CAFrame define a specific afine frame which is just orthogonal vectors and 
	// matrices but not common afine frame.
	class DLLCOAPI CAFrame : public CFrame
	{
		//Herite from CFrame
	public:
		virtual void Transform(Matrix4x4 mat);


	public:
		CAFrame();
		virtual ~CAFrame();

		void Create(const Vector3& forward, const Vector3& up, const Vector3& position);

	//attribute
	public:
		Vector3& pos() { return m_v4Pos.v3; }
		Matrix4x4& matG2Local() { return m_matToLocal; }
		Matrix4x4& matL2Global() { return m_matToGlobal; }


	private:
		void UpdateFrameMatrix();

	protected:
		Vector4 m_v4Pos;
		Vector4 m_v4PosOrg;

		Vector4 m_v4TmpOff;
		Vector3 m_v3TmpX;
		Vector3 m_v3TmpY;
		Vector3 m_v3TmpZ;

		//The affine frame matrix (m_matAFrame) correspond to a affine frame.
		AMatrix4x4 m_amtAFrame;

		Matrix4x4 m_matToLocal;
		Matrix4x4 m_matToGlobal;
	};

	

}

#endif // !_FW_FRAME_
