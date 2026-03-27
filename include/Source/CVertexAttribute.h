/*
CVertexAttribute

Author:  Zhen Yi

Created Date: Aug. 27, 2023

Version: 0.2.0 Alpha

*/


#ifndef _FW_VERTEX_ATTRIBUTE_
#define _FW_VERTEX_ATTRIBUTE_

#include<string>
#include"CShaderVariable.h"
#include"CommonPrimatter.h"


namespace FW
{
	class DLLCOAPI CVertexAttribute : public CShaderVariable
	{
	public:
		CVertexAttribute();
		CVertexAttribute(const char* pszName);
		virtual~ CVertexAttribute();

		void Initialize(EVATYPE type, const char* pszVarName, int countComponent, int sizeComponent, int offset);
		bool Copy(CVertexAttribute* pSrcVA);

	//attribute
	public:
		int count() { return m_nCountComponent; }
		//void setCount(int countElement) { m_nCountComponent = countElement; }

		int local() { return m_nOffset; }
		void setLocal(int nOffset) { m_nOffset = nOffset; }

		int sizeComponent() { return m_nSizeComponent; }

		int size() { return m_nSize; }

		EVATYPE typeVertexAttr() { return m_eTypeVertexAttr; }

		const char* varName() { return m_strVarName.c_str(); }


	private:
		EVATYPE m_eTypeVertexAttr;

		int m_nCountComponent;
		int m_nSizeComponent;
		int m_nOffset;
		int m_nSize;

		std::string m_strVarName;
	};
}

#endif // !_FW_VERTEX_ATTRIBUTE_
