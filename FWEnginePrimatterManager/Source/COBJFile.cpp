#include"COBJFile.h"
#include<string>
#include<math.h>

#ifdef _WND_OPENGL_PLATFORM_

//#include "CWindowsFile.h"

#else

//#include "CWebFile.h"
#include<emscripten.h>

#define _DEBUG_STATE_CHANGE_

#endif // _WND_OPENGL_PLANTFORM_


using namespace FW;
using namespace std;


COBJFile::COBJFile(const char* pszName) :CTextFile(pszName), m_nOffsetVertex(0),
m_nOffsetNormal(0), m_nOffsetUV(0), m_pIterOBJWork(0)
{
	m_szKeyTable[0] = "object";
	m_szKeyTable[1] = "vertices";
	m_szKeyTable[2] = "vertex normals";
	m_szKeyTable[3] = "texture coords";
	m_szKeyTable[4] = "polygons";
	m_szKeyTable[5] = "triangles";
	m_szKeyTable[6] = "faces";

	m_cSkipSignTable[0] = 'o';
	m_cSkipSignTable[1] = 'g';
	m_cSkipSignTable[2] = 's';

	setType(EFILETYPE::FI_OBJ);

}

COBJFile::COBJFile(const char* pszName, const char* pszFileName) :CTextFile(pszName, pszFileName), m_nOffsetVertex(0),
m_nOffsetNormal(0), m_nOffsetUV(0), m_pIterOBJWork(0)
{
	m_szKeyTable[0] = "object";
	m_szKeyTable[1] = "vertices";
	m_szKeyTable[2] = "vertex normals";
	m_szKeyTable[3] = "texture coords";
	m_szKeyTable[4] = "polygons";
	m_szKeyTable[5] = "triangles";
	m_szKeyTable[6] = "faces";

	m_cSkipSignTable[0] = 'o';
	m_cSkipSignTable[1] = 'g';
	m_cSkipSignTable[2] = 's';

	setType(EFILETYPE::FI_OBJ);

}


COBJFile::~COBJFile()
{
}


bool COBJFile::isSkippedLine(string& str)
{
	size_t local = str.find_first_of('#');
	if (local == str.npos)
	{
		for (int i = 0; i < SKIPSIGNCOUNT; i++)
		{
			if (m_cSkipSignTable[i] == str[0])
			{
				return true;
			}
		}

		return false;
	}

	bool bFound = false;
	for (int i = 0; i < KEYCOUNT; i++)
	{
		bFound = bFound || (str.find(m_szKeyTable[i]) != str.npos);
	}

	return ((local > str.find_first_not_of(' ')) ? false : (!bFound));
}

void COBJFile::InitalizeWorkIter()
{
	if (0 == m_pIterOBJWork)
	{
		m_pIterOBJWork = new OBJ_ITER;
	}

	m_pIterOBJWork->Init(m_vtOBJ.begin(), m_vtOBJ.end());
}


bool COBJFile::Parse()
{
	if (!CTextFile::Parse())
	{
		return false;
	}

	if (m_vtContent.empty())
	{
		return false;
	}

#ifdef _DEBUG_STATE_CHANGE_
	EM_ASM({
			console.log(" COBJFile::Parse, m_vtContent.size() == " + $0);;
		}, m_vtContent.size());

#endif

	string strTmp;
	//VSITER rtIter;
	VSITER iterWork = m_vtContent.begin();
	while (iterWork != m_vtContent.end())
	{
		strTmp = (char*)(*iterWork);
		size_t loc = strTmp.find("object");

		//#ifdef _DEBUG_STATE_CHANGE_
		//        char* ptmp = new char[strTmp.length()+1];
		//		memcpy(ptmp, strTmp.c_str(), strTmp.length());
		//		ptmp[strTmp.length()] = '\0';
		//
		//EM_ASM({
		//			console.log(UTF8ToString($0));
		//		}, ptmp);
		// 
		//#endif

		if (loc != strTmp.npos)
		{
			m_eParseState = EPSTATE::GN_OBJ_CHUNK;

			//the second paramter iterWork receive return value.
			if (!CreateObjectChunk(loc, iterWork, iterWork))
			{
				return false;
			}
		}

		iterWork++;
	}

#ifdef _DEBUG_STATE_CHANGE_
	EM_ASM({ console.log("COBJFile::Parse parse successful! The name is " + UTF8ToString($0)); }, (char*)this->nameFile());
#endif	


	m_eFileState = CFile::EFSTATE::PARSE_SUC;

	return true;
}



