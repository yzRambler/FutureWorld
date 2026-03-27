/*

CShaderVariableAspect

Author: Zhen Yi


Created Date:  Nov. 18, 2023

Version: 0.2.0 Alpha


*/


#ifndef _FW_SHADERVARIABLE_ASPECT_
#define _FW_SHADERVARIABLE_ASPECT_

#include<string>
#include"CBase.h"
#include"CommonPrimatter.h"

namespace FW
{
	class  CShaderVariableAspect : public CBase
	{
	public:
		CShaderVariableAspect(ESVTYPE typeVar = ESVTYPE::SV_UNKNOW) :m_eTypeShaderVar(typeVar) {}
		CShaderVariableAspect(const char* pszName, ESVTYPE typeVar = ESVTYPE::SV_UNKNOW) :CBase(pszName),
			m_eTypeShaderVar(typeVar) {}

		virtual~CShaderVariableAspect() {}

	//property
	public:
		ESVTYPE typeShaderVar() { return m_eTypeShaderVar; }

	protected:
		ESVTYPE m_eTypeShaderVar;
	};



	class CVertexAttributeAspect : public CShaderVariableAspect
	{
	public:
		CVertexAttributeAspect(EVATYPE typeVA = EVATYPE::VA_UNKNOW) :CShaderVariableAspect(ESVTYPE::SV_VTATTR),
			m_eTypeVertexAttr(typeVA) {}

		CVertexAttributeAspect(const char* pszName, EVATYPE typeVA = EVATYPE::VA_UNKNOW) :
			CShaderVariableAspect(pszName, ESVTYPE::SV_VTATTR), m_eTypeVertexAttr(typeVA) {}

		virtual~CVertexAttributeAspect() {}

		bool Create(ESHDATATYPE dataType, EVATYPE typeVertexAtt, const char* pszVarName);
		bool Clone(CVertexAttributeAspect* pSrcVA);

	//property
	public:
		EVATYPE typeVertexAttribute() { return m_eTypeVertexAttr; }
		const char* nameVar() { return m_strVarName.c_str(); }

		int countComponent() { return m_nCountComponent; }
		int sizeComponent() { return m_nSizeComponent; }

	private:
		//ESHDATATYPE m_eDataType;
		EVATYPE m_eTypeVertexAttr;
		std::string m_strVarName;

		int m_nCountComponent;
		int m_nSizeComponent;
	};



	class CParameterUniformAspect : public CShaderVariableAspect
	{
	public:
		CParameterUniformAspect(ESUTYPE typeSU = ESUTYPE::SU_UNKNOW) :CShaderVariableAspect(ESVTYPE::SV_UNIFORM),
			m_eTypeSUniform(typeSU), m_typeShaderData(ESHDATATYPE::SD_UNKNOW) {
			m_strVarName.clear();
		}

		CParameterUniformAspect(const char* pszName, ESUTYPE typeSU = ESUTYPE::SU_UNKNOW) :
			CShaderVariableAspect(pszName, ESVTYPE::SV_UNIFORM), m_eTypeSUniform(typeSU),
			m_typeShaderData(ESHDATATYPE::SD_UNKNOW)
		{
			m_strVarName.clear();
		}

		virtual ~CParameterUniformAspect() {}

		bool Create(ESHDATATYPE dataType, const char* pszVarName)
		{
			if ((dataType == ESHDATATYPE::SD_UNKNOW) || (0 == pszVarName))
			{
				return false;
			}

			m_typeShaderData = dataType;
			m_strVarName = pszVarName;

			return true;
		}


		//property
	public:
		ESUTYPE typeShaderUniform() { return m_eTypeSUniform; }
		const char* nameVar() { return m_strVarName.c_str(); }
		ESHDATATYPE shaderDataType() { return m_typeShaderData; }

	private:
		ESUTYPE m_eTypeSUniform;
		std::string m_strVarName;
		ESHDATATYPE m_typeShaderData;
	};



	class CParaUniformCameraAspect : public CParameterUniformAspect
	{
	public:
		CParaUniformCameraAspect() : CParameterUniformAspect(ESUTYPE::SU_CAMERA), m_valueType(ESHCAMVALTYPE::SCV_UNKNOW) {}
		CParaUniformCameraAspect(const char* pszName) : CParameterUniformAspect(pszName, ESUTYPE::SU_CAMERA),
			m_valueType(ESHCAMVALTYPE::SCV_UNKNOW) {}

		virtual ~CParaUniformCameraAspect() {}

