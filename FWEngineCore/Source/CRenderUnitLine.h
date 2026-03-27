/*

CRenderUnitLine



Author:  Zhen Yi      взеђ

Created Date:  Jan. 18, 2024

Version: 0.2.0 Alpha

*/


#ifndef _FW_RENDERUNIT_LINE_
#define _FW_RENDERUNIT_LINE_

#include"CRenderUnit.h"


namespace FW
{
	class Vector4;
	class CRenderUnitLine : public CRenderUnit
	{
	public:
		CRenderUnitLine(CConstruct* pHost);
		CRenderUnitLine(const char* pszName, CConstruct* pHost);

		virtual ~CRenderUnitLine();

	//Inherit from CRenderUnit
	public:
		virtual void Initialize(int countVertexBuffer, int countIndexBuffer);
		virtual void Rendering(CMaterial* pMatl, int indexPass);

		virtual void BindModel();
		virtual void UnbindMode();

	//attribute
	public:
		void setColor(Vector4& color);

	protected:
		virtual int countSurfaceComponent() { return 2; }

	private:
		GLuint m_idVB;
		Vector4* m_pColor;
	};

}


#endif // !_FW_RENDERUNIT_LINE_
