/*
CShaderAspect

Author: Zhen Yi
Created Date: May 07, 2021

Version: 0.2.0 Alpha
*/

#ifndef _FW_SHADER_ASPECT_
#define _FW_SHADER_ASPECT_

#include<vector>
#include "CPrimatterAspect.h"
#include "CommonPrimatter.h"


namespace FW
{
	class CShaderAspect : public CPrimatterAspect
	{
	public:

		/*
		typedef struct SKeyValue
		{
			const char* key;   //sz pointer
			const char* value; //sz pointer
		}SKeyValue;
		*/

		typedef struct SKeyValue
		{
			CString* key;
			CString* value;
		};

		typedef std::vector<SKeyValue*> VTKV;
		typedef VTKV::iterator VTKV_ITER;


		//Inherite from CAspect
	public:
		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst) { return true; }

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent) { return EPMTSTATE::READY; }

		virtual bool Clone(CAspect* pAptSrc);



		//Inherit from CPrimatterAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);


	public:
		CShaderAspect(ESHDTYPE type = ESHDTYPE::SH_UNKOWN);
		CShaderAspect(const char* pszName, ESHDTYPE type = ESHDTYPE::SH_UNKOWN);
		virtual ~CShaderAspect();


		void AddKeyValue(const char* key, const char* value);
		const char* GetValue(const char* key)
		{
			for (VTKV_ITER iter = m_vtKeyValue.begin(); iter != m_vtKeyValue.end(); iter++)
			{
				if (strcmp((*iter)->key->Get(), key) == 0)
				{
					return (*iter)->value->Get();
				}
			}

			return 0;
		}



	//attribute
	public:
		ESHDTYPE typeShader() { return m_eTypeShader; }
		VTKV& vectorKeyValue() { return m_vtKeyValue; }

	private:
		void ClearSet();
		void Destroy();

	protected:
		VTKV m_vtKeyValue;
		ESHDTYPE m_eTypeShader;
	};


	class CVertexShaderAspect : public CShaderAspect
	{
		//Inherit from CPrimatterAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);


	public:
		CVertexShaderAspect();
		CVertexShaderAspect(const char* pszName);
		virtual ~CVertexShaderAspect();

	};

	class CFragmentShaderAspect : public CShaderAspect
	{
		//Inherit from CPrimatterAspect
	public:
		virtual bool Initialize(const char* pszName, const char* pszNamePathAndFile);


	public:
		CFragmentShaderAspect();
		CFragmentShaderAspect(const char* pszName);
		virtual ~CFragmentShaderAspect();

	};

}

#endif // !_FW_SHADER_ASPECT_
