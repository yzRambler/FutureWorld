/*

CTextLine

Author:  Zhen Yi (взеђ)

Created Date: Mar. 28, 2024

Version: 0.2.0 Alpha

*/

#ifndef _FW_LINE_
#define _FW_LINE_

#include<vector>
#include"CWord.h"


namespace FW
{
	class CMaterial;
	class Matrix4x4;
	class DLLCOAPI CTextLine
	{
	private:
		typedef std::vector<CLiteralUnit*> VTLTU;
		typedef VTLTU::iterator VTLTU_ITER;

	public:
		CTextLine();
		virtual ~CTextLine();

		void AddLiterUnit(CLiteralUnit* pLtUnit)
		{
			if (0 == pLtUnit){ return; }
			m_heightLine = m_heightLine < pLtUnit->height() ? pLtUnit->height() : m_heightLine;
			m_widthLine += m_widthLine < 0.0f ? pLtUnit->width() : (m_intervalWord + 
				pLtUnit->width());

			m_vtLitUnit.push_back(pLtUnit);
		}

		bool Create(float fx, float fy, float fdist, float fStep);



	//attribute
	public:
		float width() { return m_widthLine; }
		float height() { return m_heightLine; }

		int countWord() { return m_vtLitUnit.size(); }
		CWord* word(int index)
		{
			if ((index < 0) || (index >= m_vtLitUnit.size())) { return nullptr; }
			return (CWord*)m_vtLitUnit[index];
		}


	private:
		void Destroy();

	private:
		//Actually, all of CLiteralUnit objects in here are CWord objects.
		//include the word which own single char.
		VTLTU m_vtLitUnit;

		float m_widthLine;
		float m_heightLine;
		float m_intervalWord;
	};

}




#endif // ! _FW_CLINE_
