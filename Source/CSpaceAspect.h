/*

CSpaceAspect


Author:  Zhen Yi

Created Date: Nov. 1, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_SPACE_ASPECT_
#define _FW_SPACE_ASPECT_


#include"CAspect.h"
#include"CFrame.h"
#include"MathLibrary.h"


namespace FW
{
	class CSpaceAspect : public CAspect
	{
	public:
		CSpaceAspect();
		virtual ~CSpaceAspect();

		void Create(Vector3& pos, Vector3& forward, Vector3& up);
		void Create();

	//Inheriated from CAspect
	public:
	 	virtual bool Clone(CAspect* pAptSrc);
		virtual bool Copy(CAspect* pAptSrc);


	//attribute
	public:
		CFrame& frame() { return *m_pFrame; }

		Vector3& pos() { return m_v4Position.v3; }
		Vector3& up() { return m_pFrame->up(); }
		Vector3& forward() { return m_pFrame->forward(); }
		Vector3& left() { return m_pFrame->left(); }

		Matrix4x4& matTrans() { return m_matTrans; }

	private:
		CFrame* m_pFrame;
		Vector4 m_v4Position;
		Matrix4x4 m_matTrans;
	};
}



#endif // !_FW_SPACE_ASPECT_
