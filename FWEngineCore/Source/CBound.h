/*
CBound:   for collision detection


Author: Zhen Yi  ---  взеђ


Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha


*/


#ifndef _FW_BOUND_
#define _FW_BOUND_

#include"CConstruct.h"
#include"CAABB.h"
#include"MathLibrary.h"
#include"FWEngineCoreExport.h"


namespace FW
{
	class Vector3;
	class DLLCOAPI CBound : public CConstruct
	{
	public:
		CBound(CConstruct* pHost);
		CBound(const char* pszName, CConstruct* pHost);
		virtual ~CBound();

		//bool Create(Vector3& v3Max, Vector3& v3Min);
		//void Update(Vector3& v3Max, Vector3& v3Min);

		/*
		  Note: In default, axis Y is (0,1,0) and X is (1,0,0), so it's unnecessary to transfer them
		  with parameters.

		  v3MaxMS: The max point position in model space.
		  v3MinMS: The min point position in model space.
		  pos: center point position in world space.
		*/
		bool Create(Vector3& v3MaxMS, Vector3& v3MinMS, Vector3& pos);


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
		bool Create(Vector3& v3MaxMS, Vector3& v3MinMS,
			Vector3& v3UpWS, Vector3& v3ForwardWS, Vector3* pCentWS = nullptr);


		bool CreateWS(Vector3& v3MaxWS, Vector3& v3MinWS,
			Vector3& v3UpWS, Vector3& v3ForwardWS, Vector3* pCentWS = nullptr);


		/*
		  v3MaxMS: It must be the max point position in model space;
		  v3MinMS: It must be the min point position in model space;
		  v3UpWS:  It must be the vertical projection vertor (to get horizontal project plane)
				   in world space.

		  v3ForwardWS:
				   It must be the horizontal projection vertor (to get identical rectangle field on
				   the project plane) in world space.

		  pCentWS: The center pointer position in world space. 

		*/
		void Update(Vector3& v3MaxMS, Vector3& v3MinMS,
			Vector3& v3UpWS, Vector3& v3ForwardWS, Vector3* pCentWS);

		void UpdateWS(Vector3& v3MaxWS, Vector3& v3MinWS);


		//bool Hiting(Vector3& v3Pos)
		bool Inside(Vector3& v3Pos)
		{
			if (nullptr == m_pAABB) { return false; }
			return m_pAABB->inside(v3Pos);
		}


		//bool Hiting(float x, float y, float z)
		bool Inside(float x, float y, float z)
		{
			if (nullptr == m_pAABB) { return false; }
			return m_pAABB->inside(x, y, z);
		}


		//temporary code.  
		//optimize create a CRectBound specified to rectangle collision detection ??
		bool InsideRect(Vector3& v3Pos)
		{
			if (nullptr == m_pAABB) { return false; }
			return m_pAABB->insideRect(v3Pos);

		}

		//bool HitingRect(float x, float y)
		bool InsideRect(float x, float y)
		{
			if (nullptr == m_pAABB) { return false; }
			return m_pAABB->insideRect(x, y);
		}

		bool InsideRectWS(float x, float y, float z)
		{
			if (nullptr == m_pAABB) { return false; }
			return m_pAABB->insideRectWS(x, y, z);
		}


	//attribute
	public:
		Vector3& center() { return m_pAABB->center(); }



	private:
		CAABB* m_pAABB;
		
	};
}





#endif // !_FW_BOUND_
