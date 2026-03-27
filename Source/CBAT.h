/*

class CBAT


Author: Zhen Yi

Created Date: June 26, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_BONEANIMATION_TRACK_
#define _FW_BONEANIMATION_TRACK_

#include"CTrack.h"


namespace FW
{

	//for animation
	class CBAT
	{
	public:
		CBAT() :m_pTrack(nullptr)
		{
			m_matAniBaseLocal.Zero();
		}

		virtual ~CBAT()
		{

			if (0 != m_pTrack)
			{
				delete m_pTrack;
				m_pTrack = 0;
			}
		}


		CTrack* track() { if (0 == m_pTrack) { m_pTrack = new CTrack; }  return m_pTrack; }

		bool nullTrack() { return 0 == m_pTrack; }

		char* nameBone() { return (char*)m_strNameBone.Get(); }


		void setNameBone(const char* pszNameBone) { m_strNameBone.Set(pszNameBone); }


		void setAniBaseLocalMatrix(Matrix4x4& mat) { m_matAniBaseLocal = mat; }
		Matrix4x4& matAniBaseLocal() { return m_matAniBaseLocal; }

	private:
		CString m_strNameBone;
		CTrack* m_pTrack;
		Matrix4x4 m_matAniBaseLocal;
	};

}



#endif // !_FW_BONEANIMATION_TRACK_
