/*


CRectBound


Author:   Zhen Yi

 Created Data: Oct. 13, 2025

 Version: 0.2.0 Alpha

*/



#ifndef _FW_RECTBOUND_
#define _FW_RECTBOUND_

#include"CConstruct.h"
#include"CRect.h"


namespace FW
{
	class DLLCOAPI CRectBound : public CConstruct
	{
	public:
		CRectBound(CConstruct* pHost):CConstruct(pHost), m_pRect(nullptr) {}
		CRectBound(const char* pszName, CConstruct* pHost) :CConstruct(pszName, pHost), m_pRect(nullptr) {}
		virtual ~CRectBound() {}

		bool Hiting(Vector3& v3Pos)
		{
			if (m_pRect != nullptr) { return m_pRect->beInside(v3Pos); }
			return false;
		}

	private:
		CRect* m_pRect;
	};
}






#endif // !_FW_RECTBOUND_

