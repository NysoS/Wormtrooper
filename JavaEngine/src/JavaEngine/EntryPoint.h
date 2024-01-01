#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H
#include "../JavaEngine.h"

#ifdef JE_PLATFORM_WINDOWS

extern JavaEngine::Application* JavaEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = JavaEngine::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error JavaEngine only supports Windows!
#endif

#endif