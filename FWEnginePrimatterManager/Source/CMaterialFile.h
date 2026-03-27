/*

CMaterialFile


Author: Zhen Yi
Created Date: April 4, 2022

Version: 0.2.0 Alpha

*/

#ifndef _FW_MATERIALFILE_
#define _FW_MATERIALFILE_

#include"CTextFile.h"

#ifdef _WND_OPENGL_PLATFORM_

#include"cJSON/cJSON.h"

#else

#include"cJSON.h"

#endif // _WND_OPENGL_PLATFORM_



namespace FW
{
	class CMaterialAspect;
	class CTextureUnitAspect;
	class CTextureAspect;
	class CProgramAspect;
	class CPassAspect;
	class CVertexShaderAspect;
	class CFragmentShaderAspect;
	class CVertexAttributeAspect;
	class CParameterUniformAspect;
	class CCommandAspect;
	class CMaterialFile : public CTextFile
	{
	public:
		typedef struct SKV
		{
			char* key;
			char* value;
		}SKeyValue;

	public:
		CMaterialFile(const char* pszName);
		CMaterialFile(const char* pszName, const char* pszNameFile);
		virtual ~CMaterialFile();

		//derive from CTextFile
		virtual bool Parse();
		virtual bool isSkippedLine(std::string& str) { return true; }


	//attribute
	public:
		CMaterialAspect* materialAspect() { return m_pMatlApt; }


	private:
		bool CreateMaterialAspect(cJSON* pJS);
		CPassAspect* CreatePassAspect(cJSON* pJS, CMaterialAspect* pHost);
		CTextureUnitAspect* CreateTextureUnitAspect(cJSON* pJS, CMaterialAspect* pHost);
		CTextureAspect* CreateTextureAspect(cJSON* pJS, CTextureUnitAspect* pHost);
		//CProgramAspect* CreateProgramAspect(cJSON* pJS, CMaterialAspect* pHost);
		CProgramAspect* CreateProgramAspect(cJSON* pJS, CPassAspect* pHost);
		CVertexAttributeAspect* CreateVertexAttributeAspect(cJSON* pJS);
		CParameterUniformAspect* CreateParameterUniformAspect(cJSON* pJS);
		CCommandAspect* CreateCommandAspect(cJSON* pJS);

		bool InitializeVertexAttrSet(cJSON* pJS, CProgramAspect* pProgApt);
		bool InitializeParaUniformSet(cJSON* pJS, CProgramAspect* pProgApt);
		bool InitializeVertexShaderAspect(cJSON* pJS, CVertexShaderAspect& rVSApt);
		bool InitializeFragmentShaderAspect(cJSON* pJS, CFragmentShaderAspect& rFGApt);

		SKeyValue CreateKeyValue(cJSON* pJS)
		{
			SKeyValue kv;
			cJSON* pKVCom = pJS->child;
			while (pKVCom)
			{
				if (strcmp(pKVCom->string, "Key") == 0)
				{
					kv.key = pKVCom->valuestring;
				}
				else if (strcmp(pKVCom->string, "Value") == 0)
				{
					kv.value = pKVCom->valuestring;
				}

				pKVCom = pKVCom->next;
			}

			return kv;
		}


		void Destroy();

		ESHDATATYPE GetDataType(const char* pszString);

	private:
		cJSON* m_pJSSource;
		CMaterialAspect* m_pMatlApt;
	};

};


#endif // !_FW_MATERIALFILE_
