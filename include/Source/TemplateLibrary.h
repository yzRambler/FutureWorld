/*

 Template Iterator

  Author: Zhen Yi
  Created Date: April 9, 2021

  Version: 0.2.0 Alpha

*/


#ifndef _FW_TEMPLATE_LIBRARY_
#define _FW_TEMPLATE_LIBRARY_

namespace FW
{

	template<typename T>
	class TSingleton
	{
		typedef T* T_POINTER;

	public:
		TSingleton() {}
		virtual ~TSingleton() {}

		static T& Instance()
		{
			if (m_pInstance == 0)
			{
				m_pInstance = new T;
			}

			return *m_pInstance;
		}

	private:
		static T_POINTER m_pInstance;
	};

	/*
	  Note. 
	    The m_pInstance member would be initalized in the local of creating TSingleton 
		object, but not here.
	    template<typename T>
	    static TSingleton<T>::T_POINTER  TSingleton<T>::m_pInstance = 0;
	*/



	template<typename T>
	class TVTAmount
	{
		typedef T* T_POINTER;

	public:
		T_POINTER   pmain;
		float  vice;

		//T     main;   //main: AMatrix / DualQuaternion / index / Vector
		//float vice;   //vice: weight as main: AMatrix/DualQuaternion/index 
					  //vice: index as main: vector
	};



	/*
	*   The type T must be container type.
		The pointer olny is permitted to put into this collection container.
	*
	*/

	//Template Iterator
	template<typename T>
	class TIter
	{
	public:
		typedef T DATA_TYPE;
		typedef typename T::iterator DATA_TYPE_ITER;

	public:
		TIter() {}
		virtual ~TIter() {}

		void Init(DATA_TYPE_ITER begin, DATA_TYPE_ITER end) { m_iterBegin = begin; m_iterWork = begin; m_iterEnd = end; }

		void SetBegin() { m_iterWork = m_iterBegin; }
		void* getCurrent()
		{
			if (m_iterWork != m_iterEnd)
			{
				return *m_iterWork;
			}

			return 0;
		}

		//Just for T is map.    Temporary code.
		void* getCurrentPairFirst()
		{
			if (m_iterWork != m_iterEnd)
			{
				return (*m_iterWork).first;
			}

			return 0;
		}

		//Just for T is map.   Temporary code.
		void* getCurrentPairSecond()
		{
			if (m_iterWork != m_iterEnd)
			{
				return (*m_iterWork).second;
			}

			return 0;
		}



		void MoveToNext() { if (!IsEnd()) { m_iterWork++; } }
		bool IsEnd() { return m_iterWork == m_iterEnd; }

		//public:
	private:
		DATA_TYPE_ITER m_iterBegin;
		DATA_TYPE_ITER m_iterEnd;
		DATA_TYPE_ITER m_iterWork;

	};
};


#endif