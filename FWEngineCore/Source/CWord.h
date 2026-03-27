/*
CWord

Author: Zhen Yi  (взеђ)

Created Date: Mar. 28, 2024

Version: 0.2.0 Alpha


*/

#ifndef _FW_WORD_
#define _FW_WORD_

#include<vector>
#include"CChar.h"



namespace FW
{
	class DLLCOAPI CWord : public CLiteralUnit
	{
	private:
		typedef std::vector<CChar*> VTCHR;
		typedef VTCHR::iterator VTCHR_ITER;


		//Inherit from CLiteralUnit
	public:
		virtual bool Create(float fx, float fy,  float fdist, float fStep);


	public:
		CWord();
		virtual ~CWord();

		//param: len  exclude the terminate symbol in the string '\0'.
		//Will be called before Create() function.
		bool Start(char* pString, int len);



	//attribute
	public:
		//Inherit from CLiteralUnit
		virtual float width() { return m_fWidthWord; }
		virtual float height() { return m_fHightWord; }

		int countChar() { return m_vtChar.size(); }
		CChar* getChar(int index) 
		{
			if ((index < 0) || (index >= m_vtChar.size())) { return nullptr; }
			return m_vtChar[index];
		}

	private:
		void Destroy();


	private:
		VTCHR m_vtChar;
		float m_fInterval;   //the interval between two characteres.

		float m_fHightWord;
		float m_fWidthWord;
	};

}




#endif // !_FW_WORD_
