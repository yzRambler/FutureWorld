/*

CTextField

Author: Zhen Yi (взеђ)

Created Date: Mar. 28, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_TEXTFIELD_
#define _FW_TEXTFIELD_

#include<vector>
#include"CChar.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class CTextLine;
	class CMaterial;
	class Matrix4x4;
	class CEssety;
	class DLLCOAPI CTextField
	{
	private:
		typedef std::vector<CTextLine*> VTTXL;
		typedef VTTXL::iterator  VTTXL_ITER;

		typedef std::vector<CLiteralUnit*> VTLTU;
		typedef VTLTU::iterator  VTLTU_ITER;

		typedef std::vector<CChar*> VTCHA;
		typedef VTCHA::iterator VTCHA_ITER;

	public:
		CTextField();
		virtual ~CTextField();


		bool Create(float x, float y, float fdist, float w, float h, 
			const char* pszString, float fStep);



	//attribute
	public:
		void setOffX(float offX) { m_fOffX = offX; }
		void setOffY(float offY) { m_fOffY = offY; }
		

		int countLine() { return m_vtTextLine.size(); }
		CTextLine* line(int index)
		{
			if ((index < 0) || (index >= m_vtTextLine.size())) { return nullptr; }
			return m_vtTextLine[index];
		}


		int countChar() { return m_vtChar.size(); }
		CChar* getChar(int index) 
		{
			if ((index < 0) || (index >= m_vtChar.size())) { return nullptr; }
			return m_vtChar[index];
		}

	private:
		bool Parse(const char* pszText);
		void Destroy();


	private:
		VTTXL m_vtTextLine;
		VTLTU m_vtLtUnit;
		VTCHA m_vtChar;

		float m_fOffX;   //the off x relation with host left-top vertex
		float m_fOffY;    //the off y relation with host left-top vertex
		float m_fX;
		float m_fY;
		float m_fWidth;
		float m_fHeight;
		float m_fIntervalLine;
	};



}




#endif // !_FW_TEXTFIELD_
