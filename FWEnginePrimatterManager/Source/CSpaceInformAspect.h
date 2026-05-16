/*

CSpaceInformAspect

Author: Zhen Yi
Date: May 07, 2021

*/

#ifndef _FW_SPACE_ASPECT_
#define _FW_SPACE_ASPECT_


#include "CComponentAspect.h"
#include"MathLibrary.h"

namespace FW
{
	class CSpaceInformAspect : public CComponentAspect
	{
	public:

		CSpaceInformAspect(CAspect* pHost, CEssetyAspect* pComHost);
		CSpaceInformAspect(const char* pszName, CAspect* pHost, CEssetyAspect* pComHost);

		virtual ~CSpaceInformAspect();

		void Initialize(Vector3& pos, Vector3& forward, Vector3& up);

		//Inherited from CComponentAspect
		//virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, IPrimatterManager* pPmtCent);

	//attribute
	public:
		//CFrame& frame() { return m_jFrame; }
		Vector3& pos() { return m_v3Pos; }
		Vector3& forward() { return m_v3Forward; }
		Vector3& up() { return m_v3Up; }

	private:
		//CFrame m_jFrame;
		Vector3 m_v3Pos;
		Vector3 m_v3Forward;
		Vector3 m_v3Up;
	};
}


#endif // !_FW_SPACE_ASPECT_