		bool Create(ESHDATATYPE dataType, const char* pszVarName, const char* pszValue);
		bool Clone(CParaUniformCameraAspect* pPUCA);

		//property
	public:
		ESHCAMVALTYPE valueType() { return m_valueType; }

	private:
		ESHCAMVALTYPE m_valueType;
	};



	class CParaUniformLightAspect : public CParameterUniformAspect
	{
	public:
		CParaUniformLightAspect() :CParameterUniformAspect(ESUTYPE::SU_LIGHT), m_valType(ESHLITVALTYPE::SLV_UNKNOW),
			m_indexOfLightArray(-1) {}
		CParaUniformLightAspect(const char* pszName) :CParameterUniformAspect(pszName, ESUTYPE::SU_LIGHT),
			m_valType(ESHLITVALTYPE::SLV_UNKNOW), m_indexOfLightArray(-1) {}

		virtual ~CParaUniformLightAspect() {}

		bool Create(ESHDATATYPE dataType, const char* pszVarName, int index, const char* pszValue);
		bool Clone(CParaUniformLightAspect* pPULA);

		//property
	public:
		ESHLITVALTYPE valueType() { return m_valType; }
		int indexOfLightArray() { return m_indexOfLightArray; }

	private:
		ESHLITVALTYPE m_valType;
		int m_indexOfLightArray;
	};


	class CParaUniformTextureAspect : public CParameterUniformAspect
	{
	public:
		CParaUniformTextureAspect() :CParameterUniformAspect(ESUTYPE::SU_TEXTURE), m_indexOfTextureArray(-1) {}
		CParaUniformTextureAspect(const char* pszName) :CParameterUniformAspect(pszName, ESUTYPE::SU_TEXTURE),
			m_indexOfTextureArray(-1) {}
		virtual ~CParaUniformTextureAspect() {}

		bool Create(ESHDATATYPE dataType, const char* pszVarName, int index);
		bool Clone(CParaUniformTextureAspect* pPUTA);

	//property
	public:
		int indexOfTextureArray() { return m_indexOfTextureArray; }

	private:
		int m_indexOfTextureArray;
	};



	class CParaUniformWorldTransformAspect : public CParameterUniformAspect
	{
	public:
		CParaUniformWorldTransformAspect() :CParameterUniformAspect(ESUTYPE::SU_WORLDTF) {}
		CParaUniformWorldTransformAspect(const char* pszName) :CParameterUniformAspect(pszName, ESUTYPE::SU_WORLDTF){}
		virtual ~CParaUniformWorldTransformAspect() {}

	};



	//match color vector
	//uniform vector may be vec2 or vec3 or vec4
	class CParaUniformVectorAspect : public CParameterUniformAspect
	{
	public:
		CParaUniformVectorAspect() :CParameterUniformAspect(ESUTYPE::SU_VECTOR), m_x(0.0f), m_y(0.0f), m_z(0.0f),
			m_w(0.0f) {}
		CParaUniformVectorAspect(const char* pszName) :CParameterUniformAspect(pszName, ESUTYPE::SU_VECTOR), m_x(0.0f),
			m_y(0.0f), m_z(0.0f), m_w(0.0f) {}

		virtual ~CParaUniformVectorAspect() {}

		bool Create(ESHDATATYPE typeData, const char* pszName, float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
		{
			m_x = x; m_y = y; m_z = z; m_w = w;
			return CParameterUniformAspect::Create(typeData, pszName);
		}

		bool Clone(CParaUniformVectorAspect* pPUVA);


	//property
	public:
		float x() { return m_x; }
		float y() { return m_y; }
		float z() { return m_z; }
		float w() { return m_w; }


	private:
		float m_x;  //r
		float m_y;  //g
		float m_z;  //b
		float m_w;  //a
	};



	class CParaUniformNumberAspect : public CParameterUniformAspect
	{
	public:
		CParaUniformNumberAspect() :CParameterUniformAspect(ESUTYPE::SU_NUMBER), m_Number(0.0f) {}
		CParaUniformNumberAspect(const char* pszName) :CParameterUniformAspect(pszName, ESUTYPE::SU_NUMBER),
			m_Number(0.0f) {}
		virtual ~CParaUniformNumberAspect() {}

		bool Create(ESHDATATYPE typeData, const char* pszName, float numb)
		{
			m_Number = numb;
			return CParameterUniformAspect::Create(typeData, pszName);
		}

		bool Clone(CParaUniformNumberAspect* pPUNA);

	//property
	public:
		float number() { return m_Number; }

	private:
		float m_Number;
	};


}



#endif // !_FW_SHADERVARIABLE_ASPECT_
