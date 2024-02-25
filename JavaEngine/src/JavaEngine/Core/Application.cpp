#include "Application.h"
#include "Log.h"
#include "JavaEngine/LevelRenderer/Scene.h"

namespace JavaEngine
{
#define BIND_CALLBACK(fn) (std::bind(&fn, this))
#define BIND_CALLBACK_ONE_PARAM(fn) (std::bind(&fn, this, std::placeholders::_1))

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_CALLBACK_ONE_PARAM(Application::OnEvent));
		m_Window->SetEventRenderCallback(BIND_CALLBACK(Application::OnRenderer));
		m_Window->SetUpdateCallback(BIND_CALLBACK_ONE_PARAM(Application::OnUpdate));

		m_BasicScene = std::make_unique<Scene>();
	}

	Application::~Application()
	{
	
	}

	void Application::Run()
	{
		auto previousTime = m_Window->getElapsedTime();
		auto lag = 0.f;

		while (m_isRunning)
		{
			const auto elapsedTime = m_Window->getElapsedTime();
			lag += elapsedTime;

			m_Window->HandleEvent();
			while (lag >= MaxFPS)
			{
				m_Window->OnUpdate(0.1f);
				lag -= MaxFPS;
			}
			
			m_Window->OnRenderer();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CALLBACK_ONE_PARAM(Application::OnCloseWindow));

		m_BasicScene->OnEvent(event);

		for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if(event.IsHandled())
			{
				break;
			}
		}
	}


	void Application::OnUpdate(const float& deltaTime)
	{
		//JE_CORE_INFO("Application Update");
		m_BasicScene->OnUpate(deltaTime);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnUpdate();
		}
	}

	void Application::OnRenderer()
	{
		m_BasicScene->OnRenderer(*m_Window.get());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnRederer();
		}
	}

	bool Application::OnCloseWindow(WindowCloseEvent& event)
	{
		m_isRunning = false;
		JE_CORE_TRACE("Close window");
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


}
