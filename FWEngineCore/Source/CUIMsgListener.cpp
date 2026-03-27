#include"CUIMsgListener.h"
#include"CMessage.h"
#include"CUIButton.h"
#include"CScene.h"
#include"ISceneManager.h"


using namespace FW;


Vector4 v4Pos;
void CUIMsgListener::OnCallback(void* p)
{
	
	if (((CUI*)m_pHost)->typeUI() != EUITYPE::UI_UNKNOW)
	{
		CMsgBase* pMsg = (CMsgBase*)p;
		if (pMsg->type == EMSGTYPE::MSG_MMOVE)
		{
			CMsgMSMove* mm = (CMsgMSMove*)pMsg;
			v4Pos.x = mm->scrX();
			v4Pos.y = mm->scrY();
			v4Pos.z = 0.0f;
			v4Pos.w = 1.0f;

			Matrix4x4& matS2W = CreateSceneManager()->GetCurrentScene()->matSToWByUICam();
			v4Pos = Mul4(v4Pos, matS2W);

			mm->setX(v4Pos.x);
			mm->setY(v4Pos.y);
			mm->setZ(v4Pos.z);

			//pMsg = mm;

		}


		((CUI*)m_pHost)->ProcessMsg(*pMsg);
	}
}