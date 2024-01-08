#include "jepch.h"

#include "WindowsWindow.h"
#include "JavaEngine/Log.h"

namespace JavaEngine
{
	static bool s_SFMLInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		JE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		m_Window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(m_Data.Width, m_Data.Height)), m_Data.Title);

		SetVSync(true);

		shape.setFillColor(sf::Color::Green);
	}

	void WindowsWindow::Shutdown()
	{
		m_Window->close();
	}

	void WindowsWindow::OnUpdate()
	{
		JE_CORE_INFO("OnUpdate SFML Window!");
	}

	void WindowsWindow::OnRenderer()
	{
		m_Window->clear();
		m_Window->draw(shape);
		m_Window->display();
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
		{
			m_Window->setVerticalSyncEnabled(true);
		}else
		{
			m_Window->setVerticalSyncEnabled(false);
		}

		m_Data.VSync = enable;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


};
