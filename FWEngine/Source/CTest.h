/*

CTest


Author:  Zhen Yi

Date: Aug. 26, 2025

*/


#ifndef _FW_TEST_
#define _FW_TEST_

#include"FWEngineExport.h"


namespace FW
{
	class DLLEGAPI CTest
	{
	public:
		CTest();
		virtual ~CTest();

		static CTest* Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CTest;
			}

			return m_pInst;
		}

		bool Create();

	private:
		static CTest* m_pInst;
	};
}




#endif // !_FW_TEST_
