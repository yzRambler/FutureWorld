/*

CParameterUniform


Author: Zhen Yi

Created Date: Nov. 18, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_PARAMETER_UNIFORM_
#define _FW_PARAMETER_UNIFORM_

#include<vector>
#include<string>
#include <GL/glew.h>

#include"CShaderVariable.h"
#include"CommonPrimatter.h"
#include"FWEngineCoreExport.h"

#include"MathLibrary.h"



namespace FW
{
	class DLLCOAPI CParameterUniform : public CShaderVariable
	{
	public:
		CParameterUniform(ESUTYPE type = ESUTYPE::SU_UNKNOW);
		CParameterUniform(const char* pszName, ESUTYPE type = ESUTYPE::SU_UNKNOW);
		virtual ~CParameterUniform();

		bool Create(ESHDATATYPE dataType, const char* pszVarName);
		virtual void Process() = 0;

	//property
	public:
		ESUTYPE typeShaderUniform() { return m_eTypeSUniform; }
		const char* nameVar() { return m_strVarName.c_str(); }
		ESHDATATYPE shaderDataType() { return m_typeShaderData; }
		void setProgramID(GLuint idProgram) { m_idProgram = idProgram; }

		bool active() { return m_bActive; }
		void setActive(bool active) { m_bActive = active; }

	protected:
		GLuint m_idProgram;
		bool m_bActive;

	private:
		ESUTYPE m_eTypeSUniform;
		std::string m_strVarName;
		ESHDATATYPE m_typeShaderData;
	};


	class DLLCOAPI CParaUniformCamera : public CParameterUniform
	{
	private:
		typedef void (CParaUniformCamera::*PFUNC)();


	public:
		CParaUniformCamera();
		CParaUniformCamera(const char* pszName);
		virtual ~CParaUniformCamera();

		bool Create(ESHDATATYPE dataType, const char* pszVarName, ESHCAMVALTYPE valType);

		void BindVectorValue(Vector3& v3)
		{
			m_v3Value = v3; m_pWorkFun = &CParaUniformCamera::funApplyVector;
		}

		void BindMatrixValue(Matrix4x4& mat4)
		{
			m_mat4Value = mat4; m_mat4Output = m_mat4Value;  m_pWorkFun = &CParaUniformCamera::funApplyMatrix;
		}

		void ComputeOutputMatrix(Matrix4x4& mat4)
		{
			m_mat4Output = mat4;
			m_mat4Output *= m_mat4Value;
		}


	//Inherit from CParameterUniform
	public:
		virtual void Process() { (this->*m_pWorkFun)(); }


	//Property
	public:
		ESHCAMVALTYPE valueType() { return m_valueType; }
		Matrix4x4& mat() { return m_mat4Value; }

	private:
		void funApplyMatrix()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }

			//m_mat4Value.Transpose();
			//glUniformMatrix4fv(local, 1, GL_FALSE, (GLfloat*)(&m_mat4Value[0][0]));
			m_mat4Output.Transpose();
			glUniformMatrix4fv(local, 1, GL_FALSE, (GLfloat*)(&m_mat4Output[0][0]));
		}

		void funApplyVector()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform3fv(local, 1, (GLfloat*)(&m_v3Value));
		}

	private:
		ESHCAMVALTYPE m_valueType;
		Vector3 m_v3Value;
		Matrix4x4 m_mat4Value;
		Matrix4x4 m_mat4Output;

		PFUNC m_pWorkFun;
	};



	class DLLCOAPI CParaUniformLight : public CParameterUniform
	{
	private:
		typedef void (CParaUniformLight::*PFUNC)();

	public:
		CParaUniformLight();
		CParaUniformLight(const char* pszName);
		virtual ~CParaUniformLight();

		bool Create(ESHDATATYPE dataType, const char* pszVarName, int index, ESHLITVALTYPE valType);

		void BindFloatValue(float fv)
		{
			m_fValue = fv; m_pWorkFun = &CParaUniformLight::funApplyFloat;
		}

		void BindVector3Value(Vector3& v3)
		{
			m_v3Value = v3; m_pWorkFun = &CParaUniformLight::funApplyVector3;
		}


		void BindVector4Value(Vector4& v4)
		{
			m_v4Value = v4; m_pWorkFun = &CParaUniformLight::funApplyVector4;
		}



	//Inherit from CParameterUniform
	public:
		virtual void Process() { (this->*m_pWorkFun)(); }


	//property
	public:
		ESHLITVALTYPE valueType() { return m_valType; }
		int indexOfLightArray() { return m_indexOfLightArray; }

	private:
		void funApplyFloat()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform1f(local, m_fValue);
		}

		void funApplyVector3()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform3fv(local, 1, (GLfloat*)(&m_v3Value));
		}

		void funApplyVector4()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform4fv(local, 1, (GLfloat*)(&m_v4Value));
		}

	private:
		ESHLITVALTYPE m_valType;
		int m_indexOfLightArray;

		float m_fValue;
		Vector3 m_v3Value;
		Vector4 m_v4Value;

		PFUNC m_pWorkFun;
	};



	class DLLCOAPI CParaUniformTexture : public CParameterUniform
	{
	//private:
	//	typedef void (CParaUniformTexture::*PFUNC)();

	public:
		CParaUniformTexture();
		CParaUniformTexture(const char* pszName);
		virtual ~CParaUniformTexture();

		bool Create(ESHDATATYPE dataType, const char* pszVarName, int index);

	//Inherit from CParameterUniform
	public:
		virtual void Process()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0)
			{
				return;
			}

			//Active the texture unit (example. GL_TEXTURE0)
			glActiveTexture(m_eTextureUnitId);

			//Bind current 2D texture unit generated before to the texture unit actived.
			glBindTexture(GL_TEXTURE_2D, m_uTextureId);

			//Set the sampler texture unit to m_indexMaterialArray which is matching m_eTextureUnitId.
			//(example: 0 corresponding GL_TEXTURE0, 1 corresponding GL_TEXTURE0, ... )
			glUniform1i(local, m_indexOfTextureArray);
		}

	//property
	public:
		int indexOfTextureArray() { return m_indexOfTextureArray; }
		void setTextureId(GLuint idTexture) { m_uTextureId = idTexture; }
		void setTextureUnitId(GLenum idTextureUnit) { m_eTextureUnitId = idTextureUnit; }

	private:
		int m_indexOfTextureArray;

		// Correspond with the element of texture array in CMaterial object.
		// The element index equal m_indexMaterialArray.
		GLenum m_eTextureUnitId;    
		
		// be generated by OpenGLES interface function.
		GLuint m_uTextureId;

		//PFUNC m_pWorkFun;
	};




	class DLLCOAPI CParaUniformWorldTransform : public CParameterUniform
	{
	public:
		CParaUniformWorldTransform() :CParameterUniform(ESUTYPE::SU_WORLDTF) {}
		CParaUniformWorldTransform(const char* pszName) : CParameterUniform(pszName, ESUTYPE::SU_WORLDTF) {}
		virtual ~CParaUniformWorldTransform() {}

	//Inherit from CParameterUniform
	public:
		virtual void Process()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0)
			{
				return;
			}

			//glUniformMatrix4fv(local, 1, GL_FALSE, (GLfloat*)(&m_matWorld[0][0]));
			m_matWorld.Transpose();
			glUniformMatrix4fv(local, 1, GL_FALSE, (GLfloat*)(&m_matWorld[0][0]));
		}


	//attribute
	public:
		void setWorldMatrix(Matrix4x4& matWorld){ m_matWorld = matWorld; }


	private:
		Matrix4x4 m_matWorld;
	};



	class DLLCOAPI CParaUniformVector : public CParameterUniform
	{
	public:
		CParaUniformVector() :CParameterUniform(ESUTYPE::SU_VECTOR)//, m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f) 
		{}

		CParaUniformVector(const char* pszName) :CParameterUniform(pszName, ESUTYPE::SU_VECTOR)
			//, m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f) 
		{}

		virtual ~CParaUniformVector() {}

		bool Create(ESHDATATYPE typeData, const char* pszName, float x = 0.0f, float y = 0.0f, float z = 0.0f,
			float w = 0.0f)
		{
			//m_x = x; m_y = y; m_z = z; m_w = w;
			m_v4Value.x = x;
			m_v4Value.y = y;
			m_v4Value.z = z;
			m_v4Value.w = w;

			return CParameterUniform::Create(typeData, pszName);
		}

	//Inherit from CParameterUniform
	public:
		virtual void Process()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform4fv(local, 1, (GLfloat*)(&m_v4Value));
		}


	private:
		//float m_x;  //r
		//float m_y;  //g
		//float m_z;  //b
		//float m_w;  //a

		Vector4 m_v4Value;
	};



	class DLLCOAPI CParaUniformColor : public CParameterUniform
	{
	public:
		CParaUniformColor() :CParameterUniform(ESUTYPE::SU_COLOR)
		{}

		CParaUniformColor(const char* pszName) :CParameterUniform(pszName, ESUTYPE::SU_COLOR)
		{}

		virtual ~CParaUniformColor() {}

		bool Create(const char* pszName, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f)
		{
			m_v4Color.x = r; m_v4Color.y = g; m_v4Color.z = b; m_v4Color.w = a;
			return CParameterUniform::Create(ESHDATATYPE::SD_VEC4, pszName);
		}

		void Update(float r, float g, float b, float a)
		{
			m_v4Color.x = r; m_v4Color.y = g; m_v4Color.z = b; m_v4Color.w = a;
		}


	//Inherit from CParameterUniform
	public:
		virtual void Process()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform4fv(local, 1, (GLfloat*)(&m_v4Color));
		}


	private:
		//float m_r;
		//float m_g;
		//float m_b;
		//float m_a;

		Vector4 m_v4Color;
	};



	class DLLCOAPI CParaUniformNumber : public CParameterUniform
	{
	private:
		typedef void (CParaUniformNumber::*PFUNC)();

	public:
		CParaUniformNumber() :CParameterUniform(ESUTYPE::SU_NUMBER), m_Number(0.0f), m_pWorkFun(0) {}
		CParaUniformNumber(const char* pszName):CParameterUniform(pszName, ESUTYPE::SU_NUMBER), m_Number(0.0f), 
			m_pWorkFun(0)
		{}

		virtual ~CParaUniformNumber(){}

		bool Create(ESHDATATYPE typeData, const char* pszName, float numb)
		{
			m_Number = numb;
			return CParameterUniform::Create(typeData, pszName);
		}

		void BindNumber(float fv)
		{
			m_Number = fv; 
			m_pWorkFun =  (shaderDataType() == ESHDATATYPE::SD_FLOAT)? &CParaUniformNumber::funApplyFloatNumber
				:((shaderDataType() == ESHDATATYPE::SD_INT)? &CParaUniformNumber::funApplyIntNumber : 0);
		}

	//Inherit from CParameterUniform
	public:
		virtual void Process() { (this->*m_pWorkFun)(); }

	private:
		void funApplyFloatNumber()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform1f(local, m_Number);
		}

		void funApplyIntNumber()
		{
			GLint local = glGetUniformLocation(m_idProgram, nameVar());
			if (local < 0) { return; }
			glUniform1i(local, (int)m_Number);
		}


	private:
		float m_Number;
		PFUNC m_pWorkFun;
	};
}



#endif // !_FW_PARAMETER_UNIFORM_
