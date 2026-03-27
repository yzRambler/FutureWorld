#include"CFrame.h"

using namespace FW;

CFrame::CFrame()
{
	m_matTmp.Zero();
	m_matRt.Identity();
	m_matLocalRt.Identity();
}



CFrame::~CFrame()
{
}



void CFrame::Create(const Vector3& forward, const Vector3& up)
{
	/*
	m_v3Up = up;
	m_v3Left = ((Vector3&)up).Cross((Vector3&)forward);
	m_v3Forward = m_v3Left.Cross(m_v3Up);
	*/

	m_v3Up = up;
	m_v3Up.Normalize();

	m_v3Forward = forward;
	m_v3Forward.Normalize();

	m_v3Left = m_v3Up.Cross(m_v3Forward);
	m_v3Forward = m_v3Left.Cross(m_v3Up);

	m_v4ForwardOrg.SetVector(m_v3Forward);
	m_v4UpOrg.SetVector(m_v3Up);
	m_v4LeftOrg.SetVector(m_v3Left);

	m_v4Forward = m_v4ForwardOrg;
	m_v4Up = m_v4UpOrg;
	m_v4Left = m_v4LeftOrg;


	SetLocalRtMatrix();
}


void CFrame::SetLocalRtMatrix()
{
	m_matLocalRt.Identity();
	m_matLocalRt.SetColV3AT(0, m_v4Left.v3);
	m_matLocalRt.SetColV3AT(1, m_v4Up.v3);
	m_matLocalRt.SetColV3AT(2, m_v4Forward.v3);
}


/*
void CFrame::ResetMatrix()
{
	m_mat.Identity();
	//m_mat.SetCol(0, m_v4Right);

	m_mat.SetCol(0, m_v4Left);
	m_mat.SetCol(1, m_v4Up);
	m_mat.SetCol(2, m_v4Forward);


	//mat.SetColV3AT(0, v3Right);
	//mat.SetColV3AT(1, v3Up);
	//mat.SetColV3AT(2, v3Forward);
	//mat.SetElt(3, 3, 1.0);

}
*/



