
/*

CLight

Author: Zhen Yi  --  взеђ


Version: 0.2.0 Alpha


*/


#ifndef _FW_LIGHT_
#define _FW_LIGHT_

#include"CComponent.h"
#include"CSceneNode.h"
#include"MathLibrary.h"
#include"FWEngineCoreExport.h"

namespace FW
{
	class DLLCOAPI CLight : public CComponent
	{
	public:
		typedef enum eLightType{
			LT_POINT=0, LT_DIRECT, LT_SPOT, LT_UNKNOW
		}ELITTYPE;

	public:
		CLight(CConstruct* pHost, 
			ELITTYPE type = ELITTYPE::LT_UNKNOW);

		CLight(const char* pszName, CConstruct* pHost,  
			ELITTYPE type = ELITTYPE::LT_UNKNOW);

		virtual ~CLight();
		virtual bool Create(FDWORD idSpaceTime) { m_idTargetSpaceTime = idSpaceTime;  return true; }



	//Inheriate from CComponent
	public:
		virtual void Update(long lDltTime, CEssety* pEty, IPrimatterManager* pPmtCent) {}


	//attribute
	public:
		ELITTYPE typeLight() { return m_typeLight; }
		void setTypeLight(ELITTYPE type) { m_typeLight = type; }

		Vector4& color() { return m_v4Color; }
		void setColor(float r, float g, float b, float a)
		{
			m_v4Color.x = r; m_v4Color.y = g; m_v4Color.z = b; m_v4Color.w = a;
		}

		Vector3& pos() { return ((CSceneNode*)m_pHost)->spaceWorld()->pos(); }

		float intensity() { return m_fIntensity; }
		void setIntensity(float intensity) { m_fIntensity = intensity; }

		int orderTargetSpace() { return m_nTargetSpaceOrder; }
		void setTargetSpaceOrder(int order) { m_nTargetSpaceOrder = order; }

		FDWORD targetSpaceTimeID() { return m_idTargetSpaceTime; }

	private:
		ELITTYPE m_typeLight;
		Vector4 m_v4Color;

		float m_fIntensity;

		int m_nTargetSpaceOrder;
		FDWORD m_idTargetSpaceTime;

	};
}



#endif // !_FW_LIGHT_
