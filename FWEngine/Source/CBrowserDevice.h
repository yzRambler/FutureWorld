#ifndef _FW_BROWSER_DEVICE_
#define _FW_BROWSER_DEVICE_

#include"CTime.h"
#include "CDevice.h"

//#ifndef _WND_OPENGL_PLATFORM_
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
//#include <SDL_render.h>
//#include <SDL.h>
//#include <SDL_opengles2.h>
//#include "C:/Users/yz/SDL2/include/SDL.h"
//#include "C:/Users/yz/SDL2/include/SDL_opengles2.h"
//#else
//#endif // !_WND_OPENGL_PLATFORM_

namespace FW
{
	class  CBrowserDevice: public CDevice
    {
		public:
			CBrowserDevice();
			virtual ~ CBrowserDevice();

			virtual bool Create(int width, int height);
			virtual void Destroy();

			virtual bool Update();
		
			virtual void Post();

		private:
    		EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_hContex;
	};
}




#endif
