#include "Application.h"

#include "Log.h"

#define BIND_CALLBACK(fn) (std::bind(&fn, this, std::placeholders::_1))

namespace JavaEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_CALLBACK(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			m_Window->HandleEvent();
			OnUpdate();
			m_Window->OnRenderer();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CALLBACK(Application::OnCloseWindow));

		for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if(event.IsHandled())
			{
				break;
			}
		}
	}


	void Application::OnUpdate()
	{
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnUpdate();
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
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}


}