bool COBJFile::CreateObjectChunk(size_t loc, VSITER iter, VSITER& rtIter)
{
	string strTmp = *iter;//*m_iterWork;
	OBJECT* pObj = new OBJECT;

	pObj->offsetVertex = m_nOffsetVertex;
	pObj->offsetNormal = m_nOffsetNormal;
	pObj->offsetUV = m_nOffsetUV;

	size_t nloc = strTmp.find_first_not_of(' ', strTmp.find_first_of(' ', loc));
	if (nloc == strTmp.npos)
	{
		pObj->name = "";
	}
	else
	{
		string strSub = strTmp.substr(nloc);
		pObj->name = strSub.substr(0, strSub.size() - 2);
	}


	//m_iterWork++;
	iter++;
	while (iter != m_vtContent.end())
	{
		strTmp = (*iter);
		switch (m_eParseState)
		{
		case EPSTATE::GN_OBJ_CHUNK:
		{
			//if (strTmp.find_first_of("v") <= 0)
			if ((strTmp[0] == 'v') && (strTmp[1] == ' '))
			{
				m_eParseState = EPSTATE::GN_VPOS_SUBCHUNK;
				--iter;
			}
			else
			{
				ParseFailed();
			}
			break;
		}


		case EPSTATE::GN_VPOS_SUBCHUNK:
		{
			if ((strTmp[0] == 'v') && (strTmp[1] == ' '))
			{
				if (!ReadVerticePosChunk(strTmp, pObj))
				{
					ParseFailed();
				}
			}
			else if (strTmp.find("vertices") != strTmp.npos) //verify the result parsed of vertics.  
			{
				LineParse(strTmp);
				if ((m_vtLineParseResult.size() == 3) && (m_vtLineParseResult[0].compare("#") == 0))
				{
					if (atoi(m_vtLineParseResult[1].c_str()) != pObj->vertices.size())
					{
						ParseFailed();
					}
				}
			}
			else if ((strTmp[0] == 'v') && (strTmp[1] == 'n'))
			{
				m_eParseState = EPSTATE::GN_NOR_SUBCHUNK;
				--iter;
			}
			else if ((strTmp[0] == 'v') && (strTmp[1] == 't'))
			{
				m_eParseState = EPSTATE::GN_UV_SUBCHUNK;
				--iter;
			}
			else if (strTmp.find_first_of("f") <= 0)
			{
				m_eParseState = EPSTATE::GN_SURF_SUBCHUNK;
				--iter;
			}
			else if (strTmp.find("object") != strTmp.npos)
			{
				--iter;
				m_eParseState = EPSTATE::EN_OBJ_CHUNK;
			}
			else
			{
				ParseFailed();
			}
			break;
		}


		case EPSTATE::GN_NOR_SUBCHUNK:
			if ((strTmp[0] == 'v') && (strTmp[1] == 'n'))
			{
				if (!ReadVerticeNormalChunk(strTmp, pObj))
				{
					ParseFailed();
				}
			}
			else if (strTmp.find("vertex normals") != strTmp.npos) //verify the normal parsed of vertices
			{
				LineParse(strTmp);
				if ((m_vtLineParseResult.size() >= 3) && (m_vtLineParseResult[0].compare("#") == 0))
				{
					if (atoi(m_vtLineParseResult[1].c_str()) != pObj->normals.size())
					{
						ParseFailed();
					}
				}
			}
			else if ((strTmp[0] == 'v') && (strTmp[1] == 't'))
			{
				m_eParseState = EPSTATE::GN_UV_SUBCHUNK;
				--iter;
			}
			else if (strTmp.find_first_of("f") <= 0)
			{
				m_eParseState = EPSTATE::GN_SURF_SUBCHUNK;
				--iter;
			}
			else if (strTmp.find("object") != strTmp.npos)
			{
				--iter;
				m_eParseState = EPSTATE::EN_OBJ_CHUNK;
			}
			else
			{
				ParseFailed();
			}

			break;

		case EPSTATE::GN_UV_SUBCHUNK:
			if ((strTmp[0] == 'v') && (strTmp[1] == 't'))
			{
				if (!ReadVerticeUVChunk(strTmp, pObj))
				{
					ParseFailed();
				}
			}
			else if (strTmp.find("texture coords") != strTmp.npos) //check the uv parsed of vertices
			{
				LineParse(strTmp);
				if ((m_vtLineParseResult.size() >= 3) && (m_vtLineParseResult[0].compare("#") == 0))
				{
					if (atoi(m_vtLineParseResult[1].c_str()) != pObj->uvs.size())
					{
						ParseFailed();
					}
				}
			}
			else if (strTmp.find_first_of("f") <= 0)
			{
				m_eParseState = EPSTATE::GN_SURF_SUBCHUNK;
				--iter;
			}
			else if (strTmp.find("object") != strTmp.npos)
			{
				--iter;
				m_eParseState = EPSTATE::EN_OBJ_CHUNK;
			}
			else
			{
				ParseFailed();
			}
			break;

		case EPSTATE::GN_SURF_SUBCHUNK:

			if (strTmp.find_first_of("f") <= 0)
			{
				if (!ReadSurfaceIndexChunk(strTmp, pObj))
				{
					ParseFailed();
				}

			}
			else if (strTmp.find("faces") != strTmp.npos) //check the surface index parsed of vertices
			{
				LineParse(strTmp);
				if ((m_vtLineParseResult.size() == 3) && (m_vtLineParseResult[0].compare("#") == 0))
				{
					if (atoi(m_vtLineParseResult[1].c_str()) * 3 != pObj->surfaces.size())
					{
						ParseFailed();
					}
				}
			}
			else if (strTmp.find("object") != strTmp.npos)
			{
				--iter;
				m_eParseState = EPSTATE::EN_OBJ_CHUNK;
			}
			else
			{
				ParseFailed();
			}
			break;

		case EPSTATE::EN_OBJ_CHUNK:
		{
			//confirm obj chunk create over.
			if (strTmp.find("object") != strTmp.npos)
			{
				--iter;
				m_vtOBJ.push_back(pObj);

				rtIter = iter;
				return true;
			}
			else
			{
				ParseFailed();
			}

		}
		break;

		case EPSTATE::UNKNOW:
		default:
		{
#ifdef _DEBUG_STATE_CHANGE_
			//EM_ASM({
			//		console.log(" EPSTATE::UNKNOW. in COBJFile::CreateObjectChunk. successful.");;
			//	});

#endif
			delete pObj;
			return false;
		}
		break;


		}

		iter++;
	}

	//accomplish to generate the last sub chunk of the last object chunk in m_vtContent
	--iter;
	m_vtOBJ.push_back(pObj);


#ifdef _DEBUG_STATE_CHANGE_
	//	EM_ASM({
	//				console.log(" m_vtOBJ.push_back(pObj) in COBJFile::CreateObjectChunk.");;
	//		});

#endif

	rtIter = iter;
	return true;
}

