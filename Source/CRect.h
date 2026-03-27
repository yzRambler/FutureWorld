/*

CRect:
    Note:  Two points on plane cannot define a unique rectangle. So, it's impossible to create a rectangle by three 
	parameters: left-top point, right-bottom point, the normal of rectangle vector.

Author:   Zhen  Yi

Created Data: Oct, 12, 2025

Version: 0.2.0 Alpha

*/

#ifndef _FW_RECT_
#define _FW_RECT_

#include"MathLibrary.h"


namespace FW
{

	class CRect
	{
	public:
		/*
		 TR_OP_LB:  transform original point is left-bottom point.
		 TR_OP_CE:  transform original point is center point.
		*/
		typedef enum { TR_OP_LB = 0, TR_OP_CE } ETOP;



	private:
		//   1----2 
		//   |    |
		//   0----3

	public:
		CRect() :m_fWidth(0.0f), m_fHeight(0.0f) {}
		virtual ~CRect() {}

		void Create(float ltx, float lty, float ltz, float rtx, float rty, float rtz,
			float rbx, float rby, float rbz, float lbx, float lby, float lbz)
		{
			m_aryVertex[0].x = lbx; m_aryVertex[0].y = lby; m_aryVertex[0].z = lbz;
			m_aryVertex[1].x = ltx; m_aryVertex[1].y = lty; m_aryVertex[1].z = ltz;
			m_aryVertex[2].x = rtx; m_aryVertex[2].y = rty; m_aryVertex[2].z = rtz;
			m_aryVertex[3].x = rbx; m_aryVertex[3].y = rby; m_aryVertex[3].z = rbz;

			SetWComponetOfConer();

			Reset();
		}

		/*
		  lt: left-top
		  horDirt: Horizon direction, is unit vector which positive is from the edge "01" to "32".
		  verDirt: Vertical direction, is unit vector which positive is from the edge "12" to "03".
		*/
		void Create(Vector3& lt, Vector3& horDirt, Vector3& verDirt, float w, float h)
		{
			m_aryVertex[0].v3 = lt + verDirt * h;
			m_aryVertex[1].v3 = lt;
			m_aryVertex[2].v3 = lt + horDirt * w;
			m_aryVertex[3].v3 = m_aryVertex[0].v3 + horDirt * w;

			SetWComponetOfConer();

			Reset();
		}

		/*
		  lt: left-top point
		  rt: right-top point
		  rb: right-bottom point
		*/
		void Create(Vector3& lt, Vector3& rt, Vector3& rb)
		{
			m_aryVertex[1].v3 = lt;
			m_aryVertex[2].v3 = rt;
			m_aryVertex[3].v3 = rb;
			m_aryVertex[0].v3 = m_aryVertex[1].v3 - m_aryVertex[2].v3 + m_aryVertex[3].v3;

			SetWComponetOfConer();

			Reset();
		}



		/*
		  ltp: left-top point
		  offHor: horizon off vector.   orientation + lenth
		  offVer: vertical off vector.   orientation + lenth
		*/
		void Create(Vector4& ltp, Vector3& offHor, Vector3& offVer)
		{
			m_aryVertex[1] = ltp;
			m_aryVertex[2].v3 = m_aryVertex[1].v3 + offHor;
			m_aryVertex[3].v3 = m_aryVertex[2].v3 + offVer;
			m_aryVertex[0].v3 = m_aryVertex[1].v3 + offVer;

			SetWComponetOfConer();

			Reset();

		}



		/*
		  Conside:  mat = M_rotation * M_transfer * M_Scale.
		*/
		void Transform(Matrix4x4& mat, ETOP e = ETOP::TR_OP_CE) 
		{

			Vector4 vop; //vcc locate at original point. 
			vop.w = 1.0f;
			vop = Mul4(vop, mat);

			if (e == ETOP::TR_OP_CE)
			{
				Vector4 v1c = m_aryVertex[1] - m_center;   //just get the off vector, i.e. orientation vector.
				Vector4 v2c = m_aryVertex[2] - m_center;
				Vector4 v3c = m_aryVertex[3] - m_center;

				m_center.v3 += vop.v3;

				m_aryVertex[1] = Mul4(v1c, mat) + m_center;
				m_aryVertex[2] = Mul4(v2c, mat) + m_center;
				m_aryVertex[3] = Mul4(v3c, mat) + m_center;
				m_aryVertex[0] = m_aryVertex[1] - m_aryVertex[2] + m_aryVertex[3];

			}
			else
			{
				Vector4 v10 = m_aryVertex[1] - m_aryVertex[0];   //just get the off vector, i.e. orientation vector.
				Vector4 v20 = m_aryVertex[2] - m_aryVertex[0];
				Vector4 v30 = m_aryVertex[3] - m_aryVertex[0];

				m_aryVertex[0].v3 += vop.v3;

				m_aryVertex[1] = Mul4(v10, mat) + m_aryVertex[0];
				m_aryVertex[2] = Mul4(v20, mat) + m_aryVertex[0];
				m_aryVertex[3] = Mul4(v30, mat) + m_aryVertex[0];
			}

			Reset();
		}



		void Update(Vector3& lt, Vector3& offHor, Vector3& offVer)
		{
			Create(lt, offHor, offVer);
		}



		/*
		//lb: left bottom
		//rt: right top
		//nor: the normal of rectangle
		void Create(Vector3& lb, Vector3& rt, Vector3& nor){}
		*/

		//attribute:
	public:
		static const int count() { return COUNT; }
		Vector3* vertex(int n) { if (n<0 || n>COUNT - 1) { return nullptr; } return &m_aryVertex[n].v3; }
		Vector3& center() { return m_center.v3; }

		/*
		1. Get the projection p of v on the CRect plane defined by two edges 01 and 03.
		2. Check whether the p is in the CRect square.
		*/
		bool beInside(Vector3& v) 
		{
			float y = m_Y.v3.Dot(v - m_aryVertex[0].v3);
			float x = m_X.v3.Dot(v - m_aryVertex[0].v3);
			return (y > 0.0f) && (y < m_fHeight) && (x > 0.0f) && (x < m_fWidth);
		}


	private:
		void SetWComponetOfConer()
		{
			for (int i = 0; i < COUNT; i++)
			{
				m_aryVertex[i].w = 1.0f;
			}
		}

		void Reset()
		{
			m_center = (m_aryVertex[0] + m_aryVertex[3]) * 0.5f;
			m_Y = m_aryVertex[1] - m_aryVertex[0];   //Now, the m_Y.w = 0.0f
			m_fHeight = m_Y.v3.Len();
			m_Y.v3.Normalize();

			m_X = m_aryVertex[3] - m_aryVertex[0];      //Now, the m_X.w = 0.0f
			m_fWidth = m_X.v3.Len();     
			m_X.v3.Normalize();
		}


	private:	
		static const int COUNT = 4;
		Vector4 m_aryVertex[COUNT];
		Vector4 m_center;
		Vector4 m_Y;
		Vector4 m_X;
		float m_fWidth;
		float m_fHeight;
	};


}





#endif // !_FW_RECT_
