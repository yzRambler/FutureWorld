/*

CCoordsys:   coordinate system


Author: Zhen Yi   взеђ

Created Date:  Jan. 28, 2024

Version: 0.2.0 Alpha

*/



#ifndef _FW_COORDINATE_SYS_
#define _FW_COORDINATE_SYS_


#include"CComesh.h"


namespace FW
{
	class CMaterial;
	class CSpace;
	class DLLCOAPI CCoordSys : public CComesh
	{
	public:
		CCoordSys(CConstruct* pHost);
		CCoordSys(const char* pszName, CConstruct* pHost);
		virtual ~CCoordSys();

		bool Create(Vector3& pos, Vector3& forward, Vector3& up);

		//Inheriated from CComesh
	public:
		virtual void Update(CEssety* pEssety);


	private:
		bool CreateMaterial();
		void Destroy();

	private:
		CSpace* m_pSpace;
		CMaterial* m_pMatlShare;
		FDWORD m_idMatl;

		float m_fLenAxis;
	};


}



#endif // !_FW_COORDINATE_SYS_
