
#include<stdio.h>
#include<stdlib.h>


#include "IEngine.h"
#include "IInputDevice.h"
#include "IUIManager.h"

#ifndef  _WND_OPENGL_PLATFORM_


#include<emscripten/emscripten.h>
#include<emscripten/val.h>

extern "C" {
#include<emscripten/html5.h>
}

#include"CommonWeb.h"

using namespace emscripten;


#endif



extern "C" {
	extern void CallLoadObjFile(const char* pstring);
}


using namespace FW;

static IEngine* g_pEngine = 0;



static bool st = true;
static bool set = true;
void Update()
{
	g_pEngine->Run();
	if (g_pEngine->isStartUp())
	{
		if (st)
		{
			g_pEngine->LoadScene("./resources/Horse/Horse.sce");
			g_pEngine->SetCurrentScene("./resources/Horse/Horse.sce");

			st = false;
		}
	}

	
	
}



int main()
{

	g_pEngine = CreateEngine();
	if (g_pEngine == 0)
	{
		return 0;
	}


	if (!g_pEngine->Initalize(800, 600))
	{
		return 0;
	}


#ifdef _FW_WEBGL_DEBUG_
	EM_ASM({
		   console.log("Create engine success.");
		});
#endif

	//g_pEngine->Run();
#ifndef  _WND_OPENGL_PLATFORM_
	emscripten_set_main_loop(Update, 0, true);
#else
	//while (CRoot::Instance()->Circle()) {}
	while (true)
	{
		Update();
	}

#endif


	return 1;

}

