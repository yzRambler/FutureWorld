/*


CRectangel  ( like CBox )

Author: Zhen Yi (взеђ)

Created  Date: Sep. 11,  2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_RECTANGEL_
#define _FW_RECTANGLE_


#include"CComesh.h"
#include"CRect.h"

namespace FW
{

	class DLLCOAPI CRectangle : public CComesh
	{
	private:
		//   1----2 
		//   |    |
		//   0----3

		typedef enum eBD
		{
			_01 = 0,
			_12,
			_23,
			_30,
			BDCOUNT
		}EBD;


	public:
		CRectangle(CConstruct* pHost);
		CRectangle(const char* pszName, CConstruct* pHost);
		virtual ~CRectangle();

		bool Create(Vector4& ltv, Vector3& offHor, Vector3& offVer, Matrix4x4& matWorld);
		void Transform(Matrix4x4& matWorld);
		void OnAreaUpdate(Vector4& ltv, Vector3& offHor, Vector3& offVer);

		//attribute
	public:
		CMaterial* material() { return m_pMatlShare; }


	private:
		void UpdateBorderArrayByRect();
		void SetupBorders();


		//private:
	protected:
		CRect* m_pRect;
		SBorder m_border[BDCOUNT];

		CMaterial* m_pMatlShare;
		FDWORD m_idMatl;

	};


}





#endif