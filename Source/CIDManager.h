
/*

CIDManager


Author:  Zhen Yi

Version: 0.2.0 Alpha

*/




#ifndef  _FW_IDMANAGER_
#define _FW_IDMANAGER_

#include<vector>

#include"Common.h"
//#include"CommonShare.h"
#include"FWEngineShareExport.h"

#define MAX_INDEX  65535
#define MAX_SIZE  65536
#define HIGH_WORD  0xffff0000
#define LOW_WORD   0x0000ffff

namespace FW
{
	class DLLSHAPI CIDManager
	{
		typedef std::vector<UID*> VTID;
		typedef VTID::iterator VTITER;
			 
	public:
		CIDManager();
		virtual ~CIDManager();

		static CIDManager& Instance()
		{
			if (nullptr == m_pInst)
			{
				m_pInst = new CIDManager;
				m_pInst->Create();
			}

			return *m_pInst;
		}

		static void Release()
		{
			if (nullptr != m_pInst)
			{
				m_pInst->Destroy();
				delete m_pInst;

				m_pInst = nullptr;
			}
		}


		FDWORD ApplyID(); 
		void RemoveID(FDWORD id);


		//The function is used to check if the id is valid or not.
		//Note: The 0 index of m_vtUse will not be used.
		bool Inquire(FDWORD id)
		{
			return ((id & LOW_WORD) == 0) ? false :
				((id & LOW_WORD) > MAX_INDEX ? false : 
					m_vtUse[id & LOW_WORD] == nullptr ? false : m_vtUse[id & LOW_WORD]->v == id);

			//return ((id & LOW_WORD) == 0) ? false :
			//	((id & LOW_WORD) > MAX_INDEX ? false : m_vtUse[id & LOW_WORD]->v == id);
		}

		


	private:
		void Create();
		void Destroy();


	//attribute
	private:
		bool isRestVtEmpty() 
		{ return (m_indRestStart == m_indRestEnd) && (m_vtRest[m_indRestStart] == nullptr); }


		bool isRestVtFull()
		{ return  m_indRestEnd > m_indRestStart ? ( m_indRestEnd - m_indRestStart == MAX_INDEX)
			: m_indRestEnd + 1 == m_indRestStart ;}

	private:
		static CIDManager* m_pInst;

		//The index match the low 16 bits of UID.v.  (i.e. UID.u)
		//Max index : 65535  and  m_vtUse[0] don't be used (the first index just begin from m_vtUse[1]).  
		VTID m_vtUse;

		//The index match the high 16 bits of UID.v. (i.e.  UID.r)
		VTID m_vtRest;
		int m_indRestStart;  //for m_vtRest.
		int m_indRestEnd;    //for m_vtRest.

	};

};


#endif // ! _FW_IDMANAGER_

