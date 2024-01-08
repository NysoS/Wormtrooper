#include "Application.h"

#include "Log.h"

namespace JavaEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			m_Window->OnUpdate();
			m_Window->OnRenderer();
		}
	}

	void Application::OnUpdate()
	{
		
	}

}
