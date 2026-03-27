/*
CCommand

Author:  Zhen Yi

 Created Date: Oct. 26, 2023

 Version: 0.2.0 Alpha

*/


#ifndef  _FW_COMMAND_
#define _FW_COMMAND_


namespace FW
{
	class CCommand
	{
	public:
		CCommand() {}
		virtual ~CCommand() {}

		virtual bool Initialize(const char* pParam) { return true; }
		virtual void Execute() = 0;
	};


}




#endif // ! _FW_COMMAND_
