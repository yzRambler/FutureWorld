/*

FWUIExport.h


Author:  Zhen  Yi

Created Date:  Jul. 19, 2025

Version: 0.2.0 Alpha

*/


#ifndef _FW_UI_EXPORT_
#define _FW_UI_EXPORT_



#ifdef _WND_OPENGL_PLATFORM_
#ifdef _UI_MANAGER_
#define DLLUIAPI __declspec(dllexport)
#else
#define DLLUIAPI __declspec(dllimport)
#endif
#else
#define DLLUIAPI
#endif




#endif // !_FW_FWUI_EXPORT_
