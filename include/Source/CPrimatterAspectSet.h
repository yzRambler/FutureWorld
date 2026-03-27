/*

CPrimatterAspectSet



Author:  Zhen Yi

Created Date: April 23, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_PRIMATTERASPECT_SET_
#define _FW_PRIMATTERASPECT_SET_

#include<map>
#include"CData.h"



namespace FW
{

	class CPrimatterAspectSet
	{
		typedef struct SDataSign
		{
			CData* pPmt;    //Data pointer
			int count;       //the count of Data reference
		}SDataSign;

		typedef std::map<FDWORD, SDataSign*> MAPIDAS;
		typedef MAPIDAS::iterator MAPIDAS_ITER;

	public:
		CPrimatterAspectSet();
		virtual ~CPrimatterAspectSet();

		void Create();

		void AddData(FDWORD id, CData* pPmt);
		CData* GetUnpossess(FDWORD id);

		FDWORD Check(const char* pszFileName, const char* pszName);


		//Just for calling of a creating function outside.
		//CData* RequireData(FDWORD id);
		CData* AcquireReference(FDWORD id);

		/*
		  Just for outside calling. It match with AcquireReference.
		  When the Data counter decrease into zero, don't delete matching Data
		immediately.

		  If the return value equal 0 means the count of the reference of the Data
		is zero.
		  If the return value is -1, means the parameter id is invalid.
		*/
		int ReleaseReference(FWORD id);

		//for calling in create function
		FDWORD  RequireData(char* pszFileName, char* pszName);


	private:
		MAPIDAS m_mapIDASS;
	};

}




#endif // !_FW_PRIMATTERASPECT_SET_
