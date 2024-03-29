#pragma once

#include "jepch.h"

#include "JavaEngine/Core/Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "JavaEngine/Events/ApplicationEvent.h"

namespace JavaEngine
{
	class Scene;

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
		void AddScene(Scene* scene);

	private:
		void OnUpdate(const float& deltaTime);
		void OnRenderer();
		bool OnCloseWindow(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_isRunning = true;
		LayerStack m_LayerStack;
		Scene* m_BasicScene = nullptr;

		static Application* s_Instance;
		static constexpr float MaxFPS = 1.f / 60.f;
	};

	Application* CreateApplication();
}
