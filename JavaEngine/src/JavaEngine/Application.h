#ifndef APPLICATION_H
#define APPLICATION_H

#include "jepch.h"

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace JavaEngine
{
	class JE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

	private:
		void OnUpdate();
		bool OnCloseWindow(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_isRunning = true;
	};

	Application* CreateApplication();
}

#endif