#include "jepch.h"
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
		std::thread UpdateThread(std::bind(&Application::OnUpdate, this));
		while (m_isRunning)
		{
			m_Window->OnRenderer();
		}
	}

	void Application::OnUpdate()
	{
		while (m_isRunning)
		{
			m_Window->OnUpdate();
		}
	}

}
