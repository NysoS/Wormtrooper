#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window.h"

namespace JavaEngine
{
	class JE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		void OnUpdate();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_isRunning = true;
	};

	Application* CreateApplication();
}

#endif