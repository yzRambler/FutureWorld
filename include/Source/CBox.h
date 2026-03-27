/*

CBox


Author:  Zhen Yi.

Created Date: Jan. 2, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_BOX_
#define _FW_BOX_

#include"CComesh.h"


namespace FW
{
	class CAABB;
	class CMaterial;
	class DLLCOAPI CBox : public CComesh
	{
	private:
		//  The vertex order of AABB. 
		// 
		//	    3----2
        //     /|   /|
        //    / 7--/-6
        //   0----1 /
        //   |/   |/
        //   4----5


		//the edge of AABB
		typedef enum eBD
		{
			_01 = 0,
			_12,
			_23,
			_30,
			_45,
			_56,
			_67,
			_74,
			_04,
			_15,
			_26,
			_37,
			BDCOUNT
		}EBD;

		//Inheriated from CComesh
	public:
		virtual void Update(CEssety* pEssety);

		//Inheriated from CComesh
	protected:
		virtual void CleanAllMesh();



	public:
		CBox(CConstruct* pHost);
		CBox(const char* pszName, CConstruct* pHost);
		virtual ~CBox();

		bool Create();
		bool Create(Vector3& v3Max, Vector3& v3Min, Matrix4x4& matWorld);
		void OnAreaUpdate(Vector3& v3Max, Vector3& v3Min, Matrix4x4& matWorld);



		//attribute
	public:
		Vector3& center();



	private:
		void UpdateBordersByAABB();


	private:
		CAABB* m_pAABB;
		SBorder m_border[EBD::BDCOUNT];

		CMaterial* m_pMatlShare;
		FDWORD m_idMatl;
	};
}



#endif // _FW_BOUND_