void COBJFile::ParseFailed()
{
	//m_iterWork--;
	m_eParseState = EPSTATE::UNKNOW;
}


bool COBJFile::LineParse(string& str)
{
	size_t locSt = 0;
	size_t locEd = 0;

	m_vtLineParseResult.clear();
	while (true)
	{
		locSt = str.find_first_not_of(' ', locEd);
		locEd = str.find_first_of(' ', locSt);

		//Invalid
		if ((locSt == str.npos) || (locSt >= locEd))
		{
			return false;
		}

		//Check whether the substring is the last one.
		if (locEd == str.npos)
		{
			string strSub = str.substr(locSt);
			if (!isContainCRFT(strSub))  //error line
			{
				return false;
			}
			else //the last substring.
			{
				str.erase(str.size() - 2, 2);
				m_vtLineParseResult.push_back(str.substr(locSt, locEd - locSt));

				return true;
			}
		}

		m_vtLineParseResult.push_back(str.substr(locSt, locEd - locSt));
	}

	return !m_vtLineParseResult.empty();
}

bool COBJFile::ReadVerticePosChunk(string& str, OBJECT* pObj)
{
	if (!LineParse(str))
	{
		return false;
	}

	if ((m_vtLineParseResult[0] != "v") || m_vtLineParseResult.size() != 4)
	{
		return false;
	}

	Vertex* pVertex = new Vertex;
	for (int i = 0; i < 3; i++)
	{
		pVertex->c[i] = (float)atof(m_vtLineParseResult[i + 1].c_str());
	}

	pObj->vertices.push_back(pVertex);

	m_nOffsetVertex++;

	return true;
}


