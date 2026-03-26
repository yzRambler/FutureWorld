/*
CDevice

Author: Zhen Yi
Created Date: May 16, 2021

Version: 0.2.0 Alpha

*/


#ifndef  _FW_DEVICE_
#define _FW_DEVICE_


#include"IInputDevice.h"


namespace FW
{
	class CDevice
    {
		public:
		    CDevice():m_pIIDevice(0){}
	        virtual ~CDevice(){}

	        virtual bool Create(int width, int height, IInputDevice* pIIDevice) 
			{ 
				if (0 == pIIDevice)
				{
					return false;
				}

				m_nWidthWnd = width; m_nHeightWnd = height; 
				m_pIIDevice = pIIDevice;

				return true; 
			}

	        virtual void Destroy(){}
	
			virtual bool Update();

	        virtual void Post(){}

	        int GetWndWidth() { return m_nWidthWnd; }
	        int GetWndHeight() { return m_nHeightWnd; }
			int GetScreenWidth() { return m_nWidthScrn; }
			int GetScreenHeight() { return m_nHeightScrn; }

			virtual void GetWndPos(int* px, int* py) { *px = 0; *py = 0; }
		
		protected:
			IInputDevice* m_pIIDevice;

		    int m_nWidthWnd;
			int m_nHeightWnd;
			int m_nWidthScrn;
			int m_nHeightScrn;
	};
	
} // namespace  FW



#endif // ! _FW_DEVICE_

