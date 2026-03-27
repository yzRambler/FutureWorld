/*

CLightAspect


Author:  Zhen Yi

Created Date: Oct. 28, 2023

Version: 0.2.0 Alpha

*/

#ifndef _FW_LIGHT_ASPECT_
#define _FW_LIGHT_ASPECT_

#include"CommonPrimatter.h"
#include"CComponentAspect.h"
#include"MathLibrary.h"


namespace FW
{
	class CLightAspect : public CComponentAspect
	{
	public:
		CLightAspect(CAspect* pHost);
		CLightAspect(const char* pszName, CAspect* pHost);
		virtual ~CLightAspect();

		bool Create(int sceneTimeOrder);
		void GenerateSpaceTimeID();


	//Inherited from CComponentAspect
	public:

		virtual EAPTSTATE CheckState(CAspectCenter* pAtpCent, CEssetyAspect* pEsetyApt)
		{
			return EAPTSTATE::APT_READY;
		}


		virtual bool InitializeCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent, CConstruct* pHostCst /*=nullptr*/);

		virtual EPMTSTATE CheckCorrelateConstruct(CConstruct** ppConstruct, 
			IPrimatterManager* pPmtCent);

		virtual bool Clone(CAspect* pAptSrc);
		virtual CComponentAspect* CreateCoInstance(CEssetyAspect* pComHost);

	//attribute
	public:
		float intensity() { return m_fIntensity; }
		void setIntensity(float intensity) { m_fIntensity = intensity; }

		Vector4& color() { return m_v4Color; }
		void setColor(float r, float g, float b, float a) 
		{ m_v4Color.x = r; m_v4Color.y = g; m_v4Color.z = b; m_v4Color.w = a; }

		ELITTYPE typeLight() { return m_eLitType; }
		void setLightType(ELITTYPE type) { m_eLitType = type; }

		int orderTargetSpace() { return m_nTargetSpaceOrder; }
		void setTargetSpaceOrder(int order) { m_nTargetSpaceOrder = order; }

		FDWORD targetSpaceTimeID() { return m_idTargetSpaceTime; }

	private:
		int m_nSceneTimeOrder;
		int m_nTargetSpaceOrder;
		FDWORD m_idTargetSpaceTime;

		float m_fIntensity;

		Vector4 m_v4Color;
		ELITTYPE m_eLitType;
	};
}




#endif // !_FW_LIGHT_ASPECT_
