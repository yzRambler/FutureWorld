/*

CFontLibrary:  Be created with ASCII table && FontLibrary.png
       


Author: Zhen Yi (взеђ)

Created Date: Mar. 28, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_FONTLIBRARY_
#define _FW_FONTLIBRARY_

#include<vector>


namespace FW
{
	class CFontLibrary
	{
	public:
		typedef struct {
			float u;
			float v;
			float w;
			float h;
			float offV;
		}SCHR;

	private:
		typedef enum { SUM_ROWS = 4 }; // the total of rows in FontLibrary.png

		typedef std::vector<SCHR*> VTCHR;
		typedef VTCHR::iterator VTCHR_ITER;

	public:
		CFontLibrary();
		virtual ~CFontLibrary();

		static CFontLibrary& Instance()
		{
			if (0 == m_pInst)
			{
				m_pInst = new CFontLibrary;
				m_pInst->Initialize();
			}

			return *m_pInst;
		}

		void Initialize();
		SCHR* InquireChar(char c) { if ((c < '!') || (c > '~')) { return 0; } return m_vtASCIITable[c-'!']; }


	//attribute
	public:
		float width() { return m_fWidthPic; }
		float height() { return m_fHightPic; }

	private:
		void Destroy();


	private:
		static CFontLibrary* m_pInst;
		VTCHR m_vtASCIITable;
		float m_fWidthPic;    //the width of FontLibrary.png
		float m_fHightPic;    //the height of FontLibrary.png
	};



}





#endif // !_FW_FONTLIBRARY_
