#pragma once

#ifdef JE_PLATFORM_WINDOWS

extern JavaEngine::Application* JavaEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		JavaEngine::Log::Init();
		JE_CORE_WARN("Initialized JavaEngine Log!");
		JE_INFO("Initialized App Log!");

		auto app = JavaEngine::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error JavaEngine only supports Windows!
#endif