bool COBJFile::ReadVerticeNormalChunk(string& str, OBJECT* pObj)
{
	if (!LineParse(str))
	{
		return false;
	}

	if ((m_vtLineParseResult[0] != "vn") || m_vtLineParseResult.size() != 4)
	{
		return false;
	}

	Normal* pNor = new Normal;
	for (int i = 0; i < 3; i++)
	{
		pNor->c[i] = (float)atof(m_vtLineParseResult[i + 1].c_str());
	}

	pObj->normals.push_back(pNor);

	m_nOffsetNormal++;

	return true;
}

bool COBJFile::ReadVerticeUVChunk(string& str, OBJECT* pObj)
{
	if (!LineParse(str))
	{
		return false;
	}

	if ((m_vtLineParseResult[0] != "vt") || ((m_vtLineParseResult.size() != 3) && (m_vtLineParseResult.size() != 4)))
	{
		return false;
	}

	UV* pUV = new UV;
	for (int i = 0; i < 2; i++)
	{
		pUV->c[i] = (float)atof(m_vtLineParseResult[i + 1].c_str());
	}

	pObj->uvs.push_back(pUV);

	m_nOffsetUV++;

	return true;
}

//the index of surface is grouped by three indices.
bool COBJFile::ReadSurfaceIndexChunk(string& str, OBJECT* pObj)
{
	if (!LineParse(str))
	{
		return false;
	}

	if (m_vtLineParseResult[0] != "f")
	{
		return false;
	}

	string strTmp;
	VTSRG::iterator iter = m_vtLineParseResult.begin();

	Surface* pSuf;

	++iter;   //skip first string, "f".
	for (; iter != m_vtLineParseResult.end(); ++iter)
	{
		strTmp = (*iter);
		if (strTmp.find_first_not_of(' ') == strTmp.npos)
		{
			continue;
		}

		int s1 = strTmp.find_first_of('/');
		int s2 = strTmp.find_last_of('/');
		if (s1 == strTmp.npos || s2 == strTmp.npos)
		{
			return false;
		}



		pSuf = new Surface;
		pSuf->_a = atoi(strTmp.substr(0, s1).c_str());                // vertex index
		pSuf->_b = atoi(strTmp.substr(s1 + 1, s2 - s1 - 1).c_str());  // uv index
		pSuf->_c = atoi(strTmp.substr(s2 + 1).c_str());               // normal index

		pObj->surfaces.push_back(pSuf);
	}



	return true;
}

void COBJFile::CleanVTOBJ()
{
	VTOBJ::iterator iter = m_vtOBJ.begin();
	for (; iter != m_vtOBJ.end(); ++iter)
	{
		OBJECT* pObj = (*iter);
		if (0 != pObj)
		{
			for (size_t i = 0; i < pObj->vertices.size(); i++)
			{
				Vertex* pVt = pObj->vertices[i];
				if (0 != pVt)
				{
					delete pVt;
				}
			}
			pObj->vertices.clear();

			for (size_t i = 0; i < pObj->normals.size(); i++)
			{
				Normal* pNor = pObj->normals[i];
				if (0 != pNor)
				{
					delete pNor;
				}
			}
			pObj->normals.clear();

			for (size_t i = 0; i < pObj->uvs.size(); i++)
			{
				UV* puv = pObj->uvs[i];
				if (0 != puv)
				{
					delete puv;
				}
			}
			pObj->uvs.clear();

			for (size_t i = 0; i < pObj->surfaces.size(); i++)
			{
				Surface* psuf = pObj->surfaces[i];
				if (0 != psuf)
				{
					delete psuf;
				}
			}
			pObj->surfaces.clear();
		}
	}


}


