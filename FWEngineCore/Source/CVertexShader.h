
/*

CVertexShader


Author:  Zhen Yi - взеђ


Version: 0.2.0 Alpha

*/



#ifndef _FW_VERTEXSHADER_
#define _FW_VERTEXSHADER_
#include<vector>
#include "CShader.h"



namespace FW
{
	class DLLCOAPI CVertexShader : public CShader
	{
	private:
		typedef std::pair<const char*, const char*> PAIR;
		typedef std::vector<PAIR*> VTKV;
		typedef VTKV::iterator VTKV_ITER;

	public:
		CVertexShader(CConstruct* pHost);
		CVertexShader(const char* pszName, CConstruct* pHost);
		virtual ~CVertexShader();

		void AddKeyValue(const char* key, const char* value);

		const char* GetValue(const char* key)
		{
			for (VTKV_ITER iter = m_vtKeyValue.begin(); iter != m_vtKeyValue.end(); iter++)
			{
				if (strcmp((*iter)->first, key) == 0)
				{
					return (*iter)->second;
				}
			}

			return 0;
		}

		//Inherit from CShader
		virtual bool Create(char* pShaderFileBuffer);

	private:
		void Destroy();

	private:
		VTKV m_vtKeyValue;
	};
}

#endif // !_FW_VERTEXSHADER_
