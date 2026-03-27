/*
CSpace

Author: Zhen Yi

Created Date: May 10, 2021

Version: 0.2.0 Alpha

*/

#ifndef _FW_SPACE_
#define _FW_SPACE_


#include"CConstruct.h"
#include"CFrame.h"
#include"MathLibrary.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class DLLCOAPI CSpace : public CConstruct
	{
	public:
		CSpace();
		virtual ~CSpace();

		void Create(Vector3& pos, Vector3& forward, Vector3& up);
		bool Clone(CSpace& spaceSrc);

		void Eular(float angleX, float angleY, float angleZ);

	//attribute
	public:
		CFrame& frame() { return *m_pFrame; }
		Matrix4x4& matOutput() { return m_matOutput; }

		Vector3& pos() { return m_v4Position.v3; }
		Vector3& up() {  return m_pFrame->up(); }
		Vector3& forward() { return m_pFrame->forward(); }
		Vector3& left() { return m_pFrame->left(); }


	private:
		CFrame* m_pFrame;
		Vector4 m_v4Position;

		Matrix4x4 m_matOutput;
	};

}

#endif // !_FW_SPACE_
