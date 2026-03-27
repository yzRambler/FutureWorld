/*
    COBJFile

Author: Zhen Yi
Created Date: Mar. 3, 2021

Version: 0.2.0 Alpha

*/


#ifndef _FW_OBJFILE_
#define _FW_OBJFILE_

#include<vector>
#include<string>
#include"TemplateLibrary.h"
#include"CTextFile.h"
#include"Common.h"

namespace FW
{

	class COBJFile : public CTextFile
	{
	private:
		enum EPSTATE {
			GN_OBJ_CHUNK, GN_VPOS_SUBCHUNK, GN_NOR_SUBCHUNK, GN_UV_SUBCHUNK,
			GN_SURF_SUBCHUNK, EN_OBJ_CHUNK, UNKNOW
		};

		typedef std::vector<OBJECT*> VTOBJ;
		typedef VTOBJ::iterator VTOBJ_ITER;

		typedef std::vector<std::string> VTSRG;
		typedef VTSRG::iterator VTSRG_ITER;

		typedef TIter<VTOBJ> OBJ_ITER;

	public:
		COBJFile(const char* pszName);
		COBJFile(const char* pszName, const char* pszFileName);
		virtual ~COBJFile();

		//derive from CTextFile
		virtual bool Parse();

		OBJECT* GetOBJECT(const char* pszOBJName)
		{
			for (VTOBJ_ITER iter = m_vtOBJ.begin(); iter != m_vtOBJ.end(); ++iter)
			{
				OBJECT* pOBJ = (OBJECT*)(*iter);
				if (strcmp(pszOBJName, pOBJ->name.c_str()) == 0)
				{
					return pOBJ;
				}
			}

			return 0;
		}


		void InitalizeWorkIter();

		//attribute
	public:
		OBJ_ITER& iterWork() { return *m_pIterOBJWork; }


	private:
		//Derive from CTextFile
		//Note: In the object file, if the comment line include the keys:
		//      "object", "vertices","vertex normals","texture coords","polygons". 
		//      it will be not regarded as comment to skip and be remained.
		//The line is regarded as comment line, must have two conditions:
		//1. The character '#' is the [0] element or all the characters all are blank ' ' before the '#'.
		//2. This line don't include "object" string.
		virtual bool isSkippedLine(std::string& str);

		//bool CreateObjectChunk(size_t loc);
		//the seconde paramter rtIter receive return value.
		bool CreateObjectChunk(size_t loc, VSITER iter, VSITER& rtIter);
		bool ReadVerticePosChunk(std::string& str, OBJECT* pObj);
		bool ReadVerticeNormalChunk(std::string& str, OBJECT* pObj);
		bool ReadVerticeUVChunk(std::string& str, OBJECT* pObj);
		bool ReadSurfaceIndexChunk(std::string& str, OBJECT* pObj);

		void ParseFailed();
		bool LineParse(std::string& str);
		void CleanVTOBJ();

		//The string contain carriage return-line feed translation.
		bool isContainCRFT(std::string& str) { return (str[str.size() - 2] == '\r' && str[str.size() - 1] == '\n'); }

	private:
		VTOBJ m_vtOBJ;
		VTSRG m_vtLineParseResult;
		OBJ_ITER* m_pIterOBJWork;

		int m_nOffsetVertex;
		int m_nOffsetNormal;
		int m_nOffsetUV;

		//For checking the chuck (start or end) from the '#' line in the obj file. 
		static const int KEYCOUNT = 7;
		const char* m_szKeyTable[KEYCOUNT];

		static const int SKIPSIGNCOUNT = 3;
		char m_cSkipSignTable[SKIPSIGNCOUNT];

		EPSTATE m_eParseState;
	};

}

#endif