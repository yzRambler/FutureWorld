/*

CUIAspect


Author:  Zhen Yi

Created Date: Feb. 20, 2026

Version: 0.2.0 Alpha


*/


#ifndef _FW_UI_ASPECT_
#define	_FW_UI_ASPECT_

#include"CAspect.h"
#include"CComponentAspect.h"
#include"FWEnginePrimatterManagerExport.h"

namespace FW
{
	class CSceneNodeAspect;
	class CEssetyAspect;
	class CMaterialAspect;
	class CMaterial;
	class  DLLPRAPI CUIAspect: public CComponentAspect
	{
		//Inheriate from CAspect
	public:
		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent);

		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent, CConstruct* pHostCst);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct,
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		


		//Inheriate from CComponentAspect
	public:
		virtual CComponentAspect* CreateCoInstance(CEssetyAspect* pComHost);
		virtual EAPTSTATE CheckState(CAspectCenter* pAptCent, CEssetyAspect* pEsetyApt);


	public:
		CUIAspect(CAspect* pHost = nullptr);
		CUIAspect(const char* pszName, CAspect* pHost = nullptr);
		virtual ~CUIAspect();

		bool Create(const char* pszType, const char* pszNameMaterial, const char* pszNameMaterialFile, int ordTargetSpace, 
			float x, float y, float w, float h);


	public:
		void setUIType(const char* pszType) { m_strType.Set(pszType); }
		const char* nameUIType() { return m_strType.Get(); }

		void setNameMatl(const char* pszNameMatl) { m_strNameMatl.Set(pszNameMatl); }
		const char* nameMatl() { return m_strNameMatl.Get(); }

		void setNameMatlFile(const char* pszNameMatlFile) { m_strNameMatlFile.Set(pszNameMatlFile); }
		const char* nameMatlFile() { return m_strNameMatlFile.Get(); }

		

		void setOrderTargetSpace(int order) { m_nOrderTargetSpace = order; }
		int orderTargetSpace() { return m_nOrderTargetSpace; }

		void setX(float f) { m_x = f; }
		float x() { return m_x; }

		void setY(float f) { m_y = f; }
		float y() { return m_y; }

		void setW(float f) { m_w = f; }
		float w() { return m_w; }

		void setH(float f) { m_h = f; }
		float h() { return m_h; }

		CMaterialAspect* materialApt() { return m_pMatlApt; }



	private:

		CMaterialAspect* m_pMatlApt;
		CMaterial* m_pMatl;

		CString m_strType;
		CString m_strNameMatl;
		CString m_strNameMatlFile;

		int m_nOrderTargetSpace;

		float m_x;
		float m_y;
		float m_w;
		float m_h;


	};
}





#endif // !_FW_UI_ASPECT_
