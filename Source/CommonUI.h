/*
CommonUI

Author: Zhen Yi -- взеђ

Created Date: Feb. 1, 2024

Version: 0.2.0 Alpha

*/





#ifndef _FW_COMMON_UI_
#define _FW_COMMON_UI_

namespace FW
{

	typedef enum eUIType {
		UI_BUTTON = 0, UI_PANEL, UI_TEXTBOX, UI_WINDOW, UI_COUNT, UI_UNKNOW
	}EUITYPE;


	typedef enum eUICommand {
		UIC_PLAYANI = 0, UIC_STOPANI, UIC_UNKNOW
	}EUICOMD;
}




#endif // !_FW_COMMON_UI_
