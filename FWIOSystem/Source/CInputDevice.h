/*

CInputDevice


Author: Zhen Yi

Version: 0.2.0 Alpha


*/


#ifndef _FW_INPUTDEVICE_
#define _FW_INPUTDEVICE_

#include<map>

#include "IInputDevice.h"
#include "CMouse.h"

namespace FW
{
	class CKeyboard;
	class CInputDevice : public IInputDevice
	{
		typedef std::map< FDWORD, CIOListener*> MAPLST;
		typedef MAPLST::iterator MAPLST_ITER;

	public:
		CInputDevice();
		virtual ~CInputDevice();

	
		static CInputDevice* Instance() 
		{
			if (nullptr == m_pInstance)
			{
				m_pInstance = new CInputDevice();
			}

			return m_pInstance;
		}


		static void Release()
		{
			if (nullptr != m_pInstance)
			{
				m_pInstance->Destroy();

				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}
		
		void Create(CMsgCenter* pMsgCent);
		void Destroy();


	//derivate from IInputDevice
	public:
		virtual void OnMouseButtonDown(int orderMB)
		{  if (0 != m_pMouse){	m_pMouse->OnMouseButtonDown(orderMB);} }

		virtual void OnMouseButtonUp(int orderMB)
		{  if (0 != m_pMouse){  m_pMouse->OnMouseButtonUp(orderMB);} }

		virtual void OnMouseMove(int x, int y)
		{	if (0 != m_pMouse){	m_pMouse->OnMouseMove(x, y); } }

		virtual void Process(int wx, int wy, int ww, int wh, int sw, int sh);


	//attribute
	public:
		CKeyboard& key() { return *m_pKeyboard; }
		CMouse& mouse() { return *m_pMouse; }



	private:
		static CInputDevice* m_pInstance;

		CKeyboard* m_pKeyboard;
		CMouse* m_pMouse;

		MAPLST m_mapListener;
	};

};

#endif // !_FW_INPUTDEVICE_