void CFrame::Pitch(float angle, bool global /* = true */)
{
	//generate rotation matrix
	if (global)
	{
		float rad = AngleToRadian(angle);
		float cs = cos(rad);
		float sn = sin(rad);

		m_matTmp.SetRow(0, 1.0f, 0.0f, 0.0f, 0.0f);
		m_matTmp.SetRow(1, 0.0f, cs, sn, 0.0f);
		m_matTmp.SetRow(2, 0.0f, -sn, cs, 0.0f);
		m_matTmp.SetRow(3, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_matTmp.Identity();
		RotateAroundDt(m_v4Left.v3, angle, m_matTmp);
	}


	m_matRt *= m_matTmp;

	//transform axis
	m_v4Forward = m_v4Forward * m_matTmp;
	m_v4Up.v3 = m_v4Forward.v3.Cross(m_v4Left.v3);
	SetLocalRtMatrix();


}



void CFrame::Yaw(float angle, bool global /* = true */)
{
	if (global)
	{
		float rad = AngleToRadian(angle);
		float cs = cos(rad);
		float sn = sin(rad);

		m_matTmp.SetRow(0, cs, 0.0f, -sn, 0.0f);
		m_matTmp.SetRow(1, 0.0f, 1.0f, 0.0f, 0.0f);
		m_matTmp.SetRow(2, sn, 0.0f, cs, 0.0f);
		m_matTmp.SetRow(3, 0.0f, 0.0f, 0.0f, 1.0f);

	}
	else
	{
		m_matTmp.Identity();
		RotateAroundDt(m_v4Up.v3, angle, m_matTmp);
	}

	m_matRt *= m_matTmp;

	m_v4Forward = m_v4Forward * m_matTmp;
	m_v4Left.v3 = m_v4Up.v3.Cross(m_v4Forward.v3);
	SetLocalRtMatrix();
}




void CFrame::Roll(float angle, bool global /* = true */)
{
	if (global)
	{
		float rad = AngleToRadian(angle);
		float cs = cos(rad);
		float sn = sin(rad);

		m_matTmp.SetRow(0, cs, sn, 0.0f, 0.0f);
		m_matTmp.SetRow(1, -sn, cs, 0.0f, 0.0f);
		m_matTmp.SetRow(2, 0.0f, 0.0f, 1.0f, 0.0f);
		m_matTmp.SetRow(3, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_matTmp.Identity();
		RotateAroundDt(m_v4Forward.v3, angle, m_matTmp);
	}

	m_matRt *= m_matTmp;

	m_v4Left = m_v4Left * m_matTmp;
	m_v4Up.v3 = m_v4Forward.v3.Cross(m_v4Left.v3);
	SetLocalRtMatrix();
}




void CFrame::RotateAroundDt(Vector3& v3Direct, float angle, Matrix4x4& outMat)
{
	float rad = AngleToRadian(angle);
	float cs = cos(rad);
	float sn = sin(rad);

	m_matTmp2.SetRow(0, 1.0f, 0.0f, 0.0f, 0.0f);
	m_matTmp2.SetRow(1, 0.0f, cs, sn, 0.0f);
	m_matTmp2.SetRow(2, 0.0f, -sn, cs, 0.0f);
	m_matTmp2.SetRow(3, 0.0f, 0.0f, 0.0f, 1.0f);

	Vector3 v3R = v3Direct;
	v3R.Normalize();

	float absX = abs(v3R.x);
	float absY = abs(v3R.y);
	float absZ = abs(v3R.z);


	Vector3 v3S;
	if (absX < absY)
	{
		if (absX < absZ)
		{
			v3S.x = 0; v3S.y = -v3R.z; v3S.z = v3R.y;
		}
		else
		{
			v3S.x = -v3R.y; v3S.y = v3R.x; v3S.z = 0.0f;
		}
	}
	else
	{
		if (absY < absZ)
		{
			v3S.x = -v3R.z; v3S.y = 0.0f; v3S.z = v3R.x;
		}
		else
		{
			v3S.x = -v3R.y; v3S.y = v3R.x; v3S.z = 0.0f;
		}
	}



	v3S.Normalize();

	Vector3 v3T = v3R.Cross(v3S);

	Matrix4x4 matTrans;
	matTrans.Identity();

	matTrans.SetRowV3AL(0, v3R);
	matTrans.SetRowV3AL(1, v3S);
	matTrans.SetRowV3AL(2, v3T);

	Matrix4x4 matTransInv = matTrans;
	matTransInv.Transpose();

	outMat = matTrans * m_matTmp2 * matTransInv;

}



void CFrame::Transform(Matrix4x4 mat)
{
	m_v4Forward = Mul4(m_v4ForwardOrg, mat);
	m_v4Up = Mul4(m_v4UpOrg, mat);

	m_v3Forward = m_v4Forward.v3;
	m_v3Up = m_v4Up.v3;
	m_v3Left = m_v3Up.Cross(m_v3Forward);

	m_v4Left.SetVector(m_v3Left);

	SetLocalRtMatrix();
}






//--------------------------------------




CAFrame::CAFrame()
{
}

CAFrame::~CAFrame()
{
}



void CAFrame::Create(const Vector3& forward, const Vector3& up, const Vector3& position)
{
	CFrame::Create(forward, up);
	m_v4PosOrg.SetPos(position);
	m_v4Pos = m_v4PosOrg;

	//set affine frame matrix
	UpdateFrameMatrix();

}

void CAFrame::UpdateFrameMatrix()
{
	//Wrong!
	//m_amtAFrame.SetRowV3AL(0, m_v3Left);
	//m_amtAFrame.SetRowV3AL(1, m_v3Up);
	//m_amtAFrame.SetRowV3AL(2, m_v3Forward);
	//m_amtAFrame.SetRow(3, Vector4(-m_v4Pos.v3, 1.0f));

	//m_matToGlobal = m_matToLocal = m_amtAFrame;
	//m_matToGlobal.Inverse();

	/////////////////////////////////////////////////////////

	//Get the transform matrix from world space into local space. 
	m_v4TmpOff.x = -m_v4Pos.v3.Dot(m_v3Left);
	m_v4TmpOff.y = -m_v4Pos.v3.Dot(m_v3Up);
	m_v4TmpOff.z = -m_v4Pos.v3.Dot(m_v3Forward);
	m_v4TmpOff.w = 1.0f;

	m_amtAFrame.SetColV3AT(0, m_v3Left);
	m_amtAFrame.SetColV3AT(1, m_v3Up);
	m_amtAFrame.SetColV3AT(2, m_v3Forward);
	m_amtAFrame.SetCol(3, m_v4TmpOff);

	m_matToLocal = m_amtAFrame;

	//m_matToGlobal = m_matToLocal;
	//m_matToGlobal.Inverse();


	//Get the transform matrix from local space into world space.
	//Solution m_matToGlobal, the inverse matrix of m_matToLocal, 
	//in optimize algorithm ( Reference to the paper "Transform" ).
	m_v3TmpX.x = m_v3Left.x;
	m_v3TmpX.y = m_v3Up.x;
	m_v3TmpX.z = m_v3Forward.x;

	m_v3TmpY.x = m_v3Left.y;
	m_v3TmpY.y = m_v3Up.y;
	m_v3TmpY.z = m_v3Forward.y;

	m_v3TmpZ.x = m_v3Left.z;
	m_v3TmpZ.y = m_v3Up.z;
	m_v3TmpZ.z = m_v3Forward.z;


	/*
	m_v4TmpOff.x = -m_v4TmpOff.v3.Dot(m_v3TmpX);
	m_v4TmpOff.y = -m_v4TmpOff.v3.Dot(m_v3TmpY);
	m_v4TmpOff.z = -m_v4TmpOff.v3.Dot(m_v3TmpZ);
	*/


	float fx = -m_v4TmpOff.v3.Dot(m_v3TmpX);
	float fy = -m_v4TmpOff.v3.Dot(m_v3TmpY);
	float fz = -m_v4TmpOff.v3.Dot(m_v3TmpZ);

	m_v4TmpOff.x = fx;
	m_v4TmpOff.y = fy;
	m_v4TmpOff.z = fz;

	m_matToGlobal.SetColV3AT(0, m_v3TmpX);
	m_matToGlobal.SetColV3AT(1, m_v3TmpY);
	m_matToGlobal.SetColV3AT(2, m_v3TmpZ);
	m_matToGlobal.SetCol(3, m_v4TmpOff);

}



void CAFrame::Transform(Matrix4x4 mat)
{
	CFrame::Transform(mat);

	m_v4Pos = Mul4(m_v4PosOrg, mat);

	UpdateFrameMatrix();
}



/*
void CAFrame::UpdateFrameMatrix()
{
	m_matAFrame.SetRowV3AL(0, m_v3Right);
	m_matAFrame.SetRowV3AL(1, m_v3Up);
	m_matAFrame.SetRowV3AL(2, m_v3Forward);
	m_matAFrame.SetRow(3, m_v4Position);
}
*/
