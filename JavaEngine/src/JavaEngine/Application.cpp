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
			m_Window->OnUpdate();
			m_Window->OnRenderer();
		}
	}

	void Application::OnEvent(Event& event)
	{
		JE_CORE_INFO("{0}", event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_CALLBACK(Application::OnCloseWindow));
	}


	void Application::OnUpdate()
	{
		
	}

	bool Application::OnCloseWindow(WindowCloseEvent& event)
	{
		m_isRunning = false;
		JE_CORE_TRACE("Close window");
		return true;
	}
}
