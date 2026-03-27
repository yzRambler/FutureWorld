/*

CICTaget:   InterchangeTarget

Author:  Zhen Yi

Created Date:  Jul. 16, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_ICTARGET_
#define _FW_ICTARGET_

#include<map>
#include"BaseData.h"
#include"CBase.h"
#include"CommonPrimatter.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class CListener;
	class DLLCOAPI CICTarget : public CBase
	{
	protected:
		typedef std::map<FDWORD, CListener*> MAPLST;
		typedef MAPLST::iterator  MAPLST_ITER;


	public:
		CICTarget(EICTAGTYPE ictag = EICTAGTYPE::ICT_UNKNOW) : m_eTargetType(ictag){}
		CICTarget(const char* pszName, EICTAGTYPE ictag = EICTAGTYPE::ICT_UNKNOW) : CBase(pszName),
		m_eTargetType(ictag){}

		virtual ~CICTarget() {}


		virtual bool RegisterLst(CListener* pLsn);
		virtual void UnregisterLst(CListener* pLsn);
		virtual void Update() {}

	//attribute
	public:
		EICTAGTYPE typeTag() { return m_eTargetType; }


	private:
		CListener* FindListener(FDWORD id);


	//private:
	protected:
		MAPLST m_mapListener;
		EICTAGTYPE  m_eTargetType;
	};


}





#endif // !_FW_ICTARGET_
