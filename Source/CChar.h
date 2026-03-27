/*

CChar

Author: Zhen Yi  (взеђ)


Created Date: Mar. 28, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_CHAR_
#define _FW_CHAR_

#include"CLiteralUnit.h"
#include"FWEngineCoreExport.h"
#include"MathLibrary.h"


namespace FW
{
	class DLLCOAPI CChar : public CLiteralUnit
	{
	private:
		typedef enum {CAC=4};

	public:
		CChar(char c);
		virtual~CChar();

		bool Start();
		void Update(char c);

	//Inherit from CLiteralUnit
	public:
		virtual bool Create(float fx, float fy, float fdist, float fStep, bool show = true);



	//attribute
	public:
		char value() { return m_char; }
		float u() { return m_fU; }
		float v() { return m_fV; }
		float du() { return m_fDu; }
		float dv() { return m_fDv; }
		Vector3& local(){ return m_aryVt[0]->v3; }
		Vector3& horizon() { return m_v3Horizon; }
		Vector3& vertical() { return m_v3Vertical; }


		//Inherit from CLiteralUnit
		virtual float width() { return m_fWidth; }
		virtual float height() { return m_fHight; }


	private:
		void Destroy();


	private:
		char m_char;
		float m_fOffV;
		float m_fWidth;  //The width of character in FontLibrary.png
		float m_fHight;  //The hight of character in FontLibrary.png

		float m_fU;   //The u value of a square corner in FontLibrary.png
		float m_fV;   //The v value of a square corner in FontLibrary.png
		float m_fDu;
		float m_fDv;


		Vector4* m_aryVt[CAC];   // Four position of the square corners.
		Vector3 m_v3Horizon;
		Vector3 m_v3Vertical;
	};

}





#endif // !_FW_CHAR_
