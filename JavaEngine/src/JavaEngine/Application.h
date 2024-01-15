#ifndef APPLICATION_H
#define APPLICATION_H

#include "jepch.h"

#include "JavaEngine/Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

#include <SFML/System/Clock.hpp> //Test only

namespace JavaEngine
{
	class JE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		void OnUpdate();
		bool OnCloseWindow(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_isRunning = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

#endif