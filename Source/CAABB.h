/*
CAABB
    Axis Aligned Bounding Box
	right-hand law (up(y axis)-left(x axis)-forward(z axis)). 
	It always align the world coordinate system.

Author:  Zhen Yi

Created Date:  June 9, 2023

Version: 0.2.0 Alpha

*/



#ifndef _FW_AABB_
#define _FW_AABB_

//#include"Common.h"
#include"CFrame.h"
#include"MathLibrary.h"


namespace FW
{

	class  CAABB
	{
	private:
		//	    3----2
		//     /|   /|
		//    / 7--/-6
		//   0----1 /
		//   |/   |/
		//   4----5

		/*
		   Note: left is "<-",  right is "->" : for observer, but it's right-hand coordiante system,
		   so, left is "->", right is "<-". As a result, the max point is "FTL"(i.e. corner "1"), the 
		   min point is "BBR" (i.e. corner "7").
		*/
		typedef enum eVT
		{
			FTR = 0,     //front-top-right   corner  0
			FTL,         //front-top-left    corner  1
			BTL,         //back-top-left     corner  2
			BTR,         //back-top-right    corner  3
			FBR,         //front-bottom-right   corner  4
			FBL,         //front-bottom-left    corner  5
			BBL,         //back-bottom-left     corner  6
			BBR,         //back-bottom-right    corner  7
			CONCOUNT
		}EVT;


	public:
		CAABB();
		virtual ~CAABB();



		/*
		  Note: In default, axis Y is (0,1,0) and X is (1,0,0), so it's unnecessary to transfer them 
		  with parameters.

		  v3MaxMS: The max point position in model space.
		  v3MinMS: The min point position in model space.
		  pos: center point position in world space.
		*/
		void Create(Vector3& v3MaxMS, Vector3& v3MinMS, Vector3& pos);


		/*
		  v3MaxMS: It must be the max point position in model space;
		  v3MinMS: It must be the min point position in model space;
		  v3UpWS:  It must be the vertical projection vertor (to get horizontal project plane)
		           in world space.

		  v3ForwardWS: 
		           It must be the horizontal projection vertor (to get identical rectangle field on 
		           the project plane) in world space.

		  pCentWS: The center pointer position in world space. If it's null, the position in world 
		           space equal to model space.

		*/
		void Create(Vector3& v3MaxMS, Vector3& v3MinMS, 
			Vector3& v3UpWS, Vector3& v3ForwardWS, Vector3* pCentWS = nullptr);


		//temp
		void CreateWS(Vector3& v3MaxWS, Vector3& v3MinWS,
			Vector3& v3UpWS, Vector3& v3ForwardWS, Vector3* pCentWS = nullptr);


		/*
		  v3MaxMS: The max point position in model space;
		  v3MinMS: The min point position in model space;
		  v3UpWS:  The vertical projection vertor (to get horizontal project plane)
		           in world space.

		  v3ForwardWS: 
		           The horizontal projection vertor (to get identical rectangle field on 
		           the project plane) in world space.

		  v3CentWS: the center pointer position in world space.
		*/
		void Update(Vector3& v3MaxMS, Vector3& v3MinMS, 
			Vector3& v3UpWS, Vector3& v3ForwardWS, Vector3& v3CentWS);

		//temp
		void UpdateWS(Vector3& v3MaxWS, Vector3& v3MinWS);



		/*
		  v3MaxMS: The max point position in model space;
		  v3MinMS: The min point position in model space;
		  matM2W: The matrix transforming from model space into world space. 
		*/
		void Update(Vector3& v3MaxMS, Vector3& v3MinMS, Matrix4x4& matM2W);

		//attribute
	public:
		Vector3& center() { return m_v3Center; }
		int countVertices() { return CONCOUNT; }

		Vector3* vertex(int ind) { return (ind < 0 || ind >= CONCOUNT) ? 0 : &(m_box[ind].v3); }

		CAFrame& base() { return m_rCCBase; }

		bool inside(Vector3& point)
		{
			m_v4TmpPoint.v3 = point;
			m_v4TmpPoint.w = 1.0f;

			m_v4TmpPoint = Mul4(m_v4TmpPoint, m_rCCBase.matG2Local());

			return (m_v4TmpPoint.x > m_v3MinMS.x)&&(m_v4TmpPoint.y > m_v3MinMS.y)
				&&(m_v4TmpPoint.z > m_v3MinMS.z)&&(m_v4TmpPoint.x < m_v3MaxMS.x)
				&&(m_v4TmpPoint.y < m_v3MaxMS.y)&&(m_v4TmpPoint.z < m_v3MaxMS.z);
		}

		bool inside(float x, float y, float z)
		{
			m_v4TmpPoint.x = x;
			m_v4TmpPoint.y = y;
			m_v4TmpPoint.z = z;
			m_v4TmpPoint.w = 1.0f;

			m_v4TmpPoint = Mul4(m_v4TmpPoint, m_rCCBase.matG2Local());

			return (m_v4TmpPoint.x > m_v3MinMS.x) && (m_v4TmpPoint.y > m_v3MinMS.y)
				&& (m_v4TmpPoint.z > m_v3MinMS.z) && (m_v4TmpPoint.x < m_v3MaxMS.x)
				&& (m_v4TmpPoint.y < m_v3MaxMS.y) && (m_v4TmpPoint.z < m_v3MaxMS.z);
		}

		bool insideRect(Vector3& point)
		{
			m_v4TmpPoint.v3 = point;
			m_v4TmpPoint.w = 1.0f;

			m_v4TmpPoint = Mul4(m_v4TmpPoint, m_rCCBase.matG2Local());

			return (m_v4TmpPoint.x > m_v3MinMS.x) && (m_v4TmpPoint.y > m_v3MinMS.y)
				&& (m_v4TmpPoint.x < m_v3MaxMS.x) && (m_v4TmpPoint.y < m_v3MaxMS.y);
		}

		bool insideRect(float x, float y)
		{
			m_v4TmpPoint.Clean();
			m_v4TmpPoint.x = x;
			m_v4TmpPoint.y = y;
			m_v4TmpPoint.w = 1.0f;

			m_v4TmpPoint = Mul4(m_v4TmpPoint, m_rCCBase.matG2Local());

			return (m_v4TmpPoint.x > m_v3MinMS.x) && (m_v4TmpPoint.y > m_v3MinMS.y)
				&& (m_v4TmpPoint.x < m_v3MaxMS.x) && (m_v4TmpPoint.y < m_v3MaxMS.y);
		}


		bool insideRectWS(float x, float y, float z)
		{
			m_v4TmpPoint.Clean();
			m_v4TmpPoint.x = x;
			m_v4TmpPoint.y = y;
			m_v4TmpPoint.z = z;
			m_v4TmpPoint.w = 1.0f;


			return (m_v4TmpPoint.x > m_v3MinWS.x) && (m_v4TmpPoint.z > m_v3MinWS.z)
				&& (m_v4TmpPoint.x < m_v3MaxWS.x) && (m_v4TmpPoint.z < m_v3MaxWS.z);
		}


	private:
		void Clear();
		void UpdateAll();


	private:
		//front-top-left corner position in model space.
		Vector3 m_v3MaxMS;
		float m_fLenSquareMax;

		//back-bottom-right corner position in model space.
		Vector3 m_v3MinMS;
		float m_fLenSquareMin;

		//center position in model space.
		Vector3 m_v3CenterMS;


		//temp
		Vector3 m_v3MaxWS;
		Vector3 m_v3MinWS;
		

		//center position in world space.
		Vector3 m_v3Center;

		//all corners in world space.
		Vector4 m_box[CONCOUNT];

		//Local coordination system base (To be descripted by the vectors in world space).
		CAFrame m_rCCBase;

		Vector4 m_v4TmpPoint;
	};


}



#endif // !_FW_AABB_
