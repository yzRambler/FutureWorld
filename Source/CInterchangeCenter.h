/*

CInterchangeCenter



Author:   Zhen Yi

Created Data: Jun. 14, 2025

Version: 0.2.0 Alpha


*/


#ifndef _FW_INTERCHANGE_CENTER_
#define _FW_INTERCHANGER_CENTER_

#include<map>
#include"BaseData.h"
#include"FWEngineShareExport.h"
#include"CICTarget.h"
#include"CommonPrimatter.h"

namespace FW
{
	class CConstruct;
	class DLLSHAPI CInterchangeCenter
	{
		typedef std::map<EICTAGTYPE, CICTarget*> MAPTAG;
		typedef MAPTAG::iterator MAPTAG_ITER;

		typedef std::map<FDWORD, CConstruct*> MAPCST;
		typedef MAPCST::iterator MAPCST_ITER;

	public:
		CInterchangeCenter();
		virtual ~CInterchangeCenter();

		static CInterchangeCenter* Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CInterchangeCenter;
			}

			return m_pInst;
		}


		static void Release()
		{
			if (nullptr != m_pInst)
			{
				delete m_pInst;
				m_pInst = nullptr;
			}
		}

		void AddTarget(CICTarget* pTag);
		void RemoveTarget(EICTAGTYPE type);

		void AddApplication(CConstruct* pCst);
		void RemoveApplication(CConstruct* pCst);

		void Update();



	private:
		static CInterchangeCenter* m_pInst;



	private:
		MAPTAG m_mapTarget;
		MAPCST m_mapConstruct;
	};


}


















#endif // !_FW_INTERCHANGE_